

namespace SpaceCollection
{
template<class E, class C>
Iterator<E,C> LinkedList<E,C>::iterator(){
	Iterator<E,C> it;
	it.iterator = container.begin();
	it.size = container.size();
	it.index = 0;
	it.conPtr = &container;
	return it;
}

template<class E, class C>
void LinkedList<E,C>::add(E e){
	auto i = container.end();
	container.insert(i,e);
}

template<class E, class C>
void LinkedList<E,C>::addAll(Collection<E,C> & c){
	LinkedList<E,C> * llp = dynamic_cast<LinkedList<E,C> *>(&c);
	for (auto i = llp->container.begin(); i != llp->container.end(); ++i){
		container.insert(container.end(),*i);
	}
}

template<class E, class C>
void LinkedList<E,C>::clear(){
	container.clear();
}

template<class E, class C>
bool LinkedList<E,C>::contains(E e){
	bool found = false;
	for (auto i = container.begin(); i != container.end(); ++i){
		if(*i == e){
			found = true;
			break;
		}
	}
	return found;
}

template<class E, class C>
bool LinkedList<E,C>::containsAll(Collection<E,C> & c){
	LinkedList<E,C> * llp = dynamic_cast<LinkedList<E,C> *>(&c);
	for (auto i = llp->container.begin(); i != llp->container.end(); ++i){
		int found = false;
		for (auto j = container.begin(); j != container.end(); ++j){
			if(*i == *j){
				found = true;
				break;
			}
		}
		if(!found)
			return false;
	}
	return true;
}

template<class E, class C>
bool LinkedList<E,C>::isEmpty(){
	return (container.size() == 0);
}

template<class E, class C>
void LinkedList<E,C>::remove(E e){
	for (auto i = container.begin(); i != container.end(); ++i){
		if(*i == e){
			container.erase(i);
			return;
		}
	}
	return;
}

template<class E, class C>
void LinkedList<E,C>::removeAll(Collection<E,C> & c){
	LinkedList<E,C> * llp = dynamic_cast<LinkedList<E,C> *>(&c);
	for (auto i = llp->container.begin(); i != llp->container.end(); ++i){
		for (auto j = container.begin(); j != container.end(); ++j){
			if (*i == *j){
				container.erase(j);
				break;
			}
		}
	}
}

template<class E, class C>
void LinkedList<E,C>::retainAll(Collection<E,C> & c){
	LinkedList<E,C> * llp = dynamic_cast<LinkedList<E,C> *>(&c);
	for (auto i = container.begin(); i != container.end(); ++i){
		bool found = false;
		for (auto j = llp->container.begin(); j != llp->container.end(); ++j){
			if (*i == *j){
				found = true;
				break;
			}
		}
		if(!found){
			container.erase(i);
			--i;
		}
	}
}

template<class E, class C>
int LinkedList<E,C>::size(){
	return container.size();
}

template<class E, class C>
E LinkedList<E,C>::element(){
	auto i = container.begin();
	E temp = *i;
	return temp;
}

template<class E, class C>
void LinkedList<E,C>::offer(E e){
	auto i = container.end();
	container.insert(i,e);
}

template<class E, class C>
E LinkedList<E,C>::poll(){
	if (container.size() == 0)
		throw MyErrors(-2);
	auto i = container.begin();
	E temp = *i;
	container.erase(i);
	return temp;
}
//	end of SpaceCollection namespace
}