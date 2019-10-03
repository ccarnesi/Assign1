#ifndef HEADERFILE
    #define HEADERFILE
    #include <stdlib.h>
    #include <stdio.h>
    #define malloc( x ) mymalloc((x), __FILE__, __LINE__)
    #define free(x) myfree(x)

    void* mymalloc(size_t size, char* ptr, int line); 

    static char myblock[4096];
    
    typedef struct metadata{
            int isUsed;
            int isManaging;
            struct metadata* next;
            struct metadata* prev;
            char c;
    }metadata;

#endif
