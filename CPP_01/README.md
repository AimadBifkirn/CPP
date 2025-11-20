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

#### My Implementation

**Zombie Class** (`Zombie.hpp`):
```cpp
class Zombie
{
	private:
			std::string name;
	public:
			void	announce(void);
			Zombie(std::string n_name);
			~Zombie(void);
};
```

**Constructor and Destructor** (`Zombie.cpp`):
```cpp
Zombie::Zombie(std::string n_name)
{
	name = n_name;
}

Zombie::~Zombie(void)
{
	std::cout << "zombie -> " << this->name << ": died" << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
```

**Heap Allocation** (`newZombie.cpp`):
```cpp
Zombie*	newZombie(std::string name)
{
	return (new Zombie(name));
}
```

**Stack Allocation** (`randomChump.cpp`):
```cpp
void	randomChump(std::string name)
{
	Zombie	new_zombie(name);
	new_zombie.announce();
}  // Zombie destroyed here automatically
```

#### How I Solved It

**Key Design Choices:**

1. **Simple Constructor**: I used a constructor that takes the zombie's name as a parameter. This ensures every zombie has a name when created.

2. **Destructor Message**: The destructor prints a message showing which zombie died. This is crucial for understanding when objects are destroyed:
   ```cpp
   std::cout << "zombie -> " << this->name << ": died" << std::endl;
   ```

3. **`newZombie()` Function**: Creates a zombie on the heap using `new`. The zombie persists after the function returns because it's on the heap:
   ```cpp
   return (new Zombie(name));
   ```
   The caller is responsible for deleting this zombie.

4. **`randomChump()` Function**: Creates a zombie as a local variable (on the stack). It announces itself, then is automatically destroyed when the function ends:
   ```cpp
   Zombie	new_zombie(name);  // Created on stack
   new_zombie.announce();
   // Automatically destroyed here
   ```

#### When you run the program, you'll observe:

```
Stack zombie announces...
Foo: BraiiiiiiinnnzzzZ...
zombie -> Foo: died        // Stack zombie destroyed immediately

Heap zombie announces...
Bar: BraiiiiiiinnnzzzZ...
... (program continues)
zombie -> Bar: died        // Heap zombie destroyed when we delete it
```

#### Key Observations

**Stack vs Heap Lifetime:**
- **Stack zombie** (`randomChump`): Lives only within the function scope. Automatically destroyed when function ends.
- **Heap zombie** (`newZombie`): Lives until explicitly deleted with `delete`. Can be passed around and used anywhere.

**When to use each:**
- Use **stack** when the object's lifetime is limited to a function scope
- Use **heap** when the object needs to outlive the function or its size is large

#### Key Takeaways
- Heap objects survive beyond function scope
- Stack objects are automatically destroyed
- Always `delete` what you `new`
- Destructor messages help visualize object lifetimes
- The `new` keyword returns a pointer to the allocated memory

---

### Exercise 01: Moar brainz!
**Files**: `Zombie.{cpp,hpp}`, `zombieHorde.cpp`, `main.cpp`

#### What It Teaches
- Allocating arrays on the heap
- Default constructor necessity
- Deleting arrays with `delete[]`
- Initializing multiple objects
- Error handling with `new`

#### Concept
Create a function that allocates N zombies in a single allocation:

```cpp
Zombie* zombieHorde(int N, std::string name);
```

#### My Implementation

**Modified Zombie Class** (`Zombie.hpp`):
```cpp
class Zombie
{
	private:
			std::string name;
	public:
			void	announce(void);
			void	setName(std::string n_name);  // Added setter for array initialization
			~Zombie(void);
};
```

Note: Unlike ex00, this version doesn't have a parameterized constructor. When allocating an array with `new Zombie[N]`, the default constructor is called for each element.

**Zombie Implementation** (`Zombie.cpp`):
```cpp
void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string n_name)
{
	name = n_name;
}

Zombie::~Zombie(void)
{
	std::cout << "zombie -> " << this->name << ": died" << std::endl;
}
```

**zombieHorde Function** (`zombieHorde.cpp`):
```cpp
#include "Zombie.hpp"
#include <cstdlib>

Zombie*	zombieHorde(int N, std::string name)
{
	Zombie *res = new (std::nothrow) Zombie[N];

	if (!res)
	{
		std::cerr << "new failed\n";
		exit (1);
	}
	for (int i = 0; i < N; i++)
		res[i].setName(name);
	return (res);
}
```

#### How I Solved It

**1. Array Allocation with Error Handling:**

I used `new (std::nothrow)` instead of plain `new`:
```cpp
Zombie *res = new (std::nothrow) Zombie[N];
```

**Why?** 
- Regular `new` throws an exception on failure (not allowed in C++98 without exception handling)
- `new (std::nothrow)` returns `NULL` on failure, which we can check
- This allows graceful error handling

**2. Checking for Allocation Failure:**
```cpp
if (!res)
{
	std::cerr << "new failed\n";
	exit (1);
}
```

If allocation fails (e.g., requesting too much memory), the program exits cleanly with an error message.

**3. Initializing the Array:**

Since array allocation calls the default constructor (which doesn't set names), I loop through and set each zombie's name:
```cpp
for (int i = 0; i < N; i++)
	res[i].setName(name);
```

**4. Return the Array:**

The function returns a pointer to the first zombie in the array. The caller is responsible for:
- Using the zombies
- Calling `delete[]` (not `delete`!) to free the memory

#### Usage Example

```cpp
int N = 5;
Zombie* horde = zombieHorde(N, "Walker");

// Use the horde
for (int i = 0; i < N; i++) {
	horde[i].announce();
}

// Clean up - MUST use delete[] for arrays
delete[] horde;
```

#### Critical Points

**Array Allocation vs Single Object:**
```cpp
Zombie* single = new Zombie("Name");    // Single object
delete single;                           // Use delete

Zombie* array = new Zombie[10];         // Array
delete[] array;                          // Use delete[] - brackets are crucial!
```

**Why the difference?**
- `delete[]` calls the destructor for EACH element in the array
- `delete` only calls destructor for one object
- Using wrong one causes memory leaks or undefined behavior

**Default Constructor Requirement:**

When you write `new Zombie[N]`, C++ calls the default constructor N times. Therefore:
- The class must have a default constructor (compiler-generated or explicit)
- Or use placement new (advanced topic)

In my implementation, the compiler generates a default constructor since I didn't define any constructors in ex01's Zombie class.

#### Key Takeaways
- Array allocation requires default constructor
- Always use `delete[]` for arrays allocated with `new[]`
- `new (std::nothrow)` allows checking for allocation failures
- Each element in the array is a separate object with its own destructor
- Initialize array elements after allocation if they need specific values

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
- Dereferencing syntax
- How references are aliases for existing variables

#### Concept
Demonstrate pointers vs. references with a simple string to understand how they both refer to the same memory location but with different syntax.

#### My Implementation

Here's my complete `main.cpp`:
```cpp
#include <string>
#include <iostream>

int main()
{
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "The memory address of the string variable : " << &str << std::endl;
	std::cout << "The memory address held by stringPTR      : " << stringPTR << std::endl;
	std::cout << "The memory address held by stringREF      : " << &stringREF << std::endl;

	std::cout << "The value of the string variable  : " << str << std::endl;
	std::cout << "The value pointed to by stringPTR : " << *stringPTR << std::endl;
	std::cout << "The value pointed to by stringREF : " << stringREF << std::endl;
}
```

#### How I Solved It

**1. Creating the Original String:**
```cpp
std::string str = "HI THIS IS BRAIN";
```
This creates a string variable on the stack.

**2. Creating a Pointer:**
```cpp
std::string *stringPTR = &str;
```
- `&str` gets the address of `str`
- `stringPTR` stores that address
- To get the value, you must dereference with `*stringPTR`

**3. Creating a Reference:**
```cpp
std::string &stringREF = str;
```
- `stringREF` is an alias for `str`
- No need to use `*` to access the value
- Acts exactly like the original variable

**4. Printing Addresses:**
```cpp
std::cout << &str;        // Address of original
std::cout << stringPTR;   // Pointer already holds address
std::cout << &stringREF;  // Address of reference (same as str)
```

**5. Printing Values:**
```cpp
std::cout << str;         // Direct access
std::cout << *stringPTR;  // Dereference pointer with *
std::cout << stringREF;   // Reference acts like variable
```

#### Expected Output
```
The memory address of the string variable : 0x7ffc12345678
The memory address held by stringPTR      : 0x7ffc12345678
The memory address held by stringREF      : 0x7ffc12345678

The value of the string variable  : HI THIS IS BRAIN
The value pointed to by stringPTR : HI THIS IS BRAIN
The value pointed to by stringREF : HI THIS IS BRAIN
```

#### Key Observations

**All three have the same address** - they all refer to the same memory location!

**Syntax Differences:**
| Operation | Pointer | Reference |
|-----------|---------|-----------|
| Declaration | `Type* ptr = &var;` | `Type& ref = var;` |
| Get address | `ptr` (already holds it) | `&ref` |
| Get value | `*ptr` (dereference) | `ref` (direct) |

**When to use each:**
- **Pointer**: Can be null, can be reassigned, optional parameters
- **Reference**: Cannot be null, cannot be reassigned, cleaner syntax

#### Key Takeaways
- References and pointers can access the same data
- References are aliases - they ARE the original variable
- Pointers store addresses - they POINT to the original variable
- References have cleaner syntax (no * needed)
- Both avoid copying large objects

---

### Exercise 03: Unnecessary Violence
**Files**: `Weapon.{cpp,hpp}`, `HumanA.{cpp,hpp}`, `HumanB.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- When to use references vs. pointers
- Const references for getters
- Object composition
- Reference member variables
- Initializer lists with references

#### Concept
Create two human classes that use weapons differently:
- **HumanA**: Always has a weapon (uses reference)
- **HumanB**: May or may not have a weapon (uses pointer)

#### My Implementation

**Weapon Class** (`Weapon.hpp`):
```cpp
class Weapon
{
	private:
		std::string	type;
	public:
		const std::string& getType();
		void	setType(std::string new_type);
		Weapon(std::string	new_type);
};
```

**Weapon Implementation** (`Weapon.cpp`):
```cpp
const std::string& Weapon::getType()
{
	return (type);
}

void	Weapon::setType(std::string new_type)
{
	type = new_type;
}

Weapon::Weapon(std::string	new_type)
{
	type = new_type;
}
```

**HumanA Class** (`HumanA.hpp` - uses reference):
```cpp
class HumanA
{
	private:
		Weapon		&slah;   // Reference to weapon
		std::string	name;
	public:
		HumanA (std::string new_name, Weapon &new_weapon);
		void	attack();
};
```

**HumanA Implementation** (`HumanA.cpp`):
```cpp
void	HumanA::attack(void)
{
	std::cout  << this->name << " attacks with their " 
	           << this->slah.getType() << std::endl;
}

HumanA::HumanA(std::string new_name, Weapon &new_wepon)
: slah(new_wepon), name(new_name)
{
	// Reference MUST be initialized in initializer list
}
```

**HumanB Class** (`HumanB.hpp` - uses pointer):
```cpp
class HumanB
{
	private:
		Weapon		*slah;   // Pointer to weapon
		std::string	name;
	public:
		HumanB(std::string new_name);
		void	attack();
		void	setWeapon(Weapon &new_weapon);
};
```

**HumanB Implementation** (`HumanB.cpp`):
```cpp
void	HumanB::attack(void)
{
	std::cout  << this->name << " attacks with their " 
	           << this->slah->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &new_weapon)
{
	slah = &new_weapon;
}

HumanB::HumanB(std::string new_name)
{
	name = new_name;
	// Weapon pointer not initialized - will be set later
}
```

#### How I Solved It

**1. Why HumanA Uses a Reference:**

```cpp
Weapon &slah;  // Reference member
```

HumanA ALWAYS has a weapon from the moment it's created:
- References cannot be null
- References cannot be reassigned
- Must be initialized in the constructor initializer list

```cpp
HumanA::HumanA(std::string new_name, Weapon &new_wepon)
: slah(new_wepon), name(new_name)  // Initialize reference here
{
}
```

**2. Why HumanB Uses a Pointer:**

```cpp
Weapon *slah;  // Pointer member
```

HumanB might not have a weapon initially:
- Pointers can be null
- Pointers can be reassigned
- Can be set later with `setWeapon()`

```cpp
HumanB::HumanB(std::string new_name)
{
	name = new_name;
	// slah not initialized - it's okay for pointers
}

void	HumanB::setWeapon(Weapon &new_weapon)
{
	slah = &new_weapon;  // Take address of reference parameter
}
```

**3. Accessing the Weapon:**

With reference (HumanA):
```cpp
this->slah.getType()  // Use dot operator
```

With pointer (HumanB):
```cpp
this->slah->getType()  // Use arrow operator
```

**4. Const Reference Return:**

The `getType()` method returns a const reference:
```cpp
const std::string& getType();
```

Benefits:
- Avoids copying the string (efficient)
- `const` prevents caller from modifying the internal type
- Returns a reference to the actual string, not a copy

#### Key Design Decision

**When to use Reference vs Pointer:**

Use **Reference** when:
- The object MUST exist (never null)
- The relationship won't change
- You want to prevent reassignment
- Example: HumanA always has a weapon

Use **Pointer** when:
- The object might not exist (can be null)
- The relationship might change
- You need to reassign later
- Example: HumanB might get a weapon later

#### Key Takeaways
- References must be initialized in the constructor initializer list
- References cannot be null or reassigned (perfect for mandatory dependencies)
- Pointers can be null and reassigned (perfect for optional dependencies)
- Const references for getters prevent unwanted modifications
- Use `.` operator with references, `->` operator with pointers
- Taking the address of a reference (`&ref`) gives you the address of the original object

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
