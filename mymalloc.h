#ifndef HEADERFILE
    #define HEADERFILE
    #define malloc(x) mymalloc(x)
    #define free(x) myfree(x)

//    void* mymalloc(size_t size, __FILE__, __LINE__);

    static char myblock[4096];
    
    typedef struct metadata{
            int isUsed;
            int isManaging;
            struct metadata* next;
    }metadata;

#endif
