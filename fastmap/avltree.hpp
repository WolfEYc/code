#include <iostream>

int max(int a, int b){
    return (a > b)? a : b;
}

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
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

template <typename k, typename v>
class AVLTree{
private:
    Node<k,v>* root;
protected:
    int height(Node<k,v>* node)
    {
        if (node == nullptr) 
            return 0; 
        return node->height; 
    }

    int getBalance(Node<k,v> *node) 
    {
        if (node == nullptr) 
            return 0;
        return height(node->left) - height(node->right); 
    }

    Node<k,v>* minValueNode(Node<k,v>* node)
    {
        if(node == nullptr)
            return node;

        Node<k,v>* current = node;
    
        /* loop down to find the leftmost leaf */
        while (current->left != nullptr) 
            current = current->left; 
    
        return current; 
    }

    Node<k,v>* maxValueNode(Node<k,v>* node)
    {
        if(node == nullptr)
            return node;

        Node<k,v>* current = node;
    
        /* loop down to find the leftmost leaf */
        while (current->left != nullptr) 
            current = current->right; 
    
        return current; 
    }

    Node<k,v>* rightRotate(Node<k,v> *y) 
    { 
        Node<k,v> *x = y->left; 
        Node<k,v> *T2 = x->right; 
    
        // Perform rotation 
        x->right = y; 
        y->left = T2; 
    
        // Update heights 
        y->height = max(height(y->left), height(y->right)) + 1; 

        x->height = max(height(x->left), height(x->right)) + 1; 
    
        // Return new root 
        return x; 
    }
    
    Node<k,v>* leftRotate(Node<k,v> *x) 
    {
        Node<k,v> *y = x->right; 
        Node<k,v> *T2 = y->left; 
    
        // Perform rotation 
        y->left = x; 
        x->right = T2; 
    
        // Update heights 
        x->height = max(height(x->left), height(x->right)) + 1; 
        y->height = max(height(y->left), height(y->right)) + 1; 
    
        // Return new root 
        return y; 
    }
    
    Node<k,v>* insert(Node<k,v>* node, k key, v val)
    {
        /* 1. Perform the normal BST rotation */
        if (node == nullptr) 
            return new Node<k,v>(key, val);
    
        if (key < node->key) 
            node->left = insert(node->left, key, val); 
        else if (key > node->key) 
            node->right = insert(node->right, key, val); 
        else // Equal keys not allowed 
            return node; 
    
        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right)); 
    
        /* 3. Get the balance factor of this 
            ancestor node to check whether 
            this node became unbalanced */
        int balance = getBalance(node); 
    
        // If this node becomes unbalanced,
        // then there are 4 cases 
    
        // Left Left Case 
        if (balance > 1 && key < node->left->key) 
            return rightRotate(node); 
    
        // Right Right Case 
        if (balance < -1 && key > node->right->key) 
            return leftRotate(node); 
    
        // Left Right Case 
        if (balance > 1 && key > node->left->key) 
        { 
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        } 
    
        // Right Left Case 
        if (balance < -1 && key < node->right->key) 
        { 
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }
    
        /* return the (unchanged) node pointer */
        return node; 
    }

    Node<k,v>* deleteNode(Node<k,v>* root, k key)
    {
        
        // STEP 1: PERFORM STANDARD BST DELETE 
        if (root == nullptr) 
            return root; 
    
        // If the key to be deleted is smaller 
        // than the root's key, then it lies
        // in left subtree 
        if (key < root->key) 
            root->left = deleteNode(root->left, key); 
    
        // If the key to be deleted is greater 
        // than the root's key, then it lies 
        // in right subtree 
        else if(key > root->key) 
            root->right = deleteNode(root->right, key); 
    
        // if key is same as root's key, then 
        // This is the node to be deleted 
        else
        { 
            // node with only one child or no child 
            if( (root->left == NULL) || (root->right == NULL) ) 
            { 
                Node<k,v> *temp = root->left ? root->left : root->right; 
    
                // No child case 
                if (temp == NULL) 
                { 
                    temp = root; 
                    root = NULL; 
                }
                else // One child case 
                    *root = *temp; // Copy the contents of 
                            // the non-empty child 
                delete temp; 
            } 
            else
            { 
                // node with two children: Get the inorder 
                // successor (smallest in the right subtree) 
                Node<k,v>* temp = minValueNode(root->right); 
    
                // Copy the inorder successor's 
                // data to this node 
                root->key = temp->key; 
    
                // Delete the inorder successor 
                root->right = deleteNode(root->right, temp->key); 
            } 
        } 
    
        // If the tree had only one node
        // then return 
        if (root == NULL) 
            return root; 
    
        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
        root->height = 1 + max(height(root->left), height(root->right));
        // STEP 3: GET THE BALANCE FACTOR OF 
        // THIS NODE (to check whether this 
        // node became unbalanced) 
        int balance = getBalance(root); 
    
        // If this node becomes unbalanced, 
        // then there are 4 cases 
    
        // Left Left Case 
        if (balance > 1 && getBalance(root->left) >= 0) 
            return rightRotate(root);
    
        // Left Right Case 
        if (balance > 1 && getBalance(root->left) < 0) 
        { 
            root->left = leftRotate(root->left); 
            return rightRotate(root); 
        } 
    
        // Right Right Case 
        if (balance < -1 && getBalance(root->right) <= 0) 
            return leftRotate(root); 
    
        // Right Left Case 
        if (balance < -1 && getBalance(root->right) > 0) 
        { 
            root->right = rightRotate(root->right); 
            return leftRotate(root); 
        } 
    
        return root; 
    }

    Node<k,v>* find(Node<k,v>* node, k key){
        if(node == nullptr || node->key == key)
            return node;

        if(node->key < key)
            return find(node->right, key);

        return find(node->left, key);
    }

    void preOrder(Node<k,v>* root) 
    {
        
        if(root != nullptr) 
        { 
            std::cout << root->key << ": " << root->val << ", "; 
            preOrder(root->left); 
            preOrder(root->right); 
        }
        
    }
    
    void inOrder(Node<k,v>* root)
    {
        if(root != nullptr) 
        {
            inOrder(root->left);
            std::cout << root->key << ": " << root->val << ", "; 
            inOrder(root->right); 
        }
    }

public:
    AVLTree(){
        root = nullptr;
    }
    void insert(k key, v val){
        root = insert(root, key, val);
    }
    void remove(k key){
        root = deleteNode(root, key);
    }
    Node<k,v>* find(k key){
        return find(root,key);
    }
    Node<k,v>* minNode(){
        return minValueNode(root);
    }
    Node<k,v>* maxNode(){
        return maxValueNode(root);
    }
    void preOrder(){
        std::cout << "{ ";
        preOrder(root);
        std::cout << "}";
    }
    void inOrder(){
        std::cout << "{ ";
        inOrder(root);
        std::cout << "}";
    }
};

