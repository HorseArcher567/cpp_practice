# Run-Time Type Identification
RTTI（Run-Time Type Identification）是 C++ 中的一项特性，用于在运行时获取对象的类型信息。
RTTI 允许你在程序运行时检查对象的实际类型，并进行相应的处理。
C++ 提供了两个主要的 RTTI 运算符：dynamic_cast 和 typeid。

## dynamic_cast
- 用于执行安全的、动态类型转换。它在运行时检查类型信息，如果类型转换是安全的，就返回转换后的指针或引用；
否则，返回空指针（对指针进行转换）或抛出异常（对引用进行转换）。
- 适用于多态类层次结构，其中至少有一个虚函数。

## typeid
- 用于获取对象的类型信息。返回一个std::type_info对象，包含有关对象的类型的信息。
- 适用于任何类型的对象，不要求类层次结构中存在虚函数。