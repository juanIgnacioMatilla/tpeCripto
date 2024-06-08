#include <stdio.h>
#include "./cli_parser/cli_parser.h"
#include "./general_config/general_config.h"
int main(int argc, char *argv[])
{
    opts options = parse_command_line(argc,argv);
    general_cfg config = create_general_config(options);
    
    free_general_config(config);
    free_options(options);
    return 0;
}
