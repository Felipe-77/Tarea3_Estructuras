#ifndef ArrayList_h
#define ArrayList_h

typedef struct ArrayList ArrayList;
typedef struct Stack Stack;

ArrayList *createList(void);

void append(ArrayList * l, void * data);
void push(ArrayList * l, void * data, int i);
void* pop(ArrayList * l, int i);
void* get(ArrayList * l, int i);
int get_size(ArrayList * l);
void clean(ArrayList * list);

Stack * createStack(void);
void* topStack(Stack * s);
void* popStack(Stack * s);
void pushStack(Stack * s, void * data);
int get_sizeStack(Stack * s);


#endif /* List_h */