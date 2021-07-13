import java.util.ArrayList;

public class Heap<T extends Comparable<T>> {
    private ArrayList<T> elements;

    public Heap(){
        elements = new ArrayList<T>();
    }

    public Heap(ArrayList<T> list){
        this();
        for(T item : list)
            insert(item);
    }

    public int size(){
        return elements.size();
    }

    public boolean isEmpty(){
        return elements.isEmpty();
    }

    public void clear(){
        elements.clear();
    }

    //O(n)
    public boolean search(T item){
        for(T value : elements) {
            if (value == item)
                return true;
        }
        return false;
    }

    //0(log(n))
    public boolean insert(T item){
        int currInd = elements.size();
        elements.add(item);
        Sort.counter++;

        while(currInd > 0){
            Sort.counter++;
            int parentInd = (currInd-1)/2;
            T curr = elements.get(currInd);
            T parent = elements.get(parentInd);
            if(curr.compareTo(parent) > 0){
                elements.set(currInd, parent);
                elements.set(parentInd, curr);
                currInd = parentInd;
            }else
                break;
        }
        return true;
    }

    //O(log(n))
    public T delete(){
        if(isEmpty()) return null;
        T removedItem = elements.get(0);
        elements.set(0, elements.get(elements.size()-1));
        elements.remove(elements.size()-1);
        int currentIndex = 0;
        Sort.counter++;

        while (currentIndex < elements.size()) {
            Sort.counter++;
            int left = 2 * currentIndex + 1;
            int right = 2 * currentIndex + 2;
            if (left >= elements.size()) break;//reached the end
            int maxIndex = left;
            T max = elements.get(maxIndex);
            if (right < elements.size())
                if(max.compareTo(elements.get(right)) < 0)
                    maxIndex = right;
            T current = elements.get(currentIndex);
            max = elements.get(maxIndex);
            if(elements.get(currentIndex).compareTo(max) < 0)
            {
                elements.set(maxIndex, current);
                elements.set(currentIndex, max);
                currentIndex = maxIndex;
            }
            else
                break; // the tree is a heap
        }
        return removedItem;
    }

    //O(n)
    private int leafNodes(int currIdx){

        if(currIdx >= size())
            return 0;

        int leftIdx = 2 * currIdx + 1;
        int rightIdx = 2 * currIdx + 2;

        if(leftIdx >= size())
            return 1;

        return leafNodes(leftIdx) + leafNodes(rightIdx);
    }

    public int leafNodes(){
        return leafNodes(0);
    }

    //O(n)
    private int height(int currIdx){
        if(currIdx >= size())
            return 0;

        int leftIdx = 2 * currIdx + 1;
        int rightIdx = 2 * currIdx + 2;

        return 1 + Math.max(height(leftIdx), height(rightIdx));
    }

    public int height(){
        return height(0);
    }

    //O(n)
    private boolean isBalanced(int currIdx){
        if(currIdx >= size())
            return true;

        int leftIdx = 2 * currIdx + 1;
        int rightIdx = 2 * currIdx + 2;

        int left = height(leftIdx);
        int right = height(rightIdx);

        if(left >= right - 1 && left <= right + 1)
            return isBalanced(leftIdx) && isBalanced(rightIdx);

        return false;
    }

    public boolean isBalanced(){
        return isBalanced(0);
    }

    public String toString(){
        return elements.toString();
    }
}
