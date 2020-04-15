// CLieZhihuan.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "CLieZhihuan.h"
#include "afxdialogex.h"
#include "utils.h"

// CLieZhihuan 对话框
IMPLEMENT_DYNAMIC(CLieZhihuan, CDialog)

CLieZhihuan::CLieZhihuan(CWnd* pParent /*=NULL*/)
	: CDialog(LieZhihuan, pParent)
	, m_strPlain(_T(""))
	, m_strCipher(_T(""))
	, m_strPlain2(_T(""))
{
	m_strKey = _T("1234567890");    //默认密钥
	M = 0;
}

CLieZhihuan::~CLieZhihuan()
{	
}

void CLieZhihuan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PLAIN, m_strPlain);
	DDX_Text(pDX, IDC_EDITCPHER, m_strCipher);
	DDX_Text(pDX, IDC_EDITPLAIN2, m_strPlain2);
	DDX_Text(pDX, IDC_EDIT1, m_strKey);
}


BEGIN_MESSAGE_MAP(CLieZhihuan, CDialog)
	ON_BN_CLICKED(IDC_ENCRPY2, &CLieZhihuan::OnBnClickedEncrpy2)
	ON_BN_CLICKED(IDC_DECRYP2, &CLieZhihuan::OnBnClickedDecryp2)
	ON_BN_CLICKED(IDC_CLEAR2, &CLieZhihuan::OnBnClickedClear2)
END_MESSAGE_MAP()

BOOL CLieZhihuan::OnInitDialog()
{
	CDialog::OnInitDialog();

	LOGFONT logfont;
	GetFont()->GetLogFont(&logfont);
	logfont.lfHeight = 24; // 改变字体高度  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_EDIT_PLAIN)->SetFont(font);
	GetDlgItem(IDC_EDITCPHER)->SetFont(font);
	GetDlgItem(IDC_EDITPLAIN2)->SetFont(font);

	return TRUE;
}

#define LENGTH 26 
string lezhihuan(string keystr,string plainstr,int out)
{
	int i, j, l, k, m, num[300];
	char key[300], plantext[1000], plantext2[1000], cipher[1000];
	
	strcpy(key, keystr.c_str());          //得到密钥
	l = strlen(key);
	for (i = 0; i<l; i++)                 //按照密钥得到明文打乱后的顺序
	{
		num[i] = 0;
		for (j = 0; j<l; j++)
		{

			if (key[j] <= key[i])
			{

				num[i] = num[i] + 1;
			}
			if (key[j] == key[i] && j>i)
				num[i] = num[i] - 1;

		}
	}
	strcpy(plantext, plainstr.c_str());            //得到明文
	k = strlen(plantext);

	i = 0;											//末尾补x
	for (m = k%l; m<l; m++)
	{

		plantext[k + i] = 'x';
		i++;
	}

	if (k%l == 0)								    //计算有多少行
		m = k / l;
	else
		m = k / l + 1;
	printf("Encryption:\n");
	for (i = 0; i<m; i++)                             //加密
	{
		for (j = 0; j<l; j++)
		{

			cipher[i*l + j] = plantext[i*l + num[j] - 1];

		}
	}

	char cout[1000] = { 0 };
	int  cidx = 0;
	for (i = 0; i<l; i++)								//输出密文
	{
		for (j = 0; j<m; j++)
			cout[cidx++] = cipher[j*l + i];
	}
	if (out == 0)
		return cout;

	                                                   //解密	
	for (i = 0; i<m; i++)
	{
		for (j = 0; j<l; j++)
		{

			plantext2[i*l + num[j] - 1] = cipher[i*l + j];
		}
	}
	plantext2[(i - 1)*l + j] = '\0';
	return plantext2;
}

bool CLieZhihuan::checkKey()
{
	UpdateData();
	if (m_strKey.IsEmpty())
	{
		MessageBox(L"Please enter the key first!", L"Notice", MB_ICONWARNING);
		return false;
	}

	m_strKey.MakeLower();	

	return true;
}

void CLieZhihuan::OnBnClickedEncrpy2()           //加密函数
{
	if (!checkKey())
		return;

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strPlain == "")
	{
		MessageBox(L"Please enter plain text first!", L"Notice", MB_ICONWARNING);
		return;
	}
	m_strCipher.Empty();
	
	string keystr = CStr_to_str(m_strKey);
	string plain = CStr_to_str(m_strPlain);

	m_strCipher = str_to_CStr(lezhihuan(keystr,plain,0));
	UpdateData(FALSE);

}


void CLieZhihuan::OnBnClickedDecryp2() //解密函数
{
	if (!checkKey())
		return;

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strCipher == "")
	{
		MessageBox(L"Please generate cipher text first!", L"Notice", MB_ICONWARNING);
		return;
	}

	string Keystr = CStr_to_str(m_strKey);
	string plainstr = CStr_to_str(m_strPlain);
	string cipherStr = CStr_to_str(m_strCipher);


	m_strPlain2 = str_to_CStr(lezhihuan(Keystr, plainstr, 1));
	UpdateData(FALSE);
}


void CLieZhihuan::OnBnClickedClear2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strPlain = m_strCipher = m_strPlain2 = "";
	UpdateData(FALSE);
}