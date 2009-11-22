#ifndef WXXQFREADER_H_INCLUDED
#define WXXQFREADER_H_INCLUDED

#include "wxCnChessGame.h"

#if defined( __WIN32__ ) || defined( _WIN32 )
#include <windows.h>
#else
typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
#endif

namespace wxCnChess
{

    //----------------------------------------------------------------------------------
    class wxXQFReader : public IFileReader
    {

    public: // interface impliamtion
        virtual bool ReadGame(wxCnChessGame* Game, const char* filename);
        virtual bool ReadGame(wxCnChessGame* Game, std::istream& data_stream);
        virtual std::string GetLastError();

	public:
        wxXQFReader();
        ~wxXQFReader();
		inline BYTE* GetHeaderBuff() { return m_HeaderBuff; };
		std::string ReadString( const BYTE* buff );
		

	private:
        bool ReadHeader( size_t len);
        bool CheckFormat(const BYTE* buf) const;
        bool ReadInitDecryptKey(const BYTE* buf );
        bool InitChessBoard( BYTE* buf);

        bool ReadAndDecrypt(std::istream& data_stream, BYTE* buff, size_t len);
		std::string ReadCommentString( std::istream& data_stream, BYTE flag );

		GameTree_t::iterator ReadStep( std::istream& data_stream, GameTree_t::iterator curNode );

		void SetStartState( BYTE* stateBuff );

    private:
        mutable std::string m_LastError;
        enum {RECENT_VER = 0x12};

		BYTE m_HeaderBuff[0x0400];
		wxCnChessGame* m_pGame;

        // For Decrypt
        BYTE m_ucKey[0x30];
        // File Version
        BYTE m_ucVer;
        BYTE m_uc40E;
        BYTE m_uc40F;
        BYTE m_uc410;
        WORD m_w412;
    };

}

#endif // WXXQFREADER_H_INCLUDED
