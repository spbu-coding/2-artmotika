#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "sort.h"

#define MAX_INPUT_STRING_LENGTH 12000 //одно число может быть длины порядка 11 символов + пробелы
#define MAX_INPUT_CHAR_NUMBER 11
#define MAX_COUNT_OF_NUMBERS 100
#define SMALLEST_NUMBER -2147483648
#define BIGGEST_NUMBER 2147483647
#define stderr_printf(...) fprintf(stderr, __VA_ARGS__)

extern void sort_array(int copy_array[], int length_of_copy_array);

struct interval_t {
    long long from;
    long long to;
};

int parse_argv(int argc, char* argv[], struct interval_t* interval) {
    int index_param_from = 0, index_param_to = 0;
    int number_of_params = 0;
    int from_flag = 0, to_flag = 0;
    int is_repeat = 0, last_index = 0;
    for(int i = 1; i < argc; i++) {
        int number_in_string;
        if (strncmp(argv[i], "--", 2) != 0){
            number_in_string = strtoll(argv[i], NULL, 10);
            if (strncmp(argv[last_index], "--from=", 7) == 0){
                interval->from = number_in_string;
            }else if (strncmp(argv[last_index], "--to=", 5) == 0){
                interval->to = number_in_string;
            }
        }else number_of_params ++;
        if(strncmp(argv[i], "--from=", 7) == 0) {
            number_in_string = strtoll(argv[i] + 7, NULL, 10);
            interval->from = number_in_string;
            from_flag = 1;
            if (index_param_from != 0) is_repeat = 1;
            index_param_from = i;
            last_index = index_param_from;
        }
        if(strncmp(argv[i], "--to=", 5) == 0) {
            number_in_string = strtoll(argv[i] + 5, NULL, 10);
            interval->to = number_in_string;
            to_flag = 1;
            if (index_param_to != 0) is_repeat = 1;
            index_param_to = i;
            last_index = index_param_to;
        }
        if (!from_flag && !to_flag || interval->from > interval->to){
            stderr_printf("Not valid params");
            return -4;
        }
    }

    if(number_of_params < 2) {
        stderr_printf("Number of params < 2");
        return -1; // Number of params < 2
    }else if(number_of_params > 2) {
        stderr_printf("Number of params > 2");
        return -2; // Number of params > 2
    }else if(is_repeat) {
        stderr_printf("Repeat of params (you must use --from and --to only one time)");
        return -3;
    }else return 0;
}

int determine_location(char input_string){
    switch (input_string) {
        case '1':return 1;
            break;
        case '2': return 1;
            break;
        case '3': return 1;
            break;
        case '4': return 1;
            break;
        case '5': return 1;
            break;
        case '6': return 1;
            break;
        case '7': return 1;
            break;
        case '8': return 1;
            break;
        case '9': return 1;
            break;
        case '0': return 1;
            break;
        case '-': return 1;
            break;
        default: return 0;
    }
}

int make_integer(char* number_string, int length_number_string){
    int dozens = 1;
    int number = 0;
    if (number_string[0] == '-'){
        for (int i = length_number_string - 1; i > 0; i--) {
            number -= ((int)number_string[i] - 48) * dozens;
            dozens *= 10;
        }
    }else{
        for (int i = length_number_string - 1; i >= 0; i--){
            number += ((int)number_string[i] - 48) * dozens;
            dozens *= 10;
        }
    }
    return number;
}

int count_length(char* input_string){
    int length_of_string = 0, i = 0;
    while (determine_location(input_string[i])){
        length_of_string ++;
        i ++;
    }
    return length_of_string;
}

void delete_string(char* number_string, int length_number_string){
    for (int i = 0; i < length_number_string; ++i) {
        number_string[i] = ' ';
    }
}

int parse_input_string(char* input_string, int array[]){
    int length_number_string;
    char number_string[MAX_INPUT_CHAR_NUMBER];
    int index_array = 0;
    int c = 0;
    for (int i = 0; i < MAX_INPUT_STRING_LENGTH; ++i) {
        if (determine_location(input_string[i])) {
            number_string[c] = input_string[i];
            c ++;
        } else {
            length_number_string = count_length(number_string);
            if (length_number_string > 0) {
                array[index_array] = make_integer(number_string, length_number_string);
                delete_string(number_string, length_number_string);
                index_array ++;
                c = 0;
            }else break;
        }
    }
    int length_of_array = index_array;
    return length_of_array;
}

int copy_array_limitations(int array[], int array_copy[], int length_of_array, struct interval_t interval, int Stdout[], int Stderr[],
        int* index_Stdout, int* index_Stderr){
    int index_array = 0;
    Stdout[0] = SMALLEST_NUMBER;
    Stderr[0] = SMALLEST_NUMBER;
    for (int i = 0; i < length_of_array; ++i) {
        if (interval.from >= SMALLEST_NUMBER && interval.to <= BIGGEST_NUMBER){
            if (array[i] > interval.from && array[i] < interval.to){
                array_copy[index_array] = array[i];
                index_array ++;
            }else{
                if (array[i] <= interval.from) {
                    Stdout[*index_Stdout] = array[i];
                    *index_Stdout += 1;
                }else if (array[i] >= interval.to){
                    Stderr[*index_Stderr] = array[i];
                    *index_Stderr += 1;
                }
            }
        }else if (interval.from >= SMALLEST_NUMBER && interval.to == BIGGEST_NUMBER){
            if (array[i] > interval.from){
                array_copy[index_array] = array[i];
                index_array ++;
            }else{
                Stdout[*index_Stdout] = array[i];
                *index_Stdout += 1;
            }
        }else if (interval.from == SMALLEST_NUMBER && interval.to <= BIGGEST_NUMBER){
            if (array[i] < interval.to){
                array_copy[index_array] = array[i];
                index_array ++;
            }else{
                Stderr[*index_Stderr] = array[i];
                *index_Stderr += 1;
            }
        }
    }
    return index_array;
}

void copy_array(int array_copy[], int array_copy2[], int length_of_copy_array){
    for (int i = 0; i < length_of_copy_array; ++i) {
        array_copy2[i] = array_copy[i];
    }
}



int compare_arrays(const int array1[], const int array2[], int length_of_copy_array) {
    int difference_count = 0;
    for(int i = 0; i < length_of_copy_array; i++) {
        if(array1[i] != array2[i])
            difference_count++;
    }
    return difference_count;
}

int main(int argc, char* argv[]) {

    struct interval_t interval = {SMALLEST_NUMBER, BIGGEST_NUMBER};

    int parse_return_code = parse_argv(argc, argv, &interval);
    if(parse_return_code != 0 && parse_return_code != -1)
        return parse_return_code;

    int array[MAX_COUNT_OF_NUMBERS], array_copy[MAX_COUNT_OF_NUMBERS];
    char input_string[MAX_INPUT_STRING_LENGTH];
    scanf("%[^\n]s", input_string);

    int length_of_array = parse_input_string(input_string, array);

    int Stdout[MAX_COUNT_OF_NUMBERS], Stderr[MAX_COUNT_OF_NUMBERS];
    int index_Stdout = 0, index_Stderr = 0;
    int length_of_copy_array = copy_array_limitations(array, array_copy, length_of_array, interval, Stdout, Stderr, &index_Stdout,
                                          &index_Stderr);
    int array_copy2[length_of_copy_array];
    copy_array(array_copy, array_copy2, length_of_copy_array);

    printf("Stdout: ");
    if (Stdout[0] == SMALLEST_NUMBER) {
        printf("- ");
    }else{
        for (int i = 0; i < index_Stdout; ++i) {
            printf("%d ", Stdout[i]);
        }
    }

    printf("Stderr: ");
    if (Stderr[0] == SMALLEST_NUMBER){
        printf("- ");
    }else{
        for (int i = 0; i < index_Stderr; ++i) {
            printf("%d ", Stderr[i]);
        }
    }

    printf("Reduced: ");
    for (int i = 0; i < length_of_copy_array; ++i) {
        printf("%d ", array_copy[i]);
    }

    sort_array(array_copy, length_of_copy_array);
    printf("Sorted: ");
    for (int i = 0; i < length_of_copy_array; ++i) {
        printf("%d ", array_copy[i]);
    }

    return compare_arrays(array_copy, array_copy2, length_of_copy_array);
}