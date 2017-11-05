all: hw5

hw5: mainScanner.o term.o utScanner.h utParser.h #scanner.h  parser.h
	g++ -o hw5 mainScanner.o term.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h atom.h struct.h variable.h utParser.h parser.h list.h term.h number.h
	g++ -std=c++11 -c mainScanner.cpp
term.o: term.cpp term.h variable.h
	g++ -std=c++11 -c term.cpp

clean:
	rm -f *.o hw5
stat:
	wc *.h *.cpp
