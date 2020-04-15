#pragma once


// AboutRSA 对话框

class AboutRSA : public CDialog
{
	DECLARE_DYNAMIC(AboutRSA)

public:
	AboutRSA(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutRSA();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTRSA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
