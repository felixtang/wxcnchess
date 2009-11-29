

#include "wxCnChessBoardControl.h"

namespace wxCnChess {

    BEGIN_EVENT_TABLE(wxCnChessBoard, wxControl)
        EVT_MOUSE_EVENTS    (wxCnChessBoard::OnMouseMove)
        EVT_ERASE_BACKGROUND(wxCnChessBoard::OnEraseBackground)
        EVT_PAINT           (wxCnChessBoard::OnPaint)
        EVT_SIZE            (wxCnChessBoard::OnSize)
    END_EVENT_TABLE()

    IMPLEMENT_DYNAMIC_CLASS(wxCnChessBoard, wxControl)


    unsigned int wxCnChessBoard::m_instances = 0;

    //------------------------------------------------------------------------------
    wxCnChessBoard::wxCnChessBoard()
    {
        Init();
    }

    /** Constructs a window, with an embedded Chess Board window. */
    wxCnChessBoard::wxCnChessBoard(wxWindow* parent, wxWindowID id ,
                        const wxPoint& pos,
                        const wxSize& size ,
                        long style ,
                        const wxValidator& val,
                        const wxString& name )
    {
        Init();
        Create(parent, id, pos, size, style, val, name);
    }


    //------------------------------------------------------------------------------
    wxCnChessBoard::~wxCnChessBoard()
    {
        Destroy();
    }

    //------------------------------------------------------------------------------
    bool wxCnChessBoard::Create(wxWindow* parent, wxWindowID id,
                           const wxPoint& pos, const wxSize& size, long style,
                           const wxValidator& val,
                           const wxString& name)
    {
        wxString instance_name = name + wxString::Format(wxT("%u"), m_instances);

        if (!wxControl::Create(parent, id, pos, size, style, val, instance_name)) {
            wxFAIL_MSG(wxT("wxCnChessBoard Control creation failed"));
            return false;
        }


        //CreateEmptyBoard( instance_name );
        LoadChessBoardImage();

        return true;
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::Init()
    {
        m_colsize = 0;
        m_rowsize = 0;

        m_BoardBound = wxPoint(0,0);
        m_BoardOffset = wxPoint(0,0);

        m_BoardImageFile = BOARD_IMAGE_FILE;

        m_ReSized = true;
    }

    //------------------------------------------------------------------------------
    bool wxCnChessBoard::Destroy()
    {
        return true;
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::CreateEmptyBoard( wxString& instance_name )
    {
        wxLogMessage(wxT("wxCnChessBoard::CreateEmptyBoard"));

        //wxClientDC dc(this);
        //RenderDC(dc);
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::Update()
    {

    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::OnSize(wxSizeEvent& event)
    {
        m_ReSized = true;

        int iWidth = 0;
        int iHeight = 0;
        GetSize(&iWidth, &iHeight);
        ResizeChessBoard(iWidth, iHeight);

        Refresh();

        //wxLogMessage(wxT("OnSize: w=%d,h=%d" ),iWidth,iHeight);
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        RenderDC(dc);
        event.Skip();
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::OnMouseMove(wxMouseEvent& event)
    {
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::OnEraseBackground(wxEraseEvent& event)
    {
    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::LoadChessBoardImage()
    {
        wxImageHandler * jpegLoader = new wxJPEGHandler();
        wxImage::AddHandler(jpegLoader);

        m_OriginalBoardImage.LoadFile( m_BoardImageFile , wxBITMAP_TYPE_JPEG);
        m_BoardImage = m_OriginalBoardImage.GetSubBitmap(
                        wxRect(0, 0,
                            m_OriginalBoardImage.GetWidth(),
                            m_OriginalBoardImage.GetHeight())
                        );


    }

    //------------------------------------------------------------------------------
    /*
     * Here we do the actual rendering. I put it in a separate
     * method so that it can work no matter what type of DC
     * (e.g. wxPaintDC or wxClientDC) is used.
     */
    void wxCnChessBoard::RenderDC(wxDC&  dc)
    {
        //wxLogMessage(wxT("DC: w=%u, h=%u"), w,h);

        // draw some text
        //dc.DrawText(wxT("Testing"), 40, 60);

        // draw a rectangle
        //dc.SetBrush( wxColor(255,230,170) ); // blue filling
        //dc.SetPen( wxPen( wxColor(100,180,255), 20 ) ); // 10-pixels-thick pink outline
        //dc.DrawRectangle( 0, 0, w, h );

        // draw a line
        //dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
        //dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle

        if( m_BoardImage.Ok() )
        {
            dc.DrawBitmap( m_BoardImage, 0, 0 );
        }

        // draw a circle
        dc.SetBrush(*wxGREEN_BRUSH); // green filling
        dc.SetPen( wxPen( wxColor(255,0,0), 2 ) ); // 5-pixels-thick red outline
        for(int y =0; y< max_row; ++y){
            for(int x=0; x<max_col; ++x){
                dc.DrawCircle( GetPos( x,  y ), 4 /* radius */ );
            }
        }

        dc.DrawRectangle( m_BoardBound.x,m_BoardBound.y, 4, 4 );

        //wxLogMessage(wxT("offset: x=%f,y=%f"), 15.0f/bw,15.0f/bh);
        //wxLogMessage(wxT("offset: x=%d,y=%d"), bw,bh);



    }

    //------------------------------------------------------------------------------
    void wxCnChessBoard::ResizeChessBoard(wxCoord w,wxCoord  h)
    {
        wxCoord bw, bh;
        bw = m_BoardImage.GetWidth();
        bh = m_BoardImage.GetHeight();

        if( ((bw > bh) && (bw < w)) || ((bh > bw) && (bh < h))  ){
            // 图像需要被放大，重新载入数据。
            //m_BoardImage.GetSubBitmap(wxRect(0, 0, m_OriginalBoardImage.GetWidth(), m_OriginalBoardImage.GetHeight()));
            m_BoardImage = m_OriginalBoardImage.GetSubBitmap(
                            wxRect(0, 0,
                                m_OriginalBoardImage.GetWidth(),
                                m_OriginalBoardImage.GetHeight())
                            );
        }

        m_BoardImage = ScaleBitmap(m_BoardImage, w, h);
        bw = m_BoardImage.GetWidth();
        bh = m_BoardImage.GetHeight();

        SetSize( bw + 5, bh + 5);

        // If use the ChessBoard.jpg as background the offset should be the fallowing
        const float offset_x = 0.041436, offset_y = 0.037221;
        m_BoardOffset = wxPoint(offset_x*bw,offset_y*bh);
        m_BoardBound  = wxPoint( (1-offset_x)*bw, (1-offset_y)*bh);
        m_colsize = (float)(m_BoardBound.x - m_BoardOffset.x)/(float)(max_col-1);
        m_rowsize = (float)(m_BoardBound.y - m_BoardOffset.y)/(float)(max_row-1);

        m_ReSized = false;

        wxLogMessage(wxT("m_BoardBound  (%d,%d)"), m_BoardBound.x, m_BoardBound.y);
        wxLogMessage(wxT("m_BoardOffset (%d,%d)"), m_BoardOffset.x, m_BoardOffset.y);
        wxLogMessage(wxT("ReSized!\n c:%f,r:%f"), m_colsize, m_rowsize);
    }

    //------------------------------------------------------------------------------
    wxPoint wxCnChessBoard::GetPos( int x, int y )
    {
        float fx = (float)x * m_colsize + m_BoardOffset.x;
        float fy = (float)y * m_rowsize + m_BoardOffset.y;

        if( x == 8 && y ==9) {
            wxLogMessage(wxT("GetPos: fx=%f,fy=%f"), fx, fy);
        }

        return wxPoint(fx, fy);
    }

    /*
     * A function to resize the width/height of a wxBitmap proportionally (ONLY SCALE SMALLER!)
     * Author: Danny Battison
     * Contact: gabehabe@gmail.com
     */

    wxBitmap ScaleBitmap(wxBitmap& bmp, int max_width, int max_height) {
        // store the original dimensions in memory. These will be used to determine the scale
        int original_width, original_height;
        original_width = bmp.GetWidth();
        original_height = bmp.GetHeight();

        // This function only scale the bitmap smaller.
        // If Need scale bigger , load the original file, but the file should be big enough
        // to keep the resolution

        // this is our return value
        wxBitmap result;

        int new_width, new_height;

        // if the width is bigger than the height, we should determine a scale for the height
        if (original_width >= original_height && original_width > max_width) {
            float height_scale = (float)max_width / (float)original_width; // determine the scale
            wxImage img = bmp.ConvertToImage(); // create an image of the bitmap
            // now use rescale with our perfect scale dimensions
            new_width  = max_width;
            new_height = (int)(original_height * height_scale);
            result = wxBitmap(img.Rescale( new_width, new_height ));
        } else if (original_height >= original_width && original_height > max_height) {
            // do a similar thing here, only for the width instead of height
            float width_scale = (float)max_height / (float)original_height;
            wxImage img = bmp.ConvertToImage();
            new_width  = (int)(original_width * width_scale);
            new_height = max_height;
            result = wxBitmap(img.Rescale( new_width, new_height ));
        } else { // nothing to do, simply return the original bitmap
            return bmp;
        }

        //SetSize(new_width, new_height);

        // now we need to trim the actual bitmap to the same scale~ otherwise, the graphic itself
        // will be the right size, but the bitmap object will retain the original sizes (which are too big)
        result.SetWidth(new_width); result.SetHeight(new_height);
        return result; // finally, return the resized bitmap
    }
}
