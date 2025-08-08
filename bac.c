#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help()
{
        printf("Usage: bac <number> <input base> <output base>\n");
        return;
}

int char_to_digit(char c)
{
        if (c >= '0' && c <= '9')
                return c - '0';
        if (c >= 'a' && c <= 'f')
                return c - 'a' + 10;
        if (c >= 'A' && c <= 'F')
                return c - 'A' + 10;
        return -1;
}

int str_to_int(const char *str)
{
        int num = 0;
        for (size_t i = 0; str[i]; i++) {
                int digit = char_to_digit(str[i]);
                if (digit == -1) {
                        fprintf(stderr, "Invalid digit in base: %c\n", str[i]);
                        exit(1);
                }
                num = num * 10 + digit;
        }
        return num;
}

int convert_to_10(char *num, int base)
{
        int converted = 0;
        for (size_t i = 0; num[i]; i++) {
                int digit = char_to_digit(num[i]);
                if (digit == -1 || digit >= base) {
                        fprintf(stderr, "Invalid digit %c for base %d\n",
                                num[i], base);
                        exit(1);
                }
                converted = converted * base + digit;
        }
        return converted;
}

int main(int argc, char **argv)
{
        if (argc != 4) {
                print_help();
                exit(1);
        }
        char *input = argv[1];
        int input_base = str_to_int(argv[2]);
        int output_base = str_to_int(argv[3]);

        if (input_base < 2 || input_base > 16 || output_base < 2 ||
            output_base > 16) {
                fprintf(stderr, "Error: input and output bases must be between "
                                "2 and 16.\n");
                exit(1);
        }

        int converted = convert_to_10(input, input_base);
        printf("%d\n", converted);

        return 0;
}
