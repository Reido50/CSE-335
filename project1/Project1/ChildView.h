
// ChildView.h : interface of the CChildView class
//

#include "TowerGame.h"
#pragma once


// CChildView window

/** ChildView */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	/// The Tower Game
	CTowerGame mGame;

	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates

	///  Checks for first draw
	bool mFirstDraw = true; 

	/// Any item we are currently dragging
	std::shared_ptr<CItem> mGrabbedItem;

	/// vector of items  
	std::vector< std::shared_ptr<CItem> > mClickedItems;

public:
	/// afx messages
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLevelLevel0();
	afx_msg void OnLevelLevel1();
	afx_msg void OnLevelLevel2();
	afx_msg void OnLevelLevel3();
};

