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
    bool isEmpty() {
        return (top < 0);
    }
};


// A check function
void expressionCheck(string infix) {
    // The only acceptable symbols, operators
    char acceptableChars[] = {'+','-','*','/','%','^','(',')','[',']','{','}'};

    try {
        /* If input contains letters or special characters that are not arithmetic
        /  Throw an error with the nefarious character
        */
        int size = sizeof(acceptableChars)/sizeof(acceptableChars[0]);
        for (int i = 0; i < infix.length(); i++) {
            if (infix[i] < '0' || infix[i] > '9') {  // Triggers when non-numerical character is found
                for (int j = 0; j < size; j++) { // Sorts through operator list
                    if (infix[i] == acceptableChars[j]) break;
                    if (j == size - 1) throw(infix[i]);
                }
            }
        }
    }
    catch (char problem) {
        cout << "Invalid character \'" << problem << "\'in expression";
    }
}


/* Checks for the correct parentheses count in the string using a stack
* If the stack is empty, then the equation is balanced. If not, throws an error
*/
void parenthesesCheck(const string& infix) {
    try {
        Stack checker;
        for (int i = 0; i < infix.length(); i++) {
            if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[') // Push to stack if (,{,[ found
                checker.push(to_string(infix[i]));
            if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']' ) // Pops respective open thingy
                if (checker.pop() == "a") {
                    throw(false);
                }
            }
        if (!checker.isEmpty())
            throw(false);
    }
    catch(bool wrongness) {
        cout << "Invalid balancing " << wrongness << endl;
        return;
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


// Infix to Postfix conversion
string* to_postfix(const string& infix) {
    Stack postfix_op_stack;
    string* postfix = new string[infix.size()];
    int postIndex = 0; // Current index of the postfix equation array
    // Reads the infix expression
    for (char inChar : infix) {
        // Open parenthesis? Push to stack
        if (inChar == '(' || inChar == '[' || inChar == '{') {
            postfix_op_stack.push(to_string(inChar));
            if (postIndex != 0)
                postIndex++;
            continue;
        }
        // Closed parenthesis? Pop operators and add to stack until open para. encountered. Do not add parenthesis to stack
        if (inChar == ')' || inChar == ']' || inChar == '}') {
            do {
                postfix[postIndex] = postfix_op_stack.pop();
                postIndex++;
            } while (!postfix_op_stack.isEmpty() &&
                    (postfix_op_stack.peek() != "(" ||
                    postfix_op_stack.peek() != "[" ||
                    postfix_op_stack.peek() != "{"));
            postfix_op_stack.pop();
            continue;
        }

        // If operand, immediately appended to postfix string
        if (inChar >= '0' && inChar <= '9') {
            postfix[postIndex] = postfix[postIndex] + inChar;
            cout << postfix[postIndex];
            continue;
        }

        // Operator Comparisons //
        cout << postfix_op_stack.peek() << endl;
        // Current Operator higher than at top? Push to stack
        if (postfix_op_stack.isEmpty() || operator_priority(to_string(inChar)) > operator_priority(postfix_op_stack.peek())) {
            postfix_op_stack.push(to_string(inChar));
            postIndex++;
            continue;
        }
        // Same or lower? Pop operators and append those to the postfix until
        // operator has different priority, then push to stack
        do {
            postIndex++;
            postfix[postIndex] = postfix_op_stack.pop();
        } while (!postfix_op_stack.isEmpty() && operator_priority(to_string(inChar)) <= operator_priority(postfix_op_stack.peek()));
        postfix_op_stack.push(to_string(inChar));
    }
    return postfix;
}

// Print postfix
void print_postfix(const string& postfix) {
    cout << postfix.size() << endl;
}

// Arithmetic time
// Do the arithmetic using stack
// Return the result, round to 3 decimal places (use float)


int main() {
    // Input an equation in infix format.
    string infixExpression;
    cout << "Enter an infix expression: ";
    getline(cin,infixExpression);
    expressionCheck(infixExpression);
    parenthesesCheck(infixExpression);
    string* postfixExpression = to_postfix(infixExpression);
    print_postfix(*postfixExpression);
    delete[] postfixExpression;

    return 0;
}
