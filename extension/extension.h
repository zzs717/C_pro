#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "commandlist.h"
#include "polishstack.h"
#include "neillsdl2.h"

#define ERROR(PHRASE) {printf("Fatal Error %s\n\n",PHRASE); exit(2); }
#define SIZE 100
#define pai 3.141592653


struct drawingData {
	double x_old;
	double y_old;
	double x_new;
	double y_new;
	double angle;
	double arr[SIZE];
};
typedef struct drawingData data;

/*These functions for the parsing*/
void MAIN(commandlist* p, data* da, SDL_Simplewin w);
void INSTRCTLST(commandlist* p, data* da, SDL_Simplewin w);
void INSTRUCTION(commandlist* p, data* da, SDL_Simplewin w);
double FD(commandlist* p, data* da);
void FD_Draw(SDL_Simplewin w, data* da, double num);
double LT(commandlist* p, data* da);
void LT_Draw(data* da, double num);
double RT(commandlist* p, data* da);
void RT_Draw(data* da, double num);
int VARNUM(commandlist* p);
bool VAR(commandlist* p);
bool SET(commandlist* p, data* da);
double POLISH(commandlist* p, stack* s, data* da);
bool OP(commandlist* p);
bool DO(commandlist* p, data* da, SDL_Simplewin w);

int whattype(char* str);
data initdata();
double calculate(commandlist* p, stack* s);

void FUNCTION(commandlist* p, data* da, SDL_Simplewin w);
int countfucbrk(commandlist* p);
int countbrack(commandlist* p);

/*These functions to assert the parsing fuctions*/
void Assertextension();

void ASSERT_whattype();
void ASSERT_VAR(commandlist* p);
void ASSERT_VARNUM(commandlist* p);
void ASSERT_FD(commandlist* p, data* da);
void ASSERT_LT(commandlist* p, data* da);
void ASSERT_RT(commandlist* p, data* da);
void ASSERT_OP(commandlist* p);
void ASSERT_DO(commandlist* p);
void ASSERT_SET(commandlist* p, data* da);
void ASSERT_POLISH(commandlist* p, stack* s, data* da);
void ASSERT_calculate(commandlist* p, stack* ss);
