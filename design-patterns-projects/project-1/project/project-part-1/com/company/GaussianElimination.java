package com.company;
public class GaussianElimination implements SolutionType{

    private static final double EPSILON = 1e-10;

    public void solve(double[][] matA, double[] matB) {
        double det = determinant(matA);
        if (det == 0.0){
            System.err.println("No solution for this equation system");
            return;
        }
        int n = matB.length;
        for (int p = 0; p < n; p++) {
            int max = p;
            for (int i = p + 1; i < n; i++) {
                if (Math.abs(matA[i][p]) > Math.abs(matA[max][p])) {
                    max = i;
                }
            }
            double[] temp = matA[p]; matA[p] = matA[max]; matA[max] = temp;
            double   t    = matB[p]; matB[p] = matB[max]; matB[max] = t;
            for (int i = p + 1; i < n; i++) {
                double alpha = matA[i][p] / matA[p][p];
                matB[i] -= alpha * matB[p];
                for (int j = p; j < n; j++) {
                    matA[i][j] -= alpha * matA[p][j];
                }
            }
        }
        double[] x = new double[n];
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) {
                sum += matA[i][j] * x[j];
            }
            x[i] = (matB[i] - sum) / matA[i][i];
        }
        System.out.println("Roots with gaussian elimination method:");
        for (int i=0;i<x.length;++i)
            System.out.printf("%.2f ",x[i]);
        System.out.println();
    }

    public double determinant (double[][] matA) {
        double temporary[][];
        double result = 0;

        if (matA.length == 1) {
            result = matA[0][0];
            return (result);
        }

        if (matA.length == 2) {
            result = ((matA[0][0] * matA[1][1]) - (matA[0][1] * matA[1][0]));
            return (result);
        }

        for (int i = 0; i < matA[0].length; i++) {
            temporary = new double[matA.length - 1][matA[0].length - 1];

            for (int j = 1; j < matA.length; j++) {
                for (int k = 0; k < matA[0].length; k++) {
                    if (k < i) {
                        temporary[j - 1][k] = matA[j][k];
                    } else if (k > i) {
                        temporary[j - 1][k - 1] = matA[j][k];
                    }
                }
            }

            result += matA[0][i] * Math.pow (-1, (double) i) * determinant (temporary);
        }
        return (result);
    }
}
