#include"commandlist.h"

commandlist* commandlist_init() {
    commandlist* a = (commandlist*)ncalloc(1, sizeof(commandlist));
    a->wds = (char**)n2dcalloc(NUMTOKENS, MAXTOKENSIZE, 1);
    a->size = 0;
    a->capacity = NUMTOKENS;
    a->cw=0;
    a->num1=0;
    a->num2=0;
    return a;
}

void commandlist_insert(commandlist** a, char* strs) {
    if ((*a)->size>=0.8*(*a)->capacity){
       int oh= (*a)->capacity;
       int nh= resize*((*a)->capacity);
       int nw= MAXTOKENSIZE;
       int ow= MAXTOKENSIZE;
       (*a)->wds=(char**)n2drecalloc((*a)->wds, oh, nh, nw, ow, 1);
       (*a)->capacity=nh;
    }
    strcpy((*a)->wds[(*a)->size], strs);
    (*a)->size +=1 ;
    if(strcmp(strs,"{")==0){
        (*a)->num1+=1;
    }
    if(strcmp(strs,"}")==0){
        (*a)->num2+=1;
    }
}

void commandlist_free(commandlist* a) {
    n2dfree(a->wds,a->capacity);
    free(a);
}

void readfile(char* fname, char* mode, commandlist*a){
    int i=0;
    FILE* fp;
    char *strs = ncalloc(MAXTOKENSIZE, 1);
    char *strss = ncalloc(MAXTOKENSIZE, 1);
    fp = nfopen(fname, mode);
    while(fscanf(fp, "%s", strs)==1){
        commandlist_insert(&a, strs);
        i++;
        assert(a->size==i);
        strcpy(strs,strss);
    };
    fclose(fp);
}
