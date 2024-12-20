#include "NotationConverterDeque.hpp"
#include <string>
#include <stdexcept>

// constructor for new deque
NotationConverterDeque::NotationConverterDeque() : front(nullptr), rear(nullptr), size(0) {}

// destructor
NotationConverterDeque::~NotationConverterDeque()
{
	while (!isEmpty())
	{
		removeFront();
	}
}

// adds new node to front of deque
void NotationConverterDeque::insertFront(const std::string inStr)
{
	Node* newNode = new Node(inStr);

	if (isEmpty())		// in empty deque both front and rear point to only node
	{
		front = rear = newNode;
	}
	else    // if other nodes in deque, new node set as new front node of deque
	{
		newNode->next = front;
		front->prev = newNode;
		front = newNode;
	}
	size++;
}

// adds new node to back of deque
void NotationConverterDeque::insertBack(const std::string inStr)
{
	Node* newNode = new Node(inStr);

	if (isEmpty())		// in empty deque both front and rear point to only node
	{
		front = rear = newNode;
	}
	else    // if other nodes in deque, new node set as new rear node of deque
	{
		newNode->prev = rear;
		rear->next = newNode;
		rear = newNode;
	}
	size++;
}

// deletes first node from deque
void NotationConverterDeque::removeFront()
{
	if (isEmpty())		// cannot remove front if no nodes in deque
	{
		throw std::logic_error("Error: Deque is empty.");
	}

	Node* temp = front;

	if (front == rear)		// if only one node in deque, both front and rear point to null
	{
		front = rear = nullptr;
	}
	else    // if more than one node in deque, second set as new front and first deleted
	{
		front = front->next;
		front->prev = nullptr;
	}

	delete temp;
	size--;
}

// deletes last node from deque
void NotationConverterDeque::removeBack()
{
	if (isEmpty())		// cannot remove rear if no nodes in deque
	{
		throw std::logic_error("Error: Deque is empty.");
	}

	Node* temp = rear;

	if (front == rear)		// if only one node in deque, both front and rear point to null
	{
		front = rear = nullptr;
	}
	else    // if more than one node in deque, second to last set as new rear and last deleted
	{
		rear = rear->prev;
		rear->next = nullptr;
	}

	delete temp;
	size--;
}

// returns value of first node in deque
std::string NotationConverterDeque::getFront() const
{
	if (isEmpty())		// cannot return value if no nodes in deque
	{
		throw std::logic_error("Error: Deque is empty.");
	}

	return front->value;
}

// returns value of last node in deque
std::string NotationConverterDeque::getBack() const
{
	if (isEmpty())		// cannot return value if no nodes in deque
	{
		throw std::logic_error("Error: Deque is empty.");
	}

	return rear->value;
}

// checks if deque has zero nodes
bool NotationConverterDeque::isEmpty() const
{
	return size == 0;
}

// returns amount of nodes in deque
int NotationConverterDeque::getSize() const
{
	return size;
}