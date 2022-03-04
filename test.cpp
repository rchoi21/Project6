#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "proj6.h"

using namespace std;

void printMyLL(lnode* head) {
	lnode* cur = head;
	while (cur != nullptr) {
		printf("%s \n", cur->value);
    cur = cur->next;
	}
}

void printMyList(myNode* head) {
	myNode* cur = head;
	while (cur != nullptr) {
		printf("%d ", cur->getValue());
    cur = cur->getNext();
	}
	printf("\n");
}

MyList copyTest(MyList x) {
	// printMyList(x.getHead());
	MyList newx;
	newx = x;
	// printMyList(newx.getHead());
	return newx;
}

int main() {
	// Testing for MyList class
	MyList ml;
	MyList ml2;

	// Testing isEmpty & default constructor
	if (!ml.isEmpty()) {
		printf("wrong!");
		return 1;
	} // CHECKED :D
	
	// Testing push_back without duplicates
	ml.push_back(0);
	ml.push_back(1);
	ml.push_back(2);
	ml.push_back(3);
	ml.push_back(4);
	ml.push_back(5);
	ml.push_back(6);
	ml.push_back(7);
	ml.push_back(8);
	ml.push_back(9);

	// testing copy constructor
	ml2 = copyTest(ml);
	// printMyList(ml2.getHead());
	
	// printMyList(ml.getHead()); // CHECKED :D

	// Testing getSize
	// printf("size: %d\n", ml.getSize()); // CHECKED :D

	// Testing getNthVal
	for (int i = 0; i < 10; i++) {
		// printf("%d ", ml.getNthVal(i));
	}
	printf("\n"); // CHECKED :D

	// testing =copyconstructor
	ml2 = ml;
	// printf("this is ml:\n");
	// printMyList(ml.getHead());
	// printf("this is ml2:\n");
	// printMyList(ml2.getHead()); // CHECKED :D

	// Testing remove without duplicates
	ml.remove(9);
	// printMyList(ml.getHead());
	// expect 012345678
	ml.remove(8);
	// printMyList(ml.getHead());
	// expect 01234567
	ml.remove(0);
	// printMyList(ml.getHead());
	// expect 1234567
	ml.remove(1);
	// printMyList(ml.getHead());
	// expect 234567
	ml.remove(5);
	// printMyList(ml.getHead());
	// expect 23467
	ml.remove(4);
	// printMyList(ml.getHead());
	// expect 2367
	ml.remove(2);
	// printMyList(ml.getHead());
	// expect 367
	ml.remove(7);
	// printMyList(ml.getHead());
	// expect 36
	ml.remove(6);
	// printMyList(ml.getHead());
	// expect 3
	ml.remove(3);
	if (!ml.isEmpty()) {
		printf("wrong!");
		return 1;
	} // CHECKED :D

	// Testing push_back with duplicates
	ml.push_back(0);
	ml.push_back(0);
	ml.push_back(0);
	ml.push_back(3);
	ml.push_back(4);
	ml.push_back(6);
	ml.push_back(6);
	ml.push_back(9);
	ml.push_back(8);
	ml.push_back(0);
	
	// printMyList(ml.getHead()); // CHECKED :D

		// Testing remove with duplicates
	ml.remove(0);
	// printMyList(ml.getHead());
	// expect 003466980 
	ml.remove(8);
	// printMyList(ml.getHead());
	// expect 00346690
	ml.remove(0);
	// printMyList(ml.getHead());
	// expect 0346690
	ml.remove(6);
	// printMyList(ml.getHead());
	// expect 034690
	ml.remove(6);
	// printMyList(ml.getHead());
	// expect 03490
	ml.remove(4);
	// printMyList(ml.getHead());
	// expect 0390
	ml.remove(0);
	// printMyList(ml.getHead());
	// expect 390
	ml.remove(0);
	// printMyList(ml.getHead());
	// expect 39
	ml.remove(9);
	// printMyList(ml.getHead());
	// expect 3
	ml.remove(3);
	if (!ml.isEmpty()) {
		printf("wrong!");
		return 1;
	} // CHECKED :d

	// ULT TEST: CHECKING VALGRIND
	ml.push_back(0);
	ml.push_back(0);
	ml.push_back(0);
	ml.push_back(3);
	ml.push_back(4);
	ml.push_back(6);
	ml.push_back(6);
	ml.push_back(9);
	ml.push_back(8);
	ml.push_back(0); 
	// printMyList(ml.getHead()); // CHECKED :D
	// PROOF:
	// ==2015== 
	// ==2015== HEAP SUMMARY:
	// ==2015==     in use at exit: 0 bytes in 0 blocks
	// ==2015==   total heap usage: 32 allocs, 32 frees, 74,208 bytes allocated
	// ==2015== 
	// ==2015== All heap blocks were freed -- no leaks are possible
	// ==2015== 
	// ==2015== For counts of detected and suppressed errors, rerun with: -v
	// ==2015== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)	

	/* ************************************************************************ */
	// Testing for Island class
	Island is;
	// Island is:
	// nList = nullptr
	// visit = false
	// prev = -1
	if (is.getnList() != nullptr) {
		printf("wrong!");
		return 1;
	} // CHECKED :D

	is.setnList(&ml); // list: 0003466980
	is.visited();
	is.setPrev(20);
	// Island is:
	// nList = m1 : 0003466980
	// visit = true
	// prev = 20
	if (!is.isVisited()) {
		printf("wrong!");
		return 1;
	} // CHECKED :D

	// testing =operator
	Island is2;
	is2 = is;
	// printMyList(is2.getnList()->getHead());  // list: 0003466980
	if (!is2.isVisited()) {
		printf("wrong!");
		return 1;
	}
	if (is2.getPrev() != 20) {
		printf("wrong!");
		return 1;
	} // CHECKED :D

	// printMyList(is.getnList()->getHead()); // CHECKED :D
	// printf("prev: %d\n", is.getPrev()); // CHECKED :D
	// & still passes valgrind XD

	/* ************************************************************************ */
	// Testing for myLL class
	// Kinda upset I have to do this
	myLL l;
	// testing default constructor && isEmpty
	if (!l.isEmpty()) {
		printf("wrong!");
		return 1;
	}
	// testing push_back
	l.push_back("I'm");
	l.push_back("so");
	l.push_back("frikin");
	l.push_back("pissed!");
	// printMyLL(l.getHead());
	// testing getSize
	if (l.getSize() != 4) {
		printf("wrong");
		return 1;
	}
	// testing exist pt 1
	if (!l.exist("so")) {
		printf("wrong");
		return 1;
	}
	// testing exist pt 2
	if (!l.exist("pissed!")) {
		printf("wrong");
		return 1;
	}
	// testing exist pt 3
	if (!l.exist("I'm")) {
		printf("wrong");
		return 1;
	}
	// testing exist pt 4
	if (l.exist("wrong")) {
		printf("wrong");
		return 1;
	}
	// testing pop_front
	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();
	if (!l.isEmpty()) {
		printf("wrong!");
		return 1;
	}
	// testing exist pt 5
	if (l.exist("so")) {
		printf("wrong");
		return 1;
	}
	// printMyLL(l.getHead());

	l.push_back("I'm");
	l.push_back("so");
	l.push_back("frikin");
	l.push_back("pissed!");
	// printMyLL(l.getHead());
	// testing pop_back
	// printf("%s\n", l.peek_back());
	l.pop_back();
	// printf("%s\n", l.peek_back());
	l.pop_back();
	// printf("%s\n", l.peek_back());
	l.pop_back();
	// printf("%s\n", l.peek_back());
	l.pop_back();
	// printMyLL(l.getHead());
	if (!l.isEmpty()) {
		printf("wrong!");
		return 1;
	}

	// Testing destructor
	l.push_back("I'm");
	l.push_back("so");
	// printMyLL(l.getHead());

	l.clear();
	// printMyLL(l.getHead());

	l.push_back("I'm");
	l.push_back("so");
	l.push_back("frikin");
	l.push_back("pissed!");
	// printMyLL(l.getHead());

	// Passed all tests + valgrind :)

	return 0;
}