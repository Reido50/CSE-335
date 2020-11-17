/**
 * \file ViewTimeline.cpp
 *
 * \author Reid Harry
 */


#include "pch.h"
#include <sstream>
#include <algorithm>
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include "Timeline.h"
#include "MainFrm.h"
#include "Picture.h"
#include "Actor.h"

using namespace std;
using namespace Gdiplus;

/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;

IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{
    mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
    assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}




/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
    // Get the timeline
    CTimeline* timeline = GetPicture()->GetTimeline();

    // Set the scroll system correctly
    CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
    SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    Pen pen(Color(0, 0, 0), 1);

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 10);

    SolidBrush brush(Color(0, 0, 0));

    CRect rect;
    GetClientRect(&rect);
    int hit = rect.Height();
    int wid = rect.Width();

    for (int frame = 0; frame <= timeline->GetNumFrames(); frame++)
    {
        bool onSecond = (frame % timeline->GetFrameRate()) == 0;
        int tickLength = TickShort;
        int x = BorderLeft + TickSpacing * frame;

        if (onSecond)
        {
            tickLength = TickLong;

            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << frame / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            RectF size;
            PointF origin(0.0f, 0.0f);
            graphics.MeasureString(wstr.c_str(), wstr.size(),
                &font, origin, &size);
            origin = origin + PointF(x, BorderTop + tickLength) + PointF(-size.Width/2, 0);
            graphics.DrawString(wstr.c_str(),  // String to draw
                -1,         // String length, -1 means it figures it out 
                &font,      // The font to use
                origin,     // Where to draw
                &brush);    // The brush to draw the text with
        }

        graphics.DrawLine(&pen, 
            x, BorderTop,                   // Point 1
            x, BorderTop + tickLength);     // Point 2

    }

    graphics.DrawImage(mPointer.get(), BorderLeft + TickSpacing * timeline->GetCurrentFrame() - mPointer->GetWidth() / 2, BorderTop,
        mPointer->GetWidth(), mPointer->GetHeight());
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle the Edit>Set Keyframe menu option */
 void CViewTimeline::OnEditSetkeyframe()
 {
     for (auto actor : *GetPicture())
     {
         actor->SetKeyframe();
     }
 }


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
     // TODO: Add your command handler code here
 }


 /**
 * Force an update of this window when the picture changes
 */
 void CViewTimeline::UpdateObserver()
 {
     Invalidate();
     UpdateWindow();
 }


 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
     ON_WM_LBUTTONDOWN()
     ON_WM_MOUSEMOVE()
 END_MESSAGE_MAP()

 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     int x = point.x;

     // Get the timeline
     CTimeline* timeline = GetPicture()->GetTimeline();
     int pointerX = (int)(timeline->GetCurrentTime() *
         timeline->GetFrameRate() * TickSpacing + BorderLeft);

     mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
         x <= pointerX + (int)mPointer->GetWidth() / 2;

     __super::OnLButtonDown(nFlags, point);
 }


 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     double x = (double)point.x;

     if (mMovingPointer && nFlags & MK_LBUTTON)
     {
         double time = (((x - (double)BorderLeft) / (double)GetPicture()->GetTimeline()->GetFrameRate()) / (double)TickSpacing);

         // Make sure the user cannot move the pointer past 0 or the duration
         time = max(time, 0.0);
         time = min(time, (double)GetPicture()->GetTimeline()->GetDuration());

         GetPicture()->SetAnimationTime(time);
     }
     else
     {
         mMovingPointer = false;
     }

     

     __super::OnMouseMove(nFlags, point);
 }
