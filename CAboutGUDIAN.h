#pragma once


// AboutGUDIAN 对话框

class AboutGUDIAN : public CDialog
{
	DECLARE_DYNAMIC(AboutGUDIAN)

public:
	AboutGUDIAN(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AboutGUDIAN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTgudian };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeRichedit21();
	afx_msg void OnBnClickedOk();
};
