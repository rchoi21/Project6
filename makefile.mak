Project6: MyList.o Island.o ArchipelagoExpedition.o Proj6main.o
	g++ -g -o Project6 MyList.o Island.o ArchipelagoExpedition.o Proj6main.o

MyList.o: MyList.cpp proj6.h
	g++ -c MyList.cpp

Island.o: Island.cpp proj6.h
	g++ -c Island.cpp

ArchipelagoExpedition.o: ArchipelagoExpedition.cpp proj6.h
	g++ -c ArchipelagoExpedition.cpp

Proj6main.o: Proj6main.cpp proj6.h
	g++ -c Proj6main.cpp

run:
	./Project6

valgrind:
	valgrind ./Project6

clean:
	rm MyList.o Island.o Proj6main.o Project6

build_test:  MyList.o Island.o test.o
	g++ -o build_test MyList.o Island.o test.o

test.o: test.cpp proj6.h
	g++ -c test.cpp

run_test:
	./build_test

test_valgrind:
	valgrind ./build_test