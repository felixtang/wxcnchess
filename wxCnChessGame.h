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

#if defined( __WIN32__ ) || defined( _WIN32 )
#   include <windows.h>
#else
typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
#endif

namespace wxCnChess
{

    //----------------------------------------------------------------------------------
    typedef std::map<std::string, std::string> StringMap;
    typedef StringMap::iterator StringMapIter;

    //----------------------------------------------------------------------------------
    // const variables

    static const unsigned int CHESS_MAN_NUM = 32;

    static const char* const szManName[] =
    {
        "车", "马", "相", "士", "帅", "士", "相", "马", "车", "炮", "炮", "兵", "兵", "兵", "兵", "兵",
        "车", "马", "象", "士", "将", "士", "象", "马", "车", "炮", "炮", "卒", "卒", "卒", "卒", "卒"
    };

    static const char* szRedNum[] =
        {"一", "二", "三", "四", "五", "六", "七", "八", "九"};

    static const char* szBlackNum[] =
        {"１", "２", "３", "４", "５", "６", "７", "８", "９"};

    enum XM_TYPE
    {
        XM_JU, // 车
        XM_MA, // 马
        XM_XIANG, // 相象
        XM_SHI, // 仕士
        XM_KING, // 帅将
        XM_PAO, // 炮
        XM_BING // 兵卒
    };

    static const XM_TYPE g_xqMan[] =
    {
        XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING,
        XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING
    };

    // 走子顺序
    enum XQ_ORDER
    {
        XO_RED, // 红先
        XO_BLACK, // 黑先
        XO_NONE // 未知
    };

    // 结果
    enum XQ_RESULT
    {
        XR_UNKNOWN, // 未知
        XR_REDWIN, // 红胜
        XR_BLACKWIN, // 黑胜
        XR_PEACE // 和
    };

    // 数据类型
    enum XQ_TYPE
    {
        XT_ALL, // 全局
        XT_OPEN, // 开局
        XT_MIDDLE, // 中局
        XT_END // 残局
    };
    //----------------------------------------------------------------------------------


    class GameNode
    {
    public:
        GameNode();
        ~GameNode();

        unsigned char	m_ucFrom;
        unsigned char	m_ucTo;
        unsigned char	ucChessBoard[ CHESS_MAN_NUM ];

        std::string		m_Comment;
        std::string		m_Name;
    public:         //functions
        std::string     toString( GameNode* parent  );

    private:

    };

    typedef tree<GameNode>  GameTree_t;
    //----------------------------------------------------------------------------------
    class wxCnChessGame
    {
    public:
        GameTree_t  GameTree;
        StringMap	GameInfo;
    private:


    };

    //----------------------------------------------------------------------------------
    class IFileReader
    {
    public:
        virtual bool ReadGame(wxCnChessGame* Game, const char* filename) = 0;
        virtual bool ReadGame(wxCnChessGame* Game, std::istream& data_stream) = 0;
        virtual std::string GetLastError() = 0;
    };

}
#endif // WXCNCHESSGAME_H_INCLUDED
