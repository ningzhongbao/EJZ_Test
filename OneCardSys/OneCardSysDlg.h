
// OneCardSysDlg.h : ͷ�ļ�
//

#pragma once
#include "SysMainUi.h"

// COneCardSysDlg �Ի���
class COneCardSysDlg : public CDialogEx
{
// ����
public:
	COneCardSysDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~COneCardSysDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ONECARDSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CPropertySheet	m_sheet;	 // ����ҳ��������������4����ǩ��ҳ�棩
	CPicture1       m_Picture;   //��ʾ���������Ϣ����ҳ
	

// ʵ��
public:

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	
	CString m_strUser;
	CString m_strPwd;
	afx_msg void OnBnClickedBtnlogin();
	afx_msg void OnBnClickedBtncannel();
};
