# all: hw7
#
# hw7: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
# 	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest -lpthread
#
# mainIterator.o: mainIterator.cpp utIterator.h
# 	g++ -std=c++11 -c mainIterator.cpp
#
# atom.o: atom.cpp atom.h variable.h
# 	g++ -std=c++11 -c atom.cpp
# list.o: list.cpp list.h
# 	g++ -std=c++11 -c list.cpp
# struct.o: struct.cpp struct.h
# 	g++ -std=c++11 -c struct.cpp
#
# clean:
# 	rm -f *.o hw7
# stat:
# 	wc *.h *.cpp

########################################
all: hw7

hw7: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest
else
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest -lpthread
endif

mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp
list.o: list.cpp list.h
	g++ -std=gnu++0x -c list.cpp
struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif

stat:
	wc *.h *.cpp
