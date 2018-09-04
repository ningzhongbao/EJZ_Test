// FaceOper.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "FaceOper.h"
#include "afxdialogex.h"


// CFaceOper �Ի���

IMPLEMENT_DYNAMIC(CFaceOper, CDialogEx)

CFaceOper::CFaceOper(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAUPFACEPICTURE, pParent)
{
	InitLoginParams(); //��ʼ���������
	
	m_pfaceGroupArray = NULL;
	LogIn();//��¼	
}

CFaceOper::~CFaceOper()
{
	LogOut();
}

void CFaceOper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_face_group);
}


BEGIN_MESSAGE_MAP(CFaceOper, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_FACE_GROUP, &CFaceOper::OnBnClickedBtnAddFaceGroup)
	ON_BN_CLICKED(IDC_BTN_REFRESH_FACE_GROUP, &CFaceOper::OnBnClickedBtnRefreshFaceGroup)
	ON_BN_CLICKED(IDC_BTN_DELETE_FACE_GROUP, &CFaceOper::OnBnClickedBtnDeleteFaceGroup)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////
static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
{
	// TODO: 
	CFaceOper* pDlg = (CFaceOper*)dwUser;
	pDlg->m_lLoginID = 0;
}

BOOL CFaceOper::InitLoginParams()
{
	m_lLoginID = 0;
	m_Str_Ip = "192.168.7.2";
	m_int_port = 3000;
	m_Str_User = "admin";
	m_Str_Pwd = "admin123";
	
	Net_Init(disconnect_callback, (LDWORD)(void*)this); //��ʼ��sdk��

	return TRUE;
}

BOOL CFaceOper::LogIn()
{
	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
		m_Str_User.GetBuffer(), m_Str_Pwd.GetBuffer(), NULL, &m_nError); //��½

	if (0 >= m_lLoginID)
	{
		MessageBox(_T("����ʶ���ܵ�¼ʧ�ܣ��������"), _T("��¼��ʾ..."), MB_ICONHAND);

		return FALSE;
	}

	return TRUE;
}

BOOL CFaceOper::LogOut()
{
	if (m_lLoginID)
	{
		if (Net_LogoutDevice(m_lLoginID))
		{
			m_lLoginID = 0;
			// �����������Դ
			Net_Exit();

			return TRUE;
		}
	}

	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////

// CFaceOper ��Ϣ�������


void CFaceOper::OnBnClickedBtnAddFaceGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CFaceGroupAdd dlgFGAdd;
	if (IDOK != dlgFGAdd.DoModal())
		return;
	// ��������ӵ��б�
	CString strAlias = dlgFGAdd.GetAliasString();
	BOOL bEnable = dlgFGAdd.GetFaceGroupEnable();
	float fSearchThreshold = dlgFGAdd.GetSearchThreshold();
	UINT nTopRank = dlgFGAdd.GetTopRank();

	if (TRUE != AddFaceGroup(strAlias, bEnable, fSearchThreshold, nTopRank))
	{
		MessageBox("���������ʧ��.");
		return;
	}
	else
	{
		MessageBox(_T("��ӳɹ�"));
	}
}


BOOL CFaceOper::AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank)
{
	STU_FACE_GROUP_CREATE_IN_PARAM stInParam = { 0 };
	STU_FACE_GROUP_CREATE_OUT_PARAM stOutParam = { 0 };

	stInParam.bEnable = bEnable;
	sprintf(stInParam.szAlias, "%s", strAlias.GetBuffer(0));
	strAlias.ReleaseBuffer();
	stInParam.fSearchThreshold = fSearchThreshold;
	stInParam.nTopRank = nTopRank;

	if (TRUE != Net_CreateFaceGroup(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox(_T("���󣬴������������.\n"));

		return FALSE;
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////
// ������ & ��������
void CFaceOper::DeleteFaceGroupArray()
{
	if (NULL != m_pfaceGroupArray) {
		delete m_pfaceGroupArray;
		m_pfaceGroupArray = NULL;
	}
}


BOOL CFaceOper::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("��δ��¼��"), "", MB_OK);
	return FALSE;
}

BOOL CFaceOper::ReCreateFaceGroupArray()
{
	DeleteFaceGroupArray();
	m_pfaceGroupArray = new STU_FACE_GROUP_ARRAY_INFO;
	if (NULL == m_pfaceGroupArray)
	{
		return FALSE;
	}
	memset(m_pfaceGroupArray, 0x00, sizeof(STU_FACE_GROUP_ARRAY_INFO));
	return TRUE;
}

BOOL CFaceOper::RefreshFaceGroup()
{
	if (TRUE != ReCreateFaceGroupArray()) 
	{
		MessageBox(_T("ReCreateFaceGroupArray���������"), NULL, MB_OK);		
		return FALSE;
	}

	if (TRUE != Net_GetAllFaceGroups(m_lLoginID, m_pfaceGroupArray))
	{
		MessageBox(_T("��ȡ���������"), NULL, MB_OK);
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////

void CFaceOper::OnBnClickedBtnRefreshFaceGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	if (TRUE != RefreshFaceGroup())
		return;

	UI_RefreshFaceGroup();
	//UI_RefreshCurFaceInfo(NULL);
	//UI_RefreshCurPerson(NULL);
}


////////////////////////////////////////////////////////////////////////////////////////////
// �������
BOOL CFaceOper::UI_RefreshFaceGroup()
{
	m_list_face_group.ResetContent();
	for (int i = 0; i < m_pfaceGroupArray->nFaceGroupNum; i++)
	{
		CString strGroupInfo = "";
		strGroupInfo.Format("%d-%u-%s", i, m_pfaceGroupArray->stFaceGroupArr[i].nGroupID,
			m_pfaceGroupArray->stFaceGroupArr[i].szGroupName);
		m_list_face_group.AddString(strGroupInfo.GetBuffer(0));
		strGroupInfo.ReleaseBuffer();
	}
	m_list_face_group.SetCurSel(-1);
	return TRUE;
}

BOOL CFaceOper::UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo)
{
	if (NULL == pCurFaceInfo)
	{
		m_edit_uint_group_id = 0;
		m_edit_string_group_name = "";
		m_edit_string_group_alias = "";
		m_edit_string_create_time = "";
		m_edit_int_group_enable = 0;
		m_edit_int_group_top_rank = 0;
		m_edit_string_group_guid = "";
	}
	else
	{
		m_edit_uint_group_id = pCurFaceInfo->nGroupID;
		m_edit_string_group_name.Format("%s", pCurFaceInfo->szGroupName);
		m_edit_string_group_alias.Format("%s", pCurFaceInfo->szAlias);
		m_edit_string_create_time.Format("%04d-%02d-%02d %02d:%02d:%02d",
			pCurFaceInfo->stCreateTime.dwYear, pCurFaceInfo->stCreateTime.dwMonth, pCurFaceInfo->stCreateTime.dwDay,
			pCurFaceInfo->stCreateTime.dwHour, pCurFaceInfo->stCreateTime.dwMinute, pCurFaceInfo->stCreateTime.dwSecond);
		m_edit_int_group_enable = pCurFaceInfo->bEnable;
		m_edit_string_group_search_threshold.Format("%0.2f", pCurFaceInfo->fSearchThreshold);
		m_edit_int_group_top_rank = pCurFaceInfo->nTopRank;
		m_edit_string_group_guid.Format("%s", pCurFaceInfo->szGUID);
	}

	UpdateData(FALSE);
	return TRUE;
}

BOOL CFaceOper::UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson)
{
	/*if (!m_person_face_image_1.IsEmpty())
		DeleteFile(m_person_face_image_1.GetBuffer(0));
	if (!m_person_face_image_2.IsEmpty())
		DeleteFile(m_person_face_image_2.GetBuffer(0));
	if (!m_person_face_image_3.IsEmpty())
		DeleteFile(m_person_face_image_3.GetBuffer(0));
*/
	if (NULL == pCurPerson)
	{
		m_edit_uint_person_id = 0;
		m_edit_string_person_name = "";
		m_edit_string_person_birth = "";
		m_edit_string_person_sex = "";
		m_edit_string_person_certificate_type = "";
		m_edit_string_person_certificate_id = "";
		m_edit_string_person_country = "";
		m_edit_string_person_province = "";
		m_edit_string_person_city = "";

	}
	else
	{
		m_edit_uint_person_id = pCurPerson->stPersonInfo.nPersonID;
		m_edit_string_person_name.Format("%s", pCurPerson->stPersonInfo.szName);
		m_edit_string_person_birth.Format("%04d-%02d-%02d",
			pCurPerson->stPersonInfo.stBirthday.dwYear, pCurPerson->stPersonInfo.stBirthday.dwMonth, pCurPerson->stPersonInfo.stBirthday.dwDay);
		m_edit_string_person_sex = pCurPerson->stPersonInfo.emSexType == SEX_TYPE_MALE ? "male" :
			pCurPerson->stPersonInfo.emSexType == SEX_TYPE_FEMALE ? "female" : "unknown";
		m_edit_string_person_certificate_type.Format("%s", pCurPerson->stPersonInfo.szCertificateType);
		m_edit_string_person_certificate_id.Format("%s", pCurPerson->stPersonInfo.szID);
		m_edit_string_person_country.Format("%s", pCurPerson->stPersonInfo.szCountry);
		m_edit_string_person_province.Format("%s", pCurPerson->stPersonInfo.szProvince);
		m_edit_string_person_city.Format("%s", pCurPerson->stPersonInfo.szCity);

		m_edit_string_person_1_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[0].szFaceToken);
		m_edit_string_person_2_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[1].szFaceToken);
		m_edit_string_person_3_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[2].szFaceToken);

		// ����ͼƬ������

		/*for (int i = 0; i < pCurPerson->nFaceImageCount; i++)
		{
			CString strPath = "";
			strPath.Format("C:\\Tmp\\face_image_tmp_%d.jpg", i + 1);
			if (TRUE == GetFaceImage(i, strPath))
			{
				if (0 == i)
					m_person_face_image_1 = strPath;
				else if (1 == i)
					m_person_face_image_2 = strPath;
				else if (2 == i)
					m_person_face_image_3 = strPath;
			}
		}*/
	}

	UpdateData(FALSE);
	Invalidate(TRUE);
	return TRUE;
}

STU_FACE_GROUP_INFO* CFaceOper::GetCurFaceGroupInfo(int nIndex)
{
	if (0 > nIndex || MAX_FACE_GROUP_NUM <= nIndex)
		return NULL;
	if (NULL == m_pfaceGroupArray || 0 == m_pfaceGroupArray->nFaceGroupNum)
		return NULL;
	return &m_pfaceGroupArray->stFaceGroupArr[nIndex];
}

BOOL CFaceOper::DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace)
{
	STU_FACE_GROUP_DELETE_IN_PARAM stInParam = { 0 };
	STU_FACE_GROUP_DELETE_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;
	stInParam.bDelBindFace = bDelBindFace;

	if (TRUE != Net_DeleteFaceGroup(m_lLoginID, &stInParam, &stOutParam))
	{
		CString str;
		str.Format("Error | Delete face group error, nGrouID = %u, bDelBindFace = %d.\n",
			nGroupID, bDelBindFace);

		MessageBox(str, NULL, MB_OK);
		str.ReleaseBuffer(0);
		/*_OutputDebugString("Error | Delete face group error, nGrouID = %u, bDelBindFace = %d.\n",
			nGroupID, bDelBindFace);*/

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////

void CFaceOper::OnBnClickedBtnDeleteFaceGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	// �Ƿ�ѡ����
	int nIndex = m_list_face_group.GetCurSel();
	if (nIndex < 0) {
		MessageBox(_T("δѡ�������飡"), "", MB_OK);
		return;
	}

	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);
	if (NULL == pCurFaceGroup)
	{
		MessageBox("��ȡ��������Ϣʧ�ܣ�");
		return;
	}

	BOOL bDelBindFace = FALSE;
	if (IDYES == MessageBox(_T("�Ƿ�ɾ��������󶨵���������ͼƬ��") , "", MB_YESNO))
	{
		bDelBindFace = TRUE;
	}

	if (TRUE != DeleteFaceGroup(pCurFaceGroup->nGroupID, bDelBindFace))
	{
		MessageBox(_T("ɾ��������ʧ�ܣ���ˢ�������⣡"));
	}

	// ��ˢ��һ��
	RefreshFaceGroup();
	UI_RefreshFaceGroup();
	UI_RefreshCurFaceInfo(NULL);
}
