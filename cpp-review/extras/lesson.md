# C++ Extras

**Author:** *Brian Magnuson*

In this lesson, we will cover more features of C++ and its standard library. These are topics that did not fit into the previous lessons, but are still important to know.

In this lesson, we will cover the following topics:
- Strings
- Regular expressions
- Templates
- Exceptions
- Function pointers, functors, and lambdas
- File I/O

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

    if (std::regex_search(str, match, regex)) {
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

# Templates

