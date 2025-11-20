# CPP Module 00 - Introduction to C++

## 🎯 New Concepts in This Module

### Object-Oriented Programming (OOP)
C++ allows you to write **object-oriented** code, grouping data and functions together into **classes**. This is different from C's procedural approach.

**Key OOP Principles:**
- **Encapsulation**: Keep data private, access it through public methods
- **Abstraction**: Hide complex details, show only what's necessary
- **Inheritance**: Create new classes from existing ones (covered in CPP_03)
- **Polymorphism**: Objects of different types can be used interchangeably (covered in CPP_04)

### Classes and Objects
A **class** is a blueprint for creating objects.

```cpp
class Contact {
private:
    std::string name;      // Data (attributes)
    
public:
    void setName(std::string n) {  // Function (method)
        name = n;
    }
    std::string getName() {
        return name;
    }
};

Contact person;  // Object created from the class
person.setName("John");
```

### Constructors and Destructors
**Constructor**: Special function called when object is created.
**Destructor**: Special function called when object is destroyed.

```cpp
class Contact {
public:
    Contact() {  // Constructor - same name as class
        std::cout << "Object created!" << std::endl;
    }
    
    ~Contact() {  // Destructor - name with ~
        std::cout << "Object destroyed!" << std::endl;
    }
};
```

### Access Specifiers
Control who can access class members:
- **private**: Only accessible inside the class (default for class members)
- **public**: Accessible from anywhere
- **protected**: Accessible in class and derived classes (covered in CPP_03)

```cpp
class MyClass {
private:
    int privateVar;    // Only MyClass can access
    
public:
    int publicVar;     // Anyone can access
    
    void setPrivate(int val) {  // Public method to access private data
        privateVar = val;
    }
};
```

### C++ I/O Streams
Instead of `printf()` and `scanf()`:

```cpp
#include <iostream>

std::cout << "Output text" << std::endl;  // Output
std::cin >> variable;                      // Input
std::getline(std::cin, stringVar);         // Read entire line
```

### Namespaces
Organize code and prevent naming conflicts:

```cpp
std::cout << "Hello" << std::endl;  // Using std namespace

// Avoid this in headers:
using namespace std;
cout << "Hello" << endl;
```

## 💡 What You'll Build
- **ex00**: Command-line tool that converts text to uppercase
- **ex01**: PhoneBook application with contacts storage

## 📋 Quick Reference

### Compilation
```bash
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program
```

### Key Syntax
```cpp
// Class definition
class ClassName {
private:
    std::string attribute;
public:
    ClassName();           // Constructor
    ~ClassName();          // Destructor
    void method();         // Method
};

// Input/Output
std::cout << "Output" << std::endl;
std::cin >> variable;
std::getline(std::cin, variable);
```

### Common Mistakes to Avoid
- Using `printf()`/`scanf()` instead of `std::cout`/`std::cin`
- Forgetting to include `<iostream>` for I/O
- Using `using namespace std;` in header files
- Not initializing class members
- Making everything public (breaks encapsulation)

---

**Next Module**: CPP_01 covers memory management with `new`/`delete`, pointers vs references, and file I/O.
