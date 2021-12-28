
public interface Queue <T> extends Collection <T> {
	public void add(T e);
	public T element();
	public void offer(T e);
	public T poll() throws MyErrors;
}
