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
	, m_Name_ID(_T(""))
{
	InitLoginParams(); //��ʼ���������
	
	m_pfaceGroupArray = NULL;
	LogIn();//��¼	

	m_person_county = _T("�й�");
	m_person_sex = _T("male");
	m_person_certificate_type = _T("���֤");
	m_person_county = _T("�й�");
	m_person_birth = _T("2037-12-31");
	m_person_city = _T("�人��");
	m_person_certificate_id = _T("00000000000000");
	m_person_province = _T("����ʡ");

}

CFaceOper::~CFaceOper()
{
	LogOut();
}

void CFaceOper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_face_group);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT_ID, m_Name_ID);
}


BEGIN_MESSAGE_MAP(CFaceOper, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_FACE_GROUP, &CFaceOper::OnBnClickedBtnAddFaceGroup)
	ON_BN_CLICKED(IDC_BTN_REFRESH_FACE_GROUP, &CFaceOper::OnBnClickedBtnRefreshFaceGroup)
	ON_BN_CLICKED(IDC_BTN_DELETE_FACE_GROUP, &CFaceOper::OnBnClickedBtnDeleteFaceGroup)
	ON_BN_CLICKED(IDC_BTN_PERSON_ADD, &CFaceOper::OnBnClickedBtnPersonAdd)
	ON_BN_CLICKED(IDC_Btn_UP, &CFaceOper::OnBnClickedBtnUp)
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


//�������
void CFaceOper::ClearData()
{
	if (!m_FileList.empty())
	{
		m_FileList.clear();
		vector<CString>().swap(m_FileList);
	}	
}


void CFaceOper::OnBnClickedBtnPersonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (TRUE != CheckLoginOk())
		return;
	
	ClearData();  //���vector

	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);

	//��ȡ�ļ���
	GetFileFromDir(csDirParth);

	if (m_FileList.empty())
	{
		return;
	}
	
	CString strTmp = m_FileList.front();
	int posEnd = strTmp.ReverseFind('.');
	m_Name_ID = strTmp.Left(posEnd);	

	CString strPath;
	strPath = csDirParth + "\\" + m_FileList.front();
	Ui_Show(strPath);

	UpdateData(FALSE);
}

///////////////////////Ui_Show_Begin//////////////////////////////////////////////////////
void CFaceOper::Ui_Show(CString g_strPictureShow)
{
	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
	{
		AfxMessageBox(_T("����jpg�ļ�")); 
		return;
	}		

	CImage image;
	image.Load(g_strPictureShow);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����
	CRect rectControl;                        //�ؼ����ζ���
	CRect rectPicture;                        //ͼƬ���ζ���

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_Picture)->GetClientRect(rectControl);

	CDC *pDc = (&m_Picture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_Picture)->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������

	image.Destroy();
	(&m_Picture)->ReleaseDC(pDc);

	UpdateData(FALSE);
}

void CFaceOper::GetFileFromDir(CString csDirPath)
{
	csDirPath += "\\*.jpg";

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];

	//��ȡ��һ���ļ���
	file = FindFirstFile(csDirPath.GetBuffer(0), &fileData);
	m_FileList.push_back(fileData.cFileName);

	//���ݵ�һ���ļ��������»�ȡ
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState)
	{
		m_FileList.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}
//////////////////////////ui_end///////////////////////////////////////////////////

//////////////////////////˫����ʼ///////////////////////////////////////////////////
void CFaceOper::OnBnClickedBtnUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (TRUE != CheckLoginOk())
		return;

	int nIndex = CurFaceGroupIndex();
	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);
	if (NULL == pCurFaceGroup)
	{
		MessageBox(_T("��ѡ��һ�������飡"));
		return;
	}

	for (int i = 0; i < m_FileList.size(); i++)
	{	
		//��ʼ��
		memset(&m_stPersonInfo, 0x00, sizeof(STU_PERSON_INFO));		
		memset(m_stPersonInfo.szName, NULL, 128);
		char szNewName[128] = { 0 };
		m_Name_ID = "";

		CString m_person_name = m_FileList.at(i);
		int posEnd = m_person_name.ReverseFind('.');
		m_Name_ID = m_person_name.Left(posEnd);

		m_person_certificate_id = m_person_name.Left(posEnd);//���֤Ҳ��Ψһid
		//
		memcpy(m_stPersonInfo.szName, m_Name_ID.GetBuffer(0), m_Name_ID.GetLength());		

		CString strPath;
		strPath = csDirParth + "\\" + m_FileList.at(i);
		Ui_Show(strPath);		 

			
		sscanf(m_person_birth.GetBuffer(0), "%04d-%02d-%02d",
			&m_stPersonInfo.stBirthday.dwYear, &m_stPersonInfo.stBirthday.dwMonth, &m_stPersonInfo.stBirthday.dwDay);
		m_person_birth.ReleaseBuffer();

		if (m_person_sex == "male")
			m_stPersonInfo.emSexType = SEX_TYPE_MALE;
		else if (m_person_sex == "female")
			m_stPersonInfo.emSexType = SEX_TYPE_FEMALE;
		else
			m_stPersonInfo.emSexType = SEX_TYPE_UNKNOWN;

		memcpy(m_stPersonInfo.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
		m_person_certificate_type.ReleaseBuffer();


		/*	CTime tm;
			tm = CTime::GetCurrentTime();

			m_person_certificate_id = tm.Format("111%y%m%d%H%M%S");*/
		
		memcpy(m_stPersonInfo.szID, m_person_certificate_id.GetBuffer(0), m_person_certificate_id.GetLength());
		m_person_certificate_id.ReleaseBuffer();


		memcpy(m_stPersonInfo.szCountry, m_person_county.GetBuffer(0), m_person_county.GetLength());
		m_person_county.ReleaseBuffer();


		memcpy(m_stPersonInfo.szProvince, m_person_province.GetBuffer(0), m_person_province.GetLength());
		m_person_province.ReleaseBuffer();

		memcpy(m_stPersonInfo.szCity, m_person_city.GetBuffer(0), m_person_city.GetLength());
		m_person_city.ReleaseBuffer();


		//// �����Ա֮ǰ��ҪУ��������
		if (TRUE != CheckNameSuffix(m_stPersonInfo.szName, szNewName, 128))
		{
			MessageBox("����У��ʧ�ܣ�");
			return;
		}
		// ��ֵ����
		memcpy(m_stPersonInfo.szName, szNewName, strlen(szNewName));

		std::vector<CString> vecImages;
		if (!strPath.IsEmpty())
			vecImages.push_back(strPath);

		if (TRUE != AddPersonInfo(pCurFaceGroup->nGroupID, &m_stPersonInfo, vecImages))
		{
			//MessageBox("�����Ա��Ϣʧ�ܣ�");
			continue;
		}
		else
		{
			AfxMessageBox("success.\n");
		}

		Sleep(100);
		UpdateData(FALSE);
		m_Name_ID.ReleaseBuffer();
		InvalidateRect(NULL, FALSE);
	}	
	
}


BOOL CFaceOper::AddPersonInfo(unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages)
{
	if (NULL == pstPersonInfo)
		return FALSE;

	STU_FACE_ADD_IN_PARAM stInParam = { 0 };
	STU_FACE_ADD_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;
	
	stInParam.nImageCount = vecImages.size();
	memcpy(&stInParam.stPersonInfo, pstPersonInfo, sizeof(STU_PERSON_INFO));

	CString strImageFiles = "";
	std::vector<CString>::iterator iter = vecImages.begin();
	while (iter != vecImages.end())
	{
		strImageFiles.Append(*iter);
		strImageFiles.AppendChar('|');  // ͼƬ·���� ��|�� �ָ�
		iter++;
	}
	strImageFiles = strImageFiles.TrimRight('|');

	/*stInParam.lpszImageFiles = new char[vecImages.GetLength() + 1];
	memset(stInParam.lpszImageFiles, 0x00, vecImages.GetLength() + 1);
	memcpy(stInParam.lpszImageFiles, vecImages.GetBuffer(0), vecImages.GetLength());
*/
	stInParam.lpszImageFiles = new char[strImageFiles.GetLength() + 1];
	memset(stInParam.lpszImageFiles, 0x00, strImageFiles.GetLength() + 1);
	memcpy(stInParam.lpszImageFiles, strImageFiles.GetBuffer(0), strImageFiles.GetLength());
	

	if (TRUE != Net_AddPersonInfo(m_lLoginID, &stInParam, &stOutParam))
	{
		//AfxMessageBox("Error | AddPersonInfo fail.\n");
		delete[] stInParam.lpszImageFiles;
		return FALSE;
	}

	delete[] stInParam.lpszImageFiles;
	return TRUE;
}

BOOL CFaceOper::CheckNameSuffix(IN const char* lpszName, OUT char* lpszNewName, int nNewNameLen)
{
	if (NULL == lpszName || NULL == lpszNewName)
	{
		AfxMessageBox("Error | Person page error.\n");
		return FALSE;
	}

	memset(lpszNewName, 0x00, nNewNameLen);

	STU_PERSON_NAME_CHECK_IN_PARAM stInParam = { 0 };
	STU_PERSON_NAME_CHECK_OUT_PARAM stOutParam = { 0 };
	memcpy(stInParam.szName, lpszName, strlen(lpszName));

	if (TRUE != Net_CheckPersonNameSuffix(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");

		return FALSE;
	}

	if (0 == stOutParam.nSuffix)
	{
		memcpy(lpszNewName, lpszName, strlen(lpszName));
	}
	else
	{
		sprintf_s(lpszNewName, nNewNameLen, "%s%d", lpszName, stOutParam.nSuffix);
	}

	return TRUE;
}




//////////////////////////�ϴ�����///////////////////////////////////////////////////