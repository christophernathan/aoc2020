import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

public class solve7{
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("input7.txt");
        Scanner input = new Scanner(file);
        HashMap<String, ArrayList<Pair<String, Integer>>> colors = new HashMap<String, ArrayList<Pair<String, Integer>>>();
        ArrayList<String> valid = new ArrayList<String>();
        while (input.hasNextLine()){
            String line = input.nextLine();
            String[] split = line.split(" ");
            String first = split[0]; String second = split[1];
            String key = first+second;
            colors.put(key,new ArrayList<Pair<String, Integer>>());
            for (int i=3;i<split.length;i++){
                if (split[i].startsWith("bag")){
                    first=split[i-2]; second=split[i-1];
                    String s = first+second;
                    if (!s.equals("noother")){ colors.get(key).add(Pair.createPair(s,Integer.parseInt(split[i-3]))); }
                }
            }
        }

        for (String key : colors.keySet()){
            boolean add = false;
            for (Pair<String,Integer> p : colors.get(key)){
                if (containsGold(p.getKey(), colors)){ add=true; break; }
            }
            if (add==true && !key.equals("shinygold") && !valid.contains(key)){ valid.add(key); }
        }

        System.out.println(valid.size());
        System.out.println(count("shinygold", colors)-1);
    }

    private static boolean containsGold(String s, HashMap<String, ArrayList<Pair<String,Integer>>> colors){
        if (s.equals("shinygold")){ return true; }
        for (Pair<String,Integer> p : colors.get(s)){
            if (containsGold(p.getKey(), colors)){ return true; }
        }
        return false;
    }

    private static Integer count(String s, HashMap<String, ArrayList<Pair<String,Integer>>> colors){
        Integer total=1;
        if (colors.get(s).size() == 0){ return total; }
        for (Pair<String,Integer> p : colors.get(s)){
            total+=p.getValue()*count(p.getKey(), colors);
        }
        return total;
    }
}

class Pair<String, Integer> {

    private final String key;
    private final Integer value;

    public static <String, Integer> Pair<String, Integer> createPair(String key, Integer value) {
        return new Pair<String, Integer>(key,value);
    }

    public Pair(String key, Integer value) {
        this.key = key;
        this.value = value;
    }

    public String getKey() {
        return key;
    }

    public Integer getValue() {
        return value;
    }

}
