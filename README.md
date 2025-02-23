# Postfix Calculator Project
This is a calculator with extra steps. The program takes a user input infix expression, checks it for correctness, converts the infix to postfix, and then evaluates the postfix equation.

# Project Constraints
I was required to utilize an array-based stack implementation for doing comparisons and evaluations. I was not allowed to use any STL libraries besides \<string\>. It also was required to be in one file, so that's why the Stack class is not separated from the rest of the code.
# Project Structure
This is an in-depth explanation of how each section of the code works.
## Stack class
The Stack class was edited from example code provided by the professor. The original example code was an integer array, but I changed it to a string array.
- **Push:** Pushes an item to the top of the stack. If it overflows, then an error is thrown. The maximum stack size is 20, which is overkill.
- **Pop:** Pops an item from the top of the stack.
- There are also functions to check the value at the top of the stack and to check if the stack is empty. The isEmpty() returns a boolean instead of a string.

## expressionCheck() function
This function is called to check the user-typed infix expression for any problems that violate how the expression should be written. It checks for excessive operands, operators, and parentheses.
- Operands are considered invalid if there is a space between them instead of parentheses or operators.
- Operators are considered invalid if they start or end an expression, or there are multiple in sequence.
- Parentheses are invalid if they are considered "inbalanced." The three types: parentheses/round brackets (**( )**), brackets/square brackets (**[ ]**), and braces/curly brackets (**{ }**) are checked using a Stack
  - Open brackets are pushed to stack. Closed brackets that match with its corresponding open one pops it from the stack.
  - Errors are thrown if the stack is not empty or there is not matching brackets.
- It also checks for invalid characters and displays them if detected

## to_postfix() function
_WIP_
## print_postfix() function
_WIP_
## evaluate_postfix() function
_WIP_
## main() function
_WIP_
