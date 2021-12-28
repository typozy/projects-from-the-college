import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        int width = 0;
        int height = 0;
        Scanner in = new Scanner(System.in);
        while(width <= 0 || height <= 0) {
            System.out.println("Enter the width: ");
            width = in.nextInt();
            System.out.println("Enter the height: ");
            height = in.nextInt();
            if(width <= 0 || height <= 0)
                System.out.println("Please enter positive numbers!");
        }
        int[][] array = new int[height][];
        for(int i=0; i<height;++i)
            array[i] = new int[width];
        for(int i=0; i<height; ++i)
            for(int j=0; j<width; ++j)
                array[i][j] = i*width + j + 1;
        iterate(array);
    }

    public static void iterate(int[][] arr){
        int width = arr[0].length;
        int height = arr.length;
        int[][] arr2D;
        arr2D = new int[height+2][];
        for(int i=0; i<height+2; ++i)
            arr2D[i] = new int[width+2];
        for(int i=0; i<height+2; ++i){
            for(int j=0; j<width+2; ++j){
                if(i==0 || i==height+1 || j==0 || j==width+1)
                    arr2D[i][j] = -1;
                else
                    arr2D[i][j] = arr[i-1][j-1];
            }
        }
        System.out.println("Map:");
        for(int i=1; i<height+1; ++i){
            for(int j=1; j<width+1; ++j){
               System.out.printf("%2d ",arr2D[i][j]);
            }
            System.out.printf("\n");
        }
        System.out.println("Iteration:");
        boolean end = false;
        int i = 1;
        int j = 1;
        String way;
        if(width == 1)
            way = "down";
        else
            way = "right";
        System.out.printf("%d ",arr2D[i][j]);
        arr2D[i][j] = -1;
        while(!end){
            if(way.equals("right")){
                if(arr2D[i][j+1] == -1){
                    end = true;
                    break;
                }
                while(arr2D[i][j+1] != -1){
                    System.out.printf("%d ",arr2D[i][j+1]);
                    arr2D[i][j+1] = -1;
                    ++j;
                }
                way = "down";
            }
            if(way.equals("down")){
                if(arr2D[i+1][j] == -1){
                    end = true;
                    break;
                }
                while(arr2D[i+1][j] != -1){
                    System.out.printf("%d ",arr2D[i+1][j]);
                    arr2D[i+1][j] = -1;
                    ++i;
                }
                way = "left";
            }
            else if(way.equals("left")){
                if(arr2D[i][j-1] == -1){
                    end = true;
                    break;
                }
                while(arr2D[i][j-1] != -1){
                    System.out.printf("%d ",arr2D[i][j-1]);
                    arr2D[i][j-1] = -1;
                    --j;
                }
                way = "up";
            }
            else{
                if(arr2D[i-1][j] == -1){
                    end = true;
                    break;
                }
                while(arr2D[i-1][j] != -1){
                    System.out.printf("%d ",arr2D[i-1][j]);
                    arr2D[i-1][j] = -1;
                    --i;
                }
                way = "right";
            }
        }

    }

}