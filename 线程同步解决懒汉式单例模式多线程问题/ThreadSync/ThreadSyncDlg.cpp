
// ThreadSyncDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThreadSync.h"
#include "ThreadSyncDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreadSyncDlg �Ի���



CThreadSyncDlg::CThreadSyncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadSyncDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadSyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadSyncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadSyncDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CThreadSyncDlg ��Ϣ�������

BOOL CThreadSyncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CThreadSyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CThreadSyncDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CThreadSyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////////
// Singleton.cpp : �������̨Ӧ�ó������ڵ㡣
//

/*����ʽ����ģʽ���߳�����*/
/*�����ٽ�����֤����ģʽ����ȷ��*/

//����ʽ����

static CCriticalSection cs;

class Singleton
{
private:
	Singleton()
	{
		cout << "Singleton constructor called!" << endl;
	}
	~Singleton()
	{
		cout << "Singleton deconstructor called!" << endl;
	}

public:
	static Singleton* getInstance()		//��ȡʵ��
	{
		if (m_psl == NULL)
		{
			cs.Lock();		   //ֻ�е�m_pslΪ��ʱ�ſ�ʼ��������	 ���μ��
			if (m_psl == NULL)
				m_psl = new Singleton();

			cs.Unlock();
		}
		return m_psl;
	}

	static void freeInstance()		//�ͷ�ʵ��
	{
		if (m_psl != NULL)
		{
			delete m_psl;
			m_psl = NULL;
		}
	}

	void print()
	{
		cout << "Singleton test!" << endl;
	}

private:
	static Singleton *m_psl;
};

Singleton* Singleton::m_psl = NULL;

//////////////////////////////////////////////////////////////////////////////
void threadProc(void *)
{
	Singleton::getInstance()->print();
}

void CThreadSyncDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//main1();
	HANDLE thread[10];

	for (int i = 0; i < 3; i++)
	{
		thread[i] = (HANDLE)_beginthread(threadProc, 0, NULL);
		if (thread[i] == NULL)
		{
			cout << "�߳�" << i << "����ʧ��" << endl;
			break;
		}
	}

	//�������߳�,�ó�cpu,�ȴ����е����̶߳�ִ����Ϻ��ټ���ִ��
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(thread[i], INFINITE);  //�ڶ�������Ϊ�ȴ�ʱ��
	}
}
