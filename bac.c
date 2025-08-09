#include "bac.h"

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

char *convert_from_10(int num, int base)
{
        if (num == 0) {
                char *result = malloc(2);
                if (!result) {
                        fprintf(stderr, "Memory allocation failed\n");
                        exit(1);
                }
                result[0] = '0';
                result[1] = '\0';
                return result;
        }
        int is_negative = num < 0 ? 1 : 0;
        int temp = is_negative ? -num : num;
        int len = 0;
        while (temp > 0) {
                len++;
                temp /= base;
        }
        char *result = malloc(len + is_negative + 1);
        if (!result) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
        }

        int i = len - 1;
        temp = is_negative ? -num : num;
        while (temp > 0) {
                int remainder = temp % base;
                result[i--] =
                    remainder < 10 ? '0' + remainder : 'A' + remainder - 10;
                temp /= base;
        }
        if (is_negative) {
                result[0] = '-';
        }
        result[len + is_negative] = '\0';
        return result;
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
        char *result = convert_from_10(converted, output_base);
        printf("%s\n", result);
        free(result);

        return 0;
}
