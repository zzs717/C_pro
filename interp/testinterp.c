#include "general.h"
#include "commandlist.h"
#include "polishstack.h"
#include "interp.h"
#include "neillsdl2.h"

int main(int argc, char** argv){
    commandlist* cmds = commandlist_init();
    data da = initdata();
    SDL_Simplewin w;
    if (argc==1) {
        printf("please input right filename");
    }
    Assertinterp();
    readfile(argv[1], "rt", cmds);
    Neill_SDL_Init(&w);
    MAIN(cmds, &da, w);
    SDL_Quit();
    commandlist_free(cmds);
    return 0;
}

/*Testing by Assertinterp.txt*/
void Assertinterp(){
    commandlist * p = commandlist_init();
    stack* ss=stack_init();
    data daa=initdata();
    readfile("Assertinterp.txt", "rt", p);
    ASSERT_whattype();
    ASSERT_VAR(p);
    ASSERT_VARNUM(p);
    ASSERT_calculate(p,ss);
    ASSERT_POLISH(p, ss, &daa);
    ASSERT_SET(p, &daa);
    ASSERT_FD(p, &daa);
    ASSERT_LT(p, &daa);
    ASSERT_RT(p, &daa);
    ASSERT_OP(p);
    stack_free(ss);
    commandlist_free(p);
    return;
}

void ASSERT_whattype(){
    char *str1="112";
    char *str2="B";
    assert(whattype(str1)==1.0);
    assert(whattype(str2)==0.0);
    str1="90";
    str2="J";
    assert(whattype(str1)==1.0);
    assert(whattype(str2)==0.0);
    return;
}

void ASSERT_VAR(commandlist *p){
    assert(VAR(p));
    p->cw += 1;
    assert(VAR(p));
    p->cw += 1;
    return;
}

void ASSERT_VARNUM(commandlist *p){
    assert(VARNUM(p)==1.0);
    p->cw += 1;
    assert(VARNUM(p)==0.0);
    p->cw += 1;
    return;
}

void ASSERT_calculate(commandlist *p,stack *ss){
    double num1=16;
    double num2=4;
    stack_push(ss, num1);
    stack_push(ss, num2);
    assert(calculate(p, ss)==20.0);
    p->cw += 1;
    stack_push(ss, num1);
    stack_push(ss, num2);
    assert(calculate(p, ss)==12.0);
    p->cw += 1;
    stack_push(ss, num1);
    stack_push(ss, num2);
    assert(calculate(p, ss)==64.0);
    p->cw += 1;
    stack_push(ss, num1);
    stack_push(ss, num2);
    assert(calculate(p, ss)==4.0);
    p->cw += 1;
    return;
}

void ASSERT_POLISH(commandlist *p,stack *s, data *da){
    assert(POLISH(p,s,da)==5.0);
    assert(POLISH(p,s,da)==40.0);
    assert(POLISH(p,s,da)==0.0);
    return;
}

void ASSERT_SET(commandlist *p, data *da){
    p -> cw += 1;
    assert(SET(p,da));
    p -> cw += 1;
    assert(SET(p,da));
    p -> cw += 1;
    assert(SET(p,da));
    return;
}

void ASSERT_FD(commandlist *p,data *da){
    if (strcmp(p->wds[p->cw], "FD")==0.0) {
        p->cw += 1;
        assert(FD(p,da)==30.0);
        p->cw += 1;
        assert(FD(p,da)==15.0);
        p->cw += 1;
        assert(FD(p,da)==20.0);
        p->cw += 1;
        assert(FD(p,da)==24.0);
        p->cw += 1;
        assert(FD(p,da)==30.0);
        p->cw += 1;
        assert(FD(p,da)==18.0);
    }
    return;
}

void ASSERT_LT(commandlist *p,data *da){
    if (strcmp(p->wds[p->cw], "LT")==0.0) {
        p->cw += 1;
        assert(LT(p,da)==33.0);
        p->cw += 1;
        assert(LT(p,da)==17.0);
        p->cw += 1;
        assert(LT(p,da)==80.0);
        p->cw += 1;
        assert(LT(p,da)==24.0);
        p->cw += 1;
        assert(LT(p,da)==30.0);
        p->cw += 1;
        assert(LT(p,da)==18.0);
    }
    return;
}

void ASSERT_RT(commandlist *p,data *da){
    if (strcmp(p->wds[p->cw], "RT")==0) {
        p->cw += 1;
        assert(RT(p,da)==31.0);
        p->cw += 1;
        assert(RT(p,da)==54.0);
        p->cw += 1;
        assert(RT(p,da)==12.0);
        p->cw += 1;
        assert(RT(p,da)==24.0);
        p->cw += 1;
        assert(RT(p,da)==30.0);
        p->cw += 1;
        assert(RT(p,da)==18.0);
    }
    return;
}

void ASSERT_OP(commandlist *p){
    assert(OP(p));
    p->cw += 1;
    assert(OP(p));
    p->cw += 1;
    assert(OP(p));
    p->cw += 1;
    assert(OP(p));
    p->cw += 1;
    assert(!OP(p));
    p->cw += 1;
    assert(!OP(p));
    return;
}
