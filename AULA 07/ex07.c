#include <stdio.h>
#include <math.h>

#define N 2048
#define PI 3.14159265358979323846

int main() {
    float f[N];

    for (int i = 0; i < N; i++) {
        f[i] = sin(2 * PI * i / N);
    }

    for (int i = 0; i < N; i++) {
        if (i < N - 1) {
            printf("%f\n", f[i]);
        } else {
            printf("%f\n", f[i]);
        }
    }

    return 0;
}
