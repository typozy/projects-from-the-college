package com.company;

import java.io.*;
import java.util.Scanner;

public abstract class Transform {

    public void solve(String path) throws IOException {
        write(solution(read(path)));
        hook();
    }

    public abstract double[] solution(double[] input);

    public double[] read(String path) throws FileNotFoundException {
        File file = new File(path);
        Scanner scan = new Scanner(file);
        int n = 0;
        while(scan.hasNext()){
                scan.next();
                ++n;
        }
        scan.close();
        scan = new Scanner(file);
        double[] input = new double[n];
        int i = 0;
        String s;
        while (scan.hasNext()) {
            s = scan.next();
            input[i] = Double.parseDouble(s);
            ++i;
        }
        scan.close();
        return input;
    }

    public void write(double[] out) throws IOException {
        File file = new File("output.txt");
        FileWriter writer = new FileWriter(file, true);
        //PrintWriter pr = new PrintWriter(br);
        for (int i=0;i<out.length/2;++i){
            writer.write(Double.toString(out[2*i]));
            if(out[2*i+1] != 0.0) {
                writer.write(" + "+Double.toString(out[2 * i + 1])+"i");
            }
            if(i<(out.length/2)-1){
                writer.write(", ");
            }
            else{
                writer.write("\r\n");
            }
        }
        writer.close();
    }
    public void hook(){
    }
}
