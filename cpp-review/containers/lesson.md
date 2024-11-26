# C++ Containers

**Author:** *Brian Magnuson*

In this lesson, we will be discussing C++'s containers library, one of the most important parts of the C++ standard library. 

Occasionally, I may refer the containers library as the **Standard Template Library (STL)**. STL actually includes containers, algorithms, and iterators. In this lesson, we will be discussing both containers and iterators.

There are quite a few containers available in C++. Many of them use similar interfaces. So for this lesson, we will be start by covering `std::vector`, the most commonly used container in C++, in detail. Then we will discuss the other containers.

In this lesson, we will cover the following topics:
- Vectors
- Iterators
- Linked lists
- Stacks, queues, and double-ended queues
- Priority queues
- Sets
- Maps

We will not be covering `std::array` in this lesson. `std::array` is a fixed-size array that is a wrapper around a C-style array. You can read more about `std::array` [here](https://en.cppreference.com/w/cpp/container/array).

And one more thing: The purpose of this lesson is to teach you how to use these containers, not to teach you to implement them or the theory behind them. If I were to talk about that, this single lesson would turn into a full-size course on data structures and algorithms. We'll discuss these topics in later lessons.

# Vectors

An `std::vector` is C++'s dynamic array class and is defined in the `<vector>` header. A **dynamic array** is an array that can grow and shrink in size.

In actuality, dynamic arrays have a fixed capacity. When the array size reaches capacity, a new array of a larger capacity is allocated, and the elements are copied over. Usually, the old capacity is multiplied by some constant factor to get the new capacity, so this operation occurs less frequently as more elements are added.

An `std::vector` can be initialized in a number of ways. Here are a few examples:
```cpp
// Create an empty vector
std::vector<int> vec1;

// Create a vector with 10 elements, all initialized to 0 (or default constructed)
std::vector<int> vec2(10);

// Create a vector with 10 elements, all initialized to 5
std::vector<int> vec3(10, 5);

// Create a vector using an initializer list
std::vector<int> vec4 = {1, 2, 3, 4, 5};

// Copy a vector
std::vector<int> vec5(vec4);

// Copy a vector using an iterator
std::vector<int> vec6(vec4.begin(), vec4.end());
```

## Empty, Size, and Clear

I bring special attention to the `empty()`, `size()`, and `clear()` functions as almost all containers have these functions.

- `empty()` returns `true` if the container is empty and `false` otherwise. 
- `size()` returns the number of elements in the container. Usually a `size_t`, which is compatible with `unsigned int` (though GCC probably won't get mad if you use `int`).
- `clear()` removes all elements from the container.

```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
vec.empty(); // false
vec.size(); // 5
vec.clear();
vec.empty(); // true
vec.size(); // 0
```

## Accessing Elements

Vector elements can be accessed using the `[]` operator (sometimes called the subscript operator) or the `at()` function. The difference between the two is that `[]` does not do bounds checking, while `at()` does. If you try to access an element that is out of bounds using `at()`, an `std::out_of_range` exception will be thrown.

```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
vec[0]; // 1
vec.at(0); // 1
vec[5]; // Undefined behavior
vec.at(5); // Throws an exception
```

Unlike with maps, you cannot use the `[]` operator to insert elements into a vector.

Both `[]` and `at()` return a reference to the element, so you can use them on the left side of an assignment statement to modify the element. Both have const and non-const versions, so you are free to use them with `const` variables.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
vec[0] = 10;
vec.at(1) = 20;
```

You can use these functions in combination with the `size()` function to iterate over the elements of a vector.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << " ";
}
```

This is the most basic way to iterate over a vector, but there are other ways which we will discuss later.

Vectors allow you to access the front and back elements using the `front()` and `back()` functions, respectively.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
vec.front(); // 1
vec.back(); // 5
```

## Inserting and Removing Elements

With vectors, you can insert and remove elements at the end of the vector using the `push_back()` and `pop_back()` functions, respectively.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
vec.back(); // 5
vec.push_back(6);
vec.back(); // 6
vec.pop_back();
vec.back(); // 5
```

As mentioned, when the vector reaches capacity, a new array is allocated and the elements are copied over. Because of this, the worst-case time complexity of `push_back()` linear in container size. However, the amortized time complexity is constant and we generally treat it as such.

If you happen to know how much space you will need, you should make sure to initialize the vector with the size you need to avoid unnecessary reallocations.

## Comparing Vectors

Vectors can be compared using the `==` and `!=` operators. The comparison is done element-wise.
```cpp
std::vector<int> vec1 = {1, 2, 3, 4, 5};
std::vector<int> vec2 = {1, 2, 3, 4, 5};

vec1 == vec2; // true
vec1 != vec2; // false
```

Since each element is compared, the worst-case time complexity of comparing two vectors is linear in the size of the vectors.

# Iterators

Most containers have a public inner class called an **iterator**. An iterator is an object that allows you to traverse the elements of a container. Iterators are similar to pointers in that they can be dereferenced and incremented. For a vector, it is something like `std::vector<T>::iterator`, where `T` is the type of the elements in the vector.

There are a few different types of iterators:
- Forward Iterators allow you to only move forward through the container.
  - You can use the `++` operator to move to the next element.
- Bidirectional Iterators allow you to move forward and backward through the container.
  - They include all the functionality of Forward Iterators.
  - You can also use the `--` operator to move to the previous element.
- Random Access Iterators allow you access any element in the container in constant time.
  - They include all the functionality of Bidirectional Iterators.
  - You can also use the `+`, `-`, `+=`, and `-=` operators to move to any element in the container.

Vectors have random access iterators, so you can use the `+`, `-`, `+=`, and `-=` operators to move to any element in the vector. Not all containers have random access iterators, so you should be careful when using these operators.

To demonstrate iterators, we'll loop through the elements of a vector using them:
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
for (auto it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << " ";
}
```

Most containers have a `begin()` and `end()` function.
The `begin()` function returns an iterator to the first element, and the `end()` function returns an iterator to *one past the last element* of the container. Dereferencing the iterator returned by `end()` is undefined behavior.

Here, we initialize `it` to the iterator returned by `begin()`. We use the `auto` keyword since writing the type of the iterator can be quite verbose. We then loop through the elements of the vector, dereferencing the iterator to get the element.

If all we need is to iterate through the elements in order, we can use a range-based for loop. This is a more concise way to iterate through the elements of a container.
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
for (int i : vec) {
    std::cout << i << " ";
}
for (int& i : vec) { // Same as above, but we use a reference instead of a copy
    i++;
}
```

A range-based for loop uses iterators under the hood and automatically dereferences the iterator for you. Theoretically, you can write your own container class and use a range-based for loop with it, as long as you provide the `begin()` and `end()` functions.

There are other functions that make use of iterators.

- `insert()` allows you to insert elements at a specific position in the container.
  - For vectors, the elements after the position need to be shifted over, so the time complexity of this operation is linear in container size.
- `erase()` allows you to remove elements at a specific position in the container.
  - Similar to `insert()`, the elements after the position need to be shifted over.
  
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = vec.begin() + 2;
vec.insert(it, 10); // {1, 2, 10, 3, 4, 5}
vec.erase(it); // {1, 2, 3, 4, 5}
```

There are also functions defined in the `<algorithm>` header that make use of iterators.
- `std::sort()` sorts the elements of a container.
  - The time complexity of this operation is `O(n log n)`, where `n` is the size of the container.
  - This function's implementation usually combines multiple sorting algorithms to be as efficient as possible.
- `std::find()` searches for an element in a container.
  - The time complexity of this operation is linear in the size of the container.

```cpp
std::vector<int> vec = {5, 3, 1, 4, 2};
std::sort(vec.begin(), vec.end()); // {1, 2, 3, 4, 5}
std::find(vec.begin(), vec.end(), 3); // Returns an iterator to the element 3
```

And that's about everything you need to know about vectors and iterators. We'll continue by covering the other containers and how they are different from vectors.

# Linked Lists

A linked list is a data structure that consists of nodes. Each node contains a value and a pointer to the next node in the list. The last node in the list points to `nullptr`.

C++ provides two classes that implement linked lists: `std::forward_list` and `std::list`. They are single and doubly linked lists, respectively and are defined in the `<forward_list>` and `<list>` headers.

`std::list` is similar to an `std::vector`, but with the following differences:

- `insert()` and `erase()` have constant time complexity.
  - This is because the pointers in the nodes are updated, rather than shifting elements over.
  - However, you still need the iterator to the element you want to insert or erase, and arriving at that element can still take linear time.
- `list` provides some additional functions for adding elements:
  - `push_front()` and `pop_front()` add and remove elements from the front of the list.
  - These functions have constant time complexity.
- `list` only provides a bidirectional iterator, so you can't use the `+`, `-`, `+=`, and `-=` operators to move to any element in the list.
- `list` does not have `operator[]` or `at()` to access elements by index.

```cpp
std::list<int> list = {1, 2, 3, 4, 5};
auto it = list.begin();
list.insert(it, 10); // {10, 1, 2, 3, 4, 5}
list.erase(it); // {1, 2, 3, 4, 5}
list.push_front(10); // {10, 1, 2, 3, 4, 5}
list.pop_front(); // {1, 2, 3, 4, 5}
```

`std::forward_list` is similar to `std::list`, but with the following differences:

- `forward_list` is a singly linked list, so it only has a forward iterator.
  - It still has an `end()` function, but since it is a forward iterator, you can't use it to iterate backwards.
- `forward_list` does not have a `size()` function (crazy, right?).
- `forward_list` does not have a `push_back()`, `pop_back()`, or `back()` function.

`std::list` and `std::forward_list` are not very commonly used, but they still offer a few advantages over vectors in certain situations. For one, they make splitting and merging lists easier. They also have constant time complexity for inserting and erasing elements at any position.

# Stacks, Queues, and Double-Ended Queues

A **stack** is a data structure that allows you to add and remove elements from the top. This is known as a **last-in, first-out (LIFO)** data structure. 

C++ provides the `std::stack` class that implements a stack and is defined in the `<stack>` header. You'll find that it actually provides very few functions. Mainly just these:
- `push()` adds an element to the top of the stack.
- `pop()` removes the element at the top of the stack.
- `top()` returns a reference to the element at the top of the stack.
- `empty()` returns `true` if the stack is empty and `false` otherwise.
- `size()` returns the number of elements in the stack.

Note that some other programming languages use `pop()` to also return the element at the top of the stack. C++ does not do this. You need to use `top()` to get the element at the top of the stack.

```cpp
std::stack<int> stack;
stack.push(1);
stack.push(2);
stack.push(3);
stack.top(); // 3
stack.pop();
stack.top(); // 2
```

Stacks do not provide iterators, so you can't iterate through the elements of a stack. You can only access the top element.

An `std::stack` is an example of a wrapper container. It uses another container to operate. The container is required to implement the `push_back()`, `pop_back()`, and `back()` functions. By default, `std::stack` uses an `std::deque` as the underlying container, but an `std::vector` or `std::list` can also be used.

So if you were thinking you could use an `std::vector` as a stack, you'd be totally right. The main difference is that `std::stack` provides a more limited interface than `std::vector`. This can be a good thing, though, as it indicates to the programmer that the container should only be used as a stack.

A **queue** is a data structure that allows you to add elements to the back and remove elements from the front. This is known as a **first-in, first-out (FIFO)** data structure.

C++ provides the `std::queue` class that implements a queue and is defined in the `<queue>` header.

It is similar to a stack in that it provides very few functions. Mainly just these:
- `push()` adds an element to the back of the queue.
- `pop()` removes the element at the front of the queue.
- `front()` returns a reference to the element at the front of the queue.
- `back()` returns a reference to the element at the back of the queue.
- `empty()` returns `true` if the queue is empty and `false` otherwise.
- `size()` returns the number of elements in the queue.

```cpp
std::queue<int> queue;
queue.push(1);
queue.push(2);
queue.push(3);
queue.front(); // 1
queue.back(); // 3
queue.pop();
queue.front(); // 2
```

Like `std::stack`, `std::queue` is not iterable and is a wrapper for another container. The container needs to implement the `push_back()`, `pop_front()`, `front()`, and `back()` functions, so an `std::deque` is suitable.

A **double-ended queue** (deque) is a data structure that allows you to add and remove elements from both the front and back. It effectively combines the functionality of a stack and a queue.

Double-ended queues are typically implemented as a circular array (an array with two pointers to keep track of the front and back) or a doubly linked list.

C++ provides the `std::deque` class that implements a double-ended queue. It is similar to a vector and provides many of the same functions with the addition of:
- `push_front()` adds an element to the front of the deque.
- `pop_front()` removes the element at the front of the deque.

`std::deque` also provides an iterator. If you need an iterable queue, an `std::deque` is a good choice.

```cpp
std::deque<int> deque;
deque.push_front(1);
deque.push_front(2);
deque.push_back(3);
deque.push_back(4);
deque.front(); // 2
deque.back(); // 4
deque.pop_front();
deque.pop_back();
deque.front(); // 1
deque.back(); // 3
```

An `std::deque` can even be initialized like a vector:
```cpp
std::deque<int> deque = {1, 2, 3, 4, 5};
for (int i : deque) {
    std::cout << i << " ";
}
```

# Priority Queues

A **priority queue** is a data structure that allows you to add elements with a priority and remove the element with the highest priority. 

Priority queues are typically implemented as a binary heap, a data structure that is a complete binary tree where each node is greater than or equal to its children. Most operations on a binary max heap are logarithmic in the number of elements.

C++ provides the `std::priority_queue` class that implements a priority queue and is defined in the `<queue>` header. Like `std::stack` and `std::queue`, it is a wrapper for another container. The container needs to implement the `push_back()`, `pop_back()`, and `back()` functions, so an `std::vector` is suitable.

`std::priority_queue` provides the following functions:
- `push()` adds an element to the priority queue.
- `pop()` removes the element with the highest priority.
- `top()` returns a reference to the element with the highest priority.
- `empty()` returns `true` if the priority queue is empty and `false` otherwise.
- `size()` returns the number of elements in the priority queue.

```cpp
std::priority_queue<int> pq;
pq.push(3);
pq.push(1);
pq.push(2);
pq.top(); // 3
pq.pop();
pq.top(); // 2
```

Here, even though `1` was pushed before `2`, `2` has a higher priority because it is larger. 

By default, `std::priority_queue` is a max heap. But we can customize it by providing more template arguments. The second argument is the container to use, and the third argument is a comparison functor class.
```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
pq.push(3);
pq.push(1);
pq.push(2);
pq.top(); // 1
```

By default, `std::priority_queue` uses `std::less` as the comparison functor, which (confusingly) creates a max heap. If you want a min heap, you should use `std::greater`.

If you're not familiar, a **functor** or **function object** is an instance of a class that overloads the `()` operator. It is used to provide a custom comparison function to the priority queue.

The implementation of `std::less` is very simple. Usually something like this:
```cpp
template <typename T>
struct less {
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};
```

You can imagine `std::greater` is similar, but with the comparison operator flipped.

Because C++ lambda functions are functors under the hood, you can use them in place of a functor class.
```cpp
auto cmp = [](int lhs, int rhs) { return lhs > rhs; };
std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
```

This also makes it possible to use a priority queue with more complex objects. Suppose we wanted to use 2D points and compare them by their distance from the origin.
```cpp
struct ComparePoints {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        return lhs.first * lhs.first + lhs.second * lhs.second < rhs.first * rhs.first + rhs.second * rhs.second;
    }
};

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, ComparePoints> pq;
```

In this priority queue, we use the `<` operator to compare the distances of the points from the origin. This means we are creating a max heap, and the first element in the priority queue will be the point farthest from the origin.

# Sets

A **set** is a data structure that stores unique elements. It is implemented using either a binary search tree or a hash table.

C++ provides two classes that implement sets: `std::set` and `std::unordered_set`, defined in the `<set>` and `<unordered_set>` headers, respectively.
They are implemented using a binary search tree and a hash table, respectively. 

- `std::set`
  - Elements are stored in sorted order.
  - Most operations have a time complexity of `O(log n)`.
  - The keys must be comparable.
    - If the keys are not normally comparable, you can provide a comparison functor.
- `std::unordered_set`
  - Elements are stored in an arbitrary order.
  - Most operations have an amortized time complexity of `O(1)`.
  - The keys must be hashable.
    - If the keys are not normally hashable, you can provide a hash function.

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

```cpp
std::set<int> set;
set.insert(1);
set.insert(2);
set.insert(2); // 2 will not be inserted again
set.size(); // 2
set.erase(1);
set.size(); // 1

set.find(2); // Returns an iterator to 2
set.find(3); // Returns set.end()
set.count(2); // 1
set.count(3); // 0
```

Both `std::set` and `std::unordered_set` provide iterators. The iterators are bidirectional for `std::set` and forward for `std::unordered_set`.

```cpp
std::set<int> set = {1, 2, 3, 4, 5};
for (auto it = set.begin(); it != set.end(); it++) {
    std::cout << *it << " ";
}
```

By default, `std::set` uses `std::less<T>` as the comparison functor, which compares elements using the `<` operator. If you want to use a custom comparison function, you can provide a comparison functor as a template argument. This is useful for custom objects. We'll use the same `ComparePoints` functor from the priority queue example.
```cpp
std::set<std::pair<int, int>, ComparePoints> set;
set.insert({1, 2});
set.insert({3, 4});
```

For `std::unordered_set`, the default hash functor class is `std::hash<T>`. You can provide a custom hash function if the keys are not normally hashable. The rules for creating a hash function are a little complicated, so we won't go too deep into it. They go something like this:
- The return type is a `size_t` (an unsigned integer type).
- The function should be deterministic (return the same value for the same input).
- The function should be fast to compute.
- The function should distribute the hash values evenly.

You'll learn more about hash functions in a later lesson.

There is also a `std::multiset` and `std::unordered_multiset` that allow duplicate elements.
They are also defined in the `<set>` and `<unordered_set>` headers, respectively. The `insert()` function will always insert the element, and the `count()` function will return the number of elements equal to a given value.

# Maps

A **map** is a data structure that stores key-value pairs. Similar to sets, maps are implemented using either a binary search tree or a hash table.

C++ provides two classes that implement maps: `std::map` and `std::unordered_map`, defined in the `<map>` and `<unordered_map>` headers, respectively.

- `std::map`
  - Elements are stored in sorted order by key.
  - Most operations have a time complexity of `O(log n)`.
  - The keys must be comparable.
    - If the keys are not normally comparable, you can provide a comparison functor.
- `std::unordered_map`
  - Elements are stored in an arbitrary order.
  - Most operations have an amortized time complexity of `O(1)`.
  - The keys must be hashable.
    - If the keys are not normally hashable, you can provide a hash function.

Though maps can be default constructed, they can also be initialized using a list of pairs. Each pair represents a key-value pair.
```cpp
std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
```

Maps do things a bit differently than sets, so we'll go over the functions they provide.

## Inserting elements

A typical way to insert elements into a map is to use the `insert()` function with an initializer list for a pair.
```cpp
std::map<int, std::string> map;
map.insert({1, "one"});
```

You can also use `emplace()`, which constructs the element in place and returns a pair containing an iterator to the element and a boolean indicating if the element was successfully inserted.
```cpp
map.emplace(2, "two");
```

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

## Iterating over elements

Maps provide iterators that allow you to iterate over the elements. The iterators are bidirectional for `std::map` and forward for `std::unordered_map`.
However, they are slightly different from the other iterators we've seen. Iterators for maps are iterators to pairs of keys and values.

```cpp
std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
for (auto it = map.begin(); it != map.end(); it++) {
    std::cout << it->first << ": " << it->second << " ";
}
for (auto pair : map) {
    std::cout << pair.first << ": " << pair.second << " ";
}
for (auto& [key, value] : map) {
    std::cout << key << ": " << value << " ";
}
```

The first loop is the most basic way to iterate over a map. The second loop uses a range-based for loop, which is more concise. The third loop uses structured bindings, which allows you to unpack the pair into separate variables (structured bindings were introduced in C++17).

## Other map functions

The rest of the functions provided by maps are similar to those provided by sets.

- `erase()` removes an element from the map.
- `find()` searches for an element in the map.
- `empty()` returns `true` if the map is empty and `false` otherwise.
- `size()` returns the number of elements in the map.

```cpp
std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
map.erase(1);
if (map.find(2) != map.end()) {
    std::cout << "Found" << std::endl;
} else {
    std::cout << "Not found" << std::endl;
}
map.empty(); // false
map.size(); // 2
```

# Conclusion

And that's it for this lesson on C++ containers! In this lesson, we've only covered how to use these containers. We haven't discussed how they are implemented or the theory behind them. We'll discuss these topics in later lessons.

# References

- [C++ Reference](https://en.cppreference.com/w/cpp)
