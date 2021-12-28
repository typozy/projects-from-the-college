#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

namespace SpaceCollection
{
template<class E, class C>
class LinkedList : public List<E,C>, public Queue<E,C>{
private:
	C container;
public:
	Iterator<E,C> iterator();
	void add(E e);
	void addAll(Collection<E,C> & c);
	void clear();
	bool contains(E e);
	bool containsAll(Collection<E,C> & c);
	bool isEmpty();
	void remove(E e);
	void removeAll(Collection<E,C> & c);
	void retainAll(Collection<E,C> & c);
	int size();
	E element();
	void offer(E e);
	E poll();
};
//	end of SpaceCollection namespace
}

#endif