// CountDeclare.cpp : implementation file
//

#include "stdafx.h"
#include "“»µ∫Àÿ±√.h"
#include "CountDeclare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountDeclare dialog


CCountDeclare::CCountDeclare(CWnd* pParent /*=NULL*/)
	: CDialog(CCountDeclare::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountDeclare)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCountDeclare::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountDeclare)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCountDeclare, CDialog)
	//{{AFX_MSG_MAP(CCountDeclare)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountDeclare message handlers
