/**
 * \file ChildView.cpp
 *
 * \author Reid Harry
 */

// ChildView.cpp : implementation of the CChildView class
//

#include<memory>
#include "pch.h"
#include "framework.h"
#include "AquaLand.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishStinky.h"
#include "FishSparty.h"
#include "FishAngler.h"
#include "DoubleBufferDC.h"

using namespace std;
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/**
 * Constructor
 */
CChildView::CChildView()
{
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDFISH_STINKYFISH, &CChildView::OnAddfishStinkyfish)
	ON_COMMAND(ID_ADDFISH_S, &CChildView::OnAddfishSpartyfish)
	ON_COMMAND(ID_ADDFISH_ANGLERFISH, &CChildView::OnAddfishAnglerfish)
END_MESSAGE_MAP()



// CChildView message handlers

/**
 * This fuction is called before the windows is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
 * This function is called to draw in the window.
 * 
 * This fuction is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);	// device context for painting
	CDoubleBufferDC dc(&paintDC);	// device context for painting
	Graphics graphics(dc.m_hDC);

	mAquarium.OnDraw(&graphics);
}

/**
 * Add Fish/Beta menu option handler
 */
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Add Fish/Stinky menu option handler
 */
void CChildView::OnAddfishStinkyfish()
{
	auto fish = make_shared<CFishStinky>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Add Fish/Sparty menu option handler
 */
void CChildView::OnAddfishSpartyfish()
{
	auto fish = make_shared<CFishSparty>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Add Fish/Angler menu option handler 
 */
void CChildView::OnAddfishAnglerfish()
{
	auto fish = make_shared<CFishAngler>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		mAquarium.MoveToFront(mGrabbedItem);
	}
}

/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mosue button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}

/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mosue movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
		}
		else
		{
			// When the left button is released, we release the
			// item
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
 * Erase the background
 * 
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}