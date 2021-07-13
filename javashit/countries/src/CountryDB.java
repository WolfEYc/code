import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class CountryDB {

    public static String sNeeded(String str, int total){
        int strlen = total - str.length();
        StringBuilder retstr = new StringBuilder();
        for(int i = 0; i < strlen; i++)
            retstr.append(" ");
        return retstr.toString();
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new BufferedReader(new FileReader("countries.txt")));

        ArrayList<Country> countryList = new ArrayList<>();

        while(in.hasNextLine()){
            String[] line = in.nextLine().split("\\|");
            countryList.add(new Country(line[0],line[1], line[2]));
        }

        BST<Country> countryBST = new BST<>(countryList);
        Heap<Country> countryHeap = new Heap<>(countryList);

        System.out.println("\nCharacteristics of the BST and Heap (sorted list)");
        System.out.println("BST - Number of leaf Nodes: " + countryBST.leafNodes());
        System.out.println("BST - Height of the tree: " + countryBST.height());
        System.out.println("BST - Is the BST balanced? " + countryBST.isBalanced());
        System.out.println("Heap - Number of leaf Nodes: " + countryHeap.leafNodes());
        System.out.println("Heap - Height of the tree: " + countryHeap.height());
        System.out.println("Heap - Is the Heap balanced? " + countryHeap.isBalanced() + "\n");
        System.out.println("List of countries from BST (inorder)");
        System.out.println("Code" + sNeeded("Code", 10) + "Name" + sNeeded("Name", 20) + "Area (sq.Km)");
        countryBST.inOrder();
        System.out.println("\nList of countries from Heap (delete)");
        while(!countryHeap.isEmpty()){
            System.out.println(countryHeap.delete());
        }

        Collections.shuffle(countryList);

        countryBST.clear();

        countryBST = new BST<>(countryList);
        countryHeap = new Heap<>(countryList);

        System.out.println("\nCharacteristics of the BST and Heap (shuffled list)");
        System.out.println("BST - Number of leaf Nodes: " + countryBST.leafNodes());
        System.out.println("BST - Height of the tree: " + countryBST.height());
        System.out.println("BST - Is the BST balanced? " + countryBST.isBalanced());
        System.out.println("Heap - Number of leaf Nodes: " + countryHeap.leafNodes());
        System.out.println("Heap - Height of the tree: " + countryHeap.height());
        System.out.println("Heap - Is the Heap balanced? " + countryHeap.isBalanced() + "\n");
        System.out.println("List of countries from BST (inorder)");
        System.out.println("Code" + sNeeded("Code", 10) + "Name" + sNeeded("Name", 20) + "Area (sq.Km)");
        countryBST.inOrder();
        System.out.println("\nList of countries from Heap (delete)");
        while(!countryHeap.isEmpty()){
            System.out.println(countryHeap.delete());
        }

    }
}
