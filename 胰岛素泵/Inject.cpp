// Inject.cpp : implementation file
//

#include "stdafx.h"
#include "胰岛素泵.h"
#include "Inject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInject dialog


CInject::CInject(CWnd* pParent /*=NULL*/)
	: CDialog(CInject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInject)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInject)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInject, CDialog)
	//{{AFX_MSG_MAP(CInject)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInject message handlers

BOOL CInject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CMyDlg *pWnd = (CMyDlg*)AfxGetMainWnd();//获取主窗口窗口

	CString str;

	str.Format("%.3f",pWnd->inject_volume);//注射量
	str += "单位";
	SetDlgItemText(IDC_Inject_num,str);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInject::OnCancelMode() 
{
	CDialog::OnCancelMode();
	

	// TODO: Add your message handler code here
	
}
