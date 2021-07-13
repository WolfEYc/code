import java.util.ArrayList;


public class BST<T extends Comparable<T>> {

    private static class node<T>{
        public T val;
        public node<T> left;
        public node<T> right;
        public node (T value){
            this.val = value;
            this.right = null;
            this.left = null;
        }
    }

    node<T> root;

    private int counter;
    private int size;

    public BST(){
        root = null;
        counter = 0;
        size = 0;
    }

    public BST(ArrayList<T> list){
        this();
        for(T item : list)
            insert(item);
    }

    public int size(){
        return size;
    }

    public boolean isEmpty(){
        return size == 0;
    }

    public void clear(){
        root = null;
        size = 0;
    }

    private int leafNodes(node<T> node){
        if(node == null)
            return 0;

        if(node.right == null && node.left == null)
            return 1;

        return leafNodes(node.left) + leafNodes(node.right);
    }

    public int leafNodes(){
        return leafNodes(root);
    }

    private int height(node<T> node){
        if(node == null)
            return 0;

        return 1 + Math.max(height(node.left), height(node.right));
    }

    //O(n) with n being the number of elements
    public int height(){
        return height(root);
    }

    private boolean isBalanced(node<T> node){
        if(node == null)
            return true;

        int left = height(node.left);
        int right = height(node.right);
        if(left >= right - 1 && left <= right + 1)
            return isBalanced(node.left) && isBalanced(node.right);

        return false;
    }

    public boolean isBalanced(){
        return isBalanced(root);
    }

    private node<T> minValueNode(node<T> node){
        if(node.left == null)
            return node;
        return minValueNode(node.left);
    }

    private node<T> maxValueNode(node<T> node){
        if(node.right == null)
            return node;
        return maxValueNode(node.right);
    }



    //actual recursive insert method
    private node<T> insert(node<T> node, T value){
        if(node == null) { //normal BST insert
            size++;
            return new node<T>(value);
        }

        if(value.compareTo(node.val) > 0)
            node.right = insert(node.right, value);
        else if (value.compareTo(node.val) < 0)
            node.left = insert(node.left, value);

        return node;
    }

    //utility method
    //O(h) with h being the height of the tree
    public boolean insert(T value){
        int prevSize = size;
        root = insert(root, value);
        return size != prevSize;
    }

    public node<T> delete(node<T> node, T key)
    {
        // base case
        if (node == null)
            return null;

        // If the key to be deleted is
        // smaller than the root's
        // key, then it lies in left subtree
        if (key.compareTo(node.val) < 0)
            node.left = delete(root.left, key);

            // If the key to be deleted is
            // greater than the root's
            // key, then it lies in right subtree
        else if (key.compareTo(node.val) > 0)
            node.right = delete(node.right, key);

            // if key is same as root's key, then This is the node
            // to be deleted
        else {
            size--;
            // node has no child
            if (node.left==null && node.right == null) {
                return null;
            }
            else if (node.left == null) {
                return node.right;
            }
            else if (node.right == null) {
                return node.left;
            }

            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            node<T> temp = minValueNode(root.right);

            // Copy the inorder successor's content to this node
            node.val = temp.val;

            // Delete the inorder successor
            node.right = delete(node.right, temp.val);
        }
        return node;
    }

    public boolean delete(T value){
        int prevSize = size;
        root = delete(root, value);
        return prevSize != size;
    }

    //actual recursive search method
    private boolean search(node<T> node, T value){
        if(node == null)
            return false;

        if(node.val == value)
            return true;

        if(value.compareTo(node.val) > 0)
            return search(node.right, value);

        return search(node.left, value);
    }

    // public utility method
    //O(h) with h being the height of the tree
    public boolean search(T value){
        return search(root, value);
    }

    //O(n) with n being the number of elements
    private void preOrder(node<T> node){
        if(node == null)
            return;

        System.out.println(node.val);
        preOrder(node.left);
        preOrder(node.right);
    }

    //O(n) with n being the number of elements
    private void inOrder(node<T> node){
        if(node == null)
            return;

        inOrder(node.left);
        System.out.println(node.val);
        inOrder(node.right);
    }

    //O(n) with n being the number of elements
    private void postOrder(node<T> node){
        if(node == null)
            return;

        postOrder(node.left);
        postOrder(node.right);
        System.out.println(node.val);
    }

    public void preOrder(){
        preOrder(root);
    }

    public void inOrder(){
        inOrder(root);
    }

    public void postOrder(){
        postOrder(root);
    }

}
