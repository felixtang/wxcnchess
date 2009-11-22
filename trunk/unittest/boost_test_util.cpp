
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "tree.hh"

using namespace std;


BOOST_AUTO_TEST_CASE( SIZE_Test )
{
    printf("sizeof char = %d\n",sizeof(char));
    printf("sizeof int = %d\n",sizeof(int));
    printf("sizeof size_t = %d\n",sizeof(size_t));
    printf("sizeof short = %d\n",sizeof(short));

    printf("12 & 4 = %d\n",(unsigned char)(12 & 4));
    printf("12 & 8 = %d\n",(unsigned char)(12 & 8));
    printf("12 & 2 = %d\n",(unsigned char)(12 & 2));
//    printf("sizeof BYTE = %d\n",sizeof(byte));
}


BOOST_AUTO_TEST_CASE( SIZE_Tree )
{
    tree<string> tr;
    tree<string>::iterator top, one, two, loc, banana;

    top=tr.begin();
    one=tr.insert(top, "one");
    two=tr.append_child(one, "two");
    tr.append_child(two, "apple");
    banana=tr.append_child(two, "banana");
    tr.append_child(banana,"cherry");
    tr.append_child(two, "peach");
    tr.append_child(one,"three");

    //loc=find(tr.begin(), tr.end(), "one");
	loc=tr.begin();
    if (loc!=tr.end())
    {
        tree<string>::sibling_iterator sib=tr.begin(loc);
        while (sib!=tr.end(loc))
        {
            cout << (*sib) << endl;
            ++sib;
        }
        cout << endl;
        tree<string>::iterator sib2=tr.begin(loc);
        tree<string>::iterator end2=tr.end(loc);
        while (sib2!=end2)
        {
            for (int i=0; i<tr.depth(sib2)/*-2*/; ++i)
                cout << " ";
            cout << (*sib2) << endl;
            ++sib2;
        }
    }

}


