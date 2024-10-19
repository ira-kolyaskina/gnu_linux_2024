#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAXGR 10
#define INITIAL_CAPACITY 64

void append_str(char **buf, size_t *capacity_buf, size_t *len_buf, const char *add_buf, size_t add_len) {
    if (*len_buf + add_len + 1 >= *capacity_buf) {
        *capacity_buf += add_len + INITIAL_CAPACITY;
        *buf = realloc(*buf, *capacity_buf);
        if (*buf == NULL) {
            perror("Failed to realloc");
            exit(EXIT_FAILURE);
        }
    }
    memcpy(*buf + *len_buf, add_buf, add_len);
    *len_buf += add_len;
    (*buf)[*len_buf] = '\0';
}

void handle_substitution(const char *subst, const char *input, regmatch_t *bags, char **result_buf) {
    size_t capacity_buf = INITIAL_CAPACITY;
    size_t len_buf = 0;
    *result_buf = malloc(capacity_buf);
    if (*result_buf == NULL) {
        perror("Failed to allocate buffer");
        exit(1);
    }
    
    for (size_t i = 0; i < strlen(subst); ++i) {
        if (subst[i] == '\\') {
            if (subst[i + 1] >= '0' && subst[i + 1] <= '9') {
                int idx_bag = subst[i + 1] - '0';
                if (bags[idx_bag].rm_so == -1) {
                    fprintf(stderr, "Error: Non-existing capture group: %d\n", idx_bag);
                    free(*result_buf);
                    exit(EXIT_FAILURE);
                }
                int ss = bags[idx_bag].rm_so;
                int ee = bags[idx_bag].rm_eo;
                append_str(result_buf, &capacity_buf, &len_buf, &input[ss], ee - ss);
                i++; // Skip the digit
            } else {
                append_str(result_buf, &capacity_buf, &len_buf, "\\", 1);
                i++;
            }
        } else {
            append_str(result_buf, &capacity_buf, &len_buf, &subst[i], 1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "WRONG NUMBER OF ARGUMENTS!!!");
        return 1;
    }

    regex_t regex;
    regmatch_t bags[MAXGR];

    if (regcomp(&regex, argv[1], REG_EXTENDED) != 0) {
        char err_buf[1024];
        regerror(regcomp(&regex, argv[1], REG_EXTENDED), &regex, err_buf, sizeof(err_buf));
        fprintf(stderr, "%s\n", err_buf);
        return 1;
    }

    char *result_buf = NULL;
    if (regexec(&regex, argv[3], MAXGR, bags, 0) == 0) {
        handle_substitution(argv[2], argv[3], bags, &result_buf);

        int s = bags[0].rm_so;
        int e = bags[0].rm_eo;

        printf("%.*s%s%s\n", s, argv[3], result_buf, &argv[3][e]);
        
        free(result_buf);
    } else {
        printf("%s\n", argv[3]);
    }

    regfree(&regex);
    return 0;
}
