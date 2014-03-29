#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "hashmap.h"
// HashMap using linear prombing

// Inner Parameters
#define STR_MAX_LEN 256
#define HASH_CAP 64

#define HASH_SLOT_EMPTY 0x00
#define HASH_SLOT_FULL  0x01
#define HASH_SLOT_DUMMY 0x02

typedef struct hm_t {
    unsigned char slot[HASH_CAP];
    char keyArray[HASH_CAP][STR_MAX_LEN];
    int valArray[HASH_CAP];
    size_t fill; // FULL + DUMMY
    size_t used; // FULL
} HashMap;  

// Inner Method
unsigned int hashFunc(char* s);
int hmFindKey(HashMap *pThis, char* key);

unsigned int hashFunc(char* s){
    unsigned int hashVal = 5381;
    int len = strlen(s), i;
    for(i=0; i<len; i++){
        hashVal = (hashVal << 5) + hashVal + (unsigned int)s[i];
    }
    return hashVal % HASH_CAP;
}

int hmFindKey(HashMap *pThis, char* key){
    // if key exist, return the index of key.
    // if key doesn't exist, return the index that key can be inserted.
    int hashVal = hashFunc(key);
    int index = hashVal;

    int insertedIndex = -1;
    // DUMMY node, the key in th node which has been deleted.
    // Because of prombing method in hash, We can't just make slot empty.
    while(1){
        if(pThis->slot[index] == HASH_SLOT_EMPTY){ // key doesn't exist
            if(insertedIndex == -1)
                return index;
            return insertedIndex;
        }
        else if(pThis->slot[index] == HASH_SLOT_DUMMY){
            if(insertedIndex == -1)
                insertedIndex = index;
            index = (index+1) % HASH_CAP;
            continue;
        }
        else if(pThis->slot[index] == HASH_SLOT_FULL){
            if(strncmp(key, pThis->keyArray[index], STR_MAX_LEN) == 0)
                return index;
            index = (index+1) % HASH_CAP;
            continue;
        }
    }
}

// Constructor and Destructor
HashMap *hmAlloc(){
    return malloc(sizeof(HashMap));
}
int hmInit(HashMap *pThis){
    int i;
    for(i=0; i<HASH_CAP; i++){
        pThis->slot[i] = HASH_SLOT_EMPTY;
    }
    pThis->used = 0;    
    pThis->fill = 0;    
}
int hmFree(HashMap *pThis){
    if(pThis != NULL)
        free(pThis);
}

// Methods
int hmSize(HashMap *pThis){ // how many element in HashMap
    return pThis->fill;
}

int hmInsert(HashMap *pThis, char *key, int val){
    if(pThis->fill+1 >= HASH_CAP)
        return __HM__FULL__;

    int index = hmFindKey(pThis, key);
    if(pThis->slot[index] == HASH_SLOT_FULL)
        return __HM__KEY_EXIST__;
    else if(pThis->slot[index] == HASH_SLOT_DUMMY)
        pThis->used++;
    else if(pThis->slot[index] == HASH_SLOT_EMPTY){
        pThis->used++;
        pThis->fill++;
    }

    pThis->slot[index] = HASH_SLOT_FULL;
    strncpy(pThis->keyArray[index], key, STR_MAX_LEN);
    pThis->valArray[index] = val;
    return __HM__NORMAL__;
}

int hmKeyExist(HashMap *pThis, char *key){
    int index = hmFindKey(pThis, key);
    if(pThis->slot[index] == HASH_SLOT_EMPTY || pThis->slot[index] == HASH_SLOT_DUMMY)
        return 0;
    return 1;
}

int hmGet(HashMap *pThis, char *key, int *pRetVal){
    int index = hmFindKey(pThis, key);
    if(pThis->slot[index] == HASH_SLOT_FULL){
        *pRetVal = pThis->valArray[index];
        return __HM__NORMAL__;
    }
    return __HM__KEY_NOT_EXIST__;
}

int hmSet(HashMap *pThis, char *key, int newVal){
    if(pThis->fill+1 >= HASH_CAP)
        return __HM__FULL__;

    int index = hmFindKey(pThis, key);
    if(pThis->slot[index] == HASH_SLOT_DUMMY)
        pThis->used++;
    else if(pThis->slot[index] == HASH_SLOT_EMPTY){
        pThis->used++;
        pThis->fill++;
    }

    pThis->slot[index] = HASH_SLOT_FULL;
    strncpy(pThis->keyArray[index], key, STR_MAX_LEN);
    pThis->valArray[index] = newVal;
    return __HM__NORMAL__;
}

int hmDelete(HashMap *pThis, char *key){
    int index = hmFindKey(pThis, key);
    if(pThis->slot[index] == HASH_SLOT_EMPTY || pThis->slot[index] == HASH_SLOT_DUMMY)
        return __HM__KEY_NOT_EXIST__;

    pThis->used--;
    pThis->slot[index] = HASH_SLOT_DUMMY;
    return __HM__NORMAL__;
}
