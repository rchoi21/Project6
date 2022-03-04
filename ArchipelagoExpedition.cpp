#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "proj6.h"

// default constructor that sets dynamic array of islands at 10
ArchipelagoExpedition::ArchipelagoExpedition() {
	islands = new Island[11];
	for (int i = 1; i < 11; i++) {
		Island newI;
		MyList* newL = new MyList();
		newL->push_back(i);
		newI.setnList(newL);
		islands[i] = newI;
	}
	// # of islands (not storage)
	size = 10;
	files = new myLL();
}

// a function to process the input given based on a few commands
void ArchipelagoExpedition::processCommandLoop (FILE* inFile)
 {
  char buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0) {
			// delete inFile;
			doArrClear();
			delete islands;
			islands = nullptr;
			files->clear();
			files = nullptr;
			return;
		}
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) {
      doInsert();
		}
    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }

 // prints available commands to console/terminal
 void ArchipelagoExpedition::showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q\n"); // quit program
   printf ("  ?\n"); // basically showCommands
   printf ("  #\n"); // ignore line of input
   printf ("  t <int1> <int2>\n"); // find shortest path from island1 to island2
   printf ("  r <int>\n"); // remove this island & resize islands array
   printf ("  i <int1> <int2>\n"); // insert a link between island1 to island2
   printf ("  d <int1> <int2>\n"); // remove island1's link to island2
   printf ("  l\n"); // list everything
   printf ("  f <filename>\n"); // read given file
 }

 // BFS helper function that returns the path list
 MyList ArchipelagoExpedition::BFS(int x, int y) {
	// setting all prev for the islands to unvisited
	for (int i = 1; i < size + 1; i++) {
		islands[i].setPrev(-1);
	}
	MyList iq;
	iq.push_back(x);
	if (!bfs(y, iq)) {
		printf("You can NOT get from island %d to island %d\n", x, y);
		return iq;
	}
	printf("You can get from island %d to island %d\n", x, y);
	MyList pathList;
	int currentIsland = y;
	pathList.push_front(currentIsland);
	while (1) {
		currentIsland = islands[currentIsland].getPrev();
		pathList.push_front(currentIsland);
		if (currentIsland ==  x) {
			break;
		}
	}
	return pathList;
}

// BFS function that searches whether a path is possible
bool ArchipelagoExpedition::bfs(int b, MyList& IslandQueue) {
	int a;
	while (!IslandQueue.isEmpty()) {
		a = IslandQueue.getHead()->getValue();
		IslandQueue.remove(a);
		MyList* oneRide = islands[a].getnList();
		myNode* c = oneRide->getHead();
		// next node since head == current island
		c = c->getNext();
		while (c != nullptr) {
			// printf("currently c is: %d\n", c->getValue());
			if (islands[c->getValue()].getPrev() == -1) {
				islands[c->getValue()].setPrev(a);
				if (c->getValue() == b) {
					return true;
				}
				IslandQueue.push_back(c->getValue());
			}
			c = c->getNext();
		}
	}
	return false;
}

 // "travels" from one island to the next based on user input
 void ArchipelagoExpedition::doTravel()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
  
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");

  
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   printf ("Performing the Travel Command from %d to %d\n", val1, val2);
   MyList path = BFS(val1, val2);
	 if (path.getHead() == nullptr) {
		 // there exists no path
		 return;
	 }
	 printf("shortest path from %d to %d: ", val1, val2);
	 myNode* cur = path.getHead();
	 while (cur->getNext() != nullptr) {
		 printf("%d - ", cur->getValue());
		 cur = cur->getNext();
	 }
	 printf("%d\n", cur->getValue());
 }

 // member function to resize array of islands
 void ArchipelagoExpedition::doResize()
 {
   int val1 = 0;
	  // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
	 if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   printf ("Performing the Resize Command with %d\n", val1 );
	 // delete array contents
	 doArrClear();
	 delete islands;
	 // new array allocation
	 islands = new Island[val1 + 1];
	 for (int i = 1; i < val1 + 1; i++) {
		 Island newI;
		 MyList* newL = new MyList();
		 newL->push_back(i);
		 newI.setnList(newL);
		 islands[i] = newI;
	 }
	 size = val1;
 }

 // member function to insert a link between two islands
 void ArchipelagoExpedition::doInsert() {
   int val1 = 0;
   int val2 = 0;

	 // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
	 if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 if (val1 > size || val1 <= 0) {
		 printf("Invalid value for island\n");
		 return;
	 }
	 if (islands[val1].getnList() == nullptr) {
		 printf("Invalid value for island\n");
		 return;
	 }
   // get another integer value from the input
   next = strtok (NULL, " \n\t");
  
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 if (val2 > size || val2 <= 0) {
		 printf("Invalid value for island\n");
		 return;
	 }
	 if (val1 == val2) {
		 printf("Can not add ferry ride to self\n");
		 return;
	 }
	 // insert new link
	 printf("Performing the Insert Command for %d\n", val1);
	 if (islands[val1].getnList()->exist(val2)) {
		 printf("Ferry ride already added!\n");
		 return;
	 }
	 islands[val1].getnList()->push_back(val2);
 }

	// member function to delete a link between two islands
  void ArchipelagoExpedition::doDelete()
 {
	 int val1 = 0;
   int val2 = 0;

	 // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
	 if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");

   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
	 printf ("Performing the Delete Command for %d\n", val1);
	 islands[val1].getnList()->remove(val2);
 }
 
 // member function that prints everything
 void ArchipelagoExpedition::doList()
 {
   printf ("Displaying the adjacency list:\n");
	 for (int i = 1; i < size + 1; i++) {
		 printf("%d -->", i);
		 myNode* cur = islands[i].getnList()->getHead();
		 // skip the head which is a repeat of i
		 cur = cur->getNext();
		 if (cur != nullptr) {
			 printf("  ");
				while (cur->getNext() != nullptr) {
					printf("%d  ", cur->getValue());
					cur = cur->getNext();
				}
				printf("%d\n", cur->getValue());
	    }
		else {
			printf("\n");
		}
	 }
 }

 // member function to read the file
 void ArchipelagoExpedition::doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \r\n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   printf ("Performing the File command with file: %s\n", fname);
   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use
	 if (files != nullptr) {
		if (files->exist(fname)) {
			printf("File is already in use\n");
			return;
		}
	 }
   //  2. open the file using fopen creating a new instance of FILE*
	 FILE* infile = nullptr;
	 infile = fopen(fname, "r");
	 if (infile == nullptr) {
		 printf("File is already in use\n");
		 return;
	 }
	 files->push_back(fname);
	//  printf("THIS IS WHAT IS FILES HEAD RN: %s\n", files->getHead()->value);
	//  printf("THIS IS WHAT IS FILES TAIL RN: %s\n", files->getTail()->value);
   //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
	 processCommandLoop(infile);
   //  4. close the file when processCommandLoop() returns
	 fclose(infile);
	 files->pop_back();
 }

void ArchipelagoExpedition::doArrClear() {
	for (int i = 1; i < size + 1; i++) {
		if (islands[i].getnList() != nullptr) {
			islands[i].getnList()->clear();
		}
		if (islands[i].getnList() != nullptr) {
			delete islands[i].getnList();
		}
	}
	size = 0;
}