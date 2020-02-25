#include "uls.h"

void mx_putnbr_w(int n, int width) {
    int i = mx_intlen(n);

    while (i++ < width)
        mx_printchar(' ');
    mx_putnbr(n);
}

void mx_putnbr(int n) {
    if (n < -9 || n > 9)
        mx_putnbr(n / 10);
    if (n < 0) {
        if (n >= -9)
            mx_printchar('-');
        mx_printchar('0' - (n % 10));
    }
    else
        mx_printchar('0' + (n % 10));
}


void mx_putstr_w(char *str, int width, int start) {
    int i;
    int len;

    i = 0;
    len = (int)mx_strlen(str);
    if (!start) {
        while (i++ < width - len)
            mx_printchar(' ');
    }
    i = 0;
    while (str[i])
        mx_printchar(str[i++]);
    if (start) {
        while (i++ < width)
            mx_printchar(' ');
    }
}

long long mx_put_abs(long long nbr) {
    if (nbr < 0)
        return (-nbr);
    return (nbr);
}
