hw2: mainTerm.o
	g++ -o hw2 mainTerm.o -lgtest -lpthread
mainTerm.o: mainTerm.cpp Atom.h Constant.h Number.h SimpleObject.h UtTerm.h Variable.h
	g++ -std=c++11 -c mainTerm.cpp

clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp
