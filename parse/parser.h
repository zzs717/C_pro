#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "polishstack.h"
#include "commandlist.h"

#define ERROR(PHRASE) {printf("Fatal Error %s\n\n",PHRASE); exit(2); }


/*These functions for the parsing*/
void MAIN(commandlist *p);
void INSTRCTLST(commandlist *p);
void INSTRUCTION(commandlist *p);
bool FD(commandlist *p);
bool LT(commandlist *p);
bool RT(commandlist *p);
void DO(commandlist *p);
int VARNUM(commandlist *p);
bool VAR(commandlist *p);
void SET(commandlist *p);
void POLISH(commandlist *p);
bool OP(commandlist *p);

int whattype(char *str);


/*These functions to assert the parsing fuctions*/
void Assertparse();

void ASSERT_whattype();
void ASSERT_VAR(commandlist *p);
void ASSERT_VARNUM(commandlist *p);
void ASSERT_FD(commandlist *p);
void ASSERT_LT(commandlist *p);
void ASSERT_RT(commandlist *p);
void ASSERT_OP(commandlist *p);
