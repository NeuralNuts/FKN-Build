#include <stdio.h>

#include "add.h"
#include "minus.h"

int main() {
    printf("testing... 123");

    int a = add(10, 20);
    int m = minus(5, 10);
    
    printf("\nadd(): %d\n", a);
    printf("minus(): %d\n", m);

    return 0;
}
