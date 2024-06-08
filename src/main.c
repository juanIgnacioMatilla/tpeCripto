#include <stdio.h>
#include "./cli_parser/cli_parser.h"

int main(int argc, char *argv[])
{
    opts options = parse_command_line(argc,argv);
    free_options(options);
    return 0;
}
