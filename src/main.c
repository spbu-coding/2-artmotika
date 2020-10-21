#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT_OF_NUMBERS 100

#ifndef __APPLE__
# define sort_array _sort_array
#endif

extern void sort_array(int reduced_numbers_sorted[], int count_of_reduced_elements);

struct interval_t{
    int from_interaval;
    int to_interval;
};

int check_arguments(int argc, char* argv[], struct interval_t* interval, int* count_from, int* count_to){
    int temp_from = *count_from;
    int temp_to = *count_to;
    if (argc < 2) {
        return -1;
    } else if (argc > 3) {
        return -2;
    }
    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "--from=", strlen("--from=")) == 0) {
            interval->from_interaval = strtoll(argv[i] + strlen("--from="), NULL, 10);
            *count_from = temp_from + 1;
            temp_from = *count_from;
        } else if (strncmp(argv[i], "--to=", strlen("--to=")) == 0) {
            interval->to_interval = strtoll(argv[i] + strlen("--to="), NULL, 10);
            *count_to = temp_to + 1;
            temp_to = *count_to;
        }
    }
    if (*count_from > 1 || *count_to > 1) {
        return -3;
    } else if (*count_from == 0 && *count_to == 0) {
        return -4;
    }
    return 0;
}

void reduce_array(int array_numbers[], int* length_array, int array_numbers_copy[], struct interval_t interval,
        int count_from, int count_to){
    int temp_length_array = *length_array;
    for (int k = 0; k < MAX_COUNT_OF_NUMBERS; k++) {
        int number;
        char white_space;
        if (scanf("%d%c", &number, &white_space) != 2) {
            break;
        }
        int is_number_in_interval = 0;
        if (count_from == 1 && number <= interval.from_interaval) {
            fprintf(stdout, "%d ", number);
            is_number_in_interval ++;
        }
        if (count_to == 1 && number >= interval.to_interval) {
            fprintf(stderr, "%d ", number);
            is_number_in_interval ++;
        }
        if (!is_number_in_interval) {
            array_numbers[*length_array] = number;
            array_numbers_copy[*length_array] = number;
            *length_array = temp_length_array + 1;
            temp_length_array = *length_array;
        }
        if (white_space != ' ') {
            break;
        }
    }
}

int compare_arrays(int array1[], int array2[], int length_array) {
    int difference_count = 0;
    for(int i = 0; i < length_array; i++) {
        if(array1[i] != array2[i])
            difference_count++;
    }
    return difference_count;
}

int main(int argc, char* argv[]) {
    struct interval_t interval;
    int array_numbers[MAX_COUNT_OF_NUMBERS], array_numbers_copy[MAX_COUNT_OF_NUMBERS], length_array = 0;
    int count_from = 0, count_to = 0;
    check_arguments(argc, argv, &interval, &count_from, &count_to);
    reduce_array(array_numbers, &length_array, array_numbers_copy, interval, count_from, count_to);
    sort_array(array_numbers, length_array);
    int changed_elements = compare_arrays(array_numbers, array_numbers_copy, length_array);
    return changed_elements;
}
