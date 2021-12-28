public class Node <T> {

    private T node;
    private Node<T> next;

    public Node(){
        node = null;
        next = null;
    }

    public Node getNext(){
        return next;
    }

    public void setNext(Node nxt){
        next = nxt;
    }

    public T getNode(){
        return node;
    }

    public void setNode(T element){
        node = element;
    }

}
