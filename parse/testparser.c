#include "general.h"
#include "commandlist.h"
#include "polishstack.h"
#include "parser.h"

int main(int argc,char *argv[]) {
   
    commandlist * cmds = commandlist_init();
    if(argc==1){
         printf("please input filename");
    }
    Assertparse();
    readfile(argv[1], "rt", cmds);
    MAIN(cmds);
    commandlist_free(cmds);
    printf("Parsed OK\n");
    return 0;
}

void Assertparse(){
    commandlist * p = commandlist_init();
    readfile("Assertparse.txt", "rt", p);
    ASSERT_whattype();
    ASSERT_VAR(p);
    ASSERT_VARNUM(p);
    ASSERT_FD(p);
    ASSERT_LT(p);
    ASSERT_RT(p);
    ASSERT_OP(p);
    commandlist_free(p);
    return;
}

void ASSERT_whattype(){
    char *str1="100";
    char *str2="A";
    char *str3="A2X";
    assert(whattype(str1)==1);
    assert(whattype(str2)==0);
    assert(whattype(str3)==-1);
    str1="50";
    str2="S";
    str3="BH";
    assert(whattype(str1)==1);
    assert(whattype(str2)==0);
    assert(whattype(str3)==-1);
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
    assert(VARNUM(p)==1);
    p->cw += 1;
    assert(VARNUM(p)==0);
    p->cw += 1;
    return;
}

void ASSERT_FD(commandlist *p){
    if (strcmp(p->wds[p->cw], "FD")==0) {
        p->cw += 1;
        assert(FD(p));
        p->cw += 1;
        assert(FD(p));
        p->cw += 1;
        assert(FD(p));
        p->cw += 1;
        assert(!FD(p));
        p->cw += 1;
        assert(!FD(p));
        p->cw += 1;
        assert(!FD(p));
    }
    return;
}

void ASSERT_LT(commandlist *p){
    if (strcmp(p->wds[p->cw], "LT")==0) {
        p->cw += 1;
        assert(LT(p));
        p->cw += 1;
        assert(LT(p));
        p->cw += 1;
        assert(LT(p));
        p->cw += 1;
        assert(!LT(p));
        p->cw += 1;
        assert(!LT(p));
        p->cw += 1;
        assert(!LT(p));
    }
    return;
}

void ASSERT_RT(commandlist *p){
    if (strcmp(p->wds[p->cw], "RT")==0) {
        p->cw += 1;
        assert(RT(p));
        p->cw += 1;
        assert(RT(p));
        p->cw += 1;
        assert(RT(p));
        p->cw += 1;
        assert(!RT(p));
        p->cw += 1;
        assert(!RT(p));
        p->cw += 1;
        assert(!RT(p));
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
