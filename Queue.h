#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <class T>
class Queue
{
public:
	//TODO : Constructor Copy Destructor and Assignment Operator
	Queue() : m_size(0), m_head(nullptr), m_tail(nullptr) {}
	~Queue();
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);

	void pushBack(const T& value);
	T& front() const;
	void popFront();
	int size() const { return m_size; }

	class EmptyQueue {};

	class Iterator;
	Iterator begin();
	Iterator end();

	class ConstIterator;
	ConstIterator begin() const;
	ConstIterator end() const;

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

		const T& operator*() const { return m_data; }
	};

private:
	int m_size;
	Node* m_head;
	Node* m_tail;
};

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
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
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

/* Iterator Implementation */
template <class T>
class Queue<T>::Iterator
{
public:
	T& operator*() const;
	Iterator& operator++();
	bool operator!=(const Iterator& other) const { return m_node != other.m_node; }

	class InvalidOperation {};

	Node* m_node;
	Iterator(Node* node) : m_node(node) {}
};

template <class T>
T& Queue<T>::Iterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	return m_node->m_data;
}

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

/* Const Iterator Implementation */
template <class T>
class Queue<T>::ConstIterator
{
public:
	const T& operator*() const;
	ConstIterator& operator++();
	bool operator!=(const ConstIterator& other) const { return m_node != other.m_node; }

	class InvalidOperation {};

	const Node* m_node;
	ConstIterator(const Node* node) : m_node(node) {}
};

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	return m_node->m_data;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
	if (m_node == nullptr)
	{
		throw InvalidOperation();
	}
	m_node = m_node->m_next;
	return *this;
}

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



/* Queue Functions Implementation */
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

template <class T>
T& Queue<T>::front() const
{
	if (m_head == nullptr)
	{
		throw EmptyQueue();
	}
	return m_head->m_data;
}

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

template <class T, class Condition>
Queue<T> filter(const Queue<T>& queueToFilter, Condition c)
{
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

template <class T, class Function>
void transform(Queue<T>& queueToTransform, Function f)
{
	for (T& element : queueToTransform)
	{
		f(element);
	}
}


#endif // QUEUE_H
