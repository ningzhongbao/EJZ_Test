#pragma once
#include "FaceGroupAdd.h"

#include "stdafx.h"
#include "afxwin.h"

// CFaceOper �Ի���

class CFaceOper : public CDialogEx
{
	DECLARE_DYNAMIC(CFaceOper)

public:
	CFaceOper(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFaceOper();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAUPFACEPICTURE };
#endif

public:
	BOOL AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank);

public:
	BOOL InitLoginParams();//��ʼ����¼����
	BOOL LogIn();  //��¼
	BOOL LogOut();

	/////////////////������//////////////////////
	BOOL CheckLoginOk();
	BOOL RefreshFaceGroup();//ˢ��������
	BOOL ReCreateFaceGroupArray();
	void DeleteFaceGroupArray();
	STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex);
	BOOL DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace);

	//�������
	BOOL UI_RefreshFaceGroup();
	BOOL UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo);

	BOOL UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson);

public:
	LLONG m_lLoginID;
	int	m_nError;

	CString     m_Str_Ip; //ip
	INT 	    m_int_port; //�˿�
	CString 	m_Str_User; //�û���
	CString 	m_Str_Pwd; //����
						   // ��������Ϣ
	STU_FACE_GROUP_ARRAY_INFO* m_pfaceGroupArray;

	/////////////////////////////////////////////////////////
	// ҳ����Ϣ
	CString m_static_string_person_page;
	// ������ID
	UINT m_edit_uint_group_id;
	// ����������
	CString m_edit_string_group_name;
	// ���������
	CString m_edit_string_group_alias;
	// �����ⴴ��ʱ��
	CString m_edit_string_create_time;
	// ������ʹ��
	int m_edit_int_group_enable;
	// �������ѯ��ֵ
	CString m_edit_string_group_search_threshold;
	// ������ TopRank
	unsigned int m_edit_int_group_top_rank;
	// ������GUID
	CString m_edit_string_group_guid;
	// �����⵱ǰ��Աҳ��
	CString m_edit_person_page;
	// ��Ա ID
	UINT m_edit_uint_person_id;
	// ��Ա����
	CString m_edit_string_person_name;
	// ��Ա����
	CString m_edit_string_person_birth;
	// ��Ա�Ա�
	CString m_edit_string_person_sex;
	// ��Ա֤������
	CString m_edit_string_person_certificate_type;
	// ��Ա֤���� ID
	CString m_edit_string_person_certificate_id;
	// ����
	CString m_edit_string_person_country;
	// ʡ��
	CString m_edit_string_person_province;
	// ���ڳ���
	CString m_edit_string_person_city;
	// ��Ա����ͼ1��ʶ��
	CString m_edit_string_person_1_img_facetoken;
	// ��Ա����ͼ2��ʶ��
	CString m_edit_string_person_2_img_facetoken;
	// ��Ա����ͼ3��ʶ��
	CString m_edit_string_person_3_img_facetoken;
	CStatic m_static_image_1;
	CStatic m_static_image_2;
	CStatic m_static_image_3;
	/////////////////////////////////////////////////////////////
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAddFaceGroup();
	afx_msg void OnBnClickedBtnRefreshFaceGroup();
	CListBox m_list_face_group;
	afx_msg void OnBnClickedBtnDeleteFaceGroup();
};
