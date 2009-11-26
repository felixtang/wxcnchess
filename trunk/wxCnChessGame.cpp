#include <sstream>
#include <iostream>
#include "wxCnChessGame.h"

namespace wxCnChess
{

    //----------------------------------------------------------------------------------
    //        GameNode
    //----------------------------------------------------------------------------------
    GameNode::GameNode()
    {
    }

    GameNode::~GameNode()
    {
    }

//    std::string GameNode::toString(GameNode* parent)
//    {
//        std::stringstream ss;
//
//        if( parent != 0 )
//            ss << parent->m_Name << "->";
//
//        ss << /*parent->m_Name << "->" << */m_Name << std::endl;
//        return ss.str();
//    }

    std::string GameNode::toString(GameNode* parent)
    {
        if(parent == 0) {
            return std::string("Game Begin:");
        }

        const BYTE* pSrcMan = std::find( parent->ucChessBoard, parent->ucChessBoard + CHESS_MAN_NUM, m_ucFrom);
        unsigned int nSrcMan = pSrcMan - (BYTE*)parent->ucChessBoard;

//        std::cout << "addr parent->ucChessBoard:" << (unsigned long)parent->ucChessBoard << std::endl;
//        std::cout << "pSrcMan:" << (unsigned long)pSrcMan << std::endl;
//        std::cout << "pSrcMan - ucChessBoard:" << nSrcMan << std::endl;

        if (nSrcMan >= CHESS_MAN_NUM)
        {
            return std::string("Invalid node!\n");
        }

        const char** szNum;
        if (nSrcMan >= 16)
            szNum = szBlackNum;
        else
            szNum = szRedNum;

        unsigned int nStartX = m_ucFrom / 10;
        unsigned int nStartY = m_ucFrom % 10;
        unsigned int nEndX = m_ucTo / 10;
        unsigned int nEndY = m_ucTo % 10;

        if (nSrcMan < 16)
        {
            nStartX = 8 - nStartX;
            nEndX = 8 - nEndX;
        }
        else
        {
            nStartY = 9 - nStartY;
            nEndY = 9 - nEndY;
        }

        char szStep[32];

        switch(g_xqMan[nSrcMan]) {
        case XM_JU:
        case XM_PAO:
        case XM_BING:
        case XM_KING:
            if (nStartY == nEndY)
            {
                sprintf(szStep, "%s%s平%s\n", szManName[nSrcMan], szNum[nStartX], szNum[nEndX]);
            }
            else if (nStartY < nEndY)
            {
                sprintf(szStep, "%s%s进%s\n", szManName[nSrcMan], szNum[nStartX], szNum[nEndY - nStartY - 1]);
            }
            else
            {
                sprintf(szStep, "%s%s退%s\n", szManName[nSrcMan], szNum[nStartX], szNum[nStartY - nEndY - 1]);
            }
            break;
        case XM_MA:
        case XM_XIANG:
        case XM_SHI:
            if (nStartY < nEndY)
            {
                sprintf(szStep, "%s%s进%s\n", szManName[nSrcMan], szNum[nStartX], szNum[nEndX]);
            }
            else
            {
                sprintf(szStep, "%s%s退%s\n", szManName[nSrcMan], szNum[nStartX], szNum[nEndX]);
            }
            break;
        default:
            break;
        }
        std::stringstream ss;
        ss << szStep << "Comment: " << m_Comment << std::endl;
        return ss.str();
    }

    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------
}
