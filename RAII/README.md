# Resource Acquisition Is Initialization
RAII（Resource Acquisition Is Initialization）是 C++ 中的一种编程范式，它是一种资源管理的技术。
RAII 的核心思想是：通过在对象的生命周期中控制资源的获取和释放，来确保资源的正确管理。

RAII 在 C++ 中的常见应用包括但不限于：
- 智能指针：std::unique_ptr 和 std::shared_ptr 是 RAII 的实现，它们用于自动管理动态分配的内存。
- 文件句柄：将文件句柄封装在对象中，在对象的析构函数中关闭文件。
- 互斥锁：将互斥锁封装在对象中，确保在离开作用域时自动释放锁。
- 资源管理类：自定义的资源管理类，用于管理数据库连接、网络连接等。