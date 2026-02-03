# C++ CLI Calculator

A command-line scientific calculator built in C++ that evaluates mathematical and scientific expressions directly from the terminal.

This project focuses on clean logic, correct operator handling, and implementing common scientific functions without using external libraries.

## Features
- Evaluate full mathematical expressions (example: `10 + 5 * 2`)
- Operator precedence supported (`*` `/` before `+` `-`)
- Brackets / parentheses support
- Scientific functions support:
  - `sin(x)`
  - `cos(x)`
  - `tan(x)`
  - `log(x)`
  - `sqrt(x)`
- Continuous calculation without restarting the program
- Error handling for:
  - Invalid input
  - Division by zero
  - Invalid scientific operations
  - Mismatched brackets

## How It Works
- Uses stacks to process numbers, operators, and functions
- Applies operators based on precedence rules
- Evaluates expressions step-by-step
- Uses C++ math functions internally for scientific calculations

## Run
```bash
g++ calculator.cpp -o calculator
./calculator