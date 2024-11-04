#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <rhash.h>

#ifdef READLINE
#include <readline/readline.h>
#endif

void print_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}

int get_hash_algorithm(const char *algorithm) {
    if (strcmp(algorithm, "MD5") == 0) {
        return RHASH_MD5;
    } else if (strcmp(algorithm, "SHA1") == 0) {
        return RHASH_SHA1;
    } else if (strcmp(algorithm, "TTH") == 0) {
        return RHASH_TTH;
    } else {
        return -1;
    }
}


int main() {
    rhash_library_init();
    unsigned char digest[64];
    char output[128];
    char* str = NULL;

#ifdef READLINE
    while (str = readline())
#else
    size_t len = 0;
    while (getline(&str, &len, stdin) != -1)
#endif
    {
        if (strlen(str) && str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = '\0';
        }
        char* algorithm = strtok(str, " ");
        char* message = strtok(NULL, " ");

        if (!algorithm || !message) {
            print_error("Failed to args process. Usage:\n <algorithm> <filename or string>\n");
            continue;
        }

        int flag = isupper(algorithm[0]) ? RHPR_HEX : RHPR_BASE64;

        for (size_t i = 0; i < strlen(algorithm); i++) {
            algorithm[i] = toupper((unsigned char)algorithm[i]);
        }


        int rhash_algorithm = get_hash_algorithm(algorithm);
        if (rhash_algorithm == -1) {
            print_error("Failed to process hash algorithm. Wrong algorithm.\n");
            continue;
        }

        int result;
        if (message[0] == '\"') {
            result = rhash_msg(rhash_algorithm, message + 1, strlen(message) - 1, digest);
        } else {
            result = rhash_file(rhash_algorithm, message, digest);
        }

        if (result < 0) {
            print_error("Failed to compute rhash: %s: %s\n");
            continue;
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(rhash_algorithm), flag);
        printf("%s\n", output);
    }

    free(str);
    return 0;
}