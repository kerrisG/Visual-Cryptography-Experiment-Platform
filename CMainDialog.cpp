// CMainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "CMainDialog.h"
#include "afxdialogex.h"

#include "CLieZhihuan.h"
#include "CZhouqiZhihuan.h"
#include "CYiweiDaihuan.h"
#include "CVigenere.h"
#include "AESDlg.h"
#include "RSADialog.h"
#include "YuePuDialog.h"

#include "CAboutGUDIAN.h"
#include "CAboutAES.h"
#include "CAboutRSA.h"
#include "CAboutHELP.h"

// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialog)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(menu, pParent)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CMainDialog::OnBnClickedCancel)

	ON_COMMAND(ID_32785, &CMainDialog::Liezh)
	ON_COMMAND(ID_32786, &CMainDialog::Zhouqi)
	ON_COMMAND(ID_32787, &CMainDialog::Yiwei)
	ON_COMMAND(ID_32788, &CMainDialog::Vige)

	ON_COMMAND(ID_AES_ECB32776, &CMainDialog::OnAesECB)
	ON_COMMAND(ID_AES_CBC32777, &CMainDialog::OnAesCBC)
	
	ON_COMMAND(ID_RSA_32779, &CMainDialog::OnRSA)

	ON_COMMAND(ID_yuepu_32793, &CMainDialog::OnMusic)
	ON_COMMAND(ID_DANCE_32794, &CMainDialog::OnDance)

	ON_COMMAND(ID_32773, &CMainDialog::AboutGD)
	ON_COMMAND(ID_32778, &CMainDialog::Aboutaes)
	ON_COMMAND(ID_32780, &CMainDialog::Aboutrsa)
	ON_COMMAND(ID_32784, &CMainDialog::Abouthelp)
END_MESSAGE_MAP()


// CMainDialog 消息处理程序




void CMainDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CMainDialog::Liezh()
{
	CLieZhihuan dlg;
	dlg.DoModal();
}


void CMainDialog::Zhouqi()
{
	CZhouqiZhihuan dlg;
	dlg.DoModal();
}


void CMainDialog::Yiwei()
{
	CYiweiDaihuan dlg;
	dlg.DoModal();
}


void CMainDialog::Vige()
{
	CVigenere dlg;
	dlg.DoModal();
}

void CMainDialog::OnAesECB()
{
	CAESDlg dlg;
	dlg.mode = MODE_ECB;
	dlg.DoModal();
}

void CMainDialog::OnAesCBC()
{
	CAESDlg dlg;
	dlg.mode = MODE_CBC;
	dlg.DoModal();
}

void CMainDialog::OnRSA()
{
	CRSADialog dlg;
	dlg.DoModal();
}

void CMainDialog::OnMusic()
{
	CYuePuDialog dlg;
	dlg.DoModal();
}


void CMainDialog::OnDance()
{
	CYuePuDialog dlg;
	dlg.yuepu = false;
	dlg.DoModal();
}


void CMainDialog::AboutGD()
{
	AboutGUDIAN dlg;
	dlg.DoModal();
}


void CMainDialog::Aboutaes()
{
	AboutAES dlg;
	dlg.DoModal();
}


void CMainDialog::Aboutrsa()
{
	AboutRSA dlg;
	dlg.DoModal();
}


void CMainDialog::Abouthelp()
{
	AboutHELP dlg;
	dlg.DoModal();
}
