import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;

public class ImageTraverser extends Thread {
    @Override
    public void run() {
        try {
            File imageFile = new File(Main.imageName);
            BufferedImage buffer = ImageIO.read(imageFile);
            Main.width = buffer.getWidth();
            Main.height = buffer.getHeight();
            Main.imageArr = new int[Main.width][][];
            for (int i = 0; i < Main.width; ++i)
                Main.imageArr[i] = new int[Main.height][];
            for (int i = 0; i < Main.width; ++i)
                for (int j = 0; j < Main.height; ++j)
                    Main.imageArr[i][j] = new int[3];
            Main.counter = 0;
            Main.ctreuc.counter = 0;
            Main.ctrbmx.counter = 0;
            Main.ctrlex.counter = 0;
            for (int i = 0; i < Main.width; ++i) {
                for (int j = 0; j < Main.height; ++j) {
                    int rgb = buffer.getRGB(i, j);
                    Main.imageArr[i][j][0] = (rgb >> 16) & 0xFF;
                    Main.imageArr[i][j][1] = (rgb >> 8) & 0xFF;
                    Main.imageArr[i][j][2] = (rgb) & 0xFF;
                    System.out.printf("Thread1: [%d,%d,%d]\n", Main.imageArr[i][j][0], Main.imageArr[i][j][1], Main.imageArr[i][j][2]);
                    synchronized (Main.lexQ) {
                        Main.lexQ.add(Main.imageArr[i][j]);
                    }
                    synchronized (Main.ctrlex) {
                        ++Main.ctrlex.counter;
                    }
                    synchronized (Main.bmxQ) {
                        Main.bmxQ.add(Main.imageArr[i][j]);
                    }
                    synchronized (Main.ctrbmx) {
                        ++Main.ctrbmx.counter;
                    }
                    synchronized (Main.eucQ) {
                        Main.eucQ.add(Main.imageArr[i][j]);
                    }
                    synchronized (Main.ctreuc) {
                        ++Main.ctreuc.counter;
                    }
                    ++Main.counter;
                    if (Main.counter == 100) {
                        Main.eucTh = new PQEUC();
                        Main.lexTh = new PQLEX();
                        Main.bmxTh = new PQBMX();
                        Main.eucTh.start();
                        Main.lexTh.start();
                        Main.bmxTh.start();
                    }
                }
            }
            if (Main.counter < 100) {
                Main.eucTh = new PQEUC();
                Main.lexTh = new PQLEX();
                Main.bmxTh = new PQBMX();
                Main.eucTh.start();
                Main.lexTh.start();
                Main.bmxTh.start();
            }
        } catch (Exception e) {
            System.err.println("Oops!");
        }
    }

}
