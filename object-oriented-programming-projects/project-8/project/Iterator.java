/**
 * Iterator class is a generic class that iterates any of the collection objects
 * depending on their container type
 * 
 * @author Tayfun
 *
 * @param <T> type that the assigned collection object holds and iterator will amnipulate
 */
public class Iterator<T>{
	private Collection<T> col;
	private int index;
	
	Iterator(){
		col = null;
		index = 0;
	}
	
	Iterator(Collection<T> collection, int in){
		col = collection;
		index = in;
	}
	/**
	 * hasNext checks if there is any more element in the container
	 * 
	 * @return the result
	 */
	boolean hasNext(){
		return (col.getSize() - index > 0);
	}
	/**
	 * next gives the next element from the container
	 * 
	 * @return the element which type is parametrized
	 */
	public T next() throws MyErrors{
		if(!hasNext())
			throw new MyErrors(-1);
		T elem = col.getElem(index);
		++index;
		return elem;
	}
	/**
	 * remove erases the last reached element
	 * 
	 */
	void remove() throws MyErrors{
		if (col.getSize() == 0)
			throw new MyErrors(-2);
		T[] constcon = col.getContainer();
		T[] tempcon = (T[]) new Object[col.getSize()-1];
		--index;
		for(int i=0; i<index; ++i){
			tempcon[i] = constcon[i];
		}
		for(int i=index; i<col.getSize()-1; ++i){
			tempcon[i] = constcon[i+1];
		}
		col.setContainer(tempcon);
		//++index;
		col.setSize(col.getSize()-1);
	}
}
