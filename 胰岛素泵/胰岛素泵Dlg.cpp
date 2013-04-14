// 胰岛素泵Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "胰岛素泵.h"
#include "胰岛素泵Dlg.h"
#include "Options.h"
#include "explain.h"
#include "Inject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon			 = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_EQuantity		 = 20;      //电量初始值，实际中需要检测
	blood_sugar		 = 0;		//  存储当前测得血糖值的变量
	insulin_residue  = 0;		//  胰岛素剩余剂量
	dose_for_oneday  = 0;       //  一天注入胰岛素的剂量
	start_found_dose = 0;		//  胰岛素开始基础量
	RandLength		 = 15;        //模拟血糖变化产生随机数的范围
	isStart			 = FALSE;
	am_inject        = TRUE; //是否注射
	Time_BloodSugar	 = 1000 * 60;//检测血糖时间的间隔(秒)

	bsis.other_time_min       = 4.3f;		// 其他时间血糖上界
	bsis.other_time_max		  = 7.8f;		// 其他时间血糖下界
	bsis.IndexBeforeMeal_min  = 3.9f;	// 饭前血糖控制目标指数下界
	bsis.IndexBeforeMeal_max  = 6.2f;	// 饭前血糖控制目标指数上届
	bsis.IndexAfterMeal_max	  = 9.0f;	// 饭后2小时血糖控制目标指数上界
	bsis.IndexBeforeSleep_min = 5.6f;	// 睡前血糖控制目标指数下界
	bsis.IndexBeforeSleep_max = 7.8f;	// 睡前血糖控制目标指数上界
	bsis.IndexAt_3AM_min      = 5.0f;	// 凌晨三点后血糖空中目标指数下界
//	memcpy(&addedDose,0,sizeof(ADose));     // ADose addedDose;   胰岛素补充剂量
//	memcpy(&dose_before_meal,0,sizeof(DBM));//DBM 指向餐前胰岛素注入剂量
	_24HourBase                = -1.0f;//这里设置为-1是为了识别用户是否
	dose_before_meal.breakfast = -1.0f; //都对这些变量设置好了
	dose_before_meal.lunch     = -1.0f;
	dose_before_meal.supper    = -1.0f;
	inject_volume              = 0.f; //餐前注射量

	Max_range = 0.0f;
	Min_range = 0.0f;
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_ElectricQuantity, m_ElectricQuantity);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPTION, OnOption)
	ON_BN_CLICKED(IDC_EXPLAINbtn, OnEXPLAINbtn)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_Pre_Breafast, OnPreBreafast)
	ON_BN_CLICKED(IDC_Pre_Lunch, OnPreLunch)
	ON_BN_CLICKED(IDC_Pre_Supper, OnPreSupper)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_begin.SubclassDlgItem(IDC_START,this);//开始按钮的设置
	//	m_begin.SetIcon(IDI_ICONok,IDR_MAINFRAME);
	m_begin.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(239,130,238));//背景
	m_begin.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(124,250,0));
	m_begin.SetShade(CShadeButtonST::SHS_HARDBUMP);

//	m_Pause.SubclassDlgItem(IDC_PAUSE,this);
//	m_Pause.SetShade(CShadeButtonST::SHS_HARDBUMP);
	
	m_exit.SubclassDlgItem(IDCANCEL,this);
	m_exit.SetShade(CShadeButtonST::SHS_SOFTBUMP);
	
	m_BtnOptions.SubclassDlgItem(IDC_OPTION,this);
	m_BtnOptions.SetIcon(IDI_ICONOpt);
	m_BtnOptions.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(239,130,238));//背景
	m_BtnOptions.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(124,250,0));
	m_BtnOptions.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);

	m_lamp.SubclassDlgItem(IDC_lamp,this);
	m_lamp.SetIcon(IDI_Lamp1);//设置开始的灯
	m_lamp.EnableWindow(FALSE);//灭//m_lamp.ShowWindow(SW_HIDE);
	
	m_BtnExplain.SubclassDlgItem(IDC_EXPLAINbtn,this);
	m_BtnExplain.SetIcon(IDI_ICONAbout,IDI_ICONhelp);

	m_ElectricQuantity.SetRange(0,m_EQuantity);
	m_ElectricQuantity.SetStep(1);
	m_ElectricQuantity.SetPos(m_EQuantity);

	crrentT = crrentT.GetCurrentTime();
	CString st = "时间：";
	st += crrentT.Format("%H:%M:%S");
	SetDlgItemText(IDC_SHOWTIME,st);
	SetDlgItemText(IDC_SCURRENT,"按\"开始\"");

	if(ReadFile(this) == FALSE)
	{
		cout << "读取失败";
		return FALSE;
	}
	if(insulin_residue < 0)
	{
		insulin_residue = 0;
		SetDlgItemText(IDC_DoseLeft,"0");
	//	MessageBox("余量不足");
	}
	CountDose();
	st.Format("%.3f",insulin_residue);
	st += "单位";
	SetDlgItemText(IDC_DoseLeft,st);
	
	st.Format("%.3f",_24HourBase);//assertion
	SetDlgItemText(IDC_mBISIC,st);

	GetTargetRange();//当前目标范围
	ShowNowRange();
	SetTimer(T_SHOWTIME,1000,NULL);//用于当前时间显示
	SetTimer(T_ELECTRIC,1000*10,NULL); //电量检测

	CRect rect;  
	GetClientRect(&rect);     //取客户区大小
	Old.x=rect.right-rect.left;
	Old.y=rect.bottom-rect.top;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	
		CPaintDC dc(this); // device context for painting
		CRect   rect;   
		
		GetClientRect(&rect);  
		dc.FillSolidRect(&rect,RGB(64,224,209));//RGB(red,green,blue);填充背景，或者使用下面的代码用图片填充
/*		CDC   dcMem;   
		
		dcMem.CreateCompatibleDC(&dc);   
		
		CBitmap   bmpBackground;   	//加载位图（背景）
		bmpBackground.LoadBitmap(IDB_BKgroud); //是位图对应的ID 
		
		BITMAP   bitmap;   
		
		bmpBackground.GetBitmap(&bitmap);   
		
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,
			0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 

  */
	
		CDialog::OnPaint();

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CdlgConfirm Cdlg;
	
	if(IDOK == Cdlg.DoModal())//弹出（模态）对话框，确定关机？
	{
		WriteToFile(this);
		CDialog::OnCancel();
	}
}


HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		// TODO: Change any attributes of the DC here

	/* 窗口控件颜色 */
	hbr = ::CreateSolidBrush(RGB(176,224,230));//(238,221,130));//框底色
	if(pWnd->GetDlgCtrlID() == IDC_SCURRENT)
	{
		pDC->SetTextColor(RGB(250,1,1));
		pDC->SetBkColor(RGB(255,222,173));//背景底色
		hbr = ::CreateSolidBrush(RGB(238,221,130));
	}
	else if(pWnd->GetDlgCtrlID() == IDC_COPYRIGHT)//版权
	{
		pDC->SetTextColor(RGB(154,50,205));//字体颜色
		pDC->SetBkColor(RGB(255,222,173));//背景底色
		hbr = ::CreateSolidBrush(RGB(238,221,130));//框底色
	}
	else if(pWnd->GetDlgCtrlID() == IDC_SHOWTIME)
	{
		pDC->SetTextColor(RGB(0,0,205));//字体颜色
		pDC->SetBkColor(RGB(176,224,230));//背景底色
		hbr = ::CreateSolidBrush(RGB(135,206,235));//框底色
	}
	else if(IDC_STATE == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(85,25,139));//字体颜色
		pDC->SetBkColor(RGB(255,206,180));//背景底色
		hbr = ::CreateSolidBrush(RGB(255,206,180));//框底色
	}
	else if(IDC_S_D == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkColor(RGB(64,224,209));
		hbr = ::CreateSolidBrush(RGB(64,224,209));//框底色
	}
	else
	{
		pDC->SetTextColor(RGB(255,0,167));//字体颜色
		pDC->SetBkColor(RGB(176,224,230));//(205 ,190 ,112));//字符背景底色
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMyDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
		
	if(T_SHOWTIME == nIDEvent)
	{
		crrentT = crrentT.GetCurrentTime();
		CString st = "时间：";
		st += crrentT.Format("%H:%M:%S");
		SetDlgItemText(IDC_SHOWTIME,st);
	}
	else if(T_PUNM == nIDEvent)
	{
		if(am_inject == TRUE)
			Punm();//注射基础量
	}
	else if(T_CHECKBLOOD == nIDEvent)//这个时钟开始时设置，检测血糖浓度是否超过标准
	{
		CheckBloodSugar();
	}
	else if(T_ELECTRIC == nIDEvent)//更新电量
	{
		m_EQuantity--;
		m_ElectricQuantity.SetPos(m_EQuantity);
		if(m_EQuantity == 1)
		{
			PlaySound(MAKEINTRESOURCE(IDR_A_ELECTRIC),NULL, SND_RESOURCE | SND_ASYNC);
			MessageBox("!!!电量不足,请及时更换电池!!!");
		}
		else if(m_EQuantity <= 0)
		{
			KillTimer(nIDEvent);//结束监控
			KillTimer(T_LEFTDOSE);
			KillTimer(T_ELECTRIC);
			KillTimer(T_CHECKBLOOD);
			SetDlgItemText(IDC_SCURRENT,"停止");
			m_lamp.EnableWindow(FALSE);
			isStart = FALSE;
			SetDlgItemText(IDC_START,"开始");
		}

	}
	else if(T_LEFTDOSE == nIDEvent) //更新胰岛素剩余量
	{
		if(insulin_residue > 0.3)
		{
			CString str;
	
			str.Format("%.3f",insulin_residue);
			str += "单位";
			SetDlgItemText(IDC_DoseLeft,str);
		}
		else 
		{
			KillTimer(nIDEvent);
			SetDlgItemText(IDC_DoseLeft,"0单位");
			insulin_residue = 0;
			PlaySound(MAKEINTRESOURCE(IDR_USE_UP),NULL, SND_RESOURCE | SND_ASYNC);
			m_lamp.EnableWindow(FALSE);
			MessageBox("胰岛素已经用完,请更换!!!");

			
		}
	}
	else if(T_CURRENT_RANGE == nIDEvent)//目标范围，每小时更新一次
	{
		GetTargetRange();
	}

	CDialog::OnTimer(nIDEvent);
}

void CMyDlg::OnOption() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_HIDE);
	Optdlg.DoModal();

	if(dose_for_oneday <= 0 || dose_before_meal.breakfast < 0
		|| dose_before_meal.lunch < 0 || dose_before_meal.supper < 0)
	{
		MessageBox("首次使用,请把信息补充完整!");
	}

	WriteToFile(this);
	CString st;

	st.Format("%.3f",_24HourBase);//assertion
	SetDlgItemText(IDC_mBISIC,st);
	
	st.Format("%.3f",insulin_residue);
	st += "单位";
	SetDlgItemText(IDC_DoseLeft,st);
	ShowWindow(SW_SHOW);
}

void CMyDlg::OnEXPLAINbtn() 
{
	// TODO: Add your control notification handler code here
	Cexplain Exdlg;

	Exdlg.DoModal();
}

void CMyDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	if(insulin_residue < BasedForHour)//就检测余量
	{
		if(insulin_residue <= 0)
		{
			insulin_residue = 0;
			SetDlgItemText(IDC_DoseLeft,"0.000");
			MessageBox("胰岛素余量不足!");
		}
	}
	else
	{
		if(FALSE == isStart)//还没开始
		{
			if(m_EQuantity > 0)//检测电源
			{
				isStart = TRUE;
				m_lamp.EnableWindow(TRUE);
				SetDlgItemText(IDC_START,"停止");
				srand(time(NULL));//生成随机数用到

				SetTimer(T_CHECKBLOOD,Time_BloodSugar,NULL);
				SetTimer(T_LEFTDOSE,3 * 1000,NULL);//用于更新剩余胰岛素
				SetTimer(T_PUNM,10 * 1000,NULL);
				SetTimer(T_CURRENT_RANGE,60 * 60 * 1000,NULL);//每小时更新显示目标血糖
				CheckBloodSugar();
				
				CString str;
				str.Format("%.3f",insulin_residue);
				str += "单位";
				SetDlgItemText(IDC_DoseLeft,str);
				LpSugar_rand = AfxBeginThread(blood_sugar_rand, this);//, 0);
			//	LpSugar_rand = AfxBeginThread(blood_sugar_rand, &blood_sugar);
			}
			else
			{
				PlaySound(MAKEINTRESOURCE(IDR_A_ELECTRIC),NULL, SND_RESOURCE | SND_ASYNC);
				MessageBox("!!!电量不足!!!");
			}
		}
		else
		{
			m_lamp.EnableWindow(FALSE);
			KillTimer(T_CHECKBLOOD);
			KillTimer(T_PUNM);
			KillTimer(T_LEFTDOSE);
			isStart = FALSE;
			SetDlgItemText(IDC_START,"开始");
			SetDlgItemText(IDC_SCURRENT,"");
		}
	}
}
/*
void CMyDlg::OnPause() 
{
	// TODO: Add your control notification handler code here
	if(isStart == TRUE)
	{
		m_lamp.EnableWindow(FALSE);
		KillTimer(T_CHECKBLOOD);
		KillTimer(T_PUNM);
		KillTimer(T_LEFTDOSE);
		isStart = FALSE;
	}

}
*/
//读取胰岛素数据
BOOL CMyDlg::ReadFile(CMyDlg *pWnd)
{
	fstream fp;

	fp.open("InsulinData.dat",fstream::in);
	if(!fp)//说明没有该文件
	{
		WriteToFile(this);
	//	MessageBox("Empty");
	}
	else
	{
		char ch;
		while(!fp.eof())
		{
			fp >> insulin_residue;
			fp >> dose_for_oneday;	
			fp >> _24HourBase;
			fp >> dose_before_meal.breakfast;
			fp >> dose_before_meal.lunch;
			fp >> dose_before_meal.supper;
			fp >> ch;
		}
	}
	fp.close();

	return TRUE;
}

BOOL CMyDlg::CountDose()
{
	int Hour = crrentT.GetHour();

	if(Hour < 0)
		return FALSE;

	_24HourBase = (float)(dose_for_oneday / 2.0);
	BasedForHour = _24HourBase / 24.0f;
	start_found_dose =  BasedForHour * (24 - Hour);//每小时 乘以 剩下的小时数
	
	return TRUE;
}
/* 获取各个时间段的控制目标 */
void CMyDlg::GetTargetRange()
{
	int Hour = crrentT.GetHour();
	CString str;
	if(Hour > 21)
	{
		Max_range = bsis.IndexBeforeSleep_max;
		Min_range = bsis.IndexBeforeSleep_min;
	}
	else if(Hour > 8)
	{
		Max_range = bsis.other_time_max;
		Min_range = bsis.other_time_min;
		SetDlgItemText(IDC_STD,str);
	}
	else if(Hour > 3)//凌晨
	{
		//不用设置上界
		Min_range = bsis.IndexAt_3AM_min;
	}
	else
	{
		Max_range = bsis.other_time_max;
		Min_range = bsis.other_time_min;
		SetDlgItemText(IDC_STD,str);
	}
}

void CMyDlg::OnPreBreafast() 
{
	// TODO: Add your control notification handler code here
//	if(TRUE == isStart)
	{
		if(insulin_residue > 0 && insulin_residue > dose_before_meal.breakfast)
		{
			inject_volume = dose_before_meal.breakfast;
			CInject Jdlg;
			if(IDOK == Jdlg.DoModal())
			{
				insulin_residue = insulin_residue - dose_before_meal.breakfast;
				MessageBox("   注入成功!");
			}
		}
		else
			MessageBox("胰岛素余量不足,请及时添加");
	}
//	else
//		MessageBox("请先按 \"开始\" 按钮");
}

void CMyDlg::OnPreLunch() 
{
	// TODO: Add your control notification handler code here
//	if(TRUE == isStart)
	{
		if(insulin_residue > 0 && insulin_residue > dose_before_meal.lunch)
		{
			inject_volume = dose_before_meal.lunch;
			CInject Jdlg;
			if(IDOK == Jdlg.DoModal())
			{
				insulin_residue = insulin_residue - dose_before_meal.lunch;
				MessageBox("   注入成功!");
			}
		}
		else
			MessageBox("胰岛素余量不足,请及时添加");
	}
//	else
//		MessageBox("请先按 \"开始\" 按钮");
}

void CMyDlg::OnPreSupper() 
{
	// TODO: Add your control notification handler code here
	
//	if(TRUE == isStart)
	{
		if(insulin_residue > 0 && insulin_residue > dose_before_meal.supper)
		{
			inject_volume = dose_before_meal.supper;
			CInject Jdlg;
			if(IDOK == Jdlg.DoModal())
			{
				insulin_residue = insulin_residue - dose_before_meal.supper;
				MessageBox("   注入成功!");
			}
		}
		else
			MessageBox("胰岛素余量不足,请及时添加");
	}
//	else
//		MessageBox("请先按 \"开始\" 按钮");
}

void CMyDlg::ShowNowRange()
{
	CString st,tmp;
		
	st.Format("%.3f",Min_range);
	st += " -- ";

	tmp.Format("%.3f",Max_range);
	st += tmp;

	SetDlgItemText(IDC_STD,st);
}

void CMyDlg::Punm()
{
	
	if(insulin_residue >= BasedForHour)
	{
		insulin_residue -= BasedForHour/60/10;
	}
	else
		insulin_residue = 0;
}

void CMyDlg::CheckBloodSugar()
{
	blood_sugar = (float)(RandLength * rand() / (RAND_MAX+1.0) );
	CString  str;
	str.Format("%.3f",blood_sugar);
	SetDlgItemText(IDC_SCURRENT,str);
	if(blood_sugar > Max_range)
	{
		PlaySound(MAKEINTRESOURCE(IDR_WARN),NULL, SND_RESOURCE | SND_ASYNC);
		SetDlgItemText(IDC_STATE,"偏高"); 
		am_inject = TRUE;//继续注射
	}
	else if( blood_sugar < Min_range)
	{
		PlaySound(MAKEINTRESOURCE(IDR_LowAlarm),NULL, SND_RESOURCE | SND_ASYNC);
		SetDlgItemText(IDC_STATE,"偏低");	
		am_inject = FALSE;//不注射胰岛素基础量
	}
	else
		SetDlgItemText(IDC_STATE,"正常");
}

void CMyDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)//窗体大小发生变动。处理函数resize
	{
		resize();
	}
	
}

void CMyDlg::resize()
{
// 	float fsp[2];
// 	POINT Newp; //获取现在对话框的大小
// 	CRect recta;  
// 
// 	GetClientRect(&recta);     //取客户区大小
// 	Newp.x=recta.right-recta.left;
// 	Newp.y=recta.bottom-recta.top;
// 	fsp[0]=(float)Newp.x/Old.x;
// 	fsp[1]=(float)Newp.y/Old.y;
// 
// 	CRect Rect;
// 	int woc;
// 	CPoint OldTLPoint,TLPoint; //左上角
// 	CPoint OldBRPoint,BRPoint; //右下角
// 	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件
// 	while(hwndChild)  
// 	{  
// 		woc=::GetDlgCtrlID(hwndChild);//取得ID
// 		GetDlgItem(woc)->GetWindowRect(Rect);
// 		ScreenToClient(Rect);
// 		OldTLPoint = Rect.TopLeft();
// 		TLPoint.x = long(OldTLPoint.x*fsp[0]);
// 		TLPoint.y = long(OldTLPoint.y*fsp[1]);
// 		OldBRPoint = Rect.BottomRight();
// 		BRPoint.x = long(OldBRPoint.x *fsp[0]);
// 		BRPoint.y = long(OldBRPoint.y *fsp[1]);
// 		Rect.SetRect(TLPoint,BRPoint);
// 		GetDlgItem(woc)->MoveWindow(Rect,TRUE);
// 		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);  
// 	}
// 	Old=Newp;
// 	
}

void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(point.y < 20) //左键点击顶部的范围
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y)); 
	//欺骗 Windows，发送拖动标题栏的消息
	CDialog::OnLButtonDown(nFlags, point);
}

void CMyDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	isStart = FALSE;
	CMyDlg::OnCancel();
}

UINT CMyDlg::blood_sugar_rand(LPVOID pParam)
{
	
	CMyDlg *pDlg=(CMyDlg *)pParam;
	while(pDlg->isStart) 
	{
		pDlg->blood_sugar = (float)(pDlg->RandLength * rand() / (RAND_MAX+1.0) );
		CString str;
		str.Format("%f", pDlg->blood_sugar);
		pDlg->SetDlgItemText(IDC_SCURRENT,str);
		//AfxMessageBox(str);

		Sleep(pDlg->Time_BloodSugar);
	}
	return 0;
}
