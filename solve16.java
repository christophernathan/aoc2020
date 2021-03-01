import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

public class solve16{
    public static void main(String[] args) throws FileNotFoundException{
        File file = new File("input16.txt");
        Scanner input = new Scanner(file);
        ArrayList<ArrayList<String>> fields = new ArrayList<ArrayList<String>>();
        ArrayList<String> rawRules = new ArrayList<String>();
        ArrayList<ArrayList<Integer>> tickets = new ArrayList<ArrayList<Integer>>();
        ArrayList<Integer> myTicket = new ArrayList<Integer>();

        String field="";
        while (input.hasNextLine()){
            field=input.nextLine();
            if (field.equals("")){ break; }
            String[] split = field.split(" ");
            ArrayList<String> rules = new ArrayList<String>();
            for (String s : split){
                if (s.contains("-")){
                    rules.add(s);
                    rawRules.add(s);
                }
            }
            fields.add(rules);
        }
        input.nextLine(); 
        String ticket = input.nextLine(); 
        String[] split = ticket.split(",");
        for (String s : split){
            myTicket.add(Integer.parseInt(s));
        }
        input.nextLine(); input.nextLine();
        while (input.hasNextLine()){
            String next=input.nextLine();
            ArrayList<Integer> toCheck = new ArrayList<Integer>();
            split = next.split(",");
            for (String s : split){
                toCheck.add(Integer.parseInt(s));
            }
            tickets.add(toCheck);
        }
        
        Integer sum=0;
        for (ArrayList<Integer> a : tickets){
            for (Integer i : a){
            if (!check(i,rawRules)){ sum+=i; break;}
            //   System.out.println(i)
            }
        }
        System.out.println("Part 1: " + sum);

        ArrayList<ArrayList<Integer>> validTickets = removeInvalid(tickets,rawRules);
        for (ArrayList<Integer> a : validTickets){
            for (Integer i : a){
                System.out.print(i + " ");
            }
            System.out.println();
        }
        System.out.println();

       //checkIndex(0,fields.get(0),validTickets);
        HashMap<Integer,ArrayList<Integer>> indices = identifyIndices(fields, validTickets);
        System.out.println(indices.keySet());
        for (int i=0;i<indices.size();i++){
            System.out.println(i+1 + ": "  +indices.get(i));
        }
        long product=1;
        int[] departureIndices = {19,17,15,2,6,16};
        for (int i : departureIndices){
            product*=myTicket.get(i);
        }
        System.out.println(product);
    }

    public static HashMap<Integer,ArrayList<Integer>> identifyIndices(ArrayList<ArrayList<String>> fields, ArrayList<ArrayList<Integer>> tickets){
        HashMap<Integer,ArrayList<Integer>> ret = new HashMap<Integer,ArrayList<Integer>>();
        for (int i=0;i<fields.size();i++){
            int satisfies=0;
            for (int a=0;a<fields.size();a++){
                if (checkIndex(a,fields.get(i), tickets)){ 
                    if (!ret.containsKey(i)){
                        ret.put(i,new ArrayList<Integer>()); 
                    }
                    ret.get(i).add(a);
                    }
            }
            System.out.println(satisfies);
        }
        return ret;
    }

    public static ArrayList<ArrayList<Integer>> removeInvalid(ArrayList<ArrayList<Integer>> tickets, ArrayList<String> rawRules){
        ArrayList<ArrayList<Integer>> ret = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> a : tickets){
            boolean add=true;
            for (Integer i : a){
                if (!check(i,rawRules)){ add=false; break; }
            }
            if (add){ ret.add(a); }
        }
        return ret;
    }

    public static boolean check(Integer toCheck, ArrayList<String> rawRules){
        for (int i=0;i<rawRules.size();i++){
            String[] split = rawRules.get(i).split("-");
            if (toCheck>=Integer.parseInt(split[0]) && toCheck<=Integer.parseInt(split[1])){ return true; }
        }
        return false;
    }

    public static boolean checkIndex(Integer indexToCheck, ArrayList<String> field, ArrayList<ArrayList<Integer>> tickets){
        for (int i=0;i<tickets.size();i++){
            int curr = (tickets.get(i)).get(indexToCheck);
            boolean pass=false;
            for (int a=0;a<field.size();a++){
                String[] split = field.get(a).split("-");
                if (curr>=Integer.parseInt(split[0]) && curr<=Integer.parseInt(split[1])){ pass=true; }
            }
            if (!pass){ return false; }
        }
        return true;
    }
}