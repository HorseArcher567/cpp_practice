## Polymorphism（多态性）

### 1、normal_inherit（普通继承）
#### 1.1 对于钻石继承，存在二义性和资源浪费
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


### 2、virtual_inherit（虚继承）
#### 2.1 解决钻石继承的二义性和资源浪费