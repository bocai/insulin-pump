// �ȵ��ر�Dlg.h : header file
//
//timer ID
#define		T_SHOWTIME      1 //��ʾ����ʱ��
#define		T_CHECKBLOOD    2  //���Ѫ��Ũ��
#define		T_ELECTRIC      3  //����������
#define		T_LEFTDOSE		4  //������ʾʣ���ȵ���
#define     T_PUNM          5  //��ע��
#define     T_CURRENT_RANGE 6  //����Ѫ�ǿ���Ŀ��ķ�Χ

/***********************************************************************/
//Ѫ�ǲ�ͬ�׶εı�׼��ҽ�����ݻ��߲�ͬ��������ֵ
typedef struct BloodSugarIndexStandard{
	float	other_time_min;				// ����ʱ��Ѫ���Ͻ�
	float	other_time_max;				// ����ʱ��Ѫ���½�
	float	IndexBeforeMeal_min;		// ��ǰѪ�ǿ���Ŀ��ָ���½�
	float	IndexBeforeMeal_max;		// ��ǰ2СʱѪ�ǿ���Ŀ��ָ���Ͻ�
	float	IndexAfterMeal_max;			// ����2СʱѪ�ǿ���Ŀ��ָ���Ͻ�
	float	IndexBeforeSleep_min;		// ˯ǰѪ�ǿ���Ŀ��ָ���½�
	float	IndexBeforeSleep_max;		// ˯ǰѪ�ǿ���Ŀ��ָ���Ͻ�
	float	IndexAt_3AM_min;			// �賿����Ѫ�ǿ���Ŀ��ָ���½�
} BSIS;

/**************************************************************************/
 //��ǰע���ȵ��ؼ����ṹ�壬���ݻ��߲�ͬ��������ֵ

typedef struct DoseBeforeMeal{
	float	breakfast;		// ���ǰע�����
	float	lunch;			// ���ǰע�����
	float	supper;			// ���ǰע�����
}DBM;

/**************************************************************************
** ����ע���ȵ��ؼ����ṹ��,ע���DBM��ͬ����"����"����ʼʱ���ݻ��߲�ͬ��������ֵ
**************************************************************************/
typedef	struct Add_Dose{
	float	add_dose;			// �������
	float	before_meal;		// ��ǰ���Ѫ��ƫ�������ռ��������İٷֱ�
	float   after_meal;		    // �ͺ���Ѫ��ƫ�������ռ��������İٷֱ�
	float	before_sleep;		// ˯ǰ���Ѫ��ƫ�������ռ��������İٷֱ�
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
	void CheckBloodSugar();//���Ѫ��Ũ�ȣ��뵱ǰʱ��Ŀ�귶Χ�Ƚϣ�ƫ��/ƫ���򷢳�����
	void Punm();//�����ջ�����ע����Ӧ�����ȵ���
	void ShowNowRange();//��ʾʣ�����
	void GetTargetRange();//��ȡ��ʱ�εĿ���Ŀ�귶Χ

	BOOL CountDose();//���ݸ�����һ���������պ���İٷֱȼ�����ջ�����
	BOOL WriteToFile(CMyDlg *pWnd);//���ؼ�����д���ļ�	
	BOOL ReadFile(CMyDlg *pWnd);//���ļ���ȡ�ؼ�����
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

	CShadeButtonST	m_begin;//��ʼ��ť�����������Ͻ����õİ�ť�࣬��ͬ��
	CShadeButtonST	m_exit; //�˳���ť����
	CButtonST       m_BtnOptions;//ѡ�ť����
	CButtonST       m_lamp; //�ƣ�����
	CButtonST       m_BtnExplain;//������ť
	CRect			m_rect;    //�ͻ�����
	POINT			Old;//��ŶԻ���Ŀ�͸ߡ�

	int             m_EQuantity;//����ֵ
	int             RandLength; //������Ͻ�
	int             Time_BloodSugar; //��Ѫ�ǵ�ʱ����
	BOOL			isStart; //���ƿ�ʼ��ť
	BOOL            am_inject;//�Ƿ�ע�������
	COptions		Optdlg;//ѡ��Ի���

	float   blood_sugar;	//  �洢��ǰ���Ѫ��ֵ�ı���//����3.9~6.1
	float	insulin_residue;	//  �ȵ���ʣ�����
	float   dose_for_oneday;    //  һ��ע���ȵ��صļ���
	float   _24HourBase;         //  ������
	float   start_found_dose;	//  �ȵ��ؿ�ʼ������
	float   BasedForHour;       // ͨ������������ûСʱ�ȵ�������
	float   inject_volume;		//��ǰע����

	float   Max_range;        //����ʱ�β�ͬ��BSIS��Ӧ���Ͻ縳����ֵ
	float   Min_range;        //��Max_range���Ӧ
	BSIS    bsis;				//  ���ڴ洢Ѫ�ǿ���Ŀ��ָ��
	DBM	    dose_before_meal;   //  ָ���ǰ�ȵ���ע�����
//	ADose   addedDose;			//  �ȵ��ز�������ٷֱ�  /*δ���*/

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
	virtual BOOL OnInitDialog();//��һЩ��ʼ���������磺�������ú���������ȡ�ϴεĴ浵
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();//����ͼ�꣬���ñ�����
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//���ó���ť��Ŀؼ����塢������ɫ�ȵ�
	afx_msg void OnTimer(UINT nIDEvent);//��Ӧ��ʱ����Ϣ���Բ�ͬ�Ķ�ʱ��ִ�ж�Ӧ�Ĵ���
	afx_msg void OnOption();//ѡ�ť���������ô��ڣ��ṩ�������ݵı��
	afx_msg void OnEXPLAINbtn();
	afx_msg void OnStart();//��ʼ��ֹͣ��ť����Ҫ�����ִ�к�ֹͣ
	afx_msg void OnPreBreafast();//���ǰ�������õ�ֵ��ע���Ӧ�����ȵ���
	afx_msg void OnPreLunch();//���ǰ�������õ�ֵ��ע���Ӧ�����ȵ���
	afx_msg void OnPreSupper();//���ǰ�������õ�ֵ��ע���Ӧ�����ȵ���
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
