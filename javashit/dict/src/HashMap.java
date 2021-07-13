import java.util.ArrayList;
import java.util.LinkedList;

public class HashMap<K,V> {
    private int counter;
    private int size;
    private final double loadFactor;
    private Object[] hashTable;

    //Inner class hash Map Entry
    private class MapEntry{
        K key;
        V value;
        MapEntry(K k, V v){
            key = k; value = v;
        }
        K getKey(){ return key;}
        V getValue(){return value;}
        public String toString(){
            return "("+ key + "," + ")";
        }
    }
    //constructors
    public HashMap(){
        this(100, 0.9);
    }
    public HashMap(int c){
        this(c,0.9);
    }
    public HashMap(int c, double lf){
        hashTable = new Object[trimToPowerOf2(c)];
        loadFactor=lf;
    }
    //private methods
    private int trimToPowerOf2(int c) {
        return c << 1;
    }
    private int hash(int hashCode){
        return Math.abs(hashCode) % hashTable.length;
    }
    private void rehash(){
        ArrayList<MapEntry> list = toList();
        hashTable = new Object[trimToPowerOf2(hashTable.length)];
        size = 0;
        for(MapEntry entry: list)
            put(entry.getKey(),entry.getValue());
    }
    //public interface
    public int size(){
        return size;
    }
    public void clear(){
        size=0;
        for(int i=0; i<hashTable.length; i++)
            if (hashTable[i] != null)
                ((LinkedList<MapEntry>) (hashTable[i])).clear();
    }
    public int maxCollisions(){
        int max = 0;
        for(int i=0; i<hashTable.length; i++)
            if (hashTable[i] != null)
                if( ((LinkedList<MapEntry>) (hashTable[i])).size() > max )
                    max = ((LinkedList<MapEntry>) (hashTable[i])).size();
        return max;
    }

    public boolean isEmpty(){
        return (size ==0);
    }
    // search for the key in the hash map, returns true if found
    public boolean containsKey(K key){
        if(get(key) != null)
            return true;
        return false;
    }
    // returns the value of key if found, otherwise null
    public V get(K key){
        counter = 1;
        int bucketIndex = hash(key.hashCode());
        if(hashTable[bucketIndex] != null){
            LinkedList<MapEntry> bucket = (LinkedList<MapEntry>) (hashTable[bucketIndex]);
            for(MapEntry entry: bucket){
                counter++;
                if(entry.getKey().equals(key))
                    return entry.getValue();
            }
        }
        return null;
    }
    //remove a key if found
    public void remove(K key){
        int bucketIndex = hash(key.hashCode());
        if (hashTable[bucketIndex] != null){
            LinkedList<MapEntry> bucket = (LinkedList<MapEntry>) (hashTable[bucketIndex]);
            for(MapEntry entry: bucket){
                if(entry.getKey().equals(key)){
                    bucket.remove(entry);
                    size--;
                    break;
                }
            }
        }
    }
    // adds new key or modifies an existing key
    public V put(K key, V value){
        if(get(key) != null ){
            int bucketIndex = hash(key.hashCode());
            LinkedList<MapEntry> bucket = (LinkedList<MapEntry>) (hashTable[bucketIndex]);
            for(MapEntry entry: bucket) {
                if (entry.getKey().equals(key)){
                    V old = entry.getValue();
                    entry.value =value; return old;
                }
            }
        }
        // key not in the hash map - check load factor
        if (size >= hashTable.length * loadFactor)
            rehash();
        int bucketIndex = hash(key.hashCode());
        //create a new bucket if bucket is empty
        if (hashTable[bucketIndex] == null){
            hashTable[bucketIndex] = new LinkedList<MapEntry>();
        }
        ((LinkedList<MapEntry>) (hashTable[bucketIndex])).add(new MapEntry(key, value));
        size++;
        return value;
    }
    //returns the elements of the hash map as a list
    public ArrayList<MapEntry> toList(){
        ArrayList<MapEntry> list = new ArrayList<>();
        for(int i=0; i< hashTable.length; i++){
            if(hashTable[i]!=null){
                LinkedList<MapEntry> bucket = (LinkedList<MapEntry>) (hashTable[i]);
                list.addAll(bucket);
            }
        }
        return list;
    }
    public int getCounter(){
        return counter;
    }

    public void resetCounter(){
        counter = 0;
    }

    //returns the elements of the hashmap as a string
    public String toString(){
        StringBuilder out = new StringBuilder("[");
        for (int i=0;i<hashTable.length; i++){
            if(hashTable[i] !=null){
                for(MapEntry entry : (LinkedList<MapEntry>) (hashTable[i]))
                    out.append(entry.toString());
                out.append("\n");
            }
        }
        out.append("]");
        return out.toString();
    }
}


