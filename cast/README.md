# cast practice
## dynamic_cast
- 它只能用于包含虚函数的类层次结构，依赖RTTI(Run-Time Type Identification)。
- 在运行时进行安全的类型转换的操作符，它主要用于在继承体系中进行类型检查和类型转换。
这个操作符通常用于将基类指针或引用转换为派生类指针或引用。
- dynamic_cast返回指向目标类型的指针的空指针（如果是指针类型），
或者抛出 std::bad_cast异常（如果是引用类型）。

## static_cast
- 用于在编译时进行类型转换。它主要用于执行编译时已知的转换，如基本数据类型之间的转换、
明确的类型转换、以及类层次结构中的上行转换（派生类指针或引用转换为基类指针或引用）。
- 明确的类型转换指转换操作符或构造函数。

## reinterpret_cast
- 用于进行底层的、不安全的类型转换，它主要用于将一个指针类型转换为另一种指针类型，并不执行任何运行时检查。

## const_cast
- 用于去除指针或引用类型的const或volatile修饰符，它主要用于修改对象的常量性或易变性。 