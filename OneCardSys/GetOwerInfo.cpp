// GetOwerInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "GetOwerInfo.h"
#include "afxdialogex.h"


// CGetOwerInfo �Ի���

IMPLEMENT_DYNAMIC(CGetOwerInfo, CDialogEx)

CGetOwerInfo::CGetOwerInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GetOwerInfo, pParent)
{

}

CGetOwerInfo::~CGetOwerInfo()
{
}

void CGetOwerInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGetOwerInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetOwerInfo::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGetOwerInfo ��Ϣ�������


void CGetOwerInfo::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
