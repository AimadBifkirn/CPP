#  CPP Module 07
## Templates

Templates are C++ feature that enables **generic programing**, allowing to write functions and classes that work with any data typ, avoiding code duplicating.

### Types of Templates
1. Function Templates:
 Define a family of functions with the same logic but different data types.
 **Syntax:**
 ```CPP
 template <typename T>
 T add (T N1, T N2)
 {
    return (N1 + N2);
 }
 ```
 this template defines a function add that will work with all data types.
 You can call it for different types, and the compiler automatically shoses the type:
 ```CPP
 int i = add (1, 2); // T is int
 float f = add (2.1, 3.5); // T is float
```
The **typename** keyword (or **class** keyword) is used to specify a generic type parameter.