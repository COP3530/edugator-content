# Sets and Maps

**Author:** *Brian Magnuson*

In this lesson, we will be covering sets and maps, two data structures used to store collections of data. Sets are useful for storing unique values, while maps are useful for storing key-value pairs. Both use similar underlying data structures to store their data, but they have different use cases and methods for accessing and manipulating their data.

We will be covering the following:
- Introduction to sets
- Tree sets and compare functors
- Hash sets and hash functors
- Multisets
- Introduction to maps
- Tree maps and compare functors
- Hash maps and hash functors
- Multimaps
- Sets and maps in other programming languages

This lesson will largely focus on sets and maps in C++'s standard library, but the concepts can be applied to other programming languages as well.

# Introduction to Sets

A **set** is a collection of unique values. 
A set may be *ordered* or *unordered* depending on the underlying data structure used to store the values.
Sets are typically used to determine whether a value is present in a collection or to filter out duplicate values.

In C++, the standard library provides two main types of sets: `std::set` and `std::unordered_set`.

Both sets provide the following functions:
- `insert()` adds an element to the set.
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

# Tree Sets and Compare Functors

The `std::set` class in C++ is typically implemented as a **balanced binary search tree**. This means that the elements are stored in a sorted order, and operations like `insert()`, `erase()`, and `find()` have a time complexity of O(log n), where n is the number of elements in the set.
