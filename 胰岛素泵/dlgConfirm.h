#if !defined(AFX_DLGCONFIRM_H__CBBF4B89_D6AA_4455_A8E6_02003F00A8BD__INCLUDED_)
#define AFX_DLGCONFIRM_H__CBBF4B89_D6AA_4455_A8E6_02003F00A8BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgConfirm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdlgConfirm dialog

class CdlgConfirm : public CDialog
{
// Construction
public:
	CdlgConfirm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdlgConfirm)
	enum { IDD = IDD_DLGconfirm };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdlgConfirm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CdlgConfirm)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIRM_H__CBBF4B89_D6AA_4455_A8E6_02003F00A8BD__INCLUDED_)
