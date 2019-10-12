#include "mymalloc.h"
#include <sys/time.h>


void findAvg(char* testName, long array[]);
void testA();
void testB();
void testC();
void testD();

int main(int argv, char* argc[]){
    testA();
    testB();
    testC();
    testD();
}



void testA(){
    long array[100];
    struct timeval start, end;
    int j;
    for(j=0;j<100;j++){
        gettimeofday(&start, NULL);
        int i;
        for(i=0;i<150;i++){
                char * ptr = malloc(1);
                free(ptr);
        }
        gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        array[j] = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    }
    findAvg("Test A", array);

}

void testB(){
    int i;
    long timeArray[100];
    struct timeval start, end;
    int l;
    int k;
    for(l=0;l<100;l++){
        gettimeofday(&start, NULL);
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

        gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        timeArray[l] = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    }
    findAvg("Test B", timeArray);

}
void testC(){
        long timeArray[100];
        struct timeval start, end;
        int j;
        for(j=0;j<100;j++){
            gettimeofday(&start, NULL);
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
            gettimeofday(&end, NULL);
            long seconds = (end.tv_sec - start.tv_sec);
            timeArray[j] = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    }
    findAvg("Test C", timeArray);
}
void testD(){
        long timeArray[100];
        struct timeval start, end;
        int j;
        for(j=0;j<100;j++){

            gettimeofday(&start, NULL);
            char* array[50];
            int overhang = 0;
            int mallocs = 0;
            int frees = 0;
            while(mallocs != 50){
                    int choice = rand() % 1;
                            if(choice == 0){
                                //malloc
                                int size = (rand() % 64) + 1;
                                array[mallocs] = malloc(size);
                                mallocs++;
                                overhang++;
                            }else{
                                //free
                                if(overhang==0){
                                    //malloc
                                    int size = (rand() % 64) + 1;
                                    array[mallocs] = malloc(size);
                                    mallocs++;
                                    overhang++;
                                }else{
                                    free(array[frees]);
                                    frees++;
                                    overhang--;
                                }
                            }
            }
            while(overhang!=0){
                //free the rest
                free(array[frees]);
                frees++;
                overhang--;
            }
            gettimeofday(&end, NULL);
            long seconds = (end.tv_sec - start.tv_sec);
            timeArray[j] = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    }
    findAvg("Test D", timeArray);
}
void findAvg(char* testName, long array[]){
        int i;
        long sum = 0;
        for(i=0;i<100;i++){
            sum += array[i];
        }
        printf("The average time for %s is %.6f seconds\n", testName, (float)sum/100);
}
