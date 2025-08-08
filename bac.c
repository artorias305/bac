#include <stdio.h>
#include <stdlib.h>

void print_help()
{
        printf("Usage: bac <number> <input base> <output base>\n");
        return;
}

int main(int argc, char **argv)
{
        if (argc != 4) {
                print_help();
                exit(1);
        }
        char *input = argv[1];
        char *input_base = argv[2];
        char *output_base = argv[3];
}
