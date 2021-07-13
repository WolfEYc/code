import java.util.ArrayList;
import java.util.Collections;

public class TestSorting {
    public static String sNeeded(String str, int total){
        int strlen = total - str.length();
        StringBuilder retstr = new StringBuilder();
        for(int i = 0; i < strlen; i++)
            retstr.append(" ");
        return retstr.toString();
    }

    public static void main(String[] args) {

        int size = 10000;
        ArrayList<Integer> list = new ArrayList<>();

        for(int i = 0; i < size; i++){
            list.add((int) (Math.random() * 99999 + 1));
        }

        System.out.println("\nSize: "+ size);
        System.out.println("\nSorting Algorithm" + sNeeded("Sorting Algorithm",20) + "Number of iterations");

        Sort.selectionSort(list);

        System.out.println("Selection Sort"+sNeeded("Selection Sort",20)+Sort.counter);
        Sort.counter = 0;

        Collections.shuffle(list);
        Sort.insertionSort(list);

        System.out.println("Insertion Sort"+sNeeded("Insertion Sort",20)+Sort.counter);
        Sort.counter = 0;

        Collections.shuffle(list);
        Sort.bubbleSort(list);

        System.out.println("Bubble Sort"+sNeeded("Bubble Sort",20)+Sort.counter);
        Sort.counter = 0;

        Collections.shuffle(list);
        Sort.mergeSort(list);

        System.out.println("Merge Sort"+sNeeded("Merge Sort",20)+Sort.counter);
        Sort.counter = 0;

        Collections.shuffle(list);
        Sort.quickSort(list);

        System.out.println("Quick Sort"+sNeeded("Quick Sort",20)+Sort.counter);
        Sort.counter = 0;

        Collections.shuffle(list);
        Sort.heapSort(list);

        System.out.println("Heap Sort"+sNeeded("Heap Sort",20)+Sort.counter);
        Sort.counter = 0;

    }
}
