#include "mymalloc.h"

void testA(){
    //malloc and free 150 times
    int i;
    for(i=0;i<150;i++){
            char * ptr = malloc(1);
            free(ptr);
    }
}

void testB(){
    int i;
    
    char* array[50];
    int j;
    for(j=0;j<3;j++){
        for(i=0;i<50;i++){
            array[i] = malloc(1);
        }   
        int k;
        for(k=0;k<50;k++){
            free(array[k]);
        }
    }
}

void testC(){
        int overhang = 0;
        char* array[50];
        int mallocPtr = 0;
        int freePtr = 0;
        while(mallocPtr != 50){
                int num = rand() % 2;
                if(num ==0){
                        //malloc
                        array[mallocPtr] = malloc(1);
                        mallocPtr++;
                        overhang++;
                }else{
                        //free
                        if(overhang == 0){
                                //malloc
                                array[mallocPtr] = malloc(1);
                                mallocPtr++;
                                overhang++;
                        }else{
                            free(array[freePtr]); 
                            freePtr++;
                            overhang--;
                        }
                }
        }
        while(overhang != 0){
                free(array[freePtr]); 
                freePtr++;
                overhang--;
        }
}
