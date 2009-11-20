#include <iostream>
#include <boost/test/unit_test.hpp>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <vector>

using namespace std;


BOOST_AUTO_TEST_CASE( SIZE_Test2 )
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


