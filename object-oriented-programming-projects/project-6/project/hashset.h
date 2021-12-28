#ifndef HASHSET_H_
#define HASHSET_H_

namespace SpaceCollection
{
template<class E, class C>
class HashSet : public Set<E,C>{
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
};
//	end of SpaceCollection namespace
}

#endif