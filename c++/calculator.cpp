#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

/* ===================== GLOBAL STATE ===================== */

double lastResult = 0.0;
double memoryValue = 0.0;
bool hasLastResult = false;
vector<string> history;

/* ===================== UTILITIES ===================== */

double getConstant(const string& s) {
    if (s == "pi") return M_PI;
    if (s == "e") return M_E;
    throw runtime_error("Unknown constant");
}

double parseValue(const string& s) {
    if (s == "ans") {
        if (!hasLastResult) throw runtime_error("No previous result");
        return lastResult;
    }
    if (s == "pi" || s == "e") {
        return getConstant(s);
    }
    return stod(s);
}

/* ===================== SCIENTIFIC FUNCTIONS ===================== */

double calculateFunction(const string& fn, double x) {
    if (fn == "sin") return sin(x * M_PI / 180);
    if (fn == "cos") return cos(x * M_PI / 180);
    if (fn == "tan") return tan(x * M_PI / 180);
    if (fn == "log") {
        if (x <= 0) throw runtime_error("Log domain error");
        return log10(x);
    }
    if (fn == "sqrt") {
        if (x < 0) throw runtime_error("Negative sqrt");
        return sqrt(x);
    }
    throw runtime_error("Unknown function");
}

/* ===================== BINARY OPERATIONS ===================== */

double calculateBinary(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '%':
            return fmod(a, b);
        default:
            throw runtime_error("Invalid operator");
    }
}

/* ===================== UI HELP ===================== */

void printHelp() {
    cout << "\nAvailable commands:\n";
    cout << "  Basic: number + number\n";
    cout << "  Use ans for last result\n";
    cout << "  Constants: pi, e\n";
    cout << "  Functions: sin cos tan log sqrt\n";
    cout << "  Memory: M+  MR  MC\n";
    cout << "  history : show past results\n";
    cout << "  help    : show this menu\n";
    cout << "  q       : quit\n\n";
}

/* ===================== MAIN LOOP ===================== */

int main() {
    cout << "====================================\n";
    cout << "   C++ Scientific CLI Calculator\n";
    cout << "====================================\n";
    cout << "Type 'help' for instructions\n\n";

    while (true) {
        try {
            cout << "> ";
            string cmd;
            cin >> cmd;

            /* Quit */
            if (cmd == "q" || cmd == "quit") {
                cout << "Goodbye 👋\n";
                break;
            }

            /* Help */
            if (cmd == "help") {
                printHelp();
                continue;
            }

            /* History */
            if (cmd == "history") {
                if (history.empty()) {
                    cout << "No history available\n";
                } else {
                    for (int i = 0; i < history.size(); i++) {
                        cout << i + 1 << ": " << history[i] << endl;
                    }
                }
                continue;
            }

            /* Memory operations */
            if (cmd == "M+") {
                memoryValue = lastResult;
                cout << "Stored in memory\n";
                continue;
            }
            if (cmd == "MR") {
                lastResult = memoryValue;
                hasLastResult = true;
                cout << "Result: " << lastResult << endl;
                continue;
            }
            if (cmd == "MC") {
                memoryValue = 0;
                cout << "Memory cleared\n";
                continue;
            }

            /* Scientific functions */
            if (cmd == "sin" || cmd == "cos" || cmd == "tan" ||
                cmd == "log" || cmd == "sqrt") {

                double x;
                cin >> x;
                lastResult = calculateFunction(cmd, x);
                hasLastResult = true;

                history.push_back(cmd + "(" + to_string(x) + ") = " +
                                  to_string(lastResult));

                cout << "Result: " << lastResult << endl;
                continue;
            }

            /* Binary operation */
            double a = parseValue(cmd);

            char op;
            cin >> op;

            string second;
            cin >> second;

            double b = parseValue(second);

            lastResult = calculateBinary(a, b, op);
            hasLastResult = true;

            history.push_back(
                to_string(a) + " " + op + " " + to_string(b) +
                " = " + to_string(lastResult)
            );

            cout << "Result: " << lastResult << endl;
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return 0;
}
