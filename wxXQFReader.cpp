#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>

#include <numeric>

#include "wxXQFReader.h"

namespace wxCnChess
{

    //----------------------------------------------------------------------------------
    wxXQFReader::wxXQFReader() : m_LastError()
    {
    }

    //----------------------------------------------------------------------------------

    wxXQFReader::~wxXQFReader()
    {
    }
    //----------------------------------------------------------------------------------
    bool wxXQFReader::ReadGame(wxCnChessGame* Game, const char* filename)
    {
        std::ifstream fsFile( filename, std::ios::in|std::ios::binary);
        if (fsFile.good())
        {
            ReadGame( Game, fsFile);
        }
        else
        {
            std::stringstream s;

            s << "Can't open file '" << filename << "'!" << __FILE__ << __LINE__;
            m_LastError = s.str();
            //m_LastError += "Can't open file '" + filename + "'!"/* + __FILE__ + __LINE__*/;
            return false;
        }
        return true;
    }


    //----------------------------------------------------------------------------------
    bool wxXQFReader::ReadGame(wxCnChessGame* Game, std::istream& data_stream)
    {

		m_pGame = Game;

        if (data_stream.bad())
        {
            m_LastError = "Read game from istream fail!";
            return false;
        }


        memset( m_HeaderBuff, 0 ,sizeof(m_HeaderBuff) );
        data_stream.read( (char*)m_HeaderBuff, sizeof(m_HeaderBuff) );

        if( !ReadHeader( /*m_HeaderBuff,*/ sizeof(m_HeaderBuff)) ){
            return false;
        }

        //std::cout << buff << std::endl;

        return true;
    }

    //----------------------------------------------------------------------------------
    bool wxXQFReader::ReadHeader( size_t len)
    {
        assert( 0x0400 == len && "0x0400 == len");
        //assert( 0 != buf && "0 != buf");

        if ( !CheckFormat( m_HeaderBuff ) )
        {
            m_LastError = " CheckFormat Fail! ";
            return false;
        }
        std::cout << "CheckFormat OK!" << std::endl;
		
		m_ucVer = m_HeaderBuff[2];
		ReadInitDecryptKey(m_HeaderBuff);
		InitChessBoard(m_HeaderBuff);
        return true;
    }

    //----------------------------------------------------------------------------------
    bool wxXQFReader::CheckFormat(const BYTE* buf) const
    {
        // 检验文件头
        if (*(WORD*)buf != *(WORD*)"XQ"){
            m_LastError = " Head != 'XQ'! ";
            return false;
        }
        // 文件比程序版本高，无法读取
        if (buf[2] > RECENT_VER)
        {
            m_LastError = " Version > 0x12 ";
            return false;
        }

        // 较验
        BYTE ucChk = std::accumulate(buf + 0xC, buf + 0x10, 0);
        if (0 != ucChk)
        {
            m_LastError = " Check( 0xC ~ 0x10 )> 0 ";
            return false;
        }
        return true;
    }

    //----------------------------------------------------------------------------------
    ////////////////////////////////////
    // 初始化解密种子
    // Programmer : Michael Taylor
    // 0x47BDE0, 0x47B50C
    ////////////////////////////////////
    bool wxXQFReader::ReadInitDecryptKey(const BYTE* buf)
    {
        // initialize the seed for decypt
        if (m_ucVer < 0x10)
        {
            m_ucVer = 0;
            m_uc40E = 0;
            m_uc40F = 0;
            m_uc410 = 0;
            m_uc40F = 0;
            memset(m_ucKey, 0, sizeof(m_ucKey));
        }
        else
        {
            BYTE uc0xD = buf[0xd];
            m_uc40E = uc0xD * uc0xD * uc0xD * 54 + 221 * uc0xD;
            BYTE uc0xE = buf[0xe];
            m_uc40F = (54 * uc0xE * uc0xE + 221) * m_uc40E;
            BYTE uc0xF = buf[0xf];
            m_uc410 = (54 * uc0xF * uc0xF + 221) * m_uc40F;
            int n0xC = buf[0xc];
            m_w412 = ((n0xC * 256 + uc0xD) % 0x7D00) + 0x2FF;

            memset(m_ucKey, 0, sizeof(m_ucKey));

            DWORD dwEax = buf[0xF - 0xC];
            int nArg4 = buf[0x1A - 0xC];
            nArg4 &= dwEax;
            nArg4 |= buf[0x16 - 0xC];
            int nArg0 = buf[0x1B - 0xC];
            nArg0 &= dwEax;
            nArg0 |= buf[0x17 - 0xC];
            DWORD dwEcx = buf[0x19 - 0xC];
            dwEcx &= dwEax;
            dwEcx |= buf[0x15 - 0xC];
            DWORD dwEdx = buf[0x18 - 0xC];
            dwEdx &= dwEax;
            dwEdx |= buf[0x14 - 0xC];

            m_ucKey[8] = (BYTE)dwEdx;
            m_ucKey[9] = (BYTE)dwEcx;
            m_ucKey[0xA] = (BYTE)nArg4;
            m_ucKey[0xB] = (BYTE)nArg0;
            m_ucKey[0xC] = (BYTE)(dwEdx & 0x5B);
            m_ucKey[0xD] = (BYTE)(dwEcx & 0x28);
            m_ucKey[0xE] = (BYTE)(nArg4 & 0x43);
            m_ucKey[0xF] = (BYTE)(nArg0 & 0x29);
            m_ucKey[0x10] = (BYTE)(dwEdx & 0x20);
            m_ucKey[0x11] = (BYTE)(dwEcx & 0x43);
            m_ucKey[0x12] = (BYTE)(nArg4 & 0x6F);
            m_ucKey[0x13] = (BYTE)(nArg0 & 0x70);
            m_ucKey[0x14] = (BYTE)(dwEdx & 0x79);
            m_ucKey[0x15] = (BYTE)(dwEcx & 0x72);
            m_ucKey[0x16] = (BYTE)(nArg4 & 0x69);
            m_ucKey[0x17] = (BYTE)(nArg0 & 0x67);
            m_ucKey[0x18] = (BYTE)(dwEdx & 0x68);
            m_ucKey[0x19] = (BYTE)(dwEcx & 0x74);
            m_ucKey[0x1A] = (BYTE)(nArg4 & 0x20);
            m_ucKey[0x1B] = (BYTE)(nArg0 & 0x4D);
            m_ucKey[0x1C] = (BYTE)(dwEdx & 0x72);
            m_ucKey[0x1D] = (BYTE)(dwEcx & 0x2E);
            m_ucKey[0x1E] = (BYTE)(nArg4 & 0x20);
            m_ucKey[0x1F] = (BYTE)(nArg0 & 0x44);
            m_ucKey[0x20] = (BYTE)(dwEdx & 0x6F);
            m_ucKey[0x21] = (BYTE)(dwEcx & 0x6E);
            m_ucKey[0x22] = (BYTE)(nArg4 & 0x67);
            m_ucKey[0x23] = (BYTE)(nArg0 & 0x20);
            m_ucKey[0x24] = (BYTE)(dwEdx & 0x53);
            m_ucKey[0x25] = (BYTE)(dwEcx & 0x68);
            m_ucKey[0x26] = (BYTE)(nArg4 & 0x69);
            m_ucKey[0x27] = (BYTE)(nArg0 & 0x77);
            m_ucKey[0x28] = (BYTE)(dwEdx & 0x65);
            m_ucKey[0x29] = (BYTE)(dwEcx & 0x69);
            m_ucKey[0x2a] = (BYTE)(nArg4 & 0x2E);
            m_ucKey[0x2b] = (BYTE)(nArg0 & 0x5D);
        }
        return true;
    }

    //----------------------------------------------------------------------------------
    bool wxXQFReader::InitChessBoard(BYTE* buf)
    {
        if (m_ucVer < 0xC)
        {
        }
        else
        {
            BYTE tmpMan[32];
            int i;
            for (i = 1; i <= 32; ++i)
            {
                BYTE ucTmp = buf[0x0F + i];
                int nTmp = (m_uc40E + i) & 0x8000001F;
                tmpMan[nTmp] = ucTmp;
            }

            for (i = 1; i <= 32; ++i)
            {
                buf[0xF + i] = tmpMan[i - 1];
            }
        }

        for (int i = 0; i <= 0x20; ++i)
        {
            buf[0x10 + i] -= m_uc40E;
            if (buf[0x10 + i] > 89)
                buf [0x10 + i] = 0xFF;
        }
        return true;
    }

    //----------------------------------------------------------------------------------
    bool wxXQFReader::ReadAndDecrypt(std::istream& data_stream, BYTE* buff, size_t len)
    {
        int nPos = data_stream.tellg();

        // 读取数据
        if (!data_stream.read((char*)buff, len))
        {
            m_LastError = "ReadAndDecrypt: Read Fail ! ";
            return false;
        }


        for (size_t i = 0; i < len; ++i)
        {
            buff[i] -= m_ucKey[((nPos + i) & 0x1F) +  0xC];
        }
        return true;
    }

	//----------------------------------------------------------------------------------
	////////////////////////////////////
	// Read [ n( BYTE ) ,data] String
	////////////////////////////////////
	std::string wxXQFReader::ReadString(const BYTE* buff)
	{
		BYTE len = buff[0];
		std::string str( buff + 1, buff + len + 1);
		assert( str.size() == len );
		return str;
	}

    //----------------------------------------------------------------------------------
	std::string wxXQFReader::ReadCommentString( std::istream& data_stream, BYTE flag )	{		assert( 4 == sizeof(int) );
		
		int nCommentLen = 0;
		char* szComment = 0;
		if (m_ucVer <= 0xA)
		{
			ReadAndDecrypt( data_stream, (BYTE*)&nCommentLen, sizeof(int) );
		}
		else
		{
			// 高版本通过flag来标记有没有注释，有则紧跟着注释长度和注释字段
			flag &= 0xE0;
			if (flag & 0x20) // 有注释
			{
				 ReadAndDecrypt( data_stream, (BYTE*)&nCommentLen, sizeof(int) );
				 nCommentLen -= m_w412;
			}
		}		if (nCommentLen > 0)
		{
			szComment = new char[nCommentLen + 1];
			if (NULL == szComment)	{
				return std::string("ERROR when new memory! ");
			}

			szComment[nCommentLen] = 0;
			if ( false == ReadAndDecrypt( data_stream, (BYTE*)szComment, nCommentLen) )	{
				delete []szComment;
				return std::string("ERROR when read comment in file! ");
			}

			std::string result(szComment);
			assert( nCommentLen == result.size() );
			return result;
		}

		return std::string("");	}	//----------------------------------------------------------------------------------    
	void wxXQFReader::SetStartState( BYTE* stateBuff )
	{
		if( !stateBuff ) 
			return;

		memcpy( stateBuff, m_HeaderBuff + 0x10 , CHESS_MAN_NUM );
	}

	//----------------------------------------------------------------------------------
	GameTree_t::iterator wxXQFReader::ReadStep( std::istream& data_stream, GameTree_t::iterator nodeParent )
	{
        assert( data_stream.good() && "ReadStep error: data stream is bad! ");				GameTree_t* pTree = &(m_pGame->GameTree);				BYTE ucStep[4];				if( false == ReadAndDecrypt( data_stream, ucStep, 4 ) ){
			return pTree->end();
		}

		BYTE ucFlag = 0;

		// Modify the flag according to the version
		if (m_ucVer <= 0xA)
		{
			if (ucStep[2] & 0xF0)
				ucFlag |= 0x80;
			if (ucStep[2] & 0x0F)
				ucFlag |= 0x40;
		} else {
			ucFlag = ucStep[2];		}
		ReadCommentString( data_stream, ucFlag );		ucStep[0] -= 0x18;
		ucStep[0] -= m_uc40F;
		ucStep[1] -= 0x20;
		ucStep[1] -= m_uc410;				GameTree_t::iterator curNode =  pTree->append_child ( nodeParent );  // new a node under the parent node		curNode->m_ucFrom	= ucStep[0];		curNode->m_ucTo		= ucStep[1];		if( nodeParent == pTree->begin() ) {
			SetStartState( curNode->ucChessBoard );
		} else {
			memcpy( curNode->ucChessBoard, nodeParent->ucChessBoard, CHESS_MAN_NUM );		}
		std::replace( curNode->ucChessBoard, curNode->ucChessBoard + CHESS_MAN_NUM, (BYTE)curNode->m_ucTo, (BYTE)0xFF); // If a piece in the pos which this step will go to, eat it
		std::replace( curNode->ucChessBoard, curNode->ucChessBoard + CHESS_MAN_NUM, curNode->m_ucFrom, curNode->m_ucTo);
		// 有后续着法
		if ( ucFlag & 0x80 )
		{
			GameTree_t::iterator nodeChild = ReadStep( curNode );
			//if ( nodeChild != pTree->end() )
			//{
			//	pNode->pFirstChild = pChild;
			//	pNode->pCurChild = pChild;
			//}
		}		// 有变着
		if (ucStep[2] & 0x40)
		{
			GameTree_t::iterator nodeChild = ReadStep( nodeParent );
			//if (pRight)
			//{
			//	pNode->pRight = pRight;
			//	pRight->pLeft = pNode;
			//}
		}

		return curNode;
	}


    //----------------------------------------------------------------------------------
    std::string wxXQFReader::GetLastError()
    {
        return m_LastError;
    }


}
