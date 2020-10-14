void sort_array(int copy_array[], int length_of_copy_array){
    for (int i = 0; i < length_of_copy_array - 1; ++i) {
        for (int j = 0; j < length_of_copy_array - i - 1; ++j) {
            if (copy_array[j] > copy_array[j+1]){
                int tmp = copy_array[j];
                copy_array[j] = copy_array[j+1];
                copy_array[j+1] = tmp;
            }
        }
    }
}

