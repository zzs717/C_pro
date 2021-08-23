#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "general.h"

#define NUMTOKENS 10
#define MAXTOKENSIZE 30
#define resize 2

/*use an array to store the program */
struct commandlist {
    char **wds;
    int capacity;
    int size;   /* resize the array when size>0.8*capacity */
    int cw;     /* Current Word */
    int num1;   /* Number of "{" */
    int num2;   /* Number of "}" */
};
typedef struct commandlist commandlist;

/*Creat an array to store the program */
commandlist* commandlist_init();

/*Add command to the array */
void commandlist_insert(commandlist** a, char* key);

/* Clears all space used */
void commandlist_free(commandlist* a);

/* Read commands from file */
void readfile(char* fname, char* mode,commandlist*a);
