import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;

public class solve6{
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("input6.txt");
        Scanner input = new Scanner(file);
        ArrayList<String> groups = new ArrayList<String>();
        ArrayList<ArrayList<Character>> answers = new ArrayList<ArrayList<Character>>();
        ArrayList<Integer> num = new ArrayList<Integer>();

        String group = "";
        while (input.hasNextLine()){
            String line = input.nextLine();
            if (line.equals("")){
                groups.add(group);
                group = "";
            }
            else{
                group += line + " ";
            }
        }
        groups.add(group);

        int g=0;
        for (String s : groups){
            answers.add(existsIn(s));
            g++;
        }
        int total=0;
        for (int i=0;i<answers.size();i++){
            total+=answers.get(i).size();
            System.out.println(answers.get(i).size());
        }
        System.out.println(total);
        
    }
    private static ArrayList<Character> existsIn(String s){
        ArrayList<Character> ret = new ArrayList<Character>();
        String[] split = s.split(" ");
        System.out.println(s);
        System.out.println(split[0]);
        for (int i=0;i<split[0].length();i++){
            char c = split[0].charAt(i);
            System.out.println(c);
            boolean add = true;
            for (String p : split){
                System.out.println(p);
                boolean common = false;
                for (int a=0;a<p.length();a++){
                    char r = p.charAt(a);
                    if (r==c){ common = true; }
                }
                if (common == false){ add = false; }
            }
            for (char r : ret) {
                if (c==r){ add=false; }
            }
            if (add) { ret.add(c); }
        }
        System.out.println(ret);
        return ret;
    }
}