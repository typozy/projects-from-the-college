import java.util.Iterator;

public class ExperimentIterator implements Iterator {

    private ExperimentList head;
    private Node node;
    private Node nodeptr;

    public ExperimentIterator(ExperimentList explst){
        node = new Node();
        nodeptr = node;
        node.setNext(explst.getHead());
        head = explst;
    }

    @Override
    public boolean hasNext() {
        if(node.getNext() != null)
            return true;
        else
            return false;
    }

    @Override
    public Node next() {
        nodeptr = node;
        node = node.getNext();
        return node;
    }

    @Override
    public void remove() {
        if(head.getHead() == node){
            nodeptr.setNext(node.getNext());
            node = nodeptr;
            head.setHead(nodeptr.getNext());
        }
        else{
            nodeptr.setNext(node.getNext());
            node = nodeptr;
        }
    }
}
