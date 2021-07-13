import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import static java.util.Collections.swap;

public class Sort {
    public static int counter = 0;

    public static <E extends Comparable<E>> void selectionSort(ArrayList<E> list){
        int i,j,min, n = list.size();

        for(i=0;i<n-1;i++,counter++){
            min = i;
            for(j=i+1;j<n;j++, counter++){
                if(list.get(j).compareTo(list.get(min)) < 0){
                    min = j;
                }
            }
            if(min != i){
                swap(list ,i, min);
            }
        }
    }

    public static <E extends Comparable<E>> void insertionSort(ArrayList<E> list){
        int j;
        for (int i = 1 ; i < list.size(); i++) {
            counter++;
            E key = list.get(i);
            j = i - 1;
            while (j >= 0 && key.compareTo(list.get(j)) < 0) {
                list.set(j + 1, list.get(j));
                j--;
                counter++;
            }
            list.set(j + 1, key);
        }
    }

    public static <E extends Comparable<E>> void bubbleSort(ArrayList<E> list){
        for(int i = 0; i < list.size() - 1; i++, counter++){
            for(int j = 0; j < list.size() - i - 1; j++, counter++){
                if(list.get(j).compareTo(list.get(j+1)) > 0){
                    swap(list, j, j+1);
                }
            }
        }
    }

    public static <E> ArrayList<E> subList(ArrayList<E> list, int start, int end) {
        ArrayList<E> subArray = new ArrayList<>();
        for(int i = 0; i < end; i++, counter++)
            subArray.add(list.get(start + i));
        return subArray;
    }

    private static <E extends Comparable<E>> void merge (ArrayList<E> list, int left, int mid, int right){
        int sub1Idx = 0, sub2Idx = 0, mIdx = left;
        int subArrayOne = mid - left + 1;
        int subArrayTwo = right - mid;
        Sort.counter++;

        ArrayList<E> leftArray = subList(list, left, subArrayOne);
        ArrayList<E> rightArray = subList(list, mid+1, subArrayTwo);


        while(sub1Idx < leftArray.size() && sub2Idx < rightArray.size()){
            counter++;
            if(leftArray.get(sub1Idx).compareTo(rightArray.get(sub2Idx)) <= 0){
                list.set(mIdx++, leftArray.get(sub1Idx++));
            }else{
                list.set(mIdx++, rightArray.get(sub2Idx++));
            }
        }

        while(sub1Idx < leftArray.size()) {
            list.set(mIdx++, leftArray.get(sub1Idx++));
            counter++;
        }


        while(sub2Idx < rightArray.size()) {
            list.set(mIdx++, rightArray.get(sub2Idx++));
            counter++;
        }

    }

    private static <E extends Comparable<E>> void mergeSort(ArrayList<E> list, int start, int end) {
        if(start >= end)
            return;

        Sort.counter++;
        int mid = start + (end - start) / 2;
        mergeSort(list, start, mid);
        mergeSort(list, mid + 1, end);
        merge(list, start, mid, end);
    }

    public static <E extends Comparable<E>> void mergeSort(ArrayList<E> list) {
        mergeSort(list, 0, list.size()-1);
    }

    private static <E extends Comparable<E>> int partition (ArrayList<E> list, int low, int high){
        E pivot = list.get(high);
        int i = low - 1;
        Sort.counter++;
        for(int j = low; j < high; j++, counter++){
            if(list.get(j).compareTo(pivot) < 0){
                swap(list, ++i, j);
            }
        }
        swap(list, ++i, high);
        return i;
    }

    private static <E extends Comparable<E>> void quickSort(ArrayList<E> list, int low, int high){
        if(low < high){
            int pi = partition(list, low, high);
            Sort.counter++;
            quickSort(list, low, pi -1);
            quickSort(list, pi + 1, high);
        }
    }

    public static <E extends Comparable<E>> void quickSort(ArrayList<E> list){
        quickSort(list, 0, list.size() - 1);
    }

    public static <E extends Comparable<E>> void heapSort(ArrayList<E> list){
        Heap<E> heap = new Heap<>(list);
        for(int i = list.size() -1; i >= 0; i--)
            list.set(i, heap.delete());
    }
}
