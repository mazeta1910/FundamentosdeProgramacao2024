#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n;
    srand(time(NULL));

    n = rand();
    printf("%d\n", n);

    return 0;
}
