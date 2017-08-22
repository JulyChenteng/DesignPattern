// Singleton.cpp : �������̨Ӧ�ó������ڵ㡣
//

/*����ʽ����ģʽ���߳������׳�*/
/*���߳�������ʽ���ܱ�֤�ǵ���ģʽ, ���ǿ���ͨ���ٽ����ȷ��������֤���ڶ��߳����ǵ�����*/
#include "stdafx.h"
#include <process.h>
#include "afxmt.h"
#include "winbase.h"

#include <iostream>
using namespace std;

static CCriticalSection cs;

//����ʽ����
class Singleton
{
private:
	Singleton()
	{
		cout << "Singleton constructor called!\n";
	}
	~Singleton()
	{
		cout << "Singleton deconstructor called!\n";
	}

public:
	static Singleton* getInstance()		//��ȡʵ��
	{
		if (m_psl == NULL)
		{
			cs.Lock();
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
		cout << "Singleton test!\n";
	}

private:
	static Singleton *m_psl;
};

Singleton* Singleton::m_psl = NULL;

void MyThreadFunc(void *)
{
	Singleton::getInstance()->print();
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE thread[10];

	for (int i = 0; i < 3; i++)
	{
		thread[i] = (HANDLE)_beginthread(MyThreadFunc, 0, NULL);
		if (thread[i] == NULL)
			cout << "�߳�" << i << "����ʧ��" << endl;
	}

	//�������߳�,�ó�cpu,�ȴ����е����̶߳�ִ����Ϻ��ټ���ִ��
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(thread[i], INFINITE);  //�ڶ�������Ϊ�ȴ�ʱ��
	}

	Singleton::freeInstance();

	return 0;
}

