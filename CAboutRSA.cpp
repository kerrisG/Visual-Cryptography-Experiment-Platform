// CAboutRSA.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "CAboutRSA.h"
#include "afxdialogex.h"


// AboutRSA 对话框

IMPLEMENT_DYNAMIC(AboutRSA, CDialog)

AboutRSA::AboutRSA(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTRSA, pParent)
{

}

AboutRSA::~AboutRSA()
{
}

void AboutRSA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutRSA, CDialog)
END_MESSAGE_MAP()


// AboutRSA 消息处理程序
BOOL AboutRSA::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutRSA.txt"), CFile::modeRead);           //打开文件
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
	logfont.lfHeight = 18; // 改变字体高度  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_RICHEDIT21)->SetFont(font);


	return TRUE;
}