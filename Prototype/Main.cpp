#include "PrototypeManager.h"
#include "Object.h"


//Object* pObjList[3];
list<Object*>  ObjList;

void InitObject(string _Key)
{
	//** PrototypeManager ���� ���� ��ü�� ã�ƿ�.
	Object* pObj = PrototypeManager::GetInstance()->FineObject(_Key);

	//** ã������ ��ü�� ���ٸ�...
	if (pObj == nullptr)
	{
		//** ���� �޽����� ����ϰ�...
		COORD Pos = { (SHORT)50, (SHORT)15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		cout << "������ ���� ��ü�� �����ϴ�." << endl;

		// ** �Լ� ����.
		return;
	}


	// ** ������ü�� ���������� �����ߴٸ�...
	// ** pObjList �� �ʱ�ȭ
	for (int i = 0; i < 3; ++i)
	{
		// ** ������ ���� ��ü�� ���纻�� �Ѱ���
		Object* pTempObj = pObj->Clone();

		// ** �׸��� ���纻�� �ʱ�ȭ��.
		pTempObj->Initialize();

		// ** ���纻�� �ε������� ����.
		pTempObj->SetIndex(i + 1);

		// ** ����Ʈ�� �߰�
		ObjList.push_back(pTempObj);
	}
}



int main(void)
{
	//** PrototypeManager �ʱ�ȭ (�ʱ�ȭ�� ����Ǹ� ������ü�� �����Ѵ�.)
	PrototypeManager::GetInstance()->Initialize();

	//** �ʱ�ȭ
	InitObject("Object");

	//** ���
	for (list<Object*>::iterator iter = ObjList.begin();
		iter != ObjList.end(); ++iter)
			(*iter)->Render();

	//** ����
	for (list<Object*>::iterator iter = ObjList.begin();
		iter != ObjList.end(); ++iter)
	{
			delete (*iter);
			(*iter) = nullptr;
	}
	
	return 0;
}


/**********************
 * �ʱ� ����
 * ������׿� ���� ����
 * ��� ����
 * ����
***********************/

