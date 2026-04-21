#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "utils.h"

HashErr_t Fill_Hashtable(Hashtab_t* hashtab, char** word_buf) {
    assert(hashtab);
    assert(word_buf);

    char* word_ptr = word_buf[0];

    for (size_t word_cnt = 0;  (word_ptr = word_buf[word_cnt]) != NULL;  word_cnt++) 
        Hashtab_Addelem(hashtab, word_ptr);

    return no_errors;
}

HashErr_t UnitTest_Hashtab_Find(Hashtab_t* hashtab, char** word_buf) {
    assert(hashtab);
    assert(word_buf);

    char* word_ptr = word_buf[0];
    
    for (size_t word_cnt = 0;  (word_ptr = word_buf[word_cnt]) != NULL;  word_cnt++) 
        Hashtab_Find(hashtab, word_ptr);

    return no_errors;
}

char** Create_Wordbuf(char* text_buf) {
    assert(text_buf);

    size_t start_bufsize = 50000;

    char** word_buf   = (char**) calloc(start_bufsize, sizeof(word_buf[0]));
    char*  word_start = text_buf;
    char*  next_char  = text_buf;

    size_t word_cnt = 0;

    for (word_cnt = 0;  *next_char != '$';  word_cnt++) 
    {
        if (word_cnt >= start_bufsize - 1) 
        {
            start_bufsize *= 2;                    
            word_buf = (char**) realloc(word_buf, start_bufsize * sizeof(word_buf[0]));
        }

        word_start = next_char;

        while ( ! isspace(*next_char) )
            next_char++ ;

        *next_char = '\0';
        next_char++ ;
        skip_space(&next_char);
        
        word_buf[word_cnt] = word_start;
    }

        word_buf[word_cnt] = NULL;

    return word_buf;
}

char* Read_file2buf(FILE* input_file) {
    assert(input_file);

    struct stat file_info;

    int file_descriptor = fileno(input_file);

    SAFE_FSTAT(file_descriptor, &file_info);

    size_t size_of_file = file_info.st_size;

    SAFE_CALLOC(text_buf, size_of_file + 2, char);

    SAFE_FREAD(text_buf, sizeof(char), size_of_file, input_file);

    text_buf[size_of_file]     = ' ';
    text_buf[size_of_file + 1] = '$';

    return text_buf;
}

int Collect_Stat(HashData_t obj, size_t table_idx) {
    assert(obj);
    return fprintf(Statfile, "%s\t%d\n", obj, table_idx);
    // return fprintf(Statfile, "%d\n", table_idx);
}

int skip_space(char** str) {
    assert(str);
    assert(*str);
    
    int count_of_space = 0;

    while( isspace(**str) ) 
    {
        count_of_space++ ;
        (*str)++ ;
    }

    return count_of_space;
}