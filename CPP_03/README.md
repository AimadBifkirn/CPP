# CPP Module 03 - Inheritance

## 📚 Module Overview

Module 03 introduces **inheritance**, one of the pillars of object-oriented programming. You'll learn how to create class hierarchies, reuse code through inheritance, and understand the relationship between base and derived classes.

### What You'll Learn
- Class inheritance (base and derived classes)
- Access specifiers: public, protected, private
- Constructor and destructor chaining
- Function overriding
- Method name conflicts and resolution
- Code reuse through inheritance
- The "is-a" relationship

---

## 🎯 Key Concepts Explained

### 1. What is Inheritance?

Inheritance allows a class (derived/child) to inherit properties and behaviors from another class (base/parent).

```cpp
class ClapTrap {          // Base class
protected:
    std::string name;
    int hitPoints;
    
public:
    void attack(std::string target);
};

class ScavTrap : public ClapTrap {  // Derived class
    // Inherits name, hitPoints, and attack()
public:
    void guardGate();     // New function specific to ScavTrap
};
```

**Benefits**:
- Code reuse (DRY - Don't Repeat Yourself)
- Logical hierarchy
- Easier maintenance
- Polymorphism foundation (CPP_04)

### 2. Access Specifiers in Inheritance

```
┌──────────────────────────────────────────────────────────┐
│                     Base Class Access                    │
├─────────────┬──────────────┬──────────────┬──────────────┤
│  Specifier  │   public     │  protected   │   private    │
├─────────────┼──────────────┼──────────────┼──────────────┤
│ public      │   public     │  protected   │  inaccessible│
│ inheritance │              │              │              │
├─────────────┼──────────────┼──────────────┼──────────────┤
│ protected   │   protected  │  protected   │  inaccessible│
│ inheritance │              │              │              │
├─────────────┼──────────────┼──────────────┼──────────────┤
│ private     │   private    │  private     │  inaccessible│
│ inheritance │              │              │              │
└─────────────┴──────────────┴──────────────┴──────────────┘
```

**Most common**: `public` inheritance (maintains access levels)

**Access Levels Explained**:
- **private**: Only accessible within the class
- **protected**: Accessible within the class AND derived classes
- **public**: Accessible everywhere

```cpp
class Base {
private:
    int privateVar;      // Only Base can access
protected:
    int protectedVar;    // Base and derived classes can access
public:
    int publicVar;       // Everyone can access
};

class Derived : public Base {
public:
    void test() {
        // privateVar = 10;    // ERROR - can't access private
        protectedVar = 10;     // OK - can access protected
        publicVar = 10;        // OK - can access public
    }
};
```

### 3. Constructor and Destructor Chaining

When creating or destroying derived objects, constructors and destructors are called in a specific order:

**Construction order** (top to bottom):
1. Base class constructor
2. Derived class constructor

**Destruction order** (bottom to top):
1. Derived class destructor
2. Base class destructor

```cpp
class Base {
public:
    Base() { std::cout << "Base constructor" << std::endl; }
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived constructor" << std::endl; }
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
};

int main() {
    Derived d;
    // Output:
    // Base constructor
    // Derived constructor
    // Derived destructor
    // Base destructor
}
```

### 4. Calling Base Class Constructors

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

### 5. Function Overriding

Derived classes can replace (override) base class functions:

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
        std::cout << "ScavTrap attacks differently!" << std::endl;
    }
};
```

To call the base class version from derived:
```cpp
void ScavTrap::attack(std::string target) {
    ClapTrap::attack(target);  // Call base version
    // Add ScavTrap-specific behavior
}
```

---

## 💻 Exercise Breakdown

### Exercise 00: Aaaaand... OPEN!
**Files**: `ClapTrap.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Creating a base class
- Member variables and methods
- Encapsulation with private/public
- Basic game-like attributes

#### Concept
Create a `ClapTrap` robot class with attributes and actions.

#### Implementation

```cpp
class ClapTrap {
private:
    std::string name;
    unsigned int hitPoints;      // Health (10 at start)
    unsigned int energyPoints;   // Energy (10 at start)
    unsigned int attackDamage;   // Damage (0 at start)
    
public:
    ClapTrap();
    ClapTrap(std::string name);
    ClapTrap(const ClapTrap& other);
    ClapTrap& operator=(const ClapTrap& other);
    ~ClapTrap();
    
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};
```

#### Key Implementations

**Constructor**:
```cpp
ClapTrap::ClapTrap(std::string name) 
    : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap " << name << " constructed!" << std::endl;
}
```

**Attack Method**:
```cpp
void ClapTrap::attack(const std::string& target) {
    if (energyPoints == 0 || hitPoints == 0) {
        std::cout << "ClapTrap " << name << " cannot attack!" << std::endl;
        return;
    }
    
    energyPoints--;
    std::cout << "ClapTrap " << name << " attacks " << target 
              << ", causing " << attackDamage << " points of damage!" 
              << std::endl;
}
```

**Take Damage Method**:
```cpp
void ClapTrap::takeDamage(unsigned int amount) {
    if (hitPoints == 0) {
        std::cout << "ClapTrap " << name << " is already dead!" << std::endl;
        return;
    }
    
    if (amount >= hitPoints) {
        hitPoints = 0;
    } else {
        hitPoints -= amount;
    }
    
    std::cout << "ClapTrap " << name << " takes " << amount 
              << " damage! HP: " << hitPoints << std::endl;
}
```

**Be Repaired Method**:
```cpp
void ClapTrap::beRepaired(unsigned int amount) {
    if (energyPoints == 0 || hitPoints == 0) {
        std::cout << "ClapTrap " << name << " cannot repair!" << std::endl;
        return;
    }
    
    energyPoints--;
    hitPoints += amount;
    
    std::cout << "ClapTrap " << name << " repairs " << amount 
              << " HP! Current HP: " << hitPoints << std::endl;
}
```

#### Example Usage
```cpp
ClapTrap clap("CT-001");
clap.attack("Enemy");
clap.takeDamage(5);
clap.beRepaired(3);
```

#### Output
```
ClapTrap CT-001 constructed!
ClapTrap CT-001 attacks Enemy, causing 0 points of damage!
ClapTrap CT-001 takes 5 damage! HP: 5
ClapTrap CT-001 repairs 3 HP! Current HP: 8
ClapTrap CT-001 destructed!
```

#### Key Takeaways
- Check resource availability before actions (energy, HP)
- Unsigned integers can't go negative (use checks)
- Provide meaningful output for game states
- Initialize all attributes properly

#### Common Mistakes
1. Not checking if energy/HP is 0 before actions
2. Integer underflow with unsigned types
3. Not updating resources after actions
4. Inconsistent messaging

---

### Exercise 01: Serena, my love!
**Files**: `ClapTrap.{cpp,hpp}`, `ScavTrap.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Creating a derived class
- Public inheritance
- Constructor chaining
- Function overriding
- Adding new functionality to derived class

#### Concept
Create `ScavTrap` class that inherits from `ClapTrap` with:
- Different initial values (100 HP, 50 Energy, 20 Damage)
- Different attack message
- New special ability: `guardGate()`

#### Implementation

**Header (ScavTrap.hpp)**:
```cpp
#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
    ScavTrap();
    ScavTrap(std::string name);
    ScavTrap(const ScavTrap& other);
    ScavTrap& operator=(const ScavTrap& other);
    ~ScavTrap();
    
    void attack(const std::string& target);  // Override
    void guardGate();                         // New function
};

#endif
```

**Implementation (ScavTrap.cpp)**:
```cpp
#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    hitPoints = 100;      // Override ClapTrap's values
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap " << name << " constructed!" << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << name << " destructed!" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (energyPoints == 0 || hitPoints == 0) {
        std::cout << "ScavTrap " << name << " cannot attack!" << std::endl;
        return;
    }
    
    energyPoints--;
    std::cout << "ScavTrap " << name << " fiercely attacks " << target 
              << ", causing " << attackDamage << " points of damage!" 
              << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name 
              << " is now in Gate keeper mode!" << std::endl;
}
```

#### Why Protected Members?

**ClapTrap.hpp must use protected**:
```cpp
class ClapTrap {
protected:  // Changed from private!
    std::string name;
    unsigned int hitPoints;
    unsigned int energyPoints;
    unsigned int attackDamage;
    
public:
    // ...
};
```

**Reason**: ScavTrap needs access to these members!

#### Constructor Chaining in Action
```cpp
ScavTrap scav("ST-001");
// 1. ClapTrap("ST-001") constructor called
// 2. ScavTrap constructor body executes
//    - Overrides hitPoints, energyPoints, attackDamage
```

#### Example Usage
```cpp
ClapTrap clap("CL-4P-TP");
ScavTrap scav("SC4V-TP");

clap.attack("Bandit");  // ClapTrap version
scav.attack("Bandit");  // ScavTrap version (overridden)

scav.guardGate();       // ScavTrap-specific function
scav.takeDamage(30);    // Inherited from ClapTrap
scav.beRepaired(20);    // Inherited from ClapTrap
```

#### Expected Output
```
ClapTrap CL-4P-TP constructed!
ClapTrap SC4V-TP constructed!
ScavTrap SC4V-TP constructed!
ClapTrap CL-4P-TP attacks Bandit, causing 0 points of damage!
ScavTrap SC4V-TP fiercely attacks Bandit, causing 20 points of damage!
ScavTrap SC4V-TP is now in Gate keeper mode!
ScavTrap SC4V-TP takes 30 damage! HP: 70
ScavTrap SC4V-TP repairs 20 HP! Current HP: 90
ScavTrap SC4V-TP destructed!
ClapTrap SC4V-TP destructed!
ClapTrap CL-4P-TP destructed!
```

#### Key Observations
1. Base constructor called before derived constructor
2. Derived destructor called before base destructor
3. Derived class can override base methods
4. Derived class can add new methods

#### Key Takeaways
- Use `public` inheritance for "is-a" relationships
- Call base constructor in initializer list
- Override values in derived constructor body
- Function overriding changes behavior
- Destruction happens in reverse order of construction

#### Common Mistakes
1. Using `private` instead of `protected` in base class
2. Not calling base constructor
3. Forgetting to override initial values
4. Not implementing copy constructor/assignment for derived class
5. Calling base destructor manually (automatic!)

---

### Exercise 02: Repetitive work
**Files**: `ClapTrap.{cpp,hpp}`, `ScavTrap.{cpp,hpp}`, `FragTrap.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Multiple derived classes from same base
- Code reuse through inheritance
- Different specializations of same concept

#### Concept
Create another derived class `FragTrap` with:
- Different stats (100 HP, 100 Energy, 30 Damage)
- Different attack message
- Special ability: `highFivesGuys()`

#### Implementation

**FragTrap.hpp**:
```cpp
#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
    FragTrap();
    FragTrap(std::string name);
    FragTrap(const FragTrap& other);
    FragTrap& operator=(const FragTrap& other);
    ~FragTrap();
    
    void attack(const std::string& target);  // Override
    void highFivesGuys();                    // New function
};

#endif
```

**FragTrap.cpp**:
```cpp
#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap " << name << " constructed!" << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap " << name << " destructed!" << std::endl;
}

void FragTrap::attack(const std::string& target) {
    if (energyPoints == 0 || hitPoints == 0) {
        std::cout << "FragTrap " << name << " cannot attack!" << std::endl;
        return;
    }
    
    energyPoints--;
    std::cout << "FragTrap " << name << " explosively attacks " << target 
              << ", causing " << attackDamage << " points of damage!" 
              << std::endl;
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << name 
              << " requests high fives! ✋" << std::endl;
}
```

#### Class Hierarchy Diagram

```
        ClapTrap (Base)
           /    \
          /      \
    ScavTrap   FragTrap
   (Derived)  (Derived)
```

**Comparison Table**:
| Feature | ClapTrap | ScavTrap | FragTrap |
|---------|----------|----------|----------|
| HP | 10 | 100 | 100 |
| Energy | 10 | 50 | 100 |
| Damage | 0 | 20 | 30 |
| Special | - | guardGate() | highFivesGuys() |
| Attack Msg | "attacks" | "fiercely attacks" | "explosively attacks" |

#### Example Usage
```cpp
ClapTrap clap("Clap");
ScavTrap scav("Scav");
FragTrap frag("Frag");

clap.attack("Enemy");  // ClapTrap attack
scav.attack("Enemy");  // ScavTrap attack
frag.attack("Enemy");  // FragTrap attack

scav.guardGate();      // ScavTrap only
frag.highFivesGuys();  // FragTrap only
```

#### Key Takeaways
- Multiple classes can inherit from the same base
- Each derived class can specialize differently
- Inheritance promotes code reuse
- Each derived class maintains its own state

---

## 🎓 Best Practices

### 1. When to Use Inheritance

**Good use cases** (is-a relationship):
```cpp
class Animal { };
class Dog : public Animal { };  // Dog IS-AN Animal ✓

class Vehicle { };
class Car : public Vehicle { };  // Car IS-A Vehicle ✓
```

**Bad use cases** (has-a relationship):
```cpp
class Engine { };
class Car : public Engine { };  // Car IS-AN Engine? ✗

// Better:
class Car {
private:
    Engine engine;  // Car HAS-AN Engine ✓
};
```

### 2. Constructor Initialization Lists

**Always call base constructor explicitly**:
```cpp
// Good
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    hitPoints = 100;
}

// Bad (uses default constructor)
ScavTrap::ScavTrap(std::string name) {
    ClapTrap(name);  // This creates a temporary object!
}
```

### 3. Protected vs. Private

**Use protected when**:
- Derived classes need access
- You want to share implementation details

**Use private when**:
- Implementation detail that shouldn't be inherited
- You want strict encapsulation

```cpp
class Base {
private:
    int secretImplementation;  // Never expose
protected:
    int sharedWithChildren;    // OK for derived classes
public:
    int publicInterface;       // Everyone can use
};
```

### 4. Virtual Destructors (Preview)

In CPP_04, you'll learn about virtual functions. For now, know that:
```cpp
class Base {
public:
    virtual ~Base() {}  // Virtual destructor for polymorphism
};
```

This ensures proper cleanup in inheritance hierarchies.

---

## 🔗 Building on CPP_02

CPP_02 taught you to create robust single classes. CPP_03 extends this with:
- ✅ Class hierarchies through inheritance
- ✅ Code reuse and specialization
- ✅ Understanding is-a relationships
- ✅ Constructor/destructor chaining

---

## 🚀 Preparing for CPP_04

You've learned basic inheritance. Next comes:
- **Virtual functions**: Dynamic dispatch
- **Abstract classes**: Pure virtual functions
- **Interfaces**: Abstract base classes
- **Polymorphism**: One interface, multiple implementations
- **Virtual destructors**: Proper cleanup in hierarchies

**Preview**:
```cpp
class Animal {
public:
    virtual void makeSound() = 0;  // Pure virtual
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void makeSound() { std::cout << "Woof!"; }
};

Animal* animal = new Dog();
animal->makeSound();  // Calls Dog::makeSound()!
delete animal;
```

---

## 🐛 Common Pitfalls

1. **Private members in base class**:
   ```cpp
   class Base {
   private:
       int value;  // Derived classes can't access!
   };
   
   // Use protected instead:
   protected:
       int value;  // Derived classes can access
   ```

2. **Not calling base constructor**:
   ```cpp
   // Wrong
   Derived::Derived() {
       // Base default constructor called automatically
       // but you might want parameterized one!
   }
   
   // Right
   Derived::Derived() : Base(params) {
       // Calls specific base constructor
   }
   ```

3. **Confusion about destruction order**:
   ```
   Construction: Base → Derived
   Destruction:  Derived → Base
   ```

4. **Trying to override non-virtual functions**:
   ```cpp
   class Base {
   public:
       void func() { }  // Not virtual
   };
   
   class Derived : public Base {
   public:
       void func() { }  // Hides, doesn't override!
   };
   
   Base* b = new Derived();
   b->func();  // Calls Base::func(), not Derived::func()!
   ```

5. **Multiple inheritance issues** (not in this module):
   - Diamond problem
   - Ambiguity
   - Complexity

---

## 🎯 Summary

Module 03 covers inheritance fundamentals:
- ✅ Base and derived classes
- ✅ Public, protected, private access
- ✅ Constructor and destructor chaining
- ✅ Function overriding
- ✅ Code reuse through inheritance
- ✅ Multiple derived classes from one base

**Key Concepts**:
- Inheritance models "is-a" relationships
- Derived classes extend base functionality
- Protected members are shared with derived classes
- Construction flows base → derived
- Destruction flows derived → base

**Remember**:
- Use inheritance for "is-a" relationships
- Use composition for "has-a" relationships
- Always call base constructors
- Protected members enable sharing with derived classes

**You now understand class hierarchies and code reuse! Next: polymorphism!** 🎉
