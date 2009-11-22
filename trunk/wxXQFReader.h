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
    public:
        wxXQFReader();
        ~wxXQFReader();

    public: // interface impliamtion
        virtual bool ReadGame(wxCnChessGame& Game, const char* filename);
        virtual bool ReadGame(wxCnChessGame& Game, std::istream& data_stream);
        virtual std::string GetLastError();

    private:
        bool ReadHeader(const BYTE* buf, size_t len);
        bool CheckFormat(const BYTE* buf) const;
        bool ReadInitDecryptKey(const BYTE* buf);
        bool InitChessBoard( BYTE* buf);

        bool ReadAndDecrypt(std::istream& data_stream, BYTE* buff, size_t len);

    private:
        std::string m_LastError;
        enum {RECENT_VER = 0x12};
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
