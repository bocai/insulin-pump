// Guide.cpp : implementation file
//

#include "stdafx.h"
#include "胰岛素泵.h"
#include "Guide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuide dialog


CGuide::CGuide(CWnd* pParent /*=NULL*/)
	: CDialog(CGuide::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuide)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGuide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuide)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGuide, CDialog)
	//{{AFX_MSG_MAP(CGuide)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuide message handlers

void CGuide::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
		CRect   rect;   
		
		GetClientRect(&rect);   
		CDC   dcMem;   
		
		dcMem.CreateCompatibleDC(&dc);   
		
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_GUIDE); //IDB_BITMAP1是位图对应的ID 
		
		BITMAP   bitmap;   
		
		bmpBackground.GetBitmap(&bitmap);   
		
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,
			0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
	// Do not call CDialog::OnPaint() for painting messages
}


void CGuide::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
		
	SCROLLINFO scrollinfo;
	
    GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	
	switch (nSBCode) 
		
	{ 
		
	case SB_BOTTOM: 
		
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*10); 
		
		scrollinfo.nPos = scrollinfo.nMax; 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		break; 
		
	case SB_TOP: 
		
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*10); 
		
		scrollinfo.nPos = scrollinfo.nMin; 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		break; 
		
	case SB_LINEUP: 
		
		scrollinfo.nPos -= 1; 
		
		if (scrollinfo.nPos<scrollinfo.nMin)
			
		{ 
			
			scrollinfo.nPos = scrollinfo.nMin; 
			
			break;
			
		} 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		ScrollWindow(0,10); 
		
		break; 
		
	case SB_LINEDOWN:
		
		scrollinfo.nPos += 1; 
		
		if (scrollinfo.nPos>scrollinfo.nMax) 
			
		{ 
			
			scrollinfo.nPos = scrollinfo.nMax; 
			
			break; 
			
		} 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		ScrollWindow(0,-10); 
		
		break; 
		
	case SB_PAGEUP: 
		
		scrollinfo.nPos -= 5; 
		
		if (scrollinfo.nPos<scrollinfo.nMin)
			
		{ 
			
			scrollinfo.nPos = scrollinfo.nMin; 
			
			break; 
			
		} 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		ScrollWindow(0,10*5); 
		
		break; 
		
	case SB_PAGEDOWN: 
		
		scrollinfo.nPos += 5; 
		
		if (scrollinfo.nPos>scrollinfo.nMax) 
			
		{ 
			
			scrollinfo.nPos = scrollinfo.nMax; 
			
			break; 
			
		} 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		ScrollWindow(0,-10*5); 
		
		break; 
		
	case SB_ENDSCROLL: 
		
		// MessageBox("SB_ENDSCROLL"); 
		break; 
		
	case SB_THUMBPOSITION: 
		
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		
		// scrollinfo.nPos = nPos; 
		
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		break; 
		
	case SB_THUMBTRACK: 
		
		ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		
		scrollinfo.nPos = nPos; 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		break; 
		
       }

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
