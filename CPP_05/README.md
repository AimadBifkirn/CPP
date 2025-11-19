# CPP Module 05 - Exceptions

## 📚 Module Overview

Module 05 introduces **exception handling**, a crucial mechanism for dealing with errors and exceptional situations in C++. You'll learn how to throw, catch, and create custom exceptions, and understand how to write exception-safe code.

### What You'll Learn
- Try-catch blocks
- Throwing exceptions
- Standard exception hierarchy
- Custom exception classes
- Exception specifications (throw())
- Exception safety guarantees
- RAII and exception handling
- Stack unwinding

---

## 🎯 Key Concepts Explained

### 1. What Are Exceptions?

Exceptions are a way to handle errors and exceptional conditions in a structured manner, separating error handling from normal program flow.

**Without exceptions** (C-style):
```cpp
int divide(int a, int b, int* result) {
    if (b == 0) {
        return -1;  // Error code
    }
    *result = a / b;
    return 0;  // Success
}

int result;
if (divide(10, 0, &result) == -1) {
    // Handle error
}
```

**With exceptions** (C++-style):
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

**Benefits**:
- Separates error handling from normal code
- Can't ignore errors (unlike return codes)
- Propagates through call stack automatically
- Type-safe error information

### 2. Try-Catch Blocks

```cpp
try {
    // Code that might throw
    riskyOperation();
    anotherRiskyOperation();
} catch (SpecificException& e) {
    // Handle specific exception
    std::cout << "Specific: " << e.what() << std::endl;
} catch (std::exception& e) {
    // Handle all standard exceptions
    std::cout << "General: " << e.what() << std::endl;
} catch (...) {
    // Catch all (including non-exception types)
    std::cout << "Unknown exception" << std::endl;
}
```

**Order matters**: Catch specific exceptions before general ones!

### 3. Throwing Exceptions

```cpp
// Throw standard exception
throw std::runtime_error("Something went wrong");

// Throw custom exception
throw MyException("Custom error message");

// Re-throw caught exception
catch (std::exception& e) {
    // Do something
    throw;  // Re-throw same exception
}
```

### 4. Standard Exception Hierarchy

```
std::exception
├── std::bad_alloc          (memory allocation failed)
├── std::bad_cast           (invalid cast)
├── std::bad_typeid         (invalid typeid)
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::domain_error
│   ├── std::length_error
│   ├── std::out_of_range
│   └── std::future_error
└── std::runtime_error
    ├── std::range_error
    ├── std::overflow_error
    └── std::underflow_error
```

**All inherit from `std::exception`** and implement `what()` method.

### 5. Custom Exceptions

```cpp
class MyException : public std::exception {
private:
    std::string message;
    
public:
    MyException(const std::string& msg) : message(msg) {}
    
    virtual const char* what() const throw() {
        return message.c_str();
    }
    
    virtual ~MyException() throw() {}
};
```

**Key points**:
- Inherit from `std::exception` (or its derived classes)
- Override `what()` method
- Mark `what()` and destructor as `throw()` (no-throw guarantee)

### 6. Stack Unwinding

When an exception is thrown, the stack is unwound:
1. Current function exits
2. Local objects are destroyed (destructors called)
3. Moves to calling function
4. Repeats until exception is caught

```cpp
void function3() {
    MyClass obj;  // Constructor called
    throw std::runtime_error("Error!");
    // obj destructor called during unwinding
}

void function2() {
    function3();  // Exception propagates
}

void function1() {
    try {
        function2();
    } catch (std::exception& e) {
        // Exception caught here
    }
}
```

### 7. Exception Safety Guarantees

**No-throw guarantee**: Function never throws
```cpp
void func() throw() {  // C++98 (deprecated)
void func() noexcept { // C++11
    // Never throws
}
```

**Strong guarantee**: Function succeeds or has no effect
```cpp
void func() {
    // Either completes successfully
    // OR throws and leaves state unchanged
}
```

**Basic guarantee**: No resource leaks, object in valid state
```cpp
void func() {
    // May throw, but no memory leaks
    // Object still usable after exception
}
```

---

## 💻 Exercise Breakdown

### Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!
**Files**: `Bureaucrat.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Creating custom exception classes
- Nested exception classes
- Throwing and catching exceptions
- Input validation with exceptions
- Const member variables

#### Concept
Create a `Bureaucrat` class with a grade (1-150) that throws exceptions for invalid grades.

#### Implementation

**Bureaucrat.hpp**:
```cpp
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat {
private:
    const std::string name;  // Const - cannot change
    int grade;               // 1 (highest) to 150 (lowest)
    
public:
    Bureaucrat();
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();
    
    // Getters
    const std::string& getName() const;
    int getGrade() const;
    
    // Grade modification
    void incrementGrade();  // Decrease number (better grade)
    void decrementGrade();  // Increase number (worse grade)
    
    // Nested exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    
    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

// Stream insertion operator
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif
```

**Bureaucrat.cpp**:
```cpp
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150) {
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : name(name) {
    if (grade < 1) {
        throw GradeTooHighException();
    }
    if (grade > 150) {
        throw GradeTooLowException();
    }
    this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) 
    : name(other.name), grade(other.grade) {
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        // Can't assign name (it's const)
        grade = other.grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {
}

const std::string& Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

void Bureaucrat::incrementGrade() {
    if (grade <= 1) {
        throw GradeTooHighException();
    }
    grade--;  // Lower number = higher grade
}

void Bureaucrat::decrementGrade() {
    if (grade >= 150) {
        throw GradeTooLowException();
    }
    grade++;  // Higher number = lower grade
}

// Exception implementations
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high! (minimum is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low! (maximum is 150)";
}

// Stream operator
std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat) {
    out << bureaucrat.getName() << ", bureaucrat grade " 
        << bureaucrat.getGrade();
    return out;
}
```

#### Example Usage
```cpp
int main() {
    try {
        Bureaucrat bob("Bob", 2);
        std::cout << bob << std::endl;
        
        bob.incrementGrade();  // Now grade 1
        std::cout << bob << std::endl;
        
        bob.incrementGrade();  // Throws exception!
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        Bureaucrat invalid("Invalid", 151);  // Throws immediately
    } catch (Bureaucrat::GradeTooLowException& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
    
    try {
        Bureaucrat tooBad("Too Bad", 150);
        tooBad.decrementGrade();  // Throws!
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
```

#### Expected Output
```
Bob, bureaucrat grade 2
Bob, bureaucrat grade 1
Exception: Grade is too high! (minimum is 1)
Caught: Grade is too low! (maximum is 150)
Too Bad, bureaucrat grade 150
Exception: Grade is too low! (maximum is 150)
```

#### Key Design Decisions

**1. Nested exception classes**:
```cpp
class Bureaucrat {
    class GradeTooHighException : public std::exception {
        // Scoped to Bureaucrat
    };
};

// Usage: Bureaucrat::GradeTooHighException
```

**Benefits**:
- Logical grouping
- Namespace cleanliness
- Clear ownership

**2. Const name**:
```cpp
const std::string name;
```
- Bureaucrat's name cannot change
- Must initialize in constructor initializer list
- Cannot be assigned in assignment operator

**3. Grade validation**:
- Check in constructor (throw if invalid)
- Check in increment/decrement (throw if would become invalid)

#### Key Takeaways
- Exceptions provide input validation
- Nested classes organize related types
- throw() specification indicates no-throw guarantee
- Catching by reference avoids slicing

#### Common Mistakes
1. Not using throw() on what() and destructor
2. Throwing from destructor (dangerous!)
3. Not validating in constructor
4. Forgetting to check bounds before increment/decrement
5. Catching by value (causes slicing)

---

### Exercise 01: Form up, maggots!
**Files**: `Bureaucrat.{cpp,hpp}`, `Form.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Exception handling in class interactions
- Const objects and methods
- Object relationships
- Exception propagation

#### Concept
Create a `Form` class that can be signed by bureaucrats with sufficient grade.

#### Implementation

**Form.hpp**:
```cpp
#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;  // Forward declaration

class Form {
private:
    const std::string name;
    bool isSigned;
    const int gradeToSign;      // Minimum grade to sign
    const int gradeToExecute;   // Minimum grade to execute
    
public:
    Form();
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form();
    
    // Getters
    const std::string& getName() const;
    bool getSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;
    
    // Actions
    void beSigned(const Bureaucrat& bureaucrat);
    
    // Exceptions
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const Form& form);

#endif
```

**Form.cpp**:
```cpp
#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), 
      gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) {
    if (gradeToSign < 1 || gradeToExecute < 1) {
        throw GradeTooHighException();
    }
    if (gradeToSign > 150 || gradeToExecute > 150) {
        throw GradeTooLowException();
    }
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > gradeToSign) {
        throw GradeTooLowException();
    }
    isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form grade is too low!";
}

std::ostream& operator<<(std::ostream& out, const Form& form) {
    out << "Form " << form.getName()
        << ", signed: " << (form.getSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute();
    return out;
}
```

**Updated Bureaucrat.hpp**:
```cpp
class Bureaucrat {
    // ... previous members ...
    
    void signForm(Form& form);  // New method
};
```

**Updated Bureaucrat.cpp**:
```cpp
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);
        std::cout << name << " signed " << form.getName() << std::endl;
    } catch (std::exception& e) {
        std::cout << name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

#### Example Usage
```cpp
int main() {
    try {
        Bureaucrat bob("Bob", 50);
        Form form1("Tax Form", 25, 10);
        Form form2("Simple Form", 100, 50);
        
        std::cout << form1 << std::endl;
        std::cout << form2 << std::endl;
        
        bob.signForm(form1);  // Too low grade
        bob.signForm(form2);  // Success!
        
        std::cout << form2 << std::endl;
        
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    try {
        Form invalidForm("Invalid", 0, 50);  // Throws immediately
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
```

#### Expected Output
```
Form Tax Form, signed: no, grade to sign: 25, grade to execute: 10
Form Simple Form, signed: no, grade to sign: 100, grade to execute: 50
Bob couldn't sign Tax Form because Form grade is too low!
Bob signed Simple Form
Form Simple Form, signed: yes, grade to sign: 100, grade to execute: 50
Exception: Form grade is too high!
```

#### Key Takeaways
- Exceptions enable clean error handling across objects
- Try-catch in signForm() provides user-friendly messages
- Const correctness matters (beSigned takes const Bureaucrat&)
- Forward declarations resolve circular dependencies

---

### Exercise 02: No, you need form 28B, not 28C...
**Files**: `Bureaucrat.{cpp,hpp}`, `AForm.{cpp,hpp}`, `ShrubberyCreationForm.{cpp,hpp}`, `RobotomyRequestForm.{cpp,hpp}`, `PresidentialPardonForm.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Abstract base classes with exceptions
- Polymorphism with exception handling
- Template Method pattern
- Concrete implementations with specific behaviors

#### Concept
Make Form abstract (`AForm`) and create three concrete forms with different execution behaviors:
- **ShrubberyCreationForm**: Creates ASCII tree file
- **RobotomyRequestForm**: 50% chance to robotomize
- **PresidentialPardonForm**: Presidential pardon

#### Implementation

**AForm.hpp** (Abstract):
```cpp
class AForm {
private:
    const std::string name;
    bool isSigned;
    const int gradeToSign;
    const int gradeToExecute;
    
public:
    AForm(const std::string& name, int gradeToSign, int gradeToExecute);
    virtual ~AForm();
    
    // ... getters ...
    
    void beSigned(const Bureaucrat& bureaucrat);
    void execute(const Bureaucrat& executor) const;
    
    // Pure virtual - concrete forms must implement
    virtual void executeAction() const = 0;
    
    // Exceptions
    class GradeTooHighException : public std::exception {
        const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
        const char* what() const throw();
    };
    class FormNotSignedException : public std::exception {
        const char* what() const throw();
    };
};
```

**AForm.cpp**:
```cpp
void AForm::execute(const Bureaucrat& executor) const {
    if (!isSigned) {
        throw FormNotSignedException();
    }
    if (executor.getGrade() > gradeToExecute) {
        throw GradeTooLowException();
    }
    
    executeAction();  // Call pure virtual function
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "Form is not signed!";
}
```

**ShrubberyCreationForm.hpp**:
```cpp
class ShrubberyCreationForm : public AForm {
private:
    std::string target;
    
public:
    ShrubberyCreationForm(const std::string& target);
    ~ShrubberyCreationForm();
    
    void executeAction() const;  // Override
};
```

**ShrubberyCreationForm.cpp**:
```cpp
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation", 145, 137), target(target) {
}

void ShrubberyCreationForm::executeAction() const {
    std::ofstream file((target + "_shrubbery").c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Cannot create file");
    }
    
    file << "       ###" << std::endl;
    file << "      #o###" << std::endl;
    file << "    #####o###" << std::endl;
    file << "   #o#\\#|#/###" << std::endl;
    file << "    ###\\|/#o#" << std::endl;
    file << "     # }|{  #" << std::endl;
    file << "       }|{" << std::endl;
    
    file.close();
}
```

**RobotomyRequestForm.cpp**:
```cpp
RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("Robotomy Request", 72, 45), target(target) {
}

void RobotomyRequestForm::executeAction() const {
    std::cout << "* drilling noises *" << std::endl;
    
    // 50% chance of success
    srand(time(NULL));
    if (rand() % 2 == 0) {
        std::cout << target << " has been robotomized!" << std::endl;
    } else {
        std::cout << "Robotomy failed!" << std::endl;
    }
}
```

**PresidentialPardonForm.cpp**:
```cpp
PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("Presidential Pardon", 25, 5), target(target) {
}

void PresidentialPardonForm::executeAction() const {
    std::cout << target << " has been pardoned by Zaphod Beeblebrox" 
              << std::endl;
}
```

**Updated Bureaucrat**:
```cpp
void Bureaucrat::executeForm(const AForm& form) const {
    try {
        form.execute(*this);
        std::cout << name << " executed " << form.getName() << std::endl;
    } catch (std::exception& e) {
        std::cout << name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

#### Example Usage
```cpp
int main() {
    try {
        Bureaucrat bob("Bob", 1);  // Highest grade
        Bureaucrat jim("Jim", 140);
        
        ShrubberyCreationForm shrubbery("home");
        RobotomyRequestForm robotomy("Bender");
        PresidentialPardonForm pardon("Arthur Dent");
        
        // Sign forms
        bob.signForm(shrubbery);
        bob.signForm(robotomy);
        bob.signForm(pardon);
        
        // Execute forms
        bob.executeForm(shrubbery);  // Creates file
        bob.executeForm(robotomy);   // 50% success
        bob.executeForm(pardon);     // Success
        
        // Jim tries to execute (too low grade)
        jim.executeForm(pardon);  // Fails
        
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
```

#### Key Design Patterns

**Template Method Pattern**:
```cpp
// AForm defines the template
void AForm::execute(...) const {
    // 1. Check if signed
    // 2. Check executor grade
    // 3. Call executeAction() - implemented by subclass
}

// Subclass provides specific implementation
void ShrubberyCreationForm::executeAction() const {
    // Specific behavior
}
```

#### Key Takeaways
- Abstract classes define common behavior
- Pure virtual functions enforce implementation
- Template Method pattern separates validation from action
- Polymorphism enables uniform handling of different forms

---

### Exercise 03: At least this beats coffee-making
**Files**: Previous + `Intern.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Factory pattern
- Dynamic object creation
- Array of function pointers
- Error handling in factory methods

#### Concept
Create an `Intern` class that can create any form by name.

#### Implementation

**Intern.hpp**:
```cpp
class Intern {
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();
    
    AForm* makeForm(const std::string& formName, 
                    const std::string& target);
    
private:
    AForm* createShrubbery(const std::string& target);
    AForm* createRobotomy(const std::string& target);
    AForm* createPardon(const std::string& target);
};
```

**Intern.cpp**:
```cpp
AForm* Intern::createShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, 
                        const std::string& target) {
    // Array of form names
    std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    // Array of creation functions (function pointers)
    AForm* (Intern::*creators[])(const std::string&) = {
        &Intern::createShrubbery,
        &Intern::createRobotomy,
        &Intern::createPardon
    };
    
    // Find and create
    for (int i = 0; i < 3; i++) {
        if (formNames[i] == formName) {
            std::cout << "Intern creates " << formName << std::endl;
            return (this->*creators[i])(target);
        }
    }
    
    std::cout << "Intern cannot create form: " << formName << std::endl;
    return NULL;
}
```

#### Example Usage
```cpp
int main() {
    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);
    
    AForm* form1 = someRandomIntern.makeForm("robotomy request", "Bender");
    AForm* form2 = someRandomIntern.makeForm("presidential pardon", "Arthur");
    AForm* form3 = someRandomIntern.makeForm("unknown form", "Target");
    
    if (form1) {
        boss.signForm(*form1);
        boss.executeForm(*form1);
        delete form1;
    }
    
    if (form2) {
        boss.signForm(*form2);
        boss.executeForm(*form2);
        delete form2;
    }
    
    if (form3) {
        delete form3;  // Won't happen
    }
    
    return 0;
}
```

#### Member Function Pointers
```cpp
// Declaration
AForm* (Intern::*funcPtr)(const std::string&);

// Assignment
funcPtr = &Intern::createShrubbery;

// Calling
AForm* form = (this->*funcPtr)("target");
// or
AForm* form = (intern.*funcPtr)("target");
```

#### Key Takeaways
- Factory pattern centralizes object creation
- Function pointer arrays eliminate switch/if-else chains
- Returning NULL for unknown forms (or could throw exception)
- Caller must manage returned pointer (delete)

---

## 🎓 Best Practices

### 1. Exception Safety Checklist

```cpp
class Safe {
private:
    Resource* resource;
    
public:
    Safe() : resource(NULL) {
        resource = new Resource();  // Might throw
        // If throws, destructor won't be called
        // Resource would leak if constructor allocated before this
    }
    
    ~Safe() {
        delete resource;  // Must not throw!
    }
    
    void operation() {
        Resource* temp = new Resource();  // Allocate new
        delete resource;                  // Delete old
        resource = temp;                  // Assign
        // Strong exception guarantee
    }
};
```

### 2. RAII (Resource Acquisition Is Initialization)

```cpp
class File {
private:
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
            file.close();  // Always cleanup
        }
    }
    
    // No need for manual cleanup!
};
```

### 3. Catch by Reference

```cpp
// Wrong - slicing
catch (std::exception e) {
    // Derived class information lost
}

// Right - polymorphic
catch (std::exception& e) {
    // Full derived class behavior
}

// Also right - prevents modification
catch (const std::exception& e) {
    // Const reference
}
```

### 4. Exception Hierarchies

```cpp
class MyException : public std::exception { };
class SpecificException : public MyException { };

try {
    throw SpecificException();
} catch (SpecificException& e) {
    // Catches specific
} catch (MyException& e) {
    // Catches general MyException
} catch (std::exception& e) {
    // Catches all standard exceptions
} catch (...) {
    // Catches everything
}
```

---

## 🔗 Building on CPP_04

CPP_04 taught polymorphism. CPP_05 extends this with:
- ✅ Exception handling for error management
- ✅ Custom exception classes
- ✅ Exception-safe code practices
- ✅ Factory pattern with exceptions

---

## 🚀 Beyond CPP_05

You've completed the foundational C++ modules! Next topics might include:
- **CPP_06**: Type casting (static_cast, dynamic_cast, reinterpret_cast, const_cast)
- **CPP_07**: Templates and generic programming
- **CPP_08**: STL containers, iterators, algorithms
- **Advanced topics**: Smart pointers, move semantics, lambda functions

---

## 🐛 Common Pitfalls

1. **Throwing from destructor**:
   ```cpp
   ~MyClass() {
       throw std::exception();  // NEVER DO THIS!
       // If destructor called during stack unwinding, program terminates
   }
   ```

2. **Catching by value**:
   ```cpp
   catch (std::exception e) {  // Slicing!
       // Loses derived class information
   }
   ```

3. **Memory leaks with exceptions**:
   ```cpp
   void func() {
       int* ptr = new int[100];
       riskyOperation();  // Might throw
       delete[] ptr;      // Never reached if exception thrown!
   }
   
   // Solution: RAII
   void func() {
       std::vector<int> vec(100);  // Automatic cleanup
       riskyOperation();
   }
   ```

4. **Not checking return values**:
   ```cpp
   AForm* form = intern.makeForm("unknown", "target");
   form->execute(bureaucrat);  // Crash if form is NULL!
   
   // Always check:
   if (form) {
       form->execute(bureaucrat);
       delete form;
   }
   ```

5. **Exception specification violations**:
   ```cpp
   void func() throw() {  // Says: never throws
       throw std::exception();  // But it does!
       // Calls std::unexpected() → program termination
   }
   ```

---

## 🎯 Summary

Module 05 covers exception handling:
- ✅ Try-catch blocks for error handling
- ✅ Throwing exceptions
- ✅ Custom exception classes
- ✅ Exception hierarchies
- ✅ Exception safety guarantees
- ✅ Stack unwinding
- ✅ RAII pattern

**Key Concepts**:
- Exceptions separate error handling from normal flow
- Always catch by reference
- Custom exceptions inherit from std::exception
- Mark what() and destructor as throw()
- RAII ensures cleanup even with exceptions
- Never throw from destructors

**Remember**:
```cpp
// Define exception
class MyException : public std::exception {
    const char* what() const throw() {
        return "My error message";
    }
};

// Throw exception
throw MyException();

// Catch exception
try {
    riskyCode();
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

**Congratulations! You've mastered the C++ fundamentals!** 🎉

You now understand:
- Classes and OOP
- Memory management
- Operator overloading
- Inheritance
- Polymorphism
- Exception handling

**These skills form the foundation for advanced C++ development. Keep practicing and building!** 🚀
