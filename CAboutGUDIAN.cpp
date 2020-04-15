// CAboutGUDIAN.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "CAboutGUDIAN.h"
#include "afxdialogex.h"


// AboutGUDIAN 对话框

IMPLEMENT_DYNAMIC(AboutGUDIAN, CDialog)

AboutGUDIAN::AboutGUDIAN(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTgudian, pParent)
{

}

AboutGUDIAN::~AboutGUDIAN()
{
}

void AboutGUDIAN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutGUDIAN, CDialog)
	ON_EN_CHANGE(IDC_RICHEDIT21, &AboutGUDIAN::OnEnChangeRichedit21)
	ON_BN_CLICKED(IDOK, &AboutGUDIAN::OnBnClickedOk)
END_MESSAGE_MAP()


// AboutGUDIAN 消息处理程序

BOOL AboutGUDIAN::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutGD.txt"), CFile::modeRead);           //打开文件
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

void AboutGUDIAN::OnEnChangeRichedit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码


}


void AboutGUDIAN::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
