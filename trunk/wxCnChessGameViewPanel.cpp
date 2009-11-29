#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/imaglist.h>

#include "wxCnChessGameViewPanel.h"

namespace wxCnChess {

    BEGIN_EVENT_TABLE(wxCnChessGameView, wxPanel)
        //EVT_MOUSE_EVENTS    (wxCnChessGameView::OnMouseMove)
        //EVT_ERASE_BACKGROUND(wxCnChessGameView::OnEraseBackground)
        //EVT_PAINT           (wxCnChessGameView::OnPaint)
        //EVT_SIZE            (wxCnChessGameView::OnSize)
    END_EVENT_TABLE()

    IMPLEMENT_DYNAMIC_CLASS(wxCnChessGameView, wxPanel)


    unsigned int wxCnChessGameView::m_instances = 0;

    //------------------------------------------------------------------------------
    wxCnChessGameView::wxCnChessGameView()
    {
        Init();
    }

    /** Constructs a window, with an embedded Chess Board window. */
    wxCnChessGameView::wxCnChessGameView(wxWindow* parent, wxWindowID id ,
                        const wxPoint& pos,
                        const wxSize& size ,
                        long style ,
                        const wxString& name )
    {
        Init();
        Create(parent, id, pos, size, style, name);
    }


    //------------------------------------------------------------------------------
    wxCnChessGameView::~wxCnChessGameView()
    {
        Destroy();
    }

    //------------------------------------------------------------------------------
    bool wxCnChessGameView::Create(wxWindow* parent, wxWindowID id,
                           const wxPoint& pos, const wxSize& size, long style,
                           const wxString& name)
    {
        wxString instance_name = name + wxString::Format(wxT("%u"), m_instances);

        if (!wxPanel::Create(parent, id, pos, size, style, instance_name)) {
            wxFAIL_MSG(wxT("wxCnChessGameView Control creation failed"));
            return false;
        }

        CreateUI();

        return true;
    }

    //------------------------------------------------------------------------------
    void wxCnChessGameView::CreateUI()
    {
        wxBoxSizer* topSizer = new wxBoxSizer( wxHORIZONTAL );
        m_ChessBoard = new wxCnChessBoard(this, wxID_ANY);

        topSizer->Add(m_ChessBoard, 1,wxCenter| wxEXPAND | wxALL, 2 );

        wxStaticBoxSizer* controlSizer = new wxStaticBoxSizer( wxVERTICAL, this );
        //wxBoxSizer* controlSizer = new wxBoxSizer( wxVERTICAL );

        CreateTreeControl( controlSizer );
        CreateListControl( controlSizer );
        CreateTextControl( controlSizer );

        //create a sizer with no border and centered horizontally
        topSizer->Add( controlSizer, 1, wxEXPAND | wxALL );

        SetSizer( topSizer ) ;
        topSizer->Fit( this );
        topSizer->SetSizeHints( this );

    }

    //------------------------------------------------------------------------------
    void wxCnChessGameView::CreateTreeControl( wxSizer* sizer )
    {
        m_Tree = new wxTreeCtrl(this, ID_TreeCtrl,
                            wxDefaultPosition, wxSize(100,100),
                            wxTR_DEFAULT_STYLE);

        wxImageList* imglist = new wxImageList(16, 16, true, 2);
        imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
        imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
        m_Tree->AssignImageList(imglist);

        wxTreeItemId root = m_Tree->AddRoot(wxT("Objects"), 0);
        wxArrayTreeItemIds items;

        items.Add(m_Tree->AppendItem(root, wxT("Item 1"), 0));
        items.Add(m_Tree->AppendItem(root, wxT("Item 2"), 0));
        items.Add(m_Tree->AppendItem(root, wxT("Item 3"), 0));
        items.Add(m_Tree->AppendItem(root, wxT("Item 4"), 0));
        items.Add(m_Tree->AppendItem(root, wxT("Item 5"), 0));

        int i, count;
        for (i = 0, count = items.Count(); i < count; ++i)
        {
            wxTreeItemId id = items.Item(i);
            m_Tree->AppendItem(id, wxT("Subitem 1"), 1);
            m_Tree->AppendItem(id, wxT("Subitem 2"), 1);
            m_Tree->AppendItem(id, wxT("Subitem 3"), 1);
            m_Tree->AppendItem(id, wxT("Subitem 4"), 1);
            m_Tree->AppendItem(id, wxT("Subitem 5"), 1);
        }

        m_Tree->Expand(root);

        sizer->Add( m_Tree, 1, wxEXPAND | wxALL, 2 );

    }

    //------------------------------------------------------------------------------
    void wxCnChessGameView::CreateTextControl( wxSizer* sizer )
    {
        m_Comment = new wxTextCtrl( this, -1,
                            wxEmptyString, wxDefaultPosition,
                            wxSize(100,50), wxTE_MULTILINE);

        sizer->Add( m_Comment, 1,  wxEXPAND | wxALL, 2 );

    }

    //------------------------------------------------------------------------------
    void wxCnChessGameView::CreateListControl( wxSizer* sizer )
    {
        m_List = new wxListCtrl( this, ID_ListCtrl,
                            wxDefaultPosition, wxSize(100,80),
                            wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES);

        wxListItem itemCol;
        itemCol.SetText(wxT("Red"));
        m_List->InsertColumn(0, itemCol);
        m_List->SetColumnWidth(0, 80 );

        itemCol.SetText(wxT("Black"));
        itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
        m_List->InsertColumn(1, itemCol);
        m_List->SetColumnWidth(1, 80 );

        wxString buf;
        for(int i = 0; i< 5; ++i){
            buf.Printf(wxT("Item %d"), i);
            m_List->InsertItem(i, buf);

            buf.Printf(wxT("Item List %d"), i);
            m_List->SetItem(i, 1, buf);

        }
        sizer->Add( m_List, 1, wxEXPAND | wxALL, 2 );
    }
    //------------------------------------------------------------------------------
    void wxCnChessGameView::Init()
    {

    }

    //------------------------------------------------------------------------------
    bool wxCnChessGameView::Destroy()
    {
        return true;
    }

    //------------------------------------------------------------------------------
//    void wxCnChessGameView::OnSize(wxSizeEvent& event)
//    {
//        wxPanel::OnSize(event);
//        //m_ReSized = true;
//
//        Refresh();
//
//        //wxLogMessage(wxT("OnSize: w=%d,h=%d" ),iWidth,iHeight);
//    }
//
//    //------------------------------------------------------------------------------
//    void wxCnChessGameView::OnPaint(wxPaintEvent& event)
//    {
//        wxPanel::OnPaint(event);
//    }
//
//    //------------------------------------------------------------------------------
//    void wxCnChessGameView::OnMouseMove(wxMouseEvent& event)
//    {
//    }
//
//    //------------------------------------------------------------------------------
//    void wxCnChessGameView::OnEraseBackground(wxEraseEvent& event)
//    {
//    }
}
