# OEM Language Tokenizer

This project is a **custom tokenizer** designed to support a **Roman Urdu-based programming language**. The tokenizer reads source code written in Roman Urdu, tokenizes it, and classifies it into various categories, such as reserved words, data types, operators, booleans, and punctuations. This allows Roman Urdu speakers to write code in their native language.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Tokenization](#tokenization)
  - [Reserved Words](#reserved-words)
  - [Data Types](#data-types)
  - [Operators](#operators)
  - [Booleans](#booleans)
  - [Punctuation](#punctuation)
- [Regex](#regex)
- [Example](#example)
- [Supported Tokens](#supported-tokens)
  - [Reserved Words](#reserved-words-1)
  - [Data Types](#data-types-1)
  - [Operators](#operators-1)
  - [Booleans](#booleans-1)
  - [Punctuation](#punctuation-1)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Features

- **Custom Tokenization:** The tokenizer tokenizes source code into various token types such as reserved words, data types, operators, values, booleans, and punctuation.
- **Roman Urdu Syntax:** Supports key programming features like `if`, `else`, `while`, `break`, and `return`, all written in Roman Urdu.
- **Regex-Based Matching:** Uses regular expressions to identify patterns for identifiers, operators, and other tokens.
- **Code Categorization:** Categorizes code into multiple types, providing a clear structure to the parsed program.

---

## Installation

1. **Clone the Repository:**
   Clone the repository to your local machine.

2. **Compile the Code:**
   Use `g++` or any C++ compiler to compile the source code.

   ```bash
   g++ main.cpp -o tokenizer
   ```

3. **Run the Tokenizer:**
   After compiling the code, run the tokenizer by providing a file name (without extension) that contains the source code.

   ```bash
   ./tokenizer
   ```

   Enter the file name (e.g., `program`) when prompted. The source file should be placed in the `programs/` directory and have a `.oem` extension.

---

## Tokenization

The core of this compiler is **tokenization**, where the input source code is broken down into **tokens** that are categorized based on their type. The program identifies various components such as reserved words, data types, operators, and booleans.

### Reserved Words
Reserved words are predefined keywords that have special meanings in the language. In this tokenizer, we have the following Roman Urdu reserved words:

| Roman Urdu Keyword | C++ Equivalent      | Description                                    |
|--------------------|---------------------|------------------------------------------------|
| `agar`             | `if`                | Conditional statement                          |
| `warna`            | `else`              | Alternative for conditional execution          |
| `dobara`           | `while`             | Looping structure                              |
| `roko`             | `break`             | Exits from a loop                              |
| `wapas`            | `return`            | Returns a value from a function                |
| `mukarrar`         | `const`             | Defines a constant value                       |

### Data Types
Data types define the kind of value that a variable can hold. Here are the supported data types in Roman Urdu:

| Roman Urdu Keyword | C++ Equivalent      | Description                                    |
|--------------------|---------------------|------------------------------------------------|
| `adad`             | `int, float`        | Numeric data types, both integers and floats   |
| `lafz`             | `string`            | String type for storing text                   |
| `boolean`          | `bool`              | Boolean type, can be true or false             |
| `nishan`           | `char`              | Character type for single characters           |
| `khaali`           | `void`              | Used for functions that do not return a value  |
| `fahrist`          | `array`             | Array data type                                |
| `sancha`           | `class`             | Class definition for object-oriented programming|

### Operators
Operators perform operations on variables and values. The tokenizer recognizes the following operators:

| Operator   | Description                      | C++ Equivalent |
|------------|----------------------------------|----------------|
| `:=`       | Assignment                       | `=`            |
| `+`        | Addition                         | `+`            |
| `-`        | Subtraction                      | `-`            |
| `*`        | Multiplication                   | `*`            |
| `/`        | Division                         | `/`            |
| `==`       | Equal to                         | `==`           |
| `!=`       | Not equal to                     | `!=`           |
| `<`        | Less than                        | `<`            |
| `<=`       | Less than or equal to            | `<=`           |
| `>`        | Greater than                     | `>`            |
| `>=`       | Greater than or equal to         | `>=`           |
| `&&`       | Logical AND                      | `&&`           |
| `||`       | Logical OR                       | `||`           |
| `!`        | Logical NOT                      | `!`            |

### Booleans
Boolean values are used to represent truth values (true or false).

| Roman Urdu Keyword | C++ Equivalent | Description          |
|--------------------|----------------|----------------------|
| `sahi`             | `true`         | Represents true       |
| `ghalat`           | `false`        | Represents false      |

### Punctuation
Punctuation tokens represent characters like semicolons, parentheses, and braces used for syntactical purposes.

| Symbol | Description     |
|--------|-----------------|
| `;`    | Semicolon       |
| `(`    | Opening parenthesis |
| `)`    | Closing parenthesis |
| `{`    | Opening curly brace |
| `}`    | Closing curly brace |

---

## Regex

The tokenizer uses **regular expressions** to match and classify different components of the code. Here's how they are used:

- **Chemical Element Identifiers:** Recognizes variable names based on chemical elements using the regex:

  ```regex
  ^(?:H|He|Li|Be|B|C|N|O|F|Ne|Na|Mg|Al|Si|P|S|Cl|Ar)_\d{1,2}$
  ```

  This matches identifiers that start with a chemical element symbol followed by an underscore and 1-2 digits. Valid examples:
  - `H_1` (Hydrogen)
  - `O_2` (Oxygen)
  - `Na_1` (Sodium)
  - `Cl_12` (Chlorine)

- **Numeric values:** Matches numbers (both integers and floating-point) using:

  ```regex
  ^\d+(\.\d+)?$
  ```

  This matches integer or floating-point numbers (e.g., `5`, `3.14`).

- **String literals:** Strings are matched when enclosed in double quotes:

  ```regex
  ^".*"$ 
  ```

  This matches any string surrounded by double quotes.

- **Two-Character Operators:** Some operators, such as `==` and `!=`, are matched using a two-character check:

  ```regex
  ^==|!=|<=|>=$
  ```

---

## Example

Here's an example of how a source file written in Roman Urdu might look:

```plaintext
adad H_1 := 10;
adad O_2 := 20;
adad Na_1 := H_1 + O_2;

agar (Na_1 > 20) {
    wapas sahi;
} warna {
    wapas ghalat;
}
```

This code will be tokenized into the following tokens:

```plaintext
Line no: 1, Token: adad, Type: Data Type
Line no: 1, Token: H_1, Type: Identifier
Line no: 1, Token: :=, Type: Operator
Line no: 1, Token: 10, Type: Value
Line no: 1, Token: ;, Type: Punctuation
Line no: 2, Token: adad, Type: Data Type
Line no: 2, Token: O_2, Type: Identifier
Line no: 2, Token: :=, Type: Operator
Line no: 2, Token: 20, Type: Value
Line no: 2, Token: ;, Type: Punctuation
Line no: 3, Token: adad, Type: Data Type
Line no: 3, Token: Na_1, Type: Identifier
Line no: 3, Token: :=, Type: Operator
Line no: 3, Token: H_1, Type: Identifier
Line no: 3, Token: +, Type: Operator
Line no: 3, Token: O_2, Type: Identifier
Line no: 3, Token: ;, Type: Punctuation
Line no: 5, Token: agar, Type: Reserved Word
Line no: 5, Token: (, Type: Punctuation
Line no: 5, Token: Na_1, Type: Identifier
Line no: 5, Token: >, Type: Operator
Line no: 5, Token: 20, Type: Value
Line no: 5, Token: ), Type: Punctuation
Line no: 5, Token: {, Type: Punctuation
Line no: 6, Token: wapas, Type: Reserved Word
Line no: 6, Token: sahi, Type: Boolean
Line no: 6, Token: ;, Type: Punctuation
Line no: 7, Token: }, Type: Punctuation
Line no: 7, Token: warna, Type: Reserved Word
Line no: 7, Token: {, Type: Punctuation
Line no: 8, Token: wapas, Type: Reserved Word
Line no: 8, Token: ghalat, Type: Boolean
Line no: 8, Token: ;, Type: Punctuation
Line no: 9, Token: }, Type: Punctuation
```

---

## Contributing

If you'd like to contribute to the development of this tokenizer, feel free to fork the repository, create a new branch, and submit a pull request.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---