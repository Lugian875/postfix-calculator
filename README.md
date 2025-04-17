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
This function is called to convert an infix equation (one that is human readable) to a postfix equation (one that is computer readable).
- The infix equation is read one character at a time
- It understands multi-digit operands
- Parenthesis and operators are pushed and popped from the stack under certain conditions
  - Open parenthesis are pushed to a stack
  - Closed parenthesis pops everything from the stack and appends them to the postfix equation string from the stack until reaching a matching open parenthesis. Both parentheses are not appended to the string.
  - Operators follow order-of-operations, with operators assigned a certain priority. If their priority is higher, it is pushed to stack. If their priority is lower, operators are continuously popped from the stack and added to the string until become a higher priority than the one at the top, then that is pushed to the stack.
  - At the end, the remaining operators are appended to the end of the string.

## print_postfix() function
Simply prints the equation in postfix form, which was a string made in the previous function.
## evaluate_postfix() function
This function evaluates the postfix function like a computer.
## main() function
Prompts the user for input in infix form, then runs through all the functions. It prints the postfix expression as well as the result, if it doesn't run into any errors.

# Example Output from Input
_WIP_
