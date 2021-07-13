import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class AnimalDB {
    public static String sNeeded(String str, int total){
        int strlen = total - str.length();
        String retstr = "";
        for(int i = 0; i < strlen; i++)
            retstr += " ";
        return retstr;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner fin = new Scanner(new BufferedReader(new FileReader("animals.txt")));

        ArrayList<String> animalAL = new ArrayList<String>();
        BST<String> animalBST = new BST<String>();
        Heap<String> animalHeap = new Heap<String>();

        fin.nextLine();
        while(fin.hasNextLine()){
            animalAL.add(fin.nextLine());
        }

        int avgBST = 0, avgHeap = 0;

        for(String str : animalAL){
            avgBST += animalBST.insert(str);
            avgHeap += animalHeap.insert(str);
        }

        avgBST/=animalAL.size();
        avgHeap/= animalAL.size();

        System.out.println("\nAverage number of iterations for Insert operations (unsorted list)");
        System.out.println("BST insert\t\tHeap insert");
        System.out.println(avgBST + "\t\t\t\t" + avgHeap);

        System.out.println("\nAverage number of iterations for Search operations (unsorted list)");
        System.out.println("Name"+sNeeded("Name",30) + "BST search\t\t\tHeap search");
        for(int i = 0; i < 20; i++) {
            int randy = (int) (Math.random() * animalAL.size());
            String toSearch = animalAL.get(randy);
            int bstItr = animalBST.search(toSearch);
            int heapItr = animalHeap.search(toSearch);
            System.out.println(toSearch + sNeeded(toSearch,30) + bstItr + sNeeded(""+bstItr,22) + heapItr);
        }

        //resetting data structures for sorted operation
        animalBST = new BST<String>();
        animalHeap = new Heap<String>();

        //sort animalAL
        Collections.sort(animalAL);

        avgBST = 0; avgHeap = 0;

        for(String str : animalAL){
            avgBST += animalBST.insert(str);
            avgHeap += animalHeap.insert(str);
        }

        avgBST/=animalAL.size();
        avgHeap/= animalAL.size();

        System.out.println("\nAverage number of iterations for Insert operations (sorted list)");
        System.out.println("BST insert\t\tHeap insert");
        System.out.println(avgBST + "\t\t\t\t" + avgHeap);

        System.out.println("\nAverage number of iterations for Search operations (sorted list)");
        System.out.println("Name"+sNeeded("Name",30) + "BST search\t\t\tHeap search");
        for(int i = 0; i < 20; i++) {
            int randy = (int) (Math.random() * animalAL.size());
            String toSearch = animalAL.get(randy);
            int bstItr = animalBST.search(toSearch);
            int heapItr = animalHeap.search(toSearch);
            System.out.println(toSearch + sNeeded(toSearch,30) + bstItr + sNeeded(""+bstItr,22) + heapItr);
        }

    }
}
