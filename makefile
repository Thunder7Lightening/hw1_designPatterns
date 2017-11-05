all: hw5

hw5: mainScanner.o term.o utScanner.h utParser.h
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainScanner.o term.o -lgtest
else
	g++ -o hw5 mainScanner.o term.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utScanner.h scanner.h atom.h struct.h variable.h utParser.h parser.h list.h term.h number.h
	g++ -std=c++11 -c mainScanner.cpp
term.o: term.cpp term.h variable.h
	g++ -std=c++11 -c term.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
stat:
	wc *.h *.cpp
