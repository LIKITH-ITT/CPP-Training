# Coding Guidelines

These guidelines define the coding style, structure, and practices followed in this repository.  
They are derived strictly from the existing codebase and reflect how the programs are actually written.

---

## 1. Language & Standards
- Programming Language: C++
- Commonly used headers:
  - <iostream>
  - <string> (when required)
- Code follows a procedural programming style

---

## 2. File Structure
Each .cpp file follows this order:
1. #include statements
2. User-defined functions
3. main() function

Example:

    #include <iostream>

    void helperFunction() {
        // logic
    }

    int main() {
        // program flow
    }

---

## 3. Naming Conventions

### Variables
- Descriptive, meaningful names in camelCase are used:

    int number, option;
    float numerator, divisor;
    bool decimal, negative;

### Functions
- camelCase naming is followed with name starting from a verb:

    convertStringToFloat()
    printPattern()

### Indexing
- Use meaningful names instead of i, j

---

## 4. Input & Output Handling

### Input
- cin is used for numeric values
- getline() is used for string input

### Output
- cout is used with clear and descriptive messages

Example:

    cout << "Enter the size of the pattern:";
    cin >> n;

---

## 5. Menu-Driven Program Structure
- Programs use infinite loops for continuous execution:

    while(true)

- User choices are handled using switch-case
- Program termination:

    Use a bool variable to terminate

---

## 6. Formatting & Indentation
- Indentation: 4 spaces
- Blank lines separate logical blocks
- Code is formatted for readability and clarity
