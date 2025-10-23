#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "mini_lib.h"

#define BUF_SIZE 1024

char* buffer = NULL;
int ind = -1;

void mini_printf(char* line)
{
    char target = '\n';
    if(ind == -1) {
        buffer = (char*) mini_calloc(sizeof(char), BUF_SIZE);
        ind = 0;
    }
    int i = 0; // creation of an int i to unlink the route of the buffer and the line
    while (line[i] != '\0'){
        buffer[ind] = line[i];
        ind++; // we put the post-incrementation of ind here because we ind to represent the first emptycell of our buffer
        if(buffer[ind-1] == target || ind >= BUF_SIZE) {
            write(STDOUT_FILENO, buffer, ind);
            ind = 0;
        }
        i++;
    }
}

void empty()
{
    if(buffer != NULL && ind > 0 && ind < BUF_SIZE) {
        write(STDOUT_FILENO, buffer, ind);
        mini_free(buffer);
        buffer = NULL;
        ind = -1;
    }
}

int mini_scanf(char* buffer, int size_buffers)
{
    int nb = read(STDIN_FILENO, buffer, size_buffers);
    if(nb == 0) {
        mini_printf("Not enough characters \n");
    }
    if(nb < 0) {
        mini_printf("Error");
        return -1;
    }
    buffer[nb] = '\0';
    return nb;
}

int mini_strlen(char* s)
{
    if(s == NULL)
        return -1;
    int i = 0;
    while(s[i] != '\0') {
        i++;
    }
    return i;
}

int mini_strcopy(char* s, char* d)
{
    if(s == NULL || d == NULL)
        return -1;
    int i;
    int nb = mini_strlen(s);
    for (i = 0; i < nb; i++) {
        ((char*)d)[i] = '\0';
    }
    i=0;
    while(s[i] != '\0') {
        d[i] = s[i];
        i++;
    }
    return i;
}

int mini_strcmp(char* s1, char *s2)
{
    if(s1 == NULL || s2 == NULL){
        mini_printf("Error\n");
        return -1;
    }
    int i = 0;
    while(s1[i] != '\0' && s2[i] != '\0') {
        if(s1[i] != s2[i]) {
            return -1;
        }
        i++;
    }
    return 0;
}

void mini_perror(char* message)
{
    switch (errno) {
        case 0: 
             mini_printf(message);
             mini_printf("0\n");
             return;
        case EPERM: 
             mini_printf(message);
             mini_printf("EPERM\n");
             return;
        case ENOENT: 
             mini_printf(message);
             mini_printf("ENOENT\n");
             return;
        case ESRCH: 
             mini_printf(message);
             mini_printf("ESRCH\n");
             return;
        case EINTR: 
             mini_printf(message);
             mini_printf("EINTR\n");
             return;
        case EIO: 
             mini_printf(message);
             mini_printf("EIO\n");
             return;
        case ENOMEM: 
             mini_printf(message);
             mini_printf("ENOMEM\n");
             return;
        case EACCES: 
             mini_printf(message);
             mini_printf("EACESS\n");
             return;
        case EEXIST: 
             mini_printf(message);
             mini_printf("EEXIST\n");
             return;
        case ENOTDIR: 
             mini_printf(message);
             mini_printf("ENOTDIR\n");
             return;
        default: 
             mini_printf("Unknown error\n");
             return;
    }
}

