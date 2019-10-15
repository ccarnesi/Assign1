#include "mymalloc.h"

#define blockSize 4096
metadata* breakOff(metadata* prev, int size);



void* mymalloc(size_t size, char* file, int line){
        if(size<=0){
                printf("error: asked for memory of size <=0  in file: %s on line: %d\n", file, line);
                return NULL;
        }else if(size + sizeof(metadata) > blockSize){
                printf("error: asked for memory larger than block size in file: %s on line: %d\n", file, line);
                return NULL;
        }
        metadata* meta = (metadata*)myblock;
        if(meta->c != '#'){
                //first time create sstruct managing block size - metadata size in use 0
                meta->isUsed = 1;
                meta->isManaging = size;
                meta->prev = NULL;
                char* ptr = myblock + sizeof(metadata) + size;
                metadata* second = (metadata*)ptr; //this should be the second meta that manages the rest of data
                meta->next = second;
                second->isUsed = 0;
                second->isManaging = blockSize - 2*sizeof(metadata) - size;
                second->prev = meta;
                second-> next = NULL;
		        meta->c = '#';
		        second->c = '#';
                return myblock + sizeof(metadata);

        }else{
            //iterate till you find metadata that fits for your use
                while(meta->next != NULL){
                        //traverse until you find an unused chunk or the end of meta chain
                        if(meta->isUsed == 0 && meta->isManaging >= size + sizeof(metadata)){
                            //found a spot
                            // break off whats left after the size
                            metadata* newStruct = breakOff(meta, size);
                            meta->isManaging = size;
                            meta->isUsed = 1;
                            meta->next = newStruct;
                            char* ptr = (char*) meta;
                            return ptr + sizeof(metadata); 
                        }else if(meta->isUsed ==0 && meta->isManaging>=size){
                            //found a spot but no room for anymore meta after
                                meta->isUsed =1;
                                char* ptr = (char*) meta;
                                return ptr + sizeof(metadata);

                        }
                        meta = meta->next;
                }
                //At last block
                if(meta->isUsed == 0 && meta->isManaging >= size + sizeof(metadata)){
                        //found a spot
                        // break off whats left after the size
                        printf("HEREi\n");
                        metadata* newStruct = breakOff(meta, size);
                        meta->isManaging = size;
                        meta->isUsed = 1;
                        meta->next = newStruct;
                        char* ptr = (char*)meta;
                        return ptr + sizeof(metadata); 
                    }else if(meta->isUsed ==0 && meta->isManaging>=size){
                            //found a spot but no room for anymore meta after
                            meta->isUsed =1;
                            char* ptr = (char*) meta;
                            return ptr + sizeof(metadata);

                    }else{
                            //couldn't find room
                            return NULL;
                    }
        }
}

metadata* breakOff(metadata* prev, int size){
    char* ptr = (char*)prev + sizeof(metadata)+ size;
    metadata* newStruct = (metadata*)ptr;
    int newSize = prev->isManaging - size;
    newStruct->prev = prev;
    newStruct->next = prev->next;
    newStruct->isManaging = newSize; 
    newStruct->isUsed = 0;
    newStruct->c = '#';
    return newStruct;

}

void myfree(void* ptr, char* file, int line){
    	char* charPtr = (char*) ptr;
	/* make sure that its something that is inside of our array and not some random location, we do this by comparing the memory address of our pointer vs the memory of our array*/
	if(charPtr<myblock||charPtr>(myblock+blockSize)){
		printf("Error: attempting to access data that is not inside our malloc array in file: %s, on line %d\n",file,line);
		return;
	}	
	char* curr =(char*) charPtr-sizeof(metadata);
	metadata * meta =(metadata*) curr;
	/*check to see if the pointer actually points to a *metadata struct*/
	if(meta->c != '#'){
		printf("Error:freeing before the array is even made or not a valid pointer to the array in file: %s, on line %d\n",file, line);
		return;
	}
	
	/*check if this pointer was already freed by checking in use possibly have to fix this in order to account for tthe fact that the pointer leads to the data*/
	if(meta->isUsed==0){
		printf("Error: attempting to free an already unused block\n in file: %s, on line %d\n",file, line);
		return;
	}
	/*I dont think there are any more cases left to check for so we gotta now free the thing and check for stuff*/
	meta->isUsed = 0;
	/*if we have someone to the right of us that is also free we must merge with them and become one big happy block, but first we gotta do some edge case checking*/
	if(meta->next == NULL){
			
	}else{
		/*since there is a right block lets check to see if we can merge it in the case its not in use*/
		if(meta->next->isUsed == 0){
			/*lets merge so kill the node and its pointers*/
			metadata * proxima  = meta->next;
			meta->next = proxima->next;
			proxima->prev = NULL;
			meta->isManaging += proxima->isManaging + sizeof(metadata);
		}
	}
	/*just make sure we arent at first block*/ 
	if(meta->prev != NULL){
		if(meta->prev->isUsed==0){
			/*merge the left as well*/
			metadata* antes = meta->prev;
			/*we are able to link our right cuz we arent at the end*/
			antes->next = meta->next;
			antes->isManaging += meta->isManaging +sizeof(metadata);
			printf("mem to left was also free so we merged\n");
		}
		/*we don really care about the data so we can just leave it as is since we already said its no longer in use*/

	}
	return;


}


