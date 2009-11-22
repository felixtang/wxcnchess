#ifndef WXCNCHESSGAME_H_INCLUDED
#define WXCNCHESSGAME_H_INCLUDED

/** Chinese Chess Game Interfaces.
 *
 * @remark This classes are all interfaces to load and matainate a chess game
 *
 * @author Yaohua Xiao bentry@163.com
 */

#include <map>
#include <string>

// tree.hh: an STL-like C++ tree class
// Kasper Peeters, kasper.peeters (at) gmail.com
#include "tree.hh"

namespace wxCnChess{

    //----------------------------------------------------------------------------------
    typedef std::map<std::string, std::string> StringMap;
    typedef StringMap::iterator StringMapIter;

	const int CHESS_MAN_NUM = 32; // 双方棋子总数
	
	class GameNode{
    public:

		unsigned char	m_ucFrom;
		unsigned char	m_ucTo;
		std::string		m_Comment;

		unsigned char	ucChessBoard[ CHESS_MAN_NUM ];

    private:

    };

	typedef tree<GameNode>  GameTree_t;
    //----------------------------------------------------------------------------------
    class wxCnChessGame{
    public:
        GameTree_t  GameTree;
        StringMap	GameInfo;		
    private:


    };

    //----------------------------------------------------------------------------------
    class IFileReader {
    public:
        virtual bool ReadGame(wxCnChessGame* Game, const char* filename) = 0;
        virtual bool ReadGame(wxCnChessGame* Game, std::istream& data_stream) = 0;
        virtual std::string GetLastError() = 0;
    };

}
#endif // WXCNCHESSGAME_H_INCLUDED
