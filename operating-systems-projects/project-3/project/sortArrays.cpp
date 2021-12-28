#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <tr1/unordered_map>

#define CLOCK_INTERVAL 1 //miliseconds

#define TRESHOLD 5 //clock interval

int frameSize;
int physicalPageCount;
int virtualPageCount;
int opCount = 0;
int printInterval;


int valuesToSearchLinearly[5];

int valuesToSearchLogarithmicly[5];

char pageReplacementType[50];

char tableType[50];

char diskName[50];

struct pageTable{
	int referenced;
	int modified;
	int present;
	int frameNum;
	int clock;
};

struct pageStats{
	int readCount;
	int writeCount;
	int pageMissCount;
	int pageReplacementCount;
	int diskReadCount;
	int diskWriteCount;
};

int * physicalMemory;

pageTable * virtualMemory;

std::tr1::unordered_map <int,struct pageTable> hashedVirtualMemory;

std::tr1::unordered_map <char *, struct pageStats> stats;

int * bitMap;

int iterator = 0;

int fd;

int current = 0;

sem_t sem;

void generateNumbersToSearch();
void createEnvironments();
void fillVirtualMemory();
void writeBack();
void printTable();
void set(unsigned int index,int value, char * tName);
int get(unsigned int index, char * tName);
int replace(int virtualPageNum,char * tName,int notFill);
void * clock(void * args);
void * bubble(void * args);
void * quick(void * args);
void quickSort(int start,int end);
int partite(int start,int end);
void merge();
void * linear(void * args);
int linearSearch(int value);
void * binary(void * args);
int binarySearch(int value);
void writeStats();

int main(int argc, char *argv[]){
	if(argc != 8){
		printf("Please enter arguments with required count.\n");
		exit(-1);
	}
	if((frameSize = atoi(argv[1])) == 0){
		printf("Please enter a regular argument for frame size.\n");
		exit(-1);
	}
	frameSize = pow(2,frameSize);
	if((physicalPageCount = atoi(argv[2])) == 0){
		printf("Please enter a regular argument for physical page count.\n");
		exit(-1);
	}
	physicalPageCount = pow(2,physicalPageCount);
	if((virtualPageCount = atoi(argv[3])) == 0){
		printf("Please enter a regular argument for virtual page count.\n");
		exit(-1);
	}
	virtualPageCount = pow(2,virtualPageCount);
	strcpy(pageReplacementType,argv[4]);
	if(strcmp(pageReplacementType,"NRU") != 0 && strcmp(pageReplacementType,"FIFO") != 0 && strcmp(pageReplacementType,"SC") != 0 
	&& strcmp(pageReplacementType,"LRU") != 0 && strcmp(pageReplacementType,"WSClock") != 0){
		printf("Please enter a regular argument for page replacement type.\n");
		exit(-1);
	}
	strcpy(tableType,argv[5]);
	if(strcmp(tableType,"regular") != 0 && strcmp(tableType,"inverted") != 0){
		printf("Please enter a regular argument for table type.\n");
		exit(-1);
	}
	if((printInterval = atoi(argv[6])) == 0){
		printf("Please enter a regular argument for print interval.\n");
		exit(-1);
	}
	strcpy(diskName,argv[7]);
	if((fd = open(diskName,O_CREAT|O_RDWR,00666)) == -1){
		printf("The disk is not able to be accessed.\n");
		exit(-1);
	}
	sem_init(&sem,0,1);
	pthread_t threadClock;
	pthread_create(&threadClock,0,&clock,0);
	createEnvironments();
	fillVirtualMemory();
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1,0,&bubble,0);
	pthread_create(&thread2,0,&quick,0);
	pthread_join(thread1,0);
	pthread_join(thread2,0);
	merge();
	generateNumbersToSearch();
	pthread_t thread3;
	pthread_t thread4;
	pthread_create(&thread3,0,&linear,0);
	pthread_create(&thread4,0,&binary,0);
	pthread_join(thread3,0);
	pthread_join(thread4,0);
	writeBack();	//this function writes all modified frames from physical memory to the disk before the program ends
	writeStats();
	
	//optional code to write all the contents of the disk file

	/*
	lseek(fd,0,SEEK_SET);
	int temp;
	for (int i = 0; i < virtualPageCount*frameSize; ++i){
		read(fd,&temp,sizeof(int));
		printf("Index %d: %d\n",i,temp);
	}
	*/
	return 0;
}

void generateNumbersToSearch(){
	int indexToSearch = (virtualPageCount*frameSize-3)%(virtualPageCount*frameSize);
	lseek(fd,indexToSearch*sizeof(int),SEEK_SET);
	read(fd,&valuesToSearchLinearly[0],sizeof(int));
	indexToSearch = (indexToSearch+1)%(virtualPageCount*frameSize);
	lseek(fd,indexToSearch*sizeof(int),SEEK_SET);
	read(fd,&valuesToSearchLinearly[1],sizeof(int));
	indexToSearch = (indexToSearch+1)%(virtualPageCount*frameSize);
	lseek(fd,indexToSearch*sizeof(int),SEEK_SET);
	read(fd,&valuesToSearchLinearly[2],sizeof(int));
	valuesToSearchLinearly[3] = valuesToSearchLinearly[2] + 1;
	valuesToSearchLinearly[4] = valuesToSearchLinearly[3] + 1;
	indexToSearch = 0;
	lseek(fd,indexToSearch*sizeof(int),SEEK_SET);
	read(fd,&valuesToSearchLogarithmicly[2],sizeof(int));
	indexToSearch = (indexToSearch+1)%(virtualPageCount*frameSize);
	lseek(fd,indexToSearch*sizeof(int),SEEK_SET);
	read(fd,&valuesToSearchLogarithmicly[3],sizeof(int));
	indexToSearch = (indexToSearch+1)%(virtualPageCount*frameSize);
	lseek(fd,indexToSearch*sizeof(int),SEEK_SET);
	read(fd,&valuesToSearchLogarithmicly[4],sizeof(int));
	valuesToSearchLogarithmicly[1] = valuesToSearchLogarithmicly[2] - 1;
	valuesToSearchLogarithmicly[0] = valuesToSearchLogarithmicly[1] - 1;
	return;
}

void createEnvironments(){
	for (int i = 0; i < 6; ++i){
		struct pageStats * temp = (struct pageStats *)calloc(1,sizeof(struct pageStats));
		temp->readCount = 0;
		temp->writeCount = 0;
		temp->pageMissCount = 0;
		temp->pageReplacementCount = 0;
		temp->diskReadCount = 0;
		temp->diskWriteCount = 0;
		if(i == 0){
			stats["fill"] = *temp;
		}
		else if(i == 1){
			stats["quick"] = *temp;
		}
		else if(i == 2){
			stats["bubble"] = *temp;
		}
		else if(i == 3){
			stats["merge"] = *temp;
		}
		else if(i == 4){
			stats["linear"] = *temp;
		}
		else if(i == 5){
			stats["binary"] = *temp;
		}
		else{
			stats["writeBack"] = *temp;
		}
	}
	physicalMemory = (int*)calloc(physicalPageCount*frameSize,sizeof(int));
	bitMap = (int*) calloc(physicalPageCount,sizeof(int));
	for (int i = 0; i < physicalPageCount; ++i){
		bitMap[i] = -1;
	}
	if(strcmp(tableType,"regular") == 0){
		virtualMemory = (struct pageTable *)calloc(virtualPageCount,sizeof(struct pageTable));
		for (int i = 0; i < virtualPageCount; ++i)
		{
			virtualMemory[i].present = 0;
			virtualMemory[i].referenced = 0;
			virtualMemory[i].modified = 0;
			virtualMemory[i].clock = 0;
			virtualMemory[i].frameNum = -1;
		}
	}
	else{
		for (int i = 0; i < virtualPageCount; ++i){
			struct pageTable * temp = (struct pageTable *)calloc(1,sizeof(struct pageTable));
			temp->present = 0;
			temp->referenced = 0;
			temp->modified = 0;
			temp->clock = 0;
			temp->frameNum = -1;
			hashedVirtualMemory[i] = *temp;
		}
	}
	return;
}

void fillVirtualMemory(){
	srand(1000);
	for (int i = 0; i < virtualPageCount*frameSize; ++i){
		set(i,rand(),"fill");
	}
	return;
}

void writeBack(){
	if(strcmp(tableType,"regular") == 0){
		for (int i = 0; i < physicalPageCount; ++i){
			if(virtualMemory[bitMap[i]].modified = 1){
				int * offset = &physicalMemory[i*frameSize];
				lseek(fd,bitMap[i]*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats["writeBack"].diskWriteCount;
			}
		}
	}
	else{
		for (int i = 0; i < physicalPageCount; ++i){
			if(hashedVirtualMemory[bitMap[i]].modified = 1){
				int * offset = &physicalMemory[i*frameSize];
				lseek(fd,bitMap[i]*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats["writeBack"].diskWriteCount;
			}
		}
	}
	return;
}

void printTable(){
	if(strcmp(tableType,"regular") == 0){
		printf("\nContent of all tables after interval %d:\n\n",opCount/printInterval);
		for (int i = 0; i < virtualPageCount; ++i){
			printf("	Page number: %d\n",i);
			printf("	Present bit: %d\n",virtualMemory[i].present);
			if(virtualMemory[i].present){
				printf("	Frame number: %d\n",virtualMemory[i].frameNum);
				printf("	Referenced bit: %d\n",virtualMemory[i].referenced);
				printf("	Modified bit: %d\n",virtualMemory[i].modified);
				if(strcmp(pageReplacementType,"WSClock") == 0){
					printf("	Last access time: %d\n\n",virtualMemory[i].clock);
				}
				else if(strcmp(pageReplacementType,"LRU") == 0){
					printf("	Age info of the page: %08d\n\n",virtualMemory[i].clock);
				}
				else printf("\n");
			}
			else printf("\n");
		}
	}
	else{
		printf("\nContent of all tables after interval %d:\n\n",opCount/printInterval);
		for (int i = 0; i < virtualPageCount; ++i){
			printf("	Page number: %d\n",i);
			printf("	Present bit: %d\n",hashedVirtualMemory[i].present);
			if(hashedVirtualMemory[i].present){
				printf("	Frame number: %d\n",hashedVirtualMemory[i].frameNum);
				printf("	Referenced bit: %d\n",hashedVirtualMemory[i].referenced);
				printf("	Modified bit: %d\n",hashedVirtualMemory[i].modified);
				if(strcmp(pageReplacementType,"WSClock") == 0){
					printf("	Last access time: %d\n\n",hashedVirtualMemory[i].clock);
				}
				else if(strcmp(pageReplacementType,"LRU") == 0){
					printf("	Age info of the page: %08d\n\n",hashedVirtualMemory[i].clock);
				}
				else printf("\n");
			}
			else printf("\n");
		}
	}
	return;
}

void set(unsigned int index,int value, char * tName){
	if(strcmp(tableType,"regular") == 0){
		sem_wait(&sem);
		int virtualPageNum = index / frameSize;
		int offset = index % frameSize;
		if(strcmp(tName,"fill") == 0){
			if(virtualMemory[virtualPageNum].present == 1){
				physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
				virtualMemory[virtualPageNum].referenced = 1;
				virtualMemory[virtualPageNum].modified = 1;
				if(strcmp(pageReplacementType,"WSClock") == 0){
					virtualMemory[virtualPageNum].clock = current;
				}
				++stats[tName].writeCount;
			}
			else{
				for (int i = 0; i < physicalPageCount; ++i){
					if(bitMap[i] == -1){
						bitMap[i] = virtualPageNum;
						virtualMemory[virtualPageNum].present = 1;
						virtualMemory[virtualPageNum].referenced = 1;
						virtualMemory[virtualPageNum].modified = 1;
						virtualMemory[virtualPageNum].frameNum = i;
						physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
						if(strcmp(pageReplacementType,"WSClock") == 0){
							virtualMemory[virtualPageNum].clock = current;
						}
						++stats[tName].writeCount;
						break;
					}
				}
				if(virtualMemory[virtualPageNum].present == 0){
					virtualMemory[virtualPageNum].frameNum = replace(virtualPageNum,tName,0);
					virtualMemory[virtualPageNum].present = 1;
					virtualMemory[virtualPageNum].referenced = 1;
					virtualMemory[virtualPageNum].modified = 1;
					physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
					if(strcmp(pageReplacementType,"WSClock") == 0){
						virtualMemory[virtualPageNum].clock = current;
					}
					++stats[tName].writeCount;
					++stats[tName].pageMissCount;
					++stats[tName].pageReplacementCount;
				}
			}
		}
		else{
			if(virtualMemory[virtualPageNum].present == 1){
				physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
				virtualMemory[virtualPageNum].referenced = 1;
				virtualMemory[virtualPageNum].modified = 1;
				if(strcmp(pageReplacementType,"WSClock") == 0){
					virtualMemory[virtualPageNum].clock = current;
				}
				++stats[tName].writeCount;
			}
			else{
				virtualMemory[virtualPageNum].frameNum = replace(virtualPageNum,tName,1);
				virtualMemory[virtualPageNum].present = 1;
				virtualMemory[virtualPageNum].referenced = 1;
				virtualMemory[virtualPageNum].modified = 1;
				physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
				if(strcmp(pageReplacementType,"WSClock") == 0){
					virtualMemory[virtualPageNum].clock = current;
				}
				++stats[tName].writeCount;
				++stats[tName].pageMissCount;
				++stats[tName].pageReplacementCount;
			}
		}
		++opCount;
		if(opCount%printInterval == 0){
			printTable();
		}
		sem_post(&sem);
	}
	else{
		sem_wait(&sem);
		int virtualPageNum = index / frameSize;
		int offset = index % frameSize;
		if(strcmp(tName,"fill") == 0){
			if(hashedVirtualMemory[virtualPageNum].present == 1){
				physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
				hashedVirtualMemory[virtualPageNum].referenced = 1;
				hashedVirtualMemory[virtualPageNum].modified = 1;
				if(strcmp(pageReplacementType,"WSClock") == 0){
					hashedVirtualMemory[virtualPageNum].clock = current;
				}
				++stats[tName].writeCount;
			}
			else{
				for (int i = 0; i < physicalPageCount; ++i){
					if(bitMap[i] == -1){
						bitMap[i] = virtualPageNum;
						hashedVirtualMemory[virtualPageNum].present = 1;
						hashedVirtualMemory[virtualPageNum].referenced = 1;
						hashedVirtualMemory[virtualPageNum].modified = 1;
						hashedVirtualMemory[virtualPageNum].frameNum = i;
						physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
						if(strcmp(pageReplacementType,"WSClock") == 0){
							hashedVirtualMemory[virtualPageNum].clock = current;
						}
						++stats[tName].writeCount;
						break;
					}
				}
				if(hashedVirtualMemory[virtualPageNum].present == 0){
					hashedVirtualMemory[virtualPageNum].frameNum = replace(virtualPageNum,tName,0);
					hashedVirtualMemory[virtualPageNum].present = 1;
					hashedVirtualMemory[virtualPageNum].referenced = 1;
					hashedVirtualMemory[virtualPageNum].modified = 1;
					physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
					if(strcmp(pageReplacementType,"WSClock") == 0){
						hashedVirtualMemory[virtualPageNum].clock = current;
					}
					++stats[tName].writeCount;
					++stats[tName].pageMissCount;
					++stats[tName].pageReplacementCount;
				}
			}
		}
		else{
			if(hashedVirtualMemory[virtualPageNum].present == 1){
				physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
				hashedVirtualMemory[virtualPageNum].referenced = 1;
				hashedVirtualMemory[virtualPageNum].modified = 1;
				if(strcmp(pageReplacementType,"WSClock") == 0){
					hashedVirtualMemory[virtualPageNum].clock = current;
				}
				++stats[tName].writeCount;
			}
			else{
				hashedVirtualMemory[virtualPageNum].frameNum = replace(virtualPageNum,tName,1);
				hashedVirtualMemory[virtualPageNum].present = 1;
				hashedVirtualMemory[virtualPageNum].referenced = 1;
				hashedVirtualMemory[virtualPageNum].modified = 1;
				physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset] = value;
				if(strcmp(pageReplacementType,"WSClock") == 0){
					hashedVirtualMemory[virtualPageNum].clock = current;
				}
				++stats[tName].writeCount;
				++stats[tName].pageMissCount;
				++stats[tName].pageReplacementCount;
			}
		}
		++opCount;
		if(opCount%printInterval == 0){
			printTable();
		}
		sem_post(&sem);
	}
	return;
}

int get(unsigned int index, char * tName){
	int value;
	if(strcmp(tableType,"regular") == 0){
		sem_wait(&sem);
		int virtualPageNum = index / frameSize;
		int offset = index % frameSize;
		if(virtualMemory[virtualPageNum].present == 1){
			value = physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset];
			virtualMemory[virtualPageNum].referenced = 1;
			if(strcmp(pageReplacementType,"WSClock") == 0){
				virtualMemory[virtualPageNum].clock = current;
			}
			++stats[tName].readCount;
		}
		else{
			virtualMemory[virtualPageNum].frameNum = replace(virtualPageNum,tName,1);
			virtualMemory[virtualPageNum].present = 1;
			virtualMemory[virtualPageNum].referenced = 1;
			value = physicalMemory[virtualMemory[virtualPageNum].frameNum*frameSize + offset];
			if(strcmp(pageReplacementType,"WSClock") == 0){
				virtualMemory[virtualPageNum].clock = current;
			}
			++stats[tName].readCount;
			++stats[tName].pageMissCount;
			++stats[tName].pageReplacementCount;
		}
		++opCount;
		if(opCount%printInterval == 0){
			printTable();
		}
		sem_post(&sem);
	}
	else{
		sem_wait(&sem);
		int virtualPageNum = index / frameSize;
		int offset = index % frameSize;
		if(hashedVirtualMemory[virtualPageNum].present == 1){
			value = physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset];
			hashedVirtualMemory[virtualPageNum].referenced = 1;
			if(strcmp(pageReplacementType,"WSClock") == 0){
				hashedVirtualMemory[virtualPageNum].clock = current;
			}
			++stats[tName].readCount;
		}
		else{
			hashedVirtualMemory[virtualPageNum].frameNum = replace(virtualPageNum,tName,1);
			hashedVirtualMemory[virtualPageNum].present = 1;
			hashedVirtualMemory[virtualPageNum].referenced = 1;
			value = physicalMemory[hashedVirtualMemory[virtualPageNum].frameNum*frameSize + offset];
			if(strcmp(pageReplacementType,"WSClock") == 0){
				hashedVirtualMemory[virtualPageNum].clock = current;
			}
			++stats[tName].readCount;
			++stats[tName].pageMissCount;
			++stats[tName].pageReplacementCount;
		}
		++opCount;
		if(opCount%printInterval == 0){
			printTable();
		}
		sem_post(&sem);
	}
	return value;
}

int replace(int virtualPageNum,char * tName,int notFill){
	int frameNum;
	if(strcmp(tableType,"regular") == 0){
		if(strcmp(pageReplacementType,"FIFO") == 0){
			int pageToReplace = bitMap[iterator];
			int * offset = &physicalMemory[iterator*frameSize];
			if(virtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[iterator] = virtualPageNum;
			virtualMemory[pageToReplace].present = 0;
			virtualMemory[pageToReplace].referenced = 0;
			virtualMemory[pageToReplace].modified = 0;
			virtualMemory[pageToReplace].frameNum = -1;
			frameNum = iterator;
			iterator = (iterator+1)%physicalPageCount;
		}
		else if(strcmp(pageReplacementType,"SC") == 0){
			while(virtualMemory[bitMap[iterator]].referenced == 1){
				virtualMemory[bitMap[iterator]].referenced = 0;
				iterator = (iterator+1)%physicalPageCount;
			}
			int pageToReplace = bitMap[iterator];
			int * offset = &physicalMemory[iterator*frameSize];
			if(virtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[iterator] = virtualPageNum;
			virtualMemory[pageToReplace].present = 0;
			virtualMemory[pageToReplace].referenced = 0;
			virtualMemory[pageToReplace].modified = 0;
			virtualMemory[pageToReplace].frameNum = -1;
			frameNum = iterator;
			iterator = (iterator+1)%physicalPageCount;
		}
		else if(strcmp(pageReplacementType,"NRU") == 0){
			int index = -1;
			for (int i = 0; i < physicalPageCount; ++i){
				if(virtualMemory[bitMap[i]].referenced == 0 && virtualMemory[bitMap[i]].modified == 0){
					index = i;
					break;
				}
			}
			if(index == -1){
				for (int i = 0; i < physicalPageCount; ++i){
					if(virtualMemory[bitMap[i]].referenced == 0 && virtualMemory[bitMap[i]].modified == 1){
						index = i;
						break;
					}
				}
			}
			if(index == -1){
				for (int i = 0; i < physicalPageCount; ++i){
					if(virtualMemory[bitMap[i]].referenced == 1 && virtualMemory[bitMap[i]].modified == 0){
						index = i;
						break;
					}
				}
			}
			if(index == -1){
				for (int i = 0; i < physicalPageCount; ++i){
					if(virtualMemory[bitMap[i]].referenced == 1 && virtualMemory[bitMap[i]].modified == 1){
						index = i;
						break;
					}
				}
			}
			int pageToReplace = bitMap[index];
			int * offset = &physicalMemory[index*frameSize];
			if(virtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[index] = virtualPageNum;
			virtualMemory[pageToReplace].present = 0;
			virtualMemory[pageToReplace].referenced = 0;
			virtualMemory[pageToReplace].modified = 0;
			virtualMemory[pageToReplace].frameNum = -1;
			frameNum = index;
		}
		else if(strcmp(pageReplacementType,"LRU") == 0){
			int clock = 111111111;
			int index = -1;
			for (int i = 0; i < physicalPageCount; ++i){
				if(virtualMemory[bitMap[i]].clock < clock){
					clock = virtualMemory[bitMap[i]].clock;
					index = i;
				}
			}
			int pageToReplace = bitMap[index];
			int * offset = &physicalMemory[index*frameSize];
			if(virtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[index] = virtualPageNum;
			virtualMemory[pageToReplace].present = 0;
			virtualMemory[pageToReplace].referenced = 0;
			virtualMemory[pageToReplace].modified = 0;
			virtualMemory[pageToReplace].clock = 0;
			virtualMemory[pageToReplace].frameNum = -1;
			frameNum = index;
		}
		else{
			int breakHappened = 0;
			int firstModified = -1;
			int smallerModified = -1;
			int smallerClean = -1;
			for (int i = 0; i < physicalPageCount; ++i){
				if(virtualMemory[bitMap[iterator]].referenced == 1){
					virtualMemory[bitMap[iterator]].referenced = 0;
					iterator = (iterator+1)%physicalPageCount;
				}
				else if((current - virtualMemory[bitMap[iterator]].clock) > TRESHOLD && virtualMemory[bitMap[iterator]].modified == 0){
					breakHappened = 1;
					break;
				}
				else if((current - virtualMemory[bitMap[iterator]].clock) > TRESHOLD && virtualMemory[bitMap[iterator]].modified == 1){
					if(firstModified == -1)
						firstModified = iterator;
					int innerPageToReplace = bitMap[iterator];
					int * innerOffset = &physicalMemory[iterator*frameSize];
					lseek(fd,innerPageToReplace*frameSize*sizeof(int),SEEK_SET);
					write(fd,innerOffset,frameSize*sizeof(int));
					virtualMemory[bitMap[iterator]].modified = 0;
					++stats[tName].diskWriteCount;
					iterator = (iterator+1)%physicalPageCount;
				}
				else{
					if(virtualMemory[bitMap[iterator]].modified == 1){
						if(smallerModified == -1)
							smallerModified = iterator;
					}
					else{
						if(smallerClean == -1)
							smallerClean = iterator;
					}
					iterator = (iterator+1)%physicalPageCount;
				}
			}
			if(!breakHappened){
				if(firstModified != -1){
					iterator = firstModified;
				}
				else if(smallerClean != -1){
					iterator = smallerClean;
				}
				else if(smallerModified != -1){
					iterator = smallerModified;
				}
			}
			int pageToReplace = bitMap[iterator];
			int * offset = &physicalMemory[iterator*frameSize];
			if(virtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[iterator] = virtualPageNum;
			virtualMemory[pageToReplace].present = 0;
			virtualMemory[pageToReplace].referenced = 0;
			virtualMemory[pageToReplace].modified = 0;
			virtualMemory[pageToReplace].clock = 0;
			virtualMemory[pageToReplace].frameNum = -1;
			frameNum = iterator;
			iterator = (iterator+1)%physicalPageCount;
		}
	}
	else{
		if(strcmp(pageReplacementType,"FIFO") == 0){
			int pageToReplace = bitMap[iterator];
			int * offset = &physicalMemory[iterator*frameSize];
			if(hashedVirtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[iterator] = virtualPageNum;
			hashedVirtualMemory[pageToReplace].present = 0;
			hashedVirtualMemory[pageToReplace].referenced = 0;
			hashedVirtualMemory[pageToReplace].modified = 0;
			hashedVirtualMemory[pageToReplace].frameNum = -1;
			frameNum = iterator;
			iterator = (iterator+1)%physicalPageCount;
		}
		else if(strcmp(pageReplacementType,"SC") == 0){
			while(hashedVirtualMemory[bitMap[iterator]].referenced == 1){
				hashedVirtualMemory[bitMap[iterator]].referenced = 0;
				iterator = (iterator+1)%physicalPageCount;
			}
			int pageToReplace = bitMap[iterator];
			int * offset = &physicalMemory[iterator*frameSize];
			if(hashedVirtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[iterator] = virtualPageNum;
			hashedVirtualMemory[pageToReplace].present = 0;
			hashedVirtualMemory[pageToReplace].referenced = 0;
			hashedVirtualMemory[pageToReplace].modified = 0;
			hashedVirtualMemory[pageToReplace].frameNum = -1;
			frameNum = iterator;
			iterator = (iterator+1)%physicalPageCount;
		}
		else if(strcmp(pageReplacementType,"NRU") == 0){
			int index = -1;
			for (int i = 0; i < physicalPageCount; ++i){
				if(hashedVirtualMemory[bitMap[i]].referenced == 0 && hashedVirtualMemory[bitMap[i]].modified == 0){
					index = i;
					break;
				}
			}
			if(index == -1){
				for (int i = 0; i < physicalPageCount; ++i){
					if(hashedVirtualMemory[bitMap[i]].referenced == 0 && hashedVirtualMemory[bitMap[i]].modified == 1){
						index = i;
						break;
					}
				}
			}
			if(index == -1){
				for (int i = 0; i < physicalPageCount; ++i){
					if(hashedVirtualMemory[bitMap[i]].referenced == 1 && hashedVirtualMemory[bitMap[i]].modified == 0){
						index = i;
						break;
					}
				}
			}
			if(index == -1){
				for (int i = 0; i < physicalPageCount; ++i){
					if(hashedVirtualMemory[bitMap[i]].referenced == 1 && hashedVirtualMemory[bitMap[i]].modified == 1){
						index = i;
						break;
					}
				}
			}
			int pageToReplace = bitMap[index];
			int * offset = &physicalMemory[index*frameSize];
			if(hashedVirtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[index] = virtualPageNum;
			hashedVirtualMemory[pageToReplace].present = 0;
			hashedVirtualMemory[pageToReplace].referenced = 0;
			hashedVirtualMemory[pageToReplace].modified = 0;
			hashedVirtualMemory[pageToReplace].frameNum = -1;
			frameNum = index;
		}
		else if(strcmp(pageReplacementType,"LRU") == 0){
			int clock = 111111111;
			int index = -1;
			for (int i = 0; i < physicalPageCount; ++i){
				if(hashedVirtualMemory[bitMap[i]].clock < clock){
					clock = hashedVirtualMemory[bitMap[i]].clock;
					index = i;
				}
			}
			int pageToReplace = bitMap[index];
			int * offset = &physicalMemory[index*frameSize];
			if(hashedVirtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[index] = virtualPageNum;
			hashedVirtualMemory[pageToReplace].present = 0;
			hashedVirtualMemory[pageToReplace].referenced = 0;
			hashedVirtualMemory[pageToReplace].modified = 0;
			hashedVirtualMemory[pageToReplace].clock = 0;
			hashedVirtualMemory[pageToReplace].frameNum = -1;
			frameNum = index;
		}
		else{
			int breakHappened = 0;
			int firstModified = -1;
			int smallerModified = -1;
			int smallerClean = -1;
			for (int i = 0; i < physicalPageCount; ++i){
				if(hashedVirtualMemory[bitMap[iterator]].referenced == 1){
					hashedVirtualMemory[bitMap[iterator]].referenced = 0;
					iterator = (iterator+1)%physicalPageCount;
				}
				else if((current - hashedVirtualMemory[bitMap[iterator]].clock) > TRESHOLD && hashedVirtualMemory[bitMap[iterator]].modified == 0){
					breakHappened = 1;
					break;
				}
				else if((current - hashedVirtualMemory[bitMap[iterator]].clock) > TRESHOLD && hashedVirtualMemory[bitMap[iterator]].modified == 1){
					if(firstModified == -1)
						firstModified = iterator;
					int innerPageToReplace = bitMap[iterator];
					int * innerOffset = &physicalMemory[iterator*frameSize];
					lseek(fd,innerPageToReplace*frameSize*sizeof(int),SEEK_SET);
					write(fd,innerOffset,frameSize*sizeof(int));
					hashedVirtualMemory[bitMap[iterator]].modified = 0;
					++stats[tName].diskWriteCount;
					iterator = (iterator+1)%physicalPageCount;
				}
				else{
					if(hashedVirtualMemory[bitMap[iterator]].modified == 1){
						if(smallerModified == -1)
							smallerModified = iterator;
					}
					else{
						if(smallerClean == -1)
							smallerClean = iterator;
					}
					iterator = (iterator+1)%physicalPageCount;
				}
			}
			if(!breakHappened){
				if(firstModified != -1){
					iterator = firstModified;
				}
				else if(smallerClean != -1){
					iterator = smallerClean;
				}
				else if(smallerModified != -1){
					iterator = smallerModified;
				}
			}
			int pageToReplace = bitMap[iterator];
			int * offset = &physicalMemory[iterator*frameSize];
			if(hashedVirtualMemory[pageToReplace].modified == 1){
				lseek(fd,pageToReplace*frameSize*sizeof(int),SEEK_SET);
				write(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskWriteCount;
			}
			if(notFill){
				lseek(fd,virtualPageNum*frameSize*sizeof(int),SEEK_SET);
				read(fd,offset,frameSize*sizeof(int));
				++stats[tName].diskReadCount;
			}
			bitMap[iterator] = virtualPageNum;
			hashedVirtualMemory[pageToReplace].present = 0;
			hashedVirtualMemory[pageToReplace].referenced = 0;
			hashedVirtualMemory[pageToReplace].modified = 0;
			hashedVirtualMemory[pageToReplace].clock = 0;
			hashedVirtualMemory[pageToReplace].frameNum = -1;
			frameNum = iterator;
			iterator = (iterator+1)%physicalPageCount;
		}
	}
	return frameNum;
}	

void * clock(void * args){
	while(1){
		usleep(CLOCK_INTERVAL*1000);
		if(strcmp(tableType,"regular") == 0){
			if(strcmp(pageReplacementType,"LRU") == 0){
				sem_wait(&sem);
				for (int i = 0; i < physicalPageCount; ++i){
					if(bitMap[i] != -1){
						virtualMemory[bitMap[i]].clock /= 10;
						if(virtualMemory[bitMap[i]].referenced == 1){
							virtualMemory[bitMap[i]].clock += 10000000;
						}
					}
				}
				sem_post(&sem);
			}
			else if(strcmp(pageReplacementType,"WSClock") == 0){
				sem_wait(&sem);
				++current;
				sem_post(&sem);
			}
		}
		else{
			if(strcmp(pageReplacementType,"LRU") == 0){
				sem_wait(&sem);
				for (int i = 0; i < physicalPageCount; ++i){
					if(bitMap[i] != -1){
						hashedVirtualMemory[bitMap[i]].clock /= 10;
						if(hashedVirtualMemory[bitMap[i]].referenced == 1){
							hashedVirtualMemory[bitMap[i]].clock += 10000000;
						}
					}
				}
				sem_post(&sem);
			}
			else if(strcmp(pageReplacementType,"WSClock") == 0){
				sem_wait(&sem);
				++current;
				sem_post(&sem);
			}
		}
	}
	return 0;
}

void * bubble(void * args){
	int start = 0;
	int end = (virtualPageCount*frameSize)/2 - 1;
	for (int i = end; i > start; --i){
		for (int j = start; j < i; ++j){
			int tempI = get(j,"bubble");
			int tempJ = get(j+1,"bubble");
			if(tempI > tempJ){
				set(j,tempJ,"bubble");
				set(j+1,tempI,"bubble");
			}
		}
	}
	return 0;
}

void * quick(void * args){
	int start = (virtualPageCount*frameSize)/2;
	int end = virtualPageCount*frameSize - 1;
	int mid = partite(start,end);
	if(mid-start > 1)
		quickSort(start,mid-1);
	if(end-mid > 1)
		quickSort(mid+1,end);
	return 0;
}

void quickSort(int start,int end){
	int mid = partite(start,end);
	if(mid-start > 1)
		quickSort(start,mid-1);
	if(end-mid > 1)
		quickSort(mid+1,end);
	return;
}

int partite(int start,int end){
	int pivot = get(end,"quick");
	int i = start;
	for (int j = start; j < end; ++j){
		int tempJ = get(j,"quick");
		if(tempJ <= pivot){
			int tempI = get(i,"quick");
			set(i,tempJ,"quick");
			set(j,tempI,"quick");
			++i;
		}
	}
	int mid = get(i,"quick");
	set(i,pivot,"quick");
	set(end,mid,"quick");
	return i;
}

void merge(){
	int mid = (virtualPageCount*frameSize)/2;
	int end = virtualPageCount*frameSize - 1;
	for (int i = mid; i <= end; ++i){
		for (int j = i; j > 0; --j){
			int tempI = get(j-1,"merge");
			int tempJ = get(j,"merge");
			if(tempJ < tempI){
				set(j-1,tempJ,"merge");
				set(j,tempI,"merge");
			}
			else break;
		}
	}
	return;
}

void * linear(void * args){
	for (int i = 0; i < 5; ++i){
		int res = linearSearch(valuesToSearchLinearly[i]);
		if(res != -1){
			printf("%d found in the disk linearly\n",valuesToSearchLinearly[i]);
		}
		else{
			printf("%d not found in the disk linearly\n",valuesToSearchLinearly[i]);
		}
	}
	return 0;
}

int linearSearch(int value){
	int end =virtualPageCount*frameSize-1;
	int res = -1;
	for (int i = 0; i <= end; ++i){
		int temp = get(i,"linear");
		if(temp == value){
			res = i;
			break;
		}
	}
	return res;
}

void * binary(void * args){
	for (int i = 0; i < 5; ++i){
		int res = binarySearch(valuesToSearchLogarithmicly[i]);
		if(res != -1){
			printf("%d found in the disk logarithmicly\n",valuesToSearchLogarithmicly[i]);
		}
		else{
			printf("%d not found in the disk logarithmicly\n",valuesToSearchLogarithmicly[i]);
		}
	}
	return 0;
}

int binarySearch(int value){
	int start = 0;
	int end = virtualPageCount*frameSize-1;
	int res = -1;
	while(end >= start){
		int mid = (start+end)/2;
		int temp = get(mid,"binary");
		if(temp == value){
			res = mid;
			break;
		}
		else if(temp > value){
			end = mid - 1;
		}
		else{
			start = mid + 1;
		}
	}
	return res;
}

void writeStats(){
	printf("\nRESULTS\n\n");
	for (int i = 0; i < 7; ++i){
		struct pageStats * temp;
		if(i == 0){
			printf("	Thread to fill the virtual memory:\n\n");
			temp = &stats["fill"];
		}
		else if(i == 1){
			printf("	Quick sort thread:\n\n");
			temp = &stats["quick"];
		}
		else if(i == 2){
			printf("	Bubble sort thread:\n\n");
			temp = &stats["bubble"];
		}
		else if(i == 3){
			printf("	Merge thread:\n\n");
			temp = &stats["merge"];
		}
		else if(i == 4){
			printf("	Linear search thread:\n\n");
			temp = &stats["linear"];
		}
		else if(i == 5){
			printf("	Binary search thread:\n\n");
			temp = &stats["binary"];
		}
		else{
			printf("	Thread to write back to disk:\n\n");
			temp = &stats["writeBack"];
		}
		printf("	Total reads: %d\n",temp->readCount);
		printf("	Total writes: %d\n",temp->writeCount);
		printf("	Total page misses: %d\n",temp->pageMissCount);
		printf("	Total page replacements: %d\n",temp->pageReplacementCount);
		printf("	Total disk reads: %d\n",temp->diskReadCount);
		printf("	Total disk writes: %d\n\n",temp->diskWriteCount);
	}
}