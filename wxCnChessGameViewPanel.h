#ifndef WXCNCHESSGAMEVIEWPANEL_H_INCLUDED
#define WXCNCHESSGAMEVIEWPANEL_H_INCLUDED

/** An Chinese Chess Game view UI.
 *
 * @remark This class creates an Chess Board view panel
 *
 * @author Yaohua Xiao bentry@163.com
 */
#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>

#include "wxCnChessBoardControl.h"

namespace wxCnChess {

    class wxCnChessGameView : public wxPanel
    {
        DECLARE_DYNAMIC_CLASS(wxCnChessGameView)
        DECLARE_EVENT_TABLE()

    public:
        /** Default constructor. */
        wxCnChessGameView();

        /** Constructs a window, with an embedded Chess Board window. */
        wxCnChessGameView(wxWindow* parent, wxWindowID id = wxID_ANY,
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize,
                            long style = wxSUNKEN_BORDER | wxTRANSPARENT_WINDOW,
                            const wxString& name = wxT("wxCnChessGameView"));

        virtual ~wxCnChessGameView();

        virtual bool Create(wxWindow* parent, wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxSUNKEN_BORDER | wxTRANSPARENT_WINDOW,
                    const wxString& name = wxT("wxCnChessGameView"));

        /** Destructor */
        virtual bool Destroy();

    protected:

        virtual void OnSize(wxSizeEvent& event);
        virtual void OnPaint(wxPaintEvent& event);
        virtual void OnMouseMove(wxMouseEvent& event);
        virtual void OnEraseBackground(wxEraseEvent& event);

    public:
        enum
        {
            ID_CreateTree = wxID_HIGHEST+1,

            ID_TreeCtrl,
            ID_ListCtrl

        };

    private:
        static unsigned int m_instances;
        /** Initializes private variables. */
        virtual void Init();
        virtual void CreateUI();

        void CreateTreeControl( wxSizer* sizer );
        void CreateTextControl( wxSizer* sizer );
        void CreateListControl( wxSizer* sizer );

        wxCnChessBoard* m_ChessBoard;
        wxTreeCtrl* m_Tree;  // Game tree
        wxTextCtrl* m_Comment;  // Display Comments
        wxListCtrl* m_List; // Current tree's Move List
    };

}

#endif // WXCNCHESSGAMEVIEWPANEL_H_INCLUDED
