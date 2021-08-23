#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "general.h"

typedef enum bool {false, true} bool;

struct node {
   double i;
   struct node* next;
};
typedef struct node node;

struct stack {
   node* start;
   int size;
};
typedef struct stack stack;

/* Create an empty stack for Reverse Polish */
stack* stack_init(void);

/* Add element to top */
void stack_push(stack* s, double j);

/* Take element from top */
bool stack_pop(stack* s, double* d);

/*  */
bool stack_peek(stack* s, double* d);

/* Clears all space used */
bool stack_free(stack* s);
