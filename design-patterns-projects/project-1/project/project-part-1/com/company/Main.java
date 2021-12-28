package com.company;

public class Main {
    public static void main(String[] args) {
        double A[][] = {{2,1,-1,2},{4,5,-3,6},{-2,5,-2,6},{4,11,-4,8}};
        double B[] = {5,9,4,2};
        Customer anyone = new Customer();
        anyone.solve(A,B);
        anyone.setSolutionType(new GaussianElimination());
        anyone.solve(A,B);
        anyone.setSolutionType(new MatrixInversion());
        anyone.solve(A,B);
        double C[][] = {{1,2,3},{4,5,6},{7,8,9}};
        double D[] = {10,28,46};
        anyone.solve(C,D);
    }
}
