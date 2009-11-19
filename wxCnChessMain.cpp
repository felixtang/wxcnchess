

#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/imaglist.h>

#include "wxCnChessMain.h"
#include "wxCnChessGameViewPanel.h"

IMPLEMENT_APP(wxCnChess::wxCnChessApp)

namespace wxCnChess {



    BEGIN_EVENT_TABLE(wxCnChessMainFrame, wxFrame)

        EVT_MENU(wxID_EXIT,   wxCnChessMainFrame::OnQuit)

    END_EVENT_TABLE()

    IMPLEMENT_CLASS(wxCnChessMainFrame, wxFrame)


    wxCnChessMainFrame::wxCnChessMainFrame(wxWindow* parent, wxWindowID id)
    : wxFrame(parent, id, _("wxCnChess"), wxDefaultPosition, wxSize(800,600))
    {
        m_mgr = new wxAuiManager(this);

        m_statusbar = CreateStatusBar();
        m_statusbar->SetStatusText(_T("Welcome to wxModelEditor!"));

        SetMenu();
        SetToolBar();
        CreateLogWin();
        CreateCheseBord();

        m_mgr->Update();
    }

    bool wxCnChessMainFrame::Destroy()
    {
        for (int page = (m_notebook->GetPageCount() -1); page >= 0; page--) {
            m_notebook->GetPage(page)->Destroy();
            m_notebook->DeletePage(page);
        }

        delete wxLog::SetActiveTarget(m_logOld);
        return wxFrame::Destroy();
    }

    void wxCnChessMainFrame::SetMenu()
    {
        wxMenu* fmenu = new wxMenu();
        fmenu->Append(wxID_NEW, _T("&New\tCtrl+T"), _T("Open a new tab"));
        fmenu->Append(wxID_CLOSE, _T("&Close\tCtrl+W"),_T("Close current tab"));
        fmenu->AppendSeparator();
        fmenu->Append(wxID_EXIT, _T("E&xit\tCtrl+Q"), _T("Quit"));

        wxMenu* hmenu = new wxMenu();
        hmenu->Append(wxID_ABOUT, _T("&About\tF1"), _T("About"));

        wxMenuBar* menubar = new wxMenuBar();
        menubar->Append(fmenu, _T("&File"));
        menubar->Append(hmenu, _T("&Help"));

        SetMenuBar(menubar);
    }

    void wxCnChessMainFrame::SetToolBar()
    {
        wxAuiToolBar* tb3 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                         wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
        tb3->SetToolBitmapSize(wxSize(16,16));
        wxBitmap tb3_bmp1 = wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16));
        tb3->AddTool(wxID_NEW, wxT("Test2"), tb3_bmp1);

        wxBitmap tb3_bmp2 = wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER, wxSize(16,16));
        tb3->AddTool(ID_NewAnimation, wxT("NewAnim"), tb3_bmp2);

        tb3->AddSeparator();
        wxBitmap tb3_bmp3 = wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_OTHER, wxSize(16,16));
        tb3->AddTool(ID_PlayAnimation, wxT("Play Animation"), tb3_bmp3);

        wxBitmap tb3_bmp4 = wxArtProvider::GetBitmap(wxART_CROSS_MARK , wxART_OTHER, wxSize(16,16));
        tb3->AddTool(ID_StopAnimation, wxT("Stop Animation"), tb3_bmp4);

        tb3->AddSeparator();
        wxBitmap tb3_bmp5 = wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_OTHER, wxSize(16,16));
        tb3->AddTool(ID_ListAnimations, wxT("List Animations"), tb3_bmp5);

        tb3->AddTool(ID_ToolBarItem+21, wxT("Test"), tb3_bmp1);
        //tb3->SetCustomOverflowItems(prepend_items, append_items);
        tb3->Realize();

        m_mgr->AddPane(tb3, wxAuiPaneInfo().
                      Name(wxT("tb3")).Caption(wxT("Toolbar 3")).
                      ToolbarPane().Top().Row(1).
                      LeftDockable(false).RightDockable(false));
    }

    void wxCnChessMainFrame::CreateLogWin()
    {
        m_logWin = new wxTextCtrl(this, wxID_ANY,  wxEmptyString,
                           wxDefaultPosition, wxSize(100,50),
                           wxNO_BORDER | wxTE_MULTILINE);
        m_logWin->SetEditable(false);
        wxLogTextCtrl* logger = new wxLogTextCtrl( m_logWin );
        m_logOld = logger->SetActiveTarget( logger );
        logger->SetTimestamp( NULL );

        m_mgr->AddPane(m_logWin, wxBOTTOM, wxT("Message & Logs"));
    }

    void wxCnChessMainFrame::CreateCheseBord()
    {
        m_notebook = new wxNotebook(this, wxID_ANY);
        //wxPanel* notebook_1_pane_1 = new wxPanel(m_notebook, wxID_ANY);

        //wxCnChessBoard* board = new wxCnChessBoard(m_notebook, wxID_ANY);
        //m_notebook->AddPage(board, wxT("tab1"));

        wxCnChessGameView* gameView = new wxCnChessGameView(m_notebook, wxID_ANY);
        m_notebook->AddPage(gameView, wxT("tab1"));

        m_mgr->AddPane(m_notebook, wxCENTER, wxT("Chess Board"));
    }

    void wxCnChessMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
    {
        Close(true);
    }


} //namespace wxCnChess
