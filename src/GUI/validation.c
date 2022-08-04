#include "validation.h"

int get_file_name(char* absolute_path, char* file_name) {
    int last_slash_index = -1;
    for (int i = 0; absolute_path[i] != '\0'; i++) {
        if (absolute_path[i] == '/')
            last_slash_index = i;
    }
    for (int i = last_slash_index + 1, j = 0; absolute_path[i] != '\0'; i++) {
        file_name[j++] = absolute_path[i];
    }
    return last_slash_index;
}

int rgb_processing(char* rgb) {
    int errors = 0;
    if (rgb[0] != '0' && rgb[0] != '1')
        errors++;
    if (rgb[1]) {
        if (rgb[0] == '0' && rgb[1] == '.') {
            if (rgb[2] < '1' || rgb[2] > '9')
                errors++;
        } else {
            errors++;
        }
    }
    return errors;
}
