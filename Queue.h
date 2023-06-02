#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Node
{
public:
	T m_data;
	Node* m_next;

	explicit Node(T data) : m_data(data), m_next(nullptr) {}
	Node& operator=(const Node& other) = default;
	Node(const Node& other) = default;
	~Node() = default;

	const T& operator*() const { return m_data; }
};

template <class T>
class Queue
{
public:
	//TODO : Constructor Copy Destructor and Assignment Operator

	void pushBack(const T& value);
	T& front() const;
	void popFront();
	int size() const { return m_size; }

	class EmptyQueue {};

	class Iterator;
	Iterator begin();
	Iterator end();

	class ConstIterator {};
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	int m_size;
	Node* m_head;
	Node* m_tail;
};

/* Iterator Implementation */
template <class T>
class Queue<T>::Iterator
{
public:
	T& operator*() const;
	Iterator& operator++();
	bool operator!=(const Iterator& other) const;

	class InvalidOperation {};

private:
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
bool Queue<T>::Iterator::operator!=(const Iterator& other) const
{
	return m_node != other.m_node;
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
	bool operator!=(const ConstIterator& other) const;

	class InvalidOperation {};

private:
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
bool Queue<T>::ConstIterator::operator!=(const Queue<T>::ConstIterator& other) const
{
	return m_node != other.m_node;
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
		throw Empty();
	}
	return m_head->m_data;
}

template <class T>
void Queue<T>::popFront()
{
	if (m_head == nullptr)
	{
		throw Empty();
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

//TODO : Faire avec Itérateur
template <class T, class Condition>
Queue<T> filter(const Queue<T>& queueToFilter, Condition c)
{
	Queue<T> filteredQueue;
	Node* temp = queueToFilter.m_head;
	while (temp != nullptr)
	{
		if (c(temp->m_data))
		{
			filteredQueue.pushBack(temp->m_data);
		}
		temp = temp->m_next;
	}
	return filteredQueue;
}


#endif // QUEUE_H
