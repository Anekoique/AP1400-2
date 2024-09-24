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