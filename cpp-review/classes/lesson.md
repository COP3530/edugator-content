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

For your C++ projects in this course, you will be expected to utilize encapsulation to protect your class members.

# Constructors

Suppose we have the following classes:
```cpp
class Vector2D {
public:
    int x = 0;
    int y = 0;
};
class Character {
public:
    Point position;
    int health;
    int power;
};
```

We can instantiate a `Character` in one of these ways:
```cpp
Character player_1 = Character();
Character player_2; // More concise
```

Both of these methods call the class's **default constructor**. A **constructor** is a special member function that instantiates an object of a class. A default constructor is a constructor that takes no arguments.

Since we didn't define any constructor for `Character`, C++ provides a default constructor for us. The automatic default constructor calls the default constructors of all the class's members, except for primitive types like `int`, which are not initialized. Using `player_1.health` at this point would be undefined behavior.

To define our own constructor, we can do this:
```cpp
class Character {
public:
    Point position;
    int health;
    int power;
    Character() {
        health = 100;
        power = 10;
    }
};
```

Constructors and destructors do not have a return type.

We can also declare the constructor outside the class definition:
```cpp
class Character {
public:
    Point position;
    int health;
    int power;
    Character();
};

Character::Character() {
    health = 100;
    power = 10;
}
```

To define class members outside the class definition, we use the scope resolution operator `::`. This operator is used to define functions that are declared inside a class. Remember, it's a good idea to put your function implementations in a separate source file.

You can also define your constructor like this:
```cpp
Character::Character() : health(100), power(10) {}
```

This method effectively does the same thing, but by using an initializer list like this, you can initialize members that cannot be assigned a value in the constructor body (such as `const` members).

You can also write constructors that take arguments:
```cpp
class Character {
public:
    Point position;
    int health;
    int power;
    Character(int h, int p) : health(h), power(p) {}
};
```

However, if you do not also have a default constructor, C++ will NOT provide one for you.

# Member Functions

Member functions are functions that are part of a class. They can access the class's private members and are called using the `.` operator on an object of the class.

Here's an example of a class with a member function:
```cpp
class Character {
    Point position;
    int health = 100;
    int power = 10;
public:
    void move(int x, int y);
};

void Character::move(int x, int y) {
    position.x += x;
    position.y += y;
}
```

And we can use it like this:
```cpp
Character player;
player.move(5, 10);
```

Even though `position` is private, the `move` function can access it because it's a member of the `Character` class.

If `player` happened to be a pointer, we would have to dereference it to call the member function. The syntax for this is a bit messy which is why C++ provides a special operator `->` for this purpose:
```cpp
Character* player = new Character();
// (*player).move(5, 10);
player->move(5, 10);
```

All non-static member functions have access to a special pointer called `this`, which points to the object on which the function was called. Earlier, we did not need it because `position` unambiguously referred to the `position` member. However, if we had a parameter with the same name as a member, we would need to use `this` to access the member:
```cpp
void Character::take_damage(int health) {
    this->health -= health;
}
```

Notice that we have to use the `->` operator here since `this` is a pointer.

Both of these member functions, `move` and `take_damage` change, or **mutate**, the state of the object. Sometimes, we don't want to mutate the object. And in some cases, we *can't* mutate the object.
```cpp
const Character player;
// player.move(5, 10); // Error: Cannot call non-const member function on const object
```

This helps make sure we don't accidentally change the state of an object when we shouldn't. But not every member function will mutate the object. In these cases, we need to tell the compiler that the function won't change the object's state by using the `const` keyword:
```cpp
bool Character::is_alive() const {
    return health > 0;
}
```

By marking the function as `const`, we disallow any modifications to `this` inside the function. We can then call this function on a `const` object:
```cpp
const Character player;
player.is_alive(); // OK
```

It is good practice to mark member functions as `const` if they do not modify the object's state.

On rare occassions, you will want to create a member function that returns a reference to a member variable for the caller to access and possibly modify. In these cases, you may need both a `const` and non-`const` version of the function. This is the case for many STL containers, like `std::vector`.

# Copy Constructors and Copy Assignment Operators

There are two ways to create a copy of an object in C++: the copy constructor and the copy assignment operator.
```cpp
Character player_1;
Character player_2 = player_1; // player_2 is copy-constructed from player_1
Character player_3;
player_3 = player_1; // player_3 is copy-assigned from player_1
```

The difference between the two is that one is used to create a new object, while the other is used to assign an existing object.

The copy constructor and copy assignment operator have these signatures:
```cpp
Character(const Character& other);
Character& operator=(const Character& other);
```

If you do not define a copy constructor or copy assignment operator, C++ will provide a default implementation for you. This implementation will simply copy each member of the object one by one.

If one of your members is a pointer, this default implementation will copy the pointer, not the object it points to. In other words, both objects will point to the same memory location. This is known as a **shallow copy**. This can be problematic if one of your objects will deallocate the memory it points to. The other object will be left with a dangling pointer.
```cpp
class Character {
    char* name;
};
```

To fix this, you need to define your own copy constructor and copy assignment operator. This is known as a **deep copy**.
```cpp
Character(const Character& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}
Character& operator=(const Character& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    return *this;
}
```

Notice how the copy assignment operator has to return `*this`.

On the rare occasion that you want to prevent copying of your object, you can delete the copy constructor and copy assignment operator:
```cpp
class Character {
    Character(const Character& other) = delete;
    Character& operator=(const Character& other) = delete;
};
```

You can also do this with the default constructor and destructor.

There is another special set of member functions called **move constructors** and **move assignment operators**. These are used to transfer ownership of resources from one object to another. We won't cover them in this lesson.

# Destructors

A **destructor** is a special member function that is called when an object goes out of scope (if allocated on the stack) or is explicitly deleted (if allocated on the heap). It is used to clean up resources that the object has acquired during its lifetime. Like the constructor, it has no return type. It also does not take any arguments.
```cpp
class Character {
    char* name;
public:
    Character(const char* n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    /* copy constructor and copy assignment operator here */
    ~Character() {
        delete[] name;
    }
};
```

A common rule of thumb is that for the copy constructor, copy assignment operator, and destructor, if you need to define one, you probably need to define all three.

If you don't define a destructor, C++ will provide a default implementation for you. This implementation will not delete any resources that the object has acquired, which can lead to memory leaks.

# Inheritance

Let's say you want to create a new class that is similar to an existing class, but with some additional features. You can use **inheritance** to achieve this.
```cpp
class Player : public Character {
    int score;
public:
    Player(int h, int p, int s) : Character(h, p), score(s) {}
};
```

Here, we write `Player : public Character`. This means that `Player` inherits from `Character`. This allows `Player` to access all of `Character`'s members and member functions. We can also add new members and member functions to `Player` like `score`.

We interpret public inheritance as an "is-a" relationship. In this case, a *`Player` is a `Character`*.
There are different types of inheritance in C++: **public**, **protected**, and **private**. You probably won't need to use the latter two in this course, so we will focus on public inheritance.

If the members of `Character` are private, `Player` will not be able to access them. If we want `Player` to access them, but maintain some level of encapsulation, we can use the `protected:` access specifier:
```cpp
class Character {
protected:
    int health;
    int power;
};
```

This makes it so that only `Character` and its derived classes can access these members.

Inheritance allows us to create new classes while reusing existing code. This is a key feature of OOP. Inheritance also allows for **polymorphism**.

Suppose we want to change the behavior of the `take_damage` function for a `Player`. We can override the function in the `Player` class:
```cpp
class Player : public Character {
    int score;
public:
    Player(int h, int p, int s) : Character(h, p), score(s) {}
    void take_damage(int damage) override {
        health -= damage / 2;
    }
};
```

Now, when we call `take_damage` on a `Player`, it will use the `Player` version of the function, not the `Character` version.

In C++, pointers of a base class to point to objects of a derived class. In our case, we can make a `Character*` point to a `Player` object. After all, a `Player` is a `Character`.
```cpp
Character* player = new Player(100, 10, 0);
```

This has a few caveats.
First, we cannot access `score` through `player` because C++ does not know if `score` exists in this kind of character. If we're careful, we can cast `player` to a `Player*` to access `score`.
```cpp
Player* player = dynamic_cast<Player*>(character);
if (player) {
    std::cout << player->score << std::endl;
}
```

Dynamic casting is a way to safely cast a pointer of a base class to a pointer of a derived class. If the cast fails, `dynamic_cast` will return `nullptr`.

Second, if we try to call `take_damage` on `player`, it will call the `Character` version of the function. To fix this, we need to make the function `virtual` in the base class:
```cpp
class Character {
public:
    virtual void take_damage(int damage);
};
```

Now, when we call `take_damage` on a `Character*`, it will call the correct version of the function.
```cpp
Character* player = new Player(100, 10, 0);
player->take_damage(10); // Calls Player::take_damage
```

Third, when we delete a `Character*`, only the `Character` destructor will be called. This is bad since `Player` has its own resources to clean up. To fix this, we need to make the destructor `virtual` in the base class:
```cpp
class Character {
public:
    virtual ~Character();
};
```

Polymorphism is tricky, but it can be a powerful tool when used correctly. We can have a collection of `Character*` pointers that point to different types of characters and call the correct functions on them.
```cpp
std::vector<Character*> characters;
characters.push_back(new Player(100, 10, 0));
characters.push_back(new Character(100, 10));
for (Character* character : characters) {
    character->take_damage(10);
}
```

# Abstract Classes
