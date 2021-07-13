import java.util.*;
import java.io.*;

public class Dictionary {

    public static String sNeeded(String str, int total){
        int strlen = total - str.length();
        String retstr = "";
        for(int i = 0; i < strlen; i++)
            retstr += " ";
        return retstr;
    }

    public static void main(String[] args) throws FileNotFoundException {
        ArrayList<Pair<String, String>> list = new ArrayList<>();

        Scanner in = new Scanner(new BufferedReader(new FileReader("Dictionary.txt")));

        while(in.hasNextLine()){
            String line = in.nextLine();
            String first = line.substring(1,line.indexOf('|')-1);
            String last = line.substring(line.indexOf("|")+2,line.lastIndexOf('\"'));
            if(first.equals("Scan")){
                in.nextLine();
                in.nextLine();
            }
            list.add(new Pair<String,String>(first, last));
        }


        BST<Pair<String, String>> BSTDictionary = new BST<>();
        LinkedList<Pair<String,String>> LLDictionary = new LinkedList<>();
        HashMap<String,String> dictionary = new HashMap<>(list.size());



        Collections.shuffle(list);

        for(Pair<String,String> item: list){
            BSTDictionary.insert(item);
            LLDictionary.addLast(item);
            dictionary.put(item.getFirst(), item.getSecond());
        }

        double BSTavg = 0, LLavg = 0, Hashavg = 0;

        for(int i = 0; i < 100; i++){
            int randInd = (int) (Math.random() * list.size());
            Pair<String, String> randWord = list.get(randInd);
            BSTavg += BSTDictionary.search(randWord);
            LLavg += LLDictionary.search(randWord);
            dictionary.get(randWord.getFirst());
            Hashavg += dictionary.getCounter();
            dictionary.resetCounter();
        }

        BSTavg/=100; LLavg/=100; Hashavg/=100;

        System.out.println("Average number of iterations to find words in the dictionary");
        System.out.println("LL" + sNeeded("LL",20) + "BST" + sNeeded("BST",20) + "HashMap");
        System.out.println(LLavg + sNeeded(LLavg+"",20) + BSTavg + sNeeded(BSTavg+"",20) + Hashavg);
        System.out.println("\nMaximum number of collisions: "+ dictionary.maxCollisions());

        //Pair<String,String>  x = new Pair<HashMap,Dictionary>(50000);

    }

}
