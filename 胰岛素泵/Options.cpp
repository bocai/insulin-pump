// Options.cpp : implementation file
//

#include "stdafx.h"
#include "胰岛素泵.h"
#include "Options.h"
#include "胰岛素泵Dlg.h"
#include "Guide.h"
#include "CountDeclare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptions dialog


COptions::COptions(CWnd* pParent /*=NULL*/)
	: CDialog(COptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptions)
	m_GetFval = 0.0f;
	m_ChooseIndex = -1;
	//}}AFX_DATA_INIT

}


void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptions)
	DDX_Text(pDX, IDC_GetDataText, m_GetFval);
	DDV_MinMaxFloat(pDX, m_GetFval, 0.f, 100.f);
	DDX_Radio(pDX, IDC_RADIO1left, m_ChooseIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	//{{AFX_MSG_MAP(COptions)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_m_HELP, OnmHELP)
	ON_BN_CLICKED(IDC_tacitly, Ontacitly)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_RADIO1left, OnRADIO1left)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
BOOL CMyDlg::WriteToFile(CMyDlg *pWnd)
{
	fstream fp;
	fp.open("InsulinData.dat",fstream::out);
	
	if(!fp)
	{
		AfxMessageBox("打开文件失败！");
		return FALSE;
	}
	else
	{
		fp << pWnd->insulin_residue;fp << "\n";
		fp << pWnd->dose_for_oneday;fp << "\n";//
		fp << pWnd->_24HourBase;    fp << "\n";
		fp << dose_before_meal.breakfast;fp << "\n";
		fp << dose_before_meal.lunch;fp << "\n";
		fp << dose_before_meal.supper;fp << "\n ";
		
		fp.close();
	}
	return TRUE;
}
// COptions message handlers

void COptions::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	//根据用户选择的设置输入的值
	//	float	insulin_residue;		//  胰岛素剩余剂量
	//	float   dose_for_oneday;        //  一天注入胰岛素的剂量
	//	float   start_found_dose;		//  胰岛素开始基础量
	CString str;
	str.Format("%.3f",m_GetFval);
	CMyDlg *pWnd = (CMyDlg*)AfxGetMainWnd();//AfxGetApp();//获取父窗口
	
	switch(m_ChooseIndex)
	{
	case 0:
		pWnd->insulin_residue += m_GetFval;//  添加胰岛素剩余剂量
		str.Format("%.3f",pWnd->insulin_residue);
		SetDlgItemText(IDC_INSULINleft,str);
		
		break;
	case 1:
		pWnd->dose_for_oneday = m_GetFval;//  一天注入胰岛素的剂量
		pWnd->CountDose();
		SetDlgItemText(IDC_ForDay,str);
		
		pWnd->SetDlgItemText(IDC_mBISIC,str);
		break;
	case 2:
		pWnd->_24HourBase = pWnd->start_found_dose = m_GetFval;
		SetDlgItemText(IDC_DAYBASIC,str);//  胰岛素开始基础量
		
		break;
	case 3:
		pWnd->dose_before_meal.breakfast = m_GetFval;
		SetDlgItemText(IDC_sBreakfast,str);
		
		break;
	case 4://MessageBox("设置4！");
		pWnd->dose_before_meal.lunch = m_GetFval;
		SetDlgItemText(IDC_sLunch,str);
		
		break;
	case 5:
		pWnd->dose_before_meal.supper = m_GetFval;
		SetDlgItemText(IDC_sSupper,str);
		
		break;
	case 6:
		if(m_GetFval < 1.0)
			MessageBox("请输入一个大于 1 的数字!");
		else
		{
			pWnd->Time_BloodSugar = (int)m_GetFval * 60 * 1000; 
			if(pWnd->isStart == TRUE)
			{
				pWnd->KillTimer(T_CHECKBLOOD);
				pWnd->SetTimer(T_CHECKBLOOD,pWnd->Time_BloodSugar,NULL);
			}
			str.Format("%d",(int)m_GetFval);
			SetDlgItemText(IDC_Time_Interval,str);
		//MessageBox("设置成功!!");
		}
		break;
	default: 
		MessageBox("请选择一个选项设置!!");
	}
	
	if(m_ChooseIndex >= 0 && m_ChooseIndex < 6)
	{
	//	pWnd->WriteToFile(pWnd);//按"返回"再写入
		UpdateData(FALSE);
		SetDlgItemText(IDC_GetDataText,"");
		GetDlgItem(IDC_GetDataText)->SetFocus();
	}
	//	CDialog::OnOK();//不调用
}


void COptions::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
		
/*	SCROLLINFO scrollinfo;
	
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
		
		 ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		
		 scrollinfo.nPos = nPos; 
		
		 SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		break; 
		
	case SB_THUMBTRACK: 
		
		ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		
		scrollinfo.nPos = nPos; 
		
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		
		break; 
		
       }
*/


      int nCurpos,nMin,nMax,nThumbWidth;
 
       SCROLLINFO siInfo;
 
       GetScrollInfo(SB_VERT,&siInfo);
 
       nCurpos = siInfo.nPos;
 
       nMin = siInfo.nMin;
 
       nMax = siInfo.nMax;
 
       nThumbWidth = siInfo.nPage;
 
       switch (nSBCode)
 
       {
 
       case SB_THUMBTRACK:
 
              nCurpos = GetScrollPos(SB_VERT);
 
              ScrollWindow(0,-(nPos-nCurpos));
 
              SetScrollPos(SB_VERT,nPos);     

       break;
 
 
 
       case SB_LINELEFT:
 
              nCurpos = GetScrollPos(SB_VERT);
 
              SetScrollPos(SB_VERT,nCurpos-1);
 
              if (nCurpos !=0)
 
                     ScrollWindow(0,1);
 
       break;
 
       case SB_LINERIGHT:
 
              nCurpos = GetScrollPos(SB_VERT);
 
              SetScrollPos(SB_VERT,nCurpos+1);
 
              if (nCurpos+nThumbWidth < nMax)
 
                     ScrollWindow(0,-1);      

       break;
 
       case SB_PAGELEFT: //在滚动块的上方空白滚动区域单击,增量为6
 
              SetScrollPos(SB_VERT,nCurpos-6);
 
              if (nCurpos+nThumbWidth >0)
 
                     ScrollWindow(0,6);
 
       break;
 
       case SB_PAGERIGHT: //在滚动块的下方空白滚动区域单击,增量为6
 
              SetScrollPos(SB_VERT,nCurpos+6);
 
              if (nCurpos+nThumbWidth < nMax)
 
                     ScrollWindow(0,-6);
 
       break;
 
       case SB_LEFT:      

              SetScrollPos(SB_VERT,0);
 
              ScrollWindow(0,nCurpos);
 
       break;
 
       }     


	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void COptions::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect re;
	
	GetClientRect(&re);//
	dc.FillSolidRect(&re,RGB(100,149,237));//(30,144,255));//RGB(red,green,blue);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void COptions::OnmHELP() 
{
	// TODO: Add your control notification handler code here
		//初始每日胰岛素总量计算说明
	MessageBox("糖尿病医生会教你怎么改变基础率来适应不停变化着的胰岛素需要,以下仅供参考!\
	a.根据体重计算（尚未使用胰岛素）一日总量＝体重kg×0.44 b.根据用泵前的用量计算\
	一日总量＝用泵前胰岛素用量×（80%--100%）c.50%基础量：基础率总量\
	24=每小时基础量50%餐前量：40%早餐，30%中餐，30%晚餐。----By Bocai");

}

BOOL COptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	SetScrollRange(SB_VERT,0,190,TRUE);//限定滚动范围
	SetWindowPos(&wndTop,0,0,380,260,SWP_SHOWWINDOW | SWP_NOMOVE);//SWP_NOMOVE);//重设窗口大小

	CMyDlg *pWnd = (CMyDlg*)AfxGetMainWnd();//AfxGetApp();//获取主窗口窗口

	/****** 显示各个控件对应的值 ******/
	CString str;
	
	if(pWnd->insulin_residue <= 0)
		str.Format("%.3f",0.0f);
	else
		str.Format("%.3f",pWnd->insulin_residue);
	SetDlgItemText(IDC_INSULINleft,str);
	
	if(pWnd->dose_for_oneday <= 0)
		str.Format("%.3f",0.0f);
	else
		str.Format("%.3f",pWnd->dose_for_oneday);
	SetDlgItemText(IDC_ForDay,str);

	if(pWnd->_24HourBase <= 0)
		str.Format("%.3f",0.0f);
	else
		str.Format("%.3f",pWnd->_24HourBase);
	SetDlgItemText(IDC_DAYBASIC,str);

	if(pWnd->dose_before_meal.breakfast <= 0)
		str.Format("%.3f",0.0f);
	else
		str.Format("%.3f",pWnd->dose_before_meal.breakfast);
	SetDlgItemText(IDC_sBreakfast,str);

	if(pWnd->dose_before_meal.lunch <= 0)
		str.Format("%.3f",0.0f);
	else
		str.Format("%.3f",pWnd->dose_before_meal.lunch);
	SetDlgItemText(IDC_sLunch,str);

	if(pWnd->dose_before_meal.supper <= 0)
		str.Format("%.3f",0.0f);
	else
		str.Format("%.3f",pWnd->dose_before_meal.supper);
	SetDlgItemText(IDC_sSupper,str);

	str.Format("%d",pWnd->Time_BloodSugar/60/1000);//检测时间间隔
	SetDlgItemText(IDC_Time_Interval,str);

	/*******  按钮的美化    *********/
	m_help.SubclassDlgItem(IDC_m_HELP,this);
	m_help.SetIcon(IDI_ICONhelp);
	
	m_BackBtn.SubclassDlgItem(IDCANCEL,this);
	m_BackBtn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(255,0,0));//背景
	m_BackBtn.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(255,70,0));
//	m_BackBtn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);

	m_Change.SubclassDlgItem(IDOK,this);
	m_Change.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0,0,255));//背景
	m_Change.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(255,0,0));
//	m_Change.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	
	m_tacitly.SubclassDlgItem(IDC_tacitly,this);
	m_tacitly.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(64,224,209));//148,0,211));
	GetDlgItem(IDC_GetDataText)->SetFocus();
	
	return FALSE;//TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//    还原默认值
void COptions::Ontacitly() 
{
	// TODO: Add your control notification handler code here
	
	CMyDlg *pWnd = (CMyDlg*)AfxGetMainWnd();//AfxGetApp();
	if(pWnd->dose_for_oneday > 0.0f)
	{
		CString str;
		
		pWnd->CountDose();	str.Format("%.3f",pWnd->_24HourBase);  //%50          
		SetDlgItemText(IDC_DAYBASIC,str);
		
		pWnd->dose_before_meal.breakfast = pWnd->dose_for_oneday * 20.0f / 100.0f;//%20
		str.Format("%.3f",pWnd->dose_before_meal.breakfast);
		SetDlgItemText(IDC_sBreakfast,str);
		
		pWnd->dose_before_meal.lunch = pWnd->dose_for_oneday * 15.0f / 100.0f;//%15
		str.Format("%.3f",pWnd->dose_before_meal.lunch);
		SetDlgItemText(IDC_sLunch,str);
		
		pWnd->dose_before_meal.supper = pWnd->dose_for_oneday * 15.0f / 100.0f;//%15
		str.Format("%.3f",pWnd->dose_before_meal.supper);
		SetDlgItemText(IDC_sSupper,str);
		
		pWnd->Time_BloodSugar = 120 * 1000;
		str.Format("%d",2);
		SetDlgItemText(IDC_Time_Interval,str);
		if(pWnd->WriteToFile(pWnd) == TRUE)
			MessageBox("设置成功！");
	}
	else
		MessageBox("请先设置\"一日总量\"!!!");
}
//    鼠标滚轮转动
BOOL COptions::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
       SCROLLINFO siInfo;                       //定义滚动信息对象
 
       GetScrollInfo(SB_VERT,&siInfo);          //获取滚动信息
 
       int nMin,nMax,nThumbWidth;                           

       nMin = siInfo.nMin;                     //获取滚动最小值
 
       nMax = siInfo.nMax;
 
       nThumbWidth = siInfo.nPage;             //获取滚动块大小
 
       int nPos = GetScrollPos(SB_VERT);       //获取垂直滚动条的当前位置
 
       if (zDelta > 0)                         //向上滚动
 
       {
 
              if (nPos == 0)
 
                     return TRUE;
 
              SetScrollPos(SB_VERT,nPos-7);        //设置滚动条位置
 
              ScrollWindow(0,7);                   //向上滚动窗口
 
       }
       else
       {
              if ((nPos+nThumbWidth >= nMax))
 
                     return TRUE;
 
              SetScrollPos(SB_VERT,nPos+7);
 
              ScrollWindow(0,-7);

       }

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void COptions::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void COptions::OnRADIO1left() 
{
	// TODO: Add your control notification handler code here
//	SetDlgItemText(IDOK,"添加");
}
