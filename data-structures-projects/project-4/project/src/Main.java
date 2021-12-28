
public class Main {

    public static String imageName;
    public static int[][][] imageArr;
    public static int width;
    public static int height;
    public static PriorityQueue lexQ;
    public static PriorityQueue eucQ;
    public static PriorityQueue bmxQ;
    public static int counter;
    public static CTRLEX ctrlex;
    public static CTRBMX ctrbmx;
    public static CTREUC ctreuc;
    public static ImageTraverser imgTh;
    public static PQLEX lexTh;
    public static PQBMX bmxTh;
    public static PQEUC eucTh;

    public static void main(String[] args) {
        imageName = args[0];
        lexQ = new PriorityQueue("LEX");
        eucQ = new PriorityQueue("EUC");
        bmxQ = new PriorityQueue("BMX");
        ctrlex = new CTRLEX();
        ctrbmx = new CTRBMX();
        ctreuc = new CTREUC();
        imgTh = new ImageTraverser();
        imgTh.start();
    }

}
