# CPP Module 04 - Subtype Polymorphism, Abstract Classes, and Interfaces

## 📚 Module Overview

Module 04 introduces **polymorphism**, one of the most powerful concepts in object-oriented programming. You'll learn about virtual functions, abstract classes, interfaces, and how to write flexible, extensible code that works with multiple types through a common interface.

### What You'll Learn
- Virtual functions and dynamic dispatch
- Abstract classes and pure virtual functions
- Interfaces in C++
- Polymorphism and its benefits
- Deep copy with polymorphic objects
- Memory management in inheritance hierarchies
- Virtual destructors and why they matter

---

## 🎯 Key Concepts Explained

### 1. Polymorphism - The Big Picture

**Polymorphism** means "many forms" - the ability to treat objects of different types uniformly through a common interface.

```cpp
// Without polymorphism
Dog dog;
Cat cat;
dog.makeSound();  // Bark
cat.makeSound();  // Meow

// With polymorphism
Animal* animal1 = new Dog();
Animal* animal2 = new Cat();
animal1->makeSound();  // Bark - calls Dog::makeSound()
animal2->makeSound();  // Meow - calls Cat::makeSound()
```

**The magic**: The correct function is called based on the actual object type, not the pointer type!

### 2. Virtual Functions

The `virtual` keyword enables polymorphism:

```cpp
class Animal {
public:
    virtual void makeSound() {  // Virtual function
        std::cout << "Some generic animal sound" << std::endl;
    }
    
    virtual ~Animal() {}  // Virtual destructor (critical!)
};

class Dog : public Animal {
public:
    void makeSound() {  // Overrides Animal::makeSound()
        std::cout << "Woof!" << std::endl;
    }
};
```

**Without virtual**:
```cpp
Animal* animal = new Dog();
animal->makeSound();  // Calls Animal::makeSound() ✗
```

**With virtual**:
```cpp
Animal* animal = new Dog();
animal->makeSound();  // Calls Dog::makeSound() ✓
```

### 3. Pure Virtual Functions and Abstract Classes

A **pure virtual function** has no implementation and must be overridden:

```cpp
class Animal {
public:
    virtual void makeSound() = 0;  // Pure virtual function
    //                       ^^^^
    virtual ~Animal() {}
};

// Animal is now abstract - cannot instantiate
// Animal a;  // ERROR!

class Dog : public Animal {
public:
    void makeSound() {  // Must implement
        std::cout << "Woof!" << std::endl;
    }
};

Dog d;  // OK - Dog provides implementation
```

**Abstract Class**: A class with at least one pure virtual function
- Cannot be instantiated directly
- Forces derived classes to provide implementations
- Defines interface contracts

### 4. Interfaces

In C++, an **interface** is an abstract class with:
- Only pure virtual functions
- No member variables (usually)
- No implementation (usually)

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
    // Must implement all pure virtual functions
};
```

### 5. Virtual Destructors - Critical!

**Always** use virtual destructors in polymorphic base classes:

```cpp
class Base {
public:
    virtual ~Base() {
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

// Without virtual destructor:
Base* obj = new Derived();
delete obj;  // Only calls Base destructor - MEMORY LEAK! ✗

// With virtual destructor:
Base* obj = new Derived();
delete obj;  // Calls Derived destructor, then Base destructor ✓
```

### 6. Deep Copy in Inheritance

When copying polymorphic objects, you need deep copying:

```cpp
class Animal {
public:
    virtual Animal* clone() const = 0;  // Virtual copy
};

class Dog : public Animal {
private:
    Brain* brain;
    
public:
    Dog(const Dog& other) {
        brain = new Brain(*other.brain);  // Deep copy
    }
    
    Animal* clone() const {
        return new Dog(*this);
    }
};
```

---

## 💻 Exercise Breakdown

### Exercise 00: Polymorphism
**Files**: `Animal.{cpp,hpp}`, `Dog.{cpp,hpp}`, `Cat.{cpp,hpp}`, `WrongAnimal.{cpp,hpp}`, `WrongCat.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Virtual functions
- Polymorphism basics
- Virtual destructors
- The difference between virtual and non-virtual

#### Concept
Create an Animal hierarchy demonstrating correct (virtual) and incorrect (non-virtual) polymorphism.

#### My Implementation

**Animal Base Class** (`Animal.hpp`):
```cpp
class Animal
{
	protected:
		std::string type;
	public:
		Animal ();
		Animal (const Animal &other);
		Animal &operator= (const Animal &obj);
		virtual ~Animal ();  // Virtual destructor - CRITICAL!

		const std::string &getType(void) const;
		virtual void makeSound() const;  // Virtual function - enables polymorphism
};
```

**Animal Implementation** (`Animal.cpp`):
```cpp
Animal::Animal () : type("Animal")
{
	std::cout << "Animal: Default constructor called" << std::endl;
}

Animal::~Animal ()
{
	std::cout << "Animal: Destructor called" << std::endl;
}

void Animal::makeSound() const
{
	std::cout << "Animal sound!!" << std::endl;
}

const std::string &Animal::getType(void) const
{
	return (type);
}
```

**Cat Derived Class** (`Cat.hpp`):
```cpp
class Cat : public Animal
{
	public:
		Cat ();
		Cat (const Cat &other);
		Cat &operator= (const Cat &obj);
		~Cat ();

		void makeSound() const;  // Override virtual function
};
```

**Cat Implementation** (`Cat.cpp`):
```cpp
Cat::Cat ()
{
	this->type = "Cat";
	std::cout << "Cat: Default constructor called" << std::endl;
}

Cat::~Cat ()
{
	std::cout << "Cat: Destructor called" << std::endl;
}

void Cat::makeSound() const  // Overrides Animal::makeSound()
{
	std::cout << "Meaw Meaw!!" << std::endl;
}
```

#### How Polymorphism Works

**1. Virtual Functions Enable Runtime Polymorphism:**

```cpp
const Animal* animal = new Cat();
animal->makeSound();  // Calls Cat::makeSound(), not Animal::makeSound()
delete animal;
```

Output:
```
Animal: Default constructor called
Cat: Default constructor called
Meaw Meaw!!
Cat: Destructor called
Animal: Destructor called
```

**Why?** The `virtual` keyword makes the function polymorphic. At runtime, C++ looks at the actual object type (Cat), not the pointer type (Animal*).

**2. Virtual Destructor is CRITICAL:**

```cpp
virtual ~Animal ();  // In base class
```

Without `virtual`:
- `delete animal` would only call `Animal::~Animal()`
- `Cat::~Cat()` would never be called
- Memory leak if Cat has dynamic memory!

With `virtual`:
- `delete animal` calls `Cat::~Cat()` first
- Then calls `Animal::~Animal()`
- Proper cleanup guaranteed

**3. WrongAnimal Example (non-virtual):**

To demonstrate the importance of `virtual`, there's also a `WrongAnimal` class without virtual functions:

```cpp
class WrongAnimal {
public:
	void makeSound() const;  // NOT virtual
	~WrongAnimal();          // NOT virtual
};

WrongAnimal* wrong = new WrongCat();
wrong->makeSound();  // Calls WrongAnimal::makeSound(), NOT WrongCat::makeSound()!
```

This is **static binding** (compile-time) vs **dynamic binding** (runtime) with virtual.
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();
    
    void makeSound() const;  // Override
};

#endif
```

**Cat.hpp**:
```cpp
#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    ~Cat();
    
    void makeSound() const;  // Override
};

#endif
```

**Implementations**:
```cpp
// Animal.cpp
Animal::Animal() : type("Animal") {
    std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Generic animal sound" << std::endl;
}

// Dog.cpp
Dog::Dog() {
    type = "Dog";
    std::cout << "Dog constructor called" << std::endl;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}

// Cat.cpp
Cat::Cat() {
    type = "Cat";
    std::cout << "Cat constructor called" << std::endl;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meow! Meow!" << std::endl;
}
```

**WrongAnimal** (demonstrates incorrect implementation):
```cpp
class WrongAnimal {
protected:
    std::string type;
    
public:
    WrongAnimal();
    WrongAnimal(const WrongAnimal& other);
    WrongAnimal& operator=(const WrongAnimal& other);
    ~WrongAnimal();  // NOT virtual!
    
    const std::string& getType() const;
    void makeSound() const;  // NOT virtual!
};

class WrongCat : public WrongAnimal {
public:
    WrongCat();
    ~WrongCat();
    void makeSound() const;
};
```

#### Example Usage
```cpp
int main() {
    // Correct polymorphism
    const Animal* meta = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();
    
    std::cout << dog->getType() << std::endl;  // "Dog"
    std::cout << cat->getType() << std::endl;  // "Cat"
    
    dog->makeSound();  // "Woof! Woof!" ✓
    cat->makeSound();  // "Meow! Meow!" ✓
    meta->makeSound(); // "Generic animal sound"
    
    delete meta;
    delete dog;  // Calls Dog destructor, then Animal destructor ✓
    delete cat;
    
    // Wrong polymorphism
    const WrongAnimal* wrongCat = new WrongCat();
    wrongCat->makeSound();  // "Generic animal sound" ✗
    // Calls WrongAnimal::makeSound(), not WrongCat::makeSound()!
    
    delete wrongCat;  // Only calls WrongAnimal destructor ✗
    
    return 0;
}
```

#### Expected Output
```
Animal constructor called
Dog constructor called
Animal constructor called
Cat constructor called
Dog
Cat
Woof! Woof!
Meow! Meow!
Generic animal sound
Animal destructor called
Dog destructor called
Animal destructor called
Cat destructor called
Animal destructor called
WrongAnimal constructor called
WrongCat constructor called
Generic animal sound    <-- Wrong! Should be "Meow!"
WrongAnimal destructor called    <-- WrongCat destructor not called!
```

#### Key Observations
1. **Virtual functions** enable correct polymorphic behavior
2. **Virtual destructors** ensure proper cleanup
3. Without `virtual`, static binding occurs (compile-time)
4. With `virtual`, dynamic binding occurs (runtime)

#### Key Takeaways
- Always use `virtual` for functions you want to override
- Always use virtual destructors in polymorphic base classes
- The type of the pointer doesn't matter with virtual functions
- WrongAnimal demonstrates why virtual is necessary

---

### Exercise 01: I don't want to set the world on fire
**Files**: `Animal.{cpp,hpp}`, `Dog.{cpp,hpp}`, `Cat.{cpp,hpp}`, `Brain.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Deep copy in polymorphic classes
- Managing dynamically allocated members
- Copy constructor and assignment operator with pointers
- Memory leaks prevention

#### Concept
Add a `Brain` class to Dog and Cat, demonstrating deep copy.

#### Implementation

**Brain.hpp**:
```cpp
#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain {
private:
    std::string ideas[100];  // 100 ideas
    
public:
    Brain();
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    ~Brain();
    
    void setIdea(int index, const std::string& idea);
    const std::string& getIdea(int index) const;
};

#endif
```

**Brain.cpp**:
```cpp
Brain::Brain() {
    std::cout << "Brain constructor called" << std::endl;
    for (int i = 0; i < 100; i++) {
        ideas[i] = "";
    }
}

Brain::Brain(const Brain& other) {
    std::cout << "Brain copy constructor called" << std::endl;
    for (int i = 0; i < 100; i++) {
        ideas[i] = other.ideas[i];  // Deep copy
    }
}

Brain& Brain::operator=(const Brain& other) {
    std::cout << "Brain assignment operator called" << std::endl;
    if (this != &other) {
        for (int i = 0; i < 100; i++) {
            ideas[i] = other.ideas[i];  // Deep copy
        }
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}
```

**Updated Dog.hpp**:
```cpp
class Dog : public Animal {
private:
    Brain* brain;  // Dynamically allocated
    
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();
    
    void makeSound() const;
    Brain* getBrain() const;
};
```

**Updated Dog.cpp**:
```cpp
Dog::Dog() {
    type = "Dog";
    brain = new Brain();  // Allocate brain
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    brain = new Brain(*other.brain);  // Deep copy!
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);  // Call base assignment
        delete brain;               // Delete old brain
        brain = new Brain(*other.brain);  // Deep copy
    }
    return *this;
}

Dog::~Dog() {
    delete brain;  // Free brain
    std::cout << "Dog destructor called" << std::endl;
}
```

#### Why Deep Copy?

**Shallow copy (wrong)**:
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    brain = other.brain;  // Both dogs share same brain! ✗
}
```

**Problem**:
```
Dog1's brain: [0x1000]
Dog2's brain: [0x1000]  // Same address!

Delete Dog1 → frees 0x1000
Delete Dog2 → tries to free 0x1000 again → CRASH!
```

**Deep copy (correct)**:
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    brain = new Brain(*other.brain);  // New brain, same ideas ✓
}
```

**Result**:
```
Dog1's brain: [0x1000]
Dog2's brain: [0x2000]  // Different address, same content!

Delete Dog1 → frees 0x1000
Delete Dog2 → frees 0x2000  // No problem! ✓
```

#### Testing Deep Copy
```cpp
int main() {
    // Create original
    Dog basic;
    {
        Dog tmp = basic;  // Copy constructor
        // tmp destroyed here
    }
    // basic is still valid! ✓
    
    // Test assignment
    Dog dog1;
    Dog dog2;
    dog2 = dog1;  // Assignment operator
    
    // Both should have independent brains
    
    return 0;
}
```

#### Key Takeaways
- Always deep copy dynamically allocated members
- Delete old memory before assigning new in assignment operator
- Call base class copy constructor and assignment operator
- Test that objects remain valid after copying

#### Common Mistakes
1. Shallow copy (copying pointers instead of data)
2. Not deleting old memory in assignment operator (memory leak)
3. Not checking for self-assignment
4. Not calling base class constructors/operators
5. Forgetting to delete in destructor

---

### Exercise 02: Abstract class
**Files**: Same as ex01, but Animal is now abstract

#### What It Teaches
- Abstract classes (cannot instantiate)
- Pure virtual functions
- Enforcing implementation in derived classes

#### Concept
Make Animal abstract so you can't create generic animals, only specific types.

#### Implementation

**Animal.hpp**:
```cpp
class Animal {
protected:
    std::string type;
    
public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();
    
    const std::string& getType() const;
    virtual void makeSound() const = 0;  // Pure virtual!
};
```

**Effect**:
```cpp
Animal* animal = new Animal();  // ERROR! Cannot instantiate abstract class
Animal* dog = new Dog();        // OK - Dog is concrete
Animal* cat = new Cat();        // OK - Cat is concrete
```

#### Why Use Abstract Classes?

1. **Prevent instantiation of incomplete types**:
   - What sound does a generic "Animal" make?
   - Force users to create specific animals

2. **Define interface contracts**:
   - All animals MUST implement makeSound()
   - Compiler enforces this

3. **Better design**:
   - Clearer intent
   - Compile-time checks
   - Self-documenting code

#### Testing
```cpp
int main() {
    // Animal a;  // Compilation error!
    
    Animal* animals[4];
    animals[0] = new Dog();
    animals[1] = new Dog();
    animals[2] = new Cat();
    animals[3] = new Cat();
    
    for (int i = 0; i < 4; i++) {
        animals[i]->makeSound();
        delete animals[i];
    }
    
    return 0;
}
```

---

### Exercise 03: Interface & recap
**Files**: `AMateria.{cpp,hpp}`, `Ice.{cpp,hpp}`, `Cure.{cpp,hpp}`, `ICharacter.{cpp,hpp}`, `Character.{cpp,hpp}`, `IMateriaSource.{cpp,hpp}`, `MateriaSource.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Interface design
- Multiple inheritance from interfaces
- Complex polymorphic system
- The Prototype pattern

#### Concept
Create a materia (spell) system with:
- Abstract materia base class
- Concrete materia types (Ice, Cure)
- Character interface and implementation
- Materia source interface and implementation

#### Class Hierarchy

```
      AMateria (Abstract)
         /    \
        /      \
      Ice    Cure

   ICharacter (Interface)
        |
    Character

IMateriaSource (Interface)
        |
  MateriaSource
```

#### Implementation

**AMateria.hpp** (Abstract base):
```cpp
class ICharacter;  // Forward declaration

class AMateria {
protected:
    std::string type;
    
public:
    AMateria(std::string const& type);
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    virtual ~AMateria();
    
    std::string const& getType() const;
    
    virtual AMateria* clone() const = 0;  // Pure virtual
    virtual void use(ICharacter& target);
};
```

**Ice.hpp** (Concrete materia):
```cpp
class Ice : public AMateria {
public:
    Ice();
    Ice(const Ice& other);
    Ice& operator=(const Ice& other);
    ~Ice();
    
    AMateria* clone() const;  // Returns new Ice
    void use(ICharacter& target);
};
```

**Ice.cpp**:
```cpp
Ice::Ice() : AMateria("ice") {
    std::cout << "Ice constructor" << std::endl;
}

Ice::~Ice() {
    std::cout << "Ice destructor" << std::endl;
}

AMateria* Ice::clone() const {
    return new Ice(*this);  // Prototype pattern
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " 
              << target.getName() << " *" << std::endl;
}
```

**Cure.cpp**:
```cpp
Cure::Cure() : AMateria("cure") {
}

AMateria* Cure::clone() const {
    return new Cure(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " << target.getName() 
              << "'s wounds *" << std::endl;
}
```

**ICharacter.hpp** (Interface):
```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

**Character.hpp** (Implementation):
```cpp
class Character : public ICharacter {
private:
    std::string name;
    AMateria* inventory[4];  // Max 4 materia
    
public:
    Character(std::string const& name);
    Character(const Character& other);
    Character& operator=(const Character& other);
    ~Character();
    
    std::string const& getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};
```

**Character.cpp**:
```cpp
Character::Character(std::string const& name) : name(name) {
    for (int i = 0; i < 4; i++) {
        inventory[i] = NULL;
    }
}

Character::~Character() {
    for (int i = 0; i < 4; i++) {
        if (inventory[i])
            delete inventory[i];
    }
}

void Character::equip(AMateria* m) {
    if (!m) return;
    
    for (int i = 0; i < 4; i++) {
        if (!inventory[i]) {
            inventory[i] = m;
            return;
        }
    }
    // Inventory full, materia not equipped
}

void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4) {
        inventory[idx] = NULL;  // Don't delete! User must manage
    }
}

void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < 4 && inventory[idx]) {
        inventory[idx]->use(target);
    }
}
```

**IMateriaSource.hpp** (Interface):
```cpp
class IMateriaSource {
public:
    virtual ~IMateriaSource() {}
    virtual void learnMateria(AMateria*) = 0;
    virtual AMateria* createMateria(std::string const& type) = 0;
};
```

**MateriaSource.cpp**:
```cpp
class MateriaSource : public IMateriaSource {
private:
    AMateria* templates[4];  // Learned materia templates
    
public:
    MateriaSource();
    ~MateriaSource();
    
    void learnMateria(AMateria* m);
    AMateria* createMateria(std::string const& type);
};

void MateriaSource::learnMateria(AMateria* m) {
    if (!m) return;
    
    for (int i = 0; i < 4; i++) {
        if (!templates[i]) {
            templates[i] = m;
            return;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const& type) {
    for (int i = 0; i < 4; i++) {
        if (templates[i] && templates[i]->getType() == type) {
            return templates[i]->clone();  // Prototype pattern!
        }
    }
    return NULL;
}
```

#### Example Usage
```cpp
int main() {
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    
    ICharacter* me = new Character("me");
    
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    
    ICharacter* bob = new Character("bob");
    
    me->use(0, *bob);  // * shoots an ice bolt at bob *
    me->use(1, *bob);  // * heals bob's wounds *
    
    delete bob;
    delete me;
    delete src;
    
    return 0;
}
```

#### Design Patterns Used

**1. Prototype Pattern**:
```cpp
AMateria* Ice::clone() const {
    return new Ice(*this);  // Create copy of itself
}
```

**2. Factory Pattern**:
```cpp
AMateria* MateriaSource::createMateria(std::string const& type) {
    // Creates materia based on type string
}
```

**3. Interface Segregation**:
- Separate interfaces for Character and MateriaSource
- Each interface has focused responsibility

#### Key Takeaways
- Interfaces define contracts (pure virtual functions)
- Abstract classes can have partial implementation
- Polymorphism enables flexible, extensible systems
- clone() implements Prototype pattern
- Memory management is critical with complex systems

---

## 🎓 Best Practices

### 1. Virtual Function Checklist

```cpp
class Base {
public:
    virtual ~Base() {}               // 1. Virtual destructor (always!)
    virtual void pureVirtual() = 0;  // 2. Pure virtual (abstract)
    virtual void implemented() {     // 3. Virtual with default
        // default implementation
    }
};
```

### 2. Interface Design

**Good interface**:
```cpp
class IDrawable {
public:
    virtual ~IDrawable() {}
    virtual void draw() const = 0;
    virtual void setColor(Color c) = 0;
};
```

**Characteristics**:
- Pure virtual functions only
- No member variables
- Virtual destructor
- Clear, focused purpose

### 3. Deep Copy Template

```cpp
class MyClass : public Base {
private:
    Resource* resource;
    
public:
    // Copy constructor
    MyClass(const MyClass& other) : Base(other) {
        resource = new Resource(*other.resource);
    }
    
    // Assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            Base::operator=(other);
            delete resource;
            resource = new Resource(*other.resource);
        }
        return *this;
    }
    
    // Destructor
    ~MyClass() {
        delete resource;
    }
};
```

---

## 🔗 Building on CPP_03

CPP_03 taught basic inheritance. CPP_04 extends this with:
- ✅ Virtual functions for dynamic dispatch
- ✅ Abstract classes for interface enforcement
- ✅ Polymorphism for flexible code
- ✅ Deep copy with dynamically allocated members
- ✅ Complex object hierarchies

---

## 🚀 Preparing for CPP_05

You've mastered polymorphism. Next:
- **Exceptions**: Error handling with try/catch
- **Custom exceptions**: Creating your own exception classes
- **Exception safety**: Writing exception-safe code
- **RAII with exceptions**: Resource management

**Preview**:
```cpp
class GradeTooHighException : public std::exception {
public:
    const char* what() const throw() {
        return "Grade is too high!";
    }
};

try {
    // risky code
    throw GradeTooHighException();
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

---

## 🐛 Common Pitfalls

1. **Forgetting virtual destructor**:
   ```cpp
   class Base {
   public:
       ~Base() {}  // Not virtual! ✗
   };
   
   Base* obj = new Derived();
   delete obj;  // Only Base destructor called - memory leak!
   ```

2. **Slicing**:
   ```cpp
   Derived d;
   Base b = d;  // Slicing! Only Base part copied
   b.virtualFunc();  // Calls Base version, not Derived
   ```

3. **Not marking overrides**:
   ```cpp
   class Base {
   public:
       virtual void func();
   };
   
   class Derived : public Base {
   public:
       void func();  // Should mark as override (C++11)
       // virtual void func() override;
   };
   ```

4. **Shallow copy with pointers**:
   ```cpp
   MyClass(const MyClass& other) {
       ptr = other.ptr;  // Shallow copy - both point to same data!
   }
   ```

5. **Pure virtual function calls**:
   ```cpp
   class Base {
   public:
       Base() {
           init();  // Calls pure virtual in constructor! ✗
       }
       virtual void init() = 0;
   };
   ```

---

## 🎯 Summary

Module 04 covers polymorphism and abstract classes:
- ✅ Virtual functions enable dynamic dispatch
- ✅ Pure virtual functions create abstract classes
- ✅ Interfaces define contracts
- ✅ Virtual destructors prevent memory leaks
- ✅ Deep copy required for pointer members
- ✅ Polymorphism enables flexible, extensible code

**Key Concepts**:
- `virtual` keyword enables runtime polymorphism
- Pure virtual (`= 0`) forces implementation in derived classes
- Always use virtual destructors in polymorphic hierarchies
- Deep copy prevents shared pointer issues
- Interfaces separate specification from implementation

**Remember**:
- Virtual functions: `virtual void func();`
- Pure virtual functions: `virtual void func() = 0;`
- Virtual destructor: `virtual ~ClassName();`
- Deep copy: `new Type(*other.ptr)`

**You now understand polymorphism—one of OOP's most powerful tools!** 🎉
