# CPP Module 02 - Operator Overloading and Orthodox Canonical Form

## 🎯 New Concepts in This Module

### Orthodox Canonical Form (OCF)
Every class should implement these four essential methods:

```cpp
class Fixed {
public:
    Fixed();                            // 1. Default constructor
    Fixed(const Fixed& other);          // 2. Copy constructor
    Fixed& operator=(const Fixed& other); // 3. Copy assignment operator
    ~Fixed();                           // 4. Destructor
};
```

**Why?** Ensures your class can be safely copied and assigned.

### Copy Constructor vs Assignment Operator

```cpp
Fixed a;
Fixed b(a);    // Copy constructor - b is being created from a
Fixed c = a;   // Copy constructor - c is being created (not assignment!)

Fixed d;
d = a;         // Assignment operator - d already exists, overwrite it
```

**Copy Constructor**: Creates a new object as a copy
**Assignment Operator**: Overwrites an existing object

### Copy Constructor Implementation
```cpp
Fixed::Fixed(const Fixed& other) {
    *this = other;  // Reuse assignment operator
    // OR manually copy each member:
    // this->value = other.value;
}
```

### Assignment Operator Implementation
```cpp
Fixed& Fixed::operator=(const Fixed& other) {
    if (this != &other) {  // Check for self-assignment
        this->value = other.value;
    }
    return *this;  // Return *this for chaining (a = b = c)
}
```

**Critical points:**
- Always check for self-assignment (`if (this != &other)`)
- Return `*this` to enable chaining
- Return by reference (avoid copying)

### Operator Overloading
Make your classes work with operators like built-in types:

**Arithmetic Operators:**
```cpp
class Fixed {
public:
    Fixed operator+(const Fixed& rhs) const {
        Fixed result;
        result.value = this->value + rhs.value;
        return result;
    }
    
    Fixed operator-(const Fixed& rhs) const { /* ... */ }
    Fixed operator*(const Fixed& rhs) const { /* ... */ }
    Fixed operator/(const Fixed& rhs) const { /* ... */ }
};
```

**Comparison Operators:**
```cpp
bool operator>(const Fixed& rhs) const {
    return this->value > rhs.value;
}

bool operator<(const Fixed& rhs) const { /* ... */ }
bool operator>=(const Fixed& rhs) const { /* ... */ }
bool operator<=(const Fixed& rhs) const { /* ... */ }
bool operator==(const Fixed& rhs) const { /* ... */ }
bool operator!=(const Fixed& rhs) const { /* ... */ }
```

**Increment/Decrement Operators:**
```cpp
// Prefix: ++a (returns reference)
Fixed& operator++() {
    value++;
    return *this;
}

// Postfix: a++ (int parameter is just a marker, returns copy)
Fixed operator++(int) {
    Fixed temp(*this);  // Save current value
    ++(*this);          // Use prefix version
    return temp;        // Return old value
}
```

**Stream Insertion Operator:**
```cpp
// Must be non-member (left operand is std::ostream, not your class)
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
```

### Fixed-Point Arithmetic
Represent decimal numbers using integers for efficiency:

```cpp
class Fixed {
private:
    int value;                        // Stores the fixed-point value
    static const int fractionalBits = 8;  // Number of fractional bits
    
public:
    Fixed(int num) {
        value = num << fractionalBits;  // Shift left to convert
    }
    
    Fixed(float num) {
        value = roundf(num * (1 << fractionalBits));
    }
    
    float toFloat() const {
        return (float)value / (1 << fractionalBits);
    }
    
    int toInt() const {
        return value >> fractionalBits;  // Shift right to convert
    }
};
```

**How it works:**
- `42` (int) stored as `42 << 8 = 10752`
- `42.5` (float) stored as `roundf(42.5 × 256) = 10880`
- Retrieved: `10880 >> 8 = 42` (toInt) or `10880 / 256.0 = 42.5` (toFloat)

### Static Member Functions
Functions that don't need an instance:

```cpp
class Fixed {
public:
    static Fixed& min(Fixed& a, Fixed& b) {
        return (a < b) ? a : b;
    }
    
    static const Fixed& min(const Fixed& a, const Fixed& b) {
        return (a < b) ? a : b;
    }
};

// Usage
Fixed a(5), b(10);
Fixed& smaller = Fixed::min(a, b);  // Returns reference to a
```

## 💡 What You'll Build
- **ex00**: Fixed-point class with OCF
- **ex01**: Add int/float constructors and conversions
- **ex02**: Complete with all operators and static min/max

## 📋 Quick Reference

### OCF Template
```cpp
class MyClass {
public:
    MyClass();                           // Default constructor
    MyClass(const MyClass& other);       // Copy constructor
    MyClass& operator=(const MyClass& other); // Assignment operator
    ~MyClass();                          // Destructor
};
```

### Operator Overloading Return Types
```cpp
bool operator==(const T& rhs) const;      // Comparison → bool
T operator+(const T& rhs) const;          // Arithmetic → new object
T& operator++();                          // Prefix ++ → reference
T operator++(int);                        // Postfix ++ → copy
std::ostream& operator<<(std::ostream&, const T&); // Stream → stream&
```

### Bit Shifting for Powers of 2
```cpp
x << n  // Multiply by 2^n
x >> n  // Divide by 2^n

5 << 3  // 5 × 2^3 = 5 × 8 = 40
40 >> 3 // 40 / 2^3 = 40 / 8 = 5
```

### Common Mistakes to Avoid
- Not checking for self-assignment in operator=
- Not returning `*this` from assignment operator
- Wrong return type for operators (value vs reference)
- Forgetting `const` on methods that don't modify the object
- Using `delete` instead of `delete[]` for arrays
- Arithmetic without considering overflow

---

**Previous Module**: CPP_01 covered memory management and pointers/references  
**Next Module**: CPP_03 covers inheritance
