#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

char *** dataset;
int UTC = 3;
int hostFD = 0;

int * clientFD = 0;
int portno;
int poolSize;
int datasetFD = 0;
int logFD = 0;
int errOut = 2;
int usedThreads = 0;
int threadID = 0;
char pathIn[10000];
char pathToLogFile[10000];
int endServer = 0;
int * busyClient;

int daemonFD;

char * daemonName = "/tmp/161044083_DB_Server";

char * enter = "\n";
char * selectString = "SELECT";
char * distinctString = "DISTINCT";

struct sockaddr_in hostAddr;
struct sockaddr_storage socketStore;
socklen_t addrSize;

pthread_mutex_t initLock;
pthread_mutex_t cacheLock;
pthread_mutex_t poolLock;
pthread_mutex_t acceptLock;
pthread_mutex_t endLock;
pthread_cond_t poolSignal;
pthread_t * handlerThread;
pthread_t poolThread;

pthread_mutex_t readWriteLock;
pthread_cond_t writeSignal;
pthread_cond_t readSignal;

int activeWriters = 0;
int waitingWriters = 0;
int activeReaders = 0;
int waitingReaders = 0;


int columnCount = 0;
int rowCount = 0;

struct sigaction act;

sigset_t sigIntMask;

int strToInt(char * str);

void inputCheck(int argcount, char *argvalue[]);

void * requestHandler(void * args);

void * poolHandler(void * args);

void loadDataset();

int selectDistinct(char * query,int myID);

int selectNormal(char * query,int myID);

int update(char * query, int myID);

void handlerSigInt(int signo){
	char bufLine[10000];
	struct timeval cur;
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Termination signal received, waiting for ongoing threads to complete.\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000);
	write(logFD,bufLine,strlen(bufLine));
	pthread_mutex_lock(&endLock);
	endServer = 1;
	for (int i = 0; i < poolSize; ++i){
		if(!busyClient[i]){
			pthread_detach(handlerThread[i]);
		}
	}
	pthread_mutex_unlock(&endLock);
	for (int i = 0; i < poolSize; ++i){
		if(busyClient[i]){
			pthread_join(handlerThread[i],0);
		}
	}
	pthread_detach(poolThread);
	pthread_mutex_destroy(&initLock);
	pthread_mutex_destroy(&cacheLock);
	pthread_mutex_destroy(&poolLock);
	pthread_mutex_destroy(&acceptLock);
	pthread_mutex_destroy(&endLock);
	pthread_mutex_destroy(&readWriteLock);
	pthread_cond_destroy(&writeSignal);
	pthread_cond_destroy(&readSignal);
	pthread_cond_destroy(&poolSignal);
	close(hostFD);
	close(datasetFD);
	for (int i = 0; i < poolSize; ++i){
		close(clientFD[i]);
	}
	free(clientFD);
	free(handlerThread);
	free(busyClient);
	for (int i = 0; i < rowCount; ++i){
		for (int j = 0; j < columnCount; ++j){
			free(dataset[i][j]);
		}
		free(dataset[i]);
	}
	free(dataset);
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld All threads have terminated, server shutting down.\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000);
	write(logFD,bufLine,strlen(bufLine));
	close(logFD);
	close(daemonFD);
	unlink(daemonName);
	exit(0);
}

int main(int argc, char *argv[]){

	if((daemonFD = open(daemonName, O_CREAT|O_EXCL)) < 0){
		write(errOut,"The DB server is already running!\n",34);
		exit(-1);
	}

	inputCheck(argc,argv);

	if(fork())
		exit(0);

	setsid();

	memset(&act, 0, sizeof(act));
	act.sa_handler = &handlerSigInt;
	sigaction(SIGINT,  &act, 0);

	if(fork())
		exit(0);

	chdir("/");
	umask(0);
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	sigfillset(&sigIntMask);
	sigdelset(&sigIntMask,SIGINT);

	struct timeval cur;
	char bufLine[10000];
	gettimeofday(&cur,0); 
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Executing with parameters:\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000);
	write(logFD,bufLine,strlen(bufLine));
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld -p %d\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,portno);
	write(logFD,bufLine,strlen(bufLine));
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld -o %s\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,pathToLogFile);
	write(logFD,bufLine,strlen(bufLine));
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld -l %d\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,poolSize);
	write(logFD,bufLine,strlen(bufLine));
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld -d %s\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,pathIn);
	write(logFD,bufLine,strlen(bufLine));
	struct timeval start, end;
	gettimeofday(&start,0); 
	sprintf(bufLine,"Loading dataset...\n");
	write(logFD,bufLine,strlen(bufLine));
	loadDataset();
	gettimeofday(&end,0);
	double secpassed = (double)(end.tv_sec-start.tv_sec);
	double usecpassed = (double)(end.tv_usec-start.tv_usec);
	if(usecpassed < 0.0){
		secpassed = secpassed - 1.0;
		usecpassed = usecpassed + 1000000.0;
	}
	secpassed = secpassed + (usecpassed/1000000.0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Dataset loaded in %.3f seconds with %d records\n",(end.tv_sec/3600+UTC)%24,(end.tv_sec/60)%60,end.tv_sec%60,end.tv_usec/1000,secpassed,rowCount-1);
	write(logFD,bufLine,strlen(bufLine));
	clientFD = (int *) malloc(poolSize*sizeof(int));
	for (int i = 0; i < poolSize; ++i){
		clientFD[i] = 0;
	}
	while((hostFD = socket(AF_INET, SOCK_STREAM, 0)) == -1);
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(portno);
	hostAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(hostAddr.sin_zero, '\0', sizeof(hostAddr.sin_zero));
	while(bind(hostFD, (struct sockaddr *) &hostAddr, sizeof(hostAddr)) == -1);
	while(listen(hostFD,5) == -1);
	pthread_mutex_init(&initLock,0);
	pthread_mutex_init(&cacheLock,0);
	pthread_mutex_init(&poolLock,0);
	pthread_mutex_init(&acceptLock,0);
	pthread_mutex_init(&endLock,0);
	pthread_mutex_init(&readWriteLock,0);
	pthread_cond_init(&writeSignal,0);
	pthread_cond_init(&readSignal,0);
	pthread_cond_init(&poolSignal,0);
	busyClient = (int *) malloc(poolSize*sizeof(int));
	for (int i = 0; i < poolSize; ++i){
		busyClient[i] = 0;
	}
	handlerThread = (pthread_t *) malloc(poolSize*sizeof(pthread_t));
	pthread_create(&poolThread,0,poolHandler,0);
	for (int i = 0; i < poolSize; ++i){
		pthread_create(&(handlerThread[i]),0,requestHandler,0);
	}
	sigsuspend(&sigIntMask);
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
		if((opt = getopt(argcount,argvalue,"p:o:l:d:")) == -1){
			write(errOut,"There are missed arguments\n",27);
			exit(-1);
		}
		switch(opt){
			case 'p':
				if(!checkArr[0]){
					portno = strToInt(optarg);
					if(portno < 1024 || portno == 8080){
						write(errOut,"Enter a port number that the OS does not use\n",45);
						exit(-1);
					}
					checkArr[0] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'o':
				if(!checkArr[1]){
					if((logFD = open(optarg,O_WRONLY|O_APPEND|O_CREAT,00666)) == -1){
						write(errOut,"Log file could not be opened\n",29);
						exit(-1);
					}
					strcpy(pathToLogFile,optarg);
					checkArr[1] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'l':
				if(!checkArr[2]){
					poolSize = strToInt(optarg);
					if(poolSize < 2){
						write(errOut,"Enter an integer which is greater than 1 for pool size\n",55);
						exit(-1);
					}
					checkArr[2] = 1;
				}
				else{
					write(errOut,"More than one input from the same option\n",41);
					exit(-1);
				}
				break;
			case 'd':
				if(!checkArr[3]){
					if((datasetFD = open(optarg,O_RDONLY)) == -1){
						write(errOut,"There is no file to open in this path\n",38);
						exit(-1);
					}
					strcpy(pathIn,optarg);
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

void * requestHandler(void * args){
	pthread_mutex_lock(&initLock);
	int ID = threadID;
	++threadID;
	pthread_mutex_unlock(&initLock);
	char bufQuery[10000];
	char bufLine[10000];
	struct timeval cur;
	while(1){
		gettimeofday(&cur,0);
		sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Thread #%d: waiting for connection\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,ID);
		write(logFD,bufLine,strlen(bufLine));
		pthread_mutex_lock(&acceptLock);
		addrSize = sizeof(socketStore);
		while((clientFD[ID] = accept(hostFD, (struct sockaddr *) &socketStore, &addrSize)) == -1)
			addrSize = sizeof(socketStore);
		pthread_mutex_unlock(&acceptLock);
		pthread_mutex_lock(&endLock);
		++busyClient[ID];
		pthread_mutex_unlock(&endLock);
		pthread_mutex_lock(&poolLock);
		++usedThreads;
		gettimeofday(&cur,0);
		sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld A connection has been delegated to thread id #%d\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,ID);
		write(logFD,bufLine,strlen(bufLine));
		pthread_cond_signal(&poolSignal);
		pthread_mutex_unlock(&poolLock);
		int requestCount;
		read(clientFD[ID],&requestCount,sizeof(int));
		while(write(clientFD[ID],&rowCount,sizeof(int)) == -1);
		while(write(clientFD[ID],&columnCount,sizeof(int)) == -1);
		for (int i = 0; i < requestCount; ++i){	
			bufQuery[0] = '\0';
			char cursor[2];
			cursor[1] = '\0';
			while(read(clientFD[ID],cursor,sizeof(char)) != 1);
			while(cursor[0] != ';'){
				strcat(bufQuery,cursor);
				while(read(clientFD[ID],cursor,sizeof(char)) != 1);
			}
			strcat(bufQuery,cursor);
			gettimeofday(&cur,0);
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Thread #%d: received query ‘%s‘\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,ID,bufQuery);
			write(logFD,bufLine,strlen(bufLine));
			int recordCount;
			if(strncmp(bufQuery,selectString,6) == 0){

				pthread_mutex_lock(&readWriteLock);
				while ((activeWriters + waitingWriters) > 0){
					++waitingReaders;
					pthread_cond_wait(&readSignal,&readWriteLock);
					--waitingReaders;
				}
				++activeReaders;
				pthread_mutex_unlock(&readWriteLock);

				usleep(500000);
				if(strncmp(&bufQuery[7],distinctString,8) == 0){
					recordCount = selectDistinct(bufQuery,ID);
				}
				else{
					recordCount = selectNormal(bufQuery,ID);
				}

				pthread_mutex_lock(&readWriteLock);
				--activeReaders;
				if (activeReaders == 0 && waitingWriters > 0)
					pthread_cond_signal(&writeSignal);
				pthread_mutex_unlock(&readWriteLock);
			}
			else{
				pthread_mutex_lock(&readWriteLock);
				while ((activeWriters + activeReaders) > 0) {
					++waitingWriters;
					pthread_cond_wait(&writeSignal,&readWriteLock);
					--waitingWriters;
				}
				++activeWriters;
				pthread_mutex_unlock(&readWriteLock);

				usleep(500000);
				recordCount = update(bufQuery,ID);

				pthread_mutex_lock(&readWriteLock);
				--activeWriters;
				if (waitingWriters > 0)
					pthread_cond_signal(&writeSignal);
				else if (waitingReaders > 0)
					pthread_cond_broadcast(&readSignal);
				pthread_mutex_unlock(&readWriteLock);
			}
			if(strncmp(bufQuery,selectString,6) == 0){
				gettimeofday(&cur,0);
				sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Thread #%d: query completed, %d records have been returned.\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,ID,recordCount);
				write(logFD,bufLine,strlen(bufLine));
			}
			else{
				gettimeofday(&cur,0);
				sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld Thread #%d: query completed, %d records have been modified.\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000,ID,recordCount);
				write(logFD,bufLine,strlen(bufLine));
			}
		}
		close(clientFD[ID]);
		pthread_mutex_lock(&poolLock);
		--usedThreads;
		pthread_cond_signal(&poolSignal);
		pthread_mutex_unlock(&poolLock);
		pthread_mutex_lock(&endLock);
		int endLoop = endServer;
		if(!endLoop)
			--busyClient[ID];
		pthread_mutex_unlock(&endLock);
		if(endLoop)
			break;
	}
	pthread_exit(0);
	return 0;
}

void * poolHandler(void * args){
	char bufLine[10000];
	struct timeval cur;
	gettimeofday(&cur,0);
	sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld There is/are available thread(s).\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000);
	write(logFD,bufLine,strlen(bufLine));
	int previous = usedThreads;
	pthread_mutex_lock(&poolLock);
	while(1){
		if(usedThreads == poolSize){
			gettimeofday(&cur,0);
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld No thread is available! Waiting for one.\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000);
			write(logFD,bufLine,strlen(bufLine));
		}
		else if(usedThreads == poolSize-1 && previous == poolSize){
			gettimeofday(&cur,0);
			sprintf(bufLine,"%02ld:%02ld:%02ld.%03ld There is/are available thread(s).\n",(cur.tv_sec/3600+UTC)%24,(cur.tv_sec/60)%60,cur.tv_sec%60,cur.tv_usec/1000);
			write(logFD,bufLine,strlen(bufLine));
		}
		previous = usedThreads;
		pthread_cond_wait(&poolSignal,&poolLock);
	}
	pthread_mutex_unlock(&poolLock);
	pthread_exit(0);
	return 0;
}

void loadDataset(){
	char cur[2];
	cur[1] = '\0';
	while(read(datasetFD,cur,sizeof(char))){
		if(cur[0] == '"'){
			read(datasetFD,cur,sizeof(char));
			while(cur[0] != '"'){
				read(datasetFD,cur,sizeof(char));
			}
			read(datasetFD,cur,sizeof(char));
			if(cur[0] == ','){
				++columnCount;
			}
			else if(cur[0] == '\n'){
				++columnCount;
				++rowCount;
			}
			else{
				read(datasetFD,cur,sizeof(char));
				++columnCount;
				++rowCount;
			}
		}
		else if(cur[0] == ','){
			++columnCount;
		}
		else if(cur[0] == '\n'){
			++columnCount;
			++rowCount;
		}
		else if(cur[0] == '\r'){
			read(datasetFD,cur,sizeof(char));
			++columnCount;
			++rowCount;
		}
		else{
			read(datasetFD,cur,sizeof(char));
			while(cur[0] != 13 && cur[0] != 10 && cur[0] != ','){
				read(datasetFD,cur,sizeof(char));
			}
			if(cur[0] == ','){
				++columnCount;
			}
			else if(cur[0] == '\n'){
				++columnCount;
				++rowCount;
			}
			else{
				read(datasetFD,cur,sizeof(char));
				++columnCount;
				++rowCount;
			}
		}
	}
	columnCount = columnCount/rowCount;
	dataset = (char ***)malloc(rowCount*sizeof(char**));
	for (int i = 0; i < rowCount; ++i){
		dataset[i] = (char **)malloc(columnCount*sizeof(char*));
	}
	for (int i = 0; i < rowCount; ++i){
		for (int j = 0; j < columnCount; ++j){
			dataset[i][j] = (char *)malloc(512*sizeof(char));
			dataset[i][j][0] = '\0';
		}
	}

	int columnIndex = 0;
	int rowIndex = 0;
	lseek(datasetFD,0,SEEK_SET);
	while(read(datasetFD,cur,sizeof(char))){
		if(cur[0] == '"'){
			read(datasetFD,cur,sizeof(char));
			while(cur[0] != '"'){
				if(cur[0] == '\n'){
					strcat(dataset[rowIndex][columnIndex],"\\n");
				}
				else if(cur[0] == '\r'){
					strcat(dataset[rowIndex][columnIndex],"\\r");
					read(datasetFD,cur,sizeof(char));
				}
				else{
					strcat(dataset[rowIndex][columnIndex],cur);
				}
				read(datasetFD,cur,sizeof(char));
			}
			read(datasetFD,cur,sizeof(char));
			if(cur[0] == ','){
				columnIndex = (columnIndex+1)%columnCount;
			}
			else if(cur[0] != 10){
				columnIndex = (columnIndex+1)%columnCount;
				++rowIndex;
			}
			else{
				read(datasetFD,cur,sizeof(char));
				columnIndex = (columnIndex+1)%columnCount;
				++rowIndex;
			}
		}
		else if(cur[0] == ','){
			columnIndex = (columnIndex+1)%columnCount;
		}
		else if(cur[0] == '\n'){
			columnIndex = (columnIndex+1)%columnCount;
			++rowIndex;
		}
		else if(cur[0] == '\r'){
			read(datasetFD,cur,sizeof(char));
			columnIndex = (columnIndex+1)%columnCount;
			++rowIndex;
		}
		else{
			strcat(dataset[rowIndex][columnIndex],cur);
			read(datasetFD,cur,sizeof(char));
			while(cur[0] != 13 && cur[0] != 10 && cur[0] != ','){
				strcat(dataset[rowIndex][columnIndex],cur);
				read(datasetFD,cur,sizeof(char));
			}
			if(cur[0] == ','){
				columnIndex = (columnIndex+1)%columnCount;
			}
			else if(cur[0] == '\n'){
				columnIndex = (columnIndex+1)%columnCount;
				++rowIndex;
			}
			else{
				read(datasetFD,cur,sizeof(char));
				columnIndex = (columnIndex+1)%columnCount;
				++rowIndex;
			}
		}
	}
	for (int j = 0; j < columnCount; ++j){
		int max = -1;
		for (int i = 0; i < rowCount; ++i){
			int tempMax = strlen(dataset[i][j]);
			if(tempMax > max){
				max = tempMax;
			}
		}
		max = max + 1;
		for (int i = 0; i < rowCount; ++i){
			int len = strlen(dataset[i][j]);
			while(len < max){
				strcat(dataset[i][j]," ");
				++len;
			}
		}
	}
	return;
}

int selectDistinct(char * query,int myID){
	int count;
	int star = 0;
	int start = 0;
	for (int i = 0; i < 2; ++i){
		while(query[start] != ' ')
			++start;
		while(query[start] == ' ')
			++start;
	}
	if(query[start] == '*')
		star = 1;
	if(star){
		count = columnCount;
	}
	else{
		count = 1;
		for (int i = 0; i < strlen(query); ++i){
			if(query[i] == ','){
				++count;

			}
		}
	}
	int index[count];
	if(star){
		for (int i = 0; i < count; ++i){
			index[i] = i;
		}
	}
	else{
		char key[count][512];
		int cur = start;
		for (int i = 0; i < count; ++i){
			int tempCur = 0;
			while(query[cur] != ',' && query[cur] != ' '){
				key[i][tempCur] = query[cur];
				++tempCur;
				++cur;
			}
			key[i][tempCur] = '\0';
			while(query[cur] == ',' || query[cur] == ' ')
				++cur;
		}
		for (int i = 0; i < count; ++i){
			int tempIndex = 0;
			while(1){
				int found = 0;
				if(strncmp(dataset[0][tempIndex],key[i],strlen(key[i])) == 0){
					found = 1;
					for (int j = strlen(key[i]); j < strlen(dataset[0][tempIndex]); ++j){
						if(dataset[0][tempIndex][j] != ' '){
							found = 0;
							break;
						}
					}
				}
				if(found)
					break;
				++tempIndex;
			}
			index[i] = tempIndex;
		}
	}
	int uniqueCount = 0;
	for (int i = 1; i < rowCount; ++i){
		int unique = 1;
		for (int j = 1; j < i; ++j){
			int hasDuplicate = 1;
			for (int k = 0; k < count; ++k){
				if(strcmp(dataset[i][index[k]],dataset[j][index[k]]) != 0){
					hasDuplicate = 0;
					break;
				}
			}
			if(hasDuplicate){
				unique = 0;
				break;
			}
		}
		if(unique){
			++uniqueCount;
		}
	}
	while(write(clientFD[myID],&uniqueCount,sizeof(int)) == -1);
	int len = 1;
	for (int i = 0; i < count; ++i){
		len += strlen(dataset[0][index[i]]);
	}
	while(write(clientFD[myID],&len,sizeof(int)) == -1);
	for (int i = 0; i < count; ++i){
		while(write(clientFD[myID],dataset[0][index[i]],strlen(dataset[0][index[i]])) == -1);
	}
	while(write(clientFD[myID],enter,strlen(enter)) == -1);
	for (int i = 1; i < rowCount; ++i){
		int unique = 1;
		for (int j = 1; j < i; ++j){
			int hasDuplicate = 1;
			for (int k = 0; k < count; ++k){
				if(strcmp(dataset[i][index[k]],dataset[j][index[k]]) != 0){
					hasDuplicate = 0;
					break;
				}
			}
			if(hasDuplicate){
				unique = 0;
				break;
			}
		}
		if(unique){
			for (int j = 0; j < count; ++j){
				while(write(clientFD[myID],dataset[i][index[j]],strlen(dataset[i][index[j]])) == -1);
			}
			while(write(clientFD[myID],enter,strlen(enter)) == -1);
		}
	}
	return uniqueCount;
}

int selectNormal(char * query,int myID){
	int count;
	int star = 0;
	int start = 0;
	while(query[start] != ' ')
		++start;
	while(query[start] == ' ')
		++start;
	if(query[start] == '*')
		star = 1;
	if(star){
		count = columnCount;
	}
	else{
		count = 1;
		for (int i = 0; i < strlen(query); ++i){
			if(query[i] == ','){
				++count;

			}
		}
	}
	int index[count];
	if(star){
		for (int i = 0; i < count; ++i){
			index[i] = i;
		}
	}
	else{
		char key[count][512];
		int cur = start;
		for (int i = 0; i < count; ++i){
			int tempCur = 0;
			while(query[cur] != ',' && query[cur] != ' '){
				key[i][tempCur] = query[cur];
				++tempCur;
				++cur;
			}
			key[i][tempCur] = '\0';
			while(query[cur] == ',' || query[cur] == ' ')
				++cur;
		}
		for (int i = 0; i < count; ++i){
			int tempIndex = 0;
			while(1){
				int found = 0;
				if(strncmp(dataset[0][tempIndex],key[i],strlen(key[i])) == 0){
					found = 1;
					for (int j = strlen(key[i]); j < strlen(dataset[0][tempIndex]); ++j){
						if(dataset[0][tempIndex][j] != ' '){
							found = 0;
							break;
						}
					}
				}
				if(found)
					break;
				++tempIndex;
			}
			index[i] = tempIndex;
		}
	}
	int rowSend = rowCount-1;
	while(write(clientFD[myID],&rowSend,sizeof(int)) == -1);
	int len = 1;
	for (int i = 0; i < count; ++i){
		len += strlen(dataset[0][index[i]]);
	}
	while(write(clientFD[myID],&len,sizeof(int)) == -1);
	for (int i = 0; i < rowCount; ++i){
		for (int j = 0; j < count; ++j){
			while(write(clientFD[myID],dataset[i][index[j]],strlen(dataset[i][index[j]])) == -1);
		}
		while(write(clientFD[myID],enter,strlen(enter)) == -1);
	}
	return rowSend;
}

int update(char * query, int myID){
	int affectedCount = 0;
	int count = 1;
	for (int i = 0; i < strlen(query); ++i){
		if(query[i] == ','){
			++count;
		}
	}
	int start = 0;
	for (int i = 0; i < 3; ++i){
		while(query[start] != ' ')
			++start;
		while(query[start] == ' ')
			++start;
	}
	int index[count];
	char key[count][512];
	char value[count][512];
	int cur = 17;
	for (int i = 0; i < count; ++i){
		int tempCur = 0;
		while(query[cur] != '=' && query[cur] != ' '){
			key[i][tempCur] = query[cur];
			++tempCur;
			++cur;
		}
		key[i][tempCur] = '\0';
		while(query[cur] != '\'')
			++cur;
		++cur;
		tempCur = 0;
		while(query[cur] != '\''){
			if(query[cur] == '\n'){
				value[i][tempCur] = '\\';
				++tempCur;
				value[i][tempCur] = 'n';
				++tempCur;
				++cur;
			}
			else if(query[cur] == '\r'){
				value[i][tempCur] = '\\';
				++tempCur;
				value[i][tempCur] = 'r';
				++tempCur;
				++cur;
			}
			else{
				value[i][tempCur] = query[cur];
				++tempCur;
				++cur;
			}
		}
		++cur;
		value[i][tempCur] = '\0';
		while(query[cur] == ',' || query[cur] == ' ')
			++cur;
	}
	while(query[cur] != ' ')
			++cur;
	while(query[cur] == ' ')
		++cur;
	char condKey[512];
	char condValue[512];
	int condIndex;
	int tempCur = 0;
	while(query[cur] != ' ' && query[cur] != '='){
		condKey[tempCur] = query[cur];
		++tempCur;
		++cur;
	}
	condKey[tempCur] = '\0';
	while(query[cur] != '\'')
		++cur;
	++cur;
	tempCur = 0;
	while(query[cur] != '\''){
		if(query[cur] == '\n'){
			condValue[tempCur] = '\\';
			++tempCur;
			condValue[tempCur] = 'n';
			++tempCur;
			++cur;
		}
		else if(query[cur] == '\r'){
			condValue[tempCur] = '\\';
			++tempCur;
			condValue[tempCur] = 'r';
			++tempCur;
			++cur;
		}
		else{
			condValue[tempCur] = query[cur];
			++tempCur;
			++cur;
		}
	}
	condValue[tempCur] = '\0';
	for (int i = 0; i < count; ++i){
		int tempIndex = 0;
		while(1){
			int found = 0;
			if(strncmp(dataset[0][tempIndex],key[i],strlen(key[i])) == 0){
				found = 1;
				for (int j = strlen(key[i]); j < strlen(dataset[0][tempIndex]); ++j){
					if(dataset[0][tempIndex][j] != ' '){
						found = 0;
						break;
					}
				}
			}
			if(found)
				break;
			++tempIndex;
		}
		index[i] = tempIndex;
	}
	int tempIndex = 0;
	while(1){
		int found = 0;
		if(strncmp(dataset[0][tempIndex],condKey,strlen(condKey)) == 0){
			found = 1;
			for (int j = strlen(condKey); j < strlen(dataset[0][tempIndex]); ++j){
				if(dataset[0][tempIndex][j] != ' '){
					found = 0;
					break;
				}
			}
		}
		if(found)
			break;
		++tempIndex;
	}
	condIndex = tempIndex;
	for (int i = 0; i < count; ++i){
		int len = strlen(value[i]);
		value[i][len] = ' ';
		value[i][len+1] = '\0';
	}
	for (int i = 1; i < rowCount; ++i){
		int found = 0;
		if(strncmp(dataset[i][condIndex],condValue,strlen(condValue)) == 0){
			found = 1;
			for (int j = strlen(condValue); j < strlen(dataset[0][tempIndex]); ++j){
				if(dataset[i][condIndex][j] != ' '){
					found = 0;
					break;
				}
			}
		}
		if (found){
			for (int j = 0; j < count; ++j){
				strcpy(dataset[i][index[j]],value[j]);
			}
			++affectedCount;
		}
	}
	for (int j = 0; j < count; ++j){
		int max = -1;
		for (int i = 0; i < rowCount; ++i){
			int tempMax = strlen(dataset[i][index[j]]);
			if(tempMax > max){
				max = tempMax;
			}
		}
		for (int i = 0; i < rowCount; ++i){
			int len = strlen(dataset[i][index[j]]);
			while(len < max){
				strcat(dataset[i][index[j]]," ");
				++len;
			}
		}
	}
	write(clientFD[myID],&affectedCount,sizeof(int));
	return affectedCount;
}