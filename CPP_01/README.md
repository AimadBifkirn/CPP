# CPP Module 01 - Memory Allocation, Pointers, and References

## 📚 Module Overview

Module 01 focuses on one of the most critical aspects of C++: **memory management**. You'll learn the differences between stack and heap allocation, understand pointers vs. references, and explore constructors and destructors in depth.

### What You'll Learn
- Stack vs. heap memory allocation
- Dynamic memory with `new` and `delete`
- Pointers vs. references in C++
- Constructor and destructor lifecycles
- File stream operations (`std::ifstream`, `std::ofstream`)
- String manipulation and replacement
- Switch statements and function pointers

---

## 🎯 Key Concepts Explained

### 1. Stack vs. Heap Memory

**Stack Memory**:
- Automatic allocation/deallocation
- Fast access
- Limited size
- Managed by the compiler

```cpp
void function() {
    Zombie zombie("Stack");  // Allocated on stack
    // Automatically destroyed when function ends
}
```

**Heap Memory**:
- Manual allocation with `new`
- Manual deallocation with `delete`
- Larger available memory
- Slower than stack
- Risk of memory leaks if not freed

```cpp
void function() {
    Zombie* zombie = new Zombie("Heap");  // Allocated on heap
    // Must manually delete
    delete zombie;
}
```

### 2. Pointers vs. References

**Pointers**:
```cpp
Zombie* ptr = new Zombie("Bob");
ptr->announce();        // Use -> for pointers
delete ptr;
ptr = nullptr;         // Can be reassigned
```

**References**:
```cpp
Zombie zombie("Bob");
Zombie& ref = zombie;   // Reference to existing object
ref.announce();         // Use . for references
// Cannot be reassigned
// No need to delete (refers to existing object)
```

**Key Differences**:
| Feature | Pointer | Reference |
|---------|---------|-----------|
| Can be null | ✅ Yes | ❌ No |
| Can be reassigned | ✅ Yes | ❌ No |
| Syntax | `->` | `.` |
| Must be initialized | ❌ No | ✅ Yes |
| Can point to nothing | ✅ Yes (nullptr) | ❌ No |

### 3. When to Use Each

**Use Heap (new/delete)** when:
- Object lifetime extends beyond current scope
- You need dynamic size
- Returning objects from functions

**Use Stack** when:
- Lifetime is limited to current scope
- Fixed size is acceptable
- Performance is critical

**Use References** when:
- You want to avoid copying
- The reference will always be valid
- You don't need to reassign

**Use Pointers** when:
- You need optional parameters (can be null)
- Dynamic memory allocation
- You need to reassign

### 4. Constructors and Destructors

```cpp
class Zombie {
private:
    std::string name;
    
public:
    // Constructor - called when object is created
    Zombie(std::string n) : name(n) {
        std::cout << name << " created" << std::endl;
    }
    
    // Destructor - called when object is destroyed
    ~Zombie() {
        std::cout << name << " destroyed" << std::endl;
    }
};

// Usage
{
    Zombie z1("Stack");           // Constructor called
    Zombie* z2 = new Zombie("Heap");  // Constructor called
    delete z2;                    // Destructor called
}  // z1 destructor called automatically
```

---

## 💻 Exercise Breakdown

### Exercise 00: BraiiiiiiinnnzzzZ
**Files**: `Zombie.{cpp,hpp}`, `newZombie.cpp`, `randomChump.cpp`, `main.cpp`

#### What It Teaches
- Stack vs. heap allocation
- When objects are destroyed
- Constructor and destructor timing
- Function return values vs. local variables

#### Concept
Create a Zombie class with two different allocation methods:
- `newZombie()`: Creates a zombie on the heap (returns pointer)
- `randomChump()`: Creates a zombie on the stack (local variable)

#### Implementation
```cpp
class Zombie {
private:
    std::string name;
    
public:
    Zombie(std::string name);
    ~Zombie();
    void announce();  // Prints "name: BraiiiiiiinnnzzzZ..."
};

// Heap allocation - zombie survives function return
Zombie* newZombie(std::string name) {
    return new Zombie(name);
}

// Stack allocation - zombie destroyed at function end
void randomChump(std::string name) {
    Zombie zombie(name);
    zombie.announce();
}  // Zombie destroyed here
```

#### Key Observations
When you run the program, you'll see:
```
Creating heap zombie...
Foo: BraiiiiiiinnnzzzZ...
Creating stack zombie...
Bar: BraiiiiiiinnnzzzZ...
Bar destroyed        // Stack zombie destroyed immediately
...
Foo destroyed        // Heap zombie destroyed when we delete it
```

#### Key Takeaways
- Heap objects survive beyond function scope
- Stack objects are automatically destroyed
- Always `delete` what you `new`
- Use heap when object lifetime needs to extend beyond current scope

#### Common Mistakes
1. Forgetting to `delete` heap-allocated zombies (memory leak)
2. Trying to use stack zombie after function returns
3. Deleting stack-allocated objects (crash!)
4. Not understanding when destructors are called

---

### Exercise 01: Moar brainz!
**Files**: `Zombie.{cpp,hpp}`, `zombieHorde.cpp`, `main.cpp`

#### What It Teaches
- Allocating arrays on the heap
- Default constructor necessity
- Deleting arrays with `delete[]`
- Initializing multiple objects

#### Concept
Create a function that allocates N zombies in a single allocation:

```cpp
Zombie* zombieHorde(int N, std::string name);
```

#### Implementation
```cpp
Zombie* zombieHorde(int N, std::string name) {
    // Allocate array of N zombies
    Zombie* horde = new Zombie[N];
    
    // Initialize each zombie
    for (int i = 0; i < N; i++) {
        horde[i].setName(name);
        // or use placement new for constructor
    }
    
    return horde;
}

// Usage in main
Zombie* horde = zombieHorde(10, "HordeZombie");
for (int i = 0; i < 10; i++) {
    horde[i].announce();
}
delete[] horde;  // Must use delete[] for arrays!
```

#### Critical Points

**Array Allocation**:
```cpp
Zombie* single = new Zombie("Name");    // Single object
delete single;                          // Use delete

Zombie* array = new Zombie[10];         // Array of objects
delete[] array;                         // Use delete[]
```

**Default Constructor Requirement**:
When you allocate an array (`new Zombie[N]`), each object is created using the default constructor. You need one:

```cpp
class Zombie {
public:
    Zombie();              // Default constructor needed for arrays
    Zombie(std::string n); // Parameterized constructor
};
```

#### Key Takeaways
- `new[]` requires `delete[]` (not `delete`)
- Array allocation calls default constructor for each element
- Single allocation is more efficient than multiple individual allocations
- All zombies in the horde share the same name (unless you modify them individually)

#### Common Mistakes
1. Using `delete` instead of `delete[]` for arrays (undefined behavior!)
2. Not having a default constructor when needed
3. Forgetting to delete the array (memory leak)
4. Accessing array out of bounds

---

### Exercise 02: HI THIS IS BRAIN
**Files**: `main.cpp`

#### What It Teaches
- Difference between pointers and references
- Memory addresses
- Dereferencing

#### Concept
Demonstrate pointers vs. references with a simple string:

```cpp
int main() {
    std::string str = "HI THIS IS BRAIN";
    std::string* stringPTR = &str;  // Pointer to str
    std::string& stringREF = str;   // Reference to str
    
    // Print addresses
    std::cout << "Address of str:       " << &str << std::endl;
    std::cout << "Address in stringPTR: " << stringPTR << std::endl;
    std::cout << "Address of stringREF: " << &stringREF << std::endl;
    
    // Print values
    std::cout << "Value of str:       " << str << std::endl;
    std::cout << "Value via stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value via stringREF: " << stringREF << std::endl;
    
    return 0;
}
```

#### Expected Output
```
Address of str:       0x7ffc1234
Address in stringPTR: 0x7ffc1234
Address of stringREF: 0x7ffc1234

Value of str:       HI THIS IS BRAIN
Value via stringPTR: HI THIS IS BRAIN
Value via stringREF: HI THIS IS BRAIN
```

#### Key Observations
- All three point to the **same memory address**
- References are essentially const pointers with automatic dereferencing
- Pointers need `*` to access value, references use variable directly

#### Key Takeaways
- References and pointers can access the same data
- References are safer (can't be null, can't be reassigned)
- Both avoid copying large objects

---

### Exercise 03: Unnecessary Violence
**Files**: `Weapon.{cpp,hpp}`, `HumanA.{cpp,hpp}`, `HumanB.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- When to use references vs. pointers
- Const references
- Object composition
- Reference member variables

#### Concept
Create two human classes that use weapons differently:
- **HumanA**: Always has a weapon (reference)
- **HumanB**: May or may not have a weapon (pointer)

#### Implementation

**Weapon Class**:
```cpp
class Weapon {
private:
    std::string type;
    
public:
    Weapon(std::string type);
    const std::string& getType() const;
    void setType(std::string type);
};
```

**HumanA** (with reference):
```cpp
class HumanA {
private:
    std::string name;
    Weapon& weapon;  // Reference - must be initialized
    
public:
    HumanA(std::string name, Weapon& weapon) 
        : name(name), weapon(weapon) {
        // weapon MUST be initialized in initializer list
    }
    
    void attack() {
        std::cout << name << " attacks with " 
                  << weapon.getType() << std::endl;
    }
};
```

**HumanB** (with pointer):
```cpp
class HumanB {
private:
    std::string name;
    Weapon* weapon;  // Pointer - can be null
    
public:
    HumanB(std::string name) : name(name), weapon(nullptr) {}
    
    void setWeapon(Weapon& weapon) {
        this->weapon = &weapon;
    }
    
    void attack() {
        if (weapon)
            std::cout << name << " attacks with " 
                      << weapon->getType() << std::endl;
    }
};
```

#### Usage Example
```cpp
// HumanA - weapon required at construction
Weapon club = Weapon("crude spiked club");
HumanA bob("Bob", club);
bob.attack();
club.setType("some other type of club");
bob.attack();  // Uses updated weapon

// HumanB - weapon optional
HumanB jim("Jim");
jim.attack();  // No weapon yet
Weapon sword = Weapon("sword");
jim.setWeapon(sword);
jim.attack();  // Now has weapon
```

#### Key Design Decision
- **HumanA uses reference**: The weapon is mandatory and won't change
- **HumanB uses pointer**: The weapon is optional and can be set later

#### Key Takeaways
- References must be initialized in the constructor initializer list
- References cannot be reassigned (perfect for mandatory dependencies)
- Pointers can be null and reassigned (perfect for optional dependencies)
- Const references prevent modification: `const std::string& getType()`

#### Common Mistakes
1. Not initializing reference in initializer list
2. Trying to reassign a reference
3. Not checking if pointer is null before using
4. Returning references to local variables

---

### Exercise 04: Sed is for losers
**Files**: `main.cpp`

#### What It Teaches
- File I/O with `ifstream` and `ofstream`
- String manipulation and searching
- Command-line argument validation
- String replacement

#### Concept
Create a program that replaces all occurrences of s1 with s2 in a file:

```bash
./replace filename s1 s2
```

Creates `filename.replace` with all s1 occurrences replaced by s2.

#### Implementation
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: ./replace filename s1 s2" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    
    // Open input file
    std::ifstream infile(filename.c_str());
    if (!infile.is_open()) {
        std::cout << "Error: cannot open " << filename << std::endl;
        return 1;
    }
    
    // Open output file
    std::ofstream outfile((filename + ".replace").c_str());
    if (!outfile.is_open()) {
        std::cout << "Error: cannot create output file" << std::endl;
        return 1;
    }
    
    // Read and replace
    std::string line;
    while (std::getline(infile, line)) {
        size_t pos = 0;
        while ((pos = line.find(s1, pos)) != std::string::npos) {
            line.erase(pos, s1.length());
            line.insert(pos, s2);
            pos += s2.length();
        }
        outfile << line << std::endl;
    }
    
    infile.close();
    outfile.close();
    
    return 0;
}
```

#### Key Functions
- `std::ifstream`: Input file stream
- `std::ofstream`: Output file stream
- `std::getline()`: Read line by line
- `std::string::find()`: Find substring
- `std::string::erase()`: Remove characters
- `std::string::insert()`: Insert string

#### Edge Cases to Handle
1. Empty s1 (would cause infinite loop)
2. File doesn't exist
3. Cannot create output file
4. s1 not found in file
5. Overlapping replacements

#### Key Takeaways
- File streams work like `cin`/`cout`
- Always check if file opened successfully
- Close files when done
- String find() returns `std::string::npos` if not found
- Be careful with string position updates after replacement

#### Common Mistakes
1. Not checking if file opened
2. Infinite loop when s1 is empty or s2 contains s1
3. Not updating position after replacement
4. Forgetting to close files
5. Using `c_str()` for C++98 compatibility

---

### Exercise 05: Harl 2.0
**Files**: `Harl.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Member function pointers
- Array of function pointers
- Switch statement alternative
- Cleaner code organization

#### Concept
Create a class `Harl` that complains at different levels without using long if-else chains.

#### Implementation
```cpp
class Harl {
private:
    void debug();
    void info();
    void warning();
    void error();
    
public:
    void complain(std::string level);
};

void Harl::complain(std::string level) {
    // Array of function pointers
    void (Harl::*functions[])() = {
        &Harl::debug,
        &Harl::warning,
        &Harl::info,
        &Harl::error
    };
    
    std::string levels[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };
    
    // Find and call the appropriate function
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*functions[i])();
            return;
        }
    }
}
```

#### Member Function Pointer Syntax
```cpp
// Declaration
void (Harl::*funcPtr)();

// Assignment
funcPtr = &Harl::debug;

// Calling
(this->*funcPtr)();
// or
(object.*funcPtr)();
```

#### Key Takeaways
- Function pointers avoid long if-else chains
- Member function pointers require `(this->*ptr)()`
- Arrays of function pointers enable table-driven code
- This pattern is useful for command dispatching

#### Common Mistakes
1. Incorrect function pointer syntax
2. Forgetting `this->` when calling
3. Not matching function signatures exactly
4. Off-by-one errors in array indexing

---

### Exercise 06: Harl filter (Bonus)
Similar to ex05 but uses switch statement to filter by level and show all higher severity levels.

```cpp
switch (level) {
    case DEBUG:
        this->debug();
        // Fall through
    case INFO:
        this->info();
        // Fall through
    case WARNING:
        this->warning();
        // Fall through
    case ERROR:
        this->error();
        break;
    default:
        std::cout << "Invalid level" << std::endl;
}
```

---

## 🎓 Best Practices

### 1. Memory Management
```cpp
// RAII - Resource Acquisition Is Initialization
class ResourceHolder {
private:
    int* data;
    
public:
    ResourceHolder() {
        data = new int[100];  // Acquire in constructor
    }
    
    ~ResourceHolder() {
        delete[] data;  // Release in destructor
    }
};
```

### 2. Const Correctness
```cpp
class Weapon {
public:
    const std::string& getType() const {
        //                           ^^^^^ Method doesn't modify object
        // ^^^^^^ Return const reference to prevent modification
        return type;
    }
};
```

### 3. Initialization Lists
```cpp
// Preferred
HumanA::HumanA(std::string n, Weapon& w) : name(n), weapon(w) {}

// Avoid (assignment, not initialization)
HumanA::HumanA(std::string n, Weapon& w) {
    name = n;
    weapon = w;  // Error! Can't reassign reference
}
```

---

## 🔗 Building on CPP_00

CPP_00 taught you classes and basic OOP. CPP_01 extends this with:
- ✅ Understanding object lifetime (constructors/destructors)
- ✅ Memory management (stack vs. heap)
- ✅ References as an alternative to pointers
- ✅ File I/O operations
- ✅ More advanced C++ features (function pointers)

---

## 🚀 Preparing for CPP_02

Module 01 establishes memory management fundamentals. Next:
- **Operator Overloading**: Make objects work with `+`, `-`, `<<`, etc.
- **Orthodox Canonical Form**: Copy constructors, assignment operators
- **Fixed-point arithmetic**: Custom numeric types

---

## 🐛 Common Pitfalls

1. **Memory Leaks**:
   ```cpp
   Zombie* z = new Zombie("Foo");
   // ... forget to delete z
   ```

2. **Using delete instead of delete[]**:
   ```cpp
   Zombie* horde = new Zombie[10];
   delete horde;      // WRONG!
   delete[] horde;    // Correct
   ```

3. **Dangling pointers**:
   ```cpp
   Zombie* getZombie() {
       Zombie z("Local");
       return &z;  // WRONG! z is destroyed when function returns
   }
   ```

4. **Not initializing references**:
   ```cpp
   class HumanA {
       Weapon& weapon;
   public:
       HumanA(Weapon& w) {
           weapon = w;  // ERROR! Reference not initialized
       }
   };
   ```

---

## 🎯 Summary

Module 01 covers essential C++ memory and resource management:
- ✅ Stack vs. heap allocation
- ✅ new/delete and new[]/delete[]
- ✅ Pointers vs. references
- ✅ Constructor/destructor lifecycles
- ✅ File I/O with streams
- ✅ String manipulation
- ✅ Function pointers

**Remember**: 
- Always `delete` what you `new`
- Use `delete[]` for arrays
- Prefer references over pointers when possible
- Initialize references in constructor initializer lists

**Master these concepts—they're fundamental to writing safe, efficient C++ code!** 🚀
