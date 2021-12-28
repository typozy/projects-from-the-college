
public class ExperimentList implements Iterable {

    private Node head;

    public ExperimentList (){
        head = null;
    }

    public ExperimentList (Node exp){
        head = exp;
    }

    @Override
    public ExperimentIterator iterator(){
        return new ExperimentIterator(this);
    }

    public Node getHead(){
        return head;
    }

    public void setHead(Node hd){
        head = hd;
    }

    public void listAll()
    {
        System.out.println("List experiment view:");
        Node last = head;
        while( last != null) {
            System.out.println(last.getNode().toString());
            last = last.getNext();
        }
        System.out.println("List day view:");
        last = head;
        while( last != null) {
            System.out.println(last.getNode().toString());
            last = last.getNextDay();
        }
    }

    public void addExp(Experiment exp) {
        if (head == null) {
            head = new Node();
            head.setNode(exp);
        }
        else {
            Node temp = head;
            Node temp2 = null;
            while(temp.getNode().getDay() < exp.getDay() && temp.getNextDay() != null) {
                temp2 = temp;
                temp = temp.getNextDay();
            }
            if(temp.getNode().getDay() < exp.getDay()) {
                temp2 = new Node();
                temp.setNextDay(temp2);
                temp.getNextDay().setNode(exp);
                while(temp.getNext() != null) {
                    temp.setNextDay(temp2);
                    temp = temp.getNext();
                }
                temp.setNextDay(temp2);
                temp.setNext(temp2);
            }
            else if(temp.getNode().getDay() == exp.getDay()) {
                if(temp.getNextDay() == null) {
                    while(temp.getNext() != null)
                        temp = temp.getNext();
                    temp.setNext(new Node());
                    temp.getNext().setNode(exp);
                }
                else {
                    Node temp3 = temp;
                    while(temp.getNextDay() == temp.getNext().getNextDay())
                        temp = temp.getNext();
                    temp2 = temp.getNext();
                    temp.setNext(new Node());
                    temp = temp.getNext();
                    temp.setNode(exp);
                    temp.setNext(temp2);
                    temp = temp.getNext();
                    while(temp3 != temp) {
                        temp3.setNextDay(temp);
                        temp3 = temp3.getNext();
                    }
                }
            }
            else {
                if (temp2 == null) {

                    head = new Node();
                    head.setNode(exp);
                    head.setNext(temp);
                    head.setNextDay(temp);
                }
                else{
                    Node temp3 = new Node();
                    temp3.setNode(exp);
                    temp3.setNext(temp);
                    temp3.setNextDay(temp);
                    temp = temp2;
                    while(temp2.getNext() != temp3.getNext())
                        temp2 = temp2.getNext();
                    temp2.setNext(temp3);
                    while(temp != temp3) {
                        temp.setNextDay(temp3);
                        temp = temp.getNext();
                    }
                }
            }
        }
    }

    public Experiment getExp(int day, int index) throws Exception{
        if (head == null) throw new Exception();
        Node temp = head;
        while(temp.getNode().getDay() != day && temp.getNextDay() != null)
            temp = temp.getNextDay();
        if(temp.getNode().getDay() == day) {
            for(int i=0; i<index; ++i) {
                if(temp.getNext() != null)
                    temp = temp.getNext();
                else
                    throw new Exception();
            }
            if(temp.getNode().getDay() == day)
                return temp.getNode();
            else throw new Exception();
        }
        else throw new Exception();

    }

    public void setExp(int day, int index, Experiment exp) throws Exception{
        if (head == null) throw new Exception();
        Node temp = head;
        while(temp.getNode().getDay() != exp.getDay() && temp.getNextDay() != null)
            temp = temp.getNextDay();
        if(temp.getNode().getDay() == exp.getDay()) {
            for(int i=0; i<index; ++i) {
                if(temp.getNext() != null)
                    temp = temp.getNext();
                else
                    throw new Exception();
            }
            if(temp.getNode().getDay() == exp.getDay())
                temp.setNode(exp);

            else throw new Exception();

        }
        else throw new Exception();

    }

    public void removeExp(int day, int index) throws Exception{
        if (head == null) throw new Exception();
        Node temp = head;
        Node temp2 = null;
        while(temp.getNode().getDay() != day && temp.getNextDay() != null) {
            temp2 = temp;
            temp = temp.getNextDay();
        }
        if(temp.getNode().getDay() == day) {
            for(int i=0; i<index; ++i) {
                if(temp.getNext() != null)
                    temp = temp.getNext();
                else
                    throw new Exception();
            }
            if(temp.getNode().getDay() == day) {
                if (temp == head) {
                    head = head.getNext();
                }
                else {
                    System.out.printf("-%s\n",temp.getNode());
                    Node temp3 = temp2;
                    if(index == 0 && temp.getNext() == temp.getNextDay()) {
                        while(temp2 != temp) {
                            temp2.setNextDay(temp.getNextDay());
                            temp2 = temp2.getNext();
                        }
                    }
                    else if(index == 0) {
                        while(temp2 != temp) {
                            temp2.setNextDay(temp.getNext());
                            temp2 = temp2.getNext();
                        }
                    }
                    while(temp3.getNext() != temp)
                        temp3 = temp3.getNext();
                    temp3.setNext(temp.getNext());
                }
            }
            else throw new Exception();
        }
        else throw new Exception();
    }

    public ExperimentList listExp(int day) throws Exception {
        if (head == null) throw new Exception();
        Node temp = head;
        while(temp.getNode().getDay() != day && temp.getNextDay() != null)
            temp = temp.getNextDay();
        if(temp.getNode().getDay() == day) {
            ExperimentList exp = new ExperimentList();
            Node temp2 = null;
            if(temp.getNode().completed()) {
                exp.head = new Node();
                exp.head.setNode(temp.getNode());
                temp2 = exp.head;
            }
            temp = temp.getNext();
            while(temp != null) {
                if(temp.getNode().getDay() == day) {
                    if(temp.getNode().completed()) {
                        if (exp.head == null) {
                            exp.head = new Node();
                            exp.head.setNode(temp.getNode());
                            temp2 = exp.head;
                        }
                        else {
                            temp2.setNext(new Node());
                            temp2 = temp2.getNext();
                            temp2.setNode(temp.getNode());
                        }

                    }
                }
                else break;
                temp = temp.getNext();
            }
            temp2 = exp.head;
            while (temp2 != null) {
                System.out.printf("%s\n", temp2.getNode());
                temp2 = temp2.getNext();
            }
            return exp;
        }
        else throw new Exception();
    }

    public void removeDay(int day) throws Exception{
        if (head == null) throw new Exception();
        Node temp = head;
        Node temp2 = null;
        while(temp.getNode().getDay() != day && temp.getNextDay() != null) {
            temp2 = temp;
            temp = temp.getNextDay();
        }
        if(temp.getNode().getDay() == day) {
            if (temp == head) {
                head = head.getNextDay();
            }
            else {
                Node temp3 = temp2;
                while (temp3 != temp) {
                    temp3.setNextDay(temp.getNextDay());
                    temp3 = temp3.getNext();
                }
                while (temp2.getNext() != temp)
                    temp2 = temp2.getNext();
                temp2.setNext(temp.getNextDay());
            }

        }
        else throw new Exception();
    }

    public void orderDay(int day) throws Exception {
        if (head == null) {
            throw new Exception();
        }
        else {
            Node temp = head;
            Node temp2 = null;
            while (temp.getNode().getDay() != day && temp.getNextDay() != null) {
                temp2 = temp;
                temp = temp.getNextDay();
            }

            if(temp.getNode().getDay() != day ){
                throw new Exception();
            }
            else if(temp == head){
                Node temphead = new Node();
                temphead.setNext(head);
                Node temp3, temp4;
                temp3 = temphead;
                while(temp3.getNext().getNext() != temp3.getNext().getNextDay()){
                    temp4 = temp3.getNext();
                    while(temp4.getNext() != temp4.getNextDay()){
                        if(temp4.getNext().getNode().getAccuracy() < temp3.getNext().getNode().getAccuracy()){
                            if (temp3.getNext().getNext() == temp4.getNext()) {
                                Node temp5 = temp3.getNext().getNext();
                                Node temp6 = temp3.getNext();
                                Node temp7 = temp3.getNext().getNext().getNext();
                                temp3.setNext(temp5);
                                temp5.setNext(temp6);
                                temp6.setNext(temp7);
                                temp4 = temp3.getNext();
                            }
                            else{
                                Node temp5 = temp4.getNext();
                                Node temp6 = temp3.getNext().getNext();
                                Node temp7 = temp3.getNext();
                                Node temp8 = temp4.getNext().getNext();
                                temp3.setNext(temp5);
                                temp5.setNext(temp6);
                                temp4.setNext(temp7);
                                temp7.setNext(temp8);
                            }
                        }
                        temp4 = temp4.getNext();
                    }
                    temp3 = temp3.getNext();
                }
                head = temphead.getNext();
            }
            else{
                while(temp2.getNext() != temp)
                    temp2 = temp2.getNext();
                Node temphead = temp2;
                Node temp3, temp4;
                temp3 = temphead;
                while(temp3.getNext().getNext() != null){
                    temp4 = temp3.getNext();
                    while(temp4.getNext() != null){
                        if(temp4.getNext().getNode().getAccuracy() < temp3.getNext().getNode().getAccuracy()){
                            if (temp3.getNext().getNext() == temp4.getNext()) {
                                Node temp5 = temp3.getNext().getNext();
                                Node temp6 = temp3.getNext();
                                Node temp7 = temp3.getNext().getNext().getNext();
                                temp3.setNext(temp5);
                                temp5.setNext(temp6);
                                temp6.setNext(temp7);
                                temp4 = temp3.getNext();
                            }
                            else{
                                Node temp5 = temp4.getNext();
                                Node temp6 = temp3.getNext().getNext();
                                Node temp7 = temp3.getNext();
                                Node temp8 = temp4.getNext().getNext();
                                temp3.setNext(temp5);
                                temp5.setNext(temp6);
                                temp4.setNext(temp7);
                                temp7.setNext(temp8);
                            }
                        }
                        temp4 = temp4.getNext();
                    }
                    temp3 = temp3.getNext();
                }
            }
        }
    }

    public ExperimentList orderExperiments() {
        if(head != null) {
            Node temphead = new Node();
            Node temp = new Node();
            temphead.setNext(temp);
            temp.setNode(head.getNode().clone());
            if(head.getNext() != null){
                Node iterator = head.getNext();
                temp.setNext(new Node());
                temp = temp.getNext();
                temp.setNode(iterator.getNode().clone());
                while(iterator.getNext() != null){
                    iterator = iterator.getNext();
                    temp.setNext(new Node());
                    temp = temp.getNext();
                    temp.setNode(iterator.getNode().clone());
                }
                Node temp3, temp4;
                temp3 = temphead;
                while(temp3.getNext().getNext() != null){
                    temp4 = temp3.getNext();
                    while(temp4.getNext() != null){
                        if(temp4.getNext().getNode().getAccuracy() < temp3.getNext().getNode().getAccuracy()) {
                            if (temp3.getNext().getNext() == temp4.getNext()) {
                                Node temp5 = temp3.getNext().getNext();
                                Node temp6 = temp3.getNext();
                                Node temp7 = temp3.getNext().getNext().getNext();
                                temp3.setNext(temp5);
                                temp5.setNext(temp6);
                                temp6.setNext(temp7);
                                temp4 = temp3.getNext();
                            }
                            else{
                                Node temp5 = temp4.getNext();
                                Node temp6 = temp3.getNext().getNext();
                                Node temp7 = temp3.getNext();
                                Node temp8 = temp4.getNext().getNext();
                                temp3.setNext(temp5);
                                temp5.setNext(temp6);
                                temp4.setNext(temp7);
                                temp7.setNext(temp8);
                            }
                        }
                        temp4 = temp4.getNext();
                    }
                    temp3 = temp3.getNext();
                }
                ExperimentList lastExp = new ExperimentList();
                lastExp.head = temphead.getNext();
                return lastExp;
            }
            else return new ExperimentList(temp);
        }
        else return new ExperimentList();
    }

}




