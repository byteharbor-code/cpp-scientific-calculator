#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>

using namespace std;

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

// Apply operator
double applyOp(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw runtime_error("Division by zero");
        return a / b;
    }
    if (op == '%') {
        if (b == 0) throw runtime_error("Division by zero");
        return fmod(a, b);
    }
    throw runtime_error("Invalid operator");
}

// Evaluate expression using stacks
double evaluateExpression(const string& expr) {
    stack<double> values;
    stack<char> ops;

    for (size_t i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i]) || expr[i] == '.') {
            double val = 0;
            size_t len = 0;
            val = stod(expr.substr(i), &len);
            values.push(val);
            i += len - 1;
        }
        else note: if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            if (ops.empty()) throw runtime_error("Mismatched brackets");
            ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    if (values.size() != 1) throw runtime_error("Invalid expression");
    return values.top();
}

int main() {
    cout << "Level 2 Calculator (q to quit)\n";

    double currentValue = 0;
    bool hasValue = false;

    while (true) {
        try {
            cout << "Enter expression: ";
            string input;
            getline(cin, input);

            if (input == "q" || input == "quit") break;
            if (input == "c" || input == "clear") {
                currentValue = 0;
                hasValue = false;
                cout << "Cleared\n";
                continue;
            }

            if (hasValue && (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/')) {
                input = to_string(currentValue) + input;
            }

            currentValue = evaluateExpression(input);
            hasValue = true;
            cout << "Result: " << currentValue << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
