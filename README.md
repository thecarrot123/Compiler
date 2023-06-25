# Dysfunctional Lisp Compiler

Welcome to the Dysfunctional Lisp Compiler repository! This project is a reduced version of the Lisp programming language. It aims to provide a functional programming language that allows you to write programs using a series of function declarations.

## About Dysfunctional Lisp Compiler

This repository contains various components of the compiler, which include:

- Lexical Analyzer: Responsible for tokenizing the source code into meaningful units.
- Syntax Analyzer: Performs syntactic analysis on the tokens to construct the AST and ensure correct syntax.
- Semantic Analyzer: Analyzes and purifies the AST to produce the AAST and identify any semantic errors.
- Code Interpreter: Evaluates the AAST to check for any runtime errors and formulate the final output.

The compiler was built using c++ and makefile, to run it on your machine make sure to meet the <a href="#prerequisites">prerequisites</a>.

## About Dysfunctional Lisp Language

### Features

- **Functional Programming:** Dysfunctional Lisp emphasizes functional programming concepts, enabling you to write programs using pure functions and immutable data.
- **Minimalistic Syntax:** The language employs a reduced syntax compared to standard Lisp, making it more accessible to newcomers while still capturing the essence of Lisp's power.
- **Function Declarations:** Programs in Dysfunctional Lisp are composed of function declarations, allowing you to define and invoke functions easily.

### The language

Dysfunctional Lisp programs consist of a sequence of function declarations, with one of them serving as the entry point to the program, referred to as "prog." The language defines three types of entities:

1. Literals: Explicitly written values such as integers, real numbers, booleans, and null values.
2. Atoms: These can be viewed as variables in conventional programming languages. They follow the syntax rules for identifiers and can hold values that are either literals or functions.
3. Lists: Sequences of elements enclosed by parentheses and separated by whitespace.

Program execution begins with the very last element of the program, which is a special form known as "prog." Each element is evaluated according to its specific semantics. If an element is an atom, its value is simply returned by the interpreter. If an element is a list, it is treated as a function call, where the first element represents the function name and the remaining elements are considered arguments for the call.

Certain lists have special meanings and are referred to as special forms. Special forms are evaluated differently, as described in the subsequent section. The special form lists begin with keywords such as quote, setq, func, lambda, prog, cond, while, return, and break.

In addition to the language's core features, Dysfunctional Lisp provides a multitude of predefined functions that can be utilized. Some of these include:

- Arithmetic functions: plus, minus, times, divide.
- Operations on lists: head, tail, cons, isempty.
- Comparison functions: equal, nonequal, less, lesseq, greater, greatereq.
- Predicates: isint, isreal, isbool, isnull, isatom.
- Logical operators: and, or, xor, not.
Evaluator: eval.

<h2 id="prerequisites">prerequisites</h2>

Before getting started with Dysfunctional Lisp, ensure that you have the following prerequisites installed:

- C++17 compatible compiler
- Makefile

## Usage

To use the Dysfunctional Lisp Compiler, follow these steps:

1. Clone the repository to your local machine:

```git clone https://github.com/thecarrot123/Compiler.git```


2. Change to the project directory:

```cd Compiler```


3. Build the project using the provided Makefile:

```make```

4. Launch the Dysfunctional Lisp Compiler by running the executable:

```./compiler -f [filename]```

Replace `[filename]` with the path to your Dysfunctional Lisp code file.

### To run tests
```make run_tests```

### To remove executable and tests output
```make clear```

## Contributing

Contributions to the Dysfunctional Lisp Compiler project are welcome! If you would like to contribute, please follow these steps:

1. Fork the repository on GitHub.
2. Create a new branch with a descriptive name.
3. Make your changes and commit them with clear and concise messages.
4. Push your changes to your forked repository.
5. Submit a pull request, explaining the changes you have made.
