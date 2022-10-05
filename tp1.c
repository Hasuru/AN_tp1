#include <stdio.h>
#include <math.h>

#define MAX 20

// io functions
void macro_values();
void eps_function_values(double eps);
void approximation_results(double *l);

// eps calc function
double factorial(double n);
double macheps(double eps);
double limEuler(double n);
double sumEuler(double n);

int main() {
    macro_values();
    eps_function_values(macheps(0.5));

    double l[MAX];
    for (int i = 1; i <= MAX; i++)
        l[i-1] = limEuler(i);
    approximation_results(l);

    for (int i = 1; i <= MAX; i++)
        l[i-1] = sumEuler(i);
    approximation_results(l);

    return 0;
}

void macro_values() {
    printf("Macro values stored in C\n");
    printf("\tFloat epsilon: %e\n", __FLT_EPSILON__);
    printf("\tDouble epsilon: %e\n", __DBL_EPSILON__);
    printf("\tLong Double epsilon: %Le\n", __LDBL_EPSILON__);
    printf("-------------------------------------------\n");
}

void eps_function_values(double eps) {
    printf("Machine epsilon by function: %e\n", eps);
    printf("-------------------------------------------\n");
}

void approximation_results(double *l) {
    printf("Table with approximated values:\n");
    for (int i = 0; i < MAX; i++)
        printf("\t%d\t->\t%.19f\n", i+1, l[i]);
    printf("-------------------------------------------\n");
}

double factorial(double n) {
    double value = 1;
    for (int i = 2; i <= n; i++) {
        value *= i;
    }
    return value;
}

// Cálculo da eps da máquina
double macheps(double eps) {
    double prev;

    while ((1+eps) != 1) {
        prev = eps;
        eps /= 2;
    }
    return prev;
}

double limEuler(double n) {
    double e = 1+(1/n);
    return pow(e,n);
}

double sumEuler(double n) {
    return 1/factorial(n);
}