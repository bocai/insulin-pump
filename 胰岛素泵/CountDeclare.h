#if !defined(AFX_COUNTDECLARE_H__6E68AD6F_A73C_4D4E_8BD1_A96259002907__INCLUDED_)
#define AFX_COUNTDECLARE_H__6E68AD6F_A73C_4D4E_8BD1_A96259002907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CountDeclare.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountDeclare dialog

class CCountDeclare : public CDialog
{
// Construction
public:
	CCountDeclare(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCountDeclare)
	enum { IDD = IDD_Declare };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountDeclare)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCountDeclare)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTDECLARE_H__6E68AD6F_A73C_4D4E_8BD1_A96259002907__INCLUDED_)
