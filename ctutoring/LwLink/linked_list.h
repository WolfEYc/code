#ifndef MY_LIST_H
#define MY_LIST_H

#include <string>
#include <iostream>

/**
 * Simple node representation of singly-linked list data structure.
 * - public:
 *    - MyNode(std::string, int);
 *    - std::string name();
 *    - int score();
 *    - MyNode* next();
 *    - void setNext(MyNode*);
 * - private
 *    - std::string _name;
 *    - int _score;
 *    - MyNode* _nextPtr;
 */
class MyNode {
  public:
	/**
	 * Two-parameter constructor for name and score.
	 * @param	name	Name.
	 * @param	score	Score.
	 */
    MyNode(std::string name, int score);

    /**
	 * Access name value of node.
	 * @return	Name value of node.
	 */
    std::string name();

    /**
     * Access score value of node.
     * @return	Score value of node.
     */
    int score();

    /**
     * Access link to next node in linked list.
     * @return	Next node.
     */
    MyNode* next();

    /**
     * Modify link to next node in linked list.
     * @param	other	Next node.
     */
    void setNext(MyNode* other);
  private:
	/**
	 * Name value of node.
	 */
    std::string _name;

    /**
     * Score value of node.
     */
    int _score;

    /**
     * Link to next node in linked list.
     */
    MyNode* _nextPtr;
};


/**
 * Simple singly-linked list data structure representation.
 * - public:
 *    - MyList()
 *    - ~MyList()
 *    - size_t size()
 *    - bool empty()
 *    - MyNode* head()
 *    - void add(std::string, int)
 *    - bool remove(std::string)
 *    - void clear()
 *    - void insert(std::string, int, size_t)
 *    - void printList()
 * - private
 *    - size_t _size
 *    - MyNode* _headPtr
 *    - MyNode* _tailPtr
 */
class MyList {
  public:
    /**
     * Default constructor that initializes list size and node pointers.
     */
    MyList();

    /**
     * Destructor that deallocates node pointers
     */
    ~MyList();

    /**
     * Get size of linked list.
     * @return      Size of linked list.
     */
    size_t size();

    /**
     * Get whether linked list is empty or not.
     * @return      Whether linked list is empty or not.
     */
    bool empty();

    /**
     * Get head node of linked list.
     * @return      Head node of linked list.
     */
    MyNode* head() const;

    /**
     * Add node to end of linked list with node data.
     * @param   name    Name data of node.
     * @param   score   Score data of node.
     */
    void add(std::string name, int score);

    /**
     * Remove node from linked list with name data.
     * @param       Name data of node to remove.
     * @return      Whether node was removed from name data.
     */
    bool remove(std::string name);

    /**
     * Clears linked list of all nodes, if any.
     */
    void clear();

    /**
     * Insert node into index of linked list with node data.
     */
    bool insert(std::string name, int score, size_t index);

  private:
    /**
     * Size of linked list.
     */
    size_t _size;

    /**
     * Pointer to head node.
     */
    MyNode* _headPtr;

    /**
     * Pointer to tail node.
     */
    MyNode* _tailPtr;
};

/**
 * Display data of every node in linked list.
 */
std::ostream& operator<<(std::ostream& os, const MyList& myList);


#endif
