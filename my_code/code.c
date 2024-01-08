#include <stdio.h>

int main() {
    double revenue;
    double annual_payment;

    printf("Enter revenue value: ");
    scanf("%lf", &revenue);

    if (revenue < 25000000) {
        annual_payment = 15000;
    } else if (revenue < 75000000) {
        annual_payment = 35000;
    } else if (revenue < 150000000) {
        annual_payment = 50000;
    } else if (revenue < 300000000) {
        annual_payment = 65000;
    } else if (revenue < 750000000) {
        annual_payment = 165000;
    } else if (revenue < 1500000000) {
        annual_payment = 230000;
    } else if (revenue < 3000000000) {
        annual_payment = 330000;
    } else if (revenue < 10000000000) {
        annual_payment = 460000;
    } else {
        annual_payment = 650000;
    }

    printf("Annual payment is %.2lf", annual_payment);

    return 0;
}