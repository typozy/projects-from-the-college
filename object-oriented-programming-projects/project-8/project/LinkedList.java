/**
 * LinkedList is a queue type container that uses first in first out method
 * 
 * @author Tayfun
 *
 * @param <T> parametrized container type
 */
public class LinkedList<T> implements List<T>, Queue<T> {
	
	private T[] container;
	private int size;
	
	public LinkedList(){
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
		T[] temp = (T[]) new Object[size+1];
		for(int i = 0; i < size; ++i){
			temp[i] = container[i];
		}
		temp[size] = e;
		container = temp;
		++size;
	}


	public void addAll(Collection<T> c){
		T[] tempcon = c.getContainer();
		int tempsize = c.getSize();
		T[] temp = (T[]) new Object[size+tempsize];
		for (int i=0; i<size; ++i){
			temp[i] = container[i];
		}
		for (int i=size; i<size+tempsize; ++i){
			temp[i] = tempcon[i-size];
		}
		container = temp;
		size = size + tempsize;
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
	
	public T element(){
		return container[0];
	}

	public void offer(T e){
		T[] temp = (T[]) new Object[size+1];
		for(int i = 0; i < size; ++i){
			temp[i] = container[i];
		}
		temp[size] = e;
		container = temp;
		++size;
	}

	public T poll() throws MyErrors{
		if (size == 0)
			throw new MyErrors(-2);
		T elem = container[0];
		T[] temp = (T[]) new Object[size-1];
		for(int i=0; i<size-1; ++i){
			temp[i] = container[i+1];
		}
		container = temp;
		--size;
		return elem;
	}
	
}