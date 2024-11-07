#include <iostream>
using namespace std;

int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}


void fibonacciIterative(int n) {
    int a = 0, b = 1, fib;

    cout << "Fibonacci series up to " << n << " terms is: ";

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            cout << a << " ";
        } else if (i == 1) {
            cout << b << " ";
        } else {
            fib = a + b;
            a = b;
            b = fib;
            cout << fib << " ";
        }
    }
    cout << endl;
}



int main() {

    int n1;
    cout << "Enter the number of terms for Fibonacci series (iterative): ";
    cin >> n1;

    fibonacciIterative(n1);
    int n2;
    cout << "Enter the number of terms for Fibonacci series (recursive): ";
    cin >> n2;

    cout << "Fibonacci series up to " << n2 << " terms is: ";
    for (int i = 0; i < n2; i++) {
        cout << fibonacciRecursive(i) << " ";
    }
    cout << endl;

    return 0;
}
