all: hw8 #shell

hw8: mainHW8.o atom.o list.o struct.o scanner.h parser.h shell.h
	g++ -o hw8 mainHW8.o atom.o list.o struct.o -lgtest -lpthread
mainHW8.o: mainHW8.cpp scanner.h parser.h atom.h struct.h variable.h expression.h shell.h #exception.h
	g++ -std=c++11 -c mainHW8.cpp

# shell: mainShell.o
# 	g++ -o hw8 mainShell.o -lgtest -lpthread
# mainShell.o: mainShell.cpp shell.h
# 	g++ -std=c++11 -c mainShell.cpp



utScanner: mainScanner.o atom.o list.o struct.o scanner.h parser.h utScanner.h utParser.h
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp scanner.h parser.h atom.h struct.h variable.h utScanner.h utParser.h utExp.h
	g++ -std=c++11 -c mainScanner.cpp

utAtom: mainAtom.o list.o atom.o struct.o
	g++ -o utAtom mainAtom.o atom.o list.o struct.o  -lgtest -lpthread
mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
	g++ -std=c++11 -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp

utVariable: mainVariable.o atom.o struct.o
		g++ -o utVariable mainVariable.o atom.o struct.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=c++11 -c mainVariable.cpp
list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=c++11 -c struct.cpp

utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread
mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=c++11 -c mainIterator.cpp

clean:
	rm -f *.o hw8 shell
stat:
	wc *.h *.cpp
