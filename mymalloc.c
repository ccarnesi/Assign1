#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define blockSize 4096

int main(int argv, char* argc[]){



        return 0;
}




void* mymalloc(size_t size,char* file_,int line){
        if(size<=0){
                return NULL;
        }else if(size + sizeof(metadata) > blockSize){

        }
}

void myfree(void* ptr, char* file, int line){

}
