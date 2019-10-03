#include "mymalloc.h"
#include <stdlib.h>
#include <stdio.h>

#define blockSize 4096

int main(int argv, char* argc[]){
        malloc(100);

        return 0;
}




void* mymalloc(size_t size){
        if(size<=0){
                return NULL;
        }else if(size + sizeof(metadata) > blockSize){
                return NULL;
        }
        metadata* meta = (metadata*)myblock;
        if(meta->c != '#'){
                //first time create sstruct managing block size - metadata size in use 0
        }else{
            //iterate till you find metadata that fits for your use
        }



}

void myfree(void* ptr){

}
