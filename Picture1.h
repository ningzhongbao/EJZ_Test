#pragma once
#include "afxwin.h"


// CPicture1 �Ի���
#include <vector>
#include "Protocol.h"
#include "afxcmn.h"
using namespace std;

class CPicture1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPicture1)

public:
	CPicture1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPicture1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSON_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	CString				m_image_path;			//ͼ��·�� 
	DWORD				m_nFileLen;			//�ļ�����
	char				*pBufImgDate;      //�洢������ͼƬ����
	CString				m_csFileName;      //·���ļ���
	vector<CString>		m_FileList;        //�ļ���
	CString				csDirParth;        //
	CString				m_AllPath;				//listboxѡ���·����
	OPEN_DOOR_PROTO     m_Protocol;     //Э���
public:
	char *LoadImaData(CString imagPath);     //��ȡͼƬ���� 
	void GetFileFromDir(CString csDirPath);  //��ȡͼƬ·��
	void JxFileName(CString jpgName);
	void Ui_Show_Info(CString filename);

public:	
	CStatic m_Image;
	afx_msg void OnBnClickedAddPerface();
	afx_msg void OnBnClickedDelePerface();
	CString m_Image_String;
	afx_msg void OnBnClickedCannel();
	CString m_Name;
	CString m_IDCard;
	CString m_DyId;
	CString m_LcId;
	CString m_LcIdd;
	CString m_ShId;
	afx_msg void OnBnClickedIdok();
	afx_msg void OnBnClickedOpenFacepath();
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedDeleList();
};