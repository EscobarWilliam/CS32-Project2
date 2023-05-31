//
//  main.cpp
//  CS32_Final_Project
//
//  Created by William  Escobar on 9/5/22.
//  Copyright © 2022 William  Escobar. All rights reserved.
//
#define TESTNUM 4

// (If you know how to specify a value for TESTNUM at the time you invoke the
// compiler, using either a project setting in Visual C++ or Xcode or by
// defining the value on the command line, you could leave the #define line
// above commented out and instead set TESTNUM that other way.)

#ifndef TESTNUM  // In case you haven't already defined the name TESTNUM
#define TESTNUM 0
#endif

//**************************************************************************
#if TESTNUM == 1
#include "Sequence.h"
#include <type_traits>

#define CHECKTYPE(c, f, r, a)  \
{  \
    static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
    "You did not declare " #c "::" #f " as the Project 2 spec does");  \
    auto p = static_cast<r (c::*)a>(&c::f);  \
    (void) p;  \
}
#define CHECKTYPENONMEMBER(f, r, a)  \
{  \
    static_assert(std::is_same<decltype(&f), r (*)a>::value, \
        "You did not declare " #f " as the Project 2 spec does");  \
    auto p = static_cast<r (*)a>(f);  \
    (void) p;  \
}

static_assert(std::is_default_constructible<Sequence>::value,
                "Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
                "Sequence must be copy-constructible.");
static_assert(std::is_copy_assignable<Sequence>::value,
                "Sequence must be assignable.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(Sequence, empty,  bool, () const);
    CHECKTYPE(Sequence, size,   int,  () const);
    CHECKTYPE(Sequence, erase,  bool, (int));
    CHECKTYPE(Sequence, remove, int,  (const ItemType&));
    CHECKTYPE(Sequence, get,    bool, (int, ItemType&) const);
    CHECKTYPE(Sequence, set,    bool, (int, const ItemType&));
    CHECKTYPE(Sequence, find,   int,  (const ItemType&) const);
    CHECKTYPE(Sequence, swap,   void, (Sequence&));
    CHECKTYPENONMEMBER(subsequence,   int,  (const Sequence&, const Sequence&));
    CHECKTYPENONMEMBER(concatReverse, void, (const Sequence&, const Sequence&, Sequence&));
    { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void) p; }
    { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void) p; }
        }

int main()
{}
//**************************************************************************
#elif TESTNUM == 2
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, "lavash") == 0);
    assert(s.insert(0, "tortilla") == 0);
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
//**************************************************************************
#elif TESTNUM == 3
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, 10) == 0);
    assert(s.insert(0, 20) == 0);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x)  &&  x == 20);
    assert(s.get(1, x)  &&  x == 10);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
//**************************************************************************
//**************************************************************************
#elif TESTNUM == 4
#include <iostream>
#include <cassert>
#include "Sequence.h"

void test()
{
    //test default constructor
    Sequence s;
    std::string x;
    int pos;

    assert(s.empty());                          //test empty()
    assert(s.insert(0,"e") == 0);               //test 1st insert()
    assert(s.insert(0,"a") == 0);
    assert(s.size() == 2);                      //test size()
    assert(s.remove("paratha") == 0);           //nothing to remove

    x="c";
    assert( (pos = s.insert(x)) && pos == 1 );  //test 2nd insert()
    assert(s.get(0, x) && x == "a");
    x = "g";
    assert( (pos = s.insert(x)) && pos == 3);
    assert( s.get(3,x) && x == "g");            //test get()
    x = "";

    Sequence r;
    assert(r.insert(0,"f") == 0);
    assert(r.insert(0,"b") == 0);
    assert(r.size() == 2);
    assert(r.remove("paratha") == 0);

    x="d";
    assert( (pos = r.insert(x)) && pos == 1 );
    assert( r.get(0, x) && x == "b");
    x = "h";
    assert( (pos = r.insert(x)) && pos == 3);
    assert(r.get(1, x) && x == "d");
    x = "";

    r.swap(s);                                  //test swap()
    assert(r.get(0,x) && x=="a" );              //test get after swap()
    assert((pos = subsequence(s, r)) && pos == -1 ); //test subsequence()


    r = s;                                      //test overload operator
    assert(r.get(0, x) && x == "b");
    assert(r.erase(0));                         //test erase()
    assert(r.get(0,x) && x == "d");             //test get after erase()
    
    x = "wild";
    assert(r.set(0, x));                        //test set()
    assert(r.get(0,x) && x == "wild");

    x="b";
    pos = s.find(x);                           //test find()
    assert(pos == 0);
    

    Sequence p(r);
    assert(p.get(0, x) && x == "wild");        //test copy constructor
    

}

int main()
{
    test();
    std::cout << "Passed all tests" << std::endl;
    return 0;
}


#elif TESTNUM == 5

#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    //Test creation and maintianing code for sequence class
    Sequence s1;
    assert(s1.insert(0, "p") == 0);
    assert(s1.insert(1, "a") == 1);
    assert(s1.insert(2, "r") == 2);
    
    Sequence s2;
    assert(s2.insert(0, "r") == 0);
    assert(s2.insert(1, "o") == 1);
    assert(s2.insert(2, "t") == 2);
    //-----------------------------------------------------
    
    //Test oncatReverse() functionality-----
    Sequence result;
    concatReverse(s1,s2,result);
    
    assert(result.size() == 6);
    ItemType x;
    assert(result.get(0,x) && x == "r");
    assert(result.get(1,x) && x == "a");
    assert(result.get(2,x) && x == "p");
    assert(result.get(3,x) && x == "t");
    assert(result.get(4,x) && x == "o");
    assert(result.get(5,x) && x == "r");
    result.dump();
    //--------------------------------------
    
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#elif TESTNUM == 6
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s1;
    assert(s1.insert(0, "a") == 0);
    assert(s1.insert(1, "b") == 1);
    assert(s1.insert(2, "c") == 2);
    assert(s1.insert(3, "d") == 3);
    assert(s1.insert(4, "e") == 4);
    assert(s1.insert(5, "f") == 5);
    assert(s1.insert(6, "g") == 6);
    
    Sequence s2;
    assert(s2.insert(0, "b") == 0);
    assert(s2.insert(1, "c") == 1);
    assert(s2.insert(2, "d") == 2);
    assert(s2.insert(3, "e") == 3);
    
    //S2 IS A SUBSEQUENCE
    Sequence result;
    assert(subsequence(s1, s2) == 1);
    
    //-----------------------------
    //THIS NEXT TEST CHECKS TO MAKE
    //SURE SUBSEQUENCE WORKS PROPERLY
    //WITH A SEQUENCE THAT IS ALMOST
    //A SUBSEQUENCE
    
    //s2 ISNT A SUBSEQUENCE
    
    assert(s2.insert(0, "b") == 0);
    assert(s2.insert(1, "c") == 1);
    assert(s2.insert(2, "d") == 2);
    assert(s2.insert(3, "F") == 3);
    assert( !(subsequence(s1, s2) == 1) );
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

#else
int main()
{
    return 0;
}
#endif
