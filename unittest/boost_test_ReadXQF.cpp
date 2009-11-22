#define BOOST_AUTO_TEST_MAIN

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <vector>
#include <algorithm>

#include "wxXQFReader.h"

using namespace std;

void outByteString( BYTE b )
{
	printf("%x ",b );
}


BOOST_AUTO_TEST_CASE( Read_Sample_XQF )
{
    wxCnChess::wxXQFReader reader;
    wxCnChess::wxCnChessGame Game;
    std::cout << "Read XQF " << std::endl;
    if ( false == reader.ReadGame( &Game, "./unittest/Sample.XQF") )
    {
        std::cout << "Read XQF fail: " << reader.GetLastError() << std::endl;
    }
	
	BYTE* buf = reader.GetHeaderBuff();
	BYTE WholeOpen[] =  {	
		0x50, 0x46, 0x3C, 0x32, 0x28, 0x1E, 0x14, 0x0A, /**/ 0x00, 0x48, 0x0C, 0x53, 0x3F, 0x2B, 0x17, 0x03,
		0x09, 0x13, 0x1D, 0x27, 0x31, 0x3B, 0x45, 0x4F, /**/ 0x59, 0x11, 0x4D, 0x06, 0x1A, 0x2E, 0x42, 0x56
	}; 

	std::vector< BYTE > strWholeOpen( WholeOpen, WholeOpen + 0x20 );
	std::vector< BYTE > strOpenBuff( buf + 0x10, buf + 0x30 );

	std::for_each( strWholeOpen.begin(),strWholeOpen.end(),outByteString );
	std::cout << std::endl;
	std::for_each( strOpenBuff.begin(), strOpenBuff.end(), outByteString );
	std::cout << std::endl;

	BOOST_CHECK( strWholeOpen == strOpenBuff );

	std::string strName = reader.ReadString( buf + 0xD0  );
	std::cout << "strName: " << strName << std::endl;
}


