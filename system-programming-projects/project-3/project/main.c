
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/mman.h>
#include <errno.h>


struct potato{
	int endProcessed;
	int processNum;
	int totalProcessCount;
	int started[100];
	int switchNum[100];
	int totalSwitchCount[100];
	int PID[100];
	int waitsForRead[100];
	int hasPotato[100];
	char fifoName[100][100];
};

struct potato * mySweetPotato;

sem_t * sem;

int shmDes;

int semDes;

char shmName[50];

char semName[50];

char filePath[500];

int totalSwitchCount;

int processNum;

int totalProcessCount;

int rd, wr;

int strToInt(char * str){
	int res = 0;
	int i=0;
	int minus = 0;
	if(str[0] == '-'){
		++i;
		minus = 1;
	}
	while(str[i] != '\0'){
		if(str[i]>='0' && str[i]<='9'){
			res = res*10;
			res = res+(str[i]-'0');
			++i;
		}
		else{
			write(2,"Enter integer as argument\n",26);
			exit(-1);
		}
	}
	if(minus)
		res = -res;
	if(res < 0){
			write(2,"Enter a nonnegative integer\n",28);
			exit(-1);
	}
	return res;
}

void handler(int no){
	if(no == SIGINT){
		int id;
		for (int i = 0; i < mySweetPotato->processNum-1; ++i){
			id = i;
			if(id >= processNum){
				++id;
			}
			kill(mySweetPotato->PID[id],SIGUSR1);
		}
		for (int i = 0; i < totalProcessCount; ++i){
			unlink((char *)&mySweetPotato->fifoName[i]);
		}
		if(semDes)
			close(semDes);
		if(shmDes)
			close(shmDes);
		if(wr)
			close(wr);
		if(rd)
			close(rd);
		sem_destroy(&sem[0]);
		sem_destroy(&sem[1]);
		sem_destroy(&sem[2]);
		sem_destroy(&sem[3]);
		sem_destroy(&sem[4]);
		sem_destroy(&sem[5]);
		shm_unlink(semName);
		shm_unlink(shmName);
		write(1,"\nSIGINT handled...\n",19);
		exit(-1);
	}
	else if(no == SIGUSR1){
		if(semDes)
			close(semDes);
		if(shmDes)
			close(shmDes);
		if(wr)
			close(wr);
		if(rd)
			close(rd);
		write(1,"SIGINT handled...\n",19);
		exit(-1);
	}
}

int main(int argc, char *argv[]){
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigaction(SIGINT,  &act, 0);
	sigaction(SIGUSR1, &act, 0);

	srand(time(NULL));

	int fd;
	int opt;
	int bCheck,sCheck,fCheck,mCheck;
	bCheck = 0; sCheck = 0; fCheck = 0; mCheck = 0;
	for(int i=0; i<4; ++i){
		if((opt = getopt(argc,argv,"b:s:f:m:")) == -1){
			write(2,"There are missed arguments\n",27);
			exit(-1);
		}
		switch(opt){
			case 'b':
			if(!bCheck){
				totalSwitchCount = strToInt(optarg);
				bCheck = 1;
			}
			else{
				write(2,"More than one input from the same option\n",41);
				exit(-1);
			}
			break;
			case 's':
			if(!sCheck){
				strcpy(shmName,optarg);
				sCheck = 1;
			}
			else{
				write(2,"More than one input from the same option\n",41);
				exit(-1);
			}
			break;
			case 'f':
			if(!fCheck){
				if ((fd = open(optarg,O_RDONLY)) == -1){
					write(2,"There is no file to open in this path\n",38);
					exit(-1);
				}
				fCheck = 1;
			}
			else{
				write(2,"More than one input from the same option\n",41);
				exit(-1);
			}
			break;
			case 'm':
			if(!mCheck){
				strcpy(semName,optarg);
				mCheck = 1;
			}
			else{
				write(2,"More than one input from the same option\n",41);
				exit(-1);
			}
			break;
			default:
			write(2,"Wrong argument type\n",20);
			exit(-1);
		}
	}
	if((opt = getopt(argc,argv,"")) != -1){
		write(2,"There are extra arguments\n",26);
		exit(-1);
	}

	semDes = 0;
	shmDes = 0;
	wr = 0;
	rd = 0;


	if((semDes = shm_open(semName,O_RDWR,00666)) == -1){
		semDes = shm_open(semName,O_RDWR|O_CREAT,00666);
		ftruncate(semDes,6*sizeof(sem_t));
		sem = (sem_t *) mmap(0,6*sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,semDes,0);
		sem_init(&sem[0],1,1);
		sem_init(&sem[1],1,0);
		sem_init(&sem[2],1,1);
		sem_init(&sem[3],1,1);
		sem_init(&sem[4],1,1);
		sem_init(&sem[5],1,0);
	}
	else{
		sem = (sem_t *) mmap(0,6*sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED,semDes,0);
	}
	
	sem_wait(&sem[0]);
	if((shmDes = shm_open(shmName,O_RDWR,00666)) == -1){
		shmDes = shm_open(shmName,O_RDWR|O_CREAT,00666);
		ftruncate(shmDes,sizeof(struct potato));
		mySweetPotato = (struct potato *) mmap(0,sizeof(struct potato),PROT_READ|PROT_WRITE,MAP_SHARED,shmDes,0);



		char cur[2];
		cur[1] = '\0';
		char temp[50];
		int count = 0;
		while(read(fd,cur,1)){
			strcpy(temp,cur);
			while(read(fd,cur,1)){
				if(cur[0] == '\n'){
					break;
				}
				strcat(temp,cur);
			}
			strcpy(mySweetPotato->fifoName[count],temp);
			++count;
		}
		close(fd);

		mySweetPotato->totalProcessCount = count;
		totalProcessCount = mySweetPotato->totalProcessCount;

		mySweetPotato->processNum = 0;
		processNum = mySweetPotato->processNum++;

		for (int i = 0; i < totalProcessCount; ++i){
			if(mkfifo(mySweetPotato->fifoName[i],0666) == -1){
				if(errno != EEXIST){
					write(2,"Something is wrong\n",19);
					exit(-1);
				}
				else{
					unlink(mySweetPotato->fifoName[i]);
					if(mkfifo(mySweetPotato->fifoName[i],0666) == -1){
						write(2,"Something is wrong\n",19);
						exit(-1);
					}
				}
			}
		}

		if(totalSwitchCount > 0){
			mySweetPotato->hasPotato[processNum] = 1;
		}
		else{
			mySweetPotato->hasPotato[processNum] = 0;
		}
		mySweetPotato->totalSwitchCount[processNum] = totalSwitchCount;
		mySweetPotato->switchNum[processNum] = 0;
		mySweetPotato->PID[processNum] = getpid();
		mySweetPotato->endProcessed = 0;

		mySweetPotato->started[processNum] = 0;

		for (int i = 0; i < totalProcessCount; ++i){
			mySweetPotato->waitsForRead[i] = 0;
		}
	}
	else{
		mySweetPotato = (struct potato *) mmap(0,sizeof(struct potato),PROT_READ|PROT_WRITE,MAP_SHARED,shmDes,0);

		close(fd);

		totalProcessCount = mySweetPotato->totalProcessCount;

		processNum = mySweetPotato->processNum++;

		if(totalSwitchCount > 0){
			mySweetPotato->hasPotato[processNum] = 1;
		}
		else{
			mySweetPotato->hasPotato[processNum] = 0;
		}
		mySweetPotato->totalSwitchCount[processNum] = totalSwitchCount;
		mySweetPotato->switchNum[processNum] = 0;
		mySweetPotato->PID[processNum] = getpid();
		mySweetPotato->endProcessed = 0;	

		mySweetPotato->started[processNum] = 0;

		for (int i = 0; i < totalProcessCount; ++i){
			mySweetPotato->waitsForRead[i] = 0;
		}
	}
	sem_post(&sem[0]);
	char junk;
	if(processNum == totalProcessCount-1){
		for (int i = 0; i < totalProcessCount-1; ++i){
			sem_wait(&sem[5]);
			sem_wait(&sem[4]);
			int id;
			for (int j = 0; j < totalProcessCount-1; ++j){
				if(mySweetPotato->started[j] == 1){
					id = j;
					mySweetPotato->started[j] = 0;
					break;
				}
			}
			sem_post(&sem[4]);
			while((wr = open(mySweetPotato->fifoName[id],O_WRONLY)) == -1 && (errno == EINTR));
			write(wr,&junk,sizeof(char));
			close(wr);
			wr = 0;
		}
	}
	else{
		sem_wait(&sem[4]);
		++mySweetPotato->started[processNum];
		sem_post(&sem[4]);
		sem_post(&sem[5]);
		while((rd = open(mySweetPotato->fifoName[processNum],O_RDONLY)) == -1 && (errno == EINTR));
		read(rd,&junk,sizeof(char));
		close(rd);
		rd = 0;
	}
	char buffer[250];
	int firstIDpotato[3];
	while(1){
		int hasPotato = 0;
		if(mySweetPotato->hasPotato[processNum]){
			--mySweetPotato->hasPotato[processNum];
			hasPotato = 1;
			firstIDpotato[0] = processNum;
			firstIDpotato[2] = getpid();
		}
		else{
			sem_wait(&sem[0]);
			++mySweetPotato->waitsForRead[processNum];
			sem_post(&sem[0]);
			sem_post(&sem[1]);
			while((rd = open(mySweetPotato->fifoName[processNum],O_RDONLY)) == -1 && (errno == EINTR));
			read(rd,firstIDpotato,3*sizeof(int));
			close(rd);
			rd = 0;
		}
		if(firstIDpotato[2] > 0){
			if(!hasPotato){
				sprintf(buffer,"pid=%d receiving potato number %d from %s\n", getpid(),firstIDpotato[2],mySweetPotato->fifoName[firstIDpotato[1]]);
				write(1,buffer,strlen(buffer));
			}
			sem_wait(&sem[2]);
			if(mySweetPotato->switchNum[firstIDpotato[0]] < mySweetPotato->totalSwitchCount[firstIDpotato[0]]){
				sem_post(&sem[2]);
				int sendNum;
				sem_wait(&sem[1]);
				sem_wait(&sem[0]);
				int count = 0;
				for (int i = 0; i < totalProcessCount; ++i){
					if (mySweetPotato->waitsForRead[i] == 1){
						++count;
					}
				}
				int rn = (rand()%count)+1;
				count = 0;
				for (int i = 0; i < totalProcessCount; ++i){
					if (mySweetPotato->waitsForRead[i] == 1){
						++count;
						if(count == rn){
							sendNum = i;
							break;
						}
					}
				}
				mySweetPotato->waitsForRead[sendNum] = 0;
				sem_post(&sem[0]);
				sem_wait(&sem[2]);
				sprintf(buffer,"pid=%d sending potato number %d to %s; this is switch number %d\n", getpid(),firstIDpotato[2],mySweetPotato->fifoName[sendNum],++mySweetPotato->switchNum[firstIDpotato[0]]);
				sem_post(&sem[2]);
				write(1,buffer,strlen(buffer));
				firstIDpotato[1] = processNum;
				while((wr = open(mySweetPotato->fifoName[sendNum],O_WRONLY)) == -1 && (errno == EINTR));
				write(wr,firstIDpotato,3*sizeof(int));
				close(wr);
				wr = 0;
			}
			else{
				sem_post(&sem[2]);
				sprintf(buffer,"pid=%d; potato number %d has cooled down.\n",getpid(),firstIDpotato[2]);
				write(1,buffer,strlen(buffer));
				int end = 1;
				sem_wait(&sem[2]);
				for (int i = 0; i < totalProcessCount; ++i){
					if (mySweetPotato->switchNum[i] < mySweetPotato->totalSwitchCount[i]){
						end = 0;
						break;
					}
				}
				sem_post(&sem[2]);
				sem_wait(&sem[3]);
				if(end && mySweetPotato->endProcessed++ == 0){
					sem_post(&sem[3]);
					firstIDpotato[2] = -1;
					int sendNum;
					for (int i = 0; i < totalProcessCount-1; ++i){
						sem_wait(&sem[1]);
						sem_wait(&sem[0]);

						for (int j = 0; j < totalProcessCount; ++j){
							if (mySweetPotato->waitsForRead[j] == 1){
								sendNum = j;
								mySweetPotato->waitsForRead[j] = 0;
								break;
							}
						}
						
						sem_post(&sem[0]);
						while((wr = open(mySweetPotato->fifoName[sendNum],O_WRONLY)) == -1 && (errno == EINTR));
						write(wr,firstIDpotato,3*sizeof(int));
						close(wr);
						wr = 0;
					}
					for (int i = 0; i < totalProcessCount; ++i){
						unlink((char *)&mySweetPotato->fifoName[i]);
					}
					close(semDes);
					close(shmDes);
					sem_destroy(&sem[0]);
					sem_destroy(&sem[1]);
					sem_destroy(&sem[2]);
					sem_destroy(&sem[3]);
					sem_destroy(&sem[4]);
					sem_destroy(&sem[5]);
					shm_unlink(semName);
					shm_unlink(shmName);
					break;
				}
				else sem_post(&sem[3]);
			}
		}
		else{
			close(semDes);
			close(shmDes);
			break;
		}
	}
	return 0;
}