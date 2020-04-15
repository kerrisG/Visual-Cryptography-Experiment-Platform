#pragma once


// AboutHELP 对话框

class AboutHELP : public CDialog
{
	DECLARE_DYNAMIC(AboutHELP)

public:
	AboutHELP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutHELP();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTHELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
