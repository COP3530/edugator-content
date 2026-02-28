# Sets and Maps

**Author:** *Brian Magnuson*

In this lesson, we will be covering sets and maps, two data structures used to store collections of data. Sets are useful for storing unique values, while maps are useful for storing key-value pairs. Both use similar underlying data structures to store their data, but they have different use cases and methods for accessing and manipulating their data.

We will be covering the following:
- Introduction to sets
- Introduction to maps
- Tree sets and tree maps
- Hash sets and hash maps
- Multisets and multimaps
- Sets and maps in other programming languages

This lesson will largely focus on sets and maps in C++'s standard library, but the concepts can be applied to other programming languages as well.

We'll start by introducing the interfaces for sets and maps, then we'll explore the differences between their ordered and unordered implementations.

# Introduction to Sets

A **set** is a collection of unique values. 
A set may be *ordered* or *unordered* depending on the underlying data structure used to store the values.
Sets are typically used to determine whether a value is present in a collection or to filter out duplicate values.

In C++, the standard library provides two main types of sets: `std::set` and `std::unordered_set`.

Both sets provide the following functions:
- `insert()` adds an element to the set.
- `emplace()` constructs an element in-place in the set.
  - The arguments passed to `emplace()` are forwarded to the constructor of the element type.
  - This can be more efficient than `insert()` because it avoids creating temporary objects.
- `erase()` removes an element from the set.
- `find()` searches for an element in the set.
  - Returns an iterator to the element if found, otherwise returns `end()`.
  - Note: this is different from `std::find()`; this function uses a more efficient search algorithm.
- `empty()` returns `true` if the set is empty and `false` otherwise.
- `size()` returns the number of elements in the set.
- `count()` returns the number of elements in the set that are equal to a given value.
  - This function is useful for checking if an element is in the set.
  - Since sets only store unique elements, the return value will be `0` or `1`.

In the following example, we demonstrate how to use a set to store unique values:

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(3); // duplicate value, will not be added
    for (int i : s) {
        std::cout << i << " "; // 1 2 3
    }
    return 0;
}
```

This code will compile and run successfully, outputting `1 2 3`. Even though we attempted to insert the value `3` twice, it was only added once because sets do not allow duplicate values. 
No error will be thrown; the duplicate value will simply be ignored.

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.erase(2);
    for (int i : s) {
        std::cout << i << " "; // 1 3
    }
    std::cout << "\n";
    std::cout << s.count(1) << "\n"; // 1
    std::cout << s.count(2) << "\n"; // 0
    std::cout << s.size() << "\n"; // 2 (2 elements in the set)
    std::cout << s.empty() << "\n"; // false (set is not empty)
    return 0;
}
```

Here, we use the `erase()` function to remove the value `2` from the set. We then use the `count()` function to check if the values `1` and `2` are in the set. `count()` is a useful function for checking if an element is in the set. Since sets only store unique elements, the return value will be `0` or `1`.

In both of the above examples, we use a range-based for loop to iterate over the elements in the set. We can also use iterators to traverse the set:

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s = {1, 2, 3};
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " "; // 1 2 3
    }
    return 0;
}
```

In this example, we use an iterator `it` to traverse the set. We start at the beginning of the set with `s.begin()` and iterate until we reach the end of the set with `s.end()`. We then dereference the iterator with `*it` to access the value at that position.

------

```cpp
std::set<int> s;
s.insert(10);
s.insert(10);
s.erase(10);
s.insert(20);
s.insert(20);
s.insert(30);
s.erase(20);
s.insert(40);
for (int i : s) std::cout << i << " ";
```

What is the output of the above code?
- 30 40
- 10 30 40
- 10 20 30 40
- 10 10 20 20 30 40
- (runtime error)

<details>
<summary>Answer</summary>
30 40
</details>

------

# Introduction to Maps

A **map** is a collection of key-value pairs.
A map may be *ordered* or *unordered* depending on the underlying data structure used to store the key-value pairs.
Maps are useful for associating values with keys and looking up values based on keys (rather than array indices).

In C++, the standard library provides two main types of maps: `std::map` and `std::unordered_map`.

Maps have a similar interface to sets, but their usage is a bit more complex due to the key-value pair structure.

## Inserting Elements

A typical way to insert elements into a map is to use the `insert()` function with an initializer list for a pair.
```cpp
std::map<int, std::string> map;
map.insert({1, "one"});
```

You can also use `emplace()`, which constructs the element in place and returns a pair containing an iterator to the element and a boolean indicating if the element was successfully inserted.
```cpp
map.emplace(2, "two");
```

`emplace()` can get a little messy when the constructors for the key and value types use multiple arguments. You can refer to the examples [here](https://en.cppreference.com/w/cpp/container/map/emplace).

If the key already exists in the map, `insert()` and `emplace()` will not insert a new element nor modify the existing entry. If you want to overwrite the value for an existing key, you can use the `[]` operator or the `at()` function.

## Accessing elements

You can access elements in a map using the `[]` operator or the `at()` function.

The `[]` operator will locate the element with the given key and return a reference to the value. If the key does not exist, a new element will be created with the default value for the value type.
```cpp
std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
map[1]; // "one"
map[4]; // ""
```

The `at()` function will locate the element with the given key and return a reference to the value. If the key does not exist, an `std::out_of_range` exception will be thrown.
```cpp
map.at(1); // "one"
map.at(5); // Throws an exception
```

Be careful about using the `[]` operator to access elements in a map. You might accidentally insert a new element if you aren't careful.

## Other Map Functions

The rest of the functions provided by maps are similar to those provided by sets.

- `erase()` removes an element from the map.
- `find()` searches for an element in the map.
  - Returns an iterator to the key-value pair if found, otherwise returns `end()`.
  - The iterator points to an `std::pair`, so you can access the key and value using `iter->first` and `iter->second`.
- `count()` returns the number of elements with the given key.
  - Since maps only store unique keys, the return value will be `0` or `1`.
- `empty()` returns `true` if the map is empty and `false` otherwise.
- `size()` returns the number of elements in the map.

```cpp
std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
map.erase(1);
auto iter = map.find(2);
if (iter != map.end()) {
    std::cout << "Found\n";
    std::cout << "Key: " << iter->first << "\n"; // Key: 2
    std::cout << "Value: " << iter->second << "\n"; // Value: two
} else {
    std::cout << "Not found\n";
}
map.empty(); // false
map.size(); // 2
```

------

```cpp
std::map<int, std::string> m;
m.emplace(1234, "Abby");
m.emplace(5678, "Bob");
m.emplace(1234, "Charlie");
m.emplace(9012, "Bob");
for (auto p : m) std::cout << p.second << " ";
```

Based on the above code, whose names will be printed to the console?
- Abby, Bob, and Charlie
- Abby and 2 instances of Bob
- Charlie and 2 instances of Bob
- Abby, Charlie, and 2 instances of Bob
- This program will have a runtime error

<details>
<summary>Answer</summary>
Abby and 2 instances of Bob
</details>

------

```cpp
std::map<char, int> m;
std::string s = "hello";
for (char c : s) m[c]++;
std::cout << m['l'] << " " << m['p'] << "\n";
```

Describe the output of the above code.
- The program is deterministic and will output "2 1".
- The program is deterministic and will output "2 0".
- The program behavior is undefined, but will likely output "2 0".
- The program behavior is undefined and the output is not predictable.
- The program will have a runtime error.

<details>
<summary>Answer</summary>
The program is deterministic and will output "2 0".
</details>

------

# Tree Sets and Tree Maps

**Tree sets** and **tree maps**, also known as ordered sets and ordered maps, are implemented using balanced binary search trees. This allows for efficient insertion, deletion, and searching of elements in O(log n) time.

In C++, `std::set` and `std::map` are implemented as tree sets and tree maps, respectively. The elements in a tree set or tree map are ordered based on the keys. Most implementations use a red-black tree, which is a type of self-balancing binary search tree.

`std::set` and `std::map` iterators are **bidirectional iterators**, meaning they can be incremented and decremented. They can be used to traverse the elements in the set or map in ascending or descending order.

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s = {3, 1, 2};
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " "; // 1 2 3
    }
    std::cout << "\n";
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        std::cout << *it << " "; // 3 2 1
    }
    return 0;
}
```

Tree sets and tree maps generally require that the key types be **comparable**. This can mean different things depending on the language. The value types for maps do not need to be comparable.

C++'s sets and maps, by default, use the `std::less` function object to compare elements. A **function object**, also known as a **functor** is an object whose type overloads `operator()`, allowing it to be called like a function.

The following lines are equivalent:
```cpp
std::set<std::string> s;
std::set<std::string, std::less<std::string>> s;
```

The implementation of `std::less` is something like this:
```cpp
template <typename T>
struct less {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};
```

Because of this, any type that overloads the `operator<` can be used as a key in a set or map.

You can technically achieve the same behavior by creating a specialization of `std::less` for your type, but this is generally not recommended.

```cpp
#include <set>
#include <string>

struct Student {
    std::string name;
    int id;
    bool operator<(const Student& other) const {
        return id < other.id;
    }
};

int main() {
    std::set<Student> students;
    students.insert({"Alice", 1}); // OK
    students.insert({"Bob", 2}); // OK
    return 0;
}
```

In this example, we define a `Student` class with a `name` and `id`. We overload the `operator<` to compare students based on their `id`. This allows us to use `Student` objects as keys in a set.

If we don't want to overload `operator<`, we can provide a custom comparison functor to the set or map.

```cpp
struct CompareStudents {
    bool operator()(const Student& lhs, const Student& rhs) const {
        return lhs.id < rhs.id;
    }
};

int main() {
    std::set<Student, CompareStudents> students;
    students.insert({"Alice", 1}); // OK
    students.insert({"Bob", 2}); // OK
    return 0;
}
```

In this example, we define a `CompareStudents` functor that compares students based on their `id`. We then provide this functor as the second template argument to the set.

If we don't want to create a separate class, we can use a lambda function as a comparison functor (since lambdas are syntactic sugar for function objects).
```cpp
int main() {
    auto compare_students = [](const Student& lhs, const Student& rhs) {
        return lhs.id < rhs.id;
    };
    std::set<Student, decltype(compare_students)> students(compare_students);
    students.insert({"Alice", 1}); // OK
    students.insert({"Bob", 2}); // OK
    return 0;
}
```

Notice how we have to use `decltype` in the template argument and pass the lambda function to the set's constructor.

# Hash Sets and Hash Maps

**Hash sets** and **hash maps**, also known as unordered sets and unordered maps, are implemented using hash tables. 
This allows for elements to be inserted, deleted, and searched in O(1) time on average and O(n) time in the worst case.

In C++, `std::unordered_set` and `std::unordered_map` are implemented as hash sets and hash maps, respectively. Elements are stored based on their hash values, which makes the exact order of elements unpredictable to the user.

Unlike tree sets and tree maps, hash sets and hash maps use forward iterators, which can only be incremented. They can be used to traverse the elements in the set or map.

```cpp
#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> s = {987, 123, 456};
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " "; 
        // 456 123 987
        // Exact order may vary
    }
    return 0;
}
```

Every element is reachable in this way, but the order in which they are reached is not guaranteed.

Hash sets and hash maps require that the key types be **hashable**. The exact requirements for this depend on the language. The value types for maps do not need to be hashable.

C++'s hash sets and maps, by default, use the `std::hash` function object to hash elements and `std::equal_to` to compare elements for equality.

The following lines are equivalent:
```cpp
std::unordered_set<std::string> s;
std::unordered_set<std::string, std::hash<std::string>> s;
std::unordered_set<std::string, std::hash<std::string>, std::equal_to<std::string>> s;
```

The implementation of `std::equal_to` is something like this:
```cpp
template <typename T>
struct equal_to {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs == rhs;
    }
};
```

Because of this, any type that overloads the `operator==` can potentially be used as a key in a hash set or hash map.

The implementation of `std::hash` is more complex. `std::hash` typically doesn't work unless there exists a specialization for the type you're using. Built-in specializations exist for the following types:
- All arithmetic types (integers, floating-point numbers)
- All pointer types (including smart pointers)
- All enumeration types
- `std::string`
- `std::bitset`
- `std::vector<bool>`
- And others; see [here](https://en.cppreference.com/w/cpp/utility/hash) for more information

If you want to use a custom type as a key in a hash set or hash map, you'll need to provide a specialization of `std::hash` for that type.
```cpp
#include <unordered_set>
#include <string>

struct Student {
    std::string name;
    int id;
    bool operator==(const Student& other) const {
        return id == other.id;
    }
};
template<>
struct std::hash<Student> {
    std::size_t operator()(const Student& s) const {
        return std::hash<int>()(s.id);
    }
};

int main() {
    std::unordered_set<Student> students;
    students.insert({"Alice", 1}); // OK
    students.insert({"Bob", 2}); // OK
    return 0;
}
```

This is one of the rare times where it is *recommended* to specialize a standard library template. The `std::hash` specialization for `Student` is necessary for the hash set to work correctly.

If you prefer, you can also create a custom functor for hashing.
```cpp
struct HashStudent {
    std::size_t operator()(const Student& s) const {
        return std::hash<int>()(s.id);
    }
};
```

You can also use a lambda function as a hash function.
```cpp
int main() {
    auto hash_student = [](const Student& s) {
        return std::hash<int>()(s.id);
    };
    std::unordered_set<Student, decltype(hash_student)> students(10, hash_student);
    students.insert({"Alice", 1}); // OK
    students.insert({"Bob", 2}); // OK
    return 0;
}
```

------

Which of the following statements is FALSE regarding sets and maps?
- The keys in tree sets and maps must be comparable.
- The keys in hash sets and maps must be hashable.
- The keys in sets and maps must be unique.
- The values in sets and maps must be unique.
- None of these; all statements are true.

<details>
<summary>Answer</summary>
The values in sets and maps must be unique.
</details>

------

# Multisets and Multimaps

This section is optional, but can be useful to know.

**Multisets** and **multimaps** are similar to sets and maps, respectively, but they allow duplicate keys. This means that you can have multiple elements with the same key in a multiset or multimap.

C++ provides a "multi-" version of all the associative containers:
- `std::multiset` in `<set>`
- `std::multimap` in `<map>`
- `std::unordered_multiset` in `<unordered_set>`
- `std::unordered_multimap` in `<unordered_map>`

## Multisets

The multiset interfaces are very similar to the set interfaces, but with a few differences:
- `insert()` and `emplace()` will always add the element to the container as long as the element type meets the requirements.
- `erase()`, when passed a key, will remove all elements with that key.
  - If passed an iterator, it will only remove that element.
- `count()` will return the number of elements with the given key.
- `find()` will return an iterator to any element that matches the key.
- `equal_range()` will return a pair of iterators that represent the range of elements with the given key.

```cpp
#include <iostream>
#include <set>

int main() {
    std::multiset<int> ms = {1, 2, 2, 3, 3, 3};
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    for (int i : ms) {
        std::cout << i << " "; // 1 2 2 3 3 3
    }
    std::cout << "\n";
    std::cout << ms.count(2) << "\n"; // 2
    auto it = ms.find(3);
    if (it != ms.end()) {
        std::cout << *it << "\n"; // 3
    }
    auto range = ms.equal_range(3);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " "; // 3 3 3
    }
    return 0;
}
```

## Multimaps

The multimap interfaces are very similar to the map interfaces, but with a few differences:
- `insert()` and `emplace()` will always add the key-value pair to the container as long as the key and value types meet the requirements.
- `erase()`, when passed a key, will remove all key-value pairs with that key.
  - If passed an iterator, it will only remove that key-value pair.
- `count()` will return the number of key-value pairs with the given key.
- `find()` will return an iterator to any key-value pair that matches the key.
- Neither container implements `at()` or `operator[]`.
- `equal_range()` will return a pair of iterators that represent the range of key-value pairs with the given key.

```cpp
#include <iostream>
#include <map>

int main() {
    std::multimap<int, std::string> mm = {{1, "one"}, {2, "two"}, {2, "dos"}, {3, "three"}, {3, "tres"}, {3, "trois"}};
    mm.insert({1, "uno"});
    mm.insert({2, "deux"});
    mm.insert({3, "quatre"});
    for (auto [key, value] : mm) {
        std::cout << key << ": " << value << "\n";
    }
    std::cout << mm.count(2) << "\n"; // 2
    auto it = mm.find(3);
    if (it != mm.end()) {
        std::cout << it->first << ": " << it->second << "\n"; // 3: three
    }
    auto range = mm.equal_range(3);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << "\n"; // 3: three, 3: tres, 3: quatre
    }
    return 0;
}
```

# Sets and Maps in Other Programming Languages

This section is also optional, but can be useful to know.

Sets and maps are so useful that nearly every modern programming language has some implementation of sets and maps built in to their standard libraries. Here are a few examples:

**Java**

In the `java.util` package, Java provides the `Set<E>` and `Map<K, V>` interfaces, which define a set of methods common across all set and map implementations. Some common implementations include `HashSet`, `TreeSet`, `LinkedHashSet`, `HashMap`, `TreeMap`, and `LinkedHashMap`.

**C#**

In the `System.Collections.Generic` namespace, C# provides the `HashSet<T>`, `SortedSet<T>`, `Dictionary<TKey, TValue>`, and `SortedDictionary<TKey, TValue>` classes.

**Python**

Python provides sets and dictionaries as built-in data types. Sets are created using curly braces `{}` and are not ordered. Dictionaries are created using curly braces `{}` with key-value pairs separated by colons `:`.

```python
s = {1, 2, 3}
d = {1: 'one', 2: 'two', 3: 'three'}
```

Curiously, as of Python 3.7, dictionaries are ordered by insertion order. This means that iterating over a dictionary will return the key-value pairs in the order they were inserted.

**JavaScript**

In JavaScript, sets and maps are built-in data structures. Sets are created using the `Set` class, and maps are created using the `Map` class.

```javascript
let s = new Set([1, 2, 3]);
let m = new Map([[1, 'one'], [2, 'two'], [3, 'three']]);
```

These data structures order their elements based on insertion order, similar to Python dictionaries.

JavaScript objects also function very similarly to maps, as they allow you to associate keys with values.

```javascript
let o = {1: 'one', 2: 'two', 3: 'three'};
```

This is a brief overview of sets and maps in other programming languages. Each language has its own unique features and implementations, but the core concepts of sets and maps remain the same.

# Conclusion

In this lesson, we covered sets and maps, two data structures used to store collections of data. Sets are useful for storing unique values, while maps are useful for storing key-value pairs. Both sets and maps have ordered and unordered implementations, which use different underlying data structures to store their data.

We discussed tree sets and tree maps, which are implemented using balanced binary search trees, and hash sets and hash maps, which are implemented using hash tables. We also covered multisets and multimaps, which allow duplicate keys.

Finally, we briefly discussed sets and maps in other programming languages.

# References

- [Cppreference: Containers library](https://en.cppreference.com/w/cpp/container)
- [Java SE 11 & SDK 11: java.util](https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/util/package-summary.html)
- [Microsoft .NET Docs: System.Collections.Generic Namespace](https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic?view=net-9.0)
- [Python Documentation: Data Structures](https://docs.python.org/3/tutorial/datastructures.html)

Lesson content written with AI assistance.

This work by Brian Magnuson is licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).

Find a mistake? Open an issue on [GitHub](https://github.com/COP3530/edugator-content/issues)!
