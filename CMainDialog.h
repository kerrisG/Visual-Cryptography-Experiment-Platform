#pragma once


// CMainDialog 对话框

class CMainDialog : public CDialog
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();

	afx_msg void Liezh();
	afx_msg void Zhouqi();
	afx_msg void Yiwei();
	afx_msg void Vige();
	afx_msg void OnAesECB();
	afx_msg void OnAesCBC();
	afx_msg void OnRSA();
	/*afx_msg void OnYuePU();*/
	afx_msg void OnMusic();
	afx_msg void OnDance();
	afx_msg void AboutGD();
	afx_msg void Aboutaes();
	afx_msg void Aboutrsa();
	afx_msg void Abouthelp();
};
