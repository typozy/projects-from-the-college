#ifndef MYERRORS_H_
#define MYERRORS_H_

namespace SpaceCollection
{
class MyErrors{
private:
	int errType;
public:
	MyErrors(){}
	MyErrors(int theErr):errType(theErr){}
	void what();
};

void MyErrors::what(){
	switch (errType){
		case -1:
			cerr << "You are out of range!" << endl;
			break;
		case -2:
			cerr << "The collection is empty!" << endl;
			break;
	}
}
//	end of SpaceCollection namespace
}

#endif