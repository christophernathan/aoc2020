import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

public class solve8{
    public static int acc = 0;

    public static void main(String[] args) throws FileNotFoundException{
        File file = new File("input8.txt");
        Scanner input = new Scanner(file);
        ArrayList<String> operations = new ArrayList<String>();

        while (input.hasNextLine()){
            operations.add(input.nextLine());
        }
        int[] visited = new int[operations.size()];
        System.out.println(visited[0]);
      System.out.println(tryAll(operations, visited));
    }

    private static int executeOperation(int i, int flip, ArrayList<String> operations, int[] visited){
        if (i>=operations.size()){ return 1; }
        if (visited[i]!=0){ return 0; }
        String s = operations.get(i);
        String[] split = s.split(" ");
        int value = Integer.parseInt(split[1].substring(1));

        if (s.startsWith("nop") || (s.startsWith("jmp")&&i==flip)){ 
            visited[i]++;
            return executeOperation(i+1, flip, operations, visited);
        }
        else if (s.startsWith("acc")){
            if (split[1].charAt(0) == '+'){ acc += value; }
            else{ acc -= value; }
            visited[i]++;
            return executeOperation(i+1, flip, operations, visited);
        }
        else if (s.startsWith("jmp") || (s.startsWith("nop")&&i==flip)){
            visited[i]++;
            if (split[1].charAt(0) == '+'){ return executeOperation(i+value, flip, operations, visited); }
            else{ return executeOperation(i-value, flip, operations, visited);}
        }
        return 0;
    }

    private static int tryAll(ArrayList<String> operations, int[] visited){
        for (int i=0; i<operations.size();i++){
            acc=0;
            visited = new int[operations.size()];
            if (executeOperation(0, i, operations, visited)==1){ return acc; }
        }
        return 0;
    }
}