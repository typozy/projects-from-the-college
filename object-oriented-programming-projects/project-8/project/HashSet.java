/**
 * HashSet is a set type container that it does not insist the same elements
 * 
 * @author Tayfun
 *
 * @param <T> parametrized container type
 */
public class HashSet <T> implements Set <T> {
	
	private T[] container;
	private int size;
	
	public HashSet(){
		container = null;
		size = 0;
	}
	
	
	public T getElem(int index){
		return container[index];
	}
	public T[] getContainer(){
		return container;
	}
	public void setContainer(T[] con){
		container = con;
	}
	public int getSize(){
		return size;
	}
	public void setSize(int sz){
		size = sz;
	}

	public Iterator<T> iterator(){
		Iterator <T> it = new Iterator<T>(this,0);
		return it;
	}


	public void add(T e){
		boolean found = false;
		for (int i=0; i<size; ++i){
			if(container[i] == e){
				found = true;
				break;
			}
		}
		if (!found){
			T[] temp = (T[]) new Object[size+1];
			for(int i = 0; i < size; ++i){
				temp[i] = container[i];
			}
			temp[size] = e;
			container = temp;
			++size;
		}
	}


	public void addAll(Collection<T> c){
		T[] tempcon = c.getContainer();
		int tempsize = c.getSize();
		for (int i = 0; i < tempsize; ++i){
			boolean found = false;
			for (int j = 0; j < size; ++j){
				if(tempcon[i] == container[j]){
					found = true;
					break;
				}
			}
			if(!found){
				T[] newcon =(T[]) new Object[size+1];
				for(int k=0; k<size; ++k)
					newcon[k] = container[k];
				newcon[size] = tempcon[i];
				container = newcon;
				++size;
			}
		}
	}


	public void clear(){
		size = 0;
	}


	public boolean contains(T e){
		boolean found = false;
		for (int i=0; i<size; ++i){
			if(container[i] == e){
				found = true;
				break;
			}
		}
		return found;
	}


	public boolean containsAll(Collection<T> c){
		T[] tempcon = c.getContainer();
		int tempsize = c.getSize();
		for (int i=0; i<tempsize; ++i){
			boolean found = false;
			for (int j=0; j<size; ++j){
				if(tempcon[i] == container[j]){
					found = true;
					break;
				}
			}
			if(!found)
				return false;
		}
		return true;
	}


	public boolean isEmpty(){
		return (size == 0);
	}


	public void remove(T e){
		for (int i=0; i<size; ++i){
			if(container[i] == e){
				T[] temp = (T[]) new Object[size-1];
				for(int j=0; j<i; ++j){
					temp[j] = container[j];
				}
				for(int j=i; j<size-1; ++j){
					temp[j] = container[j+1];
				}
				container = temp;
				--size;
				return;
			}
		}
		return;
	}


	public void removeAll(Collection<T> c){
		T[] tempcon = c.getContainer();
		int tempsize = c.getSize();
		for (int i=0; i<tempsize; ++i){
			for (int j=0; j<size; ++j){
				if (tempcon[i] == container[j]){
					T[] temp = (T[]) new Object[size-1];
					for(int k=0; k<j; ++k){
						temp[k] = container[k];
					}
					for(int k=j; k<size-1; ++k){
						temp[k] = container[k+1];
					}
					container = temp;
					--size;
					break;
				}
			}
		}
	}


	public void retainAll(Collection<T> c){
		T[] tempcon = c.getContainer();
		int tempsize = c.getSize();
		for (int i=0; i<size; ++i){
			boolean found = false;
			for (int j=0; j<tempsize; ++j){
				if (container[i] == tempcon[j]){
					found = true;
					break;
				}
			}
			if(!found){
				T[] temp = (T[]) new Object[size-1];
				for(int j=0; j<i; ++j){
					temp[j] = container[j];
				}
				for(int j=i; j<size-1; ++j){
					temp[j] = container[j+1];
				}
				container = temp;
				--size;
				--i;
			}
		}
	}


	public int size(){
		return size;
	}
	
	
}