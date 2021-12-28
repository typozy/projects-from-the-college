
public class PQLEX extends Thread {
    @Override
    public void run() {
        try {
            int totalConsumed = 0;
            while (true) {
                if (Main.ctrlex.counter > 0) {
                    synchronized (Main.ctrlex) {
                        --Main.ctrlex.counter;
                        ++totalConsumed;
                    }
                    synchronized (Main.lexQ) {
                        int[] temp = Main.lexQ.remove();
                        System.out.printf("Thread2-PQLEX: [%d,%d,%d]\n", temp[0], temp[1], temp[2]);
                    }
                }
                if(totalConsumed == Main.width * Main.height)
                    break;
            }

        } catch (Exception e) {
            System.err.println("Oops!");
        }
    }
}
