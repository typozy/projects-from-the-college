#ifndef ITERATOR_H_
#define ITERATOR_H_

namespace SpaceCollection
{
template<class E, class C>
class Iterator{
private:
	C * conPtr;
	class C::iterator iterator;
	int index;
	int size;
public:
	friend class HashSet<E,C>;
	friend class ArrayList<E,C>;
	friend class LinkedList<E,C>;
	bool hasNext();
	E next();
	void remove();
};
//	end of SpaceCollection namespace
}

#endif