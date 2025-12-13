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

2. Class Templates:

   Define a family of classes with the same logic but different data types.

   **syntax:**

   ```CPP
   template <typename T>
   class test
   {
      public:
         T value;
         test (T arg) : value(arg) {};
   };
   ```
   You must explicitly specify the type when creating an object with this template class.
   ```CPP
   test a(1); // compiler error
   test<int> b(1337); // ok !
   test<std::string> c("this is a test!"); // ok !
   ```

3. Variable Templates: _(Since C++14)_

   A single variable definition that can be used with different types.

   **syntaX:**

   ```CPP
   template <typename T>
   T pi = T(3.141592653589793);
   ```
   you can use it like this:
   ```CPP
   double d = pi<double>;
   float f = pi<float>;
   int i = pi<int>; //  = 3
   ```

### Template specialization

Template specialization means writing a special version of a template for a specific type when the general version is not good enough.

- Lets have an example

   **General template**

   ```CPP
   template <typename T>
   void printValue (T value)
   {
      std::cout << value << std::endl;
   }
   ```
   This works fine for most types, but let's say we want a deferent behaivior when it comes to bool type.

   **Specialized version (for bool)**

   ```CPP
   template <> // Empty angle brackets signal that this is a specialization, not a general template
   void printValue<bool> (bool value) // printValue<bool> : Specifies the exact type we are specializing for (bool) | bool value : Parameter is now specific to bool, instead of generic T
   {
      std::cout << (value ? "true" : "false") << std::endl;
   }
   ```

   **Usage**
   ```CPP
   printValue(5); // general template
   printValue(true); // specialized template
   ```
