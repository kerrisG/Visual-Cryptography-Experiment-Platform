#pragma once


// AboutAES �Ի���

class AboutAES : public CDialog
{
	DECLARE_DYNAMIC(AboutAES)

public:
	AboutAES(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AboutAES();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTAES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeRichedit21();
};