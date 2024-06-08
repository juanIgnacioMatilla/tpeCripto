#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cli_parser.h"

static struct option static_options[] = {
   {"embed",    no_argument,        0,  EMBED   },
   {"extract",  no_argument,        0,  EXTRACT },
   {"in",       required_argument,  0,  IN      },
   {"p",        required_argument,  0,  P       },
   {"out",      required_argument,  0,  OUT     },
   {"steg",     required_argument,  0,  STEG    },
   {"a",        required_argument,  0,  A       },
   {"m",        required_argument,  0,  M       },
   {"pass",     required_argument,  0,  PASS    },
   {"help",     no_argument,        0,  HELP    },
   {0,          0,                  0,  0       }
};


typedef struct options_struct {
    int mode;
    char * input_file;
    char * carrier_file;
    char * output_file;
    char * stego_algo; 
    char * enc_algo; 
    char * enc_mode; 
    char * password;
} options_struct;


static void print_help();


opts parse_command_line(int argc, char * argv[]) {
    opts options = calloc(1, sizeof(options_struct));

    if (NULL == options){
        printf("No memory allocation for options_struct\n");
        exit(EXIT_FAILURE);
    }        
    
    int cli_argument = 0;

    while (1) {
        int option_index = 0;

        cli_argument = getopt_long_only(argc, argv, "", static_options, &option_index);
        if (cli_argument == -1) break;

        switch(cli_argument) {
            case EMBED:
                options->mode = EMBED;
                break;
            case EXTRACT:
                options->mode = EXTRACT;
                break;
            case IN: 
                options->input_file = optarg;
                break;
            case P:
                options->carrier_file = optarg;
                break;
            case OUT:
                options->output_file = optarg;
                break;
            case STEG:
                options->stego_algo = optarg;
                break;
            case A:
                options->enc_algo = optarg;
                break;
            case M:
                options->enc_mode = optarg;
                break;
            case PASS:
                options->password = optarg;
                break;
            case HELP: 
                print_help();
                break;
            default:
               printf("Unknown argument: 0%o\n", cli_argument);
        }
    }

    if (optind < argc) {
       printf("Wrong argmuments: ");
       while (optind < argc)
           printf("%s\n", argv[optind++]);
    }

    return options;
}

void free_options(opts options) {
    free(options);
}

int get_mode(opts options) {
    return options->mode;
}

char * get_input_file(opts options) {
    return options->input_file;
}

char * get_carrier_file(opts options) {
    return options->carrier_file;
}

char * get_output_file(opts options) {
    return options->output_file;
}

char * get_stego_algo(opts options) {
    return options->stego_algo;
}

char * get_enc_algo(opts options) {
    return options->enc_algo;
}

char * get_enc_mode(opts options) {
    return options->enc_mode;
}

char * get_password(opts options) {
    return options->password;
}

static void print_help() {
    printf("Usage: stegobmp -MODE [-in filename] -p filename -out filename -steg <LSB1 | LSB4 | LSBI> [-a <aes128 | aes196 | aes256 | des>] [-m <ecb | cfb | ofb | cbc>] [-pass password] [-help] \n");

    printf("\nModes.\n");
    printf("%-*s\t%s", 40, "-embed", "Enable embed mode.\n");
    printf("%-*s\t%s", 40, "-extract", "Enable extract mode.\n");

    printf("\nRequired arguments.\n");
    printf("%-*s\t%s", 40, "-in filename", "File to be hidden.\n");
    printf("%-*s\t%s", 40, "-p filename", "Carrier file, must be a BMP image.\n");
    printf("%-*s\t%s", 40, "-out filename", "Output file.\n");
    printf("%-*s\t%s", 40, "-steg <LSB1 | LSB4 | LSBI>", "Steganography algorithm.\n");

    printf("\nOptional arguments.\n");
    printf("%-*s\t%s", 40, "-a <aes128 | aes196 | aes256 | des>", "Cryptography algorithm.\n");
    printf("%-*s\t%s", 40, "-m <ecb | cfb | ofb | cbc>", "Cryptography mode.\n");
    printf("%-*s\t%s", 40, "-pass password", "Password for encryption.\n");

    printf("\nAdditional arguments.\n");
    printf("%-*s\t%s", 40, "-help", "Display usage and this help message, then exit.\n");

    printf("\n%s\n", "Encryption will be skipped if no password is provided.");
    printf("%s\n", "Default cryptography algorithm is aes128.");
    printf("%s\n", "Default cryptography mode is cbc.");

    exit(EXIT_SUCCESS);
}