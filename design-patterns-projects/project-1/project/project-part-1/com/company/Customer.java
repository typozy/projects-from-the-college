package com.company;

public class Customer {

    private SolutionType solution;

    public Customer(){
        solution = new NoSolution();
    }

    public void setSolutionType(SolutionType type){
        solution = type;
    }

    public void solve(double[][] matA, double[] matB){
        solution.solve(matA,matB);
    }
}
