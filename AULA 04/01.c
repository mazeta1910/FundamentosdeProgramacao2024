#include <stdio.h>
#include <math.h>

int main() {
    int n = 1000000; // number of trials double total = 0.0;
    double temp = 0.0; // using another variable "temp" for the old value
    double division;
    int counter;
    int factorial;
    int total;

    do {
        temp = total; // storing the value of total in temp before modifying total
        counter = 1;
        factorial = n;

        while (counter < n) {
            factorial *= (n - counter);
            counter++;
        }

        division = 1.0 / factorial;
        total = total + division;
        n++;
    } while (fabs(total - temp) > 0.0000001); // loop until the difference between total and temp is less than 0.0000001

    printf("Approximation of Euler's number: %f\n", total);
    return 0;
}