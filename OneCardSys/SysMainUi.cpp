// SysMainUi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "SysMainUi.h"
#include "afxdialogex.h"


// CSysMainUi �Ի���

IMPLEMENT_DYNAMIC(CSysMainUi, CDialogEx)

CSysMainUi::CSysMainUi(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAMAINUI, pParent)
{
	m_pPicDlg = NULL;
	m_pPerDlg = NULL;
	m_OwenInfo = NULL;

}

CSysMainUi::~CSysMainUi()
{
	if (NULL != m_pPerDlg)
	{
		delete m_pPerDlg;
		m_pPerDlg = NULL;
	}
	if (NULL != m_pPicDlg)
	{
		delete m_pPicDlg;
		m_pPicDlg = NULL;
	}
	if (NULL != m_OwenInfo)
	{
		delete m_OwenInfo;
		m_OwenInfo = NULL;
	}
}

void CSysMainUi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysMainUi, CDialogEx)
	ON_BN_CLICKED(IDC_GetPerInfo, &CSysMainUi::OnBnClickedGetperinfo)
	ON_BN_CLICKED(IDC_BtnPerInfo, &CSysMainUi::OnBnClickedBtnperinfo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_GetOweInfo, &CSysMainUi::OnBnClickedGetoweinfo)
	ON_BN_CLICKED(IDC_BtnSendOwerInfo, &CSysMainUi::OnBnClickedBtnsendowerinfo)
	ON_BN_CLICKED(IDC_BtnFaceOper, &CSysMainUi::OnBnClickedBtnfaceoper)
END_MESSAGE_MAP()


// CSysMainUi ��Ϣ�������


BOOL CSysMainUi::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ModifyStyleEx(0, WS_EX_APPWINDOW);//��ʾ������ͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSysMainUi::OnBnClickedGetperinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_pPerDlg)
	{
		m_pPerDlg = new CGetInfoPer();
		m_pPerDlg->Create(IDD_GETPERSON, this);
	}
	m_pPerDlg->ShowWindow(SW_SHOW);	
}


void CSysMainUi::OnBnClickedBtnperinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_pPicDlg)
	{
		m_pPicDlg = new CPicture1();
		m_pPicDlg->Create(IDD_PERSON_INFO, this);
	}
	m_pPicDlg->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);

	PostQuitMessage(0);	
	CDialogEx::OnClose();
}


void CSysMainUi::OnBnClickedGetoweinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_OwenInfo)
	{
		m_OwenInfo = new CGetOwerInfo();
		m_OwenInfo->Create(IDD_GetOwerInfo, this);
	}
	m_OwenInfo->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnBnClickedBtnsendowerinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CSysMainUi::OnBnClickedBtnfaceoper()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFaceOper FaceOpen;
	FaceOpen.DoModal();
}
