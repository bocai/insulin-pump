// 胰岛素泵Dlg.h : header file
//
//timer ID
#define		T_SHOWTIME      1 //显示现在时间
#define		T_CHECKBLOOD    2  //检测血糖浓度
#define		T_ELECTRIC      3  //检测电量减少
#define		T_LEFTDOSE		4  //更新显示剩余胰岛素
#define     T_PUNM          5  //泵注入
#define     T_CURRENT_RANGE 6  //现在血糖控制目标的范围

/***********************************************************************/
//血糖不同阶段的标准，医生根据患者不同而设置其值
typedef struct BloodSugarIndexStandard{
	float	other_time_min;				// 其他时间血糖上界
	float	other_time_max;				// 其他时间血糖下界
	float	IndexBeforeMeal_min;		// 饭前血糖控制目标指数下界
	float	IndexBeforeMeal_max;		// 饭前2小时血糖控制目标指数上届
	float	IndexAfterMeal_max;			// 饭后2小时血糖控制目标指数上界
	float	IndexBeforeSleep_min;		// 睡前血糖控制目标指数下界
	float	IndexBeforeSleep_max;		// 睡前血糖控制目标指数上界
	float	IndexAt_3AM_min;			// 凌晨三点血糖空中目标指数下界
} BSIS;

/**************************************************************************/
 //餐前注射胰岛素剂量结构体，根据患者不同而设置其值

typedef struct DoseBeforeMeal{
	float	breakfast;		// 早餐前注入剂量
	float	lunch;			// 午餐前注入剂量
	float	supper;			// 晚餐前注入剂量
}DBM;

/**************************************************************************
** 补充注射胰岛素剂量结构体,注意和DBM不同的是"补充"，开始时根据患者不同而设置其值
**************************************************************************/
typedef	struct Add_Dose{
	float	add_dose;			// 补充剂量
	float	before_meal;		// 餐前测得血糖偏高添加量占补充剂量的百分比
	float   after_meal;		    // 餐后测得血糖偏高添加量占补充剂量的百分比
	float	before_sleep;		// 睡前测得血糖偏高添加量占补充剂量的百分比
}ADose;

#if !defined(AFX_DLG_H__80B3D5D4_17BB_4554_A770_BFF68349BECD__INCLUDED_)
#define AFX_DLG_H__80B3D5D4_17BB_4554_A770_BFF68349BECD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	void resize();
	void CheckBloodSugar();//检测血糖浓度，与当前时段目标范围比较，偏高/偏低则发出警报
	void Punm();//根据日基础量注射相应量的胰岛素
	void ShowNowRange();//显示剩余电量
	void GetTargetRange();//获取此时段的控制目标范围

	BOOL CountDose();//根据给定的一日总量按照合理的百分比计算出日基础量
	BOOL WriteToFile(CMyDlg *pWnd);//将关键数据写入文件	
	BOOL ReadFile(CMyDlg *pWnd);//从文件读取关键数据
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

	CShadeButtonST	m_begin;//开始按钮美化（从网上借来用的按钮类，下同）
	CShadeButtonST	m_exit; //退出按钮美化
	CButtonST       m_BtnOptions;//选项按钮美化
	CButtonST       m_lamp; //灯，亮灭
	CButtonST       m_BtnExplain;//帮助按钮
	CRect			m_rect;    //客户区域
	POINT			Old;//存放对话框的宽和高。

	int             m_EQuantity;//电量值
	int             RandLength; //随机数上界
	int             Time_BloodSugar; //测血糖的时间间隔
	BOOL			isStart; //控制开始按钮
	BOOL            am_inject;//是否注射基础量
	COptions		Optdlg;//选项对话框

	float   blood_sugar;	//  存储当前测得血糖值的变量//正常3.9~6.1
	float	insulin_residue;	//  胰岛素剩余剂量
	float   dose_for_oneday;    //  一天注入胰岛素的剂量
	float   _24HourBase;         //  基础量
	float   start_found_dose;	//  胰岛素开始基础量
	float   BasedForHour;       // 通过基础量计算没小时胰岛素用量
	float   inject_volume;		//餐前注射量

	float   Max_range;        //根据时段不同将BSIS对应的上界赋给该值
	float   Min_range;        //与Max_range相对应
	BSIS    bsis;				//  用于存储血糖控制目标指数
	DBM	    dose_before_meal;   //  指向餐前胰岛素注入剂量
//	ADose   addedDose;			//  胰岛素补充剂量百分比  /*未完成*/

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CProgressCtrl	m_ElectricQuantity;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
//	COLORREF m_textcolor;
	CTime crrentT;
	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();//做一些初始化工作，如：界面设置和美化，读取上次的存档
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();//加载图标，设置背景等
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//设置除按钮外的控件字体、背景颜色等等
	afx_msg void OnTimer(UINT nIDEvent);//响应定时器消息，对不同的定时器执行对应的代码
	afx_msg void OnOption();//选项按钮，弹出设置窗口，提供各种数据的变更
	afx_msg void OnEXPLAINbtn();
	afx_msg void OnStart();//开始或停止按钮，主要程序的执行和停止
	afx_msg void OnPreBreafast();//早餐前根据设置的值，注射对应量的胰岛素
	afx_msg void OnPreLunch();//午餐前根据设置的值，注射对应量的胰岛素
	afx_msg void OnPreSupper();//晚餐前根据设置的值，注射对应量的胰岛素
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWinThread *LpSugar_rand;
	static UINT blood_sugar_rand(LPVOID pParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__80B3D5D4_17BB_4554_A770_BFF68349BECD__INCLUDED_)
