#include "extension.h"
#include "polishstack.h"
#include "neillsdl2.h"

void MAIN(commandlist* p, data* da, SDL_Simplewin w) {
    /* Check if the "{" equals to "}" */
    if (p->num1 != p->num2) {
        ERROR("Missing brackets");
    }
    /* Check if the first command is "{" */
    if (strcmp(p->wds[p->cw], "{") != 0) {
        ERROR("There is no bracket{ after main");
    }
    p->num2 = p->num2  - countfucbrk(p);
    p->cw += 1;
    INSTRCTLST(p, da, w);
}

void INSTRCTLST(commandlist* p, data* da, SDL_Simplewin w) {
    /* Check if instruction is "}" */
    if (strcmp(p->wds[p->cw], "}") == 0) {
        /* Check if it's the last "}" in the program */
        if (p->num2 == 0) {
            return;
        }
    }
    INSTRUCTION(p, da, w);
    INSTRCTLST(p, da, w);
}

void INSTRUCTION(commandlist* p, data* da, SDL_Simplewin w) {
    if (strcmp(p->wds[p->cw], "FD") == 0) {
        double numF;
        p->cw += 1;
        numF = FD(p, da);
        FD_Draw(w, da, numF);
        return;
    }
    if (strcmp(p->wds[p->cw], "LT") == 0) {
        double numL;
        p->cw += 1;
        numL = LT(p, da);
        LT_Draw(da, numL);
        return;
    }
    if (strcmp(p->wds[p->cw], "RT") == 0) {
        double numR;
        p->cw += 1;
        numR = RT(p, da);
        RT_Draw(da, numR);
        return;
    }

    if (strcmp(p->wds[p->cw], "DO") == 0) {
        p->cw += 1;
        DO(p, da, w);
        return;
    }

    if (strcmp(p->wds[p->cw], "SET") == 0) {
        p->cw += 1;
        SET(p, da);
        return;
    }

    if (strcmp(p->wds[p->cw], "}") == 0) {
        p->num2 = p->num2 - 1;
        if ((p->num2) != 0) { p->cw += 1; }
        return;
    }

    if (strcmp(p->wds[p->cw], "FUNCTION") == 0) {
        p->cw += 1;
        FUNCTION(p,da,w);
        return;
    }
}

int VARNUM(commandlist* p) {
    if (whattype(p->wds[p->cw]) == -1) {
        ERROR("Expecting aa number or a letter");
    }
    else {
        return whattype(p->wds[p->cw]);
    }
}

bool VAR(commandlist* p) {
    if (whattype(p->wds[p->cw]) == 0) {
        return true;
    }
    return false;
}

double FD(commandlist* p, data* da) {

    double value;
    value = 0;
    /* If it is a number */
    if (VARNUM(p) == 1) {
        value = atof(p->wds[p->cw]);
    }
    /* If it is a letter */
    else {
        if (VAR(p) == true) {
            char variable = *p->wds[p->cw];
            int add = variable - 65;
            value = da->arr[add];
        }
    }
    p->cw += 1;
    return value;
}

void FD_Draw(SDL_Simplewin w, data* da, double num) {

    Neill_SDL_SetDrawColour(&w, 255, 255, 255);
    da->x_old = da->x_new;
    da->y_old = da->y_new;
    da->x_new = da->x_new + num * cos(da->angle);
    da->y_new = da->y_new + num * sin(da->angle);
    SDL_RenderDrawLine(w.renderer, da->x_old, da->y_old, da->x_new, da->y_new);
    Neill_SDL_UpdateScreen(&w);
    SDL_Delay(20);
    return;
}

double LT(commandlist* p, data* da) {
    double value;
    /* If it is a number */
    if (VARNUM(p) == 1) {
        value = atof(p->wds[p->cw]);
    }
    /* If it is a letter */
    else {
        char variable;
        int add;
        variable = *p->wds[p->cw];
        add = variable - 65;
        value = da->arr[add];
    }
    p->cw += 1;
    return value;
}

void LT_Draw(data* da, double num) {
    da->angle = da->angle - num * pai / 180;
    return;
}

double RT(commandlist* p, data* da) {
    double value;
    /* If it is a number */
    if (VARNUM(p) == 1) {
        value = atof(p->wds[p->cw]);
    }
    /* If it is a letter */
    else {
        char variable;
        int add;
        variable = *p->wds[p->cw];
        add = variable - 65;
        value = da->arr[add];
    }
    p->cw += 1;
    return value;
}

void RT_Draw(data* da, double num) {
    da->angle = da->angle + num * pai / 180;
    return;
}

bool SET(commandlist* p, data* da) {
    /* Check if SET instruction is valid and calculate value from <POLISH> expressions */
    if (VAR(p) == true) {
        stack* s = stack_init();
        char variable;
        int add;
        double result;
        variable = *p->wds[p->cw];
        add = variable - 65;
        p->cw += 1;
        if (strcmp(p->wds[p->cw], ":=") == 0) {
            p->cw += 1;
            result = POLISH(p, s, da);
            da->arr[add] = result;
            stack_free(s);
            return true;
        }
        ERROR("Expecting := Symbol");
    }
    ERROR("Expecting a letter after SET");
}

double POLISH(commandlist* p, stack* s, data* da) {
    double result;
    result = 0;
    if (strcmp(p->wds[p->cw], ";") == 0) {
        assert(stack_pop(s, &result));
        p->cw += 1;
        return result;
    }
    if (OP(p)) {
        double cal;
        cal = calculate(p, s);
        stack_push(s, cal);
        p->cw += 1;
        return POLISH(p, s, da);
    }
    else {
        if (VARNUM(p) == 1) {
            stack_push(s, atof(p->wds[p->cw]));
            p->cw += 1;
            return POLISH(p, s, da);
        }
        else  if (VARNUM(p) == 0) {
            char variable;
            int add;
            variable = *p->wds[p->cw];
            add = variable - 65;
            stack_push(s, da->arr[add]);
            p->cw += 1;
            return POLISH(p, s, da);
        }
        else {
            return -1;
        }
    }
}

bool OP(commandlist* p) {
    if (strcmp(p->wds[p->cw], "+") == 0) {
        return true;
    }
    if (strcmp(p->wds[p->cw], "-") == 0) {
        return true;
    }
    if (strcmp(p->wds[p->cw], "*") == 0) {
        return true;
    }
    if (strcmp(p->wds[p->cw], "/") == 0) {
        return true;
    }
    if ((VARNUM(p) == 1) || (VARNUM(p) == 0)) {
        return false;
    }
    ERROR("Expecting a right operator");
}

bool DO(commandlist* p, data* da, SDL_Simplewin w) {
    if (VAR(p)) {
        double loopbegin, loopend;
        int backtrack, add1;
        char variable1;
        variable1 = *p->wds[p->cw];
        add1 = variable1 - 65;
        p->cw += 1;
        if (strcmp(p->wds[p->cw], "FROM") == 0) {
            p->cw += 1;
            if (VARNUM(p) == 1) {
                loopbegin = atof(p->wds[p->cw]);
                da->arr[add1] = atof(p->wds[p->cw]);
            }
            else if (VARNUM(p) == 0) {
                char variable2;
                int add2;
                variable2 = *p->wds[p->cw];
                add2 = variable2 - 65;
                loopbegin = da->arr[add2];
                da->arr[add1] = da->arr[add2];
            }
            else { ERROR("Expecting a number or letter"); }
            p->cw += 1;
            if (strcmp(p->wds[p->cw], "TO") == 0) {
                p->cw += 1;
                if (VARNUM(p) == 1) {
                    loopend = atof(p->wds[p->cw]);
                }
                else if (VARNUM(p) == 0) {
                    char variable3;
                    int add3;
                    variable3 = *p->wds[p->cw];
                    add3 = variable3 - 65;
                    loopend = da->arr[add3];
                }
                else { ERROR("Expecting a number or letter"); }
                p->cw += 1;
                if (strcmp(p->wds[p->cw], "{") == 0) {
                    p->cw += 1;
                    backtrack = p->cw;
                    while (da->arr[add1] <= loopend) {
                        INSTRCTLST(p, da, w);
                        if (strcmp(p->wds[p->cw], "}") == 0) {
                            da->arr[add1] = da->arr[add1] + 1;
                            if (da->arr[add1] <= loopend) {
                                p->cw = backtrack;
                            }
                        }
                    }
                    return true;
                }
                ERROR("Expecting a Bracket");
            }
            ERROR("Expecting TO");
        }
        ERROR("Expecting FROM");
    }
    ERROR("Expecting a letter after DO");
}

double calculate(commandlist* p, stack* s) {
    double d;
    double g1;
    double g2;
    assert(stack_pop(s, &g2));
    assert(stack_pop(s, &g1));
    if (strcmp(p->wds[p->cw], "+") == 0) {
        d = g1 + g2;
    }
    if (strcmp(p->wds[p->cw], "-") == 0) {
        d = g1 - g2;
    }
    if (strcmp(p->wds[p->cw], "*") == 0) {
        d = g1 * g2;
    }
    if (strcmp(p->wds[p->cw], "/") == 0) {
        d = g1 / g2;
    }
    return d;
}

data initdata() {
    data da;
    int i;
    da.x_new = 250;
    da.y_new = 250;
    da.angle = 0;
    for (i = 0; i < SIZE; i++) {
        da.arr[i] = 0;
    }
    return da;
}

int whattype(char* str) {
    double number;
    if (sscanf(str, "%lf", &number) == 1) {
        return 1;
    }
    if (strlen(str) == 1 && (isupper(str[0]) != 0)) {
        return 0;
    }
    return -1;
}

void FUNCTION(commandlist* p, data* da, SDL_Simplewin w) {
    int back,numbrk,fucbrk;
    char* fucname = p->wds[p->cw];
    (p->cw) += 1;
    back = p->cw;
    numbrk = p->num2;
    while (strcmp(fucname, p->wds[p->cw])!=0||
        strcmp("{", p->wds[(p->cw)+1]) != 0) {
        (p->cw) += 1;
    }
    (p->cw) += 1;
    fucbrk=countbrack(p);
    if (strcmp(p->wds[p->cw], "{") == 0) {
        (p->cw) += 1;
        p->num2 = fucbrk;
        INSTRCTLST(p, da, w);
    }
    p->cw= back;
    p->num2 = numbrk;
    return;
}
/*Count the number of } after the MAIN */
int countfucbrk(commandlist* p) {
    int num;
    num = 0;
    while ((!(strcmp(p->wds[p->cw], "FUNCTION") == 0 &&
        strcmp(p->wds[p->cw + 2], "{") == 0))&& 
        strcmp(p->wds[p->cw], "\0") != 0){
        p->cw += 1;
    }
    while (strcmp(p->wds[p->cw], "\0") != 0) {
        if (strcmp(p->wds[p->cw], "}") == 0) {
            num++;
        }
        p->cw += 1;
    }
    p->cw = 0;
    return num;
}
/*Count the number of a function */
int countbrack(commandlist* p) {
    int num,back; 
    num = 0;
    back = p->cw;
    while (!((strcmp(p->wds[p->cw], "\0") == 0) ||
        (strcmp(p->wds[p->cw], "FUNCTION") == 0 && strcmp(p->wds[p->cw + 2], "{") == 0))){
        if (strcmp(p->wds[p->cw], "}") == 0) {
            num++;
        }
        p->cw += 1;
    }
    p->cw = back;
    return num;

}