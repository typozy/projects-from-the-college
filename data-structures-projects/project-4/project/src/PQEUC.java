
public class PQEUC extends Thread {
    @Override
    public void run() {
        try {
            int totalConsumed = 0;
            while (true) {
                if (Main.ctreuc.counter > 0) {
                    synchronized (Main.ctreuc) {
                        --Main.ctreuc.counter;
                        ++totalConsumed;
                    }
                    synchronized (Main.eucQ) {
                        int[] temp = Main.eucQ.remove();
                        System.out.printf("Thread3-EUC: [%d,%d,%d]\n", temp[0], temp[1], temp[2]);
                    }
                }
                if (totalConsumed == Main.width*Main.height)
                    break;
            }
        } catch (Exception e) {
            System.err.println("Oops!");
        }
    }
}
