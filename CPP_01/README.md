# CPP Module 01 - Memory Management, Pointers, and References

## 🎯 New Concepts in This Module

### Memory Allocation: Stack vs Heap
Learn when and how to allocate objects dynamically.

**Stack Allocation** (automatic):
```cpp
Zombie zombie("Bob");  // Created on stack
// Automatically destroyed when out of scope
```

**Heap Allocation** (manual with `new` and `delete`):
```cpp
Zombie* zombie = new Zombie("Bob");  // Created on heap
delete zombie;                       // Must manually delete!
```

**When to use each:**
- **Stack**: Object lifetime is limited to current scope, small size
- **Heap**: Object needs to outlive the function, large size, dynamic size

### new and delete Operators
Replace C's `malloc()` and `free()`:

```cpp
// Single object
Zombie* z = new Zombie("Name");
delete z;

// Array of objects
Zombie* horde = new Zombie[10];
delete[] horde;  // Note the []!
```

**Critical**: Always `delete` what you `new`, and use `delete[]` for arrays!

### Pointers vs References
Two ways to refer to existing objects:

**Pointers:**
```cpp
Zombie* ptr = new Zombie("Bob");
ptr->announce();     // Use -> for pointers
delete ptr;
ptr = nullptr;      // Can be reassigned
```

**References:**
```cpp
Zombie zombie("Bob");
Zombie& ref = zombie;   // Reference to existing object
ref.announce();         // Use . for references
// Cannot be reassigned
// No need to delete (not owning)
```

**Key Differences:**
| Feature | Pointer | Reference |
|---------|---------|-----------|
| Can be null | ✅ Yes | ❌ No |
| Can be reassigned | ✅ Yes | ❌ No |
| Syntax | `->` | `.` |
| Must initialize | ❌ No | ✅ Yes |

**When to use:**
- **Reference**: When you always have a valid object, don't need to reassign
- **Pointer**: When the object might not exist, or you need to change what it points to

### Constructor and Destructor Lifecycle
Understanding when objects are created and destroyed:

```cpp
{
    Zombie stackZombie("Stack");  // Constructor called
    Zombie* heapZombie = new Zombie("Heap");  // Constructor called
    
    delete heapZombie;  // Destructor called for heap zombie
}  // Destructor called for stack zombie (automatic)
```

Output messages in constructors/destructors help you visualize object lifetime.

### File I/O with Streams
Read and write files using C++ streams:

```cpp
#include <fstream>

// Reading
std::ifstream inputFile("file.txt");
if (!inputFile) {
    std::cerr << "Failed to open file" << std::endl;
    return;
}
std::string line;
while (std::getline(inputFile, line)) {
    // Process line
}
inputFile.close();

// Writing
std::ofstream outputFile("output.txt");
outputFile << "Text to write" << std::endl;
outputFile.close();
```

### Member Function Pointers
Advanced feature for elegant code:

```cpp
class Harl {
    void debug();
    void info();
    
public:
    void complain(std::string level) {
        // Array of function pointers
        void (Harl::*functions[])() = {&Harl::debug, &Harl::info};
        // Call through pointer
        (this->*functions[0])();
    }
};
```

## 💡 What You'll Build
- **ex00**: Zombie class with stack vs heap allocation
- **ex01**: Zombie horde (array allocation)
- **ex02**: Pointers vs references demonstration
- **ex03**: HumanA and HumanB with Weapon (reference vs pointer members)
- **ex04**: String replacement in files
- **ex05**: Function pointers (avoiding if-else chains)

## 📋 Quick Reference

### Memory Management
```cpp
// Heap allocation - single
Type* ptr = new Type(args);
delete ptr;

// Heap allocation - array
Type* arr = new Type[size];
delete[] arr;  // Don't forget the []!

// Stack allocation
Type obj(args);  // Automatic cleanup
```

### Reference Members in Classes
```cpp
class HumanA {
private:
    Weapon& weapon;  // Reference member
public:
    // MUST initialize in initializer list
    HumanA(Weapon& w) : weapon(w) {}
};
```

### Common File Operations
```cpp
std::ifstream in("input.txt");
std::ofstream out("output.txt");

std::string line;
std::getline(in, line);

std::string::find(str);  // Returns position or std::string::npos
std::string::substr(pos, len);
std::string::insert(pos, str);
std::string::erase(pos, len);
```

### Common Mistakes to Avoid
- Using `delete` instead of `delete[]` for arrays (undefined behavior!)
- Forgetting to delete dynamically allocated memory (memory leak)
- Trying to reassign a reference
- Not initializing references in constructor initializer list
- Returning pointers/references to local variables

---

**Previous Module**: CPP_00 covered classes, constructors, and encapsulation  
**Next Module**: CPP_02 covers operator overloading and copy constructors
