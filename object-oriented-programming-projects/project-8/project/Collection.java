/**
 * Collection is the composition of any type of containers
 * 
 * @author Tayfun
 *
 * @param <T> indicates which type of container it will hold
 */
public interface Collection<T>{
	public T getElem(int index);
	public T[] getContainer();
	public void setContainer(T[] con);
	public int getSize();
	public void setSize(int sz);
	
	public Iterator<T> iterator();
	public void add(T e);
	public void addAll(Collection<T> c);
	public boolean contains(T e);
	public boolean containsAll(Collection<T> c);
	public boolean isEmpty();
	public void remove(T e);
	public void removeAll(Collection<T> c);
	public void retainAll(Collection<T> c);
	public int size();
	public void clear();
}
