#if !defined(AFX_EXPLAIN_H__5165124A_6961_4CB7_9456_8F03AB6AAACB__INCLUDED_)
#define AFX_EXPLAIN_H__5165124A_6961_4CB7_9456_8F03AB6AAACB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// explain.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cexplain dialog

class Cexplain : public CDialog
{
// Construction
public:
	Cexplain(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cexplain)
	enum { IDD = IDD_EXPLIAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cexplain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cexplain)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLAIN_H__5165124A_6961_4CB7_9456_8F03AB6AAACB__INCLUDED_)
