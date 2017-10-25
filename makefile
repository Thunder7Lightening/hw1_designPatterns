all: hw4

hw4: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o -lgtest
else
	g++ -o hw4 main.o -lgtest -lpthread
endif

main.o: main.cpp atom.h constant.h number.h simpleObject.h struct.h term.h utAtom.h utNumber.h utStruct.h utVariable.h variable.h utList.h list.h
	g++ -std=gnu++0x -c main.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif

stat:
	wc *.h *.cpp
