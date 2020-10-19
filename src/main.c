#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __APPLE__
# define sort_array _sort_array
#endif

#define MAX_COUNT_OF_NUMBERS 100

extern void sort_array(long long reduced_numbers_sorted[], int count_of_reduced_elements);

struct interval_t {
    long long from;
    long long to;
};

int check_arguments(int argc, char* argv[]) {
    if (argc < 2) {
        return -1;
    }
    if (argc > 3) {
        return -2;
    }
    if (argc  == 3) {
        if (!(strncmp(argv[1], "--to=", 5) == 0 || strncmp(argv[1], "--from=", 7) == 0) &&
        !(strncmp(argv[2], "--to=", 5) == 0 || strncmp(argv[2], "--from=", 7) == 0)){
            return -4;
        }
        if ((strncmp(argv[1], argv[2], 5) == 0) || (strncmp(argv[1], argv[2], 7) == 0)){
            return -3;
        }
    }
    if (argc == 2) {
        if (!(strncmp(argv[1], "--to=", 5) == 0 || strncmp(argv[1], "--from=", 7) == 0)) {
            return -4;
        }
    }
    return 0;
}

void scan_arguments(int argc, char* argv[], struct interval_t* interval) {
    long long from = 0, to = 0;
    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "--to=", 5) == 0 || strncmp(argv[i], "--from=", 7) == 0) {
            if (strncmp(argv[i], "--from=", 5) == 0) {
                if (strtoll(argv[i] + 7, NULL, 10)) {
                    from = strtoll(argv[i] + 7, NULL, 10);
                }
            }
            if (strncmp(argv[i], "--to=", 5) == 0) {
                if (strtoll(argv[i] + 5, NULL, 10)) {
                    to = strtoll(argv[i] + 5, NULL, 10);
                }
            }

        }
    }
    interval->from = from;
    interval->to = to;
}

void read_array(long long array[], int* count_of_elements) {
    char c;
    int i = 0;
    scanf("%lli%c", &array[i], &c);
    while (c != '\n') {
        i++;
        scanf("%lli%c", &array[i], &c);
    }
    *count_of_elements = i + 1;
}

void reduce_numbers(long long array_of_numbers[], long long Stdout[], long long reduced_numbers[],
                        int count_of_elements, long long Stderr[], struct interval_t interval, int* count_of_Stderr,
                        int* count_of_Stdout, int* reduced_count) {
    int count_Stdout = 0;
    int count_Stderr = 0;
    int count_reduced = 0;
    for (int i = 0; i < count_of_elements; i++) {
        if (array_of_numbers[i] <= interval.from && interval.from != 0) {
            Stdout[count_Stdout] = array_of_numbers[i];
            count_Stdout++;
        }
        if (array_of_numbers[i] >= interval.to && interval.to != 0) {
            Stderr[count_Stderr] = array_of_numbers[i];
            count_Stderr++;
        }
        if ((array_of_numbers[i] > interval.from && (array_of_numbers[i] < interval.to || interval.to == 0)) ||
        (array_of_numbers[i] < interval.to && interval.from == 0)){
            reduced_numbers[count_reduced] = array_of_numbers[i];
            count_reduced++;
        }
    }
    *count_of_Stdout = count_Stdout;
    *count_of_Stderr = count_Stderr;
    *reduced_count = count_reduced;
}

void copy_array(long long copy_from[], long long copy_to[], int count_of_elements) {
    for (int i = 0; i < count_of_elements; i++) {
        copy_to[i] = copy_from[i];
    }
}

void display_std(long long Stdout[], int count_of_Stdout, long long Stderr[], int count_of_Stderr) {
    for (int i = 0; i < count_of_Stdout; i++) {
        fprintf(stdout, "%lli ", Stdout[i]);
    }
    for (int i = 0; i < count_of_Stderr; i++) {
        fprintf(stderr, "%lli ", Stderr[i]);
    }
}

int compare_arrays(long long array1[], long long array2[], int count_of_reduced_elements) {
    int difference_count = 0;
    for(int i = 0; i < count_of_reduced_elements; i++) {
        if(array1[i] != array2[i])
            difference_count++;
    }
    return difference_count;
}

int main(int argc, char* argv[]) {
    struct interval_t interval = {0, 0};

    long long array_of_numbers[MAX_COUNT_OF_NUMBERS], Stdout[MAX_COUNT_OF_NUMBERS], Stderr[MAX_COUNT_OF_NUMBERS],
    reduced_numbers[MAX_COUNT_OF_NUMBERS], reduced_numbers_sorted[MAX_COUNT_OF_NUMBERS];

    int count_of_elements = 0, count_of_Stdout = 0, count_of_Stderr = 0, count_of_reduced_elements = 0;

    int check_arguments_return_code = check_arguments(argc, argv);
    if (check_arguments_return_code) {
        return check_arguments_return_code;
    }
    scan_arguments(argc, argv, &interval);
    read_array(array_of_numbers, &count_of_elements);
    reduce_numbers(array_of_numbers, Stdout, reduced_numbers, count_of_elements, Stderr,
                       interval, &count_of_Stderr, &count_of_Stdout, &count_of_reduced_elements);
    copy_array(reduced_numbers, reduced_numbers_sorted, count_of_reduced_elements);
    sort_array(reduced_numbers_sorted, count_of_reduced_elements);

    int count_of_changed_elements = compare_arrays(reduced_numbers, reduced_numbers_sorted, count_of_reduced_elements);
    display_std(Stdout, count_of_Stdout, Stderr, count_of_Stderr);
    return count_of_changed_elements;
}