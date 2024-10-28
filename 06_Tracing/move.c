#include <stdio.h>
#include <stdlib.h>

void cleanup(FILE *infile, FILE *outfile, const char *outfile_name) {
    if (infile) fclose(infile);
    if (outfile) fclose(outfile);
    if (outfile_name) remove(outfile_name);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: \n%s <infile> <outfile>\n", argv[0]);
        return -1;
    }

    char* fd_in = argv[1];
    char* fd_out = argv[2];

    FILE* infile = fopen(fd_in, "r");
    if (!infile) {
        fprintf(stderr, "Failed to open input file: %s\n", fd_in);
        return 1;
    }

    FILE* outfile = fopen(fd_out, "w");
    if (!outfile) {
        fclose(infile);
        fprintf(stderr, "Failed to open output file: %s\n", fd_out);
        return 2;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), infile)) > 0) {
        if (ferror(infile)) {
            fprintf(stderr, "Failed to read input file: %s\n", argv[1]);
            cleanup(infile, outfile, argv[2]);
            return 3;
        }

        if (ferror(outfile) || fwrite(buffer, sizeof(char), bytes_read, outfile) != bytes_read) {
            fprintf(stderr, "Failed to write in output file: %s\n", argv[1]);
            cleanup(infile, outfile, argv[2]);
            return 4;
        }
    }

    fclose(infile);
    fclose(outfile);

    if (remove(fd_in)) {
        fprintf(stderr, "Failed to remove infile: %s\n", fd_in);
        remove(fd_out);
        return 5;
    }

    return 0;
}