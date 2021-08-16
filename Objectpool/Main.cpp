#include <iostream>
#include <Windows.h>
#include <list>
#include <map>
#include <string>

using namespace std;

struct Vector3
{
	float x, y;

	Vector3() : x(0), y(0) {}

	Vector3(float _x, float _y) : x(_x), y(_y) {}
};


struct Transform
{
	Vector3 Position;
	Vector3 Scale;
};


class Object
{
private:
	string str;
	Transform TransInfo;
public:
	void Initialize()
	{
		str = "->";
		TransInfo.Position = Vector3(4.0f, 15.0f);
	}

	int Update()
	{
		TransInfo.Position.x++;

		if (TransInfo.Position.x >= 100)
			return 1;

		return 0;
	}

	void Render()
	{
		COORD Pos = { (SHORT)TransInfo.Position.x, (SHORT)TransInfo.Position.y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		cout << str << endl;
	}
public:
	Object() { }
	~Object() { }
};


bool check = false;
int Count = 0;


void Output(float _x, float _y, string _str);




int main(void)
{
	//** ���� ����� ������Ʈ (������ �� ������Ʈ ����Ʈ)
	list<Object*> EnableList;

	//** ����� ��ģ ������Ʈ ����Ʈ (������ ���� ����)
	list<Object*> DesableList;


	while (true)
	{
		system("cls");

		//** �Ѿ��� �߻�� ��ġ.
		Output(2, 15, "��");

		check = false;

		//** Ű �Է� �̺�Ʈ Ȯ��
		if (GetAsyncKeyState(VK_RETURN))
			//** �ѹ��� �Է¹ޱ�����.
			check = true;

		
		//** �Է��� �Ǿ��ٸ�..
		if (check)
		{
			//** DesableList �� ������ ������Ʈ�� �ִ��� Ȯ�� �ϰ� ���ٸ�...
			if (DesableList.empty())
			{
				//** 5���� ������Ʈ�� �߰� ������ ��...
				for (int i = 0; i < 5; ++i)
					DesableList.push_back( new Object );
			}

			//** �߰� ������ ������Ʈ �ϳ��� ����.
			list<Object*>::iterator iter = DesableList.begin();


			//** �ʱ�ȭ �� �ʿ��� ���� �ۼ�.
			(*iter)->Initialize();

			//** ����� ����Ʈ�� �߰�.
			EnableList.push_back((*iter));

			//** ���� ����Ʈ���� ����.
			DesableList.pop_front();
		}


		for (list<Object*>::iterator iter = EnableList.begin();
			iter != EnableList.end();)
		{
			int iResult = (*iter)->Update();
			(*iter)->Render();

			if (iResult == 1)
			{
				//** ���� ����Ʈ���� ����.
				DesableList.push_back((*iter));

				//** ����� ����Ʈ�� �߰�.
				iter = EnableList.erase(iter);
			}
			else
				++iter;
		}

		//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (DesableList)
		string Buffer = "DesableList : " + to_string(DesableList.size());
		Output(10, 1, Buffer);
		Buffer.clear();

		//** ���� ����Ʈ�� �����ִ� ������Ʈ�� ���� Ȯ��. (EnableList)
		Buffer = "EnableList : " + to_string(EnableList.size());
		Output(10, 2, Buffer);

		Sleep(50);
	}



	//** DesableList ���� ����
	for (list<Object*>::iterator iter = DesableList.begin();
		iter != DesableList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	DesableList.clear();


	//** EnableList ���� ����
	for (list<Object*>::iterator iter = EnableList.begin();
		iter != EnableList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	EnableList.clear();

	return 0;
}

void Output(float _x, float _y, string _str)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	cout << _str << endl;
}
