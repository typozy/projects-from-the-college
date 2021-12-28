
public class Graph {

    private int[] personArr;
    private int[][] adjMatrix;

    public Graph(){
        personArr = null;
        adjMatrix = null;
    }

    public int getPerson(int in){
        return personArr[in];
    }

    public int getAdjacency(int x, int y){
        return adjMatrix[index(x)][index(y)];
    }

    public void addPerson(int num){
        if (personArr == null){
            personArr = new int[1];
            personArr[0] = num;
            adjMatrix = new int[1][];
            adjMatrix[0] = new int[1];
            adjMatrix[0][0] = 0;
        }
        else{
            int[] tempPerson = new int[personArr.length+1];
            for (int i=0; i<personArr.length; ++i)
                tempPerson[i] = personArr[i];
            tempPerson[tempPerson.length-1] = num;
            personArr = tempPerson;
            int[][] tempMatrix = new int[personArr.length][];
            for (int i=0; i<personArr.length; ++i)
                tempMatrix[i] = new int[personArr.length];
            for (int i=0; i<personArr.length; ++i) {
                for (int j = 0; j < personArr.length; ++j){
                    if (i == personArr.length-1 || j == personArr.length-1)
                        tempMatrix[i][j] = 0;
                    else
                        tempMatrix[i][j] = adjMatrix[i][j];
                }
            }
            adjMatrix = tempMatrix;
        }
    }

    public void addRelation(int x, int y){
        adjMatrix[index(x)][index(y)] = 1;
    }

    public void removeRelation(int x, int y){
        adjMatrix[index(x)][index(y)] = 0;
    }

    public int index(int num){
        for (int i=0; i<personArr.length; ++i)
            if (num == personArr[i])
                return i;
        return -1;
    }
}
