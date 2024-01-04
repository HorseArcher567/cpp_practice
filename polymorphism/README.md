# Polymorphism（多态性）

## 1、 function overriding（函数重写）
- 出现在类的继承关系中，即派生类中的函数与基类中的函数具有**相同的名称和签名**。
- 派生类中的函数重新定义（override）了基类中的同名函数。
- 重写是**运行时多态性**的一种表现，通过**虚函数和虚函数表**实现。
- 在基类中，通过 virtual 关键字声明一个函数为虚函数，派生类中使用 override 关键字表示重写基类函数。

### 1.1 normal_inherit（普通继承）
#### 1.1.1 对于钻石继承，存在二义性和资源浪费
二义性：
```c++
std::cout << "Ambiguity：" << std::endl;
std::cout << "	derived->BaseA::s: " << derived->BaseA::s << std::endl;
std::cout << "	derived->BaseB::s: " << derived->BaseB::s << std::endl;
```

资源浪费：
```c++
auto as = reinterpret_cast<uintptr_t>(&derived->BaseA::s);
auto bs = reinterpret_cast<uintptr_t>(&derived->BaseB::s);
EXPECT_NE(as, bs);
```

对象内部结构和虚函数表：
```c++
(gdb) p *derived 
$2 = {
  <normal_inherit::BaseA> = {
    <normal_inherit::Base> = {
      _vptr$Base = 0x10007da48 <vtable for normal_inherit::Derived+16>,
      s = 10
    }, 
    members of normal_inherit::BaseA:
    a = 20
  }, 
  <normal_inherit::BaseB> = {
    <normal_inherit::Base> = {
      _vptr$Base = 0x10007da70 <vtable for normal_inherit::Derived+56>,
      s = 10
    }, 
    members of normal_inherit::BaseB:
    b = 30
  }, 
  <normal_inherit::BaseC> = {
    _vptr$BaseC = 0x10007da98 <vtable for normal_inherit::Derived+96>,
    c = 40
  }, 
  members of normal_inherit::Derived:
  d = 50
}

(gdb) info vtbl derived 
vtable for 'normal_inherit::Derived' @ 0x10007da48 (subobject @ 0x600002f18000):
[0]: 0x100006750 <normal_inherit::Derived::~Derived()>
[1]: 0x100006770 <normal_inherit::Derived::~Derived()>
[2]: 0x1000067a0 <normal_inherit::Derived::foo()>

vtable for 'normal_inherit::BaseB' @ 0x10007da70 (subobject @ 0x600002f18018):
[0]: 0x1000067f0 <non-virtual thunk to normal_inherit::Derived::~Derived()>
[1]: 0x100006810 <non-virtual thunk to normal_inherit::Derived::~Derived()>
[2]: 0x100006830 <non-virtual thunk to normal_inherit::Derived::foo()>

vtable for 'normal_inherit::BaseC' @ 0x10007da98 (subobject @ 0x600002f18030):
[0]: 0x100006850 <non-virtual thunk to normal_inherit::Derived::~Derived()>
[1]: 0x100006870 <non-virtual thunk to normal_inherit::Derived::~Derived()>
[2]: 0x100006890 <non-virtual thunk to normal_inherit::Derived::foo()>
```


### 1.2 virtual_inherit（虚继承）
#### 1.2.1 解决钻石继承的二义性和资源浪费
解决二义性：
```c++
std::cout << "derived->s " << derived->s << std::endl;
std::cout << "derived->BaseA::s " << derived->BaseA::s << std::endl;
std::cout << "derived->BaseB::s " << derived->BaseB::s << std::endl;
```

解决资源浪费：
```c++
auto as = reinterpret_cast<uintptr_t>(&derived->BaseA::s);
auto bs = reinterpret_cast<uintptr_t>(&derived->BaseB::s);
EXPECT_EQ(as, bs);
EXPECT_EQ(as, reinterpret_cast<uintptr_t>(&derived->s));
```

类内部结构和虚函数表：
```c++
(gdb) p *derived
$1 = {
  <virtual_inherit::BaseA> = {
    <virtual_inherit::Base> = {
      _vptr$Base = 0x10007dd40 <vtable for virtual_inherit::Derived+184>,
      s = 10
    }, 
    members of virtual_inherit::BaseA:
    _vptr$BaseA = 0x10007dca0 <vtable for virtual_inherit::Derived+24>,
    a = 20
  }, 
  <virtual_inherit::BaseB> = {
    members of virtual_inherit::BaseB:
    _vptr$BaseB = 0x10007dcd8 <vtable for virtual_inherit::Derived+80>,
    b = 30
  }, 
  <virtual_inherit::BaseC> = {
    _vptr$BaseC = 0x10007dd00 <vtable for virtual_inherit::Derived+120>,
    c = 40
  }, 
  members of virtual_inherit::Derived:
  d = 50
}

(gdb) info vtbl derived
vtable for 'virtual_inherit::Derived' @ 0x10007dca0 (subobject @ 0x60000230c000):
[0]: 0x100007010 <virtual_inherit::Derived::~Derived()>
[1]: 0x100007050 <virtual_inherit::Derived::~Derived()>
[2]: 0x100007080 <virtual_inherit::Derived::foo()>
[3]: 0x1000070c0 <virtual_inherit::Derived::bar()>

vtable for 'virtual_inherit::BaseB' @ 0x10007dcd8 (subobject @ 0x60000230c010):
[0]: 0x100007100 <non-virtual thunk to virtual_inherit::Derived::~Derived()>
[1]: 0x100007120 <non-virtual thunk to virtual_inherit::Derived::~Derived()>
[2]: 0x100007140 <non-virtual thunk to virtual_inherit::Derived::foo()>

vtable for 'virtual_inherit::BaseC' @ 0x10007dd00 (subobject @ 0x60000230c020):
[0]: 0x100007160 <non-virtual thunk to virtual_inherit::Derived::~Derived()>
[1]: 0x100007180 <non-virtual thunk to virtual_inherit::Derived::~Derived()>
[2]: 0x1000071a0 <non-virtual thunk to virtual_inherit::Derived::foo()>
[3]: 0x1000071c0 <non-virtual thunk to virtual_inherit::Derived::bar()>

vtable for 'virtual_inherit::Base' @ 0x10007dd40 (subobject @ 0x60000230c038):
[0]: 0x1000071e0 <virtual thunk to virtual_inherit::Derived::~Derived()>
[1]: 0x100007200 <virtual thunk to virtual_inherit::Derived::~Derived()>
[2]: 0x100007220 <virtual thunk to virtual_inherit::Derived::foo()>
```

## 2、function overloading（函数重载）
- 在同一作用域中，可以定义多个函数，它们具有相同的名称但不同的参数列表。
- 参数列表的不同可以涉及到参数类型、参数个数、参数顺序。
- 编译器通过函数调用时传递的参数的类型和个数来区分重载函数。


## 3、function hiding（函数隐藏）
- 在类的派生关系中，如果派生类中的函数和基类中的函数具有相同的名称但不具有相同的参数列表，则称之为函数隐藏。
- 函数隐藏会阻止派生类中的同名函数访问基类中的同名函数。

