

namespace SpaceCollection
{
template<class E, class C>
Iterator<E,C> ArrayList<E,C>::iterator(){
	Iterator<E,C> it;
	it.iterator = container.begin();
	it.size = container.size();
	it.index = 0;
	it.conPtr = &container;
	return it;
}

template<class E, class C>
void ArrayList<E,C>::add(E e){
	auto i = container.end();
	container.insert(i,e);
}

template<class E, class C>
void ArrayList<E,C>::addAll(Collection<E,C> & c){
	ArrayList<E,C> * alp = dynamic_cast<ArrayList<E,C> *>(&c);
	for (auto i = alp->container.begin(); i != alp->container.end(); ++i){
		container.insert(container.end(),*i);
	}
}

template<class E, class C>
void ArrayList<E,C>::clear(){
	container.clear();
}

template<class E, class C>
bool ArrayList<E,C>::contains(E e){
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
bool ArrayList<E,C>::containsAll(Collection<E,C> & c){
	ArrayList<E,C> * alp = dynamic_cast<ArrayList<E,C> *>(&c);
	for (auto i = alp->container.begin(); i != alp->container.end(); ++i){
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
bool ArrayList<E,C>::isEmpty(){
	return (container.size() == 0);
}

template<class E, class C>
void ArrayList<E,C>::remove(E e){
	for (auto i = container.begin(); i != container.end(); ++i){
		if(*i == e){
			container.erase(i);
			return;
		}
	}
	return;
}

template<class E, class C>
void ArrayList<E,C>::removeAll(Collection<E,C> & c){
	ArrayList<E,C> * alp = dynamic_cast<ArrayList<E,C> *>(&c);
	for (auto i = alp->container.begin(); i != alp->container.end(); ++i){
		for (auto j = container.begin(); j != container.end(); ++j){
			if (*i == *j){
				container.erase(j);
				break;
			}
		}
	}
}

template<class E, class C>
void ArrayList<E,C>::retainAll(Collection<E,C> & c){
	ArrayList<E,C> * alp = dynamic_cast<ArrayList<E,C> *>(&c);
	for (auto i = container.begin(); i != container.end(); ++i){
		bool found = false;
		for (auto j = alp->container.begin(); j != alp->container.end(); ++j){
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
int ArrayList<E,C>::size(){
	return container.size();
}
//	end of SpaceCollection namespace
}