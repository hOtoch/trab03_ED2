#ifndef TST_H_
#define TST_H_
#include "string.h"

typedef struct tst TST;

TST* rec_insert(TST* t, String* key, void* val, int d);

TST* TST_insert(TST* t, String* key, void* val);

TST* getRight(TST* node);

TST* getLeft(TST* node);

void setValues(TST* node, void* val);

TST* getMid(TST* node);

TST* searchNCalculatePR(TST* pages);

void* getFirstElement(TST* node);

int getCountValues(TST* node);

void* getValues(TST* node);

TST* create_node();

int searchNGetCountValues(TST* t, String* key);

TST* rec_search(TST* t, String* key, int d);

void* TST_search(TST* t, String* key);


void TST_Destroi(TST* t);

#endif
