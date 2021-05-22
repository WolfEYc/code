#ifndef LIST_HPP
#define LIST_HPP

#include <string>

/**
 * Representation of a node in a linked list. Because this class is meant
 * to only contain data members and not support any complicated operations,
 * I think that making all of the members public is justified.
 */
struct Node
{
public:
    int data;
    Node* next;
};

/**
 * Representation of an entire linked list.
 */
class List
{
public:
    /**
     * Constructor. Creates an empty list.
     */
    List();

    /**
     * Copy constructor. Creates an independent clone of @other.
     */

    List(const List& other);

    /**
     * Destructor.
     */
    ~List();

    /**
     * Copy assignment operator.
     */
    List& operator=(const List& other);

    /**
     * Returns the number of nodes in the list.
     *
     * MUST run in constant time.
     */
    unsigned length() const;

    /**
     * Adds a new node with the given data to the front of the list.
     *
     * MUST run in constant time.
     */
    void pushFront(int data);

    /**
     * Adds a new node with the given data to the back of the list.
     *
     * MUST run in constant time.
     */
    void pushBack(int data);

    /**
     * Adds a new node with the given data to the back of the list.
     *
     * MUST run in constant time.
     */
    void operator+=(int data);

    /**
     * Accesses the element that is @index nodes past the first node in
     * the list.
     *
     * Throws std::out_of_range exception (the message doesn't matter) if
     * given an out-of-range index.
     */
    int& operator[](unsigned index);
    const int& operator[] (unsigned index) const;

    /**
     * Returns true if a node that contains the given data exists in the list.
     * Returns false otherwise.
     */
    bool contains(int data) const;

    /**
     * Removes the FIRST occurrence (starting from the front of the list)
     * of a node that contains the given data.
     * Returns true if a node was removed; returns false otherwise.
     */
    bool remove(int data);

    /**
     * Removes the FIRST occurrence (starting from the front of the list)
     * of a node that contains the given data.
     */
    void operator-=(int data);
    
    void clear();
    
    /**
     * Prints the contents of this list.
     */
    friend std::ostream& operator<<(std::ostream& os, const List& list);

private:
    // TODO: Any helper methods that you add should be declared or defined
    // in here.
    
    void remove_helper(int data);
    Node* head;
    unsigned len;     
    // TODO: Insert any other member variables here.

};

#endif // LIST_HPP
