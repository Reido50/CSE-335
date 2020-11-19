#pragma once

#include "Timeline.h"

// CTimelineDLG dialog

/** Class for handling the timeline dialog box */
class CTimelineDLG : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDLG)

public:
	CTimelineDLG(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTimelineDLG();

	void SetTimeline(CTimeline* timeline);

	void Take();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	/// Number of frames entered by the user in the DLG
	int mNumFrames;

	/// The timeline we are editing
	CTimeline* mTimeline = nullptr;

	/// Frame rate entered by the user in the DLG
	int mFrameRate;
};
