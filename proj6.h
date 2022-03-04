#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

// a class for specifically a filereading linked list node
class lnode {
	public:
		const char* value;
		lnode* next;
		lnode* prev;
		lnode() {
			value = "";
			next = nullptr;
			prev = nullptr;
		}
		lnode(const char* val) {
			value = val;
			next = nullptr;
			prev = nullptr;
		}
};

// a filereading linked list
class myLL {
	private:
		lnode* head;
		lnode* tail;
		int size;
	public:
		// default constructor
		myLL() {
			head = nullptr;
			tail = nullptr;
			size = 0;
		}
		// destructor
		~myLL() {
			clear();
		}

		// getters
		lnode* getHead() {
			return head;
		}
		lnode* getTail() {
			return tail;
		}
		int getSize() {
			return size;
		}

		// delete list
		void clear() {
			while (!isEmpty()) {
				pop_front();
			}
			head = nullptr;
			tail = nullptr;
			size = 0;
		} 

		// member function checks if list is empty
		bool isEmpty() {
			if (head == nullptr) {
				// printf("am i here?\n");
				return true;
			}
			// printf("am i here?\n");
			return false;
		}

		// pushes a new node at the end
		void push_back(const char* val) {
			// initialize new node
			lnode* newNode = new lnode();
			newNode->value = val;
			newNode->next = nullptr;
			newNode->prev = nullptr;
			// if adding to empty list
			if (isEmpty()) {
				head = newNode;
				tail = newNode;
				size++;
			}
			// if only one node currently in list
			else if (head == tail) {
				head->next = newNode;
				newNode->prev = head;
				tail = newNode;
				size++;
			}
			// otherwise just have current tail->next = new node and new tail = new node
			else {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
				size++;
			}
		}
		// see what value is at head
		const char* peek_front() {
			if (isEmpty()) {
				return "";
			}
			return head->value;
		}
		// see what value is at tail
		const char* peek_back() {
			if (isEmpty()) {
				return "";
			}
			return tail->value;
		}
		// remove current head node
		void pop_front() {
			if (isEmpty()) {
				return;
			}
			// if there's only one node
			if (head == tail) {
				tail = nullptr;
				delete head;
				head = nullptr;
				size--;
				return;
			}
			lnode* temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
			size--;
		}
		// remove current tail node
		void pop_back() {
			if (isEmpty()) {
				return;
			}
			// if there's only one node
			if (head == tail) {
				tail = nullptr;
				delete head;
				head = nullptr;
				size--;
				return;
			}
			lnode* temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
			size--;
		}
		// returns T/F depending on if given value already exists in list
		bool exist(const char* val) {
			lnode* cur = head;
			while (cur != nullptr) {
				if (strcmp(val, cur->value) == 0) {
					return true;
				}
				cur = cur->next;
			}
			return false;
		}
};

// A class made for the linked list for islands
class myNode {
	private:
		int value;
		myNode* next;

	public:
		// default constructor
		myNode() {
			value = 0;
			next = nullptr;
		}
		// parameterized constructor
		myNode(int value) {
			this->value = value;
			next = nullptr;
		}
		// setters
		void setValue(int value) {
			this->value = value;
		}
		void setNext(myNode* node) {
			next = node;
		}
		// getters
		int getValue() {
			return value;
		}
		myNode* getNext() {
			return next;
		}
};

// A custom linked list class
class MyList {
	private: 
		myNode* head;
		myNode* tail;
		int size;
	
	public:
		MyList();
		~MyList();
		MyList(const MyList& other);
		MyList& operator=(const MyList& other);
		void setHead(myNode* nNode);
		void setTail(myNode* nNode);
		myNode* getHead();
		myNode* getTail();
		int getSize();
		bool isEmpty();
		void push_front(int value);
		void push_back(int value);
		void remove(int value);
		bool exist(int val);
		int getNthVal(int pos);
		void clear();
};

// A Class for verticies called Islands
class Island {
	private:
		MyList* nList; // instance of the linked list for the island’s adjacency list
		bool visit; // a value to determine if an island has been visited or not
		int prev; // what island was visited before right before 
	
	public:
		Island();
		Island& operator=(const Island& other);
		void setnList(MyList* list);
		void visited();
		void setPrev(int prev);
		MyList* getnList();
		bool isVisited();
		int getPrev();
};
// BFS helper functions
// list breadthFirstSearch (int x, int y)
// {
//  mark all islands as unvisited (set all previousLocation to -1);
//  set the list IslandQueue to be empty
//  add x to the end of the IslandQueue
//  if ( bfs ( y, IslandQueue ) = = FALSE )
//  print (“You can NOT get from island “ + x + “ to island “ + y + “ in one or more ferry
// rides”);
//  return an empty list
//  else
//  print (“You can get from island “ + x + “ to island “ + y + “ in one or more ferry rides”);
//  pathList is set to an empty list
//  set currentIsland to y
//  add currentIsland to front of pathList
//  do
//  currentIsland = previousLocation for island nodeValue
//  add currentIsland to front of pathList
//  while ( currentIsland != x )
//  return pathList
// }
// given ArchipelagoExpedition Class
class ArchipelagoExpedition
{
 private:
   // Create the Data Members for the Archipelago Network here
	 Island* islands;
	 int size;
	 myLL* files;
  
 public:
	 // Use a constructor to initialize the Data Members for your expedition
   ArchipelagoExpedition();
   // The main loop for reading in input
 	 void processCommandLoop (FILE* inFile);
 	 void showCommands();
   void doTravel();
	 MyList BFS(int x, int y);
	 bool bfs(int b, MyList& IslandQueue);
   void doResize();
   void doInsert();
   void doDelete();
   void doList();
   void doFile();
	 void doArrClear();
};
