#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "proj6.h"

// default constructor for Island
Island::Island() {
	nList = nullptr;
	visit = false;
	prev = -1;
}

// overloading =copyconstructor
Island& Island::operator=(const Island& other) {
	if (this == &other) {
		return *this;
	}
	if (this->nList != nullptr) {
		nList->clear();
	}
	// deep copy =operator overload done in MyList.cpp
	this->nList = other.nList;
	this->visit = other.visit;
	this->prev = other.prev;
	return *this;
}


// add a MyList for Island
void Island::setnList(MyList* list) {
	nList = list;
}

// set visited as true
void Island::visited() {
	visit = true;
}

// set prev as given int that indicates prev island
void Island::setPrev(int prev) {
	this->prev = prev;
}

// to access the adjacency list
MyList* Island::getnList() {
	return nList;
}

// returns whether the island has been visited or not
bool Island::isVisited() {
	return visit;
}

// returns which island we came from
int Island::getPrev() {
	return prev;
}