#ifndef NOTATIONCONVERTERDEQUE_H
#define NOTATIONCONVERTERDEQUE_H

#include <string>

class NotationConverterDeque
{
private:
	struct Node
	{
		std::string value;
		Node* prev;
		Node* next;

		Node(std::string v) : value(v), prev(nullptr), next(nullptr) {}
	};

	Node* front;
	Node* rear;
	int size;

public:
	NotationConverterDeque();		// constructor
	~NotationConverterDeque();		// destructor

	void insertFront(const std::string inStr);		// inserts new first element
	void insertBack(const std::string inStr);		// inserts new last element
	void removeFront();		// removes first element
	void removeBack();		// removes last element
	std::string getFront() const;	// returns first element
	std::string getBack() const;	// returns last element
	bool isEmpty() const;	// checks if deque is empty
	int getSize() const;	// returns size of deque
};

#endif /* NOTATIONCONVERTERDEQUE_H */