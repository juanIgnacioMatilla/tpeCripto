#ifndef GENERAL_CONFIG_H
#define GENERAL_CONFIG_H
#include "../cli_parser/cli_parser.h"
typedef struct general_config * general_cfg; 
general_cfg create_general_config(opts options);
void free_general_config(general_cfg config);
#endif