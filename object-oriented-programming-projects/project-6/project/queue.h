#ifndef QUEUE_H_
#define QUEUE_H_

namespace SpaceCollection
{
template<class E, class C>
class Queue : virtual public Collection<E,C>{
public:
	virtual void add(E e) = 0;
	virtual E element() = 0;
	virtual void offer(E e) = 0;
	virtual E poll() = 0;
};
//	end of SpaceCollection namespace
}

#endif