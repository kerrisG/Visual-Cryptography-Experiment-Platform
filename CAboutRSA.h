#pragma once


// AboutRSA �Ի���

class AboutRSA : public CDialog
{
	DECLARE_DYNAMIC(AboutRSA)

public:
	AboutRSA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AboutRSA();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTRSA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
