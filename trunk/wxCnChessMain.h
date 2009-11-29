#ifndef WXCNCHESSMAIN_H_INCLUDED
#define WXCNCHESSMAIN_H_INCLUDED

#include <wx/wx.h>
#include <wx/aui/aui.h>

namespace wxCnChess {

    class wxCnChessMainFrame : public wxFrame
    {
        DECLARE_CLASS(EditorMainFrame)
        DECLARE_EVENT_TABLE()

    public:

        enum
        {
            ID_CreateTree = wxID_HIGHEST+1,
            ID_NewAnimation,
            ID_PlayAnimation,
            ID_StopAnimation,
            ID_ListAnimations,

            ID_TreeCtrl,
            ID_ListCtrl,

            ID_ToolBarItem
        };

        wxCnChessMainFrame(wxWindow* parent, wxWindowID id);

        void OnQuit(wxCommandEvent& WXUNUSED(event));

    private:
        virtual bool Destroy();

        void SetMenu();
        void SetToolBar();
        void CreateLogWin();
        void CreateCheseBord();

        wxAuiManager*   m_mgr;
        wxNotebook*     m_notebook;
        wxTextCtrl*     m_logWin;
        wxLog *         m_logOld;
        wxStatusBar*    m_statusbar;

        //wxTreeCtrl*   m_tree;
    };


    class wxCnChessApp : public wxApp
    {
    public:
        bool Initialize(int& argc, wxChar **argv)
        {
            #if defined( __WIN32__ ) || defined( _WIN32 )
            // VS2005之后版本的std::fstream对中文路径处理不正确的原因，所以加载中文路径或文件名不成功，解决办法：
            // 在主函数开始加入  setlocale(LC_ALL,"Chinese-simplified");
            setlocale(LC_ALL,"Chinese-simplified");
            #endif


            return wxApp::Initialize(argc, argv);
        };

        bool OnInit()
        {

            m_frame = new wxCnChessMainFrame(0, wxID_ANY);

            m_frame->Show();

            return true;
        };

    private:

        wxCnChessMainFrame* m_frame;

    };

    DECLARE_APP(wxCnChessApp)
}

#endif // WXCNCHESSMAIN_H_INCLUDED
