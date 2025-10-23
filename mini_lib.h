#ifndef MINI_LIB
#define MINI_LIB

typedef struct malloc_element {
    void* addr;
    size_t size;;
    int statut;
    struct malloc_element *next_malloc;;
 } malloc_element;

typedef struct MYFILE {
    int fd;
    void* buffer_read;
    void* buffer_write;
    int ind_read;
    int ind_write;
    struct MYFILE* next_myfile;
 } MYFILE;


void* mini_calloc(int size_element, int number_element);

void mini_free(void* ptr);

void mini_printf(char* line);

void mini_exit();

void empty();

int mini_scanf(char* buffer, int size_buffers);

int mini_strlen(char* s);

int mini_strcopy(char* s, char* d);

int mini_strcmp(char* s1, char *s2);

void mini_perror(char* message);

void init_MYFILE(MYFILE* file);

MYFILE* mini_fopen(char* file, char mode);

int mini_fread (void* buffer, int size_element, int number_element, MYFILE* file);

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);

int mini_fflush(MYFILE* file);

int mini_fclose(MYFILE* file);

int mini_fgetc(MYFILE* file);

int mini_fputc(MYFILE* file, char c);

#endif