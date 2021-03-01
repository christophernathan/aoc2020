import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;

public class solve5{
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("input5.txt");
        Scanner input = new Scanner(file);
        ArrayList<String> passes = new ArrayList<String>();
        int[] existing = new int[1024];

        while (input.hasNextLine()){
            String pass = input.nextLine();
            passes.add(pass);
        }

        int greatest=0;

        for (String bp : passes){
            int key = calculateKey(bp, existing);
            if (key>greatest){ greatest=key; }
        }
        System.out.println(greatest);

        for (int i=1;i<1023;i++){
            if (existing[i-1]==1 && existing[i+1]==1 && existing[i]==0){
                System.out.println(i);
            }
        }
    }

    private static int calculateKey(String bp, int[] existing){
        int lower=0;
        int upper=127;
        for (int i=0;i<7;i++){
            char c = bp.charAt(i);
            if (c=='F'){ upper=(upper+lower)/2;}
            else if (c=='B'){ lower=(upper+lower)/2 + 1; }
        }
        int row=upper;
        lower=0; upper=7;
        for (int i=7;i<10;i++){
            char c = bp.charAt(i);
            if (c=='L'){ upper=(upper+lower)/2;}
            else if (c=='R'){ lower=(upper+lower)/2 + 1; }
        }
        int col=upper;
        int key=row*8+col;
        existing[key] = 1;
        return key;
    }
}