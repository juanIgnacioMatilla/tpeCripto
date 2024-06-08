#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <getopt.h>

enum {
    EMBED = 1000,
    EXTRACT,
    IN,      
    P,
    OUT,
    STEG,
    A,
    M,
    PASS,
    HELP
};

typedef struct options_struct * opts;

opts parse_command_line(int argc, char * argv[]);

void free_options(opts options);

int get_mode(opts options);

char * get_input_file(opts options);

char * get_carrier_file(opts options);

char * get_output_file(opts options);

char * get_stego_algo(opts options);

char * get_enc_algo(opts options);

char * get_enc_mode(opts options);

char * get_password(opts options);

#endif