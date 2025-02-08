

# Notes

## hw 01

 第一个任务为基本的矩阵运算实现，基本了解 googletest，能够构建项目并运行测试即可。

Related：

- <random>

---

## hw 02

第二个任务为货币交易，实现一个服务端类和一个用户端类

Related：

- const 使用
- 前向声明
- 智能指针<memory>
- STL
  - string

  - map
- <regex>

---

## hw 03

第三个任务为实现一个二叉搜索树（BST），可以帮助学习巩固数据结构相关知识和指针的运用，内容丰富，不乏C++11的新特性 (PS:参考大佬的代码，添了加很多递归实现)

Related:

- 运算符重载
- 初始化列表 initializer_list
- 右值引用
- function使用
- lambda使用

- STL

  - queue

---

## hw 04

第四个任务为实现智能指针shared_ptr和unique_ptr，实现的shared_ptr有问题，直接使用了static int count来计数实现控制块，这会导致实例化不同指针时增加的是同一个控制块。可以使用map一个指针对应一个数字，也可以使用一个size_t指针作为引用计数器，对使用相同T指针的使用size_t指针指向同一个地址

Related:

- template 模板类

- static
- 列表初始化 优于 手动赋值
- noexpect

# Effective C++

## Chapter 1 Accustoming in c++

### 1、federation of language

- C
- Object-oriented C++
- template C++
- STL

### 2、prefer const/enum

- for simple constants, prefer object objects or enums to #defines
- for function-like macros, prefer inline functions to #defines

### 3、Use const more

- help compile to detect usage errors
- compilers enforce bitwise constness, but program using logical constness
- code duplication can be avoided by having the non-const version call the const version

### 4、initialized object

- manually initialize objects of built-in type
- prefer use the member initialization list to assignment inside the body of the construct
- replacing non-const static objects with local static objects

## Chapter 2 Construct

### 5、function silently write

- compile implicit generate class's default constructor,copy constructor,copy assignment operator and destructor

### 6、disable compile-generated

- declare the corresponding member functions private and give no implementations.Use a base class like Uncopyable.

### 7、declare virtual in polymorphic base classes

- base class should declare virtual destructors. If a class has any virtual functions, it should have a virtual destructor.
- classes not designed to be base classes or not designed to be used polymorphically should not declare virtual destructors.

### 8、Prevent exception from destructors

- Destructor should never emit exceptions
- provide a regular funtion to perform the operation that react to exception throw during operation.

### 9、never call virtual during construct

- such call will never go to a more derived class than that of the currently executing constructor or destructor.

### 10、assignment operators return *this

### 11、handle assignment to self in =

### 12、copy all parts of objects

### 13、