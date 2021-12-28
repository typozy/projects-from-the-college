#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>

int fd = 0;

int childFd[8] = {0,0,0,0,0,0,0,0};

char path[2000];

int parent = 0;

int count8lines = 0;

int countChar = 0;

int parentID;

int childID[8];

int childNum;

void isParent();

void isChild();

void lagrangeSix(double * x, double * y, double * c);

void lagrangeSeven(double * x, double * y, double * c);

double power(double number, int exp){
	double result = 1.0;
	for (int i = 0; i < exp; ++i){
		result *= number;
	}
	return result;
}

void sighandler(int signo){
	if(signo == SIGINT){
		if(parent){
			for (int i = 0; i < 8; ++i){
				wait(0);
			}
			if(fd)
				close(fd);
			write(1,"\nSIGINT handled...\n",19);
			exit(-1);
		}
		else{
			if(childFd[childNum])
				close(childFd[childNum]);
			exit(-1);
		}
	}
}

int main(int argc, char * argv[]){
	sigset_t blockMask;
	sigemptyset(&blockMask);
	sigaddset(&blockMask,SIGUSR1);
	sigaddset(&blockMask,SIGUSR2);
	sigaddset(&blockMask,SIGCHLD);
	sigprocmask(SIG_BLOCK,&blockMask,0);

	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = sighandler;
	sigaction(SIGINT,  &act, 0);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	sigaction(SIGCHLD, &act, 0);

	if(argc < 2){
		write(2,"Please enter the path of the input file\n",40);
		exit(-1);
	}
	else if(argc > 2){
		write(2,"Please enter the path truly\n",28);
		exit(-1);
	}
	else if((fd = open(argv[1],O_RDWR)) == -1){
		write(2,"The file that you declared its path does not open\n",50);
		exit(-1);
	}
	char temp[2];
	temp[1] = '\0';
	while(read(fd,temp,1)){
		++countChar;
		if(strcmp(temp,"\n") == 0)
			++count8lines;
	}
	count8lines /= 8;
	close(fd);
	fd = 0;
	strcpy(path,argv[1]);
	parentID = getpid();
	for (int i = 0; i < 8; ++i){
		int m = fork();
		if(m){
			childID[i] = m;
			if(i == 7)
				parent = 1;
		}
		else{
			childNum = i;
			break;
		}
	}
	if(parent){
		isParent();
	}
	else{
		isChild();
	}
	return 0;
}

void isParent(){
	srand(time(NULL));
	sigset_t sigMask;
	sigemptyset(&sigMask);
	fd = open(path,O_RDWR);
	int ifChosen[8];
	for (int j = 0; j < count8lines; ++j){
		for (int i = 0; i < 8; ++i)
			ifChosen[i] = 0;
		for (int i = 0; i < 8; ++i){
			int tryVal = rand()%8;
			while(ifChosen[tryVal])
				tryVal = rand()%8;
			ifChosen[tryVal] = 1;
			kill(childID[tryVal],SIGUSR1);
			sigsuspend(&sigMask);
		}

		flock(fd,LOCK_EX);
		lseek(fd,0,SEEK_SET);
		char temp[2];
		temp[0] = '\0';
		int k = 0;
		while(k < j*8){
			read(fd,temp,1);
			if(strcmp(temp,"\n") == 0)
				++k;
		}
		char dbl[50];
		double average = 0.0;
		for (int i = 0; i < 8; ++i){
			int j = 0;
			while(j < 15){
				read(fd,temp,1);
				if(strcmp(temp,",") == 0)
					++j;
			}
			dbl[0] = '\0';
			read(fd,temp,1);
			while(strcmp(temp,",") != 0){
				strcat(dbl,temp);
				read(fd,temp,1);
			}
			double y_7 = atof(dbl);
			dbl[0] = '\0';
			read(fd,temp,1);
			while(strcmp(temp,"\n") != 0 && strcmp(temp,",") != 0){
				strcat(dbl,temp);
				read(fd,temp,1);
			}
			while(strcmp(temp,"\n") != 0){
				read(fd,temp,1);
			}
			double res = atof(dbl);
			double dif = res-y_7;
			if (dif < 0.0)
				average += (-dif);
			else
				average += dif;
		}
		average /= 8.0;
		flock(fd,LOCK_UN);

		for (int i = 0; i < 8; ++i)
			ifChosen[i] = 0;
		for (int i = 0; i < 8; ++i){
			int tryVal = rand()%8;
			while(ifChosen[tryVal])
				tryVal = rand()%8;
			ifChosen[tryVal] = 1;
			kill(childID[tryVal],SIGUSR1);
			sigsuspend(&sigMask);
		}

		char buf[200];
		sprintf(buf,"Error of polynomial of degree 5: %.1f\n",average);
		write(1,buf,strlen(buf));

		for (int i = 0; i < 8; ++i)
			ifChosen[i] = 0;
		for (int i = 0; i < 8; ++i){
			int tryVal = rand()%8;
			while(ifChosen[tryVal])
				tryVal = rand()%8;
			ifChosen[tryVal] = 1;
			kill(childID[tryVal],SIGUSR1);
			sigsuspend(&sigMask);
		}

		flock(fd,LOCK_EX);
		lseek(fd,0,SEEK_SET);
		k = 0;
		while(k < j*8){
			read(fd,temp,1);
			if(strcmp(temp,"\n") == 0)
				++k;
		}
		average = 0.0;
		for (int i = 0; i < 8; ++i){
			int j = 0;
			while(j < 15){
				read(fd,temp,1);
				if(strcmp(temp,",") == 0)
					++j;
			}
			dbl[0] = '\0';
			read(fd,temp,1);
			while(strcmp(temp,",") != 0){
				strcat(dbl,temp);
				read(fd,temp,1);
			}
			double y_7 = atof(dbl);
			read(fd,temp,1);
			while(strcmp(temp,",") != 0){
				read(fd,temp,1);
			}
			dbl[0] = '\0';
			read(fd,temp,1);
			while(strcmp(temp,"\n") != 0 && strcmp(temp,",") != 0){
				strcat(dbl,temp);
				read(fd,temp,1);
			}
			while(strcmp(temp,"\n") != 0){
				read(fd,temp,1);
			}
			double res = atof(dbl);
			double dif = res-y_7;
			if (dif < 0.0)
				average += (-dif);
			else
				average += dif;
		}
		average /= 8.0;
		flock(fd,LOCK_UN);

		sprintf(buf,"Error of polynomial of degree 6: %.1f\n",average);
		write(1,buf,strlen(buf));
	}
	close(fd);

	for (int i = 0; i < 8; ++i)
		ifChosen[i] = 0;
	for (int i = 0; i < 8; ++i){
		int tryVal = rand()%8;
		while(ifChosen[tryVal])
			tryVal = rand()%8;
		ifChosen[tryVal] = 1;
		kill(childID[tryVal],SIGUSR1);
		sigsuspend(&sigMask);
	}
}

void isChild(){
	sigset_t sigMask;
	sigemptyset(&sigMask);
	childFd[childNum] = open(path,O_RDWR);
	char buf[2*countChar];
	for (int j = 0; j < count8lines; ++j){
		flock(childFd[childNum],LOCK_EX);
		lseek(childFd[childNum],0,SEEK_SET);
		char temp[2];
		temp[1] = '\0';
		char dbl[50];
		int i = 0;
		while(i < 8*j+childNum){
			read(childFd[childNum],temp,1);
			if(strcmp(temp,"\n") == 0)
				++i;
		}
		double x[7];
		double y[7];
		double x_7;
		i = 0;
		while(i < 15){
			dbl[0] = '\0';
			read(childFd[childNum],temp,1);
			while(strcmp(temp,",") != 0 && strcmp(temp,"\n") != 0){
				strcat(dbl,temp);
				read(childFd[childNum],temp,1);
			}
			if(i < 14){
				if(i%2 == 0)
					x[i/2] = atof(dbl);
				else
					y[i/2] = atof(dbl);
			}
			else{
				if(i%2 == 0)
					x_7 = atof(dbl);
			}
			++i;
		}
		flock(childFd[childNum],LOCK_UN);

		double r[7];
		lagrangeSix(x,y,r);
		double res = r[5]*power(x_7,5)+r[4]*power(x_7,4)+r[3]*power(x_7,3)+r[2]*power(x_7,2)+r[1]*x_7+r[0];
		sprintf(dbl,",%f\n",res);

		flock(childFd[childNum],LOCK_EX);
		lseek(childFd[childNum],0,SEEK_SET);
		i = 0;
		int count = 0;
		while(i < 8*j+(childNum+1)){
			read(childFd[childNum],temp,1);
			++count;
			if(strcmp(temp,"\n") == 0)
				++i;
		}
		--count;
		buf[0] = '\0';
		while(read(childFd[childNum],temp,1)){
			strcat(buf,temp);
		}
		lseek(childFd[childNum],count,SEEK_SET);
		write(childFd[childNum],dbl,strlen(dbl));
		write(childFd[childNum],buf,strlen(buf));
		flock(childFd[childNum],LOCK_UN);

		sigsuspend(&sigMask);
		kill(parentID,SIGUSR1);

		sigsuspend(&sigMask);
		kill(parentID,SIGUSR1);

		lagrangeSeven(x,y,r);
		res = r[6]*power(x_7,6)+r[5]*power(x_7,5)+r[4]*power(x_7,4)+r[3]*power(x_7,3)+r[2]*power(x_7,2)+r[1]*x_7+r[0];
		sprintf(dbl,",%f\n",res);

		flock(childFd[childNum],LOCK_EX);
		lseek(childFd[childNum],0,SEEK_SET);
		i = 0;
		count = 0;
		while(i < 8*j+(childNum+1)){
			read(childFd[childNum],temp,1);
			++count;
			if(strcmp(temp,"\n") == 0)
				++i;
		}
		--count;
		buf[0] = '\0';
		while(read(childFd[childNum],temp,1)){
			strcat(buf,temp);
		}
		lseek(childFd[childNum],count,SEEK_SET);
		write(childFd[childNum],dbl,strlen(dbl));
		write(childFd[childNum],buf,strlen(buf));
		flock(childFd[childNum],LOCK_UN);

		sigsuspend(&sigMask);
		kill(parentID,SIGUSR1);

		sprintf(buf,"Polynomial %d: %.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",childNum,r[6],r[5],r[4],r[3],r[2],r[1],r[0]);
		write(1,buf,strlen(buf));
	}
	close(childFd[childNum]);

	sigsuspend(&sigMask);
}

void lagrangeSix(double * x, double * y, double * c){

	c[5] = 

	y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])) +

	y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])) +

	y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])) +

	y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])) +

	y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])) +

	y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])) ;

	c[4] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])))*(-1.0)
	*(x[1]+x[2]+x[3]+x[4]+x[5]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])))*(-1.0)
	*(x[0]+x[2]+x[3]+x[4]+x[5]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])))*(-1.0)
	*(x[0]+x[1]+x[3]+x[4]+x[5]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[4]+x[5]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[3]+x[5]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[3]+x[4]) ;

	c[3] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])))
	*(x[1]*x[2]+x[1]*x[3]+x[1]*x[4]+x[1]*x[5]+
		x[2]*x[3]+x[2]*x[4]+x[2]*x[5]+
		x[3]*x[4]+x[3]*x[5]+
		x[4]*x[5]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])))
	*(x[0]*x[2]+x[0]*x[3]+x[0]*x[4]+x[0]*x[5]+
		x[2]*x[3]+x[2]*x[4]+x[2]*x[5]+
		x[3]*x[4]+x[3]*x[5]+
		x[4]*x[5]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])))
	*(x[0]*x[1]+x[0]*x[3]+x[0]*x[4]+x[0]*x[5]+
		x[1]*x[3]+x[1]*x[4]+x[1]*x[5]+
		x[3]*x[4]+x[3]*x[5]+
		x[4]*x[5]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[4]+x[0]*x[5]+
		x[1]*x[2]+x[1]*x[4]+x[1]*x[5]+
		x[2]*x[4]+x[2]*x[5]+
		x[4]*x[5]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[3]+x[0]*x[5]+
		x[1]*x[2]+x[1]*x[3]+x[1]*x[5]+
		x[2]*x[3]+x[2]*x[5]+
		x[3]*x[5]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[3]+x[0]*x[4]+
		x[1]*x[2]+x[1]*x[3]+x[1]*x[4]+
		x[2]*x[3]+x[2]*x[4]+
		x[3]*x[4]) ;

	c[2] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])))*(-1.0)
	*(x[1]*x[2]*x[3]+x[1]*x[2]*x[4]+x[1]*x[2]*x[5]+
		x[1]*x[3]*x[4]+x[1]*x[3]*x[5]+
		x[1]*x[4]*x[5]+
		x[2]*x[3]*x[4]+x[2]*x[3]*x[5]+
		x[2]*x[4]*x[5]+
		x[3]*x[4]*x[5]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])))*(-1.0)
	*(x[0]*x[2]*x[3]+x[0]*x[2]*x[4]+x[0]*x[2]*x[5]+
		x[0]*x[3]*x[4]+x[0]*x[3]*x[5]+
		x[0]*x[4]*x[5]+
		x[2]*x[3]*x[4]+x[2]*x[3]*x[5]+
		x[2]*x[4]*x[5]+
		x[3]*x[4]*x[5]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[3]+x[0]*x[1]*x[4]+x[0]*x[1]*x[5]+
		x[0]*x[3]*x[4]+x[0]*x[3]*x[5]+
		x[0]*x[4]*x[5]+
		x[1]*x[3]*x[4]+x[1]*x[3]*x[5]+
		x[1]*x[4]*x[5]+
		x[3]*x[4]*x[5]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[4]+x[0]*x[1]*x[5]+
		x[0]*x[2]*x[4]+x[0]*x[2]*x[5]+
		x[0]*x[4]*x[5]+
		x[1]*x[2]*x[4]+x[1]*x[2]*x[5]+
		x[1]*x[4]*x[5]+
		x[2]*x[4]*x[5]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[3]+x[0]*x[1]*x[5]+
		x[0]*x[2]*x[3]+x[0]*x[2]*x[5]+
		x[0]*x[3]*x[5]+
		x[1]*x[2]*x[3]+x[1]*x[2]*x[5]+
		x[1]*x[3]*x[5]+
		x[2]*x[3]*x[5]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[3]+x[0]*x[1]*x[4]+
		x[0]*x[2]*x[3]+x[0]*x[2]*x[4]+
		x[0]*x[3]*x[4]+
		x[1]*x[2]*x[3]+x[1]*x[2]*x[4]+
		x[1]*x[3]*x[4]+
		x[2]*x[3]*x[4]) ;

	c[1] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])))
	*(x[1]*x[2]*x[3]*x[4]+x[1]*x[2]*x[3]*x[5]+
		x[1]*x[2]*x[4]*x[5]+
		x[1]*x[3]*x[4]*x[5]+
		x[2]*x[3]*x[4]*x[5]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])))
	*(x[0]*x[2]*x[3]*x[4]+x[0]*x[2]*x[3]*x[5]+
		x[0]*x[2]*x[4]*x[5]+
		x[0]*x[3]*x[4]*x[5]+
		x[2]*x[3]*x[4]*x[5]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])))
	*(x[0]*x[1]*x[3]*x[4]+x[0]*x[1]*x[3]*x[5]+
		x[0]*x[1]*x[4]*x[5]+
		x[0]*x[3]*x[4]*x[5]+
		x[1]*x[3]*x[4]*x[5]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])))
	*(x[0]*x[1]*x[2]*x[4]+x[0]*x[1]*x[2]*x[5]+
		x[0]*x[1]*x[4]*x[5]+
		x[0]*x[2]*x[4]*x[5]+
		x[1]*x[2]*x[4]*x[5]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])))
	*(x[0]*x[1]*x[2]*x[3]+x[0]*x[1]*x[2]*x[5]+
		x[0]*x[1]*x[3]*x[5]+
		x[0]*x[2]*x[3]*x[5]+
		x[1]*x[2]*x[3]*x[5]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])))
	*(x[0]*x[1]*x[2]*x[3]+x[0]*x[1]*x[2]*x[4]+
		x[0]*x[1]*x[3]*x[4]+
		x[0]*x[2]*x[3]*x[4]+
		x[1]*x[2]*x[3]*x[4]) ;

	c[0] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])))*(-1.0)
	*(x[1]*x[2]*x[3]*x[4]*x[5]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])))*(-1.0)
	*(x[0]*x[2]*x[3]*x[4]*x[5]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[3]*x[4]*x[5]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[4]*x[5]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[3]*x[5]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[3]*x[4]) ;

}

void lagrangeSeven(double * x, double * y, double * c){

	c[6] = 

	y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])) +

	y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])) +

	y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])) +

	y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])) +

	y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])) +

	y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])) +

	y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])) ;

	c[5] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])))*(-1.0)
	*(x[1]+x[2]+x[3]+x[4]+x[5]+x[6]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])))*(-1.0)
	*(x[0]+x[2]+x[3]+x[4]+x[5]+x[6]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])))*(-1.0)
	*(x[0]+x[1]+x[3]+x[4]+x[5]+x[6]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[4]+x[5]+x[6]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[3]+x[5]+x[6]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[3]+x[4]+x[6]) +

	(y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])))*(-1.0)
	*(x[0]+x[1]+x[2]+x[3]+x[4]+x[5]) ;

	c[4] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])))
	*(x[1]*x[2]+x[1]*x[3]+x[1]*x[4]+x[1]*x[5]+x[1]*x[6]+
		x[2]*x[3]+x[2]*x[4]+x[2]*x[5]+x[2]*x[6]+
		x[3]*x[4]+x[3]*x[5]+x[3]*x[6]+
		x[4]*x[5]+x[4]*x[6]+
		x[5]*x[6]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])))
	*(x[0]*x[2]+x[0]*x[3]+x[0]*x[4]+x[0]*x[5]+x[0]*x[6]+
		x[2]*x[3]+x[2]*x[4]+x[2]*x[5]+x[2]*x[6]+
		x[3]*x[4]+x[3]*x[5]+x[3]*x[6]+
		x[4]*x[5]+x[4]*x[6]+
		x[5]*x[6]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])))
	*(x[0]*x[1]+x[0]*x[3]+x[0]*x[4]+x[0]*x[5]+x[0]*x[6]+
		x[1]*x[3]+x[1]*x[4]+x[1]*x[5]+x[1]*x[6]+
		x[3]*x[4]+x[3]*x[5]+x[3]*x[6]+
		x[4]*x[5]+x[4]*x[6]+
		x[5]*x[6]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[4]+x[0]*x[5]+x[0]*x[6]+
		x[1]*x[2]+x[1]*x[4]+x[1]*x[5]+x[1]*x[6]+
		x[2]*x[4]+x[2]*x[5]+x[2]*x[6]+
		x[4]*x[5]+x[4]*x[6]+
		x[5]*x[6]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[3]+x[0]*x[5]+x[0]*x[6]+
		x[1]*x[2]+x[1]*x[3]+x[1]*x[5]+x[1]*x[6]+
		x[2]*x[3]+x[2]*x[5]+x[2]*x[6]+
		x[3]*x[5]+x[3]*x[6]+
		x[5]*x[6]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[3]+x[0]*x[4]+x[0]*x[6]+
		x[1]*x[2]+x[1]*x[3]+x[1]*x[4]+x[1]*x[6]+
		x[2]*x[3]+x[2]*x[4]+x[2]*x[6]+
		x[3]*x[4]+x[3]*x[6]+
		x[4]*x[6]) +

	(y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])))
	*(x[0]*x[1]+x[0]*x[2]+x[0]*x[3]+x[0]*x[4]+x[0]*x[5]+
		x[1]*x[2]+x[1]*x[3]+x[1]*x[4]+x[1]*x[5]+
		x[2]*x[3]+x[2]*x[4]+x[2]*x[5]+
		x[3]*x[4]+x[3]*x[5]+
		x[4]*x[5]) ;

	c[3] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])))*(-1.0)
	*(x[1]*x[2]*x[3]+x[1]*x[2]*x[4]+x[1]*x[2]*x[5]+x[1]*x[2]*x[6]+
		x[1]*x[3]*x[4]+x[1]*x[3]*x[5]+x[1]*x[3]*x[6]+
		x[1]*x[4]*x[5]+x[1]*x[4]*x[6]+
		x[1]*x[5]*x[6]+
		x[2]*x[3]*x[4]+x[2]*x[3]*x[5]+x[2]*x[3]*x[6]+
		x[2]*x[4]*x[5]+x[2]*x[4]*x[6]+
		x[2]*x[5]*x[6]+
		x[3]*x[4]*x[5]+x[3]*x[4]*x[6]+
		x[3]*x[5]*x[6]+
		x[4]*x[5]*x[6]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])))*(-1.0)
	*(x[0]*x[2]*x[3]+x[0]*x[2]*x[4]+x[0]*x[2]*x[5]+x[0]*x[2]*x[6]+
		x[0]*x[3]*x[4]+x[0]*x[3]*x[5]+x[0]*x[3]*x[6]+
		x[0]*x[4]*x[5]+x[0]*x[4]*x[6]+
		x[0]*x[5]*x[6]+
		x[2]*x[3]*x[4]+x[2]*x[3]*x[5]+x[2]*x[3]*x[6]+
		x[2]*x[4]*x[5]+x[2]*x[4]*x[6]+
		x[2]*x[5]*x[6]+
		x[3]*x[4]*x[5]+x[3]*x[4]*x[6]+
		x[3]*x[5]*x[6]+
		x[4]*x[5]*x[6]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[3]+x[0]*x[1]*x[4]+x[0]*x[1]*x[5]+x[0]*x[1]*x[6]+
		x[0]*x[3]*x[4]+x[0]*x[3]*x[5]+x[0]*x[3]*x[6]+
		x[0]*x[4]*x[5]+x[0]*x[4]*x[6]+
		x[0]*x[5]*x[6]+
		x[1]*x[3]*x[4]+x[1]*x[3]*x[5]+x[1]*x[3]*x[6]+
		x[1]*x[4]*x[5]+x[1]*x[4]*x[6]+
		x[1]*x[5]*x[6]+
		x[3]*x[4]*x[5]+x[3]*x[4]*x[6]+
		x[3]*x[5]*x[6]+
		x[4]*x[5]*x[6]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[4]+x[0]*x[1]*x[5]+x[0]*x[1]*x[6]+
		x[0]*x[2]*x[4]+x[0]*x[2]*x[5]+x[0]*x[2]*x[6]+
		x[0]*x[4]*x[5]+x[0]*x[4]*x[6]+
		x[0]*x[5]*x[6]+
		x[1]*x[2]*x[4]+x[1]*x[2]*x[5]+x[1]*x[2]*x[6]+
		x[1]*x[4]*x[5]+x[1]*x[4]*x[6]+
		x[1]*x[5]*x[6]+
		x[2]*x[4]*x[5]+x[2]*x[4]*x[6]+
		x[2]*x[5]*x[6]+
		x[4]*x[5]*x[6]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[3]+x[0]*x[1]*x[5]+x[0]*x[1]*x[6]+
		x[0]*x[2]*x[3]+x[0]*x[2]*x[5]+x[0]*x[2]*x[6]+
		x[0]*x[3]*x[5]+x[0]*x[3]*x[6]+
		x[0]*x[5]*x[6]+
		x[1]*x[2]*x[3]+x[1]*x[2]*x[5]+x[1]*x[2]*x[6]+
		x[1]*x[3]*x[5]+x[1]*x[3]*x[6]+
		x[1]*x[5]*x[6]+
		x[2]*x[3]*x[5]+x[2]*x[3]*x[6]+
		x[2]*x[5]*x[6]+
		x[3]*x[5]*x[6]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[3]+x[0]*x[1]*x[4]+x[0]*x[1]*x[6]+
		x[0]*x[2]*x[3]+x[0]*x[2]*x[4]+x[0]*x[2]*x[6]+
		x[0]*x[3]*x[4]+x[0]*x[3]*x[6]+
		x[0]*x[4]*x[6]+
		x[1]*x[2]*x[3]+x[1]*x[2]*x[4]+x[1]*x[2]*x[6]+
		x[1]*x[3]*x[4]+x[1]*x[3]*x[6]+
		x[1]*x[4]*x[6]+
		x[2]*x[3]*x[4]+x[2]*x[3]*x[6]+
		x[2]*x[4]*x[6]+
		x[3]*x[4]*x[6]) +

	(y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[2]+x[0]*x[1]*x[3]+x[0]*x[1]*x[4]+x[0]*x[1]*x[5]+
		x[0]*x[2]*x[3]+x[0]*x[2]*x[4]+x[0]*x[2]*x[5]+
		x[0]*x[3]*x[4]+x[0]*x[3]*x[5]+
		x[0]*x[4]*x[5]+
		x[1]*x[2]*x[3]+x[1]*x[2]*x[4]+x[1]*x[2]*x[5]+
		x[1]*x[3]*x[4]+x[1]*x[3]*x[5]+
		x[1]*x[4]*x[5]+
		x[2]*x[3]*x[4]+x[2]*x[3]*x[5]+
		x[2]*x[4]*x[5]+
		x[3]*x[4]*x[5]) ;

	c[2] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])))
	*(x[1]*x[2]*x[3]*x[4]+x[1]*x[2]*x[3]*x[5]+x[1]*x[2]*x[3]*x[6]+
		x[1]*x[2]*x[4]*x[5]+x[1]*x[2]*x[4]*x[6]+
		x[1]*x[2]*x[5]*x[6]+
		x[1]*x[3]*x[4]*x[5]+x[1]*x[3]*x[4]*x[6]+
		x[1]*x[3]*x[5]*x[6]+
		x[1]*x[4]*x[5]*x[6]+
		x[2]*x[3]*x[4]*x[5]+x[2]*x[3]*x[4]*x[6]+
		x[2]*x[3]*x[5]*x[6]+
		x[2]*x[4]*x[5]*x[6]+
		x[3]*x[4]*x[5]*x[6]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])))
	*(x[0]*x[2]*x[3]*x[4]+x[0]*x[2]*x[3]*x[5]+x[0]*x[2]*x[3]*x[6]+
		x[0]*x[2]*x[4]*x[5]+x[0]*x[2]*x[4]*x[6]+
		x[0]*x[2]*x[5]*x[6]+
		x[0]*x[3]*x[4]*x[5]+x[0]*x[3]*x[4]*x[6]+
		x[0]*x[3]*x[5]*x[6]+
		x[0]*x[4]*x[5]*x[6]+
		x[2]*x[3]*x[4]*x[5]+x[2]*x[3]*x[4]*x[6]+
		x[2]*x[3]*x[5]*x[6]+
		x[2]*x[4]*x[5]*x[6]+
		x[3]*x[4]*x[5]*x[6]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])))
	*(x[0]*x[1]*x[3]*x[4]+x[0]*x[1]*x[3]*x[5]+x[0]*x[1]*x[3]*x[6]+
		x[0]*x[1]*x[4]*x[5]+x[0]*x[1]*x[4]*x[6]+
		x[0]*x[1]*x[5]*x[6]+
		x[0]*x[3]*x[4]*x[5]+x[0]*x[3]*x[4]*x[6]+
		x[0]*x[3]*x[5]*x[6]+
		x[0]*x[4]*x[5]*x[6]+
		x[1]*x[3]*x[4]*x[5]+x[1]*x[3]*x[4]*x[6]+
		x[1]*x[3]*x[5]*x[6]+
		x[1]*x[4]*x[5]*x[6]+
		x[3]*x[4]*x[5]*x[6]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])))
	*(x[0]*x[1]*x[2]*x[4]+x[0]*x[1]*x[2]*x[5]+x[0]*x[1]*x[2]*x[6]+
		x[0]*x[1]*x[4]*x[5]+x[0]*x[1]*x[4]*x[6]+
		x[0]*x[1]*x[5]*x[6]+
		x[0]*x[2]*x[4]*x[5]+x[0]*x[2]*x[4]*x[6]+
		x[0]*x[2]*x[5]*x[6]+
		x[0]*x[4]*x[5]*x[6]+
		x[1]*x[2]*x[4]*x[5]+x[1]*x[2]*x[4]*x[6]+
		x[1]*x[2]*x[5]*x[6]+
		x[1]*x[4]*x[5]*x[6]+
		x[2]*x[4]*x[5]*x[6]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])))
	*(x[0]*x[1]*x[2]*x[3]+x[0]*x[1]*x[2]*x[5]+x[0]*x[1]*x[2]*x[6]+
		x[0]*x[1]*x[3]*x[5]+x[0]*x[1]*x[3]*x[6]+
		x[0]*x[1]*x[5]*x[6]+
		x[0]*x[2]*x[3]*x[5]+x[0]*x[2]*x[3]*x[6]+
		x[0]*x[2]*x[5]*x[6]+
		x[0]*x[3]*x[5]*x[6]+
		x[1]*x[2]*x[3]*x[5]+x[1]*x[2]*x[3]*x[6]+
		x[1]*x[2]*x[5]*x[6]+
		x[1]*x[3]*x[5]*x[6]+
		x[2]*x[3]*x[5]*x[6]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])))
	*(x[0]*x[1]*x[2]*x[3]+x[0]*x[1]*x[2]*x[4]+x[0]*x[1]*x[2]*x[6]+
		x[0]*x[1]*x[3]*x[4]+x[0]*x[1]*x[3]*x[6]+
		x[0]*x[1]*x[4]*x[6]+
		x[0]*x[2]*x[3]*x[4]+x[0]*x[2]*x[3]*x[6]+
		x[0]*x[2]*x[4]*x[6]+
		x[0]*x[3]*x[4]*x[6]+
		x[1]*x[2]*x[3]*x[4]+x[1]*x[2]*x[3]*x[6]+
		x[1]*x[2]*x[4]*x[6]+
		x[1]*x[3]*x[4]*x[6]+
		x[2]*x[3]*x[4]*x[6]) +

	(y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])))
	*(x[0]*x[1]*x[2]*x[3]+x[0]*x[1]*x[2]*x[4]+x[0]*x[1]*x[2]*x[5]+
		x[0]*x[1]*x[3]*x[4]+x[0]*x[1]*x[3]*x[5]+
		x[0]*x[1]*x[4]*x[5]+
		x[0]*x[2]*x[3]*x[4]+x[0]*x[2]*x[3]*x[5]+
		x[0]*x[2]*x[4]*x[5]+
		x[0]*x[3]*x[4]*x[5]+
		x[1]*x[2]*x[3]*x[4]+x[1]*x[2]*x[3]*x[5]+
		x[1]*x[2]*x[4]*x[5]+
		x[1]*x[3]*x[4]*x[5]+
		x[2]*x[3]*x[4]*x[5]) ;

	c[1] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])))*(-1.0)
	*(x[1]*x[2]*x[3]*x[4]*x[5]+x[1]*x[2]*x[3]*x[4]*x[6]+
		x[1]*x[2]*x[3]*x[5]*x[6]+
		x[1]*x[2]*x[4]*x[5]*x[6]+
		x[1]*x[3]*x[4]*x[5]*x[6]+
		x[2]*x[3]*x[4]*x[5]*x[6]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])))*(-1.0)
	*(x[0]*x[2]*x[3]*x[4]*x[5]+x[0]*x[2]*x[3]*x[4]*x[6]+
		x[0]*x[2]*x[3]*x[5]*x[6]+
		x[0]*x[2]*x[4]*x[5]*x[6]+
		x[0]*x[3]*x[4]*x[5]*x[6]+
		x[2]*x[3]*x[4]*x[5]*x[6]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[3]*x[4]*x[5]+x[0]*x[1]*x[3]*x[4]*x[6]+
		x[0]*x[1]*x[3]*x[5]*x[6]+
		x[0]*x[1]*x[4]*x[5]*x[6]+
		x[0]*x[3]*x[4]*x[5]*x[6]+
		x[1]*x[3]*x[4]*x[5]*x[6]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[4]*x[5]+x[0]*x[1]*x[2]*x[4]*x[6]+
		x[0]*x[1]*x[2]*x[5]*x[6]+
		x[0]*x[1]*x[4]*x[5]*x[6]+
		x[0]*x[2]*x[4]*x[5]*x[6]+
		x[1]*x[2]*x[4]*x[5]*x[6]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[3]*x[5]+x[0]*x[1]*x[2]*x[3]*x[6]+
		x[0]*x[1]*x[2]*x[5]*x[6]+
		x[0]*x[1]*x[3]*x[5]*x[6]+
		x[0]*x[2]*x[3]*x[5]*x[6]+
		x[1]*x[2]*x[3]*x[5]*x[6]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[3]*x[4]+x[0]*x[1]*x[2]*x[3]*x[6]+
		x[0]*x[1]*x[2]*x[4]*x[6]+
		x[0]*x[1]*x[3]*x[4]*x[6]+
		x[0]*x[2]*x[3]*x[4]*x[6]+
		x[1]*x[2]*x[3]*x[4]*x[6]) +

	(y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])))*(-1.0)
	*(x[0]*x[1]*x[2]*x[3]*x[4]+x[0]*x[1]*x[2]*x[3]*x[5]+
		x[0]*x[1]*x[2]*x[4]*x[5]+
		x[0]*x[1]*x[3]*x[4]*x[5]+
		x[0]*x[2]*x[3]*x[4]*x[5]+
		x[1]*x[2]*x[3]*x[4]*x[5]) ;

	c[0] = 

	(y[0]/((x[0]-x[1])*(x[0]-x[2])*(x[0]-x[3])*(x[0]-x[4])*(x[0]-x[5])*(x[0]-x[6])))
	*(x[1]*x[2]*x[3]*x[4]*x[5]*x[6]) +

	(y[1]/((x[1]-x[0])*(x[1]-x[2])*(x[1]-x[3])*(x[1]-x[4])*(x[1]-x[5])*(x[1]-x[6])))
	*(x[0]*x[2]*x[3]*x[4]*x[5]*x[6]) +

	(y[2]/((x[2]-x[0])*(x[2]-x[1])*(x[2]-x[3])*(x[2]-x[4])*(x[2]-x[5])*(x[2]-x[6])))
	*(x[0]*x[1]*x[3]*x[4]*x[5]*x[6]) +

	(y[3]/((x[3]-x[0])*(x[3]-x[1])*(x[3]-x[2])*(x[3]-x[4])*(x[3]-x[5])*(x[3]-x[6])))
	*(x[0]*x[1]*x[2]*x[4]*x[5]*x[6]) +

	(y[4]/((x[4]-x[0])*(x[4]-x[1])*(x[4]-x[2])*(x[4]-x[3])*(x[4]-x[5])*(x[4]-x[6])))
	*(x[0]*x[1]*x[2]*x[3]*x[5]*x[6]) +

	(y[5]/((x[5]-x[0])*(x[5]-x[1])*(x[5]-x[2])*(x[5]-x[3])*(x[5]-x[4])*(x[5]-x[6])))
	*(x[0]*x[1]*x[2]*x[3]*x[4]*x[6]) +

	(y[6]/((x[6]-x[0])*(x[6]-x[1])*(x[6]-x[2])*(x[6]-x[3])*(x[6]-x[4])*(x[6]-x[5])))
	*(x[0]*x[1]*x[2]*x[3]*x[4]*x[5]) ;

}