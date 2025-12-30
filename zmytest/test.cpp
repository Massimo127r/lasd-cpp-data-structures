/* ************************************************************************** */
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <limits>
#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"
#include "../zlasdtest/heap/heap.hpp"
#include "../zlasdtest/pq/pq.hpp"


#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

#include "../heap/vec/heapvec.hpp"
#include "../pq/heap/pqheap.hpp"
using namespace lasd;

using namespace std;
namespace mytest {

template <typename Data>
void InsertPQM(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, const Data & val) {
    testnum++;
    bool tst = true;
    try {
        std::cout << " " << testnum << " Insert on the priority queue of the value \"" << val << "\": ";
        pq.Insert(std::move(val));
        std::cout << "Correct!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
        tst = false;
    }
    testerr += (1 - (uint) tst);
}

template <typename Data>
void ChangePQM(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, ulong idx, const Data & val) {
    testnum++;
    bool tst = true;
    try {
        std::cout << " " << testnum << " Change the value \"" << pq[idx] << "\" at index << \"" << idx << "\" to the value \"" << val << "\" in the priority queue: ";
        pq.Change(idx, std::move(val));
        std::cout << "Correct!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
        tst = false;
    }
    testerr += (1 - (uint) tst);
}

void Clear(uint & testnum, uint & testerr,  lasd::ClearableContainer & con) {
    bool tst;
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Clearing the container: ";
    con.Clear();
    std::cout << ((tst = (con.Empty())) ? "Correct" : "Error") << "!" << std::endl;
    testerr += (1 - (uint) tst);
}

template <typename Data>
void Sort(uint & testnum, uint & testerr, lasd::SortableVector<Data> & con, lasd::SortableVector<Data> &  c2, bool chk) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") Sorting Array ";
        con.Sort();

        std::cout << ((tst = ((con == c2) == chk)) ? "Correct" : "Error") << "!" << std::endl;
    } catch(std::out_of_range & exc) {

        std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }  catch(std::exception & exc) {
        tst = false;
        std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
    }
    testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertAtFrontM(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") Insert at the front of the list the value \"" << val << "\": ";
        lst.InsertAtFront(move(val));
        std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }
    testerr += (1 - (uint) tst);
}

template <typename Data>
void InsertAtBackM(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") Insert at the back of the list the value \"" << val << "\": ";
        lst.InsertAtBack(move(val));
        std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }
    testerr += (1 - (uint) tst);
}

/* ************************************************************************** */
void stestVectorInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector<int> Test:" << endl;
    try {
        {
            cout << endl << "Begin of empty Vector<int> Test:" << endl;

            lasd::SortableVector<int> vec;
            lasd::SortableVector<int> vec2;
            vec2 = vec;
            GetAt(loctestnum, loctesterr, vec, false, 2, 0);
            vec2.Sort();
            EqualVector(loctestnum, loctesterr, vec, vec2, true);
            Empty(loctestnum, loctesterr, vec, true);
            Size(loctestnum, loctesterr, vec, true, 0);

            SetAt(loctestnum, loctesterr, vec, false, 1, 0);
            SetBack(loctestnum, loctesterr, vec, false, 1);
            SetFront(loctestnum, loctesterr, vec, false, 1);

            GetFront(loctestnum, loctesterr, vec, false, 0);
            GetBack(loctestnum, loctesterr, vec, false, 0);
            GetAt(loctestnum, loctesterr, vec, false, 2, 0);

            Exists(loctestnum, loctesterr, vec, false, 0);

            Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
            FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
            FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);

            Map(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPostOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);

            lasd::SortableVector<int> chk;
            Sort(loctestnum, loctesterr, vec, chk, true);
            Clear(loctestnum, loctesterr, vec);

            cout  << "End of empty Vector<int> Test" << endl;




        }
        {
            cout << endl << "Begin of  Vector<int> Test:" << endl;

            lasd::SortableVector<int> vec(3);
            Empty(loctestnum, loctesterr, vec, false);
            Size(loctestnum, loctesterr, vec, true, 3);

            SetAt(loctestnum, loctesterr, vec, true, 0, 4);
            SetAt(loctestnum, loctesterr, vec, true, 1, 3);
            SetAt(loctestnum, loctesterr, vec, true, 2, 1);

            GetFront(loctestnum, loctesterr, vec, true, 4);
            GetBack(loctestnum, loctesterr, vec, true, 1);
            GetAt(loctestnum, loctesterr, vec, true, 2, 1);

            SetFront(loctestnum, loctesterr, vec, true, 5);
            SetBack(loctestnum, loctesterr, vec, true, 4);

            Exists(loctestnum, loctesterr, vec, true, 4);

            Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 12);
            FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 12);
            FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 2, 120);

            Map(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPostOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);

            lasd::SortableVector<int> chk(vec);
            Sort(loctestnum, loctesterr, vec, chk, false);
            chk.Sort();
            Sort(loctestnum, loctesterr, vec, chk, true);

            TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            vec.Resize(2);
            FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 42);

            lasd::SortableVector<int> mv(move(vec));
            TraversePostOrder(loctestnum, loctesterr, mv, true, &TraversePrint<int>);

            Clear(loctestnum, loctesterr, mv);
        }
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testVectorDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector<double> Test:" << endl;
    try {
        lasd::SortableVector<double> vec(3);
        Empty(loctestnum, loctesterr, vec, false);
        Size(loctestnum, loctesterr, vec, true, 3);

        SetAt(loctestnum, loctesterr, vec, true, 0, 2.5);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3.3);
        SetAt(loctestnum, loctesterr, vec, true, 2, 6.1);

        SetFront(loctestnum, loctesterr, vec, true, 5.5);
        SetBack(loctestnum, loctesterr, vec, true, 1.1);

        GetFront(loctestnum, loctesterr, vec, true, 5.5);
        GetBack(loctestnum, loctesterr, vec, true, 1.1);
        GetAt(loctestnum, loctesterr, vec, true, 2, 1.1);

        Exists(loctestnum, loctesterr, vec, true, 3.3);


        Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 9.9);
        FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 9.9);
        FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 19.965);

        Map(loctestnum, loctesterr, vec, true, &MapIncrement<double>);
        MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<double>);
        MapPostOrder(loctestnum, loctesterr, vec, true, &MapIncrement<double>);

        lasd::SortableVector<double> chk(vec);
        chk.Sort();
        Sort(loctestnum, loctesterr, vec, chk, true);
        TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);

        vec.Resize(2);
        FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 1, 11);


        Clear(loctestnum, loctesterr, vec);


    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testVectorString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector<string> Test:" << endl;
    try {
        lasd::SortableVector<string> vec(2);

        Empty(loctestnum, loctesterr, vec, false);
        Size(loctestnum, loctesterr, vec, true, 2);

        SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

        GetFront(loctestnum, loctesterr, vec, true, string("A"));
        GetBack(loctestnum, loctesterr, vec, true, string("B"));
        GetAt(loctestnum, loctesterr, vec, true, 1, string("B"));

        Exists(loctestnum, loctesterr, vec, true, string("A"));

        SetFront(loctestnum, loctesterr, vec, true, string("N"));
        SetBack(loctestnum, loctesterr, vec, true, string("A"));

        MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) {
            MapStringAppend(str, string(" "));
        });

        Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);

        Fold(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XN A "));
        FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XN A "));
        FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XA N "));

        Exists(loctestnum, loctesterr, vec, false, string("A"));

        lasd::SortableVector<string> copvec(vec);
        EqualVector(loctestnum, loctesterr, vec, copvec, true);

        MapPostOrder(loctestnum, loctesterr, vec, true, [](string & str) {
            MapStringAppend(str, string("!"));
        });
        MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) {
            MapStringAppend(str, string("!"));
        });
        NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

        copvec = move(vec);
        FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("?"), string("?N !!A !!"));

        lasd::SortableVector<string> movvec(move(vec));
        FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?N A "));

        lasd::SortableVector<string> chk(movvec);
        movvec.Sort();
        Sort(loctestnum, loctesterr, chk, movvec, true);
        FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?A N "));
        SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
        vec.Resize(1);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));

        movvec.Clear();
        Clear(loctestnum, loctesterr, vec);
        Empty(loctestnum, loctesterr, movvec, true);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testVector(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    stestVectorInt(loctestnum, loctesterr);
    testVectorDouble(loctestnum, loctesterr);
    testVectorString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
/* ************************************************************************** */

void testListInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<int> Test:" << endl;
    try {
        lasd::List<int> lst;
        lasd::List<int> lstq;
        lstq = lst;
        EqualList(loctestnum, loctesterr, lst, lstq, true);
        Empty(loctestnum, loctesterr, lst, true);
        Size(loctestnum, loctesterr, lst, true, 0);

        GetFront(loctestnum, loctesterr, lst, false, 0);
        GetBack(loctestnum, loctesterr, lst, false, 0);

        Exists(loctestnum, loctesterr, lst, false, 0);

        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);

        RemoveFromFront(loctestnum, loctesterr, lst, false);
        FrontNRemove(loctestnum, loctesterr, lst, false, 0);

        InsertAtBack(loctestnum, loctesterr, lst, true, 4);
        InsertAtFront(loctestnum, loctesterr, lst, true, 5);
        InsertAtFront(loctestnum, loctesterr, lst, true, 9);
        InsertAtBack(loctestnum, loctesterr, lst, true, 2);
        InsertAtFront(loctestnum, loctesterr, lst, true, 1);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        InsertAtFrontM(loctestnum, loctesterr, lst, true, 5);
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        InsertAtBackM(loctestnum, loctesterr, lst, true, 5);
        RemoveFromBack(loctestnum, loctesterr, lst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        GetFront(loctestnum, loctesterr, lst, true, 1);
        GetBack(loctestnum, loctesterr, lst, true, 2);
        SetFront(loctestnum, loctesterr, lst, true, 2);
        SetBack(loctestnum, loctesterr, lst, true, 6);

        GetAt(loctestnum, loctesterr, lst, true, 3, 4);
        SetAt(loctestnum, loctesterr, lst, true, 3, 3);

        Exists(loctestnum, loctesterr, lst, false, 4);
        Exists(loctestnum, loctesterr, lst, true, 3);

        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        Fold(loctestnum, loctesterr, lst, false, &FoldParity, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 25);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 1620);

        RemoveFromFront(loctestnum, loctesterr, lst, true);
        FrontNRemove(loctestnum, loctesterr, lst, true, 9);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 90);

        lasd::List<int> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        Map(loctestnum, loctesterr, lst, true, &MapDouble<int>);

        MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        InsertAtFront(loctestnum, loctesterr, lst, true, 0);
        InsertAtBack(loctestnum, loctesterr, lst, true, 0);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);
        coplst = lst;
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        RemoveFromFront(loctestnum, loctesterr, coplst, true);
        FrontNRemove(loctestnum, loctesterr, coplst, true, 11);
        coplst = move(lst);
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 20);
        FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldAdd<int>, 0, 31);

        lasd::List<int> movlst(move(lst));
        MapPostOrder(loctestnum, loctesterr, movlst, true, &MapIncrement<int>);
        Traverse(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
        FoldPreOrder(loctestnum, loctesterr, movlst, false, &FoldAdd<int>, 0, 14);

        InsertAtFront(loctestnum, loctesterr, movlst, true, 6);
        InsertAtBack(loctestnum, loctesterr, movlst, true, 8);
        RemoveFromFront(loctestnum, loctesterr, movlst, true);
        InsertAtBack(loctestnum, loctesterr, movlst, true, 7);
        Traverse(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 1, 39);
        BackNRemove(loctestnum, loctesterr, movlst, false, 0);

        Clear(loctestnum, loctesterr, movlst);
        Empty(loctestnum, loctesterr, movlst, true);
        Size(loctestnum, loctesterr, movlst, true, 0);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testListDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<double> Test:" << endl;
    try {
        lasd::List<double> lst;
        lasd::List<double> lstq;
        lstq = lst;

        EqualList(loctestnum, loctesterr, lst, lstq, true);
        Clear(loctestnum, loctesterr, lstq);
        Empty(loctestnum, loctesterr, lst, true);
        Size(loctestnum, loctesterr, lst, true, 0);

        GetFront(loctestnum, loctesterr, lst, false, 0.0);
        GetBack(loctestnum, loctesterr, lst, false, 0.0);
        Exists(loctestnum, loctesterr, lst, false, 0.0);

        RemoveFromFront(loctestnum, loctesterr, lst, false);
        FrontNRemove(loctestnum, loctesterr, lst, false, 0.0);

        InsertAtBack(loctestnum, loctesterr, lst, true, -3.5);
        InsertAtBack(loctestnum, loctesterr, lst, true, 3.5);
        SetFront(loctestnum, loctesterr, lst, true, -2.5);
        SetBack(loctestnum, loctesterr, lst, true, 2.5);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        lst.Clear();
        InsertAtFrontM(loctestnum, loctesterr, lst, true, 5.1);
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        InsertAtBackM(loctestnum, loctesterr, lst, true, 5.0);
        RemoveFromBack(loctestnum, loctesterr, lst, true);
        InsertAtBack(loctestnum, loctesterr, lst, true, 1.5);
        InsertAtFront(loctestnum, loctesterr, lst, true, 3.3);
        InsertAtFront(loctestnum, loctesterr, lst, true, 5.5);
        InsertAtBack(loctestnum, loctesterr, lst, true, 1.1);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        GetAt(loctestnum, loctesterr, lst, true, 3, 1.1);
        SetAt(loctestnum, loctesterr, lst, true, 3, 0.5);



        GetFront(loctestnum, loctesterr, lst, true, 5.5);
        GetBack(loctestnum, loctesterr, lst, false, 1.1);

        Exists(loctestnum, loctesterr, lst, false, 0.0);

        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, lst, false, &FoldAdd<double>, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 10.8);
        FoldPostOrder(loctestnum, loctesterr, lst, false, &FoldMultiply<double>, 1.0, 9.9825);

        lasd::List<double> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        Map(loctestnum, loctesterr, lst, true, &MapHalf<double>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);
        BackNRemove(loctestnum, loctesterr, coplst, true, 0.5);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<double>);
        MapPostOrder(loctestnum, loctesterr, coplst, true, &MapIncrement<double>);
        lasd::List<double> movlst(move(coplst));
        MapPreOrder(loctestnum, loctesterr, movlst, true, &MapInvert<double>);

        Traverse(loctestnum, loctesterr, movlst, true, &TraversePrint<double>);
        Clear(loctestnum, loctesterr, movlst);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testListString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<string> Test:" << endl;
    try {
        lasd::List<string> lst;
        lasd::List<string> lstq;
        lstq = lst;

        EqualList(loctestnum, loctesterr, lst, lstq, true);
        Clear(loctestnum, loctesterr, lstq);
        Empty(loctestnum, loctesterr, lst, true);
        Size(loctestnum, loctesterr, lst, true, 0);

        GetFront(loctestnum, loctesterr, lst, false, string("A"));
        GetBack(loctestnum, loctesterr, lst, false, string("A"));
        Exists(loctestnum, loctesterr, lst, false, string("A"));

        RemoveFromFront(loctestnum, loctesterr, lst, false);
        FrontNRemove(loctestnum, loctesterr, lst, false, string("A"));

        InsertAtFront(loctestnum, loctesterr, lst, true, string("N"));
        InsertAtBack(loctestnum, loctesterr, lst, true, string("A"));
        SetFront(loctestnum, loctesterr, lst, true, string("A"));
        SetBack(loctestnum, loctesterr, lst, true, string("B"));
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
        GetFront(loctestnum, loctesterr, lst, true, string("A"));
        GetBack(loctestnum, loctesterr, lst, true, string("B"));

        Exists(loctestnum, loctesterr, lst, true, string("B"));

        InsertAtFrontM(loctestnum, loctesterr, lst, true, string("front"));
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        InsertAtBackM(loctestnum, loctesterr, lst, true,  string("back"));
        GetAt(loctestnum, loctesterr, lst, true, 2, string("back"));
        SetAt(loctestnum, loctesterr, lst, true, 2, string("B"));
        RemoveFromBack(loctestnum, loctesterr, lst, true);

        MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) {
            MapStringAppend(str, string(" "));
        });
        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XA B "));
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XB A "));

        Exists(loctestnum, loctesterr, lst, false, string("B"));

        lasd::List<string> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        RemoveFromFront(loctestnum, loctesterr, coplst, true);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);

        lst = coplst;
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        InsertAtBack(loctestnum, loctesterr, lst, true, string("A"));
        InsertAtFront(loctestnum, loctesterr, lst, true, string("C"));
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);

        coplst = move(lst);
        FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldStringConcatenate, string("?"), string("?CB A"));
        MapPostOrder(loctestnum, loctesterr, coplst, true, [](string & str) {
            MapStringNonEmptyAppend(str, string("A"));
        });
        Map(loctestnum, loctesterr, coplst, true, [](string & str) {
            MapStringNonEmptyAppend(str, string("A"));
        });
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<string>);
        Clear(loctestnum, loctesterr, coplst);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testList(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testListInt(loctestnum, loctesterr);
    testListDouble(loctestnum, loctesterr);
    testListString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testSetInt(lasd::Set<int> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Empty(loctestnum, loctesterr, set, false);
        Size(loctestnum, loctesterr, set, true, 7);

        GetAt(loctestnum, loctesterr, set, true, 0, 0);
        GetBack(loctestnum, loctesterr, set, false, 0);
        GetFront(loctestnum, loctesterr, set, false, 6);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Min(loctestnum, loctesterr, set, true, 0);
        Max(loctestnum, loctesterr, set, true, 6);

        RemoveMin(loctestnum, loctesterr, set, true);
        MinNRemove(loctestnum, loctesterr, set, true, 1);

        InsertC(loctestnum, loctesterr, set, true, -1);
        InsertC(loctestnum, loctesterr, set, true, 1);

        Min(loctestnum, loctesterr, set, true, -1);
        MaxNRemove(loctestnum, loctesterr, set, true, 6);
        Size(loctestnum, loctesterr, set, true, 6);

        InsertC(loctestnum, loctesterr, set, true, 7);

        Size(loctestnum, loctesterr, set, true, 7);

        Max(loctestnum, loctesterr, set, true, 7);

        InsertC(loctestnum, loctesterr, set, true, 8);

        Size(loctestnum, loctesterr, set, true, 8);

        Exists(loctestnum, loctesterr, set, true, 8);
        Exists(loctestnum, loctesterr, set, false, 9);
        Exists(loctestnum, loctesterr, set, false, 0);
        Exists(loctestnum, loctesterr, set, true, -1);
        Exists(loctestnum, loctesterr, set, true, 3);
        Exists(loctestnum, loctesterr, set, true, 4);
        InsertC(loctestnum, loctesterr, set, true, 9);

        Exists(loctestnum, loctesterr, set, true, 4);
        Remove(loctestnum, loctesterr, set, true, 9);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Remove(loctestnum, loctesterr, set, false, 6);
        Remove(loctestnum, loctesterr, set, true, 2);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Exists(loctestnum, loctesterr, set, false, 6);
        Exists(loctestnum, loctesterr, set, false, 2);

        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, 7);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Predecessor(loctestnum, loctesterr, set, true, 4, 3);
        Predecessor(loctestnum, loctesterr, set, true, 5, 4);

        Successor(loctestnum, loctesterr, set, true, 2, 3);
        Successor(loctestnum, loctesterr, set, true, 4, 5);

        SuccessorNRemove(loctestnum, loctesterr, set, true, 0, 1);
        Min(loctestnum, loctesterr, set, true, -1);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        PredecessorNRemove(loctestnum, loctesterr, set, true, 7, 5);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Max(loctestnum, loctesterr, set, true, 7);

        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Fold(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 13);
        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 13);
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 13);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        RemovePredecessor(loctestnum, loctesterr, set, false, -3);
        RemovePredecessor(loctestnum, loctesterr, set, true, 4);
        RemovePredecessor(loctestnum, loctesterr, set, true, 0);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        RemoveSuccessor(loctestnum, loctesterr, set, false, 7);
        RemoveSuccessor(loctestnum, loctesterr, set, true, 4);


        Clear(loctestnum, loctesterr, set);
        Clear(loctestnum, loctesterr, set);
        InsertM(loctestnum, loctesterr, set, true, move(1));
        InsertC(loctestnum, loctesterr, set, true, 3);
        InsertC(loctestnum, loctesterr, set, true, -1);
        InsertC(loctestnum, loctesterr, set, false, -1);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        lasd::List<int> list;
        InsertAllC(loctestnum, loctesterr, set, true, list);

        list.InsertAtBack(4);
        list.InsertAtFront(5);
        list.InsertAtFront(9);
        list.InsertAtFront(1);
        list.InsertAtBack(2);

        InsertAllC(loctestnum, loctesterr, set, false, list);
        lasd::List<int> list2;
        list2.InsertAtFront(12);
        list2.InsertAtFront(13);
        list2.InsertAtFront(14);

        InsertAllM(loctestnum, loctesterr, set, true, move(list2));

        Remove(loctestnum, loctesterr, set, true, -1);
        Remove(loctestnum, loctesterr, set, true, 1);
        Remove(loctestnum, loctesterr, set, false, 120);

        RemoveAll(loctestnum, loctesterr, set, false, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);


        list2.Clear();
        list2.InsertAtFront(3);
        list2.InsertAtFront(120);

        InsertSomeC(loctestnum, loctesterr, set, true, list2);
        list2.InsertAtFront(121);


        InsertSomeC(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        list.Front() = 12;
        list.Back() = 121;

        RemoveSome(loctestnum, loctesterr, set, true, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        Clear(loctestnum, loctesterr, set);

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testSetInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Set<int> Test" << endl;
    try {
        lasd::Vector<int> vec(7);
        SetAt(loctestnum, loctesterr, vec, true, 0, 3);
        SetAt(loctestnum, loctesterr, vec, true, 1, 1);
        SetAt(loctestnum, loctesterr, vec, true, 2, 6);
        SetAt(loctestnum, loctesterr, vec, true, 3, 5);
        SetAt(loctestnum, loctesterr, vec, true, 4, 0);
        SetAt(loctestnum, loctesterr, vec, true, 5, 2);
        SetAt(loctestnum, loctesterr, vec, true, 6, 4);
        lasd::SetVec<int> setTest;
        InsertSomeM(loctestnum, loctesterr,setTest, true, std::move(vec));
        /* ********************************************************************** */

    cout << endl << "Begin of SetVec<int> Test:" << endl;
    lasd::SetVec<int> setvec(vec);


    testSetInt(setvec, loctestnum, loctesterr);
    cout << endl << "Begin of SetLst<int> Test:" << endl;
    lasd::SetLst<int> setlst(vec);
    testSetInt(setlst, loctestnum, loctesterr);
    cout << "\n";

    /* ***********************************************************************/
    cout << endl << "SetVec<int> and SetLst<int> Test:" << endl;

    setvec.InsertAll(vec);
    
    lasd::SetVec<int> setvec1(setvec);
    Traverse(loctestnum, loctesterr, setvec, true, &TraversePrint<int>);
    Traverse(loctestnum, loctesterr, setvec1, true, &TraversePrint<int>);
    EqualSetVec(loctestnum, loctesterr, setvec, setvec1, true);
    Remove(loctestnum, loctesterr, setvec1, true, 4);

    NonEqualSetVec(loctestnum, loctesterr, setvec, setvec1, true);
    Traverse(loctestnum, loctesterr, setvec, true, &TraversePrint<int>);
    Traverse(loctestnum, loctesterr, setvec1, true, &TraversePrint<int>);

    InsertC(loctestnum, loctesterr, setvec1, true, 4);

    EqualSetVec(loctestnum, loctesterr, setvec, setvec1, true);

    lasd::SetVec<int> setvec2 = setvec1;

    EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);

    RemovePredecessor(loctestnum, loctesterr, setvec1, true, 9);

    EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);

    lasd::SetVec<int> setvec3(move(setvec2));

    Empty(loctestnum, loctesterr, setvec2, true);
    Size(loctestnum, loctesterr, setvec2, true, 0);

    Empty(loctestnum, loctesterr, setvec3, false);
    Size(loctestnum, loctesterr, setvec3, true, 7);

    setvec2 = move(setvec1);

    Empty(loctestnum, loctesterr, setvec1, true);
    Size(loctestnum, loctesterr, setvec1, true, 0);

    Empty(loctestnum, loctesterr, setvec2, false);
    Size(loctestnum, loctesterr, setvec2, true, 6);

    NonEqualSetVec(loctestnum, loctesterr, setvec3, setvec2, true);

    Traverse(loctestnum, loctesterr, setvec2, true, &TraversePrint<int>);
    Traverse(loctestnum, loctesterr, setvec3, true, &TraversePrint<int>);

    InsertC(loctestnum, loctesterr, setvec2, true, 6);

    EqualSetVec(loctestnum, loctesterr, setvec3, setvec2, true);

    /* ********************************************************************** */

    setlst.InsertAll(vec);
    lasd::SetLst<int> setlst1(setlst);

    EqualSetLst(loctestnum, loctesterr, setlst, setlst1, true);

    Remove(loctestnum, loctesterr, setlst1, true, 4);

    NonEqualSetLst(loctestnum, loctesterr, setlst, setlst1, true);

    InsertC(loctestnum, loctesterr, setlst1, true, 4);

    EqualSetLst(loctestnum, loctesterr, setlst, setlst1, true);

    lasd::SetLst<int> setlst2 = setlst1;

    EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);

    RemovePredecessor(loctestnum, loctesterr, setlst1, true, 9);

    EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);

    lasd::SetLst<int> setlst3(move(setlst2));

    Empty(loctestnum, loctesterr, setlst2, true);
    Size(loctestnum, loctesterr, setlst2, true, 0);

    Empty(loctestnum, loctesterr, setlst3, false);
    Size(loctestnum, loctesterr, setlst3, true, 7);

    setlst2 = move(setlst1);

    Empty(loctestnum, loctesterr, setlst1, true);
    Size(loctestnum, loctesterr, setlst1, true, 0);

    Empty(loctestnum, loctesterr, setlst2, false);
    Size(loctestnum, loctesterr, setlst2, true, 6);

    NonEqualSetLst(loctestnum, loctesterr, setlst3, setlst2, true);

    Traverse(loctestnum, loctesterr, setlst2, true, &TraversePrint<int>);
    Traverse(loctestnum, loctesterr, setlst3, true, &TraversePrint<int>);

    InsertC(loctestnum, loctesterr, setlst2, true, 6);

    EqualSetLst(loctestnum, loctesterr, setlst3, setlst2, true);

    /* ********************************************************************** */

    EqualLinear(loctestnum, loctesterr, setvec3, setlst2, true);
    NonEqualLinear(loctestnum, loctesterr, setlst3, setvec2, false);


    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testSetFloat(lasd::Set<double> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        cout << endl << "Begin of Set<double> Test" << endl << endl;

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Empty(loctestnum, loctesterr, set, false);
        Size(loctestnum, loctesterr, set, true, 6);

        GetAt(loctestnum, loctesterr, set, true, 3, 3.5);
        GetBack(loctestnum, loctesterr, set, false, 5.4);
        GetFront(loctestnum, loctesterr, set, true, 0.4);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Min(loctestnum, loctesterr, set, true, 0.4);
        Max(loctestnum, loctesterr, set, false, 6.1);

        RemoveMin(loctestnum, loctesterr, set, true);
        MinNRemove(loctestnum, loctesterr, set, true, 1.2);

        InsertC(loctestnum, loctesterr, set, true, -1.1);
        InsertC(loctestnum, loctesterr, set, true, 1.0);

        Min(loctestnum, loctesterr, set, true, -1.1);
        MaxNRemove(loctestnum, loctesterr, set, false, 6.0);
        Size(loctestnum, loctesterr, set, true, 5);

        InsertC(loctestnum, loctesterr, set, true, 7.0);

        Size(loctestnum, loctesterr, set, false, 7);

        Max(loctestnum, loctesterr, set, true, 7.0);

        InsertC(loctestnum, loctesterr, set, true, 8.4);

        Size(loctestnum, loctesterr, set, true, 7);

        Exists(loctestnum, loctesterr, set, true, 8.4);
        Exists(loctestnum, loctesterr, set, false, 9.0);
        Exists(loctestnum, loctesterr, set, false, 0.0);
        Exists(loctestnum, loctesterr, set, true, -1.1);
        Exists(loctestnum, loctesterr, set, false, 2.0);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Remove(loctestnum, loctesterr, set, false, 6.0);
        Remove(loctestnum, loctesterr, set, true, -1.1);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Exists(loctestnum, loctesterr, set, false, 6.0);
        Exists(loctestnum, loctesterr, set, false, 2.0);

        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, 7.0);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Predecessor(loctestnum, loctesterr, set, true, 4.0, 3.5);
        Predecessor(loctestnum, loctesterr, set, true, 4.9, 4.0);

        Successor(loctestnum, loctesterr, set, true, 1.6, 2.1);
        Successor(loctestnum, loctesterr, set, true, 4.0, 7.0);

        SuccessorNRemove(loctestnum, loctesterr, set, true, 0.0, 1.0);
        Min(loctestnum, loctesterr, set, true, 2.1);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        PredecessorNRemove(loctestnum, loctesterr, set, true, 7.0, 4.0);
        Max(loctestnum, loctesterr, set, true, 7.0);

        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, set, true, &FoldAdd<double>, 0.0, 12.6);
        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<double>, 0.0, 12.6);
        FoldPostOrder(loctestnum, loctesterr, set, false, &FoldAdd<double>, 0.0, 11.5);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        RemovePredecessor(loctestnum, loctesterr, set, false, -3.0);
        RemovePredecessor(loctestnum, loctesterr, set, true, 4.0);
        RemovePredecessor(loctestnum, loctesterr, set, false, 0.0);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        RemoveSuccessor(loctestnum, loctesterr, set, false, 7.0);
        RemoveSuccessor(loctestnum, loctesterr, set, true, 4.0);


        Clear(loctestnum, loctesterr, set);
        Clear(loctestnum, loctesterr, set);
        InsertM(loctestnum, loctesterr, set, true, move(1.0));
        InsertC(loctestnum, loctesterr, set, true, 3.0);
        InsertC(loctestnum, loctesterr, set, true, -1.0);
        InsertC(loctestnum, loctesterr, set, false, -1.0);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        lasd::List<double> list;
        InsertAllC(loctestnum, loctesterr, set, true, list);

        list.InsertAtBack(4.0);
        list.InsertAtFront(5.0);
        list.InsertAtFront(9.0);
        list.InsertAtFront(1.0);
        list.InsertAtBack(2.0);

        InsertAllC(loctestnum, loctesterr, set, false, list);
        lasd::List<double> list2;
        list2.InsertAtFront(12.0);
        list2.InsertAtFront(13.0);
        list2.InsertAtFront(14.0);

        InsertAllM(loctestnum, loctesterr, set, true, move(list2));

        Remove(loctestnum, loctesterr, set, true, -1.0);
        Remove(loctestnum, loctesterr, set, true, 1.0);
        Remove(loctestnum, loctesterr, set, false, 120.0);

        RemoveAll(loctestnum, loctesterr, set, false, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);


        list2.Clear();
        list2.InsertAtFront(3.0);
        list2.InsertAtFront(120.0);

        InsertSomeC(loctestnum, loctesterr, set, true, list2);
        list2.InsertAtFront(121.0);


        InsertSomeC(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        list.Front() = 12.0;
        list.Back() = 121.0;

        RemoveSome(loctestnum, loctesterr, set, true, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        Clear(loctestnum, loctesterr, set);

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << endl << "End of Set<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")\n" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testSetFloat(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Set<double> Test" << endl;
    try {
        lasd::List<double> lst;
        InsertAtFront(loctestnum, loctesterr, lst, true, 4.0);
        InsertAtBack(loctestnum, loctesterr, lst, true, 0.4);
        InsertAtFront(loctestnum, loctesterr, lst, true, 1.2);
        InsertAtBack(loctestnum, loctesterr, lst, true, 2.1);
        InsertAtFront(loctestnum, loctesterr, lst, true, 3.5);
        InsertAtBack(loctestnum, loctesterr, lst, true, 5.3);

        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        /* ***********************************************************************/

        lasd::SetVec<double> setvec1(lst);
        cout << endl << "Begin of SetVec<double> Test:" << endl;

        testSetFloat(setvec1, loctestnum, loctesterr);
        InsertAllC(loctestnum, loctesterr, setvec1, true, lst);
        Empty(loctestnum, loctesterr, setvec1, false);
        Size(loctestnum, loctesterr, setvec1, true, 6);

        TraversePreOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);

        lasd::SetVec<double> setvec2;

        InsertC(loctestnum, loctesterr, setvec2, true, 2.1);
        InsertC(loctestnum, loctesterr, setvec2, true, 0.4);
        InsertC(loctestnum, loctesterr, setvec2, true, 1.2);
        InsertC(loctestnum, loctesterr, setvec2, true, 3.5);
        InsertC(loctestnum, loctesterr, setvec2, true, 5.3);
        InsertC(loctestnum, loctesterr, setvec2, true, 4.0);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);
        NonEqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);

        setvec1.Clear();
        setvec2.Clear();

        InsertC(loctestnum, loctesterr, setvec1, true, 0.2);
        InsertC(loctestnum, loctesterr, setvec1, true, 1.1);
        InsertC(loctestnum, loctesterr, setvec1, true, 2.1);

        InsertC(loctestnum, loctesterr, setvec2, true, 2.1);
        InsertC(loctestnum, loctesterr, setvec2, true, 1.1);
        InsertC(loctestnum, loctesterr, setvec2, true, 0.2);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);
        NonEqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);

        /* ********************************************************************** */

        lasd::SetLst<double> setlst1(lst);
        cout << endl << "Begin of SetList<double> Test:" << endl;

        testSetFloat(setlst1, loctestnum, loctesterr);
        InsertAllC(loctestnum, loctesterr, setlst1, true, lst);
        Empty(loctestnum, loctesterr, setlst1, false);
        Size(loctestnum, loctesterr, setlst1, true, 6);

        TraversePreOrder(loctestnum, loctesterr, setlst1, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, setlst1, true, &TraversePrint<double>);

        lasd::SetLst<double> setlst2;

        InsertC(loctestnum, loctesterr, setlst2, true, 2.1);
        InsertC(loctestnum, loctesterr, setlst2, true, 0.4);
        InsertC(loctestnum, loctesterr, setlst2, true, 1.2);
        InsertC(loctestnum, loctesterr, setlst2, true, 3.5);
        InsertC(loctestnum, loctesterr, setlst2, true, 5.3);
        InsertC(loctestnum, loctesterr, setlst2, true, 4.0);


        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);
        NonEqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);

        setlst1.Clear();
        setlst2.Clear();

        InsertC(loctestnum, loctesterr, setlst1, true, 0.2);
        InsertC(loctestnum, loctesterr, setlst1, true, 1.1);
        InsertC(loctestnum, loctesterr, setlst1, true, 2.1);

        InsertC(loctestnum, loctesterr, setlst2, true, 2.1);
        InsertC(loctestnum, loctesterr, setlst2, true, 1.1);
        InsertC(loctestnum, loctesterr, setlst2, true, 0.2);

        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);
        NonEqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);


        /* ********************************************************************** */

        EqualLinear(loctestnum, loctesterr, setvec1, setlst2, true);
        NonEqualLinear(loctestnum, loctesterr, setlst2, setvec2, false);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testSetString(lasd::Set<string> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {


        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);


        Empty(loctestnum, loctesterr, set, false);
        Size(loctestnum, loctesterr, set, true, 5);

        GetAt(loctestnum, loctesterr, set, true,  0, string("A"));
        GetBack(loctestnum, loctesterr, set, false, string("B"));
        GetFront(loctestnum, loctesterr, set, false, string("N"));

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Min(loctestnum, loctesterr, set, true,  string("A"));
        Max(loctestnum, loctesterr, set, true,  string("E"));

        RemoveMin(loctestnum, loctesterr, set, true);
        MinNRemove(loctestnum, loctesterr, set, true,  string("B"));

        InsertC(loctestnum, loctesterr, set, true,  string("A"));
        InsertC(loctestnum, loctesterr, set, true,  string("B"));

        Min(loctestnum, loctesterr, set, true,  string("A"));
        MaxNRemove(loctestnum, loctesterr, set, true, string("E"));
        Size(loctestnum, loctesterr, set, true,  4);

        InsertC(loctestnum, loctesterr, set, true,  string("Z"));
        Size(loctestnum, loctesterr, set, true,  5);
        Max(loctestnum, loctesterr, set, true,  string("Z"));

        InsertC(loctestnum, loctesterr, set, true,  string("Q"));
        Size(loctestnum, loctesterr, set, true,  6);


        Exists(loctestnum, loctesterr, set, true,  string("A"));
        Exists(loctestnum, loctesterr, set, false, string("N"));
        Exists(loctestnum, loctesterr, set, false, string("S"));
        Exists(loctestnum, loctesterr, set, true,  string("Z"));
        Exists(loctestnum, loctesterr, set, true,  string("Q"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Remove(loctestnum, loctesterr, set, false, string("c"));
        Remove(loctestnum, loctesterr, set, true,  string("D"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Exists(loctestnum, loctesterr, set, false, string("c"));
        Exists(loctestnum, loctesterr, set, false, string("D"));

        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, string("Q"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Predecessor(loctestnum, loctesterr, set, true, string("C"), string("B"));
        Predecessor(loctestnum, loctesterr, set, false, string("A"), string("B"));

        Successor(loctestnum, loctesterr, set, true, string("C"), string("Q"));
        Successor(loctestnum, loctesterr, set, false,  string("Q"), string("B"));

        SuccessorNRemove(loctestnum, loctesterr, set, true, string("C"), string("Q"));
        Min(loctestnum, loctesterr, set, true, string("A"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        PredecessorNRemove(loctestnum, loctesterr, set, true, string("Z"), string("C"));
        Max(loctestnum, loctesterr, set, true, string("B"));

        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("?"), string("?AB"));
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("?"), string("?BA"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        InsertM(loctestnum, loctesterr, set, true, move(string("Z")));
        InsertC(loctestnum, loctesterr, set, true, string("M"));
        InsertC(loctestnum, loctesterr, set, true, string("N"));
        InsertC(loctestnum, loctesterr, set, false, string("M"));

        RemovePredecessor(loctestnum, loctesterr, set, false, string("A"));
        RemovePredecessor(loctestnum, loctesterr, set, true, string("Z"));
        RemovePredecessor(loctestnum, loctesterr, set, true, string("M"));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        RemoveSuccessor(loctestnum, loctesterr, set, false, string("Z"));
        RemoveSuccessor(loctestnum, loctesterr, set, true, string("C"));


        Clear(loctestnum, loctesterr, set);
        Clear(loctestnum, loctesterr, set);

        InsertM(loctestnum, loctesterr, set, true, move(string("A")));
        InsertC(loctestnum, loctesterr, set, true, string("B"));
        InsertC(loctestnum, loctesterr, set, true, string("C"));
        InsertC(loctestnum, loctesterr, set, false, string("C"));

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        lasd::List<string> list;
        InsertAllC(loctestnum, loctesterr, set, true, list);

        list.InsertAtBack(string("C"));
        list.InsertAtFront(string("X"));
        list.InsertAtFront(string("V"));
        list.InsertAtFront(string("N"));
        list.InsertAtBack(string("L"));

        InsertAllC(loctestnum, loctesterr, set, false, list);
        lasd::List<string> list2;
        list2.InsertAtFront(string("J"));
        list2.InsertAtFront(string("K"));
        list2.InsertAtFront(string("O"));

        InsertAllM(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Remove(loctestnum, loctesterr, set, true, string("K"));
        Remove(loctestnum, loctesterr, set, true, string("L"));
        Remove(loctestnum, loctesterr, set, false, string("M"));

        RemoveAll(loctestnum, loctesterr, set, false, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);


        list2.Clear();
        list2.InsertAtFront(string("M"));
        list2.InsertAtFront(string("P"));

        InsertSomeC(loctestnum, loctesterr, set, true, list2);
        list2.InsertAtFront(string("D"));


        InsertSomeC(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        list.Front() = string("D");
        list.Back() = string("T");

        RemoveSome(loctestnum, loctesterr, set, true, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        Clear(loctestnum, loctesterr, set);

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);






    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testSetString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Set<string> Test" << endl;
    try {
        lasd::Vector<string> vec(5);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("E"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("B"));

        /* ********************************************************************** */

        cout << endl << "Begin of SetVec<string> Test:" << endl;
        lasd::SetVec<string> setvec(vec);
        testSetString(setvec, loctestnum, loctesterr);
        cout << endl << "Begin of SetLst<string> Test:" << endl;
        lasd::SetLst<string> setlst(vec);
        testSetString(setlst, loctestnum, loctesterr);
        cout << "\n";

        /* ********************************************************************** */

        EqualLinear(loctestnum, loctesterr, setvec, setlst, true);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of All Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


void testSet(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testSetInt(loctestnum, loctesterr);
    testSetFloat(loctestnum, loctesterr);
    testSetString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Set (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testHeapInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<int> Test:" << endl;
    try {
        //costruttore di default
        //test HeapVec vuoto
        lasd::HeapVec<int> heapEmpty;
        lasd::HeapVec<int> heapEmpty2;
        heapEmpty2 = heapEmpty;
        Traverse(loctestnum, loctesterr, heapEmpty, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, heapEmpty, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, heapEmpty, true, &TraversePrint<int>);


        IsHeap(loctestnum, loctesterr, heapEmpty, true);

        Size(loctestnum, loctesterr, heapEmpty, true, 0);
        Empty(loctestnum, loctesterr, heapEmpty, true);
        Clear(loctestnum, loctesterr, heapEmpty);


        Fold(loctestnum, loctesterr, heapEmpty, true, &FoldAdd<int>, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, heapEmpty, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, heapEmpty, true, &FoldAdd<int>, 0, 0);

        Map(loctestnum, loctesterr, heapEmpty, true, &MapParityInvert<int>);
        MapPostOrder(loctestnum, loctesterr, heapEmpty, true, &MapParityInvert<int>);
        MapPreOrder(loctestnum, loctesterr, heapEmpty, true, &MapParityInvert<int>);

        GetBack(loctestnum, loctesterr, heapEmpty, false, 2);
        GetFront(loctestnum, loctesterr, heapEmpty, false, 2);
        GetAt(loctestnum, loctesterr, heapEmpty, false, 2, 0);
        GetAt(loctestnum, loctesterr, heapEmpty, false, 0, 0);

        SetAt(loctestnum, loctesterr, heapEmpty, false, 2, 1);
        SetBack(loctestnum, loctesterr, heapEmpty, false, 2);
        SetFront(loctestnum, loctesterr, heapEmpty, false, 3);

        Exists(loctestnum, loctesterr, heapEmpty, false, 2);
        EqualLinear(loctestnum, loctesterr, heapEmpty, heapEmpty2, true);
        heapEmpty.Heapify();
        heapEmpty.Sort();


        lasd::Vector<int> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 4);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0);
        SetAt(loctestnum, loctesterr, vec, true, 4, 2);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8);
        SetAt(loctestnum, loctesterr, vec, true, 8, 11);
        SetAt(loctestnum, loctesterr, vec, true, 9, 20);
        SetAt(loctestnum, loctesterr, vec, true, 10, 7);
        SetAt(loctestnum, loctesterr, vec, true, 11, 3);
        SetAt(loctestnum, loctesterr, vec, true, 12, 9);
        SetAt(loctestnum, loctesterr, vec, true, 13, 6);

        //chiamata costruttore MappableContainer
        lasd::HeapVec<int> heap1(std::move(vec));
        EqualLinear(loctestnum, loctesterr, heap1, heapEmpty, false);
        //SetAt(loctestnum, loctesterr, heap1, true, 1, 3);
        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);

        SetAt(loctestnum, loctesterr, heap1, true, 1, 10);
        SetBack(loctestnum, loctesterr, heap1, true, 0);
        SetFront(loctestnum, loctesterr, heap1, true, 11);

        GetBack(loctestnum, loctesterr, heap1, true, 0);
        GetFront(loctestnum, loctesterr, heap1, true, 11);
        GetAt(loctestnum, loctesterr, heap1, true, 2, 9);
        heap1.Heapify();


        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);


        IsHeap(loctestnum, loctesterr, heap1, true);

        SetAt(loctestnum, loctesterr, vec, true, 0, 11);
        SetAt(loctestnum, loctesterr, vec, true, 1, 10);
        SetAt(loctestnum, loctesterr, vec, true, 2, 9);
        SetAt(loctestnum, loctesterr, vec, true, 3, 8);
        SetAt(loctestnum, loctesterr, vec, true, 4, 7);
        SetAt(loctestnum, loctesterr, vec, true, 5, 6);
        SetAt(loctestnum, loctesterr, vec, true, 6, 5);
        SetAt(loctestnum, loctesterr, vec, true, 7, 4);
        SetAt(loctestnum, loctesterr, vec, true, 8, 3);
        SetAt(loctestnum, loctesterr, vec, true, 9, 3);
        SetAt(loctestnum, loctesterr, vec, true, 10, 2);
        SetAt(loctestnum, loctesterr, vec, true, 11, 1);
        SetAt(loctestnum, loctesterr, vec, true, 12, 0);
        SetAt(loctestnum, loctesterr, vec, true, 13, 0);

        //chiamata costruttore TraversableContainer
        lasd::HeapVec<int> heap2(vec);

        IsHeap(loctestnum, loctesterr, heap2, true);
        Traverse(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        EqualLinear(loctestnum, loctesterr, heap1, heap2, false);

        heap1.Sort();

        IsHeap(loctestnum, loctesterr, heap1, false);
        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);

        EqualLinear(loctestnum, loctesterr, heap1, heap2, false);

        //chiamata costruttore Copy
        lasd::HeapVec<int> heap3(heap2);

        EqualLinear(loctestnum, loctesterr, heap2, heap3, true);

        Empty(loctestnum, loctesterr, heap3, false);
        Size(loctestnum, loctesterr, heap3, true, 14);

        //chiamata costruttore Move
        lasd::HeapVec<int> heap4(std::move(heap3));

        EqualLinear(loctestnum, loctesterr, heap2, heap3, false);
        EqualLinear(loctestnum, loctesterr, heap2, heap4, true);

        Empty(loctestnum, loctesterr, heap3, true);
        Size(loctestnum, loctesterr, heap3, true, 0);

        Empty(loctestnum, loctesterr, heap4, false);
        Size(loctestnum, loctesterr, heap4, true, 14);

        heap2.Sort();

        EqualLinear(loctestnum, loctesterr, heap2, heap4, false);
        EqualLinear(loctestnum, loctesterr, heap1, heap2, true);
        //copy assigment
        heap3 = heap4;

        EqualLinear(loctestnum, loctesterr, heap2, heap3, false);
        EqualLinear(loctestnum, loctesterr, heap3, heap4, true);

        //move assigment
        heap3 = std::move(heap2);

        EqualLinear(loctestnum, loctesterr, heap2, heap3, false);
        EqualLinear(loctestnum, loctesterr, heap2, heap4, true);
        EqualLinear(loctestnum, loctesterr, heap3, heap4, false);

        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, 69);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, 69);

        MapPreOrder(loctestnum, loctesterr, heap2, true, &MapInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        IsHeap(loctestnum, loctesterr, heap2, false);

        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -69);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -69);

        MapPostOrder(loctestnum, loctesterr, heap2, true, &MapInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        MapPostOrder(loctestnum, loctesterr, heap2, true, &MapParityInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        heap2.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -9);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -9);

        MapPreOrder(loctestnum, loctesterr, heap2, true, &MapParityInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        heap2.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        EqualLinear(loctestnum, loctesterr, heap1, heap2, false);

        heap2.Sort();

        EqualLinear(loctestnum, loctesterr, heap1, heap2, true);

        IsHeap(loctestnum, loctesterr, heap3, false);

        heap3.Heapify();

        IsHeap(loctestnum, loctesterr, heap3, true);

        heap3.Sort();
        TraversePreOrder(loctestnum, loctesterr, heap3, true, &TraversePrint<int>);
        cout << heap3[1] << endl;
        heap3[1] = 2;
        TraversePreOrder(loctestnum, loctesterr, heap3, true, &TraversePrint<int>);

        IsHeap(loctestnum, loctesterr, heap3, false);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Heap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testHeapDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<double> Test:" << endl;
    try {

        lasd::Vector<double> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 4.5);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3.25);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1.125);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0.0);
        SetAt(loctestnum, loctesterr, vec, true, 4, 2.25);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5.5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0.0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8.25);
        SetAt(loctestnum, loctesterr, vec, true, 8, 11.5);
        SetAt(loctestnum, loctesterr, vec, true, 9, 20.5);
        SetAt(loctestnum, loctesterr, vec, true, 10, 7.25);
        SetAt(loctestnum, loctesterr, vec, true, 11, 3.125);
        SetAt(loctestnum, loctesterr, vec, true, 12, 9.5);
        SetAt(loctestnum, loctesterr, vec, true, 13, 6.25);

        lasd::HeapVec<double> heap(vec);

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);

        SetAt(loctestnum, loctesterr, heap, true, 1, 10.5);
        SetBack(loctestnum, loctesterr, heap, true, 0.0);
        SetFront(loctestnum, loctesterr, heap, true, 11.5);

        GetBack(loctestnum, loctesterr, heap, true, 0.0);
        GetFront(loctestnum, loctesterr, heap, true, 11.5);
        GetAt(loctestnum, loctesterr, heap, true, 2, 9.5);
        heap.Sort();

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        IsHeap(loctestnum, loctesterr, heap, false);

        heap.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        IsHeap(loctestnum, loctesterr, heap, true);
        lasd::HeapVec<double> heap2(heap);
        EqualLinear(loctestnum, loctesterr, heap, heap2, true);
        Empty(loctestnum, loctesterr, heap, false);
        Size(loctestnum, loctesterr, heap, true, 14);

        Fold(loctestnum, loctesterr, heap2, true, &FoldAdd<double>, 0, 69);
        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<double>, 0, 69);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<double>, 0, 69);

        Map(loctestnum, loctesterr, heap2, true, &MapIncrement<double>);
        MapPostOrder(loctestnum, loctesterr, heap2, true, &MapIncrement<double>);
        MapPreOrder(loctestnum, loctesterr, heap2, true, &MapIncrement<double>);
        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        heap.Clear();
        //Clear(loctestnum, loctesterr, heap2);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Heap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testHeapString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<string> Test:" << endl;
    try {

        lasd::Vector<string> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("E"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 5, string("F"));
        SetAt(loctestnum, loctesterr, vec, true, 6, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 7, string("I"));
        SetAt(loctestnum, loctesterr, vec, true, 8, string("K"));
        SetAt(loctestnum, loctesterr, vec, true, 9, string("L"));
        SetAt(loctestnum, loctesterr, vec, true, 10, string("H"));
        SetAt(loctestnum, loctesterr, vec, true, 11, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 12, string("J"));
        SetAt(loctestnum, loctesterr, vec, true, 13, string("G"));

        lasd::HeapVec<string> heap(vec);

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        MapPreOrder(loctestnum, loctesterr, heap, true, [](string & str) {
            MapStringAppend(str, string("*"));
        });
        MapPreOrder(loctestnum, loctesterr, heap, true, [](string & str) {
            MapStringAppend(str, string(" "));
        });

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?A* B* D* D* C* A* E* G* F* H* I* J* K* L* "));
        FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?L* K* J* I* H* F* G* E* A* C* D* D* B* A* "));
        IsHeap(loctestnum, loctesterr, heap, true);

        heap.Sort();
        IsHeap(loctestnum, loctesterr, heap, false);

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?L* K* J* I* H* G* F* E* D* D* C* B* A* A* "));
        FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?A* A* B* C* D* D* E* F* G* H* I* J* K* L* "));

        heap.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?B* D* A* D* A* C* F* E* J* H* G* K* I* L* "));
        FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?L* I* K* G* H* J* E* F* C* A* D* A* D* B* "));

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Heap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void testPQInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<int> Test:" << endl;
    try {
        //Pq vuota
        lasd::PQHeap<int> pqEmpty;
        lasd::PQHeap<int> pqEmpty1;

        pqEmpty1 = pqEmpty1;
        Traverse(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);

        Size(loctestnum, loctesterr, pqEmpty1, true, 0);
        Empty(loctestnum, loctesterr, pqEmpty1, true);
        Clear(loctestnum, loctesterr, pqEmpty1);


        Fold(loctestnum, loctesterr, pqEmpty1, true, &FoldAdd<int>, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, pqEmpty1, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, pqEmpty1, true, &FoldAdd<int>, 0, 0);


        GetBack(loctestnum, loctesterr, pqEmpty1, false, 2);
        GetFront(loctestnum, loctesterr, pqEmpty1, false, 2);
        GetAt(loctestnum, loctesterr, pqEmpty1, false, 2, 0);
        GetAt(loctestnum, loctesterr, pqEmpty1, false, 0, 0);


        Exists(loctestnum, loctesterr, pqEmpty1, false, 2);
        EqualLinear(loctestnum, loctesterr, pqEmpty1, pqEmpty, true);
        Tip(loctestnum, loctesterr, pqEmpty, false, 10);
        RemoveTip(loctestnum, loctesterr, pqEmpty, false);
        TipNRemove(loctestnum, loctesterr, pqEmpty, false, 9);

        Insert(loctestnum, loctesterr, pqEmpty, 5);
        Insert(loctestnum, loctesterr, pqEmpty, std::move(6));
        Change(loctestnum, loctesterr, pqEmpty, false, 10, 7);
        Change(loctestnum, loctesterr, pqEmpty, true, 0, std::move(8));


        Traverse(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);

        lasd::Vector<int> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 4);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0);
        SetAt(loctestnum, loctesterr, vec, true, 4, 2);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8);
        SetAt(loctestnum, loctesterr, vec, true, 8, 10);
        SetAt(loctestnum, loctesterr, vec, true, 9, 11);
        SetAt(loctestnum, loctesterr, vec, true, 10, 7);
        SetAt(loctestnum, loctesterr, vec, true, 11, 3);
        SetAt(loctestnum, loctesterr, vec, true, 12, 9);
        SetAt(loctestnum, loctesterr, vec, true, 13, 6);

        lasd::PQHeap<int> pq(vec);
        lasd::PQHeap<int> pq22(std::move(vec));
        Insert(loctestnum, loctesterr, pq22, 6);
        Insert(loctestnum, loctesterr, pq22, 5);
        Insert(loctestnum, loctesterr, pq22, 4);
        Insert(loctestnum, loctesterr, pq22, 3);
        Insert(loctestnum, loctesterr, pq22, 2);
        Insert(loctestnum, loctesterr, pq22, 1);
        Insert(loctestnum, loctesterr, pq22, 0);


        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Tip(loctestnum, loctesterr, pq, true, 11);
        RemoveTip(loctestnum, loctesterr, pq, true);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Tip(loctestnum, loctesterr, pq, true, 10);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 9);
        TipNRemove(loctestnum, loctesterr, pq, true, 8);
        TipNRemove(loctestnum, loctesterr, pq, true, 7);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 5);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        cout << pq22[1] << endl;
        Tip(loctestnum, loctesterr, pq, true, 6);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        RemoveTip(loctestnum, loctesterr, pq, true);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq, true, 5);
        TipNRemove(loctestnum, loctesterr, pq, true, 5);
        TipNRemove(loctestnum, loctesterr, pq, true, 4);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 3);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq, true, 3);
        TipNRemove(loctestnum, loctesterr, pq, true, 3);
        TipNRemove(loctestnum, loctesterr, pq, true, 3);
        Tip(loctestnum, loctesterr, pq, true, 2);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 1);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 10);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq, true, 10);
        TipNRemove(loctestnum, loctesterr, pq, true, 0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 8);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Exists(loctestnum, loctesterr, pq, true, 8);
        Exists(loctestnum, loctesterr, pq, false, 12);

        GetAt(loctestnum, loctesterr, pq, true, 0, 8);

        TipNRemove(loctestnum, loctesterr, pq, true, 8);
        TipNRemove(loctestnum, loctesterr, pq, true, 0);
        RemoveTip(loctestnum, loctesterr, pq, false);

        Insert(loctestnum, loctesterr, pq, 7);
        Insert(loctestnum, loctesterr, pq, 6);
        Insert(loctestnum, loctesterr, pq, 5);
        Insert(loctestnum, loctesterr, pq, 4);
        Insert(loctestnum, loctesterr, pq, 3);
        Insert(loctestnum, loctesterr, pq, 2);
        Insert(loctestnum, loctesterr, pq, 1);
        Insert(loctestnum, loctesterr, pq, 0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Change(loctestnum, loctesterr, pq,  true,  0, 8);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 1);
        Insert(loctestnum, loctesterr, pq, 0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Change(loctestnum, loctesterr, pq,  true,  1, 2);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Change(loctestnum, loctesterr, pq,  true,  6, 6);

        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        ChangePQM(loctestnum, loctesterr, pq, 8, 10);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Fold(loctestnum, loctesterr, pq, true, &FoldAdd<int>, 0, 40);
        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldAdd<int>, 0, 40);
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldAdd<int>, 0, 40);

        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 10);

        lasd::PQHeap<int> pq1(std::move(pq));

        Empty(loctestnum, loctesterr, pq, true);
        Size(loctestnum, loctesterr, pq, true, 0);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        TipNRemove(loctestnum, loctesterr, pq1, true, 10);
        TipNRemove(loctestnum, loctesterr, pq1, true, 8);
        Insert(loctestnum, loctesterr, pq1, 11);
        TipNRemove(loctestnum, loctesterr, pq1, true, 11);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);

        pq = pq1;

        EqualLinear(loctestnum, loctesterr, pq, pq1, true);

        lasd::PQHeap<int> pq2(pq);

        EqualLinear(loctestnum, loctesterr, pq1, pq2, true);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 6);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        Change(loctestnum, loctesterr, pq2,  true,  0, -1);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 4);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);
        try {
            pq1.Change(100, 12);
        } catch(std::exception & exc)  {
            std::cout << exc.what() << "\": "  << "!" << std::endl;
        }
        pq2 = std::move(pq1);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 6);
        pq1.Clear();
        Empty(loctestnum, loctesterr, pq2, false);
        Size(loctestnum, loctesterr, pq2, true, 8);
        Clear(loctestnum, loctesterr, pq2);
        try {
            pq2.Change(100, 12);
        } catch(std::exception & exc)  {
            std::cout << exc.what() << "\": "  << "!" << std::endl;
        }
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQ<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testPQDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<double> Test:" << endl;
    try {

        lasd::Vector<double> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 4.0);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3.2);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1.5);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0.4);
        SetAt(loctestnum, loctesterr, vec, true, 4, 2.6);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5.8);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0.9);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8.3);
        SetAt(loctestnum, loctesterr, vec, true, 8, 10.12);
        SetAt(loctestnum, loctesterr, vec, true, 9, 11.45);
        SetAt(loctestnum, loctesterr, vec, true, 10, 7.26);
        SetAt(loctestnum, loctesterr, vec, true, 11, 3.65);
        SetAt(loctestnum, loctesterr, vec, true, 12, 9.1);
        SetAt(loctestnum, loctesterr, vec, true, 13, 6.37);

        lasd::PQHeap<double> pq(vec);
        lasd::PQHeap<double> pq22(std::move(vec));

        Insert(loctestnum, loctesterr, pq22, 6.3);
        Insert(loctestnum, loctesterr, pq22, 5.4);
        Insert(loctestnum, loctesterr, pq22, 4.20);
        Insert(loctestnum, loctesterr, pq22, 3.18);
        Insert(loctestnum, loctesterr, pq22, 2.9);
        Insert(loctestnum, loctesterr, pq22, 1.18);
        Insert(loctestnum, loctesterr, pq22, 0.23);


        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Tip(loctestnum, loctesterr, pq, true, 11.45);
        RemoveTip(loctestnum, loctesterr, pq, true);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Tip(loctestnum, loctesterr, pq, true, 10.12);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 9.1);
        TipNRemove(loctestnum, loctesterr, pq, true, 8.3);
        TipNRemove(loctestnum, loctesterr, pq, true, 7.26);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 5.27);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        Tip(loctestnum, loctesterr, pq, true, 6.37);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        RemoveTip(loctestnum, loctesterr, pq, true);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq, true, 5.8);
        TipNRemove(loctestnum, loctesterr, pq, true, 5.27);
        TipNRemove(loctestnum, loctesterr, pq, true, 4.0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 3.6);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq, true, 3.65);
        TipNRemove(loctestnum, loctesterr, pq, true, 3.6);
        TipNRemove(loctestnum, loctesterr, pq, true, 3.2);
        Tip(loctestnum, loctesterr, pq, true, 2.6);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 1.5);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 10.6);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq, true, 10.6);
        TipNRemove(loctestnum, loctesterr, pq, true, 0.9);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 8.4);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Exists(loctestnum, loctesterr, pq, true, 8.4);
        Exists(loctestnum, loctesterr, pq, false, 12.104);

        GetAt(loctestnum, loctesterr, pq, true, 0, 8.4);

        TipNRemove(loctestnum, loctesterr, pq, true, 8.4);
        TipNRemove(loctestnum, loctesterr, pq, true, 0.4);
        RemoveTip(loctestnum, loctesterr, pq, false);

        Insert(loctestnum, loctesterr, pq, 7.0);
        Insert(loctestnum, loctesterr, pq, 6.9);
        Insert(loctestnum, loctesterr, pq, 5.0);
        Insert(loctestnum, loctesterr, pq, 4.1);
        Insert(loctestnum, loctesterr, pq, 3.2);
        Insert(loctestnum, loctesterr, pq, 2.5);
        Insert(loctestnum, loctesterr, pq, 1.0);
        Insert(loctestnum, loctesterr, pq, 0.1);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Change(loctestnum, loctesterr, pq, true,  0, 0.2);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 1.3);
        Insert(loctestnum, loctesterr, pq, 0.9);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Change(loctestnum, loctesterr, pq, true, 1, 2.4);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        ChangePQM(loctestnum, loctesterr, pq, 6, 6.90);

        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Change(loctestnum, loctesterr, pq, true, 8, std::move(10.0));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, pq, true, &FoldAdd<double>, 0, 35);
        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldAdd<double>, 0, 35);
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldAdd<double>, 0, 35);

        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 10);

        lasd::PQHeap<double> pq1(std::move(pq));

        Empty(loctestnum, loctesterr, pq, true);
        Size(loctestnum, loctesterr, pq, true, 0);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        TipNRemove(loctestnum, loctesterr, pq1, true, 10.0);
        TipNRemove(loctestnum, loctesterr, pq1, true, 6.9);
        Insert(loctestnum, loctesterr, pq1, 11.0);
        TipNRemove(loctestnum, loctesterr, pq1, true, 11.0);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);

        pq = pq1;

        EqualLinear(loctestnum, loctesterr, pq, pq1, true);

        lasd::PQHeap<double> pq2(pq);

        EqualLinear(loctestnum, loctesterr, pq1, pq2, true);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 6.9);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);

        ChangePQM(loctestnum, loctesterr, pq2, 0, -1.0);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 3.2);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);

        pq2 = std::move(pq1);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 6);
        pq1.Clear();
        Empty(loctestnum, loctesterr, pq2, false);
        Size(loctestnum, loctesterr, pq2, true, 8);
        Clear(loctestnum, loctesterr, pq2);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQ<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testPQString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<string> Test:" << endl;
    try {

        lasd::Vector<string> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("E"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 5, string("F"));
        SetAt(loctestnum, loctesterr, vec, true, 6, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 7, string("I"));
        SetAt(loctestnum, loctesterr, vec, true, 8, string("K"));
        SetAt(loctestnum, loctesterr, vec, true, 9, string("L"));
        SetAt(loctestnum, loctesterr, vec, true, 10, string("H"));
        SetAt(loctestnum, loctesterr, vec, true, 11, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 12, string("J"));
        SetAt(loctestnum, loctesterr, vec, true, 13, string("G"));

        lasd::PQHeap<string> pq(vec);
        lasd::PQHeap<string> pq22(std::move(vec));
        InsertPQM(loctestnum, loctesterr, pq22, string("a"));
        InsertPQM(loctestnum, loctesterr, pq22, string("b"));
        InsertPQM(loctestnum, loctesterr, pq22, string("c"));
        InsertPQM(loctestnum, loctesterr, pq22, string("d"));
        InsertPQM(loctestnum, loctesterr, pq22, string("e"));
        InsertPQM(loctestnum, loctesterr, pq22, string("f"));
        InsertPQM(loctestnum, loctesterr, pq22, string("g"));

        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?LKJIHFGEACDDBA"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?ABDDCAEGFHIJKL"));

        Tip(loctestnum, loctesterr, pq, true, string("L"));
        RemoveTip(loctestnum, loctesterr, pq, true);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        Tip(loctestnum, loctesterr, pq, true, string("K"));
        RemoveTip(loctestnum, loctesterr, pq, true);
        Insert(loctestnum, loctesterr, pq, string("J"));
        Insert(loctestnum, loctesterr, pq, string("K"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("K"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("J"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("J"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?IHGEDFBAACD"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?DCAABFDEGHI"));

        Insert(loctestnum, loctesterr, pq, string("F"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?IHGEDFBAACDF"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?FDCAABFDEGHI"));

        Change(loctestnum, loctesterr, pq, true, 4, string("X"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?XIGEHFBAACDF"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?FDCAABFHEGIX"));

        Change(loctestnum, loctesterr, pq, true, 1, string("A"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?XHGEDFBAACAF"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?FACAABFDEGHX"));

        ChangePQM(loctestnum, loctesterr, pq, 2, string("B"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?XHFEDFBAACAB"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?BACAABFDEFHX"));

        Exists(loctestnum, loctesterr, pq, true, string("B"));
        Exists(loctestnum, loctesterr, pq, false, string("N"));

        GetAt(loctestnum, loctesterr, pq, true, 0, string("X"));

        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 12);

        lasd::PQHeap<string> pq1(std::move(pq));

        Empty(loctestnum, loctesterr, pq, true);
        Size(loctestnum, loctesterr, pq, true, 0);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 12);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        TipNRemove(loctestnum, loctesterr, pq1, true, string("X"));
        TipNRemove(loctestnum, loctesterr, pq1, true, string("H"));
        Insert(loctestnum, loctesterr, pq1, string("B"));
        TipNRemove(loctestnum, loctesterr, pq1, true, string("F"));

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        pq = pq1;

        EqualLinear(loctestnum, loctesterr, pq, pq1, true);

        lasd::PQHeap<string> pq2(pq);

        EqualLinear(loctestnum, loctesterr, pq1, pq2, true);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);

        TipNRemove(loctestnum, loctesterr, pq2, true, string("F"));

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);

        Change(loctestnum, loctesterr, pq2, true, 0, string("B"));

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);

        TipNRemove(loctestnum, loctesterr, pq2, true, string("D"));

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        pq2 = std::move(pq1);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);
        pq1.Clear();
        Empty(loctestnum, loctesterr, pq2, false);
        Size(loctestnum, loctesterr, pq2, true, 10);
        Clear(loctestnum, loctesterr, pq2);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQ<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void testHeapAdd() {
    SortableVector<int> v(12);
    int arr[] {8, 6, 20, 6, 3, 88, 10, 1, 0, -10, -4, -5};
    for(ulong index = 0; index < v.Size(); index++) {
        v[index] = arr[index];

    }
    HeapVec<int> heap(v);
    heap.PreOrderTraverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;

    cout << " dovrebbe essere un heap è " << (heap.IsHeap() ? "un heap" : "mannaggia non un heap") << endl;
    HeapVec<int> heap2(heap);
    cout << "Test equal" << (heap == heap2 ? "heap == heap2" : "heap != heap2") << endl;
    cout << "Test not equal" << (heap != heap2 ? "heap != heap2" : "heap == heap2") << endl;
    HeapVec<int> heap3;
    cout << (heap == heap3 ? "heap == heap3" : "heap != heap3") << endl;
    cout << "Test not equal" << (heap != heap3 ? "heap != heap3" : "heap == heap3") << endl;

    //costanti
    cout << "Front: " << heap.Front() << " heap[0]: " << heap[0] << endl;
    cout << "Back: " << heap.Back() << " heap[size-1]: " << heap[heap.Size() - 1] << endl;

    //mutable
    heap.Front() = 10;
    cout << "Mutable Front: " << heap.Front() << " heap[0]: " << heap[0] << endl;
    heap.Back() = 12;
    cout << "Mutable Back: " << heap.Front() << " heap[size-1]: " << heap[heap.Size() - 1] << endl;
    heap[2] = 111;
    cout << " heap[2]: " << heap[2] << endl;
    cout << "Post order travers:" << endl;
    heap.PostOrderTraverse([](const int & x) {
        cout << x << " ";
    });
    cout << "Heapify" << endl;
    heap.Heapify();
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;
    bool chk = heap.Empty();
    cout << (chk ? "Is empty" : "Is not empt") << endl;
    bool chk1 = heap.Exists(2000);
    cout << (chk1 ? "2000 exist" : "2000 not exist") << endl;
    bool chk2 = heap.Exists(111);
    cout << (chk2 ? "111 exist" : "111 not exist") << endl;

    int sumFold =  heap.Fold<int>([](const int &x, const int &acc)->int {
        return acc + x;
    }, 0);
    cout << "Fold Sum:" << sumFold << endl;

    int sumFold1 =  heap.PreOrderFold<int>([](const int &x, const int &acc)->int {
        return acc + x;
    }, 0);
    cout << "Fold Sum:" << sumFold1 << endl;
    int sumFold2 =  heap.PostOrderFold<int>([](const int &x, const int &acc)->int {
        return acc + x;
    }, 0);
    cout << "Fold Sum:" << sumFold2 << endl;
    cout << "Testing Map" << endl;
    heap.PreOrderMap([](int& x) {
        x *= 2;
    });
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;
    heap.PostOrderMap([](int& x) {
        x *= 2;
    });
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;
    heap.Map([](int& x) {
        x *= 2;
    });
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;
    cout << "Testing sort" << endl;
    heap.Sort();
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;
    cout << "Testing Clear" << endl;
    heap.Clear();
    cout << (heap.Empty() ? "Is empty" : "Is not empt") << endl;
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
}



void testPQAdd() {
    SortableVector<int> v(12);
    int arr[] {8, 6, 20, 6, 3, 88, 10, 1, 0, -10, -4, -5};
    for(ulong index = 0; index < v.Size(); index++) {
        v[index] = arr[index];

    }
    PQHeap<int> heap(v);
    heap.PreOrderTraverse([](const int & x) {
        cout << x << " ";
    });
    cout << endl;
    PQHeap<int> heap2(heap);
    cout << "Test equal " << (heap == heap2 ? "pqheap == pqheap2" : "pqheap != pqheap2") << endl;
    cout << "Test not equal " << (heap != heap2 ? "pqheap != pqheap2" : "pqheap == pqheap2") << endl;
    PQHeap<int> heap3;
    cout << (heap == heap3 ? "pqheap == pqheap3" : "pqheap != pqheap3") << endl;
    cout << "Test not equal " << (heap != heap3 ? "pqheap != pqheap3" : "pqheap == pqheap3") << endl;

    //costanti
    cout << "Front: " << heap.Front() << " pqheap[0]: " << heap[0] << endl;
    cout << "Back: " << heap.Back() << " pqheap[size-1]: " << heap[heap.Size() - 1] << endl;



    cout << "Post order travers:" << endl;
    heap.PostOrderTraverse([](const int & x) {
        cout << x << " ";
    });


    cout << endl;
    bool chk = heap.Empty();
    cout << (chk ? "Is empty" : "Is not empt") << endl;
    bool chk1 = heap.Exists(2000);
    cout << (chk1 ? "2000 exist" : "2000 not exist") << endl;
    bool chk2 = heap.Exists(111);
    cout << (chk2 ? "111 exist" : "111 not exist") << endl;

    int sumFold =  heap.Fold<int>([](const int &x, const int &acc)->int {
        return acc + x;
    }, 0);
    cout << "Fold Sum:" << sumFold << endl;

    int sumFold1 =  heap.PreOrderFold<int>([](const int &x, const int &acc)->int {
        return acc + x;
    }, 0);
    cout << "Fold Sum:" << sumFold1 << endl;
    int sumFold2 =  heap.PostOrderFold<int>([](const int &x, const int &acc)->int {
        return acc + x;
    }, 0);
    cout << "Fold Sum:" << sumFold2 << endl;


    cout << "Testing Clear" << endl;
    heap.Clear();
    cout << (heap.Empty() ? "Is empty" : "Is not empt") << endl;
    heap.Traverse([](const int & x) {
        cout << x << " ";
    });
}


void testHeap(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testHeapInt(loctestnum, loctesterr);
    testHeapDouble(loctestnum, loctesterr);
    testHeapString(loctestnum, loctesterr);

    testHeapAdd();
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Heap (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testPQ(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testPQInt(testnum, testerr);
    testPQDouble(testnum, testerr);
    testPQString(testnum, testerr);
    testPQAdd();
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Priority Queue (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testEx1(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testVector(loctestnum, loctesterr);
    testList(loctestnum, loctesterr);
    testSet(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Exercise 1 (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testEx2(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testPQ(loctestnum, loctesterr);
    testHeap(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Exercise 2 (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void mytest() {
    cout << endl << "Welcome to the testing section of MyTest()" << endl;
    bool running = true;
    uint testnum = 0;
    uint testerr = 0;
    while(running) {
        cout << "\nSelect which tests to run:\n"
             << "  1) vector\n"
             << "  2) list\n"
             << "  3) set\n"
             << "  4) Exercise 1: vector, list and set\n"
             << "  5) heap\n"
             << "  6) priority_queue\n"
             << "  7) Exercise 2: heap and priority_queue \n"
             << "  8) Exercise 1 and Exercise 2\n"
             << "  q) return to main\n"
             << "Enter your choice: ";

        char choice;
        cin >> choice;
        if(choice == 'q' || choice == 'Q') {
            running = false;
            break;
        }
        cout << "\n--- Running tests for choice [" << choice << "] ---\n";
        switch(choice) {
        case '1': {
            testVector(testnum, testnum);
            cout << "Total -  (Errors/Tests: " << testnum << "/" << testerr << ")\n";

            break;
        }
        case '2': {
            testList(testnum, testerr);
            cout << endl << "Total - (Errors/Tests: " << testnum << "/" << testerr << ")\n";
            break;
        }
        case '3': {
            testSet(testnum, testnum);
            cout << "Total -  (Errors/Tests: " << testnum << "/" << testerr << ")\n";
            break;
        }
        case '4': {
            testEx1(testnum, testnum);
            cout << "Total -  (Errors/Tests: " << testnum << "/" << testerr << ")\n";
            break;
        }
        case '5': {
            testHeap(testnum, testnum);
            cout << "Total -  (Errors/Tests: " << testnum << "/" << testerr << ")\n";
            break;
        }
        case '6': {
            testPQ(testnum, testnum);
            cout << "Total -  (Errors/Tests: " << testnum << "/" << testerr << ")\n";
            break;
        }
        case '7': {
            testEx2(testnum, testnum);
            cout << "Total -  (Errors/Tests: " << testnum << "/" << testerr << ")\n";
            break;
        }
        case '8': {
            uint loctestnum = 0;
            uint loctesterr = 0;
            testEx1(loctestnum, loctesterr);
            testEx2(loctestnum, loctesterr);
            testnum += loctestnum;
            testerr += loctesterr;
            cout << endl << "Exercise - Exercise 1 and Exercise 2 (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
            cout << "Total -  (Errors/Tests: " <<testerr  << "/" << testnum << ")\n"; 
            break;
        }
        default:
            cout << "Invalid input. Please try again.\n";
        }

    }
  

}
}