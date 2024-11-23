# C++ Basics

**Author:** *Brian Magnuson*

In the next few lessons, I'll be covering almost everything you need to know about the C++ programming language. C++ is a statically-typed, compiled, general-purpose programming language. Its low-level memory manipulation capabilities and Standard Template Library (STL) make it an ideal language for learning data structures and algorithms.

These lessons are meant to be a *review* of C++. I'll assume you have some experience with an object-oriented programming language like Java or Python. If you're new to programming, I recommend looking for more beginner-friendly resources on C++.

If you are ***already familiar with C++***, I would still recommend reading through these lessons as they may contain some useful information for success in this course.

In this lesson, we will cover:
- The main function
- Preprocessor directives
- Data types
- Variables
- Control structures
- Functions
- Function declarations and header files
- Standard input/output
- Using keyword

In addition to the above, I will also touch on best C++ practices to help you write well-structured code.

Notably, I have chosen to omit arrays from this lesson. This and memory management will be covered in the next lesson.

Let's get started!

# The Main Function

If you're building an executable, you will need a main function. Execution begins and ends in the main function. The main function is defined in a file, typically named `main.cpp`. Note that some style guides may recommend using `.cc` or `.cxx` as the file extension for C++ source files.

**For this course, we use `.cpp` for source files and `.h` for header files.**

A main function looks like this:
```cpp
int main() {
    // Your code here
    return 0;
}
```

The main function returns an integer. A return value of `0` indicates that the program executed successfully. Any other value indicates an error. You can also use `std::exit` from the `<cstdlib>` header to exit from anywhere in the program.

A main function can also look like this:
```cpp
int main(int argc, char* argv[]) {
    // Your code here
    return 0;
}
```

You may write a main function like this if you want to accept command-line arguments. `argc` is the number of arguments passed to the program, and `argv` is an array of strings containing the arguments. When there are command-line arguments, the string that invoked the program is stored in `argv[0]`, and the arguments are stored in `argv[1]`, `argv[2]`, and so on.

# Preprocessor Directives

C++ programs are built in three stages: preprocessing, compiling, and linking. Preprocessing is the first stage. The preprocessor reads the source code and processes preprocessor directives, which start with a `#` symbol. This is all done *before* compilation.

The `#define` directive creates a macro. During preprocessing, all instances of the macro are replaced with the value or expression. Macros are used to define constants or to create simple functions.
```cpp
#define MACRO_NAME_1 value
#define MACRO_NAME_2(VALUE) VALUE + 1
```

Macros are often written in `UPPER_SNAKE_CASE` to distinguish them from variables.

You can also define a macro without a value. This is often used to create a *flag* for conditional compilation.
```cpp
#define FLAG
```

The `#include` directive is used to include files. During preprocessing, the contents of the file are copied and pasted where the directive is located.
```cpp
#include <iostream>
#include "my_header.h"
```

Using quotes tells the preprocessor to check files relative to the current file, then check the system directories. Using angle brackets tells the preprocessor to check the system directories only. Typically, you will use quotes for your own header files and angle brackets for system header files.

The `#ifdef`, `#ifndef`, `#else`, and `#endif` directives are used for conditional compilation. These directives are used to include or exclude code based on whether a macro is defined.
```cpp
#ifdef FLAG
    // Code here
#else
    // Code here
#endif
```

These are often useful when you want to compile code for a specific platform or when you want to include debugging code that you can easily turn off.

The `#ifndef` directive is particularly useful for creating an **include guard**. An include guard prevents files from being compiled more than once (which can cause "multiple definition" errors). All header files should have an include guard as they are often included in multiple files.
```cpp
// my_header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

// Header code here

#endif
```

You can choose any name for the macro, but it should be unique to the file. Google's style guide recommends the format `<PROJECT>_<PATH>_<FILE>_H_`. For smaller projects, simply naming the macro after the file is sufficient (as shown above).

These are most of the directives you will encounter in C++. There is, however, one more: the `#pragma` directive. This directive is used to give instructions to the compiler. However, the exact behavior of `#pragma` is compiler-dependent, so it is best to avoid using it.

One common use of `#pragma` is to act as a simpler include guard. 
```cpp
// my_header.h
#pragma once
// No need to use #ifndef MY_HEADER_H

// Header code here
```

GCC, Clang, and MSVC all support the `#pragma once` directive, which tells the compiler to only include the file once. We accept either method in this course (though I have a slight preference for `#ifndef`).

# Data Types

C++ has a variety of data types for integers. Confusingly, the size of these data types may vary depending on the platform.

- `char`: At least 8 bits, but all architectures use 8 bits.
  - Values of the `char` data type are printed as characters. 8 bits is enough to represent all ASCII characters.
  - Range: -128 to 127 for signed, 0 to 255 for unsigned.
  - May be signed or unsigned by default depending on the platform.
- `short` or `short int`: At least 16 bits, but all architectures use 16 bits.
  - Range: 16 bits is -32,768 to 32,767 for signed, 0 to 65,535 for unsigned.
- `int`: At least 16 bits, but most architectures use 32 bits.
  - Range: 32 bits is -2,147,483,648 to 2,147,483,647 for signed, 0 to 4,294,967,295 for unsigned.
- `long` or `long int`: At least 32 bits. Some architectures use 32 bits. Unix-like systems with a 64-bit architecture use 64 bits.
  - Range: 64 bits is -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 for signed, 0 to 18,446,744,073,709,551,615 for unsigned.
- `long long` or `long long int`: At least 64 bits, but all architectures use 64 bits.

All integer types (except `char`) are signed by default. To make them unsigned, add the `unsigned` keyword. For example, `unsigned int`.

If you want to guarantee a specific size, the `<cstdint>` header provides fixed-width integer types. However, for this course, using `char`, `int`, and `long long` is usually sufficient.

For floating-point numbers, C++ has two data types:
- `float`: Single precision, IEEE-754 standard.
  - 32 bits.
- `double`: Double precision, IEEE-754 standard.
  - 64 bits.

Numeric literals with a decimal point are treated as `double` by default. To specify a `float`, add an `f` or `F` at the end of the number. E.g., `3.14f`.

Notably, both IEEE-754 floating point types also support positive infinity, negative infinity, `NaN` (not a number), and negative zero. These can be useful for some calculations. Just be aware that any comparison with `NaN` will always return `false`, including with itself.

Be careful when comparing floating-point numbers. Due to the way they are stored in memory, floating-point numbers may not be exactly equal. Instead, compare the difference between the two numbers to a small value (often called epsilon). E.g., `fabs(a - b) < 1e-9`.

Next, there is the `bool` data type. It is almost always 1 byte in size. The values are `true` and `false`. `true` is equivalent to 1, and `false` is equivalent to 0. Note that whenever a boolean value is needed (such as in an `if` statement), any value equivalent to 0 is considered `false`, and any other value is considered `true`. `NaN` is considered `true`.

Finally, there are pointer types (types with a `*`). We'll cover pointers in the next lesson, but for now, know that pointers are used to store memory addresses. The size of a pointer depends on the architecture. For 32-bit systems, pointers are 4 bytes. For 64-bit systems, pointers are 8 bytes.

To read more about data types in C++, see [this page](https://en.cppreference.com/w/cpp/language/types).

# Variables

Variables can be given any valid identifier. An identifier is a sequence of letters, digits, and underscores that does not start with a digit. Many programmers use `snake_case` or `lowerCamelCase` for variable and function names, though I have a preference for `snake_case`. You can use any style you like, but ***be consistent***.

A local variable in C++ can be declared like this:
```cpp
int variable_name;
int variable_name = 1;
auto variable_name = 1;
```

`auto` is not a data type nor a keyword for a dynamic type (C++ is statically typed). Rather, it tells the compiler to infer the data type from the value assigned to the variable. This is useful when the data type is long (like `std::unordered_map<std::string, std::vector<int>>::iterator`).

In rare cases, you may want to use `decltype` to use the type of another variable.
```cpp
decltype(variable_name) another_variable_name = 2;
```

You can use the `const` keyword to make a variable constant. This means the variable cannot be changed after it is initialized.
```cpp
const int constant_name = 1;
```

You can use `constexpr` to make a variable constant at compile time. Some features of C++ such as array sizes require compile-time constants.
```cpp
constexpr int compile_time_constant = 1;
```

We recommend against *creating global variables*. Global variables can be accessed from any function, which can make it difficult to track down bugs. If you need to share data between functions, consider using function arguments or returning values.

To create a reference to a variable, use the `&` symbol.
```cpp
int variable_name = 1;
int& reference_name = variable_name;
reference_name = 2; // also changes variable_name
```

References must always be initialized when declared, and the referenced variable cannot be changed. References are often used with range-based `for` loops and function arguments to avoid expensive copies. For other uses, it is best to use references with local variables.

It is possible to use references in structs and classes, but without guaranteeing the lifetime of the referenced variable, it can potentially lead to undefined behavior, so it is best to avoid this.

References can be thought of as a special kind of pointer. We will cover pointers and memory management in the next lesson.

# Control Structures

These, you probably already know. But let's review them anyway.

The `if` statement is used to execute code based on a condition.
```cpp
if (condition) {
    // Code here
}

if (condition) {
    // Code here
} else if (other_condition) {
    // Code here
} else {
    // Code here
}
```

The `switch` statement is used to execute code based on the value of an expression.
```cpp
switch (expression) {
    case value_1:
        // Code here
        break;
    case value_2:
        // Code here
        break;
    default:
        // Code here
}
```
Unlike other languages, the expression in a `switch` statement must be an integer or an enumeration. Floating-point numbers, strings, and other types are not allowed.

The `while` statement is used to execute code while a condition is true.
```cpp
while (condition) {
    // Code here
}
```

The `do-while` statement is used to execute code at least once and then while a condition is true.
```cpp
do {
    // Code here
} while (condition);
```

The `for` statement allows you to initialize a variable, check a condition, and update the variable in one line. It is often used to iterate a specific number of times.
```cpp
for (int i = 0; i < 10; ++i) {
    // Code here
}
```

I won't be covering most operators in this lesson, but I would like to bring special attention to the `++` and `--` also known as the increment and decrement operators. These operators can be used as a prefix or postfix. The difference is that the prefix operator increments or decrements the variable before the value is used, while the postfix operator increments or decrements the variable after the value is used. For example, `++i` increments `i` and then uses the new value, while `i++` uses the current value of `i` and then increments it.

The range-based `for` statement is used to iterate over a range of elements. It is often used with arrays, vectors, and other containers.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
for (int i : vec) {
    // Code here
}
for (int& i : vec) {
    // Code here
}
```

You can also use `auto` and `auto&` instead of writing the data type explicitly.

For all kinds of loops, you can use `break` to exit the loop early and `continue` to skip the rest of the loop and go to the next iteration.

# Functions

Here are examples of functions in C++:
```cpp
int add(int a, int b) {
    return a + b;
}

void print_result(int result) {
    std::cout << result << std::endl;
}
```

The return type is written first, then the function name, then the parameters in parentheses. If the function does not return a value, use `void`. For non-void functions, all code paths should always return a value.

You can use `...` as the last parameter in a function to create a variadic function. These can be useful at times, but I would recommend against using them for this course. You can read more about variadic functions [here](https://en.cppreference.com/w/cpp/language/variadic_arguments).

In C++, you can declare multiple functions with the same name but different parameters. This is called **function overloading**. The compiler will choose the correct function based on the parameters passed to it.
```cpp
int add(int a, int b) {
    return a + b;
}
double add(double a, double b) {
    return a + b;
}
```

# Function Declarations and Header Files

This next part is ***important***, especially for C++ beginners, so pay attention!

You ***cannot use a function before it is declared***. This is because C++ reads files from top to bottom. If you try to use a function before it is declared, the compiler will throw an error.
```cpp
// In ping_pong.cpp
void ping(int n) {
    if (n == 0) return;
    pong(n - 1); // Error: pong is not declared
}

void pong(int n) {
    if (n == 0) return;
    ping(n - 1);
}
```

To fix this, you can declare the function before it is used. This function declaration is called a **prototype**.
```cpp
// In ping_pong.cpp
void pong(int n);

void ping(int n) {
    if (n == 0) return;
    pong(n - 1);
}

void pong(int n) {
    if (n == 0) return;
    ping(n - 1);
}
```

If we want to use the `ping` and `pong` functions in another file, we can create a header file. Header files typically have the `.h` extension.
```cpp
// In ping_pong.h
#ifndef PING_PONG_H
#define PING_PONG_H

void pong(int n);

void ping(int n) {...}
void pong(int n) {...}
// Not recommended, but allowed

#endif
```

Although we could include the function definitions in the header file, this can potentially slow down compilation, especially for large projects. For best practices, we should only include the function declarations in the header file and put the function definitions in a source file (typically with a `.cpp` extension).
```cpp
// In ping_pong.h
#ifndef PING_PONG_H
#define PING_PONG_H

void ping(int n);
void pong(int n);

#endif
```
```cpp
// In ping_pong.cpp
#include "ping_pong.h"

void ping(int n) {...}
void pong(int n) {...}
```

This is the ***recommended way*** to structure your C++ code. An exception to this rule is when you are using templates, which we will cover in a later lesson.

We can then include the header file in the source file where we write the function definitions.
```cpp
// In ping_pong.cpp
#include "ping_pong.h"

void ping(int n) {
    if (n == 0) return;
    pong(n - 1);
}

void pong(int n) {
    if (n == 0) return;
    ping(n - 1);
}
```

Then, if we want to use the `ping` and `pong` functions in another file, we can include the header file.
```cpp
// In main.cpp
#include "ping_pong.h"

int main() {
    ping(10);
    return 0;
}
```

The main function will be able to use the `ping` and `pong` functions as long as `main.cpp` and `ping_pong.cpp` are compiled and linked together.

For many C++ project, you'll find that files often come in pairs: a `.cpp` file with the function definitions and a `.h` file with the function declarations. This is a common practice in C++ and is recommended for this course.

Remember that the C++ preprocessor will check file *relative* to the current file. So if `ping_pong.h` were located in a different directory, say `my_lib`, you would write `#include "my_lib/ping_pong.h"`. You do not need to do this for system header files because the preprocessor checks a specific set of directories where these files are located. You can technically add your own directories to this list using the `-I` flag during compilation, but this is recommended only if you know what you are doing.

You should ***never*** use `#include` to include a `.cpp` file. This can lead to multiple definitions of functions and variables, which will cause errors. Instead, use header files to declare functions and variables.

# Standard Input/Output

C++ uses `std::cin` for input and `std::cout` for output. To use these, you need to include the `<iostream>` header.
```cpp
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    std::cout << n << std::endl;
    return 0;
}
```

C++ will automatically convert the input to the correct data type. If the input is not a valid number, `std::cin` will set the fail bit, and you can check this with `std::cin.fail()`. You can also use `std::cin.clear()` to clear the fail bit and `std::cin.ignore()` to ignore the invalid input.

If the input is invalid, `n` will not be assigned. In the example above, it will remain uninitialized, which can lead to undefined behavior. 

Most programming problems in this course use a strict input format (which we specify), so you usually will not need to validate the input.

`std::endl` is used to insert a newline character and flush the output buffer. You can also use `'\n'` to insert a newline character without flushing the buffer. It is worth noting that in most command-line environments, the output buffer is automatically flushed when a newline character is printed, so `std::endl` is not necessary. You may use either.

If you want to get an entire line as input, you can use `std::getline`.
```cpp
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::cout << s << std::endl;
    return 0;
}
```

You can also specify the delimiter for `std::getline` if you want to read until a specific character.

# Using Keyword

The last thing I want to cover in this lesson are `using` declarations. The `using` keyword can be used for creating aliases. However, I'd like to focus on what a lot of beginners use with `using`: `using namespace std`.

You might've noticed that the last few examples have `std::` in front of several functions, types, and objects. This is because these are part of the `std` namespace. The `std` (standard) namespace is a collection of functions, types, and objects provided by the C++ Standard Library.

Beginners will often use `using namespace std;` at the top of their code. This allows the use of standard functions and types without the `std::` prefix.
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

Many style guides recommend against this as it can lead to naming conflicts. 

Perhaps a slightly safer alternative is to use `using` declarations.
```cpp
#include <iostream>
using std::cout;
using std::endl;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

Here are ***my recommendations for this course***:

You may use `using namespace std;` for any programming quiz, pseudocode problem, interview question, or project in this course. It is generally acceptable to use it in small projects.

Even I used it plenty of times before, but I've since outgrown it and have adapted to putting `std::` in front of everything. Future lessons may include it, others may not. 

# Practice

Here are some practice problems to help you get comfortable with the concepts covered in this lesson.

What is the output of the following code?
```cpp
#include <iostream>
int main() {
    int a = 1;
    int b = 2;
    int c = a / b;
    std::cout << c << std::endl;
    return 0;
}
```
- 0 (correct)
- 0.5
- 1
- (produces a compile error)
- (result is undefined)

---

What is the output of the following code?
```cpp
#include <iostream>
int main() {
    int a = 1;
    int& b = a;
    b = 2;
    std::cout << a << b << std::endl;
    return 0;
}
```
- 11
- 12
- 22 (correct)
- 21
- (produces a compile error)

---

What is the output of the following code?
```cpp
#include <iostream>
int main() {
    int n = 8;
    while (n) {
        n /= 2;
        std::cout << n;
    }
    return 0;
}
```
- 421
- 4210 (correct)
- 8421
- (produces a compile error)
- (program does not terminate)

---

What is the output of the following code?
```cpp
#include <iostream>
int main() {
    int n = 0;
    std::cout << n++ << n++ << ++n << std::endl;
    return 0;
}
```
- 011
- 012
- 013 (correct)
- 123
- 124

---

What is the output of the following code?
```cpp
#include <iostream>
int main() {
    int n = 5;
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 0) continue;
        std::cout << i;
    }
    return 0;
}
```
- 12345
- 135
- 13 (correct)
- 1
- (nothing is printed)

---

What is the output of the following code?
```cpp
#include <iostream>
void foo(int n, int& m) {
    int temp = n;
    n = m;
    m = temp;
}
int main() {
    int a = 1;
    int b = 2;
    foo(a, b);
    std::cout << a << b << std::endl;
    return 0;
}
```
- 11 (correct)
- 12
- 21
- 22
- (produces a compile error)

# Conclusion

That's it for this lesson! We've covered a lot of ground, but this is just the beginning! In the next lesson, we'll cover arrays and memory management.
