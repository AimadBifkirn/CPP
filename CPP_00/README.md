# CPP Module 00 - Introduction to C++

## 📚 Module Overview

Welcome to your first C++ module! This module introduces you to the fundamental concepts of C++ programming, focusing on the transition from C to C++. You'll learn about namespaces, classes, member functions, and the basics of object-oriented programming (OOP).

### What You'll Learn
- Basic C++ syntax and iostream library
- Namespaces and their usage
- Classes and objects
- Member functions and attributes
- Encapsulation (public/private)
- Basic input/output with streams
- The difference between C and C++ programming styles

---

## 🎯 Key Concepts Explained

### 1. Namespaces
Namespaces help organize code and prevent naming conflicts.

```cpp
#include <iostream>

// Using std namespace
std::cout << "Hello, World!" << std::endl;

// Or with using directive (not recommended in headers)
using namespace std;
cout << "Hello, World!" << endl;
```

**Best Practice**: Always use `std::` prefix instead of `using namespace std;` to avoid naming conflicts.

### 2. Classes and Objects
Classes are blueprints for creating objects. They encapsulate data (attributes) and functions (methods) that operate on that data.

```cpp
class Contact {
private:
    std::string name;      // Private attribute
    std::string phone;
    
public:
    // Constructor
    Contact() {}
    
    // Getter (accessor)
    std::string getName() {
        return name;
    }
    
    // Setter (mutator)
    void setName(std::string newName) {
        name = newName;
    }
};
```

### 3. Encapsulation
Encapsulation is hiding internal data and providing controlled access through public methods.

- **Private**: Only accessible within the class
- **Public**: Accessible from anywhere
- **Protected**: Accessible within the class and derived classes (you'll learn this later)

### 4. Input/Output Streams
C++ uses streams for I/O operations:

```cpp
#include <iostream>

int main() {
    std::string input;
    
    // Output
    std::cout << "Enter your name: ";
    
    // Input
    std::cin >> input;
    // or for entire line:
    std::getline(std::cin, input);
    
    return 0;
}
```

---

## 💻 Exercise Breakdown

### Exercise 00: Megaphone
**File**: `ex00/megaphone.cpp`

#### What It Teaches
- Basic C++ program structure
- Command-line arguments
- String manipulation with `toupper()`
- Using `std::cout` for output

#### Concept
Create a program that converts command-line arguments to uppercase and prints them.

#### Example
```bash
./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

#### Key Takeaways
- Arguments are passed as `char **argv`
- `argc` tells you the number of arguments
- `std::cout` is used for output instead of `printf()`
- Character manipulation with C++ is straightforward

#### Common Mistakes
- Forgetting to include `<iostream>`
- Not handling the case when no arguments are provided
- Using `printf()` instead of `std::cout`

---

### Exercise 01: My Awesome PhoneBook
**Files**: `ex01/PhoneBook.{cpp,hpp}`, `Contact.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Creating multiple classes
- Class composition (PhoneBook contains Contacts)
- Array of objects
- Getters and setters
- User input handling
- Formatted output
- Program loop and menu system

#### Concept
Create a phonebook application that stores up to 8 contacts with the following features:
- **ADD**: Add a new contact (replaces oldest if full)
- **SEARCH**: Display all contacts and allow viewing details
- **EXIT**: Quit the program

#### Class Structure
```
PhoneBook
├── Contact contacts[8]     // Array of 8 contacts
└── int index              // Current position

Contact
├── first_name
├── last_name
├── nickname
├── phone_number
└── darkest_secret
```

#### Example Usage
```
> ADD
First name: John
Last name: Doe
Nickname: JD
Phone number: 1234567890
Darkest secret: Loves pineapple pizza

> SEARCH
     Index|First Name| Last Name|  Nickname
         0|      John|       Doe|        JD
         1|     Alice|     Smith|    Alicia
> 0
First name: John
Last name: Doe
...
```

#### Key Implementation Details

**1. Header Guards**
```cpp
#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
// ... class definition ...
#endif
```
Prevents multiple inclusion of the same header file.

**2. Getters and Setters Pattern**
```cpp
class Contact {
private:
    std::string first_name;
    
public:
    std::string get_first_name() {
        return first_name;
    }
    
    void set_first_name(std::string name) {
        first_name = name;
    }
};
```

**3. Array Management**
```cpp
class PhoneBook {
private:
    Contact contacts[8];
    int index;  // Keeps track of current position
    
public:
    PhoneBook() : index(0) {}  // Initialize index to 0
    
    void add(Contact c) {
        contacts[index % 8] = c;  // Wrap around after 8
        index++;
    }
};
```

#### Key Takeaways
- Classes can contain other classes (composition)
- Private data should be accessed through public methods
- Formatting output requires careful string manipulation
- Static arrays in C++ are similar to C
- Modulo operator (%) is useful for circular buffers

#### Common Mistakes
1. **Not initializing index**: Always initialize member variables
   ```cpp
   PhoneBook() : index(0) {}  // Good
   PhoneBook() {}             // Bad - index is uninitialized
   ```

2. **Direct access to private members**: Use getters/setters
   ```cpp
   // Wrong
   std::cout << contact.first_name;
   
   // Correct
   std::cout << contact.get_first_name();
   ```

3. **Not handling empty fields**: Validate input before storing

4. **Memory leaks**: With static arrays, you're safe, but be aware for future modules

5. **Truncating display incorrectly**: When displaying 10 characters, remember to add "." if truncated

---

## 🎓 Best Practices

### 1. Naming Conventions
```cpp
class ClassName         // Classes: PascalCase
{
private:
    int memberVariable; // Variables: camelCase
    
public:
    void methodName();  // Methods: camelCase
};
```

### 2. Const Correctness
```cpp
class Contact {
public:
    // This method doesn't modify the object
    std::string getName() const {
        return name;
    }
};
```

### 3. Initialization Lists (Constructor)
```cpp
PhoneBook::PhoneBook() : index(0) {
    // index is initialized before the constructor body runs
}
```

### 4. Header File Organization
```cpp
// Contact.hpp
#ifndef CONTACT_HPP      // 1. Header guard
#define CONTACT_HPP

#include <string>        // 2. System includes
#include <iostream>

class Contact {          // 3. Class declaration
private:                 // 4. Private members first
    std::string name;
    
public:                  // 5. Public interface
    Contact();
    std::string getName();
    void setName(std::string n);
};

#endif                   // 6. Close header guard
```

---

## 🔗 Building on Previous Knowledge

This module assumes you have:
- Basic C programming knowledge (variables, loops, functions)
- Understanding of pointers and memory
- Familiarity with compilation and Makefiles

**Key Differences from C:**
| C | C++ |
|---|-----|
| `printf()` | `std::cout <<` |
| `scanf()` | `std::cin >>` |
| Structs | Classes (with methods) |
| No namespaces | Namespaces (`std::`) |
| Function-oriented | Object-oriented |

---

## 🚀 Preparing for CPP_01

This module establishes the foundation for:
- **Memory Management**: In CPP_01, you'll learn about dynamic allocation with `new` and `delete`
- **References**: Understanding objects prepares you for references vs. pointers
- **Constructors/Destructors**: You'll explore these in depth, including when they're called

### What's Next?
In CPP_01, you'll dive deeper into:
- Stack vs. heap allocation
- References vs. pointers
- Constructor and destructor behavior
- Memory management best practices

---

## 📝 Tips for Success

1. **Compile frequently**: Use the provided Makefile and compile often
   ```bash
   make
   ./megaphone "test"
   ```

2. **Test edge cases**:
   - Empty inputs
   - Very long strings
   - Special characters
   - Maximum capacity (8 contacts)

3. **Use good formatting**: Make your output readable and aligned

4. **Comment your code**: Especially complex logic in PhoneBook

5. **Follow the subject**: Read the exercise requirements carefully

6. **Don't use forbidden functions**: Stick to the allowed functions list

---

## 🐛 Common Pitfalls

1. **Using C functions instead of C++**:
   - ❌ `printf()`, `scanf()`
   - ✅ `std::cout`, `std::cin`

2. **Global variables**: Avoid them; use class members instead

3. **Not validating input**: Always check if input is valid

4. **Memory issues**: While not critical in Module 00, develop good habits

5. **Ignoring const correctness**: Mark methods that don't modify as `const`

---

## 🎯 Summary

Module 00 introduces you to C++ by covering:
- ✅ Basic C++ syntax and iostream
- ✅ Classes and objects
- ✅ Encapsulation with public/private
- ✅ Member functions and attributes
- ✅ Simple OOP design

You've built two programs:
1. **Megaphone**: String manipulation and I/O
2. **PhoneBook**: Multi-class design with user interaction

These fundamentals are crucial for everything that follows. Master them before moving on!

---

## 📚 Additional Resources

- [C++ Reference](https://en.cppreference.com/)
- [Learn C++](https://www.learncpp.com/)
- C++ Primer (Book)
- The C++ Programming Language by Bjarne Stroustrup

**Good luck with your C++ journey! 🚀**
