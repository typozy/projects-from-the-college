package com.company;
import java.lang.Math;
public class CosineTransform extends Transform{

    public double[] solution(double[] input){
        int len = input.length;
        double[] output = new double[len*2];
        for (int i = 0;i<len;++i){
            output[2*i] = 0.0;
            for (int j = 0;j<len;++j) {
                output[2*i] += input[j] * Math.cos((Math.PI / len) * (j + 0.5) * i);
            }
            output[2*i] *= Math.sqrt(2.0/len);
            if(i==0)
                output[2*i] *= Math.sqrt(0.5);
            output[2*i+1] = 0.0;
        }
        return output;
    }
}
