#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <new>
#include <iostream>

/*
 *  Queue:
 *  This is a template class that can be used for managing decks of cards, the turns of players, and more.
*/
template <class T>
class Queue {
    /*
    * Queue::Node
    * This class is used to create the separate nodes in the linked list
    */
    class Node {
    public:
        T m_data;
        Node* m_next;
        //Constructor
        Node();
        /*
         * Explicitly use the default methods for the copy constructor, the assignment operator and the destructor
        */
        Node(const Node&) = default;
        Node& operator=(const Node& other) = default;
        ~Node() = default;
        //Destroy node(s) in the linked list
        void destroyNode(Node* node);
    };
public:
    //Constructor
    Queue();
    //Destructor
    ~Queue();
    //Copy constructor
    Queue(const Queue& original);
    //Assignment operator
    Queue& operator=(const Queue& original);

    //-------------------------------------Method Functions----------------------------------------

    /*
    * Add new member to the end of the queue
    *
    * @param data - data that needs to be added to the queue
    * @return - void
    */
    void pushBack(const T& data);

    /*
    * Return the data of the first member of the queue
    *
    * @return - a reference to the data of the first member of the queue
    */
    T& front();

    /*
    * Return the data of the first member of a const instance of a queue
    *
    * @return - a const reference to the data of the first member of a const instance of a queue
    */
    const T& front() const;

    /*
    * Remove the first node of the queue
    *
    * @return - void
    */
    void popFront();

    /*
    * Calculate and return the size of a queue
    *
    * @return - the size of the queue
    */
    int size();

    /*
    * Calculate and return the size of a const instance of a queue
    *
    * @return - the size of the const queue
    */
    int size() const;

    /*
     * Queue::Iterator
     * This class is used in calculations and functions throughout the Queue class.
    */
    class Iterator;
    //Iterator methods for returning the first and last nodes in the queue
    Iterator begin();
    Iterator end();

    /*
    * Queue::ConstIterator
    * This class is used in calculations and functions throughout the Queue class for const queue variables.
    */
    class ConstIterator;
    //Iterator methods for returning the first and last nodes in the queue
    ConstIterator begin() const;
    ConstIterator end() const;

    /*
     * Queue::EmptyQueue
     * This class is used for the errors thrown as a result of actions performed on an empty queue.
    */
    class EmptyQueue {};
private:
    Node* m_node;
};


//-----------------------------Queue: Method Functions & Constructors------------------------------

//Constructor
template <class T>
Queue<T>::Queue()
{
    //Creating beginning empty node
    try {
        m_node = new Node;
    }
    catch (const std::bad_alloc& e) {
        delete m_node;
        throw std::bad_alloc();
    }
    //Creating end empty node
    Node* nodeNew = new Node;
    try {
        if (!nodeNew) {
            throw std::bad_alloc();
        }
    }
    catch (const std::bad_alloc& e) {
        delete nodeNew;
        throw std::bad_alloc();
    }
    //Connect between the two nodes
    m_node->m_next = nodeNew;
}

//Destructor
template <class T>
Queue<T>::~Queue()
{
    m_node->destroyNode(m_node);
}

//Copy Constructor
template <class T>
Queue<T>::Queue(const Queue& original)
{
    //Creating beginning empty node
    try {
        m_node = new Node;
    }
    catch (const std::bad_alloc& e) {
        delete m_node;
        throw std::bad_alloc();
    }
    //Creating end empty node
    Node* nodeNew = new Node;
    try {
        if (!nodeNew) {
            throw std::bad_alloc();
        }
    }
    catch (const std::bad_alloc& e) {
        delete nodeNew;
        throw std::bad_alloc();
    }
    //Connect between the two nodes
    m_node->m_next = nodeNew;
    //Copy the given queue to the current new queue
    try {
        for (const T& elem : original) {
            this->Queue<T>::pushBack(elem);
        }
    }
    catch (...) {
        m_node->Node::destroyNode(m_node);
        throw;
    }
}


//Assignment Operator
template <class T>
typename Queue<T>::Queue& Queue<T>::operator=(const Queue& original)
{
    if (this == &original) {
        return *this;
    }
    //Copy the given queue to a local queue variable
    Queue queueNew(original);
    //Swap between the local queue variable pointer to the current queue pointer
    Node* tmp = queueNew.m_node;
    queueNew.m_node = m_node;
    m_node = tmp;
    return *this;
}

// Add new member to the end of the queue
template <class T>
void Queue<T>::pushBack(const T& data)
{
    //Copy data to the empty node at the end of the queue
    Queue<T>::Iterator endIt = this->end();
    endIt.m_currentNode->m_data = data;
    //Create new empty node
    Node* nodeNew = new Node;
    try {
        if (!nodeNew) {
            throw std::bad_alloc();
        }
    }
    catch (const std::bad_alloc& e) {
        delete nodeNew;
        throw std::bad_alloc();
    }
    //Add empty node to the end of the queue
    endIt.m_currentNode->m_next = nodeNew;
}

// Return the data of the first member of the queue
template <class T>
T& Queue<T>::front()
{
    if (m_node->m_next->m_next == nullptr) {
        throw EmptyQueue();
    }
    return m_node->m_next->m_data;
}

// Return the data of the first member of a const instance of a queue
template <class T>
const T& Queue<T>::front() const
{
    if (m_node->m_next->m_next == nullptr) {
        throw EmptyQueue();
    }
    return m_node->m_next->m_data;
}

// Remove the first node of the queue
template <class T>
void  Queue<T>::popFront()
{
    if (m_node->m_next->m_next == nullptr) {
        throw EmptyQueue();
    }
    //Detach the first non-empty node in the list and delete it's allocated memory
    else {
        Node* toPop = m_node->m_next;
        m_node->m_next = m_node->m_next->m_next;
        toPop->m_next = nullptr;
        toPop->Node::destroyNode(toPop);
    }
}

// Calculate and return the size of a queue
template <class T>
int Queue<T>::size()
{
    Iterator current = this->begin();
    Iterator listEnd = this->end();
    int counter = 0;
    while (current != listEnd) {
        counter++;
        ++current;
    }
    return counter;
}

// Calculate and return the size of a const instance of a queue
template <class T>
int Queue<T>::size() const
{
    ConstIterator current = this->begin();
    ConstIterator listEnd = this->end();
    int counter = 0;
    while (current != listEnd) {
        counter++;
        ++current;
    }
    return counter;
}

//------------------------------------------Iterator Class-----------------------------------------

template <class T>
class Queue<T>::Iterator {
public:
    /*
     * Explicitly use the default methods for the copy constructor, the assignment operator and the destructor
    */
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;

    //The minimal operators needed for defining an Iterator:

    /*
    * "*" operator on the node the Iterator "points" to
    *
    * @return - a reference to the data of the requested node
    */
    T& operator*() const;

    /*
    * "++" prefix operator on the Iterator
    *
    * @return - a reference to the Iterator that now points to the next node in the queue
    */
    Iterator& operator++();

    /*
    * "!=" operator between two Iterators
    *
    * @return - true if the two Iterators point to different nodes, otherwise false
    */
    bool operator!=(const Iterator& i) const;

    /*
    * Queue::Iterator::InvalidOperation
    * This class is used for the errors thrown as a result of invalid operations
    */
    class InvalidOperation {};
private:
    Queue<T>::Node* m_currentNode;
    //Private Constructor
    Iterator(Queue<T>::Node* node);
    friend class Queue;
};

//Constructor
template <class T>
Queue<T>::Iterator::Iterator(Queue<T>::Node* node) :
    m_currentNode(node)
{}

// "*" operator on the node the Iterator "points" to
template <class T>
T& Queue<T>::Iterator::operator*() const
{
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    return m_currentNode->m_data;
}

// "++" prefix operator on the Iterator
template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    m_currentNode = m_currentNode->m_next;
    return *this;
}

// "!=" operator between two Iterators
template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    return (m_currentNode != i.m_currentNode);
}

//-------------------------------------ConstIterator Class-----------------------------------------

template <class T>
class Queue<T>::ConstIterator {
public:
    /*
     * Explicitly use the default methods for the copy constructor, the assignment operator and the destructor
    */
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
    ~ConstIterator() = default;

    //The minimal operators needed for defining an iterator:
    /*
    * "*" operator on the const node the ConstIterator "points" to
    *
    * @return - a const reference to the data of the requested const node
    */
    const T& operator*() const;
    /*
    * "++" prefix operator on the ConstIterator
    *
    * @return - a reference to the ConstIterator that now points to the next const node in the const queue
    */
    ConstIterator& operator++();
    /*
    * "!=" operator between two ConstIterators
    *
    * @return - true if the two ConstIterators point to different const nodes, otherwise false
    */
    bool operator!=(const ConstIterator& i) const;

    /*
    * Queue::ConstIterator::InvalidOperation
    * This class is used for the errors thrown as a result of invalid operations
    */
    class InvalidOperation {};
private:
    const Queue<T>::Node* m_currentNode;
    //Private Constructor
    ConstIterator(const Node* node);
    friend class Queue;
};

//Constructor
template <class T>
Queue<T>::ConstIterator::ConstIterator(const Node* node) :
    m_currentNode(node)
{}

// "*" operator on the const node the ConstIterator "points" to
template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    return m_currentNode->m_data;
}

// "++" prefix operator on the ConstIterator
template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    m_currentNode = m_currentNode->m_next;
    return *this;
}

// "!=" operator between two ConstIterators
template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& i) const
{
    return (m_currentNode != i.m_currentNode);
}


//Returns an iterator to the first node in the queue
template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    Iterator current = Iterator(m_node);
    ++current;
    return current;
}

//Returns an iterator to the node after last node in the queue
template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    if (m_node->m_next->m_next == nullptr) {
        return Iterator(m_node->m_next);
    }
    Iterator current = this->begin();
    while (current.m_currentNode->m_next != nullptr) {
        ++current;
    }
    return current;
}

//Returns an iterator to the first node in the const queue
template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    ConstIterator current = ConstIterator(m_node);
    ++current;
    return ConstIterator(current);
}

//Returns an iterator to the node after last node in the const queue
template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    if (m_node->m_next->m_next == nullptr) {
        return ConstIterator(m_node->m_next);
    }
    ConstIterator current = this->begin();
    while (current.m_currentNode->m_next != nullptr) {
        ++current;
    }
    return current;
}

/*
 * Copy given queue's elements to new queue if they fit the given condition
 *
 * @param givenQueue - the queue that needs to be copied
 * @param c - the function that will be used on the given queue's objects
 *
 * @return - a copy of the newly created queue
*/
template <class T, typename Condition>
Queue<T> filter(const Queue<T>& givenQueue, const Condition c)
{
    if (!(givenQueue.begin() != givenQueue.end())) {
        throw typename Queue<T>::EmptyQueue();
    }
    Queue<T> newQueue;
    for (const T& elem : givenQueue) {
        if (c(elem)) {
            newQueue.pushBack(elem);
        }
    }
    return newQueue;
}

/*
 * Transform all the elements of the given queue according to the condition provided
 *
 * @param givenQueue - the queue that needs to be modified
 * @param c - the function that will be used on the given queue's objects
 *
 * @return - a reference to the modified queue
*/
template <class T, typename Condition>
void transform(Queue<T>& givenQueue, const Condition c)
{
    if (!(givenQueue.begin() != givenQueue.end())) {
        throw typename Queue<T>::EmptyQueue();
    }
    for (T& elem : givenQueue) {
        c(elem);
    }
}

//-------------------------------------------Node Class--------------------------------------------

//Create a new node:
template <class T>
Queue<T>::Node::Node()
{
    m_next = nullptr;
}

//Destroy Nodes
template <class T>
void Queue<T>::Node::destroyNode(Node* node)
{
    Node* current = node;
    while (node != nullptr) {
        current = node->m_next;
        delete node;
        node = current;
    }
}


#endif //EX3_QUEUE_H