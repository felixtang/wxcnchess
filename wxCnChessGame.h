#ifndef WXCNCHESSGAME_H_INCLUDED
#define WXCNCHESSGAME_H_INCLUDED

/** Chinese Chess Game Interfaces.
 *
 * @remark This classes are all interfaces to load and matainate a chess game
 *
 * @author Yaohua Xiao bentry@163.com
 */


// tree.hh: an STL-like C++ tree class
// Kasper Peeters, kasper.peeters (at) gmail.com
#include "tree.hh"

namespace wxCnChess{

    //----------------------------------------------------------------------------------
    class GameNode{
    public:

    private:
    };

    //----------------------------------------------------------------------------------
    class wxCnChessGame{
    public:

    private:
        core::tree<GameNode> GameTree;
    };

    //----------------------------------------------------------------------------------
    class IFileReader {
    public:
        virtual bool ReadGame(wxCnChessGame& Game, const char* filename);

        virtual std::string GetLastError();
    }

}
#endif // WXCNCHESSGAME_H_INCLUDED
