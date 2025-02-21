#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// Stack Implementation
class Stack {
    int top;
public:
    #define SIZE 20  // Maximum size of the stack.
    string a[SIZE]; // String array represents stacks
    Stack() { top = -1; } // Stack constructor

    // Pushes item to the top of the stack
    // If it goes over the defined size, then a Stack Overflow error occurs
    void push(const string &item) {
        if (top >= (SIZE - 1)) {
            cout << "Stack Overflow. Breached maximum stack size of " << SIZE << endl;
            throw runtime_error("Stack Overflow");
        } else {
            top++;
            a[top] = item;
        }
    }

    // Pops item from the top of the stack.
    // If an empty stack is attempted to be popped, then a Stack Underflow error occurs
    string pop() {
        if (top == -1) {
            cout << "Stack Underflow" << endl;
            throw runtime_error("Stack Underflow");
        }
            string x = a[top];
            top--;
            return x;
    }

    // Returns the value at the top of the stack
    string peek() const {
        if (top < 0) {
            cout << "Stack is Empty";
            return "a"; // control character
        }
            string x = a[top];
            return x;
    }

    // Checks if the stack is empty
    bool isEmpty() const {
        return (top < 0);
    }
};


/* Checks an infix expression to make sure it is valid
 * It checks for proper operand, operator, and parenthesis placement
 */
void expressionCheck(const string& infix) {
    // Array of acceptable non-numerical characters (operators)
    char acceptableChars[] = {'+','-','*','/','%','^'};
    int size = sizeof(acceptableChars)/sizeof(acceptableChars[0]); // Size of the infix equation string

    Stack checker; // Creates a stack to be used for parentheses balancing
    bool prevOper = true; // Is the previous character an operator? This bool helps with throwing invalid operand errors
    for (int i = 0; i < infix.length(); i++) {
        // Operand?
        if (infix[i] >= '0' && infix[i] <= '9') {
            prevOper = false;
            continue;
        }

        // Open parenthesis? Push to stack.
        if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[') {
            checker.push(string(1, infix[i]));
            prevOper = false;
            continue;
        }

        // Closed parenthesis?
        if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']') {
            // If stack is empty, throw an error
            if (checker.isEmpty()) {
                cout << "Error: Invalid parentheses" << endl;
                throw runtime_error("Invalid parenthesis");
            }
            char top = checker.peek()[0]; // The value at the top of the stack
            // Mismatched parentheses? Throw an error
            if((top == '(' && infix[i] != ')') ||
                (top == '[' && infix[i] != ']')||
                (top == '{' && infix[i] != '}')) {
                cout << "Error: Invalid parentheses" << endl;
                throw runtime_error("Invalid parenthesis");
            }
            // If all checks pass, pops the corresponding open parentheses from the stack
            prevOper = false;
            checker.pop();
            continue;
        }

        // Operator?
        for (int j = 0; j < size; j++) {
            // If the previous entry was an operator, or it is at the end...
            // There is an invalid number of operands. Throws error
            if (prevOper == true || i == infix.length() - 1) {
                cout << "Error: Invalid number of operands" << endl;
                throw runtime_error("Invalid operand#");
            }
            // If there is a space character...
            // There is an invalid number of operators. Throws error.
            if (infix[i] == ' ') {
                cout << "Error: Invalid number of operators" << endl;
                throw runtime_error("Invalid operators#");
            }
            // If the operator is a part of the list, then break from the loop
            if (infix[i] == acceptableChars[j]) {
                prevOper = true;
                break;
            }
            // If the list is exhausted, then the checked character must be invalid. Throws error
            if (j == size - 1) {
                cout << "Error: Invalid character '" << infix[i] <<"' in the expression" << endl;
                throw runtime_error("Invalid character in expression");
            }
        }
    }
}


// Operation priority: '^','*' '/' '%', '+' '-'
int operator_priority(const string& oper) {
    if (oper == "(" || oper == "{" || oper == "[")
        return 0;
    if (oper == "+" || oper == "-")
        return 1;
    if (oper == "*" || oper == "/" || oper == "%")
        return 2;
    if (oper == "^")
        return 3;
   return 0;
}


// Converts an infix equation (human-readable) to a postfix equation (computer-readable)
string* to_postfix(const string& infix) {
    Stack postfix_op_stack; // Stack used to manipulate the infix equation
    string* postfix = new string[infix.size() + 1]; // Stores the postfix equation as a string array
    int postIndex = 0; // Current index of the postfix equation array
    // Reads the infix expression
    for (const char inChar : infix) {
        // Operand? Append to the current index of the postfix array. Supports multi-digit numbers
        if (inChar >= '0' && inChar <= '9') {
            postfix[postIndex] = postfix[postIndex] + inChar;
            continue;
        }

        // Parenthesis Checks //
        // Open parenthesis? Push to stack
        if (inChar=='(' || inChar =='[' || inChar == '{') {
            postfix_op_stack.push(string(1,inChar));
            continue;
        }

        /* Closed parenthesis?
        * Pop operators and add to postfix until an open parenthesis is popped.
        * They are not added to the string.
        */
        if (inChar == ')' || inChar == ']' || inChar == '}') {
            while (postfix_op_stack.peek() != "(" &&
                    postfix_op_stack.peek() != "[" &&
                    postfix_op_stack.peek() != "{") {
                postIndex++;
                postfix[postIndex] = postfix_op_stack.pop();
                    }
            postfix_op_stack.pop();
            continue;
        }

        // Operator Check //
        // The operator priority is higher than that of top of stack?
        // Push to stack
        if (postfix_op_stack.isEmpty() ||
            operator_priority(string(1,inChar)) > operator_priority(postfix_op_stack.peek())) {
            postfix_op_stack.push(string (1,inChar));
            postIndex++;
            continue;
        }

        /* The operator has same or lower priority than the top of the stack?
        * Operators get popped and added to the postfix equation array until the
        * current operator priority is higher than top of stack OR stack is empty.
        * Then that operator is pushed to stack
        */
        if (operator_priority(string(1,inChar)) <= operator_priority(postfix_op_stack.peek())) {
            while (!postfix_op_stack.isEmpty() &&
                operator_priority(string(1,inChar)) <= operator_priority(postfix_op_stack.peek())) {
                postIndex++;
                postfix[postIndex] = postfix_op_stack.pop();
            }
            postfix_op_stack.push(string(1,inChar));
            postIndex++;
        }
    }
    // Pops any leftover operators from the stack and adds them to the postfix array
    while (!postfix_op_stack.isEmpty()) {
        postIndex++;
        postfix[postIndex] = postfix_op_stack.pop();
    }
    postIndex++; postfix[postIndex] = "a"; // Adds "a" as the last value in the postfix to serve as a control character
    return postfix;
}

// Prints the postfix equation
void print_postfix(const string* postfix) {
    cout << "Postfix expression: ";
    int index = 0;
    // Prints out values until reaching the control character
    while (postfix[index] != "a") {
        cout << postfix[index] << " ";
        index++;
    }
    cout << endl;
}

/* Evaluates the postfix equation.
*  Supports addition, subtraction, multiplication, division, modulo, and exponents
*/
double evaluatePostfix(const string* postfix) {
    Stack evaluator; // Stack used for operations
    int index = 0; // Current index in the postfix string array
    double result = 0; // Stores results of operations

    while (postfix[index] != "a") {
        // If operator is encountered...
        if(postfix[index] == "+" || postfix[index] == "-" || postfix[index] == "*"||
            postfix[index] == "/" || postfix[index] == "%" || postfix[index] == "^") {
        // Pop two operands from stack
            double a = stod(evaluator.pop());
            double b= stod(evaluator.pop());
            char op = postfix[index][0];
        // Evaluate with operator
            switch (op) {
                case '+': result = b+a; break;
                case '-': result = b-a; break;
                case '*': result = b*a; break;
                case '/': if (a == 0) { cout << "Error: Dividing by Zero" << endl; // Divide by Zero catch
                        throw runtime_error("Divide by Zero catch");
                    }
                    result = b/a; break;
                case '%': result = fmod(b,a); break;
                case '^': result = pow(b,a); break;
                default:
                    cout << "no" << endl;
            }
        // Put result back in stack
            evaluator.push(to_string(result));
        } else {
            evaluator.push(postfix[index]); // If operand is encountered, push it to stack
        }
        index++;
    }
    return stod(evaluator.pop());
}


int main() {
    // Prompts the user to input an expression in infix format
    string infixExpression;
    cout << "Enter an infix expression (no spaces): ";
    getline(cin,infixExpression);

    expressionCheck(infixExpression); // Checks expression for errors

    string* postfixExpression = to_postfix(infixExpression); // Transform the infix expression to postfix

    print_postfix(postfixExpression); // Prints postfix expression

    // Evaluates the postfix expression
    cout << "Result: "<< fixed << setprecision(3) << evaluatePostfix(postfixExpression) << endl;

    delete[] postfixExpression;
    return 0;
}
