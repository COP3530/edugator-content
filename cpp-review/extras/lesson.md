# C++ Extras

**Author:** *Brian Magnuson*

In this lesson, we will cover more features of C++ and its standard library. These are topics that did not fit into the previous lessons, but are still important to know.

In this lesson, we will cover the following topics:
- Strings
- Regular expressions
- Templates
- Exceptions
- Function pointers, function objects, and lambdas
- File I/O

You can read these sections in order, or you can skip to the sections that interest you.

# Strings

C++ has two main types of strings: C-style strings and `std::string` (part of the C++ standard library). We will first discuss C-style strings.

Whenever you write a string literal, you are actually creating a C-style string. For example:
```cpp
auto str = "Hello, world!";
```

A C-style string is an array of characters. In the example above, the type of the string literal is `const char[14]`. 
The string has 13 characters, plus an implicit null terminator at the end.

Unlike most literal values, which are usually only stored as temporary values on the stack, C-style strings are stored in static memory.
This has a few implications:
- C-style strings are immutable. You cannot change the contents of a C-style string after it is created.
- They live for the entire duration of the program. You do not need to worry about deallocating them or using them after they go out of scope.

When storing a string literal in a variable, a `char*` pointer is usually used. For example:
```cpp
const char* str = "Hello, world!";
```

Here, `str` does not point to heap memory or stack memory. It points to static memory, which is allocated at compile time.
This means that you can do things with C-style strings that you cannot do with other types of variables. For example:

```cpp
const int* int_return() {
    const int nums[5] = {1, 2, 3, 4, 5};
    return nums; // Undefined behavior: returning address of local variable
}

const char* string_return() {
    const char* str = "Hello, World!";
    return str; // Perfectly fine: returning address of static string
}
```

These functions have a similar structure, but the first one has undefined behavior because it returns the address of a local variable. 
The memory for the variable is deallocated when the function returns, so the pointer is invalid. 
The second function is perfectly fine because it returns the address of a string literal, which is stored in static memory and lives for the entire duration of the program.

You might notice that since we store strings as a `char*`, we do not store the length of the string. This is because C-style strings are null-terminated.
This means that the end of the string is marked by a null character (`'\0'`).

Whenever printing a C-style string, each character is printed until the null terminator is reached. For example:
```cpp
const char* str = "Hello, world!";
std::cout << str << std::endl; // Prints "Hello, world!"
```

To obtain the length of a C-style string, you can use the `strlen` function from the C standard library:
```cpp
#include <cstring>
#include <iostream>

int main() {
    const char* str = "Hello, world!";
    std::cout << strlen(str) << std::endl; // Prints 13
    return 0;
}
```

The decision to use null-terminated strings was made during a time when memory was very limited; it was considered more attractive to save a few bytes of memory than to store and maintain the length of the string. However, this design choice has some drawbacks:
- Strings are not allowed to contain null characters since they would be interpreted as the end of the string.
- Inserting a null character into a string will cause the string to be truncated.
- The string must be traversed to find its length, which can be inefficient.
- Forgetting to add the null terminator can lead to undefined behavior.
- Copying the string to a buffer without checking the length can result in the buffer overflowing if the string is longer than the buffer.
  - Buffer overflow errors are a common source of security vulnerabilities, sometimes allowing attackers to execute arbitrary code.

You can read more about null-terminated strings [here](https://en.wikipedia.org/wiki/Null-terminated_string).

C++ beginners are often encouraged to use C++'s `std::string` from the `<string>` header instead of C-style strings.
`std::string` is a class that represents a string and provides many useful functions for manipulating strings.

We can construct a `std::string` from a C-style string:
```cpp
#include <string>
#include <iostream>

int main() {
    std::string str = "Hello, world!";
    std::cout << str << std::endl; // Prints "Hello, world!"
    return 0;
}
```

`std::string` is mutable, so you can change its contents after it is created:
```cpp
std::string str = "Hello, world!";
str[0] = 'h';
std::cout << str << std::endl; // Prints "hello, world!"
```

`std::string` internally stores the length of the string, so you can obtain the length of the string using the `length` or `size` member functions:
```cpp
std::string str = "Hello, world!";
std::cout << str.length() << std::endl; // Prints 13
std::cout << str.size() << std::endl; // Also prints 13

for (int i = 0; i < str.length(); i++) {
    std::cout << str[i] << std::endl; // Prints each character of the string
}
```

You can also perform other operations on `std::string`, such as concatenation, substring extraction, and searching:
```cpp
std::string str1 = "Hello, ";
std::string str2 = "world!";
std::string str3 = str1 + str2; // Concatenation
std::cout << str3 << std::endl; // Prints "Hello, world!"

std::string str4 = str3.substr(7, 5); // From index 7, take 5 characters
std::cout << str4 << std::endl; // Prints "world"

std::size_t pos = str3.find("world"); // Find the position of "world"
std::cout << pos << std::endl; // Prints 7
```

`std::string` is actually a typedef for `std::basic_string<char>`. You can read more about `std::basic_string` and the various string functions [here](https://en.cppreference.com/w/cpp/string/basic_string).

# Regular Expressions

A **regular expression (regex)** is a sequence of characters that defines a search pattern. These patterns can be used to find matches in strings, which can be useful for tasks such as input validation, searching, and find-and-replace operations.

A regular expression is often written as a string. Consider the following example:
```
Regex: "re"
String: "regular expressions are really cool"
Matches: ^^         ^^        ^^ ^^
```

Here, the regex "re" has four matches in the string "regular expressions are really cool".

C++ provides support for regular expressions through the `<regex>` header. Here is an example of how to use regular expressions in C++:
```cpp
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string str = "regular expressions are really cool";
    std::regex regex("re");
    std::smatch match;

    if (std::regex_search(str, match, regex)) {
        std::cout << "Match found: " << match.str() << std::endl;
    } else {
        std::cout << "No match found\n";
    }

    return 0;
}
```

In this example, we create a regex object with the pattern "re" and use the `std::regex_search` function to search for matches in the string. If a match is found, `regex_search` returns `true` and the match is stored in the `match` object.

`match` is of type `std::smatch`, which is a special type of `std::match_results` that is used for matching with `std::string`. It contains information about the match, such as the position of the match in the string and the matched substring.

Regular expressions also use special characters to define things like character classes, quantifiers, and anchors. The exact special characters used depend on the regex grammar. By default, C++ uses the ECMAScript grammar, which is the same grammar used by JavaScript.

The "language" of regular expressions is both powerful and vast. It may take some time for you to learn all of the special characters and their meanings.
Here are a few examples of regex patterns and their meanings:

```
Regex: "^ab"
Matches "ab" at the beginning of the string
String: "abababab"
Matches: ^^

Regex: "ab$"
Matches "ab" at the end of the string
String: "abababab"
Matches:       ^^

Regex: "^ab$"
Matches "ab" at the beginning and end of the string (i.e. the entire string)
String: "ab"
Matches: ^^

Regex: "a.b"
The '.' character matches any character
String: "a*b"
Matches: ^^^

Regex: "[bc]d"
Matches either "b" or "c" followed by "d"
String: "abd"
Matches:  ^^

Regex: "[a-z]"
Matches any lowercase letter
String: "Great"
Matches:  ^^^^

Regex: "[0-9]" or equivalently "\d"
Matches any digit
String: "12a3"
Matches: ^^ ^

Regex: "a\d+b"
Matches "a" followed by one or more digits followed by "b"
String: "a123b"
Matches: ^^^^^

Regex: "a\d*b"
Matches "a" followed by zero or more digits followed by "b"
String: "ab"
Matches: ^^

Regex: "ba{2}b"
Matches "b" followed by "a" repeated exactly 2 times followed by "b"
String: "bab baab baaab"
Matches:     ^^^^

Regex: "\d{3}-\d{3}-\d{4}"
Matches any 3 digits, followed by a hyphen, followed by 3 digits, followed by a hyphen, followed by 4 digits
String: "123-456-7890"
Matches: ^^^^^^^^^^^^
```

This is just a small sample of the many regex patterns you can use. If you want to learn more about regex, consider looking up an online tutorial or reference.

Sometimes, the best way to practice regex is to use an online regex tester. [Regex101](https://regex101.com/) is a great tool for testing regex patterns. It provides a detailed explanation of the regex pattern and highlights the matches in the string.

There is one more feature of regex that may be useful to you:
```
Regex: "(\d{3})-(\d{3})-(\d{4})"
Matches any 3 digits, capturing it in group 1,
followed by a hyphen,
followed by 3 digits, capturing it in group 2,
followed by a hyphen,
followed by 4 digits, capturing it in group 3

String: "123-456-7890"
Matches: ^^^^^^^^^^^^
Group 1: 123
Group 2: 456
Group 3: 7890
```

When you surround part of a regex pattern with parentheses, it creates a capturing group. This allows you to extract parts of the match. You can access the captured groups using the `std::smatch` object:
```cpp
#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string str = "123-456-7890";
    // Use double backslashes to escape the backslashes in the regex pattern
    std::regex regex("(\\d{3})-(\\d{3})-(\\d{4})");
    std::smatch match;

    if (std::regex_match(str, match, regex)) {
        std::cout << "Match found: " << match.str() << std::endl;
        // match[0] is the entire match
        std::cout << "Group 1: " << match[1] << std::endl;
        std::cout << "Group 2: " << match[2] << std::endl;
        std::cout << "Group 3: " << match[3] << std::endl;
    } else {
        std::cout << "No match found\n";
    }

    return 0;
}
```

We can use capturing groups to extract parts of a string. This can make it useful for tasks such as parsing a command or data format.

In the above example, we use `std::regex_match`.
- `std::regex_search` is used to check if *any part* of the string matches the regex pattern.
- `std::regex_match` is used to check if the *entire string* matches the regex pattern.

# Templates

Templates are a powerful feature of C++ that allow you to write generic code. 
This means that you can write a function or class that works with any type, rather than being limited to a specific type.

You've likely already seen template classes in the C++ standard library, such as `std::vector` and `std::map`.
These classes are defined using templates, which allow them to work with any type.
```cpp
std::vector<int> vec; // A vector of integers
std::vector<std::string> str_vec; // A vector of strings
std::vector<MyClass> my_class_vec; // A vector of MyClass objects
```

To define a template function, you use the `template` keyword followed by the template parameter(s) in angle brackets.
Template parameters begin with either `typename` or `class`, but they are interchangeable.
The name of the parameter is usually a single uppercase letter, often `T`, but any valid identifier can be used.
```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

This next part is *important* so pay attention!:
Templates are called templates because they do not directly translate to machine code. Rather, the compiler generates code for each type that is used with the template.

For example, if you end up using the following function calls:
- `swap<int>(a, b);`
- `swap<double>(x, y);`

The compiler will generate code for two separate instances of the `swap` function: one for `int` and one for `double`.

For the compiler to accomplish this, it *must* see the definition of the template function before it is used. If it does not, you may get a linker error. To avoid this, you should *always* place the definition of the template function in the same file where it is declared.

To invoke the swap function, you can pass in any type:
```cpp
int a = 5;
int b = 10;
swap<int>(a, b); // Swaps two integers
swap(a, b); // More concise: the compiler deduces the type
```

Sometimes, it is not necessary to specify the type explicitly. The compiler can deduce the type from the arguments passed to the function.

On occasion, you may want a function to behave differently for a specific type. You can use **template specialization** to achieve this.

```cpp
template <>
void swap<int>(int& a, int& b) {
    a ^= b; // Fancy XOR trick for swapping integers
    b ^= a;
    a ^= b;
}
```

Here, we use template specialization to define a specific implementation of the `swap` function for `int` types. When the `swap` function is called with `int` arguments, this specialized version will be used instead of the generic version.

To define a template class, you use the same `template` keyword followed by the template parameter(s) in angle brackets:
```cpp
template <typename T>
class MyClass {
public:
    MyClass(T value) : value(value) {}
    T getValue() const { return value; }
private:
    T value;
};
```

If you want to define the functions outside of the class definition, you can do so like this:
```cpp
template <typename T>
MyClass<T>::MyClass(T value) : value(value) {}

template <typename T>
T MyClass<T>::getValue() const {
    return value;
}
```

Again, template functions and classes must be defined in the same file where they are declared to avoid linker errors.

# Exceptions

One common way to handle errors in C++ is through exceptions. **Exceptions** are a way to signal that an error has occurred and to transfer control to a special error-handling code.

An **exception object** is created using the `throw` keyword.
```cpp
void throws_exception() {
    throw "I'm an exception!";
}
```

You can technically throw any object as long as the object's type can be instantiated and copied. However, it is generally recommended to throw objects of type `std::exception` or derived types.
```cpp
#include <exception>
#include <stdexcept>

void throws_exception() {
    throw std::exception("I'm an exception!"); // From <exception>
}

void throws_runtime_error() {
    throw std::runtime_error("Runtime error occurred!"); // From <stdexcept>
}
```

When an exception object is thrown, the function will end without returning a value. The stack will unwind until the exception is caught by a `try` block. Details of the exception can be accessed using the `catch` block.
```cpp
#include <iostream>
#include <stdexcept>

void my_function(int a) {
    if (a < 0) {
        throw std::invalid_argument("Negative value not allowed");
    }
    std::cout << "Value is: " << a << std::endl;
}

int main() {
    int a;
    std::cout << "Enter a number: ";
    std::cin >> a;
    try {
        my_function(a);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument! " << e.what() << std::endl;
    }

    return 0;
}
```

In this example, if the user enters a negative number, the `my_function` will throw an `std::invalid_argument` exception. The `catch` block will then handle the exception and print an error message.

If the exception is not caught, then the stack will continue to unwind until it reaches another `catch` block. If that doesn't happen, the program will terminate and (usually) print an error message. Many IDEs with debuggers will stop execution at the point where the exception was thrown, making it easier to debug.

You can also have multiple `catch` blocks to handle different types of exceptions:
```cpp
try {
    my_function(a);
}
catch (const std::invalid_argument& e) {
    std::cout << "Invalid argument! " << e.what() << std::endl;
}
catch (const std::runtime_error& e) {
    std::cout << "Runtime error! " << e.what() << std::endl;
}
catch (std::exception& e) {
    std::cout << "Exception occurred! " << e.what() << std::endl;
}
catch (...) {
    std::cout << "Unknown error occurred!" << std::endl;
}
```

The last `catch` block with the ellipsis (`...`) is a catch-all for any exception that does not match the previous `catch` blocks. This can be useful for handling unexpected exceptions.

Other programming languages that use exceptions also have a "finally" block, which executes regardless of whether an exception is thrown; as of this writing, C++ does not have this feature.

If you know a function will never throw an exception, you can use the `noexcept` specifier to indicate this:
```cpp
void my_function() noexcept {
    // This function is guaranteed not to throw exceptions
}
```

This can be useful for both performance optimization and for documenting the function's behavior.

If you know a function will never return normally (i.e. it will always throw an exception), you can use the `[[noreturn]]` attribute:
```cpp
[[noreturn]] int my_function() {
    throw std::runtime_error("This function will not return");
}
```

Other reasons a function might never return include calls to `std::exit`, `std::abort`, `std::terminate`, or infinite loops. Specifying `[[noreturn]]` can prevent potential warnings from the compiler about missing return statements.

## Alternatives to Exceptions

While exceptions are a common way to handle errors in many modern programming languages, they do have a few drawbacks:
- When a function throws an exception, all of its callers must be examined to ensure the exception is eventually caught and handled properly.
- Exceptions make it difficult to reason about the control flow of a program; a function may end abruptly when you don't expect it to.
- Exceptions can introduce performance overhead, especially if they are used frequently.

Some modern programming languages, such as Go and Rust, do not use exceptions at all. Instead, they use other mechanisms to handle errors, such as returning error codes or using special types to represent success or failure. This pattern *forces* the programmer to handle errors explicitly, which can lead to more robust code.

For C++, there are a few alternatives to exceptions that you can consider:
- `std::pair` or `std::tuple` can allow you to return multiple values from a function, including an error code or status, which you would check before accessing the main return value.
- C++17 provides `std::optional`, which allows you to return `std::nullopt` to indicate that a value is not present, which can be used to represent failure.
- C++17 also provides `std::variant`, which allows you to return one of several types, including an error type.
- C++23 introduces `std::expected`, which is a type that can represent either a successful value or an error value, similar to the `Result` type in Rust.

# Function Pointers, Function Objects, and Lambdas

In C++, there are a few ways to store functions in variables or pass functions to other functions as arguments.

## Function Pointers

A **function pointer** is a variable that stores the address of a function. In C++, you can use a function's identifier as a pointer to that function.
```cpp
#include <iostream>
int my_function(double x, bool flag) {
    if (flag) {
        return static_cast<int>(x);
    }
    return 0;
}

int main() {
    // Declare a function pointer
    int (*func_ptr)(double, bool) = my_function;

    // Call the function using the pointer
    int result = func_ptr(3.14, true);
    std::cout << "Result: " << result << std::endl; // Prints "Result: 3"
    
    return 0;
}
```

Functions are stored in text memory (or code memory). Text memory, like static memory, lives for the entire duration of the program. It is also immutable, so you cannot change the contents of a function.

The syntax for declaring a function pointer is a bit tricky:
```cpp
int (*func_ptr)(double, bool) = &my_function;
int (*func_ptr)(double, bool) = my_function; // Equivalent
```
This declares a pointer `func_ptr` that points to a function taking a `double` and a `bool` as arguments and returning an `int`.

Here are a few more examples of function pointers declarations:
```cpp
void (*func_ptr1)(int); // Pointer to a function taking an int and returning void
double (*func_ptr2)(); // Pointer to a function taking no arguments and returning a double
int (*func_ptr3)(const char*, int); // Pointer to a function taking a const char* and an int, returning an int
int (*func_ptr4[10])(double); // Array of 10 function pointers, each taking a double and returning an int
```

A slightly easier way to write function pointer types is to use `using`:
```cpp
using FuncPtr = int (*)(double, bool);
FuncPtr func_ptr = my_function;

using Func = int (double, bool);
Func* func_ptr = my_function;
```

Function pointers do not need to be dereferenced to call them, though you are free to do so:
```cpp
int result1 = func_ptr(3.14, true); // Valid
int result2 = (*func_ptr)(3.14, true); // Also valid
int result3 = (*****func_ptr)(3.14, true); // Yes, this is valid too!
```

## Function Objects

A **function object** or **functor** is an object that can be called as if it were a function. This is possible by creating a class with an overloaded `operator()`.
```cpp
#include <iostream>
class MyFunction {
public:
    int operator()(double x, bool flag) {
        if (flag) {
            return static_cast<int>(x);
        }
        return 0;
    }
};
int main() {
    MyFunction my_func;
    int result = my_func(3.14, true);
    std::cout << "Result: " << result << std::endl; // Prints "Result: 3"
    
    return 0;
}
```

Function objects have a bit more flexibility than function pointers. For one, their class can be passed where a template argument is expected.
```cpp
#include <iostream>
#include <vector>

template <typename T, typename Func>
T reduce(std::vector<T>& vec, Func func, T init) {
    T result = init;
    for (const auto& item : vec) {
        result = func(result, item);
    }
    return result;
}

class Add {
public:
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Add add; // Create an instance of Add
    int result = reduce<int, Add>(vec, add, 0); // Pass the Add instance to reduce
    std::cout << "Result: " << result << std::endl; // Prints "Result: 15"
    return 0;
}
```

In the above example, we create a `reduce` function that takes a vector and a function object to reduce the vector's elements to a single value. The `Add` class is a function object that adds two integers together.

Some C++ functions and classes actually depend on function objects. For example, the `std::sort` function in the C++ standard library can take a function object as a comparison function:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class Compare {
public:
    bool operator()(int a, int b) {
        return a > b; // Sort in descending order
    }
};

int main() {
    std::vector<int> vec = {5, 2, 8, 1, 4};
    std::sort(vec.begin(), vec.end(), Compare());
    
    for (const auto& item : vec) {
        std::cout << item << " "; // Prints "8 5 4 2 1"
    }
    std::cout << std::endl;
    
    return 0;
}
```
In this example, we create a `Compare` class that is a function object for comparing two integers. We then use it to sort a vector in descending order.

The `<functional>` header provides a special type, `std::function`, which can store any callable object.
```cpp
std::function<int(double, bool)> func = my_function;
```


## Lambdas

A C++ **lambda expression** is a way to define an anonymous function object. Think of it as a way to create a function object "on the fly" without needing to define a separate class.
```cpp
#include <iostream>
int main() {
    auto my_lambda = [](double x, bool flag) {
        if (flag) {
            return static_cast<int>(x);
        }
        return 0;
    };
    
    int result = my_lambda(3.14, true);
    std::cout << "Result: " << result << std::endl; // Prints "Result: 3"
    
    return 0;
}
```

C++ lambdas are sometimes called closures. A **closure** is a function that captures variables from its surrounding scope.
```cpp
int x = 5;
auto my_closure1 = [x](double val) { // Capture x by value
    return x + static_cast<int>(val);
};
auto my_closure2 = [&x](double val) { // Capture x by reference
    return x + static_cast<int>(val);
};
```
In the first lambda, `x` is captured by value, meaning that the lambda has its own copy of `x`. In the second lambda, `x` is captured by reference, meaning that the lambda can modify the original `x` variable.

This capturing ability allows lambdas to remain valid, even if the variables they capture go out of scope.
