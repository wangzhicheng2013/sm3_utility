#include <getopt.h>
#include "sm3_utility.h"
char *const short_options = "mdh:";
char *l_opt_arg = NULL;
struct option long_options[] = {  
     { "message_file_path",   1,   NULL,    'm'     },
     { "md_file_path",        1,   NULL,    'd'     },
     { "help",                0,   NULL,    'h'     },  
     {      0,                0,      0,     0      },  
};
void usage() {
    printf("./sm3_utility --message_file_path ./1.txt --md_file_path ./2.txt\n");
}
int main(int argc, char **argv) {
    int c = 0;
    char message_file_path[128] = { 0 };
    char md_file_path[128] = { 0 };
    if (argc != 5) {
        usage();
        return -1;
    }
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {  
        switch (c) {
        case 'm':
            l_opt_arg = optarg;
            snprintf(message_file_path, sizeof(message_file_path), "%s", l_opt_arg);
            break;  
        case 'd':
            l_opt_arg = optarg;
            snprintf(md_file_path, sizeof(md_file_path), "%s", l_opt_arg);
            break;
        case 'h':
            usage();
            break;
        default:
            usage();
            return -1;
            break;
        }
    }
    printf("sm3_utility result:%d\n", sm3_compute_digest_from_file(message_file_path, md_file_path));

    return 0;
}