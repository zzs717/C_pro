
#include "parser.h"
#include "commandlist.h"

void MAIN(commandlist *p){
   /* Check if the "{" equals to "}" */
   if(p->num1 != p->num2){
       ERROR("Missing brackets");
   }
   /* Check if the first command is "{" */
   if (strcmp(p->wds[p->cw], "{")!=0) {
       ERROR("There is no bracket{ after main");
   }
   p->cw += 1;
   INSTRCTLST(p);
}

void INSTRCTLST(commandlist *p){
/* Check if instruction is "}" */
    if (strcmp(p->wds[p->cw], "}")==0) {
         /* Check if it's the last "}" in the program */
       if (p->num2 == 0) {
           return;
       }
    }
    INSTRUCTION(p);
    INSTRCTLST(p);
}

void INSTRUCTION(commandlist *p){
    if (strcmp(p->wds[p->cw], "FD")==0) {
        p->cw += 1;
        FD(p);
        return;
    }
    if (strcmp(p->wds[p->cw], "LT")==0) {
        p->cw += 1;
        LT(p);
        return;
    }
    if (strcmp(p->wds[p->cw], "RT")==0) {
        p->cw += 1;
        RT(p);
        return;
    }

    if (strcmp(p->wds[p->cw], "DO")==0) {
        p->cw += 1;
        DO(p);
        return;
    }

    if (strcmp(p->wds[p->cw], "SET")==0) {
        p->cw += 1;
        SET(p);
        return;
    }

    if (strcmp(p->wds[p->cw], "}")==0) {
        p->num2 = p->num2 - 1;
        if((p->num2)!=0){p->cw += 1;}
        return;
    }
}

int VARNUM(commandlist *p){
    if(whattype(p->wds[p->cw])==-1){
        ERROR("Expecting a number or a letter");
    }
    else{
        return whattype(p->wds[p->cw]);
    }
}

bool VAR(commandlist *p){
    if(whattype(p->wds[p->cw])==0){
        return true;
    }
    return false;
}

bool FD(commandlist *p){
    /* If a number */
    if (VARNUM(p)==1) {
        p->cw += 1;
        return true;
    }
    /* If a letter */
    if (VAR(p)) {
        p->cw += 1;
        return false;
    }
    else{
        ERROR("Expecting number or letter after FD");
    }
}

bool LT(commandlist *p){
    /* If a number */
    if (VARNUM(p)==1) {
        p->cw += 1;
        return true;
    }
    /* If a letter */
    if (VAR(p)) {
        p->cw += 1;
        return false;
    }
    else{
        ERROR("Expecting number or letter after LT");
    }
}

bool RT(commandlist *p){
    /* If a number */
    if (VARNUM(p)==1) {
        p->cw += 1;
        return true;
    }
    /* If a letter */
    if (VAR(p)) {
        p->cw += 1;
        return false ;
    }
    else{
        ERROR("Expecting number or letter after RT");
    }
}

void DO(commandlist *p){
    if(VAR(p)){
        p->cw +=  1;
        if (strcmp(p->wds[p->cw], "FROM")==0) {
            p->cw +=  1;
            if (VARNUM(p)==0||VARNUM(p)==1) {
                p->cw +=  1;
            }
            else{ERROR("Expecting a number or letter");}
            if (strcmp(p->wds[p->cw], "TO")==0) {
                p->cw +=  1;
                if (VARNUM(p)==0||VARNUM(p)==1) {
                    p->cw +=  1;
                }
                else{ERROR("Expecting a number or letter");}
                if (strcmp(p->wds[p->cw], "{")==0) {
                    p->cw +=  1;
                    return;
                }
                ERROR("Expecting a Bracket");
            }
            ERROR("Expecting TO");
        }
        ERROR("Expecting FROM");
    }
    ERROR("Expecting a letter after DO");
}

void SET(commandlist *p){
    if(VAR(p)){
        p->cw += 1;
        if (strcmp(p->wds[p->cw], ":=")==0) {
            p->cw += 1;
            POLISH(p);
            return;
        }
        ERROR("Expecting the :=");
    }
    ERROR("Expecting a letter after SET");
}

void POLISH(commandlist *p){
    if(strcmp(p->wds[p->cw], ";")==0){
        p->cw += 1;
        return;
    }
    OP(p);
    p->cw += 1;
    POLISH(p);
    return;
}

bool OP(commandlist *p){
    if (strcmp(p->wds[p->cw], "+")==0) {
        return true;
    }
    if (strcmp(p->wds[p->cw], "-")==0) {
        return true;
    }
    if (strcmp(p->wds[p->cw], "*")==0) {
        return true;
    }
    if (strcmp(p->wds[p->cw], "/")==0) {
        return true;
    }
    if((VARNUM(p)==1)||(VARNUM(p)==0)){
        return false;
    }
    ERROR("Expecting a right operator");
}

int whattype(char *str){
    double number;
    if (sscanf(str, "%lf", &number)==1) {
        return 1;
    }
    if (strlen(str)==1 && (isupper(str[0])!=0)){
        return 0;
    }
    return -1;
}
