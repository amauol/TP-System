#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mini_lib.h"

extern malloc_element* malloc_list;

#include <stdio.h>
#include "mini_lib.h"

extern malloc_element* malloc_list;

int main()
{
    int* array;
    int num_elements = 5;
    array = (int*) mini_calloc(sizeof(int), num_elements);
    if(array == NULL) {
        mini_perror("Functiun do not functiun\n");
        return 1;
    }
    for(int i = 0; i < num_elements; i++) {
        array[i] = i*i;
        printf("array(%i)  = %i\n", i, array[i]);
    }
    printf("Check if array is correctly use : %i \n",malloc_list->statut);
    mini_free(array);
    printf("Liberation of array : %i \n",malloc_list->statut);

    printf("\n");
    mini_printf("Check if is it ok \n");
    mini_printf("Without break line \n");

    char* string = (char*)mini_calloc(sizeof(char), 20);
    if (string == NULL) {
        mini_perror("Error of allocation\n");
        return 1;
    }

    mini_printf("Please, write your texte (max 20 characters) : \n");
    int nb_chars = mini_scanf(string, 20);  // read on the standard input

    if (nb_chars >= 0) {
        printf("Texte readen : %s\nNumber of readen characters : %d\n", string, nb_chars);
    } else {
        mini_perror("Error of read\n");
    }

    mini_free(string);  // free of the memory

    int test_1 = mini_strlen("Check if is ok !!!!\n");
    printf("There %i characters \n", test_1);

    char* string_2 = (char*) mini_calloc(sizeof(char), 20);
    if (string_2 == NULL) {
        mini_perror("Error of allocation\n");
        return 1;
    }
    
    int test_2 = mini_strcopy("Check if is it ok\n", string_2);
    printf("Number of characters copied : %i\n", test_2);
    for(int i = 0; i < 18; i++)
        printf("%c ", (char)string_2[i]); // to check if teh string in string_2 is the correct one

    
    int test_3 = mini_strcmp("Hello world!\n", "Check if is ok\n"); // test the functiun with two string
    printf("Result :%i\n", test_3);

    
    MYFILE* file_1 = (MYFILE*) mini_calloc(sizeof(MYFILE), 1024);  // allocation of enough space memory for file
    if (file_1 == NULL) {
        mini_perror("Memory allocation failed\n");
        return 1;
    }
    init_MYFILE(file_1);
    
    file_1 = mini_fopen("titi.txt", 'r'); // we use the functiun mini_fopen to fill different informations for file_1

    char buffer_1[1024];
    int test_4 = mini_fread(&buffer_1, sizeof(char), 28, file_1);
    printf("Characters read : %i\n", test_4);
    for(int i =0; i < test_4; i++) {
        printf("%c\n", ((char*)buffer_1)[i]);
    }
    
    mini_fclose(file_1);
    

    MYFILE* file_2 = (MYFILE*) mini_calloc(sizeof(MYFILE), 1024); 
    if (file_2 == NULL) {
        mini_perror("Memory allocation failed\n");
        return -1;
    }
    init_MYFILE(file_2);

    file_2 = mini_fopen("toto.txt", 'w'); // we use the functiun mini_fopen to fill different informations for file_2 ()
    if (file_2->fd == -1) {
        mini_perror("Error opening file\n");
        return -1;
    }

    char* buffer_2 = "Check if it works";
    int test_5 = mini_fwrite(buffer_2, sizeof(char), mini_strlen(buffer_2), file_2);
    printf("Characters written: %i\n", test_5);
    for(int i =0; i < mini_strlen(buffer_2); i++)
        printf("%c\n", ((char*)file_2->buffer_write)[i]);
    
    
    mini_fclose(file_2);


    MYFILE* file_3 = (MYFILE*) mini_calloc(sizeof(MYFILE), 1024); 
    if (file_3 == NULL) {
        mini_perror("Memory allocation failed\n");
        return -1;
    }
    init_MYFILE(file_3);

    file_3 = mini_fopen("tata.txt", 'r'); // we use the functiun mini_fopen to fill different informations for file_2
    if (file_3->fd == -1) {
        mini_perror("Error opening file\n");
        return -1;
    }

    char dead = mini_fgetc(file_3);
    printf("Character read : %c\n", dead);
    
    mini_fclose(file_3);


    MYFILE* file_4 = (MYFILE*) mini_calloc(sizeof(MYFILE), 1024); 
    if (file_4 == NULL) {
        mini_perror("Memory allocation failed\n");
        return -1;
    }
    init_MYFILE(file_4);

    file_4 = mini_fopen("tete.txt", 'w'); // we use the functiun mini_fopen to fill different informations for file_2 ()
    if (file_4->fd == -1) {
        mini_perror("Error opening file\n");
        return -1;
    }

    int d = mini_fputc(file_4, 'z');
    if(d == -1) 
        mini_perror("Can't write \n");
    
    mini_fclose(file_4);

    mini_exit();
}

