import java.util.Comparator;

public class QueueComparator implements Comparator {


    public static int compare(int[] o1, int[] o2, String type) {
        if (type.compareTo("LEX") == 0) {
            if (o1[0] > o2[0])
                return 1;
            if (o1[0] < o2[0])
                return -1;
            if (o1[1] > o2[1])
                return 1;
            if (o1[1] < o2[1])
                return -1;
            if (o1[2] > o2[2])
                return 1;
            if (o1[2] < o2[2])
                return -1;
            return 0;
        } else if (type.compareTo("EUC") == 0) {
            if ((o1[0] * o1[0] + o1[1] * o1[1] + o1[2] * o1[2]) > (o2[0] * o2[0] + o2[1] * o2[1] + o2[2] * o2[2]))
                return 1;
            if ((o1[0] * o1[0] + o1[1] * o1[1] + o1[2] * o1[2]) < (o2[0] * o2[0] + o2[1] * o2[1] + o2[2] * o2[2]))
                return -1;
            return 0;
        } else {
            int[] rgb1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int[] rgb2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int red1 = o1[0];
            int green1 = o1[1];
            int blue1 = o1[2];
            int red2 = o2[0];
            int green2 = o2[1];
            int blue2 = o2[2];
            int step = 7;
            for (int bit = 128; bit > 0; bit /= 2) {
                if (red1 >= bit) {
                    rgb1[3 * step + 2] = 1;
                    red1 -= bit;
                }
                if (red2 >= bit) {
                    rgb2[3 * step + 2] = 1;
                    red2 -= bit;
                }
                if (green1 >= bit) {
                    rgb1[3 * step + 1] = 1;
                    green1 -= bit;
                }
                if (green2 >= bit) {
                    rgb2[3 * step + 1] = 1;
                    green2 -= bit;
                }
                if (blue1 >= bit) {
                    rgb1[3 * step] = 1;
                    blue1 -= bit;
                }
                if (blue2 >= bit) {
                    rgb2[3 * step] = 1;
                    blue2 -= bit;
                }
                --step;
            }
            for (int i = 23; i >= 0; --i) {
                if (rgb1[i] > rgb2[i])
                    return 1;
                if (rgb1[i] < rgb2[i])
                    return -1;
            }
            return 0;
        }
    }

    @Override
    public int compare(Object o1, Object o2) {
        return 0;
    }

}
