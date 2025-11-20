# CPP Module 00 - Introduction to C++

## 🌟 Introduction to Object-Oriented Programming (OOP)

Before diving into C++, it's essential to understand the paradigm shift from procedural to object-oriented programming.

**Object-Oriented Programming** is a programming paradigm that organizes software design around **objects** rather than functions and logic. An object combines data (attributes/properties) and behavior (methods/functions) into a single unit.

### The Four Pillars of OOP:

1. **Encapsulation**: Bundling data and methods that operate on that data within a single unit (a class), while restricting direct access to some of the object's components. This protects the integrity of the data.

2. **Abstraction**: Hiding complex implementation details and exposing only the essential features. Users interact with a simple interface without needing to understand the underlying complexity.

3. **Inheritance**: Creating new classes based on existing ones, inheriting their attributes and methods. This promotes code reuse and establishes relationships between classes.

4. **Polymorphism**: The ability for different classes to be treated as instances of the same class through a common interface. Objects can take many forms and behave differently based on their actual type.

### Why OOP?

- **Modularity**: Code is organized into self-contained objects
- **Reusability**: Classes can be reused across projects
- **Scalability**: Easy to add new features without breaking existing code
- **Maintainability**: Changes in one class don't affect others
- **Real-world modeling**: Objects represent real-world entities naturally

In C++, these principles are implemented through classes, inheritance, virtual functions, and other language features you'll learn throughout these modules.

---

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

#### My Implementation

Here's my actual implementation from `ex00/megaphone.cpp`:

```cpp
#include <iostream>

void	uper_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		std::cout << (char)toupper(str[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
		return (0);
	}
	while (argv[i])
	{
		uper_print(argv[i]);
		i++;
	}
	std::cout << "\n";
	return (0);
}
```

**How I solved it:**

1. **Helper Function**: I created a `uper_print()` function that takes a C-style string and prints each character in uppercase. This separates concerns and makes the code more readable.

2. **Character-by-Character Processing**: Instead of creating a new string, I process and output each character immediately using `toupper()` and `std::cout`.

3. **No Arguments Case**: The first check handles the case when `argc == 1` (no arguments provided), printing the default "LOUD AND UNBEARABLE FEEDBACK NOISE" message.

4. **Loop Through Arguments**: I iterate through `argv` starting from index 1 (skipping the program name at index 0), calling `uper_print()` for each argument.

5. **Final Newline**: After all arguments are printed, I add a newline character.

**Design Decisions:**
- Used C-style strings (char*) since that's what `argv` provides
- Kept it simple without string conversions or extra allocations
- Made output immediate rather than building a buffer
- Maintained C++98 compatibility

#### Key Takeaways
- Arguments are passed as `char **argv`
- `argc` tells you the number of arguments
- `std::cout` is used for output instead of `printf()`
- Character manipulation with C++ is straightforward
- Helper functions improve code organization even in small programs

#### Common Mistakes
- Forgetting to include `<iostream>`
- Not handling the case when no arguments are provided
- Using `printf()` instead of `std::cout`
- Starting loop from `argv[0]` instead of `argv[1]` (would print program name)

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

My actual implementation uses these classes:

**Contact Class** (`Contact.hpp`):
```cpp
class Contact
{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	phone_number;
		std::string	darkest_secret;
	public:
		std::string	get_first_name();
		std::string	get_last_name();
		std::string	get_nickname();
		std::string	get_phone_number();
		std::string	get_darkest_secret();
		void	set_first_name(std::string new_fn);
		void	set_last_name(std::string new_ln);
		void	set_nickname(std::string new_nickname);
		void	set_phone_number(std::string new_pn);
		void	set_darkest_secret(std::string new_ds);
};
```

**PhoneBook Class** (`PhoneBook.hpp`):
```cpp
class PhoneBook
{
	private:
		Contact con_arry[8];  // Fixed array of 8 contacts
		int		index;         // Current insertion position
	public:
		PhoneBook();
		void	getContact(int i);
		void	add(Contact c);
		int		displayContacts();
		int		getIndex();
};
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

#### My Implementation

**1. Constructor and Index Management**

My `PhoneBook` constructor initializes the index to 0:
```cpp
PhoneBook::PhoneBook()
{
	index = 0;
}
```

The `add()` method implements a circular buffer by resetting the index to 0 when it reaches 8:
```cpp
void	PhoneBook::add(Contact new_contact)
{
	con_arry[index] = new_contact;
	index++;
	if (index == 8)
		index = 0;
	std::cout << "\033[32mContact added successfully\033[0m" << std::endl;
}
```

**Why this approach?** The circular buffer automatically overwrites the oldest contact when the phonebook is full, without needing complex array shifting or tracking which contact is oldest.

**2. Getters and Setters**

The `Contact` class uses simple getter/setter methods. Here's an example:
```cpp
std::string	Contact::get_first_name()
{
	return (first_name);
}

void	Contact::set_first_name(std::string new_fn)
{
	first_name = new_fn;
}
```

All five fields follow this same pattern. This encapsulation ensures:
- Data is protected from invalid access
- Future validation can be added to setters
- Internal representation can change without breaking code that uses the class

**3. Formatted Display**

The trickiest part was displaying contacts in a formatted table. I created a helper function:
```cpp
void	print_element(std::string str)
{
	if (str.length() > 10)
		str = str.substr(0, 9) + ".";  // Truncate and add period
	std::cout << std::setw(10) << str;   // Right-align in 10 chars
}
```

Then used it in `print_contact_infos()`:
```cpp
void	print_contact_infos(Contact c)
{
	std::cout << "|";
	print_element(c.get_first_name());
	std::cout << "|";
	print_element(c.get_last_name());
	std::cout << "|";
	print_element(c.get_nickname());
	std::cout << "\n";
}
```

**Key technique**: `std::setw(10)` from `<iomanip>` sets the width for the next output. Combined with substring truncation, this creates perfectly aligned columns.

**4. Display All Contacts**

The `displayContacts()` method shows all non-empty contacts:
```cpp
int	PhoneBook::displayContacts()
{
	int	i = 0;
	
	if (con_arry[0].get_first_name().empty())
	{
		std::cout << "\033[31mERROR:\033[0m No contacts yet\n";
		return (1);
	}
	std::cout << "     index|first name| last name|  nickname\n";
	while (i < 8)
	{
		if (con_arry[i].get_first_name().empty())
			return (0);
		std::cout << std::setw(10) << i + 1;
		print_contact_infos(con_arry[i]);
		i++;
	}
	return (0);
}
```

**Design decision**: I check if `first_name` is empty to determine if a slot is used. The method returns early when it hits an empty slot, so partially-filled phonebooks display correctly.

**5. Input Validation**

In `main.cpp`, I created `ask_for_input()` to validate user input:
```cpp
std::string	ask_for_input(std::string str)
{
	std::string	input;

	std::cout << str;
	if (!std::getline(std::cin, input))
	{
		std::cout << "\nEOF detected, exiting ...\n";
		exit(0);
	}
	while (input.empty() || std::isspace(input[0]))
	{
		std::cout << "\033[31mERROR:\033[0m A saved contact can't have empty fields\n" << str;
		if (!std::getline(std::cin, input))
		{
			std::cout << "\nEOF detected, exiting ...\n";
			exit(0);
		}
	}
	return (input);
}
```

This ensures:
- No empty fields
- No fields starting with whitespace
- Graceful handling of EOF (Ctrl+D)

**6. Search Functionality**

The search function validates index input and displays the contact:
```cpp
void	PhoneBook::getContact(int i)
{
	if (con_arry[i].get_first_name().empty())
	{
		std::cout << "\033[31mERROR:\033[0m No contact with the given index\n";
		return ;
	}
	std::cout << "index      : " << i + 1 << "\nfirst name : " << con_arry[i].get_first_name() \
	<< "\nlast name  : " << con_arry[i].get_last_name() << "\nnickname   : " << con_arry[i].get_nickname() << "\n";
}
```

**How I solved it:**
- Used 1-based indexing for user display (more intuitive) but 0-based internally
- Color-coded error messages using ANSI escape codes (`\033[31m` for red, `\033[32m` for green)
- Separated concerns: `PhoneBook` manages data, main.cpp handles user interaction
- Used `std::getline()` instead of `std::cin >>` to handle inputs with spaces
- Implemented safe integer conversion to prevent crashes on invalid input

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
