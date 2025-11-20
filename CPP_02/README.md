# CPP Module 02 - Ad-hoc Polymorphism and Operator Overloading

## 📚 Module Overview

Module 02 introduces **operator overloading** and the **Orthodox Canonical Form** (OCF). You'll learn how to make your custom classes behave like built-in types by overloading operators, and you'll implement a fixed-point number class to understand low-level numeric representation.

### What You'll Learn
- Operator overloading (`+`, `-`, `*`, `/`, `<<`, etc.)
- The Orthodox Canonical Form (OCF)
- Copy constructor in depth
- Assignment operator overload
- Fixed-point arithmetic
- Increment/decrement operators (prefix and postfix)
- Comparison operators
- Ad-hoc polymorphism vs. parametric polymorphism

---

## 🎯 Key Concepts Explained

### 1. Orthodox Canonical Form (OCF)

Every class should implement these four essential functions:

```cpp
class Fixed {
public:
    Fixed();                            // 1. Default constructor
    Fixed(const Fixed& other);          // 2. Copy constructor
    Fixed& operator=(const Fixed& other); // 3. Copy assignment operator
    ~Fixed();                           // 4. Destructor
};
```

**Why is this important?**
- Ensures your class can be copied safely
- Prevents shallow copy issues (remember from CPP_00?)
- Makes objects behave predictably
- Required for RAII (Resource Acquisition Is Initialization)

### 2. Copy Constructor vs. Assignment Operator

```cpp
Fixed a;
Fixed b(a);    // Copy constructor: b is being created
Fixed c = a;   // Copy constructor: c is being created (not assignment!)

Fixed d;
d = a;         // Assignment operator: d already exists
```

**Key Difference**:
- **Copy Constructor**: Creates a new object from an existing one
- **Assignment Operator**: Overwrites an existing object with another's values

### 3. Operator Overloading Syntax

```cpp
class Fixed {
public:
    // Member function (left operand is 'this')
    Fixed operator+(const Fixed& rhs) const {
        Fixed result;
        result.value = this->value + rhs.value;
        return result;
    }
    
    // Friend function (for non-member operators)
    friend std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
};

// Non-member implementation
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
```

### 4. Fixed-Point Numbers

Fixed-point representation stores decimal numbers using integers:

```
Number = (integer_value) / (2^fractional_bits)
```

**Example** with 8 fractional bits:
- `42.42` stored as integer: `42.42 × 256 = 10859`
- Retrieved: `10859 / 256 = 42.41796875`

**Why use fixed-point?**
- Faster than floating-point on some hardware
- Predictable precision
- No floating-point rounding errors
- Historical importance (older game consoles, embedded systems)

### 5. Increment/Decrement Operators

```cpp
class Fixed {
public:
    // Prefix: ++a (returns reference)
    Fixed& operator++() {
        value++;
        return *this;
    }
    
    // Postfix: a++ (returns copy, int parameter is just a marker)
    Fixed operator++(int) {
        Fixed temp(*this);  // Save current value
        value++;            // Increment
        return temp;        // Return old value
    }
};
```

**Usage difference**:
```cpp
Fixed a(5);
++a;  // a becomes 6, returns 6
a++;  // a becomes 7, returns 6 (old value)
```

---

## 💻 Exercise Breakdown

### Exercise 00: My First Class in Orthodox Canonical Form
**Files**: `Fixed.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Orthodox Canonical Form (OCF)
- Copy constructor implementation
- Assignment operator implementation
- Understanding shallow vs. deep copy
- Static member variables

#### Concept
Implement a Fixed-point number class with:
- An integer to store the fixed-point value
- A static constant for the number of fractional bits (8)
- OCF functions

#### Implementation

```cpp
class Fixed {
private:
    int rawBits;                      // Fixed-point value
    static const int fractionalBits = 8;  // Number of fractional bits
    
public:
    // Orthodox Canonical Form
    Fixed();                          // Default constructor
    Fixed(const Fixed& other);        // Copy constructor
    Fixed& operator=(const Fixed& other);  // Assignment operator
    ~Fixed();                         // Destructor
    
    // Getters/Setters
    int getRawBits() const;
    void setRawBits(int const raw);
};
```

#### Key Implementations

**My Actual Implementation:**

**Default Constructor**:
```cpp
Fixed::Fixed ()
{
	std::cout << "Default constructor called" << std::endl;
	this->fp_value = 0;
}
```

**Copy Constructor**:
```cpp
Fixed::Fixed (const Fixed &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;  // Reuse assignment operator
}
```

Note: I reuse the assignment operator in the copy constructor. This is a common pattern that ensures consistency.

**Assignment Operator**:
```cpp
Fixed& Fixed::operator=(const Fixed &obj)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &obj)  // Check for self-assignment
	{
		this->fp_value = obj.getRawBits();
	}
	return (*this);  // Return reference for chaining (a = b = c)
}
```

Key points:
- Always check for self-assignment (`if (this != &obj)`)
- Return `*this` to allow chaining
- Use `getRawBits()` to access private member of `other`

**Destructor**:
```cpp
Fixed::~Fixed ()
{
	std::cout << "Destructor called" << std::endl;
}
```

#### Expected Output
When running the provided main:
```
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
```

#### Key Observations

1. **Copy constructor vs. Assignment**:
   ```cpp
   Fixed a;
   Fixed b(a);    // Copy constructor
   Fixed c;
   c = a;         // Assignment operator
   ```

2. **Self-assignment check**:
   ```cpp
   if (this != &other) { /* ... */ }
   ```
   Prevents issues when someone does `a = a;`

3. **Return *this**:
   Enables chaining: `a = b = c;`

#### Common Mistakes
1. Not checking for self-assignment
2. Not returning `*this` from assignment operator
3. Forgetting to initialize members in constructors
4. Shallow copy (not an issue here, but critical with pointers)

---

### Exercise 01: Towards a more useful fixed-point number class
**Files**: `Fixed.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Type conversion constructors
- Converting between int, float, and fixed-point
- Bit shifting for fixed-point arithmetic
- Const member functions
- Operator overloading introduction (`<<`)

#### Concept
Extend the Fixed class with:
- Constructor from int
- Constructor from float
- Conversion to float
- Conversion to int
- Stream insertion operator (`<<`)

#### Implementation

```cpp
class Fixed {
private:
    int rawBits;
    static const int fractionalBits = 8;
    
public:
    // OCF
    Fixed();
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();
    
    // New constructors
    Fixed(const int value);
    Fixed(const float value);
    
    // Conversion functions
    float toFloat() const;
    int toInt() const;
    
    // Getters/Setters
    int getRawBits() const;
    void setRawBits(int const raw);
};

// Stream insertion operator (must be non-member)
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
```

#### Key Implementations

**Constructor from int**:
```cpp
Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << std::endl;
    // Shift left by fractionalBits to convert to fixed-point
    rawBits = value << fractionalBits;
}
```

**Why left shift?**
- `value << 8` is equivalent to `value × 2^8` or `value × 256`
- Example: `42 << 8 = 10752` (which represents 42.0 in fixed-point)

**Constructor from float**:
```cpp
Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << std::endl;
    // Multiply by 2^fractionalBits and round
    rawBits = roundf(value * (1 << fractionalBits));
}
```

**Why roundf?**
- Converts float to nearest integer
- Reduces rounding errors
- `1 << fractionalBits` is `2^8 = 256`

**To Float conversion**:
```cpp
float Fixed::toFloat() const {
    // Divide by 2^fractionalBits
    return (float)rawBits / (1 << fractionalBits);
}
```

**To Int conversion**:
```cpp
int Fixed::toInt() const {
    // Shift right to remove fractional part
    return rawBits >> fractionalBits;
}
```

**Stream insertion operator**:
```cpp
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
```

**Why non-member?**
- Left operand is `std::ostream`, not `Fixed`
- Can't add members to `std::ostream`
- Must be non-member (often declared as `friend`)

#### Example Usage
```cpp
Fixed a;
Fixed const b(10);
Fixed const c(42.42f);
Fixed const d(b);

a = Fixed(1234.4321f);

std::cout << "a is " << a << std::endl;
std::cout << "b is " << b << std::endl;
std::cout << "c is " << c << std::endl;
std::cout << "d is " << d << std::endl;

std::cout << "a is " << a.toInt() << " as integer" << std::endl;
std::cout << "b is " << b.toInt() << " as integer" << std::endl;
std::cout << "c is " << c.toInt() << " as integer" << std::endl;
std::cout << "d is " << d.toInt() << " as integer" << std::endl;
```

#### Expected Output
```
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
```

#### Key Takeaways
- Bit shifting is used for efficient fixed-point conversion
- `<<` shifts left (multiply by power of 2)
- `>>` shifts right (divide by power of 2)
- `roundf()` prevents truncation errors
- Stream operators enable `cout << object`

---

### Exercise 02: Now we're talking
**Files**: `Fixed.{cpp,hpp}`, `main.cpp`

#### What It Teaches
- Arithmetic operator overloading (`+`, `-`, `*`, `/`)
- Comparison operator overloading (`>`, `<`, `>=`, `<=`, `==`, `!=`)
- Increment/decrement operators (prefix and postfix)
- Static member functions (`min`, `max`)

#### Concept
Make the Fixed class fully functional with all arithmetic operations.

#### Implementation

**Comparison Operators**:
```cpp
class Fixed {
public:
    bool operator>(const Fixed& rhs) const {
        return rawBits > rhs.rawBits;
    }
    
    bool operator<(const Fixed& rhs) const {
        return rawBits < rhs.rawBits;
    }
    
    bool operator>=(const Fixed& rhs) const {
        return rawBits >= rhs.rawBits;
    }
    
    bool operator<=(const Fixed& rhs) const {
        return rawBits <= rhs.rawBits;
    }
    
    bool operator==(const Fixed& rhs) const {
        return rawBits == rhs.rawBits;
    }
    
    bool operator!=(const Fixed& rhs) const {
        return rawBits != rhs.rawBits;
    }
};
```

**Arithmetic Operators**:
```cpp
class Fixed {
public:
    Fixed operator+(const Fixed& rhs) const {
        return Fixed(this->toFloat() + rhs.toFloat());
    }
    
    Fixed operator-(const Fixed& rhs) const {
        return Fixed(this->toFloat() - rhs.toFloat());
    }
    
    Fixed operator*(const Fixed& rhs) const {
        return Fixed(this->toFloat() * rhs.toFloat());
    }
    
    Fixed operator/(const Fixed& rhs) const {
        return Fixed(this->toFloat() / rhs.toFloat());
    }
};
```

**Alternative arithmetic (more efficient, direct manipulation)**:
```cpp
Fixed operator+(const Fixed& rhs) const {
    Fixed result;
    result.rawBits = this->rawBits + rhs.rawBits;
    return result;
}

Fixed operator*(const Fixed& rhs) const {
    Fixed result;
    // Multiply and shift back
    result.rawBits = (this->rawBits * rhs.rawBits) >> fractionalBits;
    return result;
}
```

**Increment/Decrement Operators**:
```cpp
class Fixed {
public:
    // Prefix increment: ++a
    Fixed& operator++() {
        rawBits++;  // Smallest representable epsilon (1/256)
        return *this;
    }
    
    // Postfix increment: a++
    Fixed operator++(int) {
        Fixed temp(*this);
        ++(*this);  // Reuse prefix version
        return temp;
    }
    
    // Prefix decrement: --a
    Fixed& operator--() {
        rawBits--;
        return *this;
    }
    
    // Postfix decrement: a--
    Fixed operator--(int) {
        Fixed temp(*this);
        --(*this);
        return temp;
    }
};
```

**Static Min/Max Functions**:
```cpp
class Fixed {
public:
    static Fixed& min(Fixed& a, Fixed& b) {
        return (a < b) ? a : b;
    }
    
    static const Fixed& min(const Fixed& a, const Fixed& b) {
        return (a < b) ? a : b;
    }
    
    static Fixed& max(Fixed& a, Fixed& b) {
        return (a > b) ? a : b;
    }
    
    static const Fixed& max(const Fixed& a, const Fixed& b) {
        return (a > b) ? a : b;
    }
};
```

**Why two versions of min/max?**
- One for non-const objects
- One for const objects
- Preserves const-correctness

#### Example Usage
```cpp
Fixed a;
Fixed const b(Fixed(5.05f) * Fixed(2));

std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;

std::cout << b << std::endl;

std::cout << Fixed::max(a, b) << std::endl;
```

#### Expected Output
```
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
```

#### Understanding the Output

1. `++a` increments by smallest value: `1/256 ≈ 0.00390625`
2. `a++` returns old value before increment
3. `5.05 × 2 = 10.1` (with minor fixed-point precision)

#### Operator Overloading Best Practices

1. **Return types**:
   - Comparison operators: `bool`
   - Arithmetic operators: `Fixed` (new object)
   - Prefix increment: `Fixed&` (reference to modified object)
   - Postfix increment: `Fixed` (copy of old value)

2. **Const correctness**:
   ```cpp
   bool operator==(const Fixed& rhs) const;
   //                               ^^^^^ method doesn't modify object
   //               ^^^^^^ parameter won't be modified
   ```

3. **Self-increment in postfix**:
   ```cpp
   Fixed operator++(int) {
       Fixed temp(*this);
       ++(*this);      // Reuse prefix version
       return temp;
   }
   ```

4. **Return by reference when possible**:
   ```cpp
   Fixed& operator++() {  // Returns reference (no copy)
       rawBits++;
       return *this;
   }
   ```

#### Common Mistakes
1. Wrong return type for operators
2. Forgetting `const` on read-only methods
3. Not implementing both const and non-const versions of static functions
4. Integer overflow in multiplication without proper shifting
5. Not handling division by zero

---

## 🎓 Advanced Topics

### Ad-hoc Polymorphism vs. Other Types

**Ad-hoc Polymorphism** (this module):
- Operator overloading
- Function overloading
- Same operation, different implementations based on type
- Resolved at compile-time

```cpp
Fixed a(5), b(3);
int x = 5, y = 3;

std::cout << a + b;  // Calls Fixed::operator+
std::cout << x + y;  // Uses built-in int addition
```

**Parametric Polymorphism** (templates - CPP_07):
```cpp
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}
```

**Subtype Polymorphism** (inheritance - CPP_03/04):
```cpp
class Animal {
    virtual void makeSound() = 0;
};

class Dog : public Animal {
    void makeSound() { std::cout << "Woof!"; }
};
```

---

## 🎯 Best Practices

### 1. OCF Implementation Checklist
```cpp
class MyClass {
public:
    // Default constructor
    MyClass() : value(0) {}
    
    // Copy constructor
    MyClass(const MyClass& other) : value(other.value) {}
    
    // Assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }
    
    // Destructor
    ~MyClass() {}
    
private:
    int value;
};
```

### 2. Operator Overloading Guidelines

**Do overload** when:
- It makes the code more readable
- The operation is intuitive
- Follows mathematical conventions

**Don't overload** when:
- The meaning is unclear
- It violates expectations (e.g., `+` for subtraction)
- It makes debugging harder

**Good examples**:
- `+`, `-`, `*`, `/` for arithmetic types
- `<<`, `>>` for streams
- `[]` for array-like access
- `==`, `!=` for comparisons

**Bad examples**:
- `+` for printing
- `*` for unrelated operations
- Overloading `&&`, `||` (can break short-circuit evaluation)

### 3. Const Correctness
```cpp
class Fixed {
public:
    // Const method - doesn't modify object
    float toFloat() const {
        return (float)rawBits / (1 << fractionalBits);
    }
    
    // Non-const method - modifies object
    void setRawBits(int raw) {
        rawBits = raw;
    }
};

// Const object can only call const methods
const Fixed a(42);
float f = a.toFloat();  // OK
a.setRawBits(100);      // ERROR - can't call non-const method
```

---

## 🔗 Building on CPP_01

CPP_01 taught memory management and object lifetime. CPP_02 extends this with:
- ✅ Deep understanding of copying (copy constructor vs. assignment)
- ✅ Making custom types behave like built-in types
- ✅ Operator overloading for intuitive code
- ✅ Fixed-point arithmetic as a practical example

---

## 🚀 Preparing for CPP_03

You've learned how to make one class work well. Next:
- **Inheritance**: Creating class hierarchies
- **Protected members**: Sharing with derived classes
- **Constructor/destructor chains**: How they work with inheritance
- **Virtual functions**: First step toward polymorphism

---

## 🐛 Common Pitfalls

1. **Self-assignment without check**:
   ```cpp
   Fixed& operator=(const Fixed& other) {
       // Missing check!
       rawBits = other.rawBits;
       return *this;
   }
   
   Fixed a;
   a = a;  // Could cause issues with more complex classes
   ```

2. **Wrong return type**:
   ```cpp
   // Wrong - should return reference
   Fixed operator++() {
       rawBits++;
       return *this;  // Returns copy, not reference!
   }
   ```

3. **Forgetting const**:
   ```cpp
   float toFloat() {  // Should be const!
       return (float)rawBits / 256;
   }
   ```

4. **Precision loss**:
   ```cpp
   Fixed a(42.99999f);
   std::cout << a.toInt();  // Outputs 42, lost decimal part
   ```

5. **Operator chaining broken**:
   ```cpp
   // Wrong - doesn't return *this
   void operator=(const Fixed& other) {
       rawBits = other.rawBits;
   }
   
   // Can't do: a = b = c;
   ```

---

## 🎯 Summary

Module 02 covers operator overloading and the Orthodox Canonical Form:
- ✅ OCF: Default constructor, copy constructor, assignment operator, destructor
- ✅ Operator overloading: arithmetic, comparison, increment/decrement
- ✅ Type conversion: int ↔ Fixed ↔ float
- ✅ Fixed-point arithmetic: bit shifting and precision
- ✅ Stream insertion operator
- ✅ Static member functions

**Key Lessons**:
- Always implement the full OCF for robustness
- Operator overloading makes code intuitive but use it wisely
- Bit shifting is efficient for power-of-2 operations
- Return types and const correctness matter

**You can now create classes that behave like built-in types!** 🎉
