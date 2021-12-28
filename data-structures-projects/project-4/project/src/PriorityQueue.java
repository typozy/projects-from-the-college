public class PriorityQueue {

    public class Node {

        private int red;
        private int green;
        private int blue;
        private Node next;

        public Node() {
            next = null;
        }

        public int[] node() {
            int[] temp = new int[3];
            temp[0] = red;
            temp[1] = green;
            temp[2] = blue;
            return temp;
        }

        public Node next() {
            return next;
        }

        public void setNode(int[] rgb) {
            red = rgb[0];
            green = rgb[1];
            blue = rgb[2];
        }

        public void setNext(Node nx) {
            next = nx;
        }

    }

    private Node head;
    private String type;

    public PriorityQueue() {
        head = null;
        type = null;
    }

    public PriorityQueue(String ty) {
        head = null;
        type = ty;
    }

    public int[] element() throws Exception {
        if (head == null)
            throw new Exception();
        int[] temp = head.node();
        return temp;
    }

    public int[] peek() {
        int[] temp = head.node();
        return temp;
    }

    public int[] remove() throws Exception {
        if (head == null)
            throw new Exception();
        int[] temp = head.node();
        head = head.next();
        return temp;
    }

    public int[] poll() {
        int[] temp = head.node();
        head = head.next();
        return temp;
    }

    public boolean add(int[] element) {
        if (head == null) {
            head = new Node();
            head.setNode(element);
        } else if (QueueComparator.compare(element, head.node(), type) == 1) {
            Node temp = new Node();
            temp.setNode(element);
            temp.setNext(head);
            head = temp;
        } else {
            Node temp = head;
            Node temp2 = head.next();
            while (temp2 != null && QueueComparator.compare(element, temp2.node(), type) <= 0) {
                temp = temp.next();
                temp2 = temp2.next();
            }
            Node temp3 = new Node();
            temp3.setNode(element);
            temp.setNext(temp3);
            temp3.setNext(temp2);
        }
        return true;
    }

    public boolean offer(int[] element) {
        if (head == null) {
            head = new Node();
            head.setNode(element);
        } else if (QueueComparator.compare(element, head.node(), type) == 1) {
            Node temp = new Node();
            temp.setNode(element);
            temp.setNext(head);
            head = temp;
        } else {
            Node temp = head;
            Node temp2 = head.next();
            while (temp2 != null && QueueComparator.compare(element, temp2.node(), type) <= 0) {
                temp = temp.next();
                temp2 = temp2.next();
            }
            Node temp3 = new Node();
            temp3.setNode(element);
            temp.setNext(temp3);
            temp3.setNext(temp2);
        }
        return true;
    }


}
