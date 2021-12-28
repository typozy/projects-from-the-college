package com.company;

public class Main {

    public static void main(String[] args) {
        Object[][][] Gokturk3 = {
                {{1,2,3},{4,5,6},{7,8,9}},
                {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}},
                {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}},
                {{1,2,3,4,5,6},{7,8,9,10,11,12},{13,14,15,16,17,18},{19,20,21,22,23,24},{25,26,27,28,29,30},{31,32,33,34,35,36}}
        };
        for (int k = 0; k < Gokturk3.length; k++) {
            System.out.printf("Gokturk3 dataPackNo%d:\n", k);
            for (int i = 0; i < Gokturk3[k].length; i++) {
                for (int j = 0; j < Gokturk3[k][0].length; j++) {
                    System.out.printf("%2s", Gokturk3[k][i][j]);
                    System.out.print(" ");
                }
                System.out.println();
            }
            ClockwiseIterator clock = new ClockwiseIterator(Gokturk3[k]);
            CounterClockwiseIterator counterclock = new CounterClockwiseIterator(Gokturk3[k]);
            System.out.println("Clockwise iterator:");
            while (clock.hasNext()) {
                System.out.print(clock.next());
                System.out.print(" ");
            }
            System.out.println();
            System.out.println("Counter clockwise iterator:");
            while (counterclock.hasNext()) {
                System.out.print(counterclock.next());
                System.out.print(" ");
            }
            System.out.println();
        }
    }
}
