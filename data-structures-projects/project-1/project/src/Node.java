
public class Node {

    private Experiment node;
    private Node next;
    private Node nextDay;

    public Node(){
        node = null;
        next = null;
        nextDay = null;
    }

    public void setNode(Experiment exp) {
        node = exp;
    }

    public void setNext(Node n) {
        next = n;
    }

    public void setNextDay(Node nd) {
        nextDay = nd;
    }

    public Experiment getNode() {
        return node;
    }

    public Node getNext() {
        return next;
    }

    public Node getNextDay() {
        return nextDay;
    }

}
