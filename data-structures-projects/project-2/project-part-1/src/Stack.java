public class Stack <T> {

    Node<T> head;

    public Stack(){
        head = null;
    }

    public T pop() throws Exception {
        if (head != null){
            Node<T> temp = head;
            head = head.getNext();
            return temp.getNode();
        }
        else
            throw new Exception();
    }

    public T push(T element){
        Node<T> temp = new Node();
        temp.setNode(element);
        Node<T> temp2 = head;
        head = temp;
        temp.setNext(temp2);
        return head.getNode();
    }

    public boolean empty(){
        if(head == null)
            return true;
        else return false;
    }

    public T peek() throws Exception{
        if (head != null){
            return head.getNode();
        }
        else
            throw new Exception();
    }

    public int search(T element){
        Node<T> temp = head;
        int count = 1;
        while (temp != null){
            if(temp.getNode().equals(element))
                return count;
            ++count;
            temp = temp.getNext();
        }
        return -1;
    }

    public Node<T> getHead(){
        return head;
    }

}
