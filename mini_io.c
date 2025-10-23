#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "mini_lib.h"
#include <stdio.h>

#define IOBUFFER_SIZE 2048

void init_MYFILE(MYFILE* file) {
    file->fd = -1;
    file->buffer_read = NULL;
    file->buffer_write = NULL;
    file->ind_read = -1;
    file->ind_write = -1;
    file->next_myfile = NULL;
}

MYFILE* myfile_list = NULL;

MYFILE* mini_fopen(char* file, char mode)
{
    MYFILE* myfile;
    MYFILE* current = myfile_list;
    myfile->fd = -1; // to indicate that the buffer is not allocated yet
    switch(mode)
    {
        case 'r' : // a series of case to test consider each mode
            myfile->fd = open(file, O_RDONLY);
                if(myfile->fd == -1)
                    mini_printf("Error\n");
            if (myfile_list == NULL){
                myfile_list = myfile;
            }
            else {
                while(current->next_myfile != NULL) {
                    current = current->next_myfile;
                }
                current->next_myfile = myfile;
            }
            return myfile;
        case 'w' :
            myfile->fd = open(file, O_WRONLY);
            if(myfile->fd == -1)
                mini_printf("Error\n");
            if (myfile_list == NULL){
                myfile_list = myfile;
            }
            else {
                while(current->next_myfile != NULL) {
                    current = current->next_myfile;
                }
                current->next_myfile = myfile;
            }
            return myfile;
        case 'b' :        
            myfile->fd = open(file, O_RDWR);
            if(myfile->fd == -1)
                mini_printf("Error\n");
            if (myfile_list == NULL){
                myfile_list = myfile;
            }
            else {
                while(current->next_myfile != NULL) {
                    current = current->next_myfile;
                }
                current->next_myfile = myfile;
            }
            return myfile;
        case 'a' : 
            myfile->fd = open(file, O_APPEND);
            if(myfile->fd == -1)
                mini_printf("Error\n");
            if (myfile_list == NULL){
                myfile_list = myfile;
            }
            else {
                while(current->next_myfile != NULL) {
                    current = current->next_myfile;
                }
                current->next_myfile = myfile;
            }
            int decal = lseek(myfile->fd, 10, SEEK_SET);
            if(decal == -1)
                mini_perror("Error\n");
            return myfile;
    }
    mini_printf("Error\n");
    return myfile;
}

int mini_fread (void* buffer, int size_element, int number_element, MYFILE* file)
{
    if(file->ind_read == -1) { // if the buffer_read isn't allocated yet, we neeed to allocate it
        file->buffer_read = (char*) mini_calloc(size_element,IOBUFFER_SIZE);
        if(file->buffer_read == NULL) {
            return -1;
        }
        file->ind_read = 0;
    }
    int nb_read;
    int total = 0;
    if (file->fd == -1) {
        return -1;
    }
    while(total < number_element) {
        if(file->ind_read == IOBUFFER_SIZE || file->ind_read == 0) {
            nb_read = read(file->fd ,file->buffer_read, IOBUFFER_SIZE);
            if(nb_read == -1)
            {
                mini_perror("Can't read\n");
                return -1;
            }
            if(nb_read == 0) {
                return total;
            }
            file->ind_read = 0;
        }
        ((char*)buffer)[total] = ((char*)file->buffer_read)[file->ind_read];
        file->ind_read++;
        total++;
    }
    ((char*)buffer)[nb_read] = '\0';
    return total;
}

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file)
{
    if(file->ind_write == -1) { // if the buffer_read isn't allocated yet, we neeed to allocate it
        file->buffer_write = (char*) mini_calloc(size_element,IOBUFFER_SIZE);
        if(file->buffer_write == NULL) {
            return -1;
        }
        file->ind_write = 0;
    }
    int nb_write;
    int total = 0;
    if (file->fd == -1) {
        return -1;
    }
    while(total < number_element) {
        if(file->ind_write == IOBUFFER_SIZE) {
            nb_write = write(file->fd ,file->buffer_write, IOBUFFER_SIZE);
            if(nb_write == -1)
            {
                return -1;
            }
            if(nb_write == 0) {
                return total;
            }
            file->ind_write = 0;
        }
        ((char*)file->buffer_write)[total] = ((char*)buffer)[total];
        file->ind_write++;
        total++;
    }
    return total;   
}

int mini_fflush(MYFILE* file)
{
    if(file->buffer_write != NULL && file->ind_write > 0 && file->ind_write < IOBUFFER_SIZE) {
            int nb = write(file->fd, file->buffer_write, file->ind_write);
            if(nb < 0)
                return -1;
            mini_free(file->buffer_write);
            file->buffer_write = NULL;
            file->ind_write = -1;
    }
    return 0;
}

int mini_fclose(MYFILE* file)
{
    mini_fflush(file);
    int nb = close(file->fd);
    if(nb < 0)
        return -1;
    MYFILE* current = myfile_list;
    MYFILE* previous = NULL;
    while (current != NULL) { // check each file of the list
        if (current == file) {
            if (previous == NULL) { // with that condition, we can check if file is the first element of myle_list
                myfile_list = current->next_myfile; // if it's the first elemeent, we put the pointer myfile_list to the next element
            } else {
                previous->next_myfile = current->next_myfile; // if it's not the first element, we use previous to change the current one
            }
            mini_free(current); // put the file->status at 0, free the memory
            return 0; 
        }
        previous = current; // at the end of each test, at each iteration, we "move forward" previous and current 
        current = current->next_myfile;
    }
    return -1;
}


int mini_fgetc(MYFILE* file)
{
    int buffer_size;
    if(file == NULL)
        return -1;
    if(file->buffer_read == NULL || file->ind_read == -1) {
        file->buffer_read = (char*) mini_calloc(sizeof(char),IOBUFFER_SIZE);
        if (file->buffer_read == NULL) {
        mini_perror("Memory allocation failed for buffer_read\n");
        return -1;
        }
    }
    buffer_size = mini_fread(file->buffer_read, sizeof(char), 1, file); // we use mini_fread on the buffer_read
    if(buffer_size == -1)
        return -1;
    file->ind_read = 0; // once we read, we put the index at 0
    char c = ((char*)file->buffer_read)[file->ind_read]; // we copy a certain character located <ith a specific index
    return c;
}

int mini_fputc(MYFILE* file, char c)
{
    int buffer_size;
    if(file == NULL)
        return -1;
    buffer_size = mini_fwrite(&c, sizeof(char), 1, file);
    if(buffer_size == -1)
        return -1;
    return 1;
}

