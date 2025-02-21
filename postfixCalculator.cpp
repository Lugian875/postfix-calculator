#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// Stack Implementation
class Stack {
    int top;
public:
    #define SIZE 10  // Maximum size of the stack.
    string a[SIZE]; // Stack array
    Stack() { top = -1; } // Stack constructor

    // Pushes item to the top of the stack. If it goes over the size, then stack overflow!
    void push(const string &item) {
        if (top >= (SIZE - 1)) {
            cout << "Stack Overflow";
        } else {
            top++;
            a[top] = item;
        }
    }

    // Pops item from the top of the stack. If it tries to pop an empty stack, then stack underflow!
    string pop() {
        if (top == -1) {
            cout << "Stack Underflow" << endl;
            return "a";
        }
            string x = a[top];
            top--;
            return x;
    }

    // Takes a look at the top value in the stack
    string peek() const {
        if (top < 0) {
            cout << "Stack is Empty";
            return "a"; // it is here for now I guess
        }
        else {
            string x = a[top];
            return x;
        }
    }

    // Checks if the stack is empty
    bool isEmpty() const {
        return (top < 0);
    }
};


// A check function
/* If input contains letters or special characters that are not arithmetic
*  Throw an error with the nefarious character
*/
void expressionCheck(const string& infix) {
    // Array of acceptable non-numerical characters
    char acceptableChars[] = {'+','-','*','/','%','^','(',')','[',']','{','}'};
    int size = sizeof(acceptableChars)/sizeof(acceptableChars[0]);

    Stack checker;
    bool prevOper = true;
    for (int i = 0; i < infix.length(); i++) {
        // If operand? Set prevNum to true
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

        if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']') {
            if (checker.isEmpty()) {
                cout << "Error: Invalid parentheses" << endl;
                throw runtime_error("Invalid parenthesis");
            }
            char top = checker.peek()[0];
            if((top == '(' && infix[i] != ')') ||
                (top == '[' && infix[i] != ']')||
                (top == '{' && infix[i] != '}')) {
                cout << "Error: Invalid parentheses" << endl;
                throw runtime_error("Invalid parenthesis");
            }
            prevOper = false;
            checker.pop();
            continue;
        }

        for (int j = 0; j < size; j++) {
            if (prevOper == true || i == infix.length() - 1 || infix[i] == ' ') {
                cout << "Error: Invalid number of operands" << endl;
                throw runtime_error("Invalid operator #");
            }
            if (infix[i] == acceptableChars[j]) {
                prevOper = true;
                break;
            }
            if (j == size - 1) {
                cout << "Error: Invalid character '" << infix[i] <<"' in the expression" << endl;
                throw runtime_error("Invalid character in expression");
            }
        }
    }
}

/* Checks for the correct parentheses count in the string using a stack
* If the stack is empty, then the equation is balanced. If not, throws an error
*/


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


// Infix to Postfix conversion
string* to_postfix(const string& infix) {
    Stack postfix_op_stack;
    string* postfix = new string[infix.size() + 1];
    int postIndex = 0; // Current index of the postfix equation array
    // Reads the infix expression
    for (const char inChar : infix) {

        // If operand, immediately appended to postfix string
        if (inChar >= '0' && inChar <= '9') {
            postfix[postIndex] = postfix[postIndex] + inChar;
            continue;
        }

        // Parenthesis check
        // Open parenthesis? Push to stack
        if (inChar=='(' || inChar =='[' || inChar == '{') {
            postfix_op_stack.push(string(1,inChar));
            continue;
        }

        // Closed parenthesis?
        // Pop operators and add to postfix until an open parenthesis is popped
        // Do not add parenthesis to postfix
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
        // If the operator priority is higher than the top of stack?
        // Push to stack
        if (postfix_op_stack.isEmpty() ||
            operator_priority(string(1,inChar)) > operator_priority(postfix_op_stack.peek())) {
            postfix_op_stack.push(string (1,inChar));
            postIndex++;
            continue;
        }

        // If the operator has same or lower priority than the top of the stack?
        // Operators get popped and added to the postfix equation array until
        // Current operator priority is higher than top of stack OR stack is empty
        // Then push it to stack
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
    while (!postfix_op_stack.isEmpty()) {
        postIndex++;
        postfix[postIndex] = postfix_op_stack.pop();
    }
    // Control character "a" because I can't get the length of a dynamically allocated array
    postIndex++; postfix[postIndex] = "a";
    return postfix;
}

// Print postfix
void print_postfix(const string* postfix) {
    cout << "Postfix expression: ";
    int index = 0;
    while (postfix[index] != "a") {
        cout << postfix[index] << " ";
        index++;
    }
    cout << endl;
}

// Arithmetic time. Operands (+,-,*,/,%.^
double evaluatePostfix(const string* postfix) {
    Stack evaluator;
    int index = 0;
    double result = 0;
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
                case '/': if (a == 0) { cout << "Error: Dividing by Zero" << endl;
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
    // Input an equation in infix format.
    string infixExpression;
    cout << "Enter an infix expression: ";
    getline(cin,infixExpression);
    expressionCheck(infixExpression);
    // parenthesesCheck(infixExpression);
    string* postfixExpression = to_postfix(infixExpression);
    print_postfix(postfixExpression);
    cout << "Result: "<< fixed << setprecision(3) << evaluatePostfix(postfixExpression) << endl;
    delete[] postfixExpression;

    return 0;
}
