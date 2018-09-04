
// OneCardSysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "OneCardSysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COneCardSysDlg �Ի���



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


// COneCardSysDlg ��Ϣ�������

BOOL COneCardSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	UpdateData(TRUE);
	
	this->SetWindowText(_T("һ��ͨרҵϵͳ"));
	m_strUser = "1";
	m_strPwd = "1";

	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COneCardSysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COneCardSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
} 


void COneCardSysDlg::OnBnClickedBtnlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	UpdateData(TRUE);

	if (m_strUser != L"1" && m_strPwd != L"1")
	{
		MessageBox("�û�ID���������\n ���������룡", "��¼ʧ�ܣ�", MB_OK | MB_ICONERROR);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(0);
}
