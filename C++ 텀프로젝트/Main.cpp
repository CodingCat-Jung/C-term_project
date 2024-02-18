#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Memo.h"
using namespace std;

const int SIZE = 80;

int menu()
{
	int num;
	cout << "\n";
	cout << "====================\n";
	cout << "1.\t�ۼ�\t\n";
	cout << "2.\t����\t\n";
	cout << "3.\t����\t\n";
	cout << "4.\t����\t\n";
	cout << "5.\tEnd\t\n";
	cout << "====================\n";

	cin >> num;
	cin.get(); // ���� ���ڸ� ����
	return num;
}

int main() {
	NoteBook note("memo");

	// cnt : �޸�� ī��Ʈ
	int cnt;

	// num : page ���ڰ� ���� ����
	// sel : �޴� �ܰ迡�� ����� ���� ��� ���� ����
	int num, sel, j, k;

	char buff[SIZE]; // ���ڿ��� �Է¹޴� �ӽ� ����

	// cnt ����
	cnt = note.Count() + 1; // ����Լ��� ī���ʹ� 0���� ī��Ʈ�Ǳ� ������ +1

	do {
		sel = menu();
		switch (sel)
		{
			// 1. �ۼ�
		case 1:
			// ī��Ʈ�� 5���� ũ�� ���̻� �ۼ� x
			// �޸� �������� ���� �Է� ����
			note.file_Open();
			cout << "�ۼ��� �޸� ������ ��ȣ�� �Է��ϼ��� : "; cin >> num;

			// ���ڿ��� �Էµ� ��� ����ó��
			if (cin.fail()) {
				cerr << "�ùٸ��� ���� �Է��Դϴ�." << endl;
				cin.clear(); // �Է� ���� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
				continue;
			}

			// ���� üũ
			if (num > 5 || num <= 0) { // �޸����� ���� 1 ~ 5
				cout << "������ ������ϴ�." << endl;
				continue;
			}
			
			cout << "�޸� ������ �Է��ϼ���: "; cin >> buff;

			if (cin.fail()) {
				cerr << "�Է��� �ʹ� ��ϴ�. ���� ũ�� �ʰ�." << endl;
				cin.clear(); // �Է� ��Ʈ�� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
				continue;
			}

			note.write(num - 1, buff); // contents[NUM] �迭�� �ش� �ε����� ���� �ӽ� ����
			
			break;

			// 2. ����
		case 2:
			// ī��Ʈ�� ��ġ���� �����ֱ�
			// c_str() : ��Ʈ�� Ŭ������ ���ڿ��� C ��Ʈ�� �������� ��ȯ
			// ���ڿ��� �� 8���ڸ� ǥ��(������ ���) : ���� �޸��� ȿ��

			// �����ϴ� ���� ���� ���
			note.display();

			cout << "\n�޸� ������ ��ȣ�� �Է��ϼ��� ( Back is 0 ) : ";
			cin >> num;
			cin.get();

			// ���ڿ��� �Էµ� ��� ����ó��
			if (cin.fail()) {
				cerr << "�ùٸ��� ���� �Է��Դϴ�." << endl;
				cin.clear(); // �Է� ���� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
				continue;
			}

			if (num == 0) // 0�� �Է½� �ڷ� (�޴�â����)
			{
				break;
			}
			else if (num > note.Count() && num < 0)// ���� ��� ���
			{
				cout << "������ ������ϴ�." << endl;
			}
			else // �޸��� ��ü ����
			{
				string memoContent = note.look(num - 1);
			}

			break;

			// 3. ����
		case 3:
			// ���� �� �޸� ������ �Է� ����
			note.file_Open();
			cout << "������ �޸� ������ ��ȣ�� �Է��ϼ��� : ";
			cin >> num;
			cin.get();

			// ���ڿ��� �Էµ� ��� ����ó��
			if (cin.fail()) {
				cerr << "�ùٸ��� ���� �Է��Դϴ�." << endl;
				cin.clear(); // �Է� ���� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
				continue;
			}

			// ���� üũ
			if (num > note.Count() && num <= 0) {
				cout << "������ ������ϴ�." << endl;
				continue;
			}

			// �� ���ڿ� ���� �Է� ����
			cout << "�� ������ �Է��ϼ���: "; cin >> buff;

			// ���� �޸� �� ���ڿ��� ��ü
			note.edit(num - 1, buff);

			break;

			// 4. ����
		case 4:
			// ������ �޸� ������ �Է� ����
			note.file_Open();
			cout << "������ �޸� ������ ��ȣ�� �Է��ϼ��� : ";
			cin >> num;
			cin.get();

			// ���ڿ��� �Էµ� ��� ����ó��
			if (cin.fail()) {
				cerr << "�ùٸ��� ���� �Է��Դϴ�." << endl;
				cin.clear(); // �Է� ���� �ʱ�ȭ
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �Է� ���� ����
				continue;
			}

			// ���� üũ
			if (num > note.Count() && num <= 0) {
				cout << "������ ������ϴ�." << endl;
				continue;
			}

			// �޸� ����
			note.remove(num - 1);

			break;

			// 5. End
		case 5:
			cout << "Program end. \n";
			break;

		default:
			// �޴� �Է� ������ ��� ���
			cout << "Input Error. Try again. \n";
			break;
		}
	} while (sel != 5);

	return 0;
}