#include "mymalloc.h"
#include <sys/time.h>



void findAvg(char* testName, long array[]);
void testA();
void testB();
void testC();
void testD();
void testE();
void testF();

int main(int argv, char* argc[]){
    srand(123);
  //  testA();
   // testB();
    //testC();
   // testD();
    testE();
    //testF();
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
        int j;

        for(j=0;j<3;j++){
            char* array[50];
            for(i=0;i<50;i++){
                array[i] = malloc(1);
            }   
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
            //printf("J:%d\n", j);
            while(mallocPtr < 50){
                    int num = rand() % 2;
                    if(num ==0){
                            //malloc
                            //printf("mallocPtr: %d\n", mallocPtr);
                            array[mallocPtr] = malloc(1);
                            ++mallocPtr;
                            ++overhang;
                    }else{
                            //free
                            if(overhang == 0){
                                    //malloc
                                    array[mallocPtr] = malloc(1);
                                    ++mallocPtr;
                                    ++overhang;
                            }else{
                                free(array[freePtr]); 
                                ++freePtr;
                                --overhang;
                            }
                    }
                    //printf("mallocs:%d\n", mallocPtr);
                    //printf("overhang%d\n", overhang);

            }
            //printf("OVER:%d\n", overhang);
            while(overhang > 0){
                    free(array[freePtr]); 
                    ++freePtr;
                    --overhang;
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
/*this plan tests how well our malloc calls work when we are at capacity then freeing that capacity*/
void testE(){
	long timeArray[100];
	struct timeval start, end;
	int j;
	int mallocs = 0;
	for(j=0;j<100;j++){
		gettimeofday(&start,NULL);
		char* array[32];
		/*malloc till capacity*/
		for(;mallocs<32;mallocs++){
		array[mallocs] = (char*) malloc(96);		
		}
		printf("fully filled array \n");
		/*now mess around with the last data block over and over again having enough space for a meta datablock at end and then without*/
		int i =0;
		for(i =0;i<50;i++){
		free(array[31]);
		array[31] = (char*) malloc(63);
		free(array[31]);
		array[31] = (char*) malloc(64);
		free(array[31]);
		}
		for(i =0;i<31;i++){
			free(array[i]);
		}
		gettimeofday(&end,NULL);
		long seconds = (end.tv_sec-start.tv_sec);
		timeArray[j] = ((seconds*1000000)+end.tv_usec)-(start.tv_usec);
	}
	
	findAvg("Test E", timeArray);
}
/*this plan tests how well free works against valid and non valid pointers*/
void testF(){
	long timeArray[100];
	struct timeval start, end;
	int nice = 69;
	int *lol = &nice;
	char *meep = "meep";
	int i=0;
	int j =0;
	int k =0;
	int mallocs = 0;
	for(i =0;i<100;i++){
		char* array[32];	
		int mallocs =0;
		/*at capacity test*/
		for(;mallocs<32;mallocs++){
			array[mallocs] = (char*) malloc(96);

		}
		free((void*)lol);
		free((void*)meep);
		for(k=0;k<10;k++){
			free(array[k]+k);
			free(&lol+k);
		}
		/*making the array empty minus the structs that were there*/
		for(j=0;j<32;j++){
			free(array[j]);
		}
		free((void*)lol);
		free((void*)meep);
		for(k=0;k<10;k++){
			free(array[k]+k);
			free(&lol+k);
		}

		gettimeofday(&end,NULL);
		long seconds = (end.tv_sec-start.tv_sec);
		timeArray[j] = ((seconds*1000000)+end.tv_usec)-(start.tv_usec);
	}	
	findAvg("Test F", timeArray);
	

}


void findAvg(char* testName, long array[]){
        int i;
        long sum = 0;
        for(i=0;i<100;i++){
            sum += array[i];
        }
        printf("The average time for %s is %.6f seconds\n", testName, (float)sum/100);
}
