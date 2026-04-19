#ifndef MYLISTLIB
#define MYLISTLIB

typedef char* ListData_t;

struct List_t {
    size_t      size;
    ListData_t* data;
    int*        next;
    int*        prev;
    size_t      free;
};

extern FILE* Statfile;  // !!! THIS FILE RELATES TO HASHTABLE, BUT I DONT WANT TO CREATE .h FILE FOR ONLY ONE DECLARATION !!! 
extern FILE* Text;      // YOU CAN DELETE THIS DECLARATION IF YOU DONT USE THESE IN YOUR PROJECT
                        
extern ListData_t POISON;

enum Utils_Constants {
    MAX_FILE_COUNT    = 32,
    MAX_DUMP_INFO_LEN = 128,
    NO_INDEX          = -1
};

enum Successful_ending {
    UNIT_TEST_PASSED = 0,
    IS_FREE          = 1,
    NOT_FREE         = 0
};

enum Errors_and_warnings {
    NO_ERRORS         = 0,
    DELETE_NULL_EL    = 1,  
    NO_MORE_FILES     = 1 << 1, 
    FILE_NAME_ERR     = 1 << 2, 
    UNIT_TEST_FAILED  = 1 << 3, 
    INCOR_ACTION_DUMP = 1 << 4, 
    MIN_CRITICAL_ERR  = 1 << 8,     // Isn`t error. It`s just constant, after which follows not critical errors (warnings)
    NULLP_TO_STRUCT   = 1 << 8, 
    NULLP_TO_DATA     = 1 << 9, 
    NULLP_TO_NEXT     = 1 << 10, 
    NULLP_TO_PREV     = 1 << 11, 
    HEAD_OUT_OF_BUF   = 1 << 12, 
    TAIL_OUT_OF_BUF   = 1 << 13, 
    FREE_OUT_OF_BUF   = 1 << 14, 
    INCOR_INDEX       = 1 << 15,
    REALLOC_ERR       = 1 << 16, 
    CYCLE_ERR         = 1 << 17
};

typedef Errors_and_warnings ListErr_t;

List_t* List_Ctor  (size_t size);
ListErr_t   List_Dtor  (List_t* list);

int         List_Insert_after (List_t* list, size_t idx, ListData_t value);
int         List_Insert_before(List_t* list, size_t idx, ListData_t value);
int         List_Insert_Head  (List_t* list, ListData_t value);
int         List_Insert_Tail  (List_t* list, ListData_t value);
ListErr_t   List_Delete       (List_t* list, size_t idx);
List_t*     List_Realloc      (List_t* list);
ListData_t  List_Find         (List_t* list, ListData_t value);

size_t      get_head (List_t* list);
size_t      get_tail (List_t* list);
size_t      get_free (List_t* list);
ListData_t  get_data (List_t* list, size_t idx);
int         get_next (List_t* list, size_t idx);
int         get_prev (List_t* list, size_t idx);


#define DATA(list)   (list)->data
#define NEXT(list)   (list)->next
#define PREV(list)   (list)->prev


#define SAFE_CALLOC(name, size_of_buf, el_type)                                                             \
    el_type* temp_##name = (el_type*) calloc(size_of_buf, sizeof(el_type));                                 \
                                                                                                            \
    if (temp_##name == NULL)                                                                                \
        fprintf(stderr, "Allocation error of " #name " in %s (%s:%d)\n", __func__, __FILE__, __LINE__);     \
                                                                                                            \
    el_type* name = temp_##name;    
    
#define SAFE_FOPEN(name, file, mode)                                                                        \
    FILE* temp_##name = fopen(file, mode);                                                                  \
                                                                                                            \
    if (temp_##name == NULL)                                                                                \
        fprintf(stderr, "File opening error (" #name ") in %s (%s:%d)\n", __func__, __FILE__, __LINE__);    \
                                                                                                            \
    FILE* name = temp_##name; 

#define SAFE_FSTAT(describtor, ptr_to_stat_struct)                                                          \
    int stat_check_##file = fstat(describtor, ptr_to_stat_struct);                                          \
                                                                                                            \
    if (stat_check_##file == -1)                                                                            \
        fprintf(stderr, "File stat error in function %s in %s:%d\n", __func__, __FILE__, __LINE__);         \
    

#define SAFE_FREAD(buffer, size_of_elem, count_of_elem, file)                                                                               \
    int fread_check_##file = fread(buffer, size_of_elem, count_of_elem, file);                                                              \
                                                                                                                                            \
    if (fread_check_##file < count_of_elem)                                                                                                 \
        fprintf(stderr, "Warning: error in fread or fread did not read any symbols (%s in %s:%d)\n", __func__, __FILE__, __LINE__);         \


    ListErr_t List_Dump         (List_t* list, const char* dump_info);
    ListErr_t List_Dump_graphviz(List_t* list, FILE* output_file);
    ListErr_t List_Dump_HTML    (List_t* list, const char* image, const char* dump_info, FILE* output_file);

    int is_free (List_t* list, size_t idx);


#define SHAPE   "shape = Mrecord, "
#define STYLE   "style = \"filled\", "

                /*COLORS*/

#define BRIGHT_GREEN    "\"#C0FFC0\""                
#define BRIGHT_RED      "\"#FFC0C0\""
#define BRIGHT_BLUE     "\"#C0C0FF\""
#define BRIGHT_YELLOW   "\"#ffff94ff\""
#define YELLOW          "\"#cdcd00ff\""

#endif