#pragma once
#include "Picture1.h"
#include "GetInfoPer.h"
#include "GetOwerInfo.h"
#include "FaceOper.h"

// CSysMainUi �Ի���

class CSysMainUi : public CDialogEx
{
	DECLARE_DYNAMIC(CSysMainUi)

public:
	CSysMainUi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysMainUi();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAMAINUI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	// ʵ��
public:
	CGetInfoPer *m_pPerDlg; //��ȡ����ͼƬ
	CPicture1   *m_pPicDlg; //�����ϴ�
	CGetOwerInfo*m_OwenInfo;//�ɼ�ҵ����Ϣ�Ի���
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedGetperinfo();
	afx_msg void OnBnClickedBtnperinfo();
	afx_msg void OnClose();
	afx_msg void OnBnClickedGetoweinfo();
	afx_msg void OnBnClickedBtnsendowerinfo();
	afx_msg void OnBnClickedBtnfaceoper();
};
