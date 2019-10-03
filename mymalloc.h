#ifndef HEADERFILE
    #define HEADERFILE
    #define malloc(x) mymalloc(x)
    #define free(x) myfree(x)

    
    static char myblock[4096];
    
    typedef struct metadata{
            int isUsed;
            int isManaging;
            struct metadata* next;
            struct metadata* prev;
            char c;
    }metadata;

#endif
