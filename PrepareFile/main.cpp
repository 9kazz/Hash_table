#include <stdio.h>
#include <ctype.h>

#include "prepare.h"

int main() {

    FILE* raw_text      = fopen("../Files/Rawtext.txt", "r");
    FILE* prepared_text = fopen("../Files/Text.txt", "w");

    size_t sizeof_file = 0;
    char*  text_buf    = Read_file2buf(raw_text, &sizeof_file);

    Prepare_File(text_buf, sizeof_file);

    fwrite(text_buf, sizeof(char), sizeof_file, prepared_text);
    
    return 0;
}
