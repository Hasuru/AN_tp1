#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX 20

// io functions
void macro_values();
void eps_function_values(double eps);
void approximation_results(double *l, double sum);

// eps calc function
double factorial(double n);
double macheps(double eps);
double value(double n);
double s(double n);
double calc_sum(double low, double high);
void error_values();
double limEuler(double n);
double sumEuler(double n);

int main() {
    macro_values();
    eps_function_values(macheps(0.5));

    double l[MAX];
    for (int i = 0; i <= MAX; i++)
        l[i] = limEuler(i);
    approximation_results(l, 0);

    double sum = 0;
    for (int i = 0; i <= MAX; i++) {
        l[i] = sumEuler(i);
        sum += l[i];
    }
    approximation_results(l, sum); // +1 do factorial de 0

    error_values();

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

void approximation_results(double *l, double sum) {
    printf("Table with approximated values:\n");
    for (int i = 0; i <= MAX; i++)
        printf("\t%d\t->\t%.19f\n", i, l[i]);

    if (sum != 0)
        printf("\tTotal sum value: %.19f\n", sum);
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

double value(double n) {
    double sum;
    for (double k = 1; k <= n; k++) {
        sum += pow(factorial(k),2) / (pow(k,2)*factorial(2*k));
    }
    return 18*sum;
}

double calc_sum(double low, double high) {
    double sum = 0;
    while (low <= high) {
        sum += s(low);
        low++;
    }
    return sum;
}

double s(double n) {
    return (18*pow(factorial(n),2))/(pow(n, 2)*factorial(2*n));
}

void error_values() {
    double epsilon[8] = {8,9,10,11,12,13,14,15};
    double n = 1;
    double prev = 1;
    double sum = 0;

    for (int i = 0; i < 8; i++) {
        while (s(n+1)*(4/3) >= pow(10,-epsilon[i])) n++;
        sum += calc_sum(prev, n);
        prev = n+1;
        printf("exp:%.0f | n:%.0f | sum:%0.19f | error:%0.19f\n", epsilon[i], n, sum, pow(M_PI,2)-sum);
    }
}

double limEuler(double n) {
    double e = 1+(1/pow(10,n));
    return pow(e,pow(10,n));
}

double sumEuler(double n) {
    return 1/factorial(n);
}