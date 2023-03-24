
// ChessClockDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ChessClock.h"
#include "ChessClockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 自定义的工具函数

BOOL DrawHorizontalDigitalTube(HDC hdc, LPPOINT ptAnchor, LONG nLength, COLORREF color)
// 画一条水平的数码管
{
	HBRUSH hBru = CreateSolidBrush(color);
	SelectObject(hdc, hBru);
	SelectObject(hdc, GetStockObject(NULL_PEN));

	POINT tube[6];
	double sepRate = 0.05;
	nLength = nLength * (1 - 2 * sepRate);

	tube[0] = { ptAnchor->x + (LONG)(nLength * sepRate), ptAnchor->y };
	tube[1] = { tube[0].x + nLength / 5, tube[0].y + nLength / 5 };
	tube[2] = { tube[1].x + LONG(nLength * 0.6), tube[1].y };
	tube[3] = { tube[2].x + nLength / 5, tube[2].y - nLength / 5 };
	tube[4] = { tube[2].x, tube[3].y - nLength / 5 };
	tube[5] = { tube[1].x, tube[4].y };

	BOOL res = Polygon(hdc, tube, 6);
	DeleteObject(hBru);
	return res;
}

BOOL DrawVerticalDigitalTube(HDC hdc, LPPOINT ptAnchor, LONG nLength, COLORREF color)
// 画一条垂直的数码管
{
	HBRUSH hBru = CreateSolidBrush(color);
	SelectObject(hdc, hBru);
	SelectObject(hdc, GetStockObject(NULL_PEN));

	POINT tube[6]; 
	double sepRate = 0.05;
	nLength = nLength * (1 - 2 * sepRate);

	tube[0] = { ptAnchor->x, ptAnchor->y + (LONG)(nLength * sepRate)};
	tube[1] = { tube[0].x + nLength / 5, tube[0].y + nLength / 5 };
	tube[2] = { tube[1].x, tube[1].y + LONG(nLength * 0.6)};
	tube[3] = { tube[2].x - nLength / 5, tube[2].y + nLength / 5 };
	tube[4] = { tube[3].x - nLength / 5, tube[2].y };
	tube[5] = { tube[4].x, tube[1].y };

	
	BOOL res = Polygon(hdc, tube, 6);
	DeleteObject(hBru);
	return res;
}

BOOL DrawDigitalTube(HDC hdc, LPPOINT ptStart, LONG nLength, COLORREF color, LPLONG pos)
{
	POINT anchor = { ptStart->x + nLength / 5, ptStart->y + nLength / 5 };

	if (pos[0] == 1)	
		DrawHorizontalDigitalTube(hdc, &anchor, nLength, color);
	if (pos[1] == 1)
		DrawVerticalDigitalTube(hdc, &anchor, nLength, color);
	if (pos[2] == 1)
	{
		POINT new_anchor = { anchor.x, anchor.y + nLength };
		DrawVerticalDigitalTube(hdc, &new_anchor, nLength, color);
	}
	if (pos[3] == 1)
	{
		POINT new_anchor = { anchor.x, anchor.y + 2 * nLength };
		DrawHorizontalDigitalTube(hdc, &new_anchor, nLength, color);
	}
	if (pos[4] == 1)
	{
		POINT new_anchor = { anchor.x + nLength, anchor.y + nLength };
		DrawVerticalDigitalTube(hdc, &new_anchor, nLength, color);
	}
	if (pos[5] == 1)
	{
		POINT new_anchor = { anchor.x + nLength, anchor.y };
		DrawVerticalDigitalTube(hdc, &new_anchor, nLength, color);
	}
	if (pos[6] == 1)
	{
		POINT new_anchor = { anchor.x, anchor.y + nLength };
		DrawHorizontalDigitalTube(hdc, &new_anchor, nLength, color);
	}
	return TRUE;
}

BOOL DrawFigure(HDC hdc, LPPOINT ptStart, LONG nLength, COLORREF color, LONG num)
{
	LONG trans[10][7] = {
	   //0 1 2 3 4 5 6
		{1,1,1,1,1,1,0},
		{0,0,0,0,1,1,0},
		{1,0,1,1,0,1,1},
		{1,0,0,1,1,1,1},
		{0,1,0,0,1,1,1},
		{1,1,0,1,1,0,1},
		{1,1,1,1,1,0,1},
		{1,0,0,0,1,1,0},
		{1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1}
	};
	return DrawDigitalTube(hdc, ptStart, nLength, color, trans[num]);
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChessClockDlg 对话框



CChessClockDlg::CChessClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHESSCLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChessClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edt1);
	DDX_Control(pDX, IDC_EDIT2, edt2);
	DDX_Control(pDX, IDC_EDIT3, edt3);
	DDX_Control(pDX, IDC_EDIT4, edt4);
	DDX_Control(pDX, IDC_BUTTON1, bt1);
	DDX_Control(pDX, IDC_EDIT5, edt5);
	DDX_Control(pDX, IDC_EDIT6, edt6);
	DDX_Control(pDX, IDC_BUTTON2, bt2);
	DDX_Control(pDX, IDC_BUTTON3, bt3);
}

BEGIN_MESSAGE_MAP(CChessClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CChessClockDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CChessClockDlg 消息处理程序

BOOL CChessClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//this->SetTimer(1, 1000, NULL);
	edt1.SetWindowTextW(TEXT("60"));
	edt2.SetWindowTextW(TEXT("20"));
	edt3.SetWindowTextW(TEXT("60"));
	edt4.SetWindowTextW(TEXT("20"));
	edt5.SetWindowTextW(TEXT("0"));
	edt6.SetWindowTextW(TEXT("0"));

	//bt2.EnableWindow(FALSE);
	this->UpdateWindow();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChessClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChessClockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		static LONG init = 0;
		PAINTSTRUCT ps;
		this->BeginPaint(&ps);
		CDialogEx::OnPaint();	// 这个语句一定需要在最前面

		CRect rect;
		RECT rcBottom;
		RECT rcTopLeft;
		RECT rcTopRight;
		GetClientRect(&rect);
		this->rcLeft.top = this->rcRight.top = rect.top + (rect.bottom - rect.top) / 5;
		this->rcLeft.bottom = this->rcRight.bottom = rect.bottom - (rect.bottom - rect.top) / 5;
		this->rcLeft.left = rect.left;
		this->rcLeft.right = (rect.right + rect.left) / 2 - 2;
		this->rcRight.left = (rect.right + rect.left) / 2 + 2;
		this->rcRight.right = rect.right;
		rcBottom.top = rcLeft.bottom;
		rcBottom.left = rcLeft.left;
		rcBottom.right = rcRight.right;
		rcBottom.bottom = rect.bottom;
		rcTopLeft.top = rcTopRight.top = rect.top;
		rcTopLeft.bottom = rcTopRight.bottom = this->rcLeft.top;
		rcTopLeft.left = this->rcLeft.left;
		rcTopLeft.right = this->rcLeft.right;
		rcTopRight.left = this->rcRight.left;
		rcTopRight.right = this->rcRight.right;

#define BITMAP_ACC 0

#if BITMAP_ACC
		HDC hDC = CreateCompatibleDC(ps.hdc);// 内存设备上下文（内存DC）
		HBITMAP hBitMap = CreateCompatibleBitmap(ps.hdc, rect.right - rect.left, rect.bottom - rect.top);
		SelectObject(hDC, hBitMap);
		HBRUSH hBru = CreateSolidBrush(GetBkColor(ps.hdc));
		FillRect(hDC, &rect, hBru);
		DeleteObject(hBru);
#else
		HDC real_hDC = ps.hdc;
		HDC hDC = CreateCompatibleDC(real_hDC);
		HBITMAP bmp = CreateCompatibleBitmap(real_hDC, rect.right - rect.left, rect.bottom - rect.top);
		SelectObject(hDC, bmp);
		FillRect(hDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));//用白色画笔填充
#endif

#define RED	RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define YELLOW RGB(255,255,0)
#define BLACK RGB(0,0,0)

		if (this->State == EDITING)
		{
			this->MyDrawRoundRect(hDC, &this->rcLeft, 1, 1, RED);
			this->MyDrawRoundRect(hDC, &this->rcRight, 1, 1, RED);
		}
		else if (this->State == WAITING)
		{
			this->MyDrawRoundRect(hDC, &this->rcLeft, 1, 1, YELLOW);
			this->MyDrawRoundRect(hDC, &this->rcRight, 1, 1, YELLOW);
		}
		else if (this->State == LRUNNING)
		{
			this->MyDrawRoundRect(hDC, &this->rcLeft, 1, 1, GREEN);
		}
		else if (this->State == RRUNNING)
		{
			this->MyDrawRoundRect(hDC, &this->rcRight, 1, 1, GREEN);
		}
		else if (this->State == LPAUSED)
		{
			this->MyDrawRoundRect(hDC, &this->rcLeft, 1, 1, YELLOW);
		}
		else if (this->State == RPAUSED)
		{
			this->MyDrawRoundRect(hDC, &this->rcRight, 1, 1, YELLOW);
		}
		else if (this->State == LENDED)
		{
			this->MyDrawRoundRect(hDC, &this->rcLeft, 1, 1, RED);
		}
		else if (this->State == RENDED)
		{
			this->MyDrawRoundRect(hDC, &this->rcRight, 1, 1, RED);
		}
		LONG bigLength = min((LONG)(rect.right - rect.left) / 10, (LONG)(rect.bottom - rect.top) / 8);
		LONG smallLength = (LONG)(bigLength * 0.6);
		LONG between_bias = (LONG)(smallLength * 0.4);
		LONG buttonLength = (LONG)(bigLength * 1.5);
		LONG topHeight = bigLength;
		LONG topLength = 4 * topHeight;

		POINT left_center = { (this->rcLeft.left + this->rcLeft.right) / 2, (this->rcLeft.top + this->rcLeft.bottom) / 2 };
		POINT right_center = { (this->rcRight.left + this->rcRight.right) / 2, (this->rcRight.top + this->rcRight.bottom) / 2 };
		POINT bottom_center = { (rcBottom.left + rcBottom.right) / 2, (rcBottom.top + rcBottom.bottom) / 2 };
		POINT top_left_center = { (rcTopLeft.left + rcTopLeft.right) / 2, (rcTopLeft.top + rcTopLeft.bottom) / 2 };
		POINT top_right_center = { (rcTopRight.left + rcTopRight.right) / 2, (rcTopRight.top + rcTopRight.bottom) / 2 };
		POINT left_big_start1 = { left_center.x - (LONG)(bigLength * 2.25) , left_center.y - (bigLength + smallLength)};
		POINT left_big_start2 = { left_center.x - (LONG)(bigLength * 0.75), left_big_start1.y };
		POINT left_big_start3 = { left_center.x + (LONG)(bigLength * 0.75), left_big_start1.y };
		POINT left_small_start1 = { left_center.x - (long)(smallLength * 1.5), left_center.y + smallLength + between_bias };
		POINT left_small_start2 = { left_center.x, left_small_start1.y };
		POINT right_big_start1 = { right_center.x - (LONG)(bigLength * 2.25) , right_center.y - (bigLength + smallLength) };
		POINT right_big_start2 = { right_center.x - (LONG)(bigLength * 0.75), right_big_start1.y };
		POINT right_big_start3 = { right_center.x + (LONG)(bigLength * 0.75), right_big_start1.y };
		POINT right_small_start1 = { right_center.x - (long)(smallLength * 1.5), right_center.y + smallLength + between_bias };
		POINT right_small_start2 = { right_center.x, right_small_start1.y };

		COLORREF crFigure = RGB(0, 0, 0);
		ULONGLONG leftSeconds, rightSeconds;
		leftSeconds = this->leftMs / 1000;
		rightSeconds = this->rightMs / 1000;
		LONG now = GetTickCount64();
		if(this->State == LRUNNING)
			leftSeconds = (this->leftMs - (now - this->lastClock)) / 1000;
		else if(this->State == RRUNNING)
			rightSeconds = (this->rightMs - (now - this->lastClock)) / 1000;
		DrawFigure(hDC, &left_big_start1, bigLength, crFigure, (leftSeconds / 6000) %10);
		DrawFigure(hDC, &left_big_start2, bigLength, crFigure, (leftSeconds / 600) % 10);
		DrawFigure(hDC, &left_big_start3, bigLength, crFigure, (leftSeconds / 60) % 10);
		DrawFigure(hDC, &left_small_start1, smallLength, crFigure, (leftSeconds % 60) / 10);
		DrawFigure(hDC, &left_small_start2, smallLength, crFigure, leftSeconds % 10);
		DrawFigure(hDC, &right_big_start1, bigLength, crFigure, (rightSeconds / 6000) % 10);
		DrawFigure(hDC, &right_big_start2, bigLength, crFigure, (rightSeconds / 600) % 10);
		DrawFigure(hDC, &right_big_start3, bigLength, crFigure, (rightSeconds / 60) % 10);
		DrawFigure(hDC, &right_small_start1, smallLength, crFigure, (rightSeconds % 60) / 10);
		DrawFigure(hDC, &right_small_start2, smallLength, crFigure, rightSeconds % 10);

		CWnd* pWnd;

		pWnd = GetDlgItem(IDC_BUTTON1);
		pWnd->MoveWindow(bottom_center.x - (LONG)(buttonLength * 0.5), 
			bottom_center.y - (LONG)(buttonLength * 0.25),
			buttonLength, 
			(LONG)(buttonLength * 0.5));

		pWnd = GetDlgItem(IDC_STATIC);
		pWnd->MoveWindow(top_left_center.x - topLength / 2, 
			top_left_center.y - topHeight / 2, 
			topLength * 0.4, 
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_STATIC1);
		pWnd->MoveWindow(top_left_center.x - topLength / 2,
			top_left_center.y,
			topLength * 0.4,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_EDIT1);
		pWnd->MoveWindow(top_left_center.x - topLength / 2 + topLength * 0.5,
			top_left_center.y - topHeight / 2,
			topLength * 0.2,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_EDIT2);
		pWnd->MoveWindow(top_left_center.x - topLength / 2 + topLength * 0.5,
			top_left_center.y,
			topLength * 0.5,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_STATIC3);
		pWnd->MoveWindow(top_right_center.x - topLength / 2,
			top_right_center.y - topHeight / 2,
			topLength * 0.4,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_STATIC4);
		pWnd->MoveWindow(top_right_center.x - topLength / 2,
			top_right_center.y,
			topLength * 0.4,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_EDIT3);
		pWnd->MoveWindow(top_right_center.x - topLength / 2 + topLength * 0.5,
			top_right_center.y - topHeight / 2,
			topLength * 0.2,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_EDIT4);
		pWnd->MoveWindow(top_right_center.x - topLength / 2 + topLength * 0.5,
			top_right_center.y,
			topLength * 0.5,
			(topHeight - between_bias) / 2);
		
		pWnd = GetDlgItem(IDC_EDIT5);
		pWnd->MoveWindow(top_left_center.x - topLength / 2 + topLength * 0.8,
			top_left_center.y - topHeight / 2,
			topLength * 0.2,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_EDIT6);
		pWnd->MoveWindow(top_right_center.x - topLength / 2 + topLength * 0.8,
			top_right_center.y - topHeight / 2,
			topLength * 0.2,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_STATIC5);
		pWnd->MoveWindow(top_left_center.x + (topLength * 0.2),
			top_left_center.y - topHeight / 2,
			topLength * 0.1,
			(topHeight - between_bias) / 2);

		pWnd = GetDlgItem(IDC_STATIC6);
		pWnd->MoveWindow(top_right_center.x + (topLength * 0.2),
			top_right_center.y - topHeight / 2,
			topLength * 0.1,
			(topHeight - between_bias) / 2);

		BitBlt(real_hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hDC, 0, 0, SRCCOPY);
		DeleteDC(hDC);
		DeleteObject(bmp);


#if BITMAP_ACC
		
#endif
		this->EndPaint(&ps);

		if (init == 0)
		{
			init++;
			Invalidate();
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChessClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChessClockDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	Invalidate();
	//UpdateWindow();


	// TODO: 在此处添加消息处理程序代码
}


void CChessClockDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->State == EDITING || this->State == LPAUSED || this->State == RPAUSED)
	{
		LONG temp1 = GetDlgItemInt(IDC_EDIT1);
		LONG temp3 = GetDlgItemInt(IDC_EDIT3);
		LONG temp5 = GetDlgItemInt(IDC_EDIT5);
		LONG temp6 = GetDlgItemInt(IDC_EDIT6);
		if (temp1 + temp5 <= 0 || temp3 + temp6 <= 0)
		{
			MessageBox(TEXT("数据非法"));
			return;
		}
		this->leftMs = ((ULONGLONG)temp1 * 60 + (ULONGLONG)temp5) * 1000;
		this->rightMs = ((ULONGLONG)temp3 * 60 + (ULONGLONG)temp6) * 1000;
		this->leftStep = (ULONGLONG)GetDlgItemInt(IDC_EDIT2) * 1000;
		this->rightStep = (ULONGLONG)GetDlgItemInt(IDC_EDIT4) * 1000;
		edt1.SetReadOnly();
		edt2.SetReadOnly();
		edt3.SetReadOnly();
		edt4.SetReadOnly();
		edt5.SetReadOnly();
		edt6.SetReadOnly();
		bt1.SetWindowTextW(TEXT("编辑"));
		this->State = WAITING;
	}
	else if (this->State == WAITING || this->State == LENDED || this->State == RENDED)
	{
		edt1.SetReadOnly(FALSE);
		edt2.SetReadOnly(FALSE);
		edt3.SetReadOnly(FALSE);
		edt4.SetReadOnly(FALSE);
		edt5.SetReadOnly(FALSE);
		edt6.SetReadOnly(FALSE);
		bt1.SetWindowTextW(TEXT("保存"));
		this->State = EDITING;
	}
	Invalidate();
}

void CChessClockDlg::MyDrawRoundRect(HDC hdc, RECT* rect, int ra, int rb, COLORREF crColor)
{
	//HBRUSH hBru = CreateSolidBrush(crColor);
	HPEN hpen = CreatePen(PS_SOLID, 5, crColor);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	SelectObject(hdc, hpen);

	RoundRect(hdc, rect->left, rect->top, rect->right, rect->bottom, ra, rb);
	//DeleteObject(hBru);
	DeleteObject(hpen);
}

void CChessClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ULONGLONG now = GetTickCount64();

	static LONGLONG left_old;
	static LONGLONG right_old;
	LONGLONG leftSeconds = 1, rightSeconds = 1;

	if (this->State == LRUNNING)
	{
		leftSeconds = (this->leftMs - (now - this->lastClock)) / 1000;
		if (leftSeconds <= 0)
		{
			this->leftMs = 0;
			this->KillTimer(MAINTIMMER);
			this->State = LENDED;
			this->bt1.EnableWindow(TRUE);
		}
		if(leftSeconds != left_old)
			InvalidateRect(&this->rcLeft);
		left_old = leftSeconds;
	}
	else if (this->State == RRUNNING)
	{
		rightSeconds = (this->rightMs - (now - this->lastClock)) / 1000;
		if (rightSeconds <= 0)
		{
			this->rightMs = 0;
			this->KillTimer(MAINTIMMER);
			this->State = RENDED;
			this->bt1.EnableWindow(TRUE);
		}
		if(rightSeconds != right_old)
			InvalidateRect(&this->rcRight);
		right_old = rightSeconds;
	}
	if (leftSeconds <= 0)
		MessageBox(TEXT("左方超时！"));
	else if (rightSeconds <= 0)
		MessageBox(TEXT("右方超时！"));

	CDialogEx::OnTimer(nIDEvent);
}


void CChessClockDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = 600;
	lpMMI->ptMinTrackSize.y = 450;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CChessClockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case 'Q':
		case 'W':
		case 'E':
		case 'R':
		case 'T':
		case 'A':
		case 'S':
		case 'D':
		case 'F':
		case 'Z':
		case 'X':
		case 'C':
			//MessageBox(TEXT("右方开始"));
			if (this->State == WAITING || this->State == LRUNNING)
			{
				ULONGLONG now = GetTickCount64();
				if (this->State == WAITING)
				{
					this->bt1.EnableWindow(FALSE);
					this->SetFocus();
				}
				if (this->State == LRUNNING)
				{
					this->leftMs -= now - this->lastClock;
					this->leftMs += this->leftStep;
				}
				this->lastClock = now;
				this->State = RRUNNING;
				this->SetTimer(MAINTIMMER, RR, NULL);
				Invalidate();
			}
			break;

		case 'P':
		case 'O':
		case 'I':
		case 'U':
		case 'Y':
		case 'L':
		case 'K':
		case 'J':
		case 'H':
		case 'M':
		case 'N':
		case 'B':
			if (this->State == WAITING || this->State == RRUNNING)
			{
				ULONGLONG now = GetTickCount64();
				if (this->State == WAITING)
				{
					this->bt1.EnableWindow(FALSE);
					this->SetFocus();
				}
				if (this->State == RRUNNING)
				{
					this->rightMs -= now - this->lastClock;
					this->rightMs += this->rightStep;
				}
				this->lastClock = now;
				this->State = LRUNNING;
				this->SetTimer(MAINTIMMER, RR, NULL);
				Invalidate();
			}
			break;

		case VK_F5:
			if (this->State == LRUNNING || this->State == RRUNNING)
			{
				ULONGLONG now = GetTickCount64();
				this->KillTimer(MAINTIMMER);
				if (this->State == LRUNNING)
				{
					this->leftMs -= now - this->lastClock;
					this->State = LPAUSED;
				}
				else
				{
					this->rightMs -= now - this->lastClock;
					this->State = RPAUSED;
				}
				this->bt1.EnableWindow(TRUE);
				this->bt1.SetWindowTextW(TEXT("结束"));
				Invalidate();
			}
			else if (this->State == LPAUSED || this->State == RPAUSED)
			{
				this->lastClock = GetTickCount64();
				this->SetTimer(MAINTIMMER, RR, NULL);
				if (this->State == LPAUSED)
				{
					this->State = LRUNNING;
				}
				else
				{
					this->State = RRUNNING;
				}
				this->bt1.SetWindowTextW(TEXT("编辑"));
				this->bt1.EnableWindow(FALSE);
				this->SetFocus();
				Invalidate();
			}
			break;
		}

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
