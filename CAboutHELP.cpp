// CAboutHELP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "code.h"
#include "CAboutHELP.h"
#include "afxdialogex.h"


// AboutHELP �Ի���

IMPLEMENT_DYNAMIC(AboutHELP, CDialog)

AboutHELP::AboutHELP(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTHELP, pParent)
{

}

AboutHELP::~AboutHELP()
{
}

void AboutHELP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutHELP, CDialog)
END_MESSAGE_MAP()


// AboutHELP ��Ϣ�������
BOOL AboutHELP::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutHELP.txt"), CFile::modeRead);           //���ļ�
	char *pBuf;
	int iLen = file1.GetLength();
	pBuf = new char[iLen + 1];
	file1.Read(pBuf, iLen);
	pBuf[iLen] = 0;
	file1.Close();
	CString Buf;
	Buf = pBuf;
	SetDlgItemText(IDC_RICHEDIT21, Buf);


	LOGFONT logfont;
	GetFont()->GetLogFont(&logfont);
	logfont.lfHeight = 18; // �ı�����߶�  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_RICHEDIT21)->SetFont(font);


	return TRUE;
}