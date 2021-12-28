package com.company;
import java.lang.Math;
import java.util.Scanner;
import static java.lang.System.nanoTime;

public class FourierTransform extends Transform{

    long timepassed;

    public double[] solution(double[] input){
        timepassed = nanoTime();
        int len = input.length;
        double[] output = new double[len*2];
        for (int i = 0;i<len;++i){
            output[2*i] = 0.0;
            output[2*i+1] = 0.0;
            for (int j=0; j<len; ++j){
                output[2*i] += input[j]* Math.cos(((2.0*Math.PI)/len)*j*i);
                output[2*i+1] -= input[j]*Math.sin(((2.0*Math.PI)/len)*j*i);
            }
        }
        timepassed = nanoTime() - timepassed;
        return output;
    }
    public void hook(){
        System.out.println("Want to know the time passed? (Y or N)");
        String s;
        Scanner scan = new Scanner(System.in);
        s = scan.nextLine();
        boolean end = false;
        while (!end) {
            if (s.equalsIgnoreCase("Y") || s.equalsIgnoreCase("Yes")) {
                System.out.print("The time passed is ");
                System.out.print(timepassed);
                System.out.println(" nanosecs, goodbye");
                end = true;
            } else if (s.equalsIgnoreCase("n") || s.equalsIgnoreCase("no")) {
                System.out.println("Ok, see you");
                end = true;
            } else {
                System.out.println("Please enter a right command (Y or N)");
                s = scan.nextLine();
            }
        }
    }
}
