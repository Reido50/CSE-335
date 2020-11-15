
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "TileBuilding.h"
#include "TileGrass.h"
#include "TileRoad.h"
#include "TileTrees.h"
#include "DoubleBufferDC.h"
#include "TowerGame.h"
#include "Item.h"
#include "TowerEight.h"
#include "TowerRing.h"
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "TowerVisitor.h"
#include "TowerCopyVisitor.h"
#include "MenuPalette.h"
#include <iostream>
#include <algorithm>
#include <list>
#include "Balloon.h"
#include "TileRoad.h"
#include "Announcer.h"
#include "Frisbee.h"
#include "CountTowerBomb.h"
#include "FrisbeeAngleSetter.h"
#include "Dart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

// CChildView

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Clicking offset for images
const int ImageClickOffset = 32;

/// Default Constructor
CChildView::CChildView()
{
}

/// Destructor
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
END_MESSAGE_MAP()



// CChildView message handlers

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

/// Draws the window and contents
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		 * Initialize the elapsed time system
		 */
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);

		// Loading level 1 by default
		mGame.Load(L"../levels/level1.xml");
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mGame.Update(elapsed);
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());
}

/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
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
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}

/** Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);

	double x = point.x;
	double y = point.y;

	mGame.ConvertToVirtualPixels(x, y);
	mClickedItems = mGame.HitTestModified(x, y);

	for (auto each_item : mClickedItems)
	{
		/// Only the towers will be visited
		CTowerVisitor visitor(&mGame);
		each_item->Accept(&visitor);
	}
}

/** Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	double x = point.x;
	double y = point.y;

	mGame.ConvertToVirtualPixels(x, y);
	mGrabbedItem = mGame.HitTest(x - ImageClickOffset, y - ImageClickOffset);

	if (mGrabbedItem != nullptr)
	{
		// Checking if tower is on map, placed, and hit
		CTowerVisitor towerVisitor = CTowerVisitor(&mGame);
		mGrabbedItem->Accept(&towerVisitor);
		bool res = towerVisitor.HitTest(x - ImageClickOffset, y - ImageClickOffset);

		if (!res)
		{
			/// instantiate visitor and retrieve type of tower
			CTowerCopyVisitor visitor;
			mGrabbedItem->Accept(&visitor);
			auto type = visitor.TowerButton();
			/// returns a pointer to the tower
			mGrabbedItem = mGame.Validate(type);
		}
	}
}

/** Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		mGame.MoveToFront(mGrabbedItem);
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			double x = point.x;
			double y = point.y;

			mGame.ConvertToVirtualPixels(x, y);
			mGrabbedItem->SetLocation(x - 32, y - 32);
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}

	CFrisbeeAngleSetter visitor(&point);
	mGame.Accept(&visitor);
}

/**
 * Handler for level 0 button
 */
void CChildView::OnLevelLevel0()
{
	mGame.Load(L"../levels/level0.xml");
}

/**
 * Handler for level 1 button
 */
void CChildView::OnLevelLevel1()
{
	mGame.Load(L"../levels/level1.xml");
}

/**
 * Handler for level 2 button
 */
void CChildView::OnLevelLevel2()
{
	mGame.Load(L"../levels/level2.xml");
}

/**
 * Handler for level 3 button
 */
void CChildView::OnLevelLevel3()
{
	mGame.Load(L"../levels/level3.xml");
}
