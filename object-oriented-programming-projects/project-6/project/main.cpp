#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <typeinfo>

using namespace std;

#include "myerrors.h"
#include "collection.h"
#include "set.h"
#include "list.h"
#include "queue.h"
#include "hashset.h"
#include "arraylist.h"
#include "linkedlist.h"
#include "iterator.h"
#include "hashset.cpp"
#include "arraylist.cpp"
#include "linkedlist.cpp"
#include "iterator.cpp"

using namespace SpaceCollection;

//	c++11 does not support template as a template parameter

#include "hashsettest.cpp"
#include "arraylisttest.cpp"
#include "linkedlisttest.cpp"

int main(){
	HashSetVec();
	HashSetVecStr();
	HashSetList();
	HashSetListStr();
	HashSetSet();
	HashSetSetStr();
	ArrayListVec();
	ArrayListVecStr();
	ArrayListList();
	ArrayListListStr();
	ArrayListSet();
	ArrayListSetStr();
	LinkedListVec();
	LinkedListVecStr();
	LinkedListList();
	LinkedListListStr();
	LinkedListSet();
	LinkedListSetStr();
	return 0;
}

