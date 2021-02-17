#include <stdio.h>

int check_cmd_input(int argc)
{
    if (argc == 1)
        {
        printf("Program got no file in input and program will be closed. Ta Ta!\n");
        return 1;
    }
    if (argc != 2)
    {
        printf("Program got too many input arguments and program will be closed. Ta Ta!\n");
        return 1;
    }
    return 0;
}

