# High-Performance C++ Template Vector

A robust, custom implementation of a dynamic array (Vector) in C++ that mirrors the functionality of `std::vector`. This project focuses on memory efficiency through **Move Semantics**, **Strong Exception Guarantees**, and a custom **Iterator** system.

## 🚀 Key Features

* **Move Semantics ($O(1)$ Reallocation):** Uses `std::move` during vector resizing to "steal" resources instead of deep-copying, significantly boosting performance for complex types.
* **The Rule of Five:** Implements Copy Constructor, Copy Assignment, Move Constructor, Move Assignment, and Destructor for perfect memory management.
* **Strong Exception Safety:** Designed to leave the container in its original state if a memory allocation fails during a growth operation.
* **Custom Iterators:** Full support for STL-style iteration, including pointer arithmetic and range-based `for` loops.
* **Template Support:** Works with any data type, from primitives like `int` to complex objects like `std::string` or even nested `Vector<Vector<T>>`.



---

## 🛠 Technical Implementation Details

### Move Constructor & Assignment
By marking move operations as `noexcept`, this class allows the compiler to optimize transfers of data without the overhead of copying.

### Exception Handling
The class uses standard C++ exceptions to handle edge cases:
- `std::out_of_range`: Thrown during invalid index access or iterator bounds violations.
- `std::bad_alloc`: Automatically propagated if the system runs out of memory during a `new` allocation.

### Memory Management
The class manages its own heap memory using `new[]` and `delete[]`. It includes a `shrinktofit()` method to reduce memory usage to the current size and a `reserve()` method to prevent unnecessary reallocations.


### How to Compile and Run:
* Run this by command normally using `g++ file_name.cpp -o my_program` as done here in the Basic Example of "Vector.hpp" file (Not a good practice).
* If you have separated files for each class i.e separate classes for List , Node , Iterator and then include all the necessary headers in your file then you need to run by including all the .cpp files like below example:
  `g++ file_name.cpp Vector.cpp Iterator.cpp -o my_program`
Although it works by both methods , the choice depends on your design and style you prefer in working environment which makes ease for you.

---

## 💻 Usage Example

```cpp
#include "Vector.hpp"

int main()
{
    // Initialization via Initializer List
    Vector<std::string> heroes = {"Batman", "Superman", "Wonder Woman"};

    // Dynamic Growth
    heroes.push_back("Flash");

    // Standard Iteration
    for (auto& hero : heroes)
    {
        std::cout << hero << std::endl;
    }

    // Safe access with bounds checking
    try
    {
        std::cout << heroes.at(10); 
    } catch (const std::out_of_range& e)
    {
        std::cerr << "Error: " << e.what();
    }

    return 0;
}
