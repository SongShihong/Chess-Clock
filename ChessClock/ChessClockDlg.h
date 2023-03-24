
// ChessClockDlg.h: 头文件
//

#pragma once


// CChessClockDlg 对话框
class CChessClockDlg : public CDialogEx
{
// 构造
public:
	CChessClockDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHESSCLOCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();

public:
#define EDITING 1
#define WAITING 2
#define LRUNNING 3
#define LPAUSED	4
#define RRUNNING	5
#define RPAUSED	6
#define LENDED	7
#define RENDED	8

#define RR	50
#define MAINTIMMER	1

	// 自定义变量和函数
	RECT rcLeft, rcRight;
	ULONGLONG leftMs = 3600000, rightMs = 3600000;
	ULONGLONG leftStep = 20000, rightStep = 20000;
	ULONGLONG lastClock;
	LONG State = EDITING;
	void MyDrawRoundRect(HDC hdc, RECT* rect, int ra, int rb, COLORREF crColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	CEdit edt1;
	CEdit edt2;
	CEdit edt3;
	CEdit edt4;
	CButton bt1;
	CEdit edt5;
	CEdit edt6;
	CButton bt2;
	CButton bt3;
	//PAINTSTRUCT ps;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
