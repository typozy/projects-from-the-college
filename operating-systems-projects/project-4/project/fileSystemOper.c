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

struct directoryEntry{
	char name[14];
	char attribute[2];
	unsigned int date;
	unsigned int time;
	int firstBlockAddress;
	int size;
};

int blockSize;
int blockOffset;

int fatFile[FAT_MAX];

char path[500];

char otherFileName[50];
 
int fd;

time_t t;

struct tm theTime;

void readFile();

void writeFile();

void deleteFile();

void listDir();

void makeDir();

void removeDir();

void dumpe2fs();

void traverseDisk(char * path,int blockNum, int size);

int main(int argc, char *argv[]){
	t = time(0);
    theTime = *localtime(&t);
	fd = open(argv[1],O_RDWR);
	
	if(fd == -1){
		printf("The data file could not be opened\n");
		exit(-1);
	}

	int opCode;

	if(strcmp(argv[2],"dir") == 0 && argc == 4){
		opCode = 0;
	}
	else if(strcmp(argv[2],"mkdir") == 0 && argc == 4){
		opCode = 1;
	}
	else if(strcmp(argv[2],"rmdir") == 0 && argc == 4){
		opCode = 2;
	}
	else if(strcmp(argv[2],"dumpe2fs") == 0 && argc == 3){
		opCode = 3;
	}
	else if(strcmp(argv[2],"write") == 0 && argc == 5){
		opCode = 4;
	}
	else if(strcmp(argv[2],"read") == 0 && argc == 5){
		opCode = 5;
	} 
	else if(strcmp(argv[2],"del") == 0 && argc == 4){
		opCode = 6;
	}
	else{
		printf("Please enter a regular operation argument\n");
		exit(-1);
	}
	read(fd,&blockSize,sizeof(int));
	read(fd,&blockOffset,sizeof(int));
	lseek(fd,blockSize,SEEK_SET);
	read(fd,fatFile,FAT_MAX*4);
	if(argc == 4){
		strcpy(path,argv[3]);
	}
	else if(argc == 5){
		strcpy(path,argv[3]);
		strcpy(otherFileName,argv[4]);
	}

	switch(opCode){
		case 0:
			listDir();
			break;
		case 1:
			makeDir();
			break;
		case 2:
			removeDir();
			break;
		case 3:
			dumpe2fs();
			break;
		case 4:
			writeFile();
			break;
		case 5:
			readFile();
			break;
		case 6:
			deleteFile();
			break;
	}
	lseek(fd,blockSize,SEEK_SET);
	write(fd,fatFile,FAT_MAX*4);
	close(fd);
	return 0;
}



void listDir(){
	if(strcmp(path,"/") == 0){
		lseek(fd,32,SEEK_SET);
		struct directoryEntry root;
		read(fd,&root,32);
		lseek(fd,blockSize*(blockOffset),SEEK_SET);
		for (int i = 0; i < root.size; ++i){
			struct directoryEntry temp;
			read(fd,&temp,32);
			if(strcmp(temp.attribute,"d") == 0){
				printf("Date: %02d.%02d.%04d Time: %02d:%02d:%02d /%s (directory)\n",temp.date/1000000,(temp.date/10000)%100,temp.date%10000,temp.time/10000,(temp.time/100)%100,temp.time%100,temp.name);
			}
			else{
				printf("Date: %02d.%02d.%04d Time: %02d:%02d:%02d /%s Size: %d\n",temp.date/1000000,(temp.date/10000)%100,temp.date%10000,temp.time/10000,(temp.time/100)%100,temp.time%100,temp.name,temp.size);
			}
		}
	}
	else{
		int count = 0;
		for (int i = 0; i < strlen(path); ++i){
			if(path[i] == '/')
				++count;
		}
		lseek(fd,32,SEEK_SET);
		struct directoryEntry curDir;
		read(fd,&curDir,32);
		int cur = 1;
		for (int i = 0; i < count; ++i){
			char tempName[50];
			tempName[0] = '\0';
			while(path[cur] != '/' && path[cur] != '\0'){
				strncat(tempName,&path[cur],1);
				++cur;
			}
			++cur;
			lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
			struct directoryEntry temp;
			for (int j = 0; j < curDir.size; ++j){
				read(fd,&temp,32);
				if(strcmp(temp.name,tempName) == 0){
					memcpy(&curDir,&temp,32);
					break;
				}
			}
		}
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);

		for (int i = 0; i < curDir.size; ++i){
			struct directoryEntry temp;
			read(fd,&temp,32);
			if(strcmp(temp.attribute,"d") == 0){
				printf("Date: %02d.%02d.%04d Time: %02d:%02d:%02d %s/%s (directory)\n",temp.date/1000000,(temp.date/10000)%100,temp.date%10000,temp.time/10000,(temp.time/100)%100,temp.time%100,path,temp.name);
			}
			else{
				printf("Date: %02d.%02d.%04d Time: %02d:%02d:%02d %s/%s Size: %d\n",temp.date/1000000,(temp.date/10000)%100,temp.date%10000,temp.time/10000,(temp.time/100)%100,temp.time%100,path,temp.name,temp.size);
			}
		}
	}
	return;
}

void makeDir(){
	int count = 0;
	for (int i = 0; i < strlen(path); ++i){
		if(path[i] == '/')
			++count;
	}


	lseek(fd,32,SEEK_SET);
	struct directoryEntry curDir;
	read(fd,&curDir,32);
	int cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		int found = 0;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				memcpy(&curDir,&temp,32);
				found = 1;
				break;
			}
		}
		if(!found){
			printf("There is no path like that to make directory\n");
			exit(-1);
		}
	}



	lseek(fd,32,SEEK_SET);
	read(fd,&curDir,32);
	curDir.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	curDir.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	if(count == 1)
		curDir.size += 1;
	lseek(fd,-32,SEEK_CUR);
	write(fd,&curDir,32);
	cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				temp.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
				temp.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
				if(i == count-2)
					temp.size += 1;
				lseek(fd,-32,SEEK_CUR);
				write(fd,&temp,32);
				memcpy(&curDir,&temp,32);
				break;
			}
		}
	}
	char tempName[50];
	tempName[0] = '\0';
	while(path[cur] != '\0'){
		strncat(tempName,&path[cur],1);
		++cur;
	}
	lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
	lseek(fd,(curDir.size-1)*32,SEEK_CUR);
	struct directoryEntry newDir;
	strcpy(newDir.name,tempName);
	strcpy(newDir.attribute,"d");
	newDir.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	newDir.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	newDir.size = 0;
	for (int i = blockOffset; i < FAT_MAX; ++i){
		if(fatFile[i] == -2){
			fatFile[i] = -1;
			newDir.firstBlockAddress = i;
			break;
		}
	}
	write(fd,&newDir,32);
	return;
}

void removeDir(){
	int count = 0;
	for (int i = 0; i < strlen(path); ++i){
		if(path[i] == '/')
			++count;
	}

	lseek(fd,32,SEEK_SET);
	struct directoryEntry curDir;
	read(fd,&curDir,32);
	int cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		int found = 0;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				memcpy(&curDir,&temp,32);
				found = 1;
				break;
			}
		}
		if(!found){
			printf("There is no directory with this path to remove\n");
			exit(-1);
		}
	}
	char tempName[50];
	tempName[0] = '\0';
	while(path[cur] != '\0'){
		strncat(tempName,&path[cur],1);
		++cur;
	}
	lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
	struct directoryEntry temp;
	int found = 0;
	for (int i = 0; i < curDir.size+1; ++i){
		read(fd,&temp,32);
		if(strcmp(tempName,temp.name) == 0){
			if(temp.size > 0){
				printf("You cannot delete this folder, It is not empty\n");
				exit(-1);
			}
			found = 1;
			break;
		}
	}
	if(!found){
		printf("There is no directory with this path to remove\n");
		exit(-1);
	}









	lseek(fd,32,SEEK_SET);
	read(fd,&curDir,32);
	curDir.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	curDir.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	if(count == 1)
		curDir.size -= 1;
	lseek(fd,-32,SEEK_CUR);
	write(fd,&curDir,32);
	cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				temp.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
				temp.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
				if(i == count-2)
					temp.size -= 1;
				lseek(fd,-32,SEEK_CUR);
				write(fd,&temp,32);
				memcpy(&curDir,&temp,32);
				break;
			}
		}
	}
	tempName[0] = '\0';
	while(path[cur] != '\0'){
		strncat(tempName,&path[cur],1);
		++cur;
	}
	lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
	int index;
	for (int i = 0; i < curDir.size+1; ++i){
		read(fd,&temp,32);
		if(strcmp(tempName,temp.name) == 0){
			index = i;
			fatFile[temp.firstBlockAddress] = -2;
			break;
		}
	}
	if(index < curDir.size){
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		lseek(fd,curDir.size*32,SEEK_CUR);
		read(fd,&temp,32);
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		lseek(fd,index*32,SEEK_CUR);
		write(fd,&temp,32);
	}
}

void readFile(){
	int fdOther = open(otherFileName,O_RDWR|O_CREAT,00666);

	int count = 0;
	for (int i = 0; i < strlen(path); ++i){
		if(path[i] == '/')
			++count;
	}

	lseek(fd,32,SEEK_SET);
	struct directoryEntry curDir;
	read(fd,&curDir,32);
	int cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				memcpy(&curDir,&temp,32);
				break;
			}
		}
	}
	char tempName[50];
	tempName[0] = '\0';
	while(path[cur] != '\0'){
		strncat(tempName,&path[cur],1);
		++cur;
	}
	lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
	struct directoryEntry curFile;
	for (int i = 0; i < curDir.size; ++i){
		read(fd,&curFile,32);
		if(strcmp(curFile.name,tempName) == 0)
			break;
	}
	int current = curFile.firstBlockAddress;
	int iteration;
	if(curFile.size%blockSize == 0){
		iteration = curFile.size/blockSize;
	}
	else{
		iteration = curFile.size/blockSize + 1;
	}
	char temp[blockSize];
	for (int i = 0; i < iteration; ++i){
		if(i == iteration-1){
			if(curFile.size%blockSize == 0){
				lseek(fd,current*blockSize,SEEK_SET);
				read(fd,temp,blockSize);
				write(fdOther,temp,blockSize);
			}
			else{
				lseek(fd,current*blockSize,SEEK_SET);
				read(fd,temp,curFile.size%blockSize);
				write(fdOther,temp,curFile.size%blockSize);
			}
		}
		else{
			lseek(fd,current*blockSize,SEEK_SET);
			read(fd,temp,blockSize);
			write(fdOther,temp,blockSize);
			current = fatFile[current];
		}
	}
}

void writeFile(){
	int fdOther = open(otherFileName,O_RDONLY);
	if(fdOther == -1){
		printf("the file could not be opened\n");
		exit(-1);
	}
	int fileSize = 0;
	char junk;
	while(read(fdOther,&junk,1))
		++fileSize;
	lseek(fdOther,0,SEEK_SET);
	int iteration;

	if(fileSize%blockSize == 0){
		iteration = fileSize/blockSize;
	}
	else{
		iteration = fileSize/blockSize + 1;
	}

	int count = 0;
	for (int i = 0; i < strlen(path); ++i){
		if(path[i] == '/')
			++count;
	}

	lseek(fd,32,SEEK_SET);
	struct directoryEntry curDir;
	read(fd,&curDir,32);
	curDir.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	curDir.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	if(count == 1)
		curDir.size += 1;
	lseek(fd,-32,SEEK_CUR);
	write(fd,&curDir,32);
	int cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				temp.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
				temp.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
				if(i == count-2)
					temp.size += 1;
				lseek(fd,-32,SEEK_CUR);
				write(fd,&temp,32);
				memcpy(&curDir,&temp,32);
				break;
			}
		}
	}
	char tempName[50];
	tempName[0] = '\0';
	while(path[cur] != '\0'){
		strncat(tempName,&path[cur],1);
		++cur;
	}
	struct directoryEntry newFile;
	strcpy(newFile.name,tempName);
	strcpy(newFile.attribute,"f");
	newFile.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	newFile.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	newFile.size = fileSize;
	char temp[blockSize];
	if(iteration > 0){
		for (int i = blockOffset; i < FAT_MAX; ++i){
			if(fatFile[i] == -2){
				fatFile[i] = -1;
				newFile.firstBlockAddress = i;
				break;
			}
		}
		
		if(fileSize >= blockSize){
			read(fdOther,temp,blockSize);
			lseek(fd,newFile.firstBlockAddress*blockSize,SEEK_SET);
			write(fd,temp,blockSize);
		}
		else{
			read(fdOther,temp,fileSize);
			lseek(fd,newFile.firstBlockAddress*blockSize,SEEK_SET);
			write(fd,temp,fileSize);
		}
	}
	else{
		newFile.firstBlockAddress = -1;
	}
	int current = newFile.firstBlockAddress;
	for (int j = 1; j < iteration; ++j){
		for (int i = blockOffset; i < FAT_MAX; ++i){
			if(fatFile[i] == -2){
				fatFile[current] = i;
				fatFile[i] = -1;
				current = i;
				break;
			}
		}
		if(j == iteration-1){
			if(fileSize%blockSize == 0){
				read(fdOther,temp,blockSize);
				lseek(fd,current*blockSize,SEEK_SET);
				write(fd,temp,blockSize);
			}
			else{
				read(fdOther,temp,fileSize%blockSize);
				lseek(fd,current*blockSize,SEEK_SET);
				write(fd,temp,fileSize%blockSize);
			}
		}
		else{
			read(fdOther,temp,blockSize);
			lseek(fd,current*blockSize,SEEK_SET);
			write(fd,temp,blockSize);
		}
	}
	lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
	lseek(fd,32*(curDir.size-1),SEEK_CUR);
	write(fd,&newFile,32);
}

void deleteFile(){
	int count = 0;
	for (int i = 0; i < strlen(path); ++i){
		if(path[i] == '/')
			++count;
	}

	lseek(fd,32,SEEK_SET);
	struct directoryEntry curDir;
	read(fd,&curDir,32);
	curDir.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
	curDir.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
	if(count == 1)
		curDir.size -= 1;
	lseek(fd,-32,SEEK_CUR);
	write(fd,&curDir,32);
	int cur = 1;
	for (int i = 0; i < count-1; ++i){
		char tempName[50];
		tempName[0] = '\0';
		while(path[cur] != '/'){
			strncat(tempName,&path[cur],1);
			++cur;
		}
		++cur;
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		struct directoryEntry temp;
		for (int j = 0; j < curDir.size; ++j){
			read(fd,&temp,32);
			if(strcmp(temp.name,tempName) == 0){
				temp.time = theTime.tm_hour*10000 + theTime.tm_min*100 + theTime.tm_sec;
				temp.date = theTime.tm_mday*1000000 + (theTime.tm_mon+1)*10000 + (theTime.tm_year+1900);
				if(i == count-2)
					temp.size -= 1;
				lseek(fd,-32,SEEK_CUR);
				write(fd,&temp,32);
				memcpy(&curDir,&temp,32);
				break;
			}
		}
	}
	char tempName[50];
	tempName[0] = '\0';
	while(path[cur] != '\0'){
		strncat(tempName,&path[cur],1);
		++cur;
	}
	lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
	struct directoryEntry temp;
	int index;
	for (int i = 0; i < curDir.size+1; ++i){
		read(fd,&temp,32);
		if(strcmp(tempName,temp.name) == 0){
			index = i;
			break;
		}
	}
	int current = temp.firstBlockAddress;
	if(current != -1){
		while(fatFile[current] != -1){
			int next = fatFile[current];
			fatFile[current] = -2;
			current = next;
		}
		fatFile[current] = -2;
	}

	if(index < curDir.size){
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		lseek(fd,curDir.size*32,SEEK_CUR);
		read(fd,&temp,32);
		lseek(fd,blockSize*curDir.firstBlockAddress,SEEK_SET);
		lseek(fd,index*32,SEEK_CUR);
		write(fd,&temp,32);
	}
}

void dumpe2fs(){
	lseek(fd,32,SEEK_SET);
	struct directoryEntry temp;
	read(fd,&temp,32);
	char myPath[500];
	myPath[0] = '/';
	myPath[1] = '\0';
	printf("Directory: %s Occupied block addresses: %d\n",myPath,temp.firstBlockAddress);
	traverseDisk(myPath,temp.firstBlockAddress,temp.size);
}

void traverseDisk(char * myPath,int blockNum,int size){
	struct directoryEntry temp;
	for (int i = 0; i < size; ++i){
		lseek(fd,blockNum*blockSize,SEEK_SET);
		lseek(fd,i*32,SEEK_CUR);
		read(fd,&temp,32);
		if(strcmp(temp.attribute,"d") == 0){
			printf("Directory: %s%s Occupied block addresses: %d\n",myPath,temp.name,temp.firstBlockAddress);
			strcat(myPath,temp.name);
			strcat(myPath,"/");
			traverseDisk(myPath,temp.firstBlockAddress,temp.size);
			int mySize = strlen(myPath);
			mySize -= 2;
			while(myPath[mySize] != '/')
				--mySize;
			myPath[mySize+1] = '\0';
		}
		else{
			printf("File: %s%s Occupied block addresses: ",myPath,temp.name);
			int iteration;
			if(temp.size%blockSize == 0)
				iteration = temp.size/blockSize;
			else
				iteration = temp.size/blockSize + 1;
			int current = temp.firstBlockAddress;
			for (int i = 0; i < iteration; ++i){
				printf("%d ",current);
				if(i < iteration - 1)
					current = fatFile[current];
			}
			printf("\n");

		}
	}
	
}