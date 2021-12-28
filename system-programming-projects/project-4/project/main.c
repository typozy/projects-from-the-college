#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

struct student{
	char name[50];
	int speed;
	int cost;
	int quality;
	int hwSolved;
	int moneyMade;
};

struct student * solverList;

int mainPipe[2];
int cheaterPipe[2];
int ** solverPipe;

int hwDes;
int stdDes;
int totalMoney;
int solverCount;
int threadIterator;

int * available;

pthread_t cheaterThread;
pthread_t * solverThread;
sem_t availableMutex,moneyMutex,threadMutex,solverAvailable;

void * cheaterFunction(void * arg);

void * solverFunction(void * arg);

int strToInt(char * str);

void sighandler(int signo){
	write(1,"\nTermination signal received, closing.\n",39);
	write(1,"Homeworks solved and money made by the students:\n",49);
	char buf[200];
	for (int i = 0; i < solverCount; ++i){
		sprintf(buf,"%s %d %d\n",solverList[i].name,solverList[i].hwSolved,solverList[i].moneyMade);
		write(1,buf,strlen(buf));
	}
	pthread_detach(cheaterThread);
	for (int i = 0; i < solverCount; ++i){
		pthread_detach(solverThread[i]);
	}
	close(mainPipe[1]);
	close(mainPipe[0]);
	close(cheaterPipe[1]);
	close(cheaterPipe[0]);
	for (int i = 0; i < solverCount; ++i){
		close(solverPipe[i][1]);
		close(solverPipe[i][0]);
	}
	close(hwDes);
	close(stdDes);
	sem_destroy(&solverAvailable);
	sem_destroy(&availableMutex);
	sem_destroy(&moneyMutex);
	sem_destroy(&threadMutex);
	free(available);
	free(solverThread);
	for (int i = 0; i < solverCount; ++i){
		free(solverPipe[i]);
	}
	free(solverPipe);
	exit(-1);
}

int main(int argc, char *argv[]){
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = sighandler;
	sigaction(SIGINT,  &act, 0);
	if(argc != 4){
		write(2,"There are missed or more than required arguments.\n",50);
		exit(-1);
	}
	else if((hwDes = open(argv[1],O_RDONLY)) == -1){
		write(2,"HW file path could not open\n",28);
		exit(-1);
	}
	else if((stdDes = open(argv[2],O_RDONLY)) == -1){
		write(2,"HW file path could not open\n",28);
		exit(-1);
	}
	else if((totalMoney = strToInt(argv[3])) < 0){
		write(2,"Please enter a positive integer as money amount\n",48);
		exit(-1);
	}
	char cur[2];
	cur[1] = '\0';
	while(read(stdDes,cur,1)){
		if(cur[0] == '\n')
			++solverCount;
	}
	solverList = (struct student *)malloc(sizeof(struct student)*solverCount);
	available = (int *)malloc(sizeof(int)*solverCount);
	for (int i = 0; i < solverCount; ++i){
		available[i] = 1;
	}
	lseek(stdDes,0,SEEK_SET);
	char temp[50];
	for (int i = 0; i < solverCount; ++i){
		temp[0] = '\0';
		read(stdDes,cur,1);
		while(cur[0] != ' '){
			strcat(temp,cur);
			read(stdDes,cur,1);
		}
		strcpy(solverList[i].name,temp);
		temp[0] = '\0';
		read(stdDes,cur,1);
		while(cur[0] != ' '){
			strcat(temp,cur);
			read(stdDes,cur,1);
		}
		solverList[i].quality = strToInt(temp);
		temp[0] = '\0';
		read(stdDes,cur,1);
		while(cur[0] != ' '){
			strcat(temp,cur);
			read(stdDes,cur,1);
		}
		solverList[i].speed = strToInt(temp);
		temp[0] = '\0';
		read(stdDes,cur,1);
		while(cur[0] != '\n'){
			strcat(temp,cur);
			read(stdDes,cur,1);
		}
		solverList[i].cost = strToInt(temp);
		solverList[i].hwSolved = 0;
		solverList[i].moneyMade = 0;
	}
	sem_init(&threadMutex,0,1);
	sem_init(&moneyMutex,0,1);
	sem_init(&availableMutex,0,1);
	sem_init(&solverAvailable,0,0);
	pipe(mainPipe);
	pipe(cheaterPipe);
	solverPipe = (int **)malloc(sizeof(int*)*solverCount);
	for (int i = 0; i < solverCount; ++i){
		solverPipe[i] = (int*)malloc(sizeof(int)*2);
	}
	for (int i = 0; i < solverCount; ++i){
		pipe(solverPipe[i]);
	}
	char buf[200];
	sprintf(buf,"%d students-for-hire threads have been created.\n",solverCount);
	write(1,buf,strlen(buf));
	write(1,"Name Q S C\n",11);
	for (int i = 0; i < solverCount; ++i){
		sprintf(buf,"%s %d %d %d\n",solverList[i].name,solverList[i].quality,solverList[i].speed,solverList[i].cost);
		write(1,buf,strlen(buf));
	}
	pthread_create(&cheaterThread,0,cheaterFunction,0);
	solverThread = (pthread_t *)malloc(sizeof(pthread_t)*sizeof(solverCount));
	for (int i = 0; i < solverCount; ++i){
		pthread_create(&solverThread[i],0,solverFunction,0);
	}
	int totalAmount = totalMoney;
	int end;
	char now;
	while(1){
		read(mainPipe[0],&now,1);
		if(now == 'C' || now == 'Q' || now == 'S'){
			sem_wait(&solverAvailable);
			sem_wait(&availableMutex);
			int availableIndex[solverCount];
			int availableSize = 0;
			for (int i = 0; i < solverCount; ++i){
				if(available[i]){
					availableIndex[availableSize] = i;
					++availableSize;
				}
			}
			int bestIndex;
			int bestOption;
			if(now == 'C'){
				bestIndex = availableIndex[0];
				bestOption = solverList[availableIndex[0]].cost;
				for (int i = 1; i < availableSize; ++i){
					if(solverList[availableIndex[i]].cost < bestOption){
						bestIndex = availableIndex[i];
						bestOption = solverList[availableIndex[i]].cost;
					}
				}
			}
			else if (now == 'Q'){
				bestIndex = availableIndex[0];
				bestOption  = solverList[availableIndex[0]].quality;
				for (int i = 1; i < availableSize; ++i){
					if(solverList[availableIndex[i]].quality > bestOption){
						bestIndex = availableIndex[i];
						bestOption = solverList[availableIndex[i]].quality;
					}
				}
			}
			else{
				bestIndex = availableIndex[0];
				bestOption = solverList[availableIndex[0]].speed;
				for (int i = 1; i < availableSize; ++i){
					if(solverList[availableIndex[i]].speed > bestOption){
						bestIndex = availableIndex[i];
						bestOption = solverList[availableIndex[i]].speed;
					}
				}
			}
			if(solverList[bestIndex].cost > totalAmount){
				sem_post(&availableMutex);
				write(1,"Money is over, closing.\n",24);
				end = 0;
				write(cheaterPipe[1],&end,sizeof(int));
				now = 'E';
				for (int i = 0; i < solverCount; ++i){
					write(solverPipe[i][1],&now,1);
				}
				break;
			}
			else{
				--available[bestIndex];
				sem_post(&availableMutex);
				totalAmount = totalAmount - solverList[bestIndex].cost;
				write(solverPipe[bestIndex][1],&now,1);
			}
		}
		else{
			write(1,"No more homeworks left or coming in, closing.\n",46);
			end = 1;
			write(cheaterPipe[1],&end,sizeof(int));
			for (int i = 0; i < solverCount; ++i){
				write(solverPipe[i][1],&now,1);
			}
			break;
		}
	}
	pthread_join(cheaterThread,0);
	for (int i = 0; i < solverCount; ++i){
		pthread_join(solverThread[i],0);
	}
	write(1,"Homeworks solved and money made by the students:\n",49);
	for (int i = 0; i < solverCount; ++i){
		sprintf(buf,"%s %d %d\n",solverList[i].name,solverList[i].hwSolved,solverList[i].moneyMade);
		write(1,buf,strlen(buf));
	}
	close(mainPipe[1]);
	close(mainPipe[0]);
	close(cheaterPipe[1]);
	close(cheaterPipe[0]);
	for (int i = 0; i < solverCount; ++i){
		close(solverPipe[i][1]);
		close(solverPipe[i][0]);
	}
	close(hwDes);
	close(stdDes);
	sem_destroy(&solverAvailable);
	sem_destroy(&availableMutex);
	sem_destroy(&moneyMutex);
	sem_destroy(&threadMutex);
	free(available);
	free(solverThread);
	for (int i = 0; i < solverCount; ++i){
		free(solverPipe[i]);
	}
	free(solverPipe);
	return 0;
}

int strToInt(char * str){
	int res = 0;
	int i=0;
	int minus = 0;
	if(str[0] == '-'){
		++i;
		minus = 1;
	}
	while(str[i] != '\0'){
		if(str[i] >= '0' && str[i] <= '9'){
			res = res*10;
			res = res+(str[i]-'0');
			++i;
		}
		else{
			write(2,"Please enter integer as argument\n",33);
			exit(-1);
		}
	}
	if(minus)
		res = -res;
	return res;
}

void * cheaterFunction(void * arg){
	char now;
	int end;
	char buf[200];
	while(read(hwDes,&now,1)){
		if(now == 'C' || now == 'Q' || now == 'S'){
			sem_wait(&moneyMutex);
			sprintf(buf,"H has a new homework %c; remaining money is %dTL\n",now,totalMoney);
			write(1,buf,strlen(buf));
			sem_post(&moneyMutex);
			write(mainPipe[1],&now,1);
		}
		else break;
	}
	now = 'E';
	write(mainPipe[1],&now,1);
	read(cheaterPipe[0],&end,sizeof(int));
	if(end){
		write(1,"H has no other homeworks, terminating.\n",39);
	}
	else{
		write(1,"H has no more money for homeworks, terminating.\n",48);
	}
	return 0;
}

void * solverFunction(void * arg){
	int threadNum;
	sem_wait(&threadMutex);
	threadNum = threadIterator;
	++threadIterator;
	sem_post(&threadMutex);
	char buf[200];
	char now;
	while(1){
		sprintf(buf,"%s is waiting for a homework\n",solverList[threadNum].name);
		write(1,buf,strlen(buf));
		sem_post(&solverAvailable);
		read(solverPipe[threadNum][0],&now,1);
		if(now == 'C' || now == 'Q' || now == 'S'){
			sem_wait(&moneyMutex);
			totalMoney = totalMoney - solverList[threadNum].cost;
			sprintf(buf,"%s is solving homework %c for %d, H has %dTL left.\n",solverList[threadNum].name,now,solverList[threadNum].cost,totalMoney);
			write(1,buf,strlen(buf));
			sem_post(&moneyMutex);
			solverList[threadNum].moneyMade = solverList[threadNum].moneyMade + solverList[threadNum].cost;
			sleep(6-solverList[threadNum].speed);
			sem_wait(&availableMutex);
			++available[threadNum];
			sem_post(&availableMutex);
			++solverList[threadNum].hwSolved;
		}
		else break;
	}
	return 0;
}