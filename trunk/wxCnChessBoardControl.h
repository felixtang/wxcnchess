#ifndef WXCNCHESSBOARDCONTROL_H_INCLUDED
#define WXCNCHESSBOARDCONTROL_H_INCLUDED

#include <wx/wx.h>

/** Manages an Chinese Chess Board rendering and its inputs.
 *
 * @remark This class creates an Chess Board control, set up
 *         and manages its update, provides basic input handling
 *         to the mouse movements.
 *
 * @author Yaohua Xiao bentry@163.com
 */


namespace wxCnChess {

    class CnChessGame;

    wxBitmap ScaleBitmap(wxBitmap& bmp, int max_width, int max_height);

    const int max_row = 10;
    const int max_col = 9;
    const wxString BOARD_IMAGE_FILE = wxT("ChessBoard.jpg");

    class wxCnChessBoard : public wxControl
    {
        DECLARE_DYNAMIC_CLASS(wxCnChessBoard)
        DECLARE_EVENT_TABLE()

    public:


        /** Default constructor. */
        wxCnChessBoard();

        /** Constructs a window, with an embedded Chess Board window. */
        wxCnChessBoard(wxWindow* parent, wxWindowID id = wxID_ANY,
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize,
                            long style = wxSUNKEN_BORDER | wxTRANSPARENT_WINDOW,
                            const wxValidator& val = wxDefaultValidator,
                            const wxString& name = wxT("wxCnChessBoard"));

        virtual ~wxCnChessBoard();

        virtual bool Create(wxWindow* parent, wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxSUNKEN_BORDER | wxTRANSPARENT_WINDOW,
                    const wxValidator& val = wxDefaultValidator,
                    const wxString& name = wxT("wxCnChessBoard"));

        /** Destructor */
        virtual bool Destroy();

        /** Render a frame and update. */
        virtual void Update();

        /** Returns a small 3:4 window size.
         *
         * @return A size of 320x240.
         */
        virtual wxSize DoGetBestSize() const { return wxSize(320, 240); };

        virtual void CreateEmptyBoard( wxString& instance_name );

        /** Returns Board position given as the x as row, y as col.
         *
         * @return wxPoint& p as result.
         */
        virtual inline wxPoint GetPos( int x, int y );

    protected:

        virtual void OnSize(wxSizeEvent& event);
        virtual void OnPaint(wxPaintEvent& event);
        virtual void OnMouseMove(wxMouseEvent& event);
        virtual void OnEraseBackground(wxEraseEvent& event);
        virtual void RenderDC(wxDC&  dc);

    private:

        /** Initializes private variables. */
        virtual void Init();
        virtual void LoadChessBoardImage();

        void ResizeChessBoard(wxCoord w,wxCoord  h);


        wxPoint m_BoardBound;
        wxPoint m_BoardOffset;
        float m_colsize, m_rowsize;
        wxString m_BoardImageFile;

        wxBitmap m_BoardImage;
        wxBitmap m_OriginalBoardImage;
        bool m_ReSized;

        wxPanel* m_panel;
        static unsigned int m_instances ;
    };
}

#endif // WXCNCHESSBOARDCONTROL_H_INCLUDED
