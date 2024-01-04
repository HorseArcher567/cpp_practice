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