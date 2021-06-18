
template <typename k, typename v>
struct Node{
    k key;
    v val;
    int height;
    Node* left;
    Node* right;
    Node(k key, v val){
        this->key = key;
        this->val = val;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

template <typename k, typename v>
class AVLtree{
private:
    Node<k,v>* root;
    void rotateRight(Node<k,v>* node);
    void rotateLeft(Node<k,v>* node);
    Node<k,v>* insert(Node<k,v>* node, k key, v val);
    Node<k,v>* remove(Node<k,v>* node, k key);
    int getBalance(Node<k,v>* node);
    int max(int a, int b);
    int height(Node<k,v>* node);
    Node<k,v>* minValueNode(Node<k,v>* node);
    void preOrder(Node<k,v>* node);
    void inOrder(Node<k,v>* node);
    v* find(Node<k,v>* node, k key);
public:
    void insert(k key, v val);
    void remove(k key);
    v* find(k key);
    void preOrder();
    void inOrder();
};
