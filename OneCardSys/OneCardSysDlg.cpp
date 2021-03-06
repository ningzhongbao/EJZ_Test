
// OneCardSysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "OneCardSysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COneCardSysDlg 对话框



COneCardSysDlg::COneCardSysDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ONECARDSYS_DIALOG, pParent)
	, m_strUser(_T(""))
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
COneCardSysDlg::~COneCardSysDlg()
{

}
void COneCardSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}

BEGIN_MESSAGE_MAP(COneCardSysDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_BtnLogin, &COneCardSysDlg::OnBnClickedBtnlogin)
	ON_BN_CLICKED(IDC_BtnCannel, &COneCardSysDlg::OnBnClickedBtncannel)
END_MESSAGE_MAP()


// COneCardSysDlg 消息处理程序

BOOL COneCardSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	UpdateData(TRUE);
	
	this->SetWindowText(_T("一卡通专业系统"));
	m_strUser = "1";
	m_strPwd = "1";

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COneCardSysDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COneCardSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
} 


void COneCardSysDlg::OnBnClickedBtnlogin()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(TRUE);

	if (m_strUser != L"1" && m_strPwd != L"1")
	{
		MessageBox("用户ID或密码错误！\n 请重新输入！", "登录失败！", MB_OK | MB_ICONERROR);
	}
	else
	{
		this->ShowWindow(SW_HIDE);

		CSysMainUi mainUi;
		mainUi.DoModal();
	}
}


void COneCardSysDlg::OnBnClickedBtncannel()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(0);
}
