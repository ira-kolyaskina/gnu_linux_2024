#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*remove_func)(const char *);

int remove(const char *filename) {
    if (strstr(filename, "PROTECT")) {
        return 1;
    }

    remove_func original_remove = dlsym(RTLD_NEXT, "remove");
    return original_remove(filename);
}