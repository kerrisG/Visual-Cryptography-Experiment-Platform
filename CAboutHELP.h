#pragma once


// AboutHELP �Ի���

class AboutHELP : public CDialog
{
	DECLARE_DYNAMIC(AboutHELP)

public:
	AboutHELP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AboutHELP();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTHELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
