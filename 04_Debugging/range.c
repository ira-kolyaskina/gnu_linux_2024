#include <stdio.h>
#include <stdlib.h>


typedef struct range {
    int start;
    int stop;
    int step;
    int cur;
} range;


int range_get(range *p) {
    return p->cur;
}


void range_next(range *p) {
    p->cur += p->step;
}


int range_run(range *p) {
    return (p->cur < p->stop);
}


void range_init(range *p) {
    p->cur = p->start;
}


void print_help() {
    printf("---help---\n");
    printf("Arithmetic progression generator program\n");
    printf("Your options:\n");
    printf("One argument N: arithmetic progression from 0 to N-1\n");
    printf("Two argument M, N: arithmetic progression from M to N-1\n");
    printf("Three argument M, N, S: arithmetic progression from M to N-1 with step S\n");
}


void argparse(int argc, char *argv[], int *start, int *stop, int *step) {
    if (argc < 2) {
        print_help();
        exit(-1);
    } else if (argc == 2) {
        *start = 0;
        *stop = strtol(argv[1], NULL, 10);
        *step = 1;
    } else if (argc == 3) {
        *start = strtol(argv[1], NULL, 10);
        *stop = strtol(argv[2], NULL, 10);
        *step = 1;
    } else if (argc == 4) {
        *start = strtol(argv[1], NULL, 10);
        *stop = strtol(argv[2], NULL, 10);
        *step = strtol(argv[3], NULL, 10);
    } else {
        printf("Wrong arguments\n");
        exit(-2);
    }
}


int main(int argc, char *argv[]) {
        range I;
        argparse(argc, argv, &I.start, &I.stop, &I.step);
        for(range_init(&I); range_run(&I); range_next(&I))
                printf("%d\n", range_get(&I));
        return 0;
}