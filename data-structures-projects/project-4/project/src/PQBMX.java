
public class PQBMX extends Thread {
    @Override
    public void run() {
        try {
            int totalConsumed = 0;
            while (true) {
                if (Main.ctrbmx.counter > 0) {
                    synchronized (Main.ctrbmx) {
                        --Main.ctrbmx.counter;
                        ++totalConsumed;
                    }
                    synchronized (Main.bmxQ) {
                        int[] temp = Main.bmxQ.remove();
                        System.out.printf("Thread4-PQBMX: [%d,%d,%d]\n", temp[0], temp[1], temp[2]);
                    }
                }
                if(totalConsumed == Main.width*Main.height)
                    break;
            }
        } catch (Exception e) {
            System.err.println("Oops!");
        }
    }
}
