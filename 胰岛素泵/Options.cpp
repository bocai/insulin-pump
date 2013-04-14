// Options.cpp : implementation file
//

#include "stdafx.h"
#include "�ȵ��ر�.h"
#include "Options.h"
#include "�ȵ��ر�Dlg.h"
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
		AfxMessageBox("���ļ�ʧ�ܣ�");
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
	//�����û�ѡ������������ֵ
	//	float	insulin_residue;		//  �ȵ���ʣ�����
	//	float   dose_for_oneday;        //  һ��ע���ȵ��صļ���
	//	float   start_found_dose;		//  �ȵ��ؿ�ʼ������
	CString str;
	str.Format("%.3f",m_GetFval);
	CMyDlg *pWnd = (CMyDlg*)AfxGetMainWnd();//AfxGetApp();//��ȡ������
	
	switch(m_ChooseIndex)
	{
	case 0:
		pWnd->insulin_residue += m_GetFval;//  ����ȵ���ʣ�����
		str.Format("%.3f",pWnd->insulin_residue);
		SetDlgItemText(IDC_INSULINleft,str);
		
		break;
	case 1:
		pWnd->dose_for_oneday = m_GetFval;//  һ��ע���ȵ��صļ���
		pWnd->CountDose();
		SetDlgItemText(IDC_ForDay,str);
		
		pWnd->SetDlgItemText(IDC_mBISIC,str);
		break;
	case 2:
		pWnd->_24HourBase = pWnd->start_found_dose = m_GetFval;
		SetDlgItemText(IDC_DAYBASIC,str);//  �ȵ��ؿ�ʼ������
		
		break;
	case 3:
		pWnd->dose_before_meal.breakfast = m_GetFval;
		SetDlgItemText(IDC_sBreakfast,str);
		
		break;
	case 4://MessageBox("����4��");
		pWnd->dose_before_meal.lunch = m_GetFval;
		SetDlgItemText(IDC_sLunch,str);
		
		break;
	case 5:
		pWnd->dose_before_meal.supper = m_GetFval;
		SetDlgItemText(IDC_sSupper,str);
		
		break;
	case 6:
		if(m_GetFval < 1.0)
			MessageBox("������һ������ 1 ������!");
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
		//MessageBox("���óɹ�!!");
		}
		break;
	default: 
		MessageBox("��ѡ��һ��ѡ������!!");
	}
	
	if(m_ChooseIndex >= 0 && m_ChooseIndex < 6)
	{
	//	pWnd->WriteToFile(pWnd);//��"����"��д��
		UpdateData(FALSE);
		SetDlgItemText(IDC_GetDataText,"");
		GetDlgItem(IDC_GetDataText)->SetFocus();
	}
	//	CDialog::OnOK();//������
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
 
       case SB_PAGELEFT: //�ڹ�������Ϸ��հ׹������򵥻�,����Ϊ6
 
              SetScrollPos(SB_VERT,nCurpos-6);
 
              if (nCurpos+nThumbWidth >0)
 
                     ScrollWindow(0,6);
 
       break;
 
       case SB_PAGERIGHT: //�ڹ�������·��հ׹������򵥻�,����Ϊ6
 
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
		//��ʼÿ���ȵ�����������˵��
	MessageBox("����ҽ���������ô�ı����������Ӧ��ͣ�仯�ŵ��ȵ�����Ҫ,���½����ο�!\
	a.�������ؼ��㣨��δʹ���ȵ��أ�һ������������kg��0.44 b.�����ñ�ǰ����������\
	һ���������ñ�ǰ�ȵ�����������80%--100%��c.50%������������������\
	24=ÿСʱ������50%��ǰ����40%��ͣ�30%�вͣ�30%��͡�----By Bocai");

}

BOOL COptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	SetScrollRange(SB_VERT,0,190,TRUE);//�޶�������Χ
	SetWindowPos(&wndTop,0,0,380,260,SWP_SHOWWINDOW | SWP_NOMOVE);//SWP_NOMOVE);//���贰�ڴ�С

	CMyDlg *pWnd = (CMyDlg*)AfxGetMainWnd();//AfxGetApp();//��ȡ�����ڴ���

	/****** ��ʾ�����ؼ���Ӧ��ֵ ******/
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

	str.Format("%d",pWnd->Time_BloodSugar/60/1000);//���ʱ����
	SetDlgItemText(IDC_Time_Interval,str);

	/*******  ��ť������    *********/
	m_help.SubclassDlgItem(IDC_m_HELP,this);
	m_help.SetIcon(IDI_ICONhelp);
	
	m_BackBtn.SubclassDlgItem(IDCANCEL,this);
	m_BackBtn.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(255,0,0));//����
	m_BackBtn.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(255,70,0));
//	m_BackBtn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);

	m_Change.SubclassDlgItem(IDOK,this);
	m_Change.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0,0,255));//����
	m_Change.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(255,0,0));
//	m_Change.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	
	m_tacitly.SubclassDlgItem(IDC_tacitly,this);
	m_tacitly.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(64,224,209));//148,0,211));
	GetDlgItem(IDC_GetDataText)->SetFocus();
	
	return FALSE;//TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//    ��ԭĬ��ֵ
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
			MessageBox("���óɹ���");
	}
	else
		MessageBox("��������\"һ������\"!!!");
}
//    ������ת��
BOOL COptions::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
       SCROLLINFO siInfo;                       //���������Ϣ����
 
       GetScrollInfo(SB_VERT,&siInfo);          //��ȡ������Ϣ
 
       int nMin,nMax,nThumbWidth;                           

       nMin = siInfo.nMin;                     //��ȡ������Сֵ
 
       nMax = siInfo.nMax;
 
       nThumbWidth = siInfo.nPage;             //��ȡ�������С
 
       int nPos = GetScrollPos(SB_VERT);       //��ȡ��ֱ�������ĵ�ǰλ��
 
       if (zDelta > 0)                         //���Ϲ���
 
       {
 
              if (nPos == 0)
 
                     return TRUE;
 
              SetScrollPos(SB_VERT,nPos-7);        //���ù�����λ��
 
              ScrollWindow(0,7);                   //���Ϲ�������
 
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
//	SetDlgItemText(IDOK,"���");
}
