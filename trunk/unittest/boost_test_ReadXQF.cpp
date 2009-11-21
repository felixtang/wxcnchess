#include <iostream>
#include <boost/test/unit_test.hpp>
#include <vector>

#include "wxXQFReader.h"

using namespace std;

BOOST_AUTO_TEST_CASE( Read_Sample_XQF )
{
    wxCnChess::wxXQFReader reader;
    wxCnChess::wxCnChessGame Game;
    reader.ReadGame( Game, "./unittest/Sample.XQF");
}


