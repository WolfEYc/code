/*
public class Item<T extends Comparable<T>> implements Comparable<Item> {
    private int s;
    private T t;
    public T getT() {
        return t;
    }
    @Override
    public int compareTo(Item o) {
        return getT().compareTo(o.getT());
    }
}
*/
public class Pair<E1 extends Comparable<E1>,E2> implements Comparable<E1> {
    private E1 first;
    private E2 second;
    interface Comparable<E1>{
        int compareTo(E1 obj);
    }
    @Override
    public int compareTo(E1 obj){
        return getFirst().compareTo(obj);
    }
    public Pair(E1 first, E2 second) {
        this.first = first;
        this.second = second;
    }
    public void setFirst(E1 first) {
        this.first = first;
    }
    public void setSecond(E2 second) {
        this.second = second;
    }
    public E1 getFirst() {
        return first;
    }
    public E2 getSecond() {
        return second;
    }
    public String toString() {
        return "(" + first.toString() + ", " +
                second.toString() + ")";
    }
    public boolean equals(Object obj) {
        Pair<E1, E2> pair = (Pair<E1, E2>) obj;
        boolean eq = pair.getFirst().equals(first);
        eq = eq && pair.getSecond().equals(second);
        return eq;
    }
}