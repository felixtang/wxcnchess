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
        "��", "��", "��", "ʿ", "˧", "ʿ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
        "��", "��", "��", "ʿ", "��", "ʿ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"
    };

    static const char* szRedNum[] =
        {"һ", "��", "��", "��", "��", "��", "��", "��", "��"};

    static const char* szBlackNum[] =
        {"��", "��", "��", "��", "��", "��", "��", "��", "��"};

    enum XM_TYPE
    {
        XM_JU, // ��
        XM_MA, // ��
        XM_XIANG, // ����
        XM_SHI, // ��ʿ
        XM_KING, // ˧��
        XM_PAO, // ��
        XM_BING // ����
    };

    static const XM_TYPE g_xqMan[] =
    {
        XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING,
        XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING
    };

    // ����˳��
    enum XQ_ORDER
    {
        XO_RED, // ����
        XO_BLACK, // ����
        XO_NONE // δ֪
    };

    // ���
    enum XQ_RESULT
    {
        XR_UNKNOWN, // δ֪
        XR_REDWIN, // ��ʤ
        XR_BLACKWIN, // ��ʤ
        XR_PEACE // ��
    };

    // ��������
    enum XQ_TYPE
    {
        XT_ALL, // ȫ��
        XT_OPEN, // ����
        XT_MIDDLE, // �о�
        XT_END // �о�
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
