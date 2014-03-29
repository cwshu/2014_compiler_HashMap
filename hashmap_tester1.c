#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "hashmap.h"

int intcmp(const void* a, const void* b){
    return *(const int*)a - *(const int*)b;
}
int strcmp_(const void* a, const void* b){
    return strcmp((const char*)a, (const char*)b);
}

void test1(){
    HashMap* pMap1 = hmAlloc();
    hmInit(pMap1);
    /* 2 4 6 12 8 16 2 4
       error: 2, 4, 4
     */
    char test1[5][10] = {"hello", "compiler", "hello", "AC", "scanning"};
    int i;
    for(i=0; i<5; i++){
        int in = i*i;
        int state = hmInsert(pMap1, test1[i], in);
        if(state != __HM__NORMAL__){
            printf("HM_error: %d\n", state); 
        }
        else{
            int map_content, map_insert;
            hmGet(pMap1, test1[i], &map_content);
            printf("Get: (%s, %d)\n", test1[i], map_content); 

            if(i > 0){
                map_insert = (i-1)*(i-1)*(i-1);
                hmSet(pMap1, test1[i-1], map_insert);
                hmGet(pMap1, test1[i-1], &map_content);
                printf("Update: (%s, %d)\n", test1[i-1], map_content);
            }
        }
    }
    
    int none, state;
    hmDelete(pMap1, test1[1]);
    state = hmGet(pMap1, test1[1], &none);
    if(state != __HM__NORMAL__){
        printf("HM_error: %d\n", state); 
    }
    hmDelete(pMap1, test1[2]);
    state = hmGet(pMap1, test1[2], &none);
    if(state != __HM__NORMAL__){
        printf("HM_error: %d\n", state); 
    }

    hmFree(pMap1);
}


int main(){
    test1();
}
