#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/mman.h>

#define MAX_NURSE_NUM 100
#define MAX_VACCINATOR_NUM 100
#define MAX_CITIZEN_NUM 100

struct clinic{
	int cursor;
	int totalProcessCount;
	int vaccine1;
	int vaccine2;
	int totalVaccinationCount;
	int remainingCitizens;
	int nursesHandled;

	int vaccinationCount[MAX_VACCINATOR_NUM];
	int citizenVacCount[MAX_CITIZEN_NUM];
	
	int nursePID[MAX_NURSE_NUM];
	int vaccinatorPID[MAX_VACCINATOR_NUM];
	int citizenPID[MAX_CITIZEN_NUM];
	
};

int fd;

int shmDes;

struct clinic * myClinic;

int n,v,c,b,t;

int processNum;

int nurse, vaccinator, citizen;

int nurseNum, vaccinatorNum, citizenNum;

char path[200];

sem_t *buffer, *vac1, *vac2, *curMutex, *vacMutex, *injMutex, *opMutex;

char * semNames[7] = {"buffer","vac1","vac2","curMutex","vacMutex","injMutex","opMutex"};

char * shmName = "SHM_161044083";

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
			write(2,"Please enter integer as argument\n",33);
			exit(-1);
		}
	}
	if(minus)
		res = -res;
	return res;
}

void sighandler(int signo){
	if(signo == SIGINT){
		if(nurseNum == 1){
			for (int i = 0; i < myClinic->totalProcessCount-1; ++i){
				wait(0);
			}
			if(fd)
				close(fd);
			sem_close(buffer);
			sem_close(vac1);
			sem_close(vac2);
			sem_close(curMutex);
			sem_close(vacMutex);
			sem_close(injMutex);
			sem_close(opMutex);
			sem_unlink(semNames[0]);
			sem_unlink(semNames[1]);
			sem_unlink(semNames[2]);
			sem_unlink(semNames[3]);
			sem_unlink(semNames[4]);
			sem_unlink(semNames[5]);
			sem_unlink(semNames[6]);
			shm_unlink(shmName);
			write(1,"\nSIGINT handled...\n",19);
			exit(-1);
		}
		else{
			if(nurse){
				if(fd)
					close(fd);
			}
			exit(-1);
		}
	}
}

int main(int argc, char *argv[]){
	sigset_t blockMask;
	sigemptyset(&blockMask);
	sigaddset(&blockMask,SIGUSR1);
	sigaddset(&blockMask,SIGUSR2);
	sigaddset(&blockMask,SIGCHLD);
	sigprocmask(SIG_BLOCK,&blockMask,0);

	sigset_t sigUsr1Mask;
	sigfillset(&sigUsr1Mask);
	sigdelset(&sigUsr1Mask,SIGUSR1);
	sigdelset(&sigUsr1Mask,SIGINT);

	sigset_t sigUsr2Mask;
	sigfillset(&sigUsr2Mask);
	sigdelset(&sigUsr2Mask,SIGUSR2);
	sigdelset(&sigUsr2Mask,SIGINT);

	sigset_t sigChldMask;
	sigfillset(&sigChldMask);
	sigdelset(&sigChldMask,SIGCHLD);
	sigdelset(&sigChldMask,SIGINT);

	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = sighandler;
	sigaction(SIGINT,  &act, 0);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	sigaction(SIGCHLD, &act, 0);

	srand(time(NULL));

	int fCheck;
	int opt;
	int nCheck,vCheck,cCheck,bCheck,tCheck,iCheck;
	nCheck = 0; vCheck = 0; cCheck = 0; bCheck = 0; tCheck = 0; iCheck = 0;
	for(int i=0; i<6; ++i){
		if((opt = getopt(argc,argv,"n:v:c:b:t:i:")) == -1){
			write(2,"There are missed arguments\n",27);
			exit(-1);
		}
		switch(opt){
			case 'n':
				if(!nCheck){
					n = strToInt(optarg);
					if(n < 2){
						write(2,"Please enter a required number for the nurses\n",46);
						exit(-1);
					}
					nCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'v':
				if(!vCheck){
					v = strToInt(optarg);
					if(v < 2){
						write(2,"Please enter a required number for the vaccinators\n",51);
						exit(-1);
					}
					vCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'c':
				if(!cCheck){
					c = strToInt(optarg);
					if(c < 3){
						write(2,"Please enter a required number for the citizens\n",48);
						exit(-1);
					}
					cCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'b':
				if(!bCheck){
					b = strToInt(optarg);
					bCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 't':
				if(!tCheck){
					t = strToInt(optarg);
					if(t < 1){
						write(2,"Please enter a required number for the two shots count\n",55);
						exit(-1);
					}
					tCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'i':
				if(!iCheck){
					if ((fCheck = open(optarg,O_RDONLY)) == -1){
						write(2,"There is no file to open in this path\n",38);
						exit(-1);
					}
					strcpy(path,optarg);
					close(fCheck);
					fCheck = 0;
					iCheck = 1;
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
	if(b < t*c + 1){
		write(2,"Please enter a required number for the buffer size\n",51);
		exit(-1);
	}
	shmDes = shm_open(shmName,O_RDWR|O_CREAT,00666);
	ftruncate(shmDes,sizeof(struct clinic));
	myClinic = (struct clinic *) mmap(0,sizeof(struct clinic),PROT_READ|PROT_WRITE,MAP_SHARED,shmDes,0);

	buffer = sem_open(semNames[0], O_CREAT | O_EXCL, 0644, b);
	vac1 = sem_open(semNames[1], O_CREAT | O_EXCL, 0644, 0);
	vac2 = sem_open(semNames[2], O_CREAT | O_EXCL, 0644, 0);
	curMutex = sem_open(semNames[3], O_CREAT | O_EXCL, 0644, 1);
	vacMutex = sem_open(semNames[4], O_CREAT | O_EXCL, 0644, 1);
	injMutex = sem_open(semNames[5], O_CREAT | O_EXCL, 0644, 1);
	opMutex = sem_open(semNames[6], O_CREAT | O_EXCL, 0644, 1);

	fd = 0;

	nurse = 0; vaccinator = 0; citizen = 0;

	nurseNum = -1; vaccinatorNum = -1; citizenNum = -1;

	processNum = -1;

	myClinic->cursor = 0;
	myClinic->totalProcessCount = 1;

	myClinic->vaccine1 = 0;
	myClinic->vaccine2 = 0;

	myClinic->totalVaccinationCount = 0;
	myClinic->remainingCitizens = c;
	myClinic->nursesHandled = 0;

	for (int i = 0; i < v; ++i){
		myClinic->vaccinationCount[i] = 0;
	}
	for (int i = 0; i < c; ++i){
		myClinic->citizenVacCount[i] = 0;
	}
	
	for (int i = 0; i < n+v+c-1; ++i){
		if(i > 0)
			sigsuspend(&sigUsr1Mask);
		if(fork()){
			if(i == n+v+c-2){
				processNum = 0;
				myClinic->nursePID[0] = getpid();
				nurse = 1;
				nurseNum = 1;
			}
		}
		else{
			processNum = i+1;
			++myClinic->totalProcessCount;
			if(i < n+v+c-2)
				kill(getppid(),SIGUSR1);
			if(i < n-1){
				myClinic->nursePID[i+1] = getpid();
				nurse = 1;
				nurseNum = i+2;
			}
			else if(i < n+v-1){
				myClinic->vaccinatorPID[i-(n-1)] = getpid();
				vaccinator = 1;
				vaccinatorNum = i-(n-2);
			}
			else{
				myClinic->citizenPID[i-(n+v-1)] = getpid();
				citizen = 1;
				citizenNum = i-(n+v-2);
			}
			break;
		}
	}

	char buf[200];
	if(nurseNum == 1){
		sprintf(buf,"Welcome to the GTU344 clinic. Number of citizens to vaccinate c=%d with t=%d doses.\n",c,t);
		write(1,buf,strlen(buf));
		for (int i = 0; i < n+v+c-1; ++i){
			if(i < n-1){
				kill(myClinic->nursePID[i+1],SIGUSR1);
				sigsuspend(&sigUsr1Mask);
			}
			else if(i < n+v-1){
				kill(myClinic->vaccinatorPID[i-(n-1)],SIGUSR1);
				sigsuspend(&sigUsr1Mask);
			}
			else{
				kill(myClinic->citizenPID[i-(n+v-1)],SIGUSR1);
				sigsuspend(&sigUsr1Mask);
			}
		}
		for (int i = 0; i < n+v+c-1; ++i){
			if(i < n-1){
				kill(myClinic->nursePID[i+1],SIGUSR1);
			}
			else if(i < n+v-1){
				kill(myClinic->vaccinatorPID[i-(n-1)],SIGUSR1);
			}
			else{
				kill(myClinic->citizenPID[i-(n+v-1)],SIGUSR1);
			}
		}
	}
	else{
		sigsuspend(&sigUsr1Mask);
		kill(myClinic->nursePID[0],SIGUSR1);
		sigsuspend(&sigUsr1Mask);
	}
	if(nurse){
		fd = open(path,O_RDONLY);
		char cur[2];
		cur[1] = '\0';
		int set;
		sem_wait(curMutex);
		while((set = myClinic->cursor++) < 2*t*c){
			lseek(fd,set,SEEK_SET);
			read(fd,cur,1);
			if(cur[0] == '1'){
				sem_wait(buffer);
				sem_wait(vacMutex);
				sprintf(buf,"Nurse %d (pid=%d) has brought vaccine 1: the myClinic has %d vaccine1 and %d vaccine2.\n",nurseNum,getpid(),++myClinic->vaccine1,myClinic->vaccine2);
				write(1,buf,strlen(buf));
				sem_post(vacMutex);
				sem_post(vac1);
			}
			else{
				sem_wait(buffer);
				sem_wait(vacMutex);
				sprintf(buf,"Nurse %d (pid=%d) has brought vaccine 2: the myClinic has %d vaccine1 and %d vaccine2.\n",nurseNum,getpid(),myClinic->vaccine1,++myClinic->vaccine2);
				write(1,buf,strlen(buf));
				sem_post(vacMutex);
				sem_post(vac2);
			}
			sem_post(curMutex);
			sem_wait(curMutex);
		}
		if(++myClinic->nursesHandled == n){
			sprintf(buf,"Nurses have carried all vaccines to the buffer, terminating.\n");
			write(1,buf,strlen(buf));
		}
		sem_post(curMutex);
		close(fd);
		fd = 0;
	}
	else if(vaccinator){
		sem_wait(injMutex);
		while(myClinic->totalVaccinationCount++ < t*c){
			sem_wait(vac1);
			sem_wait(vac2);
			sem_wait(opMutex);
			int cNew = c;
			for (int i = 0; i < c; ++i){
				if(myClinic->citizenVacCount[i] == 0){
					cNew = i+1;
					break;
				}
			}
			int count = 0;
			for (int i = 0; i < cNew; ++i){
				if(myClinic->citizenVacCount[i] < t)
					++count;
			}
			int pick = rand()%count;
			count = 0;
			for (int i = 0; i < c; ++i){
				if(myClinic->citizenVacCount[i] < t){
					if (count < pick){
						++count;
					}
					else{
						pick = i;
						break;
					}	
				}
			}
			++myClinic->citizenVacCount[pick];
			++myClinic->vaccinationCount[vaccinatorNum-1];
			sprintf(buf,"Vaccinator %d (pid=%d) is inviting citizen pid=%d to the clinic.\n",vaccinatorNum,getpid(),myClinic->citizenPID[pick]);
			write(1,buf,strlen(buf));
			kill(myClinic->citizenPID[pick],SIGUSR2);
			sem_post(injMutex);
			sem_wait(injMutex);
		}
		sem_post(injMutex);
	}
	else{
		char myBuf[400];
		for (int i = 0; i < t; ++i){
			sigsuspend(&sigUsr2Mask);
			sem_wait(vacMutex);
			myBuf[0] = '\0';
			sprintf(buf,"Citizen %d (pid=%d) is vaccinated for the %d",citizenNum,getpid(),i+1);
			strcat(myBuf,buf);
			if(i+1 == 11 || i+1 == 12 || i+1 == 13)
				strcat(myBuf,"th");
			else if((i+1)%10 == 1)
				strcat(myBuf,"st");
			else if((i+1)%10 == 2)
				strcat(myBuf,"nd");
			else if((i+1)%10 == 3)
				strcat(myBuf,"rd");
			else
				strcat(myBuf,"th");
			sprintf(buf," time: the clinic has %d vaccine1 and %d vaccine2.",--myClinic->vaccine1,--myClinic->vaccine2);
			strcat(myBuf,buf);
			if(i == t-1){
				sprintf(buf," The citizen is leaving. Remaining citizens to vaccinate: %d\n",--myClinic->remainingCitizens);
				strcat(myBuf,buf);
			}
			else{
				strcat(myBuf,"\n");
			}
			write(1,myBuf,strlen(myBuf));
			sem_post(vacMutex);
			sem_post(opMutex);
			sem_post(buffer);
			sem_post(buffer);
		}
	}
	if(nurseNum == 1){	
		for (int i = 0; i < n+v+c-1; ++i){
			if(i < n-1){
				kill(myClinic->nursePID[i+1],SIGUSR1);
				sigsuspend(&sigChldMask);
			}
			else if(i < n+v-1){
				kill(myClinic->vaccinatorPID[i-(n-1)],SIGUSR1);
				sigsuspend(&sigChldMask);
			}
			else{
				kill(myClinic->citizenPID[i-(n+v-1)],SIGUSR1);
				sigsuspend(&sigChldMask);
			}
		}
		sprintf(buf,"All citizens have been vaccinated.\n");
		write(1,buf,strlen(buf));
		char myBuf[200*(v+1)];
		myBuf[0] = '\0';
		for (int i = 0; i < v; ++i){		
			sprintf(buf,"Vaccinator %d (pid=%d) vaccinated %d doses. ",i+1,myClinic->vaccinatorPID[i],myClinic->vaccinationCount[i]);
			strcat(myBuf,buf);
		}
		sprintf(buf,"The clinic is now closed. Stay healthy.\n");
		strcat(myBuf,buf);
		write(1,myBuf,strlen(myBuf));
		sem_close(buffer);
		sem_close(vac1);
		sem_close(vac2);
		sem_close(curMutex);
		sem_close(vacMutex);
		sem_close(injMutex);
		sem_close(opMutex);
		sem_unlink(semNames[0]);
		sem_unlink(semNames[1]);
		sem_unlink(semNames[2]);
		sem_unlink(semNames[3]);
		sem_unlink(semNames[4]);
		sem_unlink(semNames[5]);
		sem_unlink(semNames[6]);
		shm_unlink(shmName);
	}
	else{
		sigsuspend(&sigUsr1Mask);
	}
	return 0;
}