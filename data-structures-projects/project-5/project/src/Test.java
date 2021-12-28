import java.io.BufferedReader;
import java.io.FileReader;

public class Test {

    private static int totalPeople;
    private static int relationCount;
    private static Graph myAdjGraph;

    public static void drive(String[] args) {
        try {
            String name = args[0];
            FileReader reader = new FileReader(name);
            BufferedReader buffer = new BufferedReader(reader);
            int totalLines = 0;
            while (buffer.readLine() != null) {
                ++totalLines;
            }
            buffer.close();
            reader = new FileReader(name);
            buffer = new BufferedReader(reader);
            {
                String[] temp = buffer.readLine().split(" ");
                totalPeople = Integer.parseInt(temp[0]);
                relationCount = Integer.parseInt(temp[1]);
            }
            int[][] relationArr = new int[totalLines-1][];
            for (int i = 0; i < totalLines-1; ++i) {
                String[] temp = buffer.readLine().split(" ");
                relationArr[i] = new int[2];
                relationArr[i][0] = Integer.parseInt(temp[0]);
                relationArr[i][1] = Integer.parseInt(temp[1]);
            }
            buffer.close();
            reader = new FileReader(name);
            buffer = new BufferedReader(reader);
            buffer.readLine();
            myAdjGraph = new Graph();
            int count = 0;
            for(int i=0; i<relationCount; ++i){
                for (int j=0; j<2; ++j){
                    boolean isThere;
                    isThere = false;
                    for(int k=0; k<count; ++k)
                        if(myAdjGraph.getPerson(k) == relationArr[i][j])
                            isThere = true;
                    if(!isThere){
                        myAdjGraph.addPerson(relationArr[i][j]);
                        ++count;
                    }
                }
            }
            if(count < totalPeople || totalPeople < 2){
                System.out.println("0");
                return;
            }
            for (int i=0; i<relationCount; ++i) {
                myAdjGraph.addRelation(relationArr[i][0],relationArr[i][1]);
            }
            System.out.printf("%d\n",totalCount());
        }
        catch (Exception e){
            System.err.println("Oops!");
        }
    }

    public static int totalCount(){
        if (totalPeople < 2)
            return 0;
        int count = 0;
        for (int i=0; i<totalPeople; ++i)
            if (popularEverywhere(myAdjGraph.getPerson(i)))
                ++count;
        return count;
    }

    public static boolean popularEverywhere(int isPop){
        for (int i=0; i<totalPeople; ++i)
            if (myAdjGraph.getPerson(i) != isPop) {
                int[] temp = new int[1];
                temp[0] = myAdjGraph.getPerson(i);
                if (!isPopular(myAdjGraph.getPerson(i), isPop, temp))
                    return false;
            }
        return true;
    }

    public static boolean isPopular(int start, int finish, int[] traversed){
        if (myAdjGraph.getAdjacency(start,finish) == 1)
            return true;
        for (int i=0; i<totalPeople; ++i)
            if(!isTraversed(myAdjGraph.getPerson(i),traversed) && myAdjGraph.getAdjacency(start,myAdjGraph.getPerson(i)) == 1){
                boolean relative = isPopular(myAdjGraph.getPerson(i),finish,traverse(myAdjGraph.getPerson(i),traversed));
                if(relative)
                    return true;
            }
        return false;
    }

    public static int[] traverse(int num, int[] list){
        int[] temp = new int[list.length+1];
        for (int i=0; i<list.length; ++i)
            temp[i] = list[i];
        temp[temp.length-1] = num;
        return temp;
    }

    public static boolean isTraversed(int num, int[] list){
        for (int i=0; i<list.length; ++i)
            if (num == list[i])
                return true;
        return false;
    }

}
