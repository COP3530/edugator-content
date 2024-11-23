# C++ Classes

**Author:** *Brian Magnuson*

In this lesson, we'll continue where we left off in our C++ review.
We'll be discussing classes, which are a fundamental part of object-oriented programming (OOP).

In this lesson, we will cover:
- Class basics
- Constructors
- Member functions
- Copy constructors and copy assignment operators
- Destructors
- Inheritance
- Abstract classes

# Class Basics

A class is usually defined in a header file, and its function implementations are defined in a separate source file. Some people prefer to define each class in its own header/source file pair. This can help keep your code organized and make it easier to find things.

Here's an example of a simple class definition:
```cpp
class MyClass {
    int z; // private by default
public:
    int x;
    int y;
};
```
Here, our class has two public member variables, `x` and `y`. These variables can be accessed and modified from outside the class.

To use our class, we can create an instance of it like this:
```cpp
MyClass obj;
obj.x = 5;
obj.y = 10;

std::cout << obj.x << " " << obj.y << std::endl; // Output: 5 10
```
The `.` operator is used to access the members of an object. Outside of the class definition, we can only access public members, i.e., members declared after the `public:` access specifier.

By default, members of a class are private, meaning they can only be accessed from within the class itself. To make members public, we use the `public:` access specifier. We can also use `private:` to declare private members after a public section.

There is another way to declare a custom composite type in C++: using a `struct`. The *only* difference between a `class` and a `struct` is that members of a `struct` are public by default, while members of a `class` are private by default.
```cpp
struct MyStruct {
    int x; // public by default
    int y; // also public by default
private:
    int z;
};
```

By specifying which members we want to make public or private, we can control how our class is used. This feature is known as **encapsulation**. Encapsulation allows us to hide certain features of our class from the outside world, preventing unwanted access and modification.


