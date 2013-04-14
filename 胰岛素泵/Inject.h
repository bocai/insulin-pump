#if !defined(AFX_INJECT_H__F25E4252_5517_4913_88BA_B2B24E8D08A1__INCLUDED_)
#define AFX_INJECT_H__F25E4252_5517_4913_88BA_B2B24E8D08A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Inject.h : header file
//

#include "stdafx.h"
#include "“»µ∫Àÿ±√.h"
#include "“»µ∫Àÿ±√Dlg.h"

/////////////////////////////////////////////////////////////////////////////
// CInject dialog

class CInject : public CDialog
{
// Construction
public:
	CInject(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInject)
	enum { IDD = IDD_INJECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInject)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECT_H__F25E4252_5517_4913_88BA_B2B24E8D08A1__INCLUDED_)
