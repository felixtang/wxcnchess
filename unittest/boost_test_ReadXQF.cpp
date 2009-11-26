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

void DumpGameTree(wxCnChess::GameTree_t& tree)
{
    std::cout << "DumpGameTree" << std::endl;
    wxCnChess::GameTree_t::pre_order_iterator iEnd = tree.end();
    for(wxCnChess::GameTree_t::pre_order_iterator iter = tree.begin(); iter != iEnd; ++iter)
    {
        if(iter == tree.begin())
            continue;

        wxCnChess::GameTree_t::iterator parent = wxCnChess::GameTree_t::parent(iter);
        wxCnChess::GameNode* nodeParent = 0;

        std::string strNode;

        if( parent.node != 0)
            strNode = iter->toString( &(*parent) );
        else
            strNode = iter->toString( 0 );

//        std::string strParent;
//
//        if( parent.node != 0)
//            strParent = parent->toString( *tree.begin() );
//
        for (int i=0; i<tree.depth(iter)/*-2*/; ++i)
                cout << " ";

        std::cout << "Dump Node :" /*<< strParent << "N:"*/ << strNode << std::endl;
    }
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
    BYTE WholeOpen[] =
    {
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

    std::cout << Game.GameTree.size() << std::endl;

    DumpGameTree(Game.GameTree);

}


