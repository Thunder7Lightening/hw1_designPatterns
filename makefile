all: hw6

hw6: mainScanner.o atom.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainScanner.o atom.o list.o -lgtest
else
	g++ -o hw6 mainScanner.o atom.o list.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utScanner.h scanner.h atom.h struct.h variable.h utParser.h parser.h node.h
	g++ -std=gnu++0x -c mainScanner.cpp
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp
list.o: list.cpp list.h
	g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw6
endif
