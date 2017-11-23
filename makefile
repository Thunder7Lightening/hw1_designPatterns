all: hw5

hw5: mainScanner.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainScanner.o -lgtest
else
	g++ -o hw5 mainScanner.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utScanner.h scanner.h atom.h struct.h variable.h utParser.h parser.h list.h term.h number.h
	g++ -std=gnu++0x -c mainScanner.cpp
# term.o: term.cpp term.h variable.h
# 	g++ -std=gnu++0x -c term.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif

stat:
	wc *.h *.cpp
