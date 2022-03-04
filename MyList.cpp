#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "proj6.h"

// personal linked list

// default constructor for MyList
MyList::MyList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

// MyStack destructor to have clean valgrind report (hopefully)
MyList::~MyList() {
	clear();
}

// copy constructor for functions because i get garbage values ;( 
MyList::MyList(const MyList& other) {
	// I HAD TO SET THIS TO AVOID GARBAGE VAL?????
	head = nullptr;
	tail = nullptr;
	size = 0;
	if (other.head == nullptr) {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	else {
		// deep copy
		myNode* cur = other.head;
		while (cur != nullptr) {
			this->push_back(cur->getValue());
			cur = cur->getNext();
		}
		this->size = other.size;
	}
}

// a copy constructor (overloaded =) to perform deep copy of list
MyList& MyList::operator=(const MyList& other) {
	// check if same list return current list
	if (this == &other) {
		return *this;
	}
	// delete current contents if not empty
	if (!this->isEmpty()) {
		this->clear();
	}
	// perform deep copy
	myNode* cur = other.head;
	while (cur != nullptr) {
		this->push_back(cur->getValue());
		cur = cur->getNext();
	}
	// copy size
	this->size = other.size;
	return *this;
}

// to alter the head pointer for MyList
void MyList::setHead(myNode* nNode) {
	head = nNode;
}

// to alter the tail pointer for MyList
void MyList::setTail(myNode* nNode) {
	tail = nNode;
}

// returns current head pointer of MyList
myNode* MyList::getHead() {
	return head;
}

// returns current tail pointer of MyList
myNode* MyList::getTail() {
	return tail;
}

// returns current size
int MyList::getSize() {
	return size;
}

// returns T/F depending if MyList is currently empty
bool MyList::isEmpty() {
	if (head == nullptr) {
		return true;
	}
	return false;
}

// adds a node of given value to front of MyList
void MyList::push_front(int value) {
	// creating a new node
	myNode* nNode = new myNode();
	nNode->setValue(value);
	nNode->setNext(nullptr);
	// check if empty node
	if (isEmpty()) {
		// single node is now both head and tail
		head = nNode;
		tail = nNode;
		size++;
		return;
	}
	nNode->setNext(head);
	head = nNode;
	size++;
}

// adds a node of given value to the back of MyList
void MyList::push_back(int value) {
	// creating a new node
	myNode* nNode = new myNode();
	nNode->setValue(value);
	nNode->setNext(nullptr);
	// check if empty node
	if (isEmpty()) {
		// printf("I HATE YOUR FRIKIN GUTS\n");
		// single node is now both head and tail
		head = nNode;
		tail = nNode;
		size++;
		return;
	}
	// For some reason my tail is NULL...?
	// if (tail == nullptr) {
	// 	printf("this is the head while tail = NULL: %d\n", head->getValue());
	// 	printf("TAIL = NULL\n");
	// }
	// printf("this is nNode: %d\nThis is prevHead: %d\n", nNode->getValue(), head->getValue());
	tail->setNext(nNode); // WHY U SEG FAULTING (b/c its null for some reason)
	tail = nNode;
	size++;
}

// removes the first instance of the node of given value 
void MyList::remove(int value) {
	// check if there's nothing to remove
	if (isEmpty()) {
		return;
	}
	// check if it is the only node
	if (head == tail) {
		// remove the only node
		if (head->getValue() == value) {
			delete head;
			head = nullptr;
			tail = nullptr;
			size--;
		}
		// otherwise, the node to remove DNE
		return;
	}
	myNode* cur = head;
	myNode* prev = nullptr;
	while (cur != nullptr) {
		if (cur->getValue() == value) {
			// if node to delete is first node & cur == head
			if (prev == nullptr) {
				head = head->getNext();
				delete cur;
				size--;
				return;
			}
			// if node to delete is the last node
			else if (cur == tail) {
				tail = prev;
				prev->setNext(nullptr);
				delete cur;
				size--;
				return;
			}
			// node to delete is in middle of list
			else {
				prev->setNext(cur->getNext());
				delete cur;
				size--;
				return;
			}
		}
		prev = cur;
		cur = cur->getNext();
	}
}

// T/F based on whether the value already exists in list
bool MyList::exist(int val) {
	myNode* cur = head;
	while (cur != nullptr) {
		if (cur->getValue() == val) {
			return true;
		}
		cur = cur->getNext();
	}
	return false;
}

// returns the value of the given ith node
int MyList::getNthVal(int pos) {
	if (pos < 0 || pos >= size) {
		try {
			throw pos;
		}
		catch (int e) {
			printf("position is out of bounds\n");
		}
	}
	if (isEmpty()) {
		try {
			throw pos;
		}
		catch (int e) {
			printf("MyList is empty\n");
		}
	}
	// if only one node list
	if (head == tail) {
		return head->getValue();
	}
	if (pos == 0) {
		return head->getValue();
	}
	if (pos == (size - 1)) {
		return tail->getValue();
	}
	myNode* cur = head->getNext();
	int counter = 1;
	while (counter != pos) {
		cur = cur->getNext();
		counter++;
	}
	return cur->getValue();
}

void MyList::clear() {
	myNode* cur = head;
	myNode* temp = nullptr;
	while (cur != nullptr) {
		temp = cur;
		cur = cur->getNext();
		delete temp;
	}
	head = nullptr;
	tail = nullptr;
	size = 0;
}