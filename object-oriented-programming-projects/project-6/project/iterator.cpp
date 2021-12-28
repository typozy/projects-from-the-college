

namespace SpaceCollection
{
template<class E, class C>
bool Iterator<E,C>::hasNext(){
	return (size - index > 0);
}

template<class E, class C>
E Iterator<E,C>::next(){
	if(!hasNext())
		throw MyErrors(-1);
	auto it = iterator;
	auto elem = *iterator;
	++index;
	++it;
	iterator = it;
	return elem;
}

template<class E, class C>
void Iterator<E,C>::remove(){
	if (size == 0)
		throw MyErrors(-2);
	if (typeid(vector<E> *) == typeid(conPtr)){
		--iterator;
		--index;
		--size;
		conPtr->erase(iterator);
	}
	else{
		auto it = iterator;
		--index;
		--size;
		--it;
		conPtr->erase(it);
	}
}
//	end of SpaceCollection namespace
}