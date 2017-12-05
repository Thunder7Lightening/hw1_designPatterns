#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "atom.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "iterator.h"

// iterate s(1, t(X,2), Y)
TEST(iterator, first) {
	// create s(1, t(X,2), Y)
	Variable X("X");
	Number two(2);
	Number one(1);

	vector<Term *> args;
	args.push_back(&X);
	args.push_back(&two);
	Struct t(Atom("t"), args);

	Variable Y("Y");
	args.clear();
	args.push_back(&one);
	args.push_back(&t);
	args.push_back(&Y);
	Struct s(Atom("s"), args);

	// iterate
	Iterator<Term*> *itStruct = s.createIterator();
	itStruct->first();
	ASSERT_EQ("1", itStruct->currentItem()->symbol());
	ASSERT_FALSE(itStruct->isDone());
	itStruct->next();
	ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
	ASSERT_FALSE(itStruct->isDone());
	itStruct->next();
	ASSERT_EQ("Y", itStruct->currentItem()->symbol());
	itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}


// iterate t(X,2) in s(1, t(X,2), Y)
TEST(iterator, nested_iterator) {
	// create s(1, t(X,2), Y)
	Variable X("X");
	Number two(2);
	Number one(1);

	vector<Term *> args;
	args.push_back(&X);
	args.push_back(&two);
	Struct t(Atom("t"), args);

	Variable Y("Y");
	args.clear();
	args.push_back(&one);
	args.push_back(&t);
	args.push_back(&Y);
	Struct s(Atom("s"), args);

	// find t(X,2)
	Iterator<Term*> *it = s.createIterator();
	it->first();
	it->next();

	// iterate
	it = it->currentItem()->createIterator();
	it->first();
	ASSERT_EQ("X", it->currentItem()->symbol());
	ASSERT_FALSE(it->isDone());
	it->next();
	ASSERT_EQ("2", it->currentItem()->symbol());
	ASSERT_FALSE(it->isDone());
	it->next();
	ASSERT_TRUE(it->isDone());
}

// iterate [1, t(X,2), Y]
TEST(iterator, firstList) {
	// create [1, t(X,2), Y]
	Number one(1);
	Variable X("X");
	Variable Y("Y");
	Number two(2);

	vector<Term *> args;
	args.push_back(&X);
	args.push_back(&two);
	Struct t(Atom("t"), args);

	args.clear();
	args.push_back(&one);
	args.push_back(&t);
	args.push_back(&Y);
	List l(args);

	// iterate
	Iterator<Term*> *it = l.createIterator();
	it->first();
	ASSERT_EQ("1", it->currentItem()->symbol());
	ASSERT_FALSE(it->isDone());
	it->next();
	ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
	ASSERT_FALSE(it->isDone());
	it->next();
	ASSERT_EQ("Y", it->currentItem()->symbol());
	it->next();
	ASSERT_TRUE(it->isDone());
}

// iterate 1
TEST(iterator, NullIterator){
	Number one(1);

	NullIterator<Term *> nullIterator(&one);
	nullIterator.first();
	ASSERT_TRUE(nullIterator.isDone());

	Iterator<Term*> *it = one.createIterator();
	it->first();
	ASSERT_TRUE(it->isDone());
}

// Here are the 8 new Tests below
// combo1(bigMac, coke)
TEST(ITERATOR, BFS_simple_struct)
{
	// create combo1(bigMac, coke)
	Atom bigMac("bigMac");
	Atom coke("coke");

	vector<Term*> args;
	args.push_back(&bigMac);
	args.push_back(&coke);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createBFSIterator();
	it->first();
	EXPECT_EQ("bigMac", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ(2, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// combo1(bigMac(bun), coke)
TEST(ITERATOR, BFS_complex_struct)
{
	// create combo1(bigMac(bun), coke)
	Atom coke("coke");
	Atom bun("bun");

	vector<Term*> args;
	args.push_back(&bun);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createBFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun)", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	EXPECT_EQ(3, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// combo1(bigMac(bun, beefPatty), coke)
TEST(ITERATOR, BFS_complex_struct2)
{
	// create combo1(bigMac(bun, beefPatty), coke)
	Atom coke("coke");
	Atom bun("bun");
	Atom beefPatty("beefPatty");

	vector<Term*> args;
	args.push_back(&bun);
	args.push_back(&beefPatty);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createBFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun, beefPatty)", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("beefPatty", it->currentItem()->symbol());
	EXPECT_EQ(4, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// [fries1, fries2]
TEST(ITERATOR, BFS_simple_list)
{
	// create [fries1, fries2]
	Atom fries1("fries1");
	Atom fries2("fries2");

	vector<Term*> args;
	args.push_back(&fries1);
	args.push_back(&fries2);
	List l(args);

	// iterate it by BSF
	Iterator<Term*> *it = l.createBFSIterator();
	it->first();
	EXPECT_EQ("fries1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries2", it->currentItem()->symbol());
	EXPECT_EQ(2, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// [fries1, fries2, [noodle1, noodle2]]
TEST(ITERATOR, BFS_simple_list2)
{
	// create [fries1, fries2, [noodle1, noodle2]]
	Atom fries1("fries1");
	Atom fries2("fries2");
	Atom noodle1("noodle1");
	Atom noodle2("noodle2");

	vector<Term*> args;
	args.push_back(&noodle1);
	args.push_back(&noodle2);
	List sublist(args);

	args.clear();
	args.push_back(&fries1);
	args.push_back(&fries2);
	args.push_back(&sublist);
	List l(args);

	// iterate it by BSF
	Iterator<Term*> *it = l.createBFSIterator();
	it->first();
	EXPECT_EQ("fries1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries2", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[noodle1, noodle2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("noodle1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("noodle2", it->currentItem()->symbol());
	EXPECT_EQ(5, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// combo1(bigMac(bun, beefPatty), coke, [fries1, fries2])
TEST(ITERATOR, BFS_complex_struct3)
{
	// create combo1(bigMac(bun, beefPatty), coke, [fries1, fries2])
	Atom coke("coke");
	Atom bun("bun");
	Atom beefPatty("beefPatty");
	Atom fries1("fries1");
	Atom fries2("fries2");

	vector<Term*> args;
	args.push_back(&bun);
	args.push_back(&beefPatty);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&fries1);
	args.push_back(&fries2);
	List l(args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	args.push_back(&l);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createBFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun, beefPatty)", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[fries1, fries2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("beefPatty", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries2", it->currentItem()->symbol());
	EXPECT_EQ(7, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(ITERATOR, BFS_complex_struct_website_example)
{
	// create combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
	Atom coke("coke");
	Atom bun("bun");
	Atom beefPatty("beefPatty");
	Atom fries1("fries1");
	Atom fries2("fries2");
	Atom shreddedLettuce("shreddedLettuce");
	Atom sauce("sauce");
	Atom cheese("cheese");
	Atom pickleSlice1("pickleSlice1");
	Atom pickleSlice2("pickleSlice2");
	Atom onions1("onions1");
	Atom onions2("onions2");

	vector<Term*> args;
	args.push_back(&pickleSlice1);
	args.push_back(&pickleSlice2);
	List pickleSliceList(args);

	args.clear();
	args.push_back(&onions1);
	args.push_back(&onions2);
	List onionsList(args);

	args.clear();
	args.push_back(&bun);
	args.push_back(&beefPatty);
	args.push_back(&shreddedLettuce);
	args.push_back(&sauce);
	args.push_back(&cheese);
	args.push_back(&pickleSliceList);
	args.push_back(&onionsList);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&fries1);
	args.push_back(&fries2);
	List l(args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	args.push_back(&l);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createBFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2])", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[fries1, fries2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("beefPatty", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("shreddedLettuce", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("sauce", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("cheese", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[pickleSlice1, pickleSlice2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[onions1, onions2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries2", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("pickleSlice1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("pickleSlice2", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("onions1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("onions2", it->currentItem()->symbol());
	EXPECT_EQ(16, dynamic_cast<BFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// combo1(bigMac(bun, beefPatty), coke)
TEST(ITERATOR, DFS_simple_struct)
{
	// create combo1(bigMac(bun, beefPatty), coke)
	Atom coke("coke");
	Atom bun("bun");
	Atom beefPatty("beefPatty");

	vector<Term*> args;
	args.push_back(&bun);
	args.push_back(&beefPatty);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createDFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun, beefPatty)", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("beefPatty", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	EXPECT_EQ(4, dynamic_cast<DFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// [fires1, fires2]
TEST(ITERATOR, DFS_simple_list)
{
	// create [fires1, fires2]
	Atom fires1("fires1");
	Atom fires2("fires2");

	vector<Term*> args;
	args.push_back(&fires1);
	args.push_back(&fires2);
	List firesList(args);

	// iterate it by BSF
	Iterator<Term*> *it = firesList.createDFSIterator();
	it->first();
	EXPECT_EQ("fires1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fires2", it->currentItem()->symbol());
	EXPECT_EQ(2, dynamic_cast<DFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// [fires1, fires2]
TEST(ITERATOR, DFS_simple_list1)
{
	// create [fires1, fires2]
	Atom fires1("fires1");
	Atom fires2("fires2");

	vector<Term*> args;
	args.push_back(&fires1);
	args.push_back(&fires2);
	List firesList(args);

	// iterate it by BSF
	Iterator<Term*> *it = firesList.createDFSIterator();
	it->first();
	EXPECT_EQ("fires1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fires2", it->currentItem()->symbol());
	EXPECT_EQ(2, dynamic_cast<DFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// [fires1, fires2, [noodle1, noodle2]]
TEST(ITERATOR, DFS_simple_list2)
{
	// create [fires1, fires2, [noodle1, noodle2]]
	Atom fires1("fires1");
	Atom fires2("fires2");
	Atom noodle1("noodle1");
	Atom noodle2("noodle2");

	vector<Term*> args;
	args.push_back(&noodle1);
	args.push_back(&noodle2);
	List noodleList(args);

	args.clear();
	args.push_back(&fires1);
	args.push_back(&fires2);
	args.push_back(&noodleList);
	List firesList(args);

	ASSERT_EQ("[fires1, fires2, [noodle1, noodle2]]", firesList.symbol());

	// iterate it by BSF
	Iterator<Term*> *it = firesList.createDFSIterator();
	it->first();
	EXPECT_EQ("fires1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fires2", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[noodle1, noodle2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("noodle1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("noodle2", it->currentItem()->symbol());
	EXPECT_EQ(5, dynamic_cast<DFSIterator<Term*> *>(it)->_traverseSequence.size());
}

//// combo1(bigMac(bun, beefPatty), coke, [fires1, fires2])
TEST(ITERATOR, DFS_somplex_structList)
{
	// create combo1(bigMac(bun, beefPatty), coke, [fires1, fires2])
	Atom coke("coke");
	Atom bun("bun");
	Atom beefPatty("beefPatty");
	Atom fires1("fires1");
	Atom fires2("fires2");

	vector<Term*> args;
	args.push_back(&bun);
	args.push_back(&beefPatty);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&fires1);
	args.push_back(&fires2);
	List friesList(args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	args.push_back(&friesList);
	Struct combo1(Atom("combo1"), args);

	ASSERT_EQ("combo1(bigMac(bun, beefPatty), coke, [fires1, fires2])", combo1.symbol());

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createDFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun, beefPatty)", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("beefPatty", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[fires1, fires2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fires1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fires2", it->currentItem()->symbol());
	EXPECT_EQ(7, dynamic_cast<DFSIterator<Term*> *>(it)->_traverseSequence.size());
}

// combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
TEST(ITERATOR, DFS_complex_struct_website_example)
{
	// create combo1(bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2]), coke, [fries1, fries2])
	Atom coke("coke");
	Atom bun("bun");
	Atom beefPatty("beefPatty");
	Atom fries1("fries1");
	Atom fries2("fries2");
	Atom shreddedLettuce("shreddedLettuce");
	Atom sauce("sauce");
	Atom cheese("cheese");
	Atom pickleSlice1("pickleSlice1");
	Atom pickleSlice2("pickleSlice2");
	Atom onions1("onions1");
	Atom onions2("onions2");

	vector<Term*> args;
	args.push_back(&pickleSlice1);
	args.push_back(&pickleSlice2);
	List pickleSliceList(args);

	args.clear();
	args.push_back(&onions1);
	args.push_back(&onions2);
	List onionsList(args);

	args.clear();
	args.push_back(&bun);
	args.push_back(&beefPatty);
	args.push_back(&shreddedLettuce);
	args.push_back(&sauce);
	args.push_back(&cheese);
	args.push_back(&pickleSliceList);
	args.push_back(&onionsList);
	Struct bigMac(Atom("bigMac"), args);

	args.clear();
	args.push_back(&fries1);
	args.push_back(&fries2);
	List l(args);

	args.clear();
	args.push_back(&bigMac);
	args.push_back(&coke);
	args.push_back(&l);
	Struct combo1(Atom("combo1"), args);

	// iterate it by BSF
	Iterator<Term*> *it = combo1.createDFSIterator();
	it->first();
	EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onions1, onions2])", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("bun", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("beefPatty", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("shreddedLettuce", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("sauce", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("cheese", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[pickleSlice1, pickleSlice2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("pickleSlice1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("pickleSlice2", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[onions1, onions2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("onions1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("onions2", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("coke", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("[fries1, fries2]", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries1", it->currentItem()->symbol());
	it->next();
	EXPECT_EQ("fries2", it->currentItem()->symbol());
	EXPECT_EQ(16, dynamic_cast<DFSIterator<Term*> *>(it)->_traverseSequence.size());
}

#endif
