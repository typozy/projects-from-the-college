#ifndef COLLECTION_H_
#define COLLECTION_H_

namespace SpaceCollection
{
//forward declaration of Iterator class
template<class E, class C> class Iterator;

template<class E, class C>
class Collection{
public:
	virtual Iterator<E,C> iterator() = 0;
	virtual void add(E e) = 0;
	virtual void addAll(Collection<E,C> & c) = 0;
	virtual void clear() = 0;
	virtual bool contains(E e) = 0;
	virtual bool containsAll(Collection<E,C> & c) = 0;
	virtual bool isEmpty() = 0;
	virtual void remove(E e) = 0;
	virtual void removeAll(Collection<E,C> & c) = 0;
	virtual void retainAll(Collection<E,C> & c) = 0;
	virtual int size() = 0;
};
//	end of SpaceCollection namespace
}

#endif