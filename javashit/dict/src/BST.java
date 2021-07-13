class node<T>{
    public T val;
    public node<T> left;
    public node<T> right;
    public node (T value){
        this.val = value;
        this.right = null;
        this.left = null;
    }
}

public class BST<T extends Comparable<T>> {
    node<T> root;

    private int counter;

    public BST(){
        root = null;
        counter = 0;
    }

    private node<T> insert(node<T> node, T value){
        counter++;
        if(node == null) //normal BST insert
            return new node<T>(value);

        if(value.compareTo(node.val) > 0)
            node.right = insert(node.right, value);
        else if (value.compareTo(node.val) < 0)
            node.left = insert(node.left, value);

        return node;
    }

    public int insert(T value){
        counter = 0;
        root = insert(root, value);
        return counter;
    }

    private int search(node<T> node, T value){
        if(node == null || node.val == value)
            return 0;

        if(value.compareTo(node.val) > 0)
            return 1 + search(node.right, value);

        return 1 + search(node.left, value);
    }

    public int search(T value){
        return search(root, value);
    }

    private void inOrder(node<T> node){
        if(node == null)
            return;

        inOrder(node.left);
        System.out.println(node.val);
        inOrder(node.right);
    }

    public void inOrder(){
        inOrder(root);
    }
}
