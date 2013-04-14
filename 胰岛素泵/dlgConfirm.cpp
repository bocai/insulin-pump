// dlgConfirm.cpp : implementation file
//

#include "stdafx.h"
#include "“»µ∫Àÿ±√.h"
#include "dlgConfirm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdlgConfirm dialog


CdlgConfirm::CdlgConfirm(CWnd* pParent /*=NULL*/)
	: CDialog(CdlgConfirm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdlgConfirm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdlgConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdlgConfirm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdlgConfirm, CDialog)
	//{{AFX_MSG_MAP(CdlgConfirm)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdlgConfirm message handlers

void CdlgConfirm::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CdlgConfirm::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

void CdlgConfirm::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	CRect re;
	
	GetClientRect(&re);//
	dc.FillSolidRect(&re,RGB(238,180,180));//RGB(red,green,blue);
	
	// Do not call CDialog::OnPaint() for painting messages
}
