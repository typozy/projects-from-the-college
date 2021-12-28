#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int foundNum = 0;

int fCheck = 0;
int bCheck = 0;
int tCheck = 0;
int pCheck = 0;
int lCheck = 0;
int wCheck = 0;

char * path = NULL;

int byteNum = 0;
int linkNum = 0;
char * theKey = NULL;
char perm[10];
char type;

struct nameList{
	char name[100];
	int depth;
	struct nameList * next;
};

struct nameList * myNameList = NULL;

int strToInt(char * str);

int comparator(char * name, char * key);

int dirSize(char * path);

void innerFunction(char * inner, int depth, int folderFound);

void handlerSigInt(){
	struct nameList * tempList2 = myNameList;
	struct nameList * tempList3;
	while(tempList2 != NULL){
		tempList3 = tempList2;
		tempList2 = tempList2->next;
		free(tempList3);
	}
	myNameList = NULL;
	if(theKey != NULL)
		free(theKey);
	if(path != NULL)
		free(path);
	write(1,"\nSIGINT handled...\n",19);
	exit(-1);
}

int main(int argc, char *argv[]){
	signal(SIGINT,handlerSigInt);
	int optFlag = 6;
	int opt;
	for(int i=0; i<6; ++i){
		if((opt = getopt(argc,argv,"f:b:t:p:l:w:")) == -1){
			optFlag = i;
			break;
		}
		switch(opt){
			case 'f':
				if(!fCheck){
					theKey = (char *) malloc(50);
					strcpy(theKey,optarg);
					fCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					if(path)
						free(path);
					if(theKey)
						free(theKey);
					exit(-1);
				}
				break;
			case 'b':
				if(!bCheck){
					byteNum = strToInt(optarg);
					bCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					if(path)
						free(path);
					if(theKey)
						free(theKey);
					exit(-1);
				}
				break;
			case 't':
				if(!tCheck){
					type = optarg[0];
					tCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					if(path)
						free(path);
					if(theKey)
						free(theKey);
					exit(-1);
				}
				break;
			case 'w':
				if(!wCheck){
					path = (char *) malloc(2000);
					strcpy(path,optarg);
					if(strcmp(path,"/") == 0){
						path[0] = '/';
						path[1] = '\0';
					}
					else if(strcmp(path,".") == 0){
						getcwd(path,2000);
					}
					else if(strcmp(path,"..") == 0){
						getcwd(path,2000);
						for (int i = strlen(path)-1; i > -1; --i){
							if(path[i] == '/'){
								path[i] = '\0';
								break;
							}	
						}
					}
					else if(path[0] != '/'){
						int cursor = strlen(path)-1;
						if(path[cursor] == '/')
							path[cursor] = '\0';
						char temp[2000];
						strcpy(temp,path);
						getcwd(path,2000);
						strcat(path,"/");
						strcat(path,temp);
					}
					else{
						int cursor = strlen(path)-1;
						if(path[cursor] == '/')
							path[cursor] = '\0';
					}
					DIR * dir;
					if((dir = opendir(path)) == NULL){
						write(2,"There is no folder with this path\n",34);
						if(path)
							free(path);
						if(theKey)
							free(theKey);
						exit(-1);
					}
					closedir(dir);
					wCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					if(path)
						free(path);
					if(theKey)
						free(theKey);
					exit(-1);
				}
				break;
			case 'l':
				if(!lCheck){
					linkNum = strToInt(optarg);
					lCheck = 1;
				}
				else{
					write(2,"More than one input from the same option\n",41);
					if(path)
						free(path);
					if(theKey)
						free(theKey);
					exit(-1);
				}
				break;
			case 'p':
				if(!pCheck){
					if(strlen(optarg) < 10){
						strcpy(perm,optarg);
						pCheck = 1;
					}
					else{
						write(2,"Permission input is too long\n",29);
						if(path)
							free(path);
						if(theKey)
							free(theKey);
						exit(-1);
					}
				}
				else{
					write(2,"More than one input from the same option\n",41);
					if(path)
						free(path);
					if(theKey)
						free(theKey);
					exit(-1);
				}
				break;
			default:
				write(2,"Wrong argument type\n",20);
				if(path)
					free(path);
				if(theKey)
					free(theKey);
				exit(-1);
		}
	}
	if(optFlag < 2){
		write(2,"There are missed parameter(s)\n",30);
		if(path)
			free(path);
		if(theKey)
			free(theKey);
		exit(-1);
	}
	else if(optFlag < 6){
		if(!wCheck){
			write(2,"Path is not entered\n",20);
			if(path)
				free(path);
			if(theKey)
				free(theKey);
			exit(-1);
		}
	}
	else if((opt = getopt(argc,argv,"")) != -1){
		write(2,"There are extra arguments\n",26);
		if(path)
			free(path);
		if(theKey)
			free(theKey);
		exit(-1);
	}
	innerFunction(path,0,0);
	if(!foundNum)
		write(1,"No file found\n",14);
	if(theKey != NULL)
		free(theKey);
	if(path != NULL)
		free(path);
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

int comparator(char * name, char * key){
	int i = 0;
	int j = 0;
	while(name[i] != '\0' && key[j] != '\0'){
		int flag = 0;
		char tempChar = '\0';
		if(key[j] >= 'A' && key[j] <= 'Z'){
			tempChar = key[j] + ('a' - 'A');
		}
		else if(key[j] >= 'a' && key[j] <= 'z'){
			tempChar = key[j] + ('A' - 'a');
		}
		else{
			tempChar = key[j];
		}
		int k = j;
		int count = 0;
		while(key[k] == '+' || key[k] == key[j] || key[k] == tempChar){
			if(key[k] == '+')
				flag = 1;
			if(key[k] == key[j] || key[k] == tempChar)
				++count;
			++k;
		}
		int l = i;
		int m = l+count;
		while(l<m){
			if(name[l] != key[j] && name[l] != tempChar){
				return -1;
			}
			++l;
		}
		if(flag){
			while(name[l] == key[j] || name[l] == tempChar){
				++l;
			}
		}
		i = l;
		j = k;
	}
	if (name[i] != '\0' || key[j] != '\0'){
		return -1;
	}
	return 0;
}

int dirSize(char * path){
	struct stat fileStat;
	struct dirent *files;
	char * temp = (char*)malloc(2000);
	DIR *dir = opendir(path);
	int total = 0;
	while ((files = readdir(dir)) != NULL){
		if(strcmp((char *)(&files->d_name),".") != 0 && strcmp((char *)(&files->d_name),"..") != 0){
			strcpy(temp,path);
			strcat(temp,"/");
			strcat(temp,(char *)(&files->d_name));
			if(!stat(temp,&fileStat)){
				if(S_ISDIR(fileStat.st_mode)){
					DIR *dir2;
					if((dir2 = opendir(temp)) != NULL){
						closedir(dir2);
						total += dirSize(temp);
					}
				}
				else
					total += fileStat.st_size;
			}
		}
	}
	closedir(dir);
	free(temp);
	return total;
}

void innerFunction(char * inner, int depth, int folderFound){
	if(!folderFound){
		int k = 0;
		for (int i = strlen(inner)-1; i > -1; --i){
			if(inner[i] == '/'){
				k = i+1;
				break;
			}
		}
		struct nameList * tempList;
		if(myNameList == NULL){
			myNameList = (struct nameList *)malloc(sizeof(struct nameList));
			tempList = myNameList;
		}
		else{
			tempList = myNameList;
			while(tempList->next != NULL){
				tempList = tempList->next;
			}
			tempList->next = (struct nameList *)malloc(sizeof(struct nameList));
			tempList = tempList->next;
		}
		if(strcmp(inner,"/") == 0){
			tempList->name[0] = '/';
			tempList->name[1] = '\0';
		}else{
			int i = 0;
			while(inner[k] != '\0'){
				tempList->name[i] = inner[k];
				++i;
				++k;
			}
			tempList->name[i] = '\0';
		}
		tempList->depth = depth;
		tempList->next = NULL;
	}
	struct stat fileStat;
	struct dirent *files;
	char * temp = (char*)malloc(2000);
	DIR *dir = opendir(inner);
	while ((files = readdir(dir)) != NULL){
		if(strcmp((char *)(&files->d_name),".") != 0 && strcmp((char *)(&files->d_name),"..") != 0){
			strcpy(temp,inner);
			if(strcmp(inner,"/") != 0)
				strcat(temp,"/");
			strcat(temp,(char *)(&files->d_name));
			stat(temp,&fileStat);
			if(!stat(temp,&fileStat)){
				int folderFlag = 0;
				int fFlag = 1;
				int bFlag = 1;
				int tFlag = 1;
				int pFlag = 1;
				int lFlag = 1;
				if(pCheck){
					pFlag = 0;
					char permissions[10];
					permissions[0] = '\0';
					strcat(permissions, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
					strcat(permissions, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
					strcat(permissions, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
					strcat(permissions, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
					strcat(permissions, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
					strcat(permissions, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
					strcat(permissions, (fileStat.st_mode & S_IROTH) ? "r" : "-");
					strcat(permissions, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
					strcat(permissions, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
					if(strcmp(perm,permissions) == 0)
						pFlag = 1;
				}
				if(fCheck){
					fFlag = 0;
					if(comparator((char *)(&files->d_name),theKey) == 0)
						fFlag = 1;
				}
				if (bCheck){
					bFlag = 0;
					int refNum = 0;
					if(S_ISDIR(fileStat.st_mode)){
						DIR *dir2;
						if((dir2 = opendir(temp)) != NULL){
							closedir(dir2);
							refNum = dirSize(temp);
						}
					}
					else{
						refNum = fileStat.st_size;
					}
					if(refNum == byteNum)
						bFlag = 1;
				}
				if (tCheck){
					tFlag = 0;
					switch(type){
						case 'd':
							if(S_ISDIR(fileStat.st_mode))
								tFlag = 1;
							break;
						case 's':
							if(S_ISSOCK(fileStat.st_mode))
								tFlag = 1;
							break;
						case 'b':
							if(S_ISBLK(fileStat.st_mode))
								tFlag = 1;
							break;
						case 'c':
							if(S_ISCHR(fileStat.st_mode))
								tFlag = 1;
							break;
						case 'f':
							if(S_ISREG(fileStat.st_mode))
								tFlag = 1;
							break;
						case 'p':
							if(S_ISFIFO(fileStat.st_mode))
								tFlag = 1;
							break;
						case 'l':
							if(S_ISLNK(fileStat.st_mode))
								tFlag = 1;
							break;
						default:
							break;
					}
				}
				if(lCheck){
					lFlag = 0;
					if(fileStat.st_nlink == linkNum)
						lFlag = 1;
				}
				if(pFlag && fFlag && bFlag && tFlag && lFlag){
					++foundNum;
					folderFlag = 1;
					struct nameList * tempList2 = myNameList;
					char foundPath[2000];
					char foundName[100];
					while(tempList2 != NULL){
						foundPath[0] = '\0';
						if(tempList2->depth != 0)
							strcat(foundPath,"|");
						for (int i = 0; i < tempList2->depth; ++i){
							strcat(foundPath,"--");
						}
						sprintf(foundName,"%s\n",tempList2->name);
						strcat(foundPath,foundName);
						write(1,foundPath,strlen(foundPath));
						tempList2 = tempList2->next;
					}
					foundPath[0] = '\0';
					strcat(foundPath,"|");
					for (int i = 0; i < depth+1; ++i){
						strcat(foundPath,"--");
					}
					sprintf(foundName,"\033[1m%s\033[0m\n",(char *)(&files->d_name));
					strcat(foundPath,foundName);
					write(1,foundPath,strlen(foundPath));
					tempList2 = myNameList;
					struct nameList * tempList3;
					while(tempList2 != NULL){
						tempList3 = tempList2;
						tempList2 = tempList2->next;
						free(tempList3);
					}
					myNameList = NULL;
				}
				if(S_ISDIR(fileStat.st_mode)){
					DIR *dir2;
					if((dir2 = opendir(temp)) != NULL){
						closedir(dir2);
						innerFunction(temp,depth+1,folderFlag);
					}
				}
			}
		}
	}
	closedir(dir);
	if(myNameList != NULL){
		if(myNameList->next == NULL){
			if (myNameList->depth == depth){
				free(myNameList);
				myNameList = NULL;
			}
		}
		else{
			struct nameList * tempList4 = myNameList;
			while(tempList4->next->next != NULL)
				tempList4 = tempList4->next;
			if(tempList4->next->depth == depth){
				free(tempList4->next);
				tempList4->next = NULL;
			}
		}
	}
	free(temp);	
	return;
}