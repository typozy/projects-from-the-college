#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/time.h>
#include <unistd.h>

#define FAT_MAX 4096

int blockSize;

struct directoryEntry{
	char name[14];
	char attribute[2];
	unsigned int date;
	unsigned int time;
	int firstBlockAddress;
	int size;
};

int main(int argc, char *argv[]){
    time_t t = time(0);
    struct tm theTime = *localtime(&t);
	if(argc != 3){
		printf("Please enter parameters truly\n");
	}
	blockSize = atoi(argv[1]);
	if(blockSize != 1 && blockSize != 2 && blockSize != 4){
		printf("Please enter 1, 2 or 4 as block size\n");
		exit(-1);
	}
	blockSize *= 1024;
	int fd = open(argv[2],O_RDWR|O_CREAT,00666);
	if(fd == -1){
		printf("The disk file could not be created\n");
		exit(-1);
	}
	char junk[blockSize];
	for (int i = 0; i < blockSize; ++i)
	{
		junk[i] = '\0';
	}
	for (int i = 0; i < FAT_MAX; ++i){
		write(fd,junk,blockSize);
	}
	int blockOffset = (FAT_MAX*4)/blockSize;
	if(blockOffset == 0)
		++blockOffset;
	blockOffset = blockOffset+1;
	
	lseek(fd,blockSize,SEEK_SET);
	int temp = -2;
	for (int i = 0; i < FAT_MAX; ++i){
		if(i == blockOffset){
			temp = -1;
			write(fd,&temp,sizeof(int));
			temp = -2;
		}
		else{
			write(fd,&temp,sizeof(int));
		}
	}
	lseek(fd,0,SEEK_SET);
	write(fd,&blockSize,sizeof(int));
	write(fd,&blockOffset,sizeof(int));
	lseek(fd,32,SEEK_SET);
	struct directoryEntry root;
	strcpy(root.name,"");
	strcpy(root.attribute,"d");
	root.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	root.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	root.size = 0;
	root.firstBlockAddress = blockOffset;
	write(fd,&root,32);
	close(fd);
	return 0;
}