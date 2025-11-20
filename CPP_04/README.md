# CPP Module 04 - Polymorphism, Abstract Classes, and Interfaces

## 🎯 New Concepts in This Module

### Virtual Functions
Enable **polymorphism** - calling the right function based on actual object type:

```cpp
class Animal {
public:
    virtual void makeSound() {  // Virtual keyword is key!
        std::cout << "Generic animal sound" << std::endl;
    }
    virtual ~Animal() {}  // Virtual destructor - CRITICAL!
};

class Dog : public Animal {
public:
    void makeSound() {  // Overrides Animal::makeSound()
        std::cout << "Woof!" << std::endl;
    }
};

// Polymorphism in action:
Animal* animal = new Dog();
animal->makeSound();  // Calls Dog::makeSound(), not Animal::makeSound() ✓
delete animal;        // Calls Dog destructor, then Animal destructor ✓
```

**Without `virtual`:** Calls Animal::makeSound() (wrong!)
**With `virtual`:** Calls Dog::makeSound() (correct!)

### Pure Virtual Functions and Abstract Classes
Force derived classes to implement certain methods:

```cpp
class Animal {
public:
    virtual void makeSound() = 0;  // Pure virtual function (= 0)
    virtual ~Animal() {}
};

// Animal is now abstract - cannot instantiate
// Animal a;  // ERROR - cannot create generic Animal

class Dog : public Animal {
public:
    void makeSound() {  // MUST implement this
        std::cout << "Woof!" << std::endl;
    }
};

Dog d;  // OK - Dog provides implementation
```

**Abstract class**: Has at least one pure virtual function
- Cannot instantiate directly
- Forces derived classes to implement the function
- Defines interface contracts

### Virtual Destructors - CRITICAL!
Always use virtual destructors in polymorphic base classes:

```cpp
class Base {
public:
    virtual ~Base() {  // MUST be virtual!
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() : data(new int[100]) {}
    ~Derived() {
        delete[] data;
        std::cout << "Derived destructor" << std::endl;
    }
};

Base* obj = new Derived();
delete obj;
// With virtual: Calls Derived destructor, then Base destructor ✓
// Without virtual: Only calls Base destructor - MEMORY LEAK! ✗
```

### Interfaces
Abstract class with only pure virtual functions:

```cpp
class ICharacter {  // 'I' prefix for interface
public:
    virtual ~ICharacter() {}
    virtual std::string const& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};

class Character : public ICharacter {
    // MUST implement all pure virtual functions
public:
    std::string const& getName() const { return name; }
    void equip(AMateria* m) { /* implementation */ }
    void unequip(int idx) { /* implementation */ }
    void use(int idx, ICharacter& target) { /* implementation */ }
};
```

### Deep Copy with Polymorphic Objects
When copying objects with pointers:

```cpp
class Animal {
public:
    virtual Animal* clone() const = 0;  // Virtual copy
};

class Dog : public Animal {
private:
    Brain* brain;  // Dynamically allocated
    
public:
    Dog(const Dog& other) {
        brain = new Brain(*other.brain);  // Deep copy!
    }
    
    Dog& operator=(const Dog& other) {
        if (this != &other) {
            delete brain;  // Delete old
            brain = new Brain(*other.brain);  // Deep copy new
        }
        return *this;
    }
    
    ~Dog() {
        delete brain;  // Clean up
    }
    
    Animal* clone() const {
        return new Dog(*this);
    }
};
```

**Shallow copy** (wrong): Both objects share same pointer → double delete!
**Deep copy** (correct): Each object has its own copy → safe!

### The Prototype Pattern
Clone objects without knowing their exact type:

```cpp
class AMateria {
public:
    virtual AMateria* clone() const = 0;  // Pure virtual clone
};

class Ice : public AMateria {
public:
    AMateria* clone() const {
        return new Ice(*this);  // Return copy of self
    }
};

// Usage:
AMateria* original = new Ice();
AMateria* copy = original->clone();  // Creates Ice even though pointer is AMateria*
```

## 💡 What You'll Build
- **ex00**: Animal hierarchy with virtual functions
- **ex01**: Deep copy with Brain class
- **ex02**: Make Animal abstract
- **ex03**: Materia system with interfaces

## 📋 Quick Reference

### Virtual Function Syntax
```cpp
class Base {
public:
    virtual void func();           // Virtual function
    virtual void pure() = 0;       // Pure virtual (abstract)
    virtual ~Base();               // Virtual destructor (ALWAYS!)
};
```

### Polymorphism in Action
```cpp
Base* ptr = new Derived();
ptr->virtualFunc();  // Calls Derived::virtualFunc()
delete ptr;          // Calls Derived destructor if virtual
```

### Deep Copy Template
```cpp
class MyClass {
    Resource* resource;
public:
    // Copy constructor
    MyClass(const MyClass& other) {
        resource = new Resource(*other.resource);  // Deep copy
    }
    
    // Assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete resource;  // Delete old
            resource = new Resource(*other.resource);  // Deep copy
        }
        return *this;
    }
    
    // Destructor
    ~MyClass() {
        delete resource;
    }
};
```

### Common Mistakes to Avoid
- Forgetting `virtual` on destructor (memory leaks!)
- Not using `virtual` for functions you want to override
- Shallow copy of pointers (double delete!)
- Slicing (copying Derived object to Base variable)
- Not implementing all pure virtual functions

### Slicing Example
```cpp
Derived d;
Base b = d;  // SLICING! Only Base part is copied
b.virtualFunc();  // Calls Base version, even if virtual
```

Always use pointers or references for polymorphism!

---

**Previous Module**: CPP_03 covered basic inheritance  
**Next Module**: CPP_05 covers exceptions
