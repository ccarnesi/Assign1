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
	/*check if its even a pointer*/
	metadata * meta = (metadata*) ptr;
	if(sizeof(ptr)!=sizeof(void*)){
		printf("Error: attempting to pass something that isnt a pointer\n");
		return;
			
	}	

	/* make sure that its something that is inside of our array and not some random pointer THIS IS PROBABLY WRONG*/
	if(meta>myblock||meta<myblock){
		printf("Error: attempting to access data that is not inside our malloc array \n");
		return;

	}
	/*check if this pointer was already freed by checking in use possibly have to fix this in order to account for tthe fact that the pointer leads to the data*/
	if(meta->isUsed==0){
		printf("Error: attempting to free an already unused block\n");
		return;
	}

}


