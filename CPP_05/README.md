# CPP Module 05 - Exceptions

## 🎯 New Concepts in This Module

### Exception Handling
Handle errors cleanly without return codes:

**C-style** (error codes):
```cpp
int divide(int a, int b, int* result) {
    if (b == 0) return -1;  // Error code
    *result = a / b;
    return 0;  // Success
}

int result;
if (divide(10, 0, &result) == -1) {
    // Handle error - easy to forget to check!
}
```

**C++-style** (exceptions):
```cpp
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

try {
    int result = divide(10, 0);
} catch (std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
```

**Benefits:**
- Can't ignore errors (unlike return codes)
- Separates error handling from normal code
- Automatic cleanup through stack unwinding

### try-catch Blocks
```cpp
try {
    // Code that might throw
    riskyOperation();
} catch (SpecificException& e) {
    // Handle specific exception
    std::cout << e.what() << std::endl;
} catch (std::exception& e) {
    // Handle all standard exceptions
    std::cout << e.what() << std::endl;
} catch (...) {
    // Catch everything (including non-exception types)
    std::cout << "Unknown exception" << std::endl;
}
```

**Order matters:** Catch specific exceptions before general ones!

### Throwing Exceptions
```cpp
// Throw standard exception
throw std::runtime_error("Something went wrong");

// Throw custom exception
throw MyException("Custom error");

// Re-throw caught exception
catch (std::exception& e) {
    // Do something
    throw;  // Re-throw same exception
}
```

### Custom Exception Classes
Inherit from `std::exception`:

```cpp
class MyException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "My error message";
    }
    
    virtual ~MyException() throw() {}
};

// Usage:
throw MyException();
```

**Key points:**
- Inherit from `std::exception`
- Override `what()` method
- Mark `what()` and destructor with `throw()` (no-throw guarantee)

### Nested Exception Classes
Organize exceptions within classes:

```cpp
class Bureaucrat {
public:
    class GradeTooHighException : public std::exception {
        const char* what() const throw() {
            return "Grade is too high!";
        }
    };
    
    class GradeTooLowException : public std::exception {
        const char* what() const throw() {
            return "Grade is too low!";
        }
    };
    
    void setGrade(int grade) {
        if (grade < 1) throw GradeTooHighException();
        if (grade > 150) throw GradeTooLowException();
        this->grade = grade;
    }
};

// Usage:
try {
    Bureaucrat bob("Bob", 0);
} catch (Bureaucrat::GradeTooHighException& e) {
    std::cerr << e.what() << std::endl;
}
```

### Stack Unwinding
When an exception is thrown:
1. Current function exits
2. Local objects' destructors are called (cleanup!)
3. Moves to calling function
4. Repeats until exception is caught

```cpp
void func3() {
    MyClass obj;  // Constructor called
    throw std::runtime_error("Error!");
    // obj's destructor called during unwinding
}

void func2() {
    func3();  // Exception propagates up
}

void func1() {
    try {
        func2();
    } catch (std::exception& e) {
        // Exception caught here
    }
}
```

### RAII and Exceptions
Resource Acquisition Is Initialization - resources cleaned up automatically:

```cpp
class File {
    std::ofstream file;
public:
    File(const std::string& filename) {
        file.open(filename.c_str());
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file");
        }
    }
    
    ~File() {
        if (file.is_open()) {
            file.close();  // Always cleanup, even with exceptions
        }
    }
};

void processFile() {
    File f("data.txt");  // Acquired in constructor
    // ... work with file ...
    // File closed in destructor automatically, even if exception thrown!
}
```

### Exception Safety Guarantees
**No-throw guarantee:**
```cpp
void func() throw() {  // C++98 (deprecated in C++11)
    // Never throws
}
```

**Strong guarantee:**
- Function succeeds completely OR
- Function fails and leaves state unchanged

**Basic guarantee:**
- No resource leaks
- Object remains in valid state

## 💡 What You'll Build
- **ex00**: Bureaucrat with grade validation
- **ex01**: Form that can be signed
- **ex02**: Abstract Form with concrete implementations
- **ex03**: Intern factory using exceptions

## 📋 Quick Reference

### Basic Exception Handling
```cpp
// Throw
throw std::exception();

// Catch
try {
    riskyCode();
} catch (std::exception& e) {  // Catch by reference!
    std::cout << e.what() << std::endl;
}
```

### Custom Exception
```cpp
class MyException : public std::exception {
    const char* what() const throw() {
        return "Error message";
    }
    ~MyException() throw() {}
};
```

### Standard Exception Hierarchy
```
std::exception
├── std::bad_alloc
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::out_of_range
│   └── ...
└── std::runtime_error
    ├── std::range_error
    ├── std::overflow_error
    └── ...
```

### Exception-Safe Code
```cpp
void func() {
    Resource* r = new Resource();  // BAD - leak if exception!
    riskyOperation();
    delete r;  // Might not reach here
}

void func() {
    std::auto_ptr<Resource> r(new Resource());  // GOOD - RAII
    riskyOperation();
    // r deleted automatically
}
```

### Common Mistakes to Avoid
- Throwing from destructors (can cause `std::terminate()`!)
- Catching by value (causes slicing)
- Memory leaks when exceptions thrown
- Not using `throw()` on `what()` and destructor
- Forgetting to check self-assignment in operator=

### Never Do This
```cpp
~MyClass() {
    throw std::exception();  // NEVER throw from destructor!
    // If destructor called during stack unwinding, program terminates
}

catch (std::exception e) {  // NEVER catch by value!
    // Slices derived class to base class
}
```

### Always Do This
```cpp
// Catch by reference
catch (std::exception& e) { }
catch (const std::exception& e) { }

// Virtual destructor in base classes
class Base {
    virtual ~Base() {}
};

// RAII for resource management
class ResourceHolder {
    Resource* r;
public:
    ResourceHolder() : r(new Resource()) {}
    ~ResourceHolder() { delete r; }
};
```

---

**Previous Module**: CPP_04 covered polymorphism and virtual functions  
**Next Modules**: CPP_06 (casting), CPP_07 (templates), CPP_08 (STL containers)

**Congratulations!** You've completed the foundational C++ modules covering:
- Classes and OOP (CPP_00)
- Memory management (CPP_01)
- Operator overloading (CPP_02)
- Inheritance (CPP_03)
- Polymorphism (CPP_04)
- Exceptions (CPP_05)
