all: hw6

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp
list.o: list.cpp list.h
	g++ -std=gnu++0x -c list.cpp

hw6: mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h
ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainScanner.o atom.o list.o -lgtest
else
	g++ -o hw6 mainScanner.o atom.o list.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utScanner.h scanner.h atom.h struct.h variable.h utParser.h parser.h node.h
	g++ -std=gnu++0x -c mainScanner.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw6
endif

stat:
	wc *.h *.cpp
