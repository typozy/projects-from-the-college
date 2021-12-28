import java.beans.Expression;
import java.io.FileReader;
import java.io.BufferedReader;

public class Main {

    public static void main(String[] args) {
        try {
            String fileName = args[0];
            FileReader reader = new FileReader(fileName);
            BufferedReader buffer = new BufferedReader(reader);
            int totalLines = 0;
            while(buffer.readLine() != null) {
                ++totalLines;
            }
            buffer.close();
            reader = new FileReader(fileName);
            buffer = new BufferedReader(reader);
            String[][] varArr = new String[totalLines-2][];
            for(int i=0; i<totalLines-2; ++i){
                varArr[i] = buffer.readLine().split(" ");
            }
            buffer.readLine();
            String[] expression = buffer.readLine().split(" ");
            buffer.close();
            Stack<String> temp = new Stack<String>();
            Stack<String> postfix = new Stack<String>();
            for (String samp:expression) {
                if(samp.compareTo("(") == 0 || samp.compareTo("sin(") == 0 || samp.compareTo("cos(") == 0 || samp.compareTo("abs(") == 0)
                    temp.push(samp);
                else if(samp.compareTo("+") == 0 || samp.compareTo("-") == 0){
                    if(temp.empty())
                        temp.push(samp);
                    else if(temp.peek().compareTo("*") == 0 || temp.peek().compareTo("/") == 0){
                        while(!temp.empty() && ((temp.peek().compareTo("*") == 0 || temp.peek().compareTo("/") == 0 || temp.peek().compareTo("+") == 0 || temp.peek().compareTo("-") == 0)))
                            postfix.push(temp.pop());
                        temp.push(samp);
                    }
                    else
                        temp.push(samp);
                }
                else if(samp.compareTo("*") == 0 || samp.compareTo("/") == 0)
                    temp.push(samp);
                else if(samp.compareTo(")") == 0) {
                    while (!temp.empty() && (temp.peek().compareTo("(") != 0 && temp.peek().compareTo("sin(") != 0 && temp.peek().compareTo("cos(") != 0 && temp.peek().compareTo("abs(") != 0))
                        postfix.push(temp.pop());
                    if(temp.peek().compareTo("sin(") == 0) {
                        temp.pop();
                        postfix.push("sin");
                    }
                    else if(temp.peek().compareTo("cos(") == 0) {
                        temp.pop();
                        postfix.push("cos");
                    }
                    else if(temp.peek().compareTo("abs(") == 0) {
                        temp.pop();
                        postfix.push("abs");
                    }
                    else {
                        temp.pop();
                    }
                }
                else {
                    boolean found = false;
                    for(String[] it:varArr){
                        if(it[0].compareTo(samp) == 0){
                            found = true;
                            postfix.push(it[2]);
                            break;
                        }
                    }
                    if(!found)
                        postfix.push(samp);
                }
            }
            while(!temp.empty())
                postfix.push(temp.pop());
            Stack<String> reverse = new Stack<String>();
            while(!postfix.empty())
                reverse.push(postfix.pop());
            double result = calculator(reverse);
            System.out.printf("\nExpression: ");
            for(int i=0; i<expression.length; ++i)
                System.out.printf("%s ",expression[i]);
            System.out.printf("\n\nResult: %f\n",result);
        }
        catch (Exception e){
            System.err.println("Oops!");
        }
    }

    public static double calculator(Stack<String> rev) throws Exception{
        Stack<String> res = new Stack<String>();
        while(!rev.empty()){
            if(rev.peek().compareTo("+") == 0){
                double temp2 = Double.parseDouble(res.pop());
                double temp1 = Double.parseDouble(res.pop());
                double result = temp1 + temp2;
                res.push(String.valueOf(result));
            }
            else if(rev.peek().compareTo("-") == 0){
                double temp2 = Double.parseDouble(res.pop());
                double temp1 = Double.parseDouble(res.pop());
                double result = temp1 - temp2;
                res.push(String.valueOf(result));
            }
            else if(rev.peek().compareTo("*") == 0){
                double temp2 = Double.parseDouble(res.pop());
                double temp1 = Double.parseDouble(res.pop());
                double result = temp1 * temp2;
                res.push(String.valueOf(result));
            }
            else if(rev.peek().compareTo("/") == 0){
                double temp2 = Double.parseDouble(res.pop());
                double temp1 = Double.parseDouble(res.pop());
                double result = temp1 / temp2;
                res.push(String.valueOf(result));
            }
            else if(rev.peek().compareTo("sin") == 0){
                double temp = Double.parseDouble(res.pop());
                double result = Math.sin(temp);
                res.push(String.valueOf(result));
            }
            else if(rev.peek().compareTo("cos") == 0){
                double temp = Double.parseDouble(res.pop());
                double result = Math.cos(temp);
                res.push(String.valueOf(result));
            }
            else if(rev.peek().compareTo("abs") == 0){
                double temp = Double.parseDouble(res.pop());
                double result = Math.abs(temp);
                res.push(String.valueOf(result));
            }
            else
                res.push(rev.peek());
            rev.pop();
        }
        double result = Double.parseDouble(res.peek());
        return result;
    }

}
