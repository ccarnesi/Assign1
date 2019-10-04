#include "mymalloc.h"

#define blockSize 4096

int main(int argv, char* argc[]){
        malloc(100);

        return 0;
}




void* mymalloc(size_t size, char* file, int line){
        if(size<=0){
                return NULL;
        }else if(size + sizeof(metadata) > blockSize){
                return NULL;
        }
        metadata* meta = (metadata*)myblock;
        if(meta->c != '#'){
                //first time create sstruct managing block size - metadata size in use 0
                meta->isUsed = 1;
                meta->isManaging = size;
                meta->prev = NULL;
                metadata* second = (metadata*)myblock + sizeof(metadata*) + size; //this should be the second meta that manages the rest of data
                meta->next = second;
                second->isUsed = 0;
                second->isManaging = blockSize - 2*sizeof(metadata*) - size;
                second->prev = meta;
                second-> next = NULL;
                return myblock + sizeof(metadata);

        }else{
            //iterate till you find metadata that fits for your use
                while(meta->next != NULL){
                        //traverse until you find an unused chunk or the end of meta chain
                        if(meta->isUsed == 0 && meta->isManaging >= size + sizeof(meta)){
                            //found a spot
                        }
                        meta = meta->next;
                        
                }
                //At last meta. check size and if not return null
        }



}

void myfree(void* ptr){

}


