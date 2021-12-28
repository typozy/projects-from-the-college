
public class Math {

    public static final double PI = 3.1415;

    public static double power(double base, int exp){
        double sum = 1.0;
        for (int i=0; i<exp; ++i)
            sum *= base;
        return sum;
    }

    public static double factorial(int number){
        int sum = 1;
        for(int i=2; i<=number; ++i)
            sum *= i;
        return sum;
    }

    public static double sin(double deg){
        double degree = deg%360;
        boolean negative = false;
        if(degree > 270) {
            degree = 360 - degree;
            negative = true;
        }
        else if(degree>180) {
            degree = degree - 180;
            negative = true;
        }
        else if(degree>90)
            degree = 180 - degree;
        double x = PI*degree/180;
        double sum = 0.0;
        for(int i=0; i<14; ++i){
            if(i%2 == 0)
                sum += power(x,2*i+1)/factorial(2*i+1);
            else
                sum -= power(x,2*i+1)/factorial(2*i+1);
        }
        if(negative)
            return -sum;
        else
            return sum;
    }

    public static double cos(double deg){
        double degree = deg%360;
        boolean negative = false;
        if(degree > 270)
            degree = 360 - degree;
        else if(degree>180) {
            degree = degree - 180;
            negative = true;
        }
        else if(degree>90) {
            degree = 180 - degree;
            negative = true;
        }
        double x = PI*degree/180;
        double sum = 0.0;
        for(int i=0; i<14; ++i){
            if(i%2 == 0)
                sum += power(x,2*i)/factorial(2*i);
            else
                sum -= power(x,2*i)/factorial(2*i);
        }
        if(negative)
            return -sum;
        else
            return sum;
    }

    public static double abs(double number){
        return ((number < 0.0) ? (number*(-1.0)) : number);
    }

}
