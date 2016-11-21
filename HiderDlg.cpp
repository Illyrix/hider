
// HiderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hider.h"
#include "HiderDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK WM_USER+1080
NOTIFYICONDATA m_nid;
static CWnd *cMain[50];
static int deep=0;
static Hotkey hideHotKey[3];
static Hotkey showHotKey[3];
static Hotkey exitHotKey[3];
// CHiderDlg 对话框
void setHotKey(){
	hideHotKey[0].setBykey(GetPrivateProfileInt(L"hide", L"1", 0x0001, L".\\config.ini"));
	hideHotKey[1].setBykey(GetPrivateProfileInt(L"hide", L"2", NULL, L".\\config.ini"));
	hideHotKey[2].setBykey(GetPrivateProfileInt(L"hide", L"3", (int)'Z', L".\\config.ini"));

	showHotKey[0].setBykey(GetPrivateProfileInt(L"show", L"1", 0x0001, L".\\config.ini"));
	showHotKey[1].setBykey(GetPrivateProfileInt(L"show", L"2", NULL, L".\\config.ini"));
	showHotKey[2].setBykey(GetPrivateProfileInt(L"show", L"3", (int)'X', L".\\config.ini"));

	exitHotKey[0].setBykey(GetPrivateProfileInt(L"exit", L"1", 0x0001, L".\\config.ini"));
	exitHotKey[1].setBykey(GetPrivateProfileInt(L"exit", L"2", NULL, L".\\config.ini"));
	exitHotKey[2].setBykey(GetPrivateProfileInt(L"exit", L"3", (int)'H', L".\\config.ini"));
}

CHiderDlg::CHiderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHiderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo_hide1);
}

BEGIN_MESSAGE_MAP(CHiderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CHiderDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//ON_BN_CLICKED(IDC_BUTTON2, &CHiderDlg::OnBnClickedButton2)
	ON_WM_KEYDOWN()
	//ON_STN_CLICKED(IDC_STATIC4, &CHiderDlg::OnStnClickedStatic4)
	ON_BN_CLICKED(IDC_BUTTON2, &CHiderDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHiderDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHiderDlg::OnBnClickedButton4)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_SIZE()
END_MESSAGE_MAP()

LRESULT CHiderDlg::OnShowTask(WPARAM wParam, LPARAM lParam)

{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
	{
		this->ShowWindow(SW_SHOWDEFAULT);         // 显示主窗口
		//this->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	break;
	}
	return 0;
}
// CHiderDlg 消息处理程序
BOOL CHiderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	int n[3];
	long IDC_COMBO[3][3] = { { IDC_COMBO1, IDC_COMBO2, IDC_COMBO3 }, { IDC_COMBO4, IDC_COMBO5, IDC_COMBO6 }, { IDC_COMBO7, IDC_COMBO8, IDC_COMBO9 } };
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[0][i]))->FindString(0, hideHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[0][i]))->SetCurSel(n[i]);
	}
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[1][i]))->FindString(0, showHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[1][i]))->SetCurSel(n[i]);
	}
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[2][i]))->FindString(0, exitHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[2][i]))->SetCurSel(n[i]);
	}

	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, L"Hider");                // VS2008 UNICODE编码用wcscpy_s()函数
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
	// TODO:  在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CHiderDlg::OnPaint()
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
		//ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnPaint();
		//ShowWindow(SW_HIDE);
	}
	
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHiderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CHiderDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	HWND dwndviem = NULL;
	HWND dwdesktopicon;
	HWND dwndparent = ::FindWindowEx(NULL, NULL, L"WorkerW", L"");
	while ((!dwndviem) && dwndparent)
	{
		dwndviem = ::FindWindowEx(dwndparent, 0, L"SHELLDLL_DefView", 0);
		dwndparent = ::FindWindowEx(0, dwndparent, L"WorkerW", L"");
	}
	dwndparent = ::GetParent(dwndviem);
	dwdesktopicon = ::FindWindowEx(dwndviem, 0, L"SysListView32", L"FolderView");
	HWND hwndTemp=::GetForegroundWindow();

	HWND hwndTaskBar = ::FindWindowEx(NULL, NULL, L"Shell_TrayWnd", L"");
	HWND hwndParent=NULL;
	HWND hwndParent2=NULL;
	HWND hwndParent3=NULL;
	if (::GetParent(hwndTemp)){
		hwndParent = ::GetParent(hwndTemp);
		if (::GetParent(hwndParent)){
			hwndParent2 = ::GetParent(hwndParent);
			if (::GetParent(hwndParent2))
				hwndParent3 = ::GetParent(hwndParent2);
		}
	}
	if ((wParam == 1520) && (dwdesktopicon != hwndTemp) && (hwndTemp != dwndparent) && (hwndTemp != dwndviem) && (hwndParent != hwndTaskBar) && (hwndParent2 != hwndTaskBar) && (hwndParent3 != hwndTaskBar)&&(hwndTemp!=hwndTaskBar))
	{
		if (deep < 50)
		{
			deep = deep + 1;
			cMain[deep - 1] = GetForegroundWindow();
			(*cMain[deep - 1]).ShowWindow(SW_HIDE);
		}
	}
	else if (wParam == 1521)
	{
		if (deep > 0)
		{
			(*cMain[deep - 1]).ShowWindow(SW_SHOW);
			deep = deep - 1;
		}
	}
	else if (wParam == 1522)
	{
		SendMessage(WM_CLOSE);
	}
	return 0;
}


int CHiderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	long x = 0x0001;
	int y = 0x2e;
	setHotKey();
	if (hideHotKey[1].getKey() == 0){
		RegisterHotKey(m_hWnd, 1520, hideHotKey[0].getKey(), hideHotKey[2].getKey());
	}
	else{
		RegisterHotKey(m_hWnd, 1520, hideHotKey[0].getKey() | hideHotKey[1].getKey(), hideHotKey[2].getKey());
	}
	if (showHotKey[1].getKey() == 0){
		RegisterHotKey(m_hWnd, 1521, showHotKey[0].getKey(), showHotKey[2].getKey());
	}
	else{
		RegisterHotKey(m_hWnd, 1521, showHotKey[0].getKey() | showHotKey[1].getKey(), showHotKey[2].getKey());
	}
	if (exitHotKey[1].getKey() == 0){
		RegisterHotKey(m_hWnd, 1522, exitHotKey[0].getKey(), exitHotKey[2].getKey());
	}
	else{
		RegisterHotKey(m_hWnd, 1522, exitHotKey[0].getKey() | exitHotKey[1].getKey(), exitHotKey[2].getKey());
	}
	ShowWindow(SW_HIDE);
	return 0;
}

void CHiderDlg::OnDestroy()
{
	for (int i = deep; i > 0; i--)
	{
		(*cMain[i - 1]).ShowWindow(SW_SHOW);
	}
	ShowWindow(SW_SHOW);
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	UnregisterHotKey(m_hWnd, 1520);
	UnregisterHotKey(m_hWnd, 1521);
	UnregisterHotKey(m_hWnd, 1522);
	CDialogEx::OnDestroy();
	// TODO:  在此处添加消息处理程序代码
}





void CHiderDlg::OnBnClickedButton2()
{
	CString text[3][3];
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(text[0][0]);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(text[0][1]);
	((CComboBox*)GetDlgItem(IDC_COMBO3))->GetWindowText(text[0][2]);
	((CComboBox*)GetDlgItem(IDC_COMBO4))->GetWindowText(text[1][0]);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->GetWindowText(text[1][1]);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->GetWindowText(text[1][2]);
	((CComboBox*)GetDlgItem(IDC_COMBO7))->GetWindowText(text[2][0]);
	((CComboBox*)GetDlgItem(IDC_COMBO8))->GetWindowText(text[2][1]);
	((CComboBox*)GetDlgItem(IDC_COMBO9))->GetWindowText(text[2][2]);
	if ((!text[0][0].GetLength()) && (!text[1][0].GetLength()) && (!text[2][0].GetLength()) && (!text[0][2].GetLength()) && (!text[1][2].GetLength()) && (!text[2][2].GetLength()))
	{
		MessageBox(L"第一列和第三列不能为空！", L"Hider", MB_OK);
		return;
	}

	for (int j = 0; j < 3; j++){
		hideHotKey[j].setByName(text[0][j]);
	}
	for (int j = 0; j < 3; j++){
		showHotKey[j].setByName(text[1][j]);
	}
	for (int j = 0; j < 3; j++){
		exitHotKey[j].setByName(text[2][j]);
	}
	WritePrivateProfileString(L"hide", L"1", (hideHotKey[0].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"hide", L"2", (hideHotKey[1].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"hide", L"3", (hideHotKey[2].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"show", L"1", (showHotKey[0].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"show", L"2", (showHotKey[1].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"show", L"3", (showHotKey[2].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"exit", L"1", (exitHotKey[0].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"exit", L"2", (exitHotKey[1].getKeyInCsr()), L".\\config.ini");
	WritePrivateProfileString(L"exit", L"3", (exitHotKey[2].getKeyInCsr()), L".\\config.ini");

	UnregisterHotKey(m_hWnd, 1520);
	UnregisterHotKey(m_hWnd, 1521);
	UnregisterHotKey(m_hWnd, 1522);

	if (hideHotKey[1].getKey() == 0){
		RegisterHotKey(m_hWnd, 1520, hideHotKey[0].getKey(), hideHotKey[2].getKey());
	}
	else{
		RegisterHotKey(m_hWnd, 1520, hideHotKey[0].getKey() | hideHotKey[1].getKey(), hideHotKey[2].getKey());
	}
	if (showHotKey[1].getKey() == 0){
		RegisterHotKey(m_hWnd, 1521, showHotKey[0].getKey(), showHotKey[2].getKey());
	}
	else{
		RegisterHotKey(m_hWnd, 1521, showHotKey[0].getKey() | showHotKey[1].getKey(), showHotKey[2].getKey());
	}
	if (exitHotKey[1].getKey() == 0){
		RegisterHotKey(m_hWnd, 1522, exitHotKey[0].getKey(), exitHotKey[2].getKey());
	}
	else{
		RegisterHotKey(m_hWnd, 1522, exitHotKey[0].getKey() | exitHotKey[1].getKey(), exitHotKey[2].getKey());
	}
	MessageBox(L"设置完成！", L"Hider", MB_OK);
	// TODO:  在此添加控件通知处理程序代码
}


void CHiderDlg::OnBnClickedButton3()
{
	setHotKey();
	int n[3];
	long IDC_COMBO[3][3] = { { IDC_COMBO1, IDC_COMBO2, IDC_COMBO3 }, { IDC_COMBO4, IDC_COMBO5, IDC_COMBO6 }, { IDC_COMBO7, IDC_COMBO8, IDC_COMBO9 } };
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[0][i]))->FindString(0, hideHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[0][i]))->SetCurSel(n[i]);
	}
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[1][i]))->FindString(0, showHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[1][i]))->SetCurSel(n[i]);
	}
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[2][i]))->FindString(0, exitHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[2][i]))->SetCurSel(n[i]);
	}
	// TODO:  在此添加控件通知处理程序代码
}


void CHiderDlg::OnBnClickedButton4()
{
	hideHotKey[0].setBykey(0x0001);
	hideHotKey[1].setBykey(NULL);
	hideHotKey[2].setBykey((int)'Z');
	showHotKey[0].setBykey(0x0001);
	showHotKey[1].setBykey(NULL);
	showHotKey[2].setBykey((int)'X');
	exitHotKey[0].setBykey(0x0001);
	exitHotKey[1].setBykey(NULL);
	exitHotKey[2].setBykey((int)'H');
	int n[3];
	long IDC_COMBO[3][3] = { { IDC_COMBO1, IDC_COMBO2, IDC_COMBO3 }, { IDC_COMBO4, IDC_COMBO5, IDC_COMBO6 }, { IDC_COMBO7, IDC_COMBO8, IDC_COMBO9 } };
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[0][i]))->FindString(0, hideHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[0][i]))->SetCurSel(n[i]);
	}
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[1][i]))->FindString(0, showHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[1][i]))->SetCurSel(n[i]);
	}
	for (int i = 0; i < 3; i++){
		n[i] = ((CComboBox*)GetDlgItem(IDC_COMBO[2][i]))->FindString(0, exitHotKey[i].getName());
		((CComboBox*)GetDlgItem(IDC_COMBO[2][i]))->SetCurSel(n[i]);
	}
	CHiderDlg::OnBnClickedButton2();
	// TODO:  在此添加控件通知处理程序代码
}


void CHiderDlg::OnSize(UINT nType, int cx, int cy)
{
	//CDialogEx::OnSize(nType, cx, cy);
	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口         
	}
	// TODO:  在此处添加消息处理程序代码
}
