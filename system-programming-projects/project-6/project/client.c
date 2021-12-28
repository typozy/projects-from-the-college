#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

int UTC = 3;
int hostFD = 0;

char * updateString = "UPDATE";

char serverIP[20];
int portno;
int consoleOut = 1;
int errOut = 2;
int ID;
int queryFD = 0;
int queryCount = 0;
int rowCount = 0;
int columnCount = 0;


char ** answer = 0;

struct sockaddr_in hostAddr;
socklen_t addrSize;

struct sigaction act;

sigset_t sigIntMask;

int strToInt(char * str);

void inputCheck(int argcount, char *argvalue[]);

void handlerSigInt(int signo){
	close(hostFD);
	close(queryFD);
	for (int i = 0; i < rowCount+1; ++i){
		free(answer[i]);
	}
	free(answer);
	write(errOut,"\nSIGINT exit...\n",16);
	exit(-1);
}

int main(int argc, char * argv[]){

	inputCheck(argc,argv);

	memset(&act, 0, sizeof(act));
	act.sa_handler = &handlerSigInt;
	sigaction(SIGINT,  &act, 0);

	sigfillset(&sigIntMask);
	sigdelset(&sigIntMask,SIGINT);

	char bufQuery[10000];
	char bufLine[10000];
	while((hostFD = socket(AF_INET, SOCK_STREAM, 0)) == -1);
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(portno);
	hostAddr.sin_addr.s_addr = inet_addr(serverIP);
	memset(hostAddr.sin_zero, '\0', sizeof(hostAddr.sin_zero));
	struct timeval cur;
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Client-%d connecting to %s:%d\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,ID,serverIP,portno);
	write(consoleOut,bufLine,strlen(bufLine));
	addrSize = sizeof(hostAddr);
	while(connect(hostFD, (struct sockaddr *) &hostAddr, addrSize) == -1)
		addrSize = sizeof(hostAddr);
	struct timeval start, end;

	char cursor[2];
	cursor[1] = '\0';
	while(read(queryFD,cursor,1)){
		char num[20];
		num[0] = '\0';
		while(cursor[0] != ' '){
			strcat(num,cursor);
			read(queryFD,cursor,1);
		}
		if(ID == strToInt(num))
			++queryCount;
		while(cursor[0] != '\n')
			read(queryFD,cursor,1);
	}
	lseek(queryFD,0,SEEK_SET);
	while(write(hostFD,&queryCount,sizeof(int)) == -1);
	read(hostFD,&rowCount,sizeof(int));
	read(hostFD,&columnCount,sizeof(int));
	answer = (char **)malloc((rowCount+1)*sizeof(char *));
	for (int i = 0; i < rowCount+1; ++i){
		answer[i] = (char *)malloc(columnCount*512*sizeof(char));
	}
	int first = 1;
	for (int i = 0; i < queryCount; ++i){
		while(read(queryFD,cursor,1)){
			char num[50];
			num[0] = '\0';
			while(cursor[0] != ' '){
				strcat(num,cursor);
				read(queryFD,cursor,1);
			}
			if(ID == strToInt(num)){
				bufQuery[0] = '\0';
				read(queryFD,cursor,1);
				while(cursor[0] == ' ')
					read(queryFD,cursor,1);
				while(cursor[0] != '\n'){
					strcat(bufQuery,cursor);
					read(queryFD,cursor,1);
				}
				break;
			}
			else{
				while(cursor[0] != '\n')
					read(queryFD,cursor,1);
			}
		}
		if(first){
			gettimeofday(&start,0); 
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Client-%d connected and sending query '%s'\n",(start.tv_sec/3600+UTC)%24,(start.tv_sec/60)%60,start.tv_sec%60,start.tv_usec/1000,ID ,bufQuery);
			write(consoleOut,bufLine,strlen(bufLine));
			first = 0;
		}
		else{
			gettimeofday(&start,0); 
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Client-%d sending query '%s'\n",(start.tv_sec/3600+UTC)%24,(start.tv_sec/60)%60,start.tv_sec%60,start.tv_usec/1000,ID ,bufQuery);
			write(consoleOut,bufLine,strlen(bufLine));
		}
		int rowsAffected;
		int recCount = 0;
		if(strncmp(bufQuery,updateString,6) == 0){
			while(write(hostFD,bufQuery,strlen(bufQuery)) == -1);
			read(hostFD,&rowsAffected,sizeof(int));
		}
		else{
			while(write(hostFD,bufQuery,strlen(bufQuery)) == -1);
			read(hostFD,&recCount,sizeof(int));
			int len = 0;
			read(hostFD,&len,sizeof(int));
			for (int j = 0; j < recCount+1; ++j){
				answer[j][0] = '\0';
				for (int k = 0; k < len; ++k){
					while(read(hostFD,cursor,1) != 1);
					strcat(answer[j],cursor);
				}
				
			}
		}
		gettimeofday(&end,0);
		double secpassed = (double)(end.tv_sec-start.tv_sec);
		double usecpassed = (double)(end.tv_usec-start.tv_usec);
		if(usecpassed < 0.0){
			secpassed = secpassed - 1.0;
			usecpassed = usecpassed + 1000000.0;
		}
		secpassed = secpassed + (usecpassed/1000000.0);
		if (strncmp(bufQuery,updateString,6) == 0){
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Server’s response to Client-%d arrived in %.3f seconds.\n",(end.tv_sec/3600+UTC)%24,(end.tv_sec/60)%60,end.tv_sec%60,end.tv_usec/1000,ID,secpassed);
			write(consoleOut,bufLine,strlen(bufLine));
			sprintf(bufLine,"You have made changes to the database. Rows affected: %d\n",rowsAffected);
			write(consoleOut,bufLine,strlen(bufLine));
		}
		else{
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Server’s response to Client-%d is %d records, and arrived in %.3f seconds.\n",(end.tv_sec/3600+UTC)%24,(end.tv_sec/60)%60,end.tv_sec%60,end.tv_usec/1000,ID,recCount,secpassed);
			write(consoleOut,bufLine,strlen(bufLine));
			for (int j = 0; j < recCount+1; ++j){
				write(consoleOut,answer[j],strlen(answer[j]));
			}

		}
	}
	sprintf(bufLine,"A total of %d queries were executed, client is terminating.\n",queryCount);
	write(consoleOut,bufLine,strlen(bufLine));
	close(hostFD);
	close(queryFD);
	for (int i = 0; i < rowCount+1; ++i){
		free(answer[i]);
	}
	free(answer);
	return 0;
}

//
//
//	END OF MAIN
//
//

int strToInt(char * str){
	int res = 0;
	int minus = 0;
	int i=0;
	if(str[i] == '-'){
		minus = 1;
		++i;
	}
	if(str[i] == '\0'){
		write(errOut,"Enter integer as argument\n",31);
		exit(-1);
	}
	while(str[i] != '\0'){
		if(str[i] >= '0' && str[i] <= '9'){
			res = res*10;
			res = res+(str[i]-'0');
			++i;
		}
		else{
			write(errOut,"Enter integer as argument\n",31);
			exit(-1);
		}
	}
	if(minus)
		res = -res;
	return res;
}

void inputCheck(int argcount, char *argvalue[]){
	int opt;
	int checkArr[4] = {0,0,0,0};
	for(int i=0; i<4; ++i){
		if((opt = getopt(argcount,argvalue,"i:a:p:o:")) == -1){
			write(errOut,"There are missed arguments\n",27);
			exit(-1);
		}
		switch(opt){
			case 'i':
				if(!checkArr[0]){
					ID = strToInt(optarg);
					if(ID < 1){
						write(errOut,"Enter a positive integer for client id\n",39);
						exit(-1);
					}
					checkArr[0] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;			
			case 'a':
				if(!checkArr[1]){
					strcpy(serverIP,optarg);
					checkArr[1] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'p':
				if(!checkArr[2]){
					portno = strToInt(optarg);
					if(portno < 1024 || portno == 8080){
						write(errOut,"Enter a port number that the OS does not use\n",45);
						exit(-1);
					}
					checkArr[2] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'o':
				if(!checkArr[3]){
					if((queryFD = open(optarg,O_RDONLY)) == -1){
						write(errOut,"Query file could not be opened\n",32);
						exit(-1);
					}
					checkArr[3] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			default:
				write(errOut,"Wrong argument type\n",20);
				exit(-1);
		}
	}
	if(optind < argcount){
		write(errOut,"There are extra arguments\n",26);
		exit(-1);
	}
	return;
}