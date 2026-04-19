#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "prepare.h"

char* Read_file2buf(FILE* input_file, size_t* size_of_file) {
    assert(input_file);
    assert(size_of_file);

    struct stat file_info;

    int file_descriptor = fileno(input_file);

    SAFE_FSTAT(file_descriptor, &file_info);

    size_t temp_size_of_file = file_info.st_size;

    SAFE_CALLOC(text_buf, temp_size_of_file, char);

    SAFE_FREAD(text_buf, sizeof(char), temp_size_of_file, input_file);

    *size_of_file = temp_size_of_file;

    return text_buf;
}

void Prepare_File(char* text_buf, size_t sizeof_file) {
    assert(text_buf);

    for (char* cur_char = text_buf;  cur_char < text_buf + sizeof_file;  cur_char++)
    {
        char char_val = *cur_char;

        if (isalpha(char_val)) {
            *cur_char = tolower(char_val);
        
        } else if ( isspace(char_val) || char_val == '-' ) {
        
        } else {
            *cur_char = ' ';
        }
    }

    return;
}