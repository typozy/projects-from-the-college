#ifndef MYERRORS_H_
#define MYERRORS_H_

class MyErrors{
public:
	MyErrors(){}
	MyErrors(int myErr)
		:errType(myErr){}
	void what(){
		switch (errType){
			case -1:
				std::cerr << "The index you confirmed is out of range!" << std::endl;
				break;
			case -2:
				std::cerr << "You cannot have a position with negative value!" << std::endl;
				break;
			case -3:
				std::cerr << "You cannot construct a rectangle with a width length of less than 1!" << std::endl;
				break;
			case -4:
				std::cerr << "You cannot construct a rectangle with a height length of less than 1!" << std::endl;
				break;
			case -5:
				std::cerr << "You cannot construct a circle with a radius length of less than 1!" << std::endl;
				break;
			case -6:
				std::cerr << "You cannot construct a triangle with an edge length of less than 1!" << std::endl;
				break;
		}		
	}
private:
	int errType;
};

#endif