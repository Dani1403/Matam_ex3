#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>

template <class T>
class Queue
{
public:
	/*
	* Constructor Destructor Copy Constructor Assignment Operator
	*/
	Queue() : m_size(0), m_head(nullptr), m_tail(nullptr) {}
	~Queue();
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	/*
	* Queue Functions
	*/
	void pushBack(const T& value);
	T& front();
	const T& front() const;
	void popFront();
	int size() const { return m_size; }

	/*
	* Node Class
	*/
	class Node
	{
	public:
		T m_data;
		Node* m_next;

		explicit Node(T data) : m_data(data), m_next(nullptr) {}
		Node& operator=(const Node& other) {
			if (this == &other)
			{
				return *this;
			}
			m_data = other.m_data;
			m_next = other.m_next;
			return *this;
		}
		Node(const Node& other) = default;
		~Node() = default;
		T& operator*() { return m_data; }
		const T& operator*() const { return m_data; }
	};

	class EmptyQueue {};

	/*
	* Iterator Class
	*/
	class Iterator;
	Iterator begin();
	Iterator end();

	/*
	* Const Iterator Class
	*/
	class ConstIterator;
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	int m_size;
	Node* m_head;
	Node* m_tail;
};

//Queue: Constructor Destructor Copy Constructor Assignment Operator Implementation ----------------------------------

template <class T>
Queue<T>::~Queue()
{
	while(this->size() > 0)
	{
		this->popFront();
	}
}

template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
	m_size = other.m_size;
	m_head = nullptr;
	m_tail = nullptr;
	for (const T& element : other)
	{
		this->pushBack(element);
	}
}

template <class T>
typename Queue<T>::Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this == &other)
	{
		return *this;
	}
	while (this->size() > 0)
	{
		this->popFront();
	}
	m_size = other.m_size;
	m_head = nullptr;
	m_tail = nullptr;
	for (const T& element : other)
	{
		this->pushBack(element);
	}
	return *this;
}

// Queue Functions Implementation ---------------------------------------------------------------------------------

/*
* Pushes a new element to the back of the queue
* @param value - the value of the new element
* @throws std::bad_alloc() if allocation fails
* @return void
*/
template <class T>
void Queue<T>::pushBack(const T& value)
{
	Node* newNode = new Node(value);
	if (!newNode)
	{
		throw std::bad_alloc();
	}
	if (m_head == nullptr)
	{
		m_head = newNode;
		m_tail = newNode;
	}
	else
	{
		m_tail->m_next = newNode;
		m_tail = newNode;
	}
	++m_size;
}

/*
* Returns the value of the first element in the queue
* @throws EmptyQueue() if the queue is empty
* @return T& - the value of the first element in the queue
*/
template <class T>
T& Queue<T>::front()
{
	if (m_head == nullptr)
	{
		throw EmptyQueue();
	}
	return m_head->m_data;
}

/*
* front Method for const objects
* Returns the value of the first element in the queue
* @throws EmptyQueue() if the queue is empty
* @return const T& - the value of the first element in the queue
*/
template <class T>
const T& Queue<T>::front() const
{
	if (m_head == nullptr)
	{
		throw EmptyQueue();
	}
	return m_head->m_data;
}

/*
* Removes the first element in the queue
* @throws EmptyQueue() if the queue is empty
* @return void
*/
template <class T>
void Queue<T>::popFront()
{
	if (m_head == nullptr)
	{
		throw EmptyQueue();
	}
	Node* temp = m_head;
	m_head = m_head->m_next;
	delete temp;
	--m_size;
	if (m_size == 0)
	{
		m_tail = nullptr;
	}
}

/* Create a new Queue with the elements of the given queue that satisfy the given condition
* @param queueToFilter - the queue to filter
* @param c - the condition
* @throws EmptyQueue() if the queue is empty
* @return Queue<T> - the new queue
*/
template <class T, class Condition>
Queue<T> filter(const Queue<T>& queueToFilter, Condition c)
{
	if (queueToFilter.size() == 0)
	{
		throw typename Queue<T>::EmptyQueue();
	}
	Queue<T> filteredQueue;
	for (const T& element : queueToFilter)
	{
		if (c(element))
		{
			filteredQueue.pushBack(element);
		}
	}
	return filteredQueue;
}

/*
* Transform all the elements in the given queue using the given function
* @param queueToTransform - the queue to transform
* @param f - the function
* @throws EmptyQueue() if the queue is empty
* @return void
*/
template <class T, class Function>
void transform(Queue<T>& queueToTransform, Function f)
{
	if (queueToTransform.size() == 0)
	{
		throw typename Queue<T>::EmptyQueue();
	}
	for (T& element : queueToTransform)
	{
		f(element);
	}
}

// Iterator Implementation ----------------------------------------------------------------------------------------

template <class T>
class Queue<T>::Iterator
{
public:
	T& operator*() const;
	Iterator& operator++();

	/*
	* Checks if the iterator is equal to another iterator
	* @param other - the other iterator
	* @return bool - true if the iterators are equal, false otherwise
	*/
	bool operator!=(const Iterator& other) const { return m_node != other.m_node; }
	class InvalidOperation {};
	
private: 
	friend class Queue;
	Node* m_node;
	Iterator(Node* node) : m_node(node) {}
};

/*
* Returns the value of the current element
* @throws InvalidOperation() if the iterator is invalid
* @return T& - the value of the current element
*/
template <class T>
T& Queue<T>::Iterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	return m_node->m_data;
}

/*
* Moves the iterator to the next element
* @throws InvalidOperation() if the iterator is invalid
* @return Iterator& - the iterator
*/
template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	m_node = m_node->m_next;
	return *this;
}

/* Begin and End Implementation */
template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
	return Iterator(m_head);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() 
{
	if (m_tail == nullptr)
	{
		return Iterator(nullptr);
	}
	return Iterator(m_tail->m_next);
}

// Const Iterator Implementation ----------------------------------------------------------------------------------

template <class T>
class Queue<T>::ConstIterator
{
public:
	const T& operator*() const;
	ConstIterator& operator++();

	/*
	* Checks if the iterator is equal to another iterator
	* @param other - the other iterator
	* @return bool - true if the iterators are equal, false otherwise
	*/
	bool operator!=(const ConstIterator& other) const { return m_node != other.m_node; }

	class InvalidOperation {};

private:
	const Queue<T>::Node* m_node;
	ConstIterator(const Node* node) : m_node(node) {}
	friend class Queue;
};

/*
* Returns the value of the current element
* @throws InvalidOperation() if the iterator is invalid
* @return const T& - the value of the current element
*/
template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	return m_node->m_data;
}

/*
* Moves the iterator to the next element
* @throws InvalidOperation() if the iterator is invalid
* @return ConstIterator& - the iterator
*/
template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	if (m_node->m_next == nullptr)
	{
		m_node = nullptr;
		return *this; 
	}
	m_node = m_node->m_next;
	return *this;
}

/* Begin and End Implementation */
template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
	return ConstIterator(m_head);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
	if (m_tail == nullptr)
	{
		return ConstIterator(nullptr);
	}
	return ConstIterator(m_tail->m_next);
}

#endif // QUEUE_H
