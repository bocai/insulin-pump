// explain.cpp : implementation file
//

#include "stdafx.h"
#include "胰岛素泵.h"
#include "explain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cexplain dialog


Cexplain::Cexplain(CWnd* pParent /*=NULL*/)
	: CDialog(Cexplain::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cexplain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cexplain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cexplain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cexplain, CDialog)
	//{{AFX_MSG_MAP(Cexplain)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cexplain message handlers

void Cexplain::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
//      CPaintDC dc(this); // device context for painting

       CRect   rect;   

       GetClientRect(&rect);   

       CDC   dcMem;   

       dcMem.CreateCompatibleDC(&dc);   

       CBitmap   bmpBackground;   
									
       bmpBackground.LoadBitmap(IDB_BITMAPexplain); //IDB_BITMAP是你自己的图对应的ID 

       BITMAP   bitmap;   

       bmpBackground.GetBitmap(&bitmap);   

       CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   

       dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,
		   0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
	// Do not call CDialog::OnPaint() for painting messages
}
