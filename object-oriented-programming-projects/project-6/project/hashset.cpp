

namespace SpaceCollection
{
template<class E, class C>
Iterator<E,C> HashSet<E,C>::iterator(){
	Iterator<E,C> it;
	it.iterator = container.begin();
	it.size = container.size();
	it.index = 0;
	it.conPtr = &container;
	return it;
}

template<class E, class C>
void HashSet<E,C>::add(E e){
	bool found = false;
	for (auto i = container.begin(); i != container.end(); ++i){
		if(*i == e){
			found = true;
			break;
		}
	}
	if (!found){
		auto j = container.end();
		container.insert(j,e);
	}
}

template<class E, class C>
void HashSet<E,C>::addAll(Collection<E,C> & c){
	HashSet<E,C> * hsp = dynamic_cast<HashSet<E,C> *>(&c);
	for (auto i = hsp->container.begin(); i != hsp->container.end(); ++i){
		bool found = false;
		for (auto j = container.begin(); j != container.end(); ++j){
			if(*i == *j){
				found = true;
				break;
			}
		}
		if(!found){
			auto k = container.end();
			container.insert(k,*i);
		}
	}
}

template<class E, class C>
void HashSet<E,C>::clear(){
	container.clear();
}

template<class E, class C>
bool HashSet<E,C>::contains(E e){
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
bool HashSet<E,C>::containsAll(Collection<E,C> & c){
	HashSet<E,C> * hsp = dynamic_cast<HashSet<E,C> *>(&c);
	for (auto i = hsp->container.begin(); i != hsp->container.end(); ++i){
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
bool HashSet<E,C>::isEmpty(){
	return (container.size() == 0);
}

template<class E, class C>
void HashSet<E,C>::remove(E e){
	for (auto i = container.begin(); i != container.end(); ++i){
		if(*i == e){
			container.erase(i);
			return;
		}
	}
	return;
}

template<class E, class C>
void HashSet<E,C>::removeAll(Collection<E,C> & c){
	HashSet<E,C> * hsp = dynamic_cast<HashSet<E,C> *>(&c);
	for (auto i = hsp->container.begin(); i != hsp->container.end(); ++i){
		for (auto j = container.begin(); j != container.end(); ++j){
			if (*i == *j){
				container.erase(j);
				break;
			}
		}
	}
}

template<class E, class C>
void HashSet<E,C>::retainAll(Collection<E,C> & c){
	HashSet<E,C> * hsp = dynamic_cast<HashSet<E,C> *>(&c);
	for (auto i = container.begin(); i != container.end(); ++i){
		bool found = false;
		for (auto j = hsp->container.begin(); j != hsp->container.end(); ++j){
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
int HashSet<E,C>::size(){
	return container.size();
}
//	end of SpaceCollection namespace
}