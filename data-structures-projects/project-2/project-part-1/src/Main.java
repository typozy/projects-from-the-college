import java.io.BufferedReader;
import java.io.FileReader;

public class Main {

    public static void main(String[] args) {
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
            String[][] varArr = new String[totalLines+2][];
            for (int i = 1; i <= totalLines; ++i) {
                String[] temp = buffer.readLine().split(" ");
                varArr[i] = new String[temp.length + 2];
                varArr[i][0] = "-1";
                varArr[i][temp.length+1] = "-1";
                for(int j=0; j<temp.length; ++j)
                    varArr[i][j+1] = temp[j];
            }
            buffer.close();
            varArr[0] = new String[varArr[1].length];
            varArr[totalLines+1] = new String[varArr[1].length];
            for(int i=0; i<varArr[1].length; ++i){
                varArr[0][i] = "-1";
                varArr[totalLines+1][i] = "-1";
            }
            int totalComponents = 0;
            for(int k=0; k<varArr.length; ++k) {
                for (int l = 0; l < varArr[0].length; ++l) {
                    if (varArr[k][l].equals("1")) {
                        Stack<Coordinate> temp = new Stack<Coordinate>();
                        temp.push(new Coordinate(k, l));
                        varArr[k][l] = "2";
                        int m = k;
                        int n = l;
                        do {
                            if (varArr[m-1][n].equals("1") || varArr[m+1][n].equals("1") || varArr[m][n-1].equals("1") || varArr[m][n+1].equals("1")) {
                                if (varArr[m-1][n].equals("1")) {
                                    temp.push(new Coordinate(m-1, n));
                                    varArr[m-1][n] = "2";
                                    m = m-1;
                                }
                                else if (varArr[m+1][n].equals("1")) {
                                    temp.push(new Coordinate(m+1, n));
                                    varArr[m+1][n] = "2";
                                    m = m+1;
                                }
                                else if (varArr[m][n-1].equals("1")) {
                                    temp.push(new Coordinate(m, n-1));
                                    varArr[m][n-1] = "2";
                                    n = n-1;
                                }
                                else  {
                                    temp.push(new Coordinate(m, n+1));
                                    varArr[m][n+1] = "2";
                                    n = n+1;
                                }
                            }
                            else {
                                if (m == k && n == l) {
                                    temp.pop();
                                }
                                else {
                                    temp.pop();
                                    m = temp.peek().x;
                                    n = temp.peek().y;
                                }
                            }
                        } while (!(m == k && n == l && (!varArr[m-1][n].equals("1") && !varArr[m+1][n].equals("1") && !varArr[m][n-1].equals("1") && !varArr[m][n+1].equals("1"))));
                        ++totalComponents;
                    }
                }
            }
            for(int i=0; i<varArr.length; ++i)
                for(int j=0; j<varArr[0].length; ++j)
                    if(varArr[i][j].equals("2"))
                        varArr[i][j] = "1";
            System.out.println("\nMap:\n");
            for(int i=1; i<varArr.length-1; ++i) {
                for (int j = 1; j < varArr[0].length-1; ++j)
                    System.out.printf("%s ",varArr[i][j]);
                System.out.printf("\n");
            }
            System.out.printf("\nTotal components: %d\n",totalComponents);
        }
        catch (Exception e){
            System.err.println("Oops!");
        }
    }
}