import java.util.ArrayList;

public class Heap<T extends Comparable<T>> {
    private ArrayList<T> heap;

    public Heap(){
        heap = new ArrayList<T>();
    }

    public int insert(T item){
        int counter = 0;
        int currInd = heap.size();
        heap.add(item);

        while(currInd > 0){
            counter++;
            int parentInd = (currInd-1)/2;
            T curr = heap.get(currInd);
            T parent = heap.get(parentInd);
            if(curr.compareTo(parent) > 0){
                heap.set(currInd, parent);
                heap.set(parentInd, curr);
                currInd = parentInd;
            }else
                break;
        }
        return counter;
    }

    public int search(T item){
        int counter = 0;
        for(T value : heap) {
            counter++;
            if (value == item)
                return counter;
        }
        return counter;
    }


}
