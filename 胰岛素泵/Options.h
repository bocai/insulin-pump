#if !defined(AFX_OPTIONS_H__9F314762_17FB_4ED9_BEB0_1F3D9072228A__INCLUDED_)
#define AFX_OPTIONS_H__9F314762_17FB_4ED9_BEB0_1F3D9072228A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Options.h : header file
//
#include "Guide.h"
/////////////////////////////////////////////////////////////////////////////
// COptions dialog

class COptions : public CDialog
{
// Construction
public:
	COptions(CWnd* pParent = NULL);   // standard constructor
	CGuide guide;

// Dialog Data
	//{{AFX_DATA(COptions)
	enum { IDD = IDD_CHOICE };
	float	m_GetFval;
	int		m_ChooseIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CButtonST m_help;
	CButtonST m_BackBtn;
	CButtonST m_Change;
	CButtonST m_tacitly;
	// Generated message map functions
	//{{AFX_MSG(COptions)
	virtual void OnOK();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnmHELP();
	virtual BOOL OnInitDialog();
	afx_msg void Ontacitly();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnCancel();
	afx_msg void OnRADIO1left();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__9F314762_17FB_4ED9_BEB0_1F3D9072228A__INCLUDED_)
