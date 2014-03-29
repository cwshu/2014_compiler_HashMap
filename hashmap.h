#include <stddef.h>
#ifndef __HM__header__
#define __HM__header__
// Outside Message 
#define __HM__NORMAL__        0x00000000
#define __HM__OUT_OF_MEM__    0x00000001
#define __HM__KEY_EXIST__     0x00000002
#define __HM__KEY_NOT_EXIST__ 0x00000004
#define __HM__FULL__          0x00000008

/* Hash Map spec */
struct hm_t;
typedef struct hm_t HashMap;

HashMap *hmAlloc();
int hmInit(HashMap *pThis);
int hmFree(HashMap *pThis);

int hmSize(HashMap *pThis); // how many element in HashMap
int hmInsert(HashMap *pThis, char *key, int val);
int hmKeyExist(HashMap *pThis, char *key);
int hmGet(HashMap *pThis, char *key, int *pRetVal);
int hmSet(HashMap *pThis, char *key, int newVal);
int hmDelete(HashMap *pThis, char *key);
/* Hash Map spec end */

void hmDebug(HashMap* pThis);

#endif
