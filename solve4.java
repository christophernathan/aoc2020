import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;

public class solve4{
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("input4.txt");
        Scanner input = new Scanner(file);
        ArrayList<String> passports = new ArrayList<String>();

        String passport = "";
        while (input.hasNextLine()){
            String line = input.nextLine();
            if (line.equals("")){
                passports.add(passport);
                passport="";
            }
            else{
                passport += " " + line;
            }
        }
        passports.add(passport);

        int legal=0;
        int valid=0;

        for (String pp : passports){
            if (isLegal(pp)){ legal++; }
        }
        for (String pp : passports){
            if (isLegal(pp) && isValid(pp)){ valid++; }
        }
        System.out.println(legal);
        System.out.println(valid);
    }

    private static boolean isValid(String pp){
        String[] split = pp.split(" ");
        for (String s : split){
            if (s.startsWith("byr:") && !s.replace("byr:", "").matches("19[2-9][0-9]|200[0-2]")){ return false; }
            else if (s.startsWith("iyr:") && !s.replace("iyr:", "").matches("201[0-9]|2020")){ return false; }
            else if (s.startsWith("eyr:") && !s.replace("eyr:", "").matches("202[0-9]|2030")){ return false; }
            else if (s.startsWith("hgt:") && !s.replace("hgt:", "").matches("1[5-8][0-9]cm|19[0-3]cm|59in|6[0-9]in|7[0-6]in")){ return false; }
            else if (s.startsWith("hcl:") && !s.replace("hcl:", "").matches("#[0-9a-f]{6}")){ return false; }
            else if (s.startsWith("ecl:") && !s.replace("ecl:", "").matches("amb|blu|brn|gry|grn|hzl|oth")){ return false; }
            else if (s.startsWith("pid:") && !s.replace("pid:", "").matches("[0-9]{9}")){ return false; }
        }
        return true;
    }

    private static boolean isLegal(String pp){
        return pp.contains("byr:") && pp.contains("iyr:") && pp.contains("eyr:") 
        && pp.contains("hgt:") && pp.contains("hcl:") && pp.contains("ecl:") 
        && pp.contains("pid:");
    }
}
