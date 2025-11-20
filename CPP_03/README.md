# CPP Module 03 - Inheritance

## 🎯 New Concepts in This Module

### Inheritance Basics
Create new classes based on existing ones, inheriting their members:

```cpp
class ClapTrap {              // Base class (parent)
protected:
    std::string name;
    int hitPoints;
    
public:
    void attack(std::string target);
};

class ScavTrap : public ClapTrap {  // Derived class (child)
    // Inherits name, hitPoints, and attack()
public:
    void guardGate();  // New function specific to ScavTrap
};
```

**Benefits:**
- Code reuse (DRY principle)
- Logical class hierarchies
- Easier maintenance

### Access Specifiers: public, protected, private

```cpp
class Base {
private:
    int privateVar;      // Only Base can access
protected:
    int protectedVar;    // Base and derived classes can access
public:
    int publicVar;       // Anyone can access
};

class Derived : public Base {
public:
    void test() {
        // privateVar = 10;    // ERROR - can't access private from base
        protectedVar = 10;     // OK - can access protected
        publicVar = 10;        // OK - can access public
    }
};
```

**protected** is the key new access level:
- Like `private`, but accessible to derived classes
- Use for members that derived classes need but others shouldn't access

### Public Inheritance
The most common type:

```cpp
class ScavTrap : public ClapTrap {
    // 'public' maintains access levels of base class
};
```

Means "ScavTrap **is-a** ClapTrap" (is-a relationship).

### Constructor and Destructor Chaining
When creating/destroying derived objects:

**Construction** (base → derived):
```cpp
class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor" << std::endl; }
};

Derived d;
// Output:
// Base constructor
// Derived constructor
```

**Destruction** (derived → base):
```cpp
// When d goes out of scope:
// Derived destructor
// Base destructor
```

**Calling Base Constructor Explicitly:**
```cpp
class ClapTrap {
public:
    ClapTrap(std::string name) : name(name) {}
};

class ScavTrap : public ClapTrap {
public:
    ScavTrap(std::string name) : ClapTrap(name) {
        // Call base constructor with name
        // Then initialize ScavTrap-specific members
    }
};
```

Always call the base constructor in the initializer list!

### Function Overriding
Derived classes can replace base class methods:

```cpp
class ClapTrap {
public:
    void attack(std::string target) {
        std::cout << "ClapTrap attacks!" << std::endl;
    }
};

class ScavTrap : public ClapTrap {
public:
    void attack(std::string target) {
        // Different implementation
        std::cout << "ScavTrap attacks with more power!" << std::endl;
    }
};
```

To call the base version from derived class:
```cpp
void ScavTrap::attack(std::string target) {
    ClapTrap::attack(target);  // Call base implementation
    // Add ScavTrap-specific behavior
}
```

### Multiple Derived Classes
Multiple classes can inherit from the same base:

```
        ClapTrap (Base)
           /    \
          /      \
    ScavTrap   FragTrap
   (Derived)  (Derived)
```

Each derived class specializes the base differently.

## 💡 What You'll Build
- **ex00**: ClapTrap base class
- **ex01**: ScavTrap derived from ClapTrap
- **ex02**: FragTrap also derived from ClapTrap

## 📋 Quick Reference

### Inheritance Syntax
```cpp
class Derived : public Base {
    // Derived inherits from Base
};
```

### Calling Base Constructor
```cpp
Derived::Derived(args) : Base(args) {
    // Initialize derived-specific members
}
```

### Access Levels Summary
```cpp
class Base {
private:   int a;  // Base only
protected: int b;  // Base + derived classes  
public:    int c;  // Everyone
};
```

### Overriding Methods
```cpp
// Base class
virtual void func();  // Can be overridden (CPP_04 covers virtual)

// Derived class
void func();  // Overrides base version

// Call base from derived
Base::func();
```

### When to Use Inheritance
**Good** (is-a relationship):
```cpp
class Dog : public Animal { };  // Dog IS-AN Animal ✓
class Car : public Vehicle { }; // Car IS-A Vehicle ✓
```

**Bad** (has-a relationship):
```cpp
class Car : public Engine { };  // Car IS-AN Engine? ✗

// Better - use composition:
class Car {
    Engine engine;  // Car HAS-AN Engine ✓
};
```

### Common Mistakes to Avoid
- Using `private` instead of `protected` in base class (derived can't access)
- Not calling base constructor (uses default)
- Forgetting to override values in derived constructor
- Manually calling base destructor (automatic!)
- Trying to override without `virtual` (covered in CPP_04)

---

**Previous Module**: CPP_02 covered operator overloading and OCF  
**Next Module**: CPP_04 covers polymorphism with virtual functions
