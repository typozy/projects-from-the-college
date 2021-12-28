package com.company;
public class MatrixInversion implements SolutionType{

    public void solve(double[][] matA, double[] matB) {
        double det = determinant(matA);
        if (det == 0.0){
            System.err.println("No solution for this equation system");
            return;
        }
        int n = matA.length;
        double inverseA[][] = new double[n][n];
        inverseA = invert(matA);
        double result[] = new double[n];
        result = multiply(inverseA,matB);
        System.out.println("Roots with matrix inversion method:");
        for (int i=0;i<result.length;++i)
            System.out.printf("%.2f ",result[i]);
        System.out.println();
    }

    public double[][] invert(double matA[][]) {
        int n = matA.length;
        double x[][] = new double[n][n];
        double b[][] = new double[n][n];
        int index[] = new int[n];
        for (int i=0; i<n; ++i)
            b[i][i] = 1;
        gaussian(matA, index);
        for (int i=0; i<n-1; ++i)
            for (int j=i+1; j<n; ++j)
                for (int k=0; k<n; ++k)
                    b[index[j]][k]
                            -= matA[index[j]][i]*b[index[i]][k];
        for (int i=0; i<n; ++i) {
            x[n-1][i] = b[index[n-1]][i]/matA[index[n-1]][n-1];
            for (int j=n-2; j>=0; --j){
                x[j][i] = b[index[j]][i];
                for (int k=j+1; k<n; ++k) {
                    x[j][i] -= matA[index[j]][k]*x[k][i];
                }
                x[j][i] /= matA[index[j]][j];
            }
        }
        return x;
    }

    public void gaussian(double matA[][], int matB[]) {
        int n = matB.length;
        double c[] = new double[n];
        for (int i=0; i<n; ++i)
            matB[i] = i;
        for (int i=0; i<n; ++i)  {
            double c1 = 0;
            for (int j=0; j<n; ++j){
                double c0 = Math.abs(matA[i][j]);
                if (c0 > c1) c1 = c0;
            }
            c[i] = c1;
        }
        int k = 0;
        for (int j=0; j<n-1; ++j)  {
            double pi1 = 0;
            for (int i=j; i<n; ++i) {
                double pi0 = Math.abs(matA[matB[i]][j]);
                pi0 /= c[matB[i]];
                if (pi0 > pi1)  {
                    pi1 = pi0;
                    k = i;
                }
            }
            int itmp = matB[j];
            matB[j] = matB[k];
            matB[k] = itmp;
            for (int i=j+1; i<n; ++i) {
                double pj = matA[matB[i]][j]/matA[matB[j]][j];
                matA[matB[i]][j] = pj;
                for (int l=j+1; l<n; ++l)
                    matA[matB[i]][l] -= pj*matA[matB[j]][l];
            }
        }
    }

    public double[] multiply(double[][] matA, double[] matB){
        int n = matB.length;
        double res[] = new double[n];
        for (int i=0; i<n; ++i){
            double temp = 0.0;
            for (int j=0; j<n; ++j){
                temp = temp + matA[i][j]*matB[j];
            }
            res[i] = temp;
        }
        return res;
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
