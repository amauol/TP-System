#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "mini_lib.h"

malloc_element* malloc_list = NULL;
extern MYFILE* myfile_list;

void* mini_calloc(int size_element, int number_element)
{
    int total_size = number_element*size_element;
    void* buf; //creation of a generic pointer to use it for point the memory space
    buf = sbrk(total_size); // allocation of enough memeory space
    if(buf == (void*)-1) { // check if the system call sbrk works properly
        mini_perror("Functiun do not work correctly\n");
        return NULL;
    }
    
    for (int i = 0; i < total_size; i++) {
        ((char*)buf)[i] = '\0'; // initialize the buffer with '\0'
    }
    malloc_element* buffer = (malloc_element*) malloc(sizeof(malloc_element)); // creation of a pointer on the structure malloc_element to stock all the infromations about buffer created previously
    
    buffer->addr = buf;
    buffer->size = total_size;
    buffer->statut = 1;
    buffer->next_malloc = NULL;
    if(malloc_list != NULL) { // check if our list is NULL or not
        malloc_element* instant = malloc_list; // create a pointer on the first element of our list
        while(instant != NULL) { // first loop while to check if reuse of a previous memory space is okay (check each current element of our list)
                if(instant->statut == 0 && instant->size >= total_size) { 
                    instant->statut = 1; // put the status in 1 because it was 0 due to mini_free
                    bzero(instant->addr, instant->size);
                    return instant->addr;
                }
            instant = instant->next_malloc;
        }
        instant = malloc_list; // we put again instant at the beginning of our list to second loop while
        while(instant->next_malloc != NULL) {  // the second loop while is too add an element at the end of our list
            instant = instant->next_malloc;
        }
        instant->next_malloc = buffer;
    }
    else {
        malloc_list = buffer;
    }
    return buf;
}

void mini_free(void* ptr)
{
    malloc_element* current = malloc_list;
    while(current != NULL) { // this loop while checks all the malloc_element in our list to see anyone is NULL
       if(current->addr == ptr) {
            current->statut = 0;
            return;
        } 
        current = current->next_malloc;
    }
    printf("Adress not found \n"); // this final line specify to the complir what to do if current is NULL
}


void mini_exit()
{
    empty();
    MYFILE* current = myfile_list;
    while(current->next_myfile != NULL) {
        mini_fclose(current);
        current = myfile_list->next_myfile;
    }
    _exit(EXIT_SUCCESS);
}
