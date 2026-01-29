// crt_strtod.c
// This program uses strtod to convert a
// string to a double-precision value; strtol to
// convert a string to long integer values; and strtoul
// to convert a string to unsigned long-integer values.
//

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *string, *stopstring;
    double x;
    long   l;
    int    base;
    unsigned long ul;

    string = "3.1415926This stopped it";
    x = strtod(string, &stopstring);
    printf("string = %s\n", string);
    printf("   strtod = %f\n", x);
    printf("   Stopped scan at: %s\n\n", stopstring);

    string = "-10110134932This stopped it";
    l = strtol(string, &stopstring, 10);
    printf("string = %s\n", string);
    printf("   strtol = %ld\n", l);
    printf("   Stopped scan at: %s\n\n", stopstring);

    string = "10110134932";
    printf("string = %s\n", string);

    // Convert string using base 2, 4, and 8:
    for (base = 2; base <= 8; base *= 2)
    {
        // Convert the string:
        ul = strtoul(string, &stopstring, base);
        printf("   strtol = %ld (base %d)\n", ul, base);
        printf("   Stopped scan at: %s\n", stopstring);
    }

    // NaN
    x = strtod("+nan", &stopstring);
    printf("\n%f\n", x);

    // INF
    x = strtod("-INF", &stopstring);
    printf("\n%f\n", x);

    // e - exponent
    x = strtod("1.18973e+49", &stopstring);
    printf("\n%f\n", x);

    // doesn't handle Fortran style
    x = strtod("1.18973d+49", &stopstring);
    printf("\n%f\n", x);
    printf("No Fortran style support. Stopped parsing at %s\n", stopstring);
}
