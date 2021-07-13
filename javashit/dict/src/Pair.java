import java.lang.Comparable;

public class Pair<E1 extends Comparable<E1>, E2> implements Comparable<Pair<E1, E2>>{
    private E1 first;
    private E2 second;
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

    @Override
    public int compareTo(Pair<E1, E2> other) {
        return this.first.compareTo(other.getFirst());
    }
}