#pragma once


// AboutAES 对话框

class AboutAES : public CDialog
{
	DECLARE_DYNAMIC(AboutAES)

public:
	AboutAES(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutAES();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTAES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeRichedit21();
};