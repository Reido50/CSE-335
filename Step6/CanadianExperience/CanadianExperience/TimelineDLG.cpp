// TimelineDLG.cpp : implementation file
//

#include "pch.h"
#include "CanadianExperience.h"
#include "TimelineDLG.h"
#include "afxdialogex.h"


// CTimelineDLG dialog

IMPLEMENT_DYNAMIC(CTimelineDLG, CDialog)

CTimelineDLG::CTimelineDLG(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TIMELINEDLG, pParent)
	, mNumFrames(0)
	, mFrameRate(0)
{

}

CTimelineDLG::~CTimelineDLG()
{
}

/**
 * Pass a timeline object to this dialog box class.
 * \param timeline The timeline object.
 */
void CTimelineDLG::SetTimeline(CTimeline* timeline)
{
	mTimeline = timeline;
	mNumFrames = mTimeline->GetNumFrames();
	mFrameRate = mTimeline->GetFrameRate();
}

/**
* Transfer dialog values to the Timeline object
*/
void CTimelineDLG::Take()
{
	mTimeline->SetNumFrames(mNumFrames);
	mTimeline->SetFrameRate(mFrameRate);
}

void CTimelineDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMFRAMES, mNumFrames);
	DDV_MinMaxInt(pDX, mNumFrames, 10, 10000);
	DDX_Text(pDX, IDC_FRAMERATE, mFrameRate);
	DDV_MinMaxInt(pDX, mFrameRate, 1, 60);
}


BEGIN_MESSAGE_MAP(CTimelineDLG, CDialog)
END_MESSAGE_MAP()


// CTimelineDLG message handlers
