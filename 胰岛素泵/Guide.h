#if !defined(AFX_GUIDE_H__228F0B14_AF07_437E_AF6B_A685545D3053__INCLUDED_)
#define AFX_GUIDE_H__228F0B14_AF07_437E_AF6B_A685545D3053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Guide.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuide dialog

class CGuide : public CDialog
{
// Construction
public:
	CGuide(CWnd* pParent = NULL);   // standard constructor

	

// Dialog Data
	//{{AFX_DATA(CGuide)
	enum { IDD = IDD_Sho };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuide)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGuide)
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDE_H__228F0B14_AF07_437E_AF6B_A685545D3053__INCLUDED_)
