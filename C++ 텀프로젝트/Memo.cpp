#include <iostream>
#include <cstring>
#include <cstdio>

#include "Memo.h"

using namespace std;

#define FILE_SIZE 5

// �⺻ ������
NoteBook::NoteBook() {

	// count�� �����ϴ� ���� �б� �õ�
	ifstream countFile("count.txt");
	if (countFile.is_open()) {
		countFile >> count; // ���Ͽ��� count ���� �о��
		countFile.close();
	}
	else {
		cerr << "����: count�� �о���� �� �����߽��ϴ�." << endl;
		count = 0; // ������ �о���� ���� ��� �⺻������ �ʱ�ȭ
	}

}

// ���ϸ��� �Է¹޴� ������
NoteBook::NoteBook(string noteName) : NoteBook() {

	this->noteName = noteName;

	// open() �Լ� ȣ�� - ���� �ε�
	open(noteName); // ��Ʈ �� �� ����ڰ� ������ �̸����� �ʱ�ȭ

}

// �Ҹ��� �Լ�
NoteBook::~NoteBook() {
	// ���Ͽ� count ���� ����
	ofstream countFile("count.txt");
	if (countFile.is_open()) {
		countFile.clear();
		countFile << count << endl;
		countFile.flush();
	}

	// close() �Լ� ȣ�� - ���� ����
	close();

}

// ���� ���� �Լ�
// ���� �ε带 ���� �Լ� - �����ڿ��� ȣ��
void NoteBook::open(string noteName) {

	// �ؽ�Ʈ ���Ͽ��� ���� �о�� contents[NUM] �迭�� ����
	for (int i = 0; i < FILE_SIZE; i++) {

		string fileName = generateFileName(i);

		// fstream �ν��Ͻ� contentsFile�� �̿��Ͽ� ���� ���� - �б� �� ���� �뵵
		contentsFile.open(fileName, ios::in | ios::out);

		// ���� ���ȴ��� Ȯ�� �� �Ҹ� �� isOpen ������ ����
		isOpen = contentsFile.is_open();

		if (!isOpen) { // ���� ���� ����
			cout << "FILE = " << generateFileName(i) << " �� �������� ���� �����Դϴ�." << endl;
			continue;
		}

		getline(contentsFile, contents[i]); // �������� ������ �о contents �迭�� ����
		//cout << contents[i] << endl;
		contentsFile.close();
	}
}

// ���� �ݱ� �Լ�
// ���� ������ ���� �Լ� - �Ҹ��ڿ��� ȣ��
void NoteBook::close() {

	// ������ ���� ũ��(5)��ŭ �ݺ� - contents �迭���� ���� ���Ͽ� ���� �� ���� �ݱ�
	// �����ϴ� ���ϸ� ����, �������� �ʴ� ������ �н�
	for (int i = 0; i < FILE_SIZE; i++) {

		if (contents[i]=="") { // �������� �ʴ� ����
			continue;
		}

		else if (isOpen) {
			// contents �迭�� ������ �����ϸ� - �����ϴ� ������ ���
			string fileName = generateFileName(i);

			// fstream �ν��Ͻ� contentsFile�� �̿��Ͽ� ���� ���� - ���� �뵵
			contentsFile.open(fileName, ios::out);

			// ���� ���ȴ��� Ȯ�� �� �Ҹ� �� isOpen ������ ����
			isOpen = contentsFile.is_open();

			contentsFile << contents[i]; // �ؽ�Ʈ ���Ͽ� �迭�� ����Ǿ� �ִ� ���� ����
		}
		
		contentsFile.close();
	}
}

// ������ ���ϸ� ���� ex) memo01.txt ...
string NoteBook::generateFileName(int i) {
	// �⺻ ���ϸ� ����
	char defaultName[BUFSIZ] = "\0";

	strcpy(defaultName, noteName.c_str());
	// c_str() : C-string ó�� string�� ������ ��ȯ
	strcat(defaultName, "00.txt");

	// �� ���ϸ� ����
	static char page[100];
	strcpy(page, defaultName); // �⺻ ���ϸ� ����
	int location = strlen(noteName.c_str());

	char number[3];
	sprintf(number, "%02d", i); // ������ ��ȣ�� �� �ڸ� ������ ��ȯ�Ͽ� ����
	// sprintf returns the number of bytes stored in buffer
	strncpy(page + location, number, 2); // ������ ��ȣ�� ���ϸ� �߰�
	// not counting the terminating null character

	return page; // ������ ���ϸ� ��ȯ
}

// �޸� �� ��ȯ �Լ�
int NoteBook::Count() const {
	return count;
}

// �޸� �ۼ� �Լ�
// page�� �ش��ϴ� �ε��� ��ȣ�� content ���� �ۼ�
void NoteBook::write(int page, string content) {

	// �������� 0 ~ 4
	if (page < 0 && page > NUM) {
		cout << "������ ��ȣ�� �߸� �ԷµǾ����ϴ�." << endl;
		return;
	}

	// ������ �������� �ʴ� ��쿡�� ���� ���� �� contents �迭�� ���� �ۼ�, count ����
	// ������ �����ϴ� ��쿡�� �н�
	string filename = generateFileName(page); // ���ϸ� ����

	ifstream testFile(filename.c_str());

	if (!testFile) { // ������ �������� ������
		testFile.close();
		ofstream newFile(filename.c_str()); // �� ���� ����

		newFile.close();

		contents[page] = content; // �ش� �迭�� �ε����� ���� ����
		count++; // �� ������ �����Ǿ����Ƿ� count ����

		cout << "���������� ���ο� ������ �����ϰ� �ۼ��Ǿ����ϴ�." << endl;
	}
	else { // ������ �����ϴ� ���
		cout << "�̹� �����ϴ� �����Դϴ�." << endl;
	}
}

// �޸� ��ȸ �Լ�
// page�� �ش��ϴ� �ε��� ��ȣ�� ������ ���
string& NoteBook::look(int page) {

	// ��ȿ�� page ������ ���
	if (page >= 0 && page < NUM) {
		cout << "�����Ͻ� " << page << "������ �����Դϴ�." << endl;
		cout << contents[page] << endl; // ������ ������ ���� contents �迭���� �о�� ���
		return contents[page];
	}

	else cout << "������ ������ϴ�." << endl;

	return contents[0];
}

// �޸� ���� �Լ�
// page�� �ش��ϴ� �ε��� ��ȣ�� ������ �Ű����� content �������� �ٲ�
void NoteBook::edit(int page, string content)
{
	// ��ȿ�� ������ ������ ���
	if (page >= 0 && page < NUM) {
		// �ش� �������� ������ �Ű������� ���� content�� ����
		contents[page] = content;
		cout << "���������� ������ �����Ǿ����ϴ�." << endl;
	}
	else {
		cerr << "�߸��� ������ ��ȣ�Դϴ�." << endl;
	}
}

// �޸� ���� �Լ�
// page�� �ش��ϴ� �ε��� ��ȣ�� �޸� ��� ����
void NoteBook::remove(int page) {
	// ��ȿ�� page ������ ���
	if (page >= 0 && page < NUM) {

		// �ش� �������� ������ ����
		contents[page] = ""; 
		cout << "���������� �ش� ������ ������ �����Ͽ����ϴ�." << endl;
		
		// �ش� ������ �ؽ�Ʈ ���� ����
		contentsFile.close(); // ������ �����ϱ� ���� �ݱ�

		// ���� ����
		string filename = generateFileName(page);

		//system("icacls filename /grant �����:����");

		if (std::remove(filename.c_str()) == 0) {
			cout << "���������� ������ �����߽��ϴ�." << endl;
			count--;
		}
		else {
			cerr << "������ �����ϴ� �߿� ������ �߻��߽��ϴ�." << endl;
		}

	}
	else {
		cerr << "�߸��� ������ ��ȣ�Դϴ�." << endl;
	}
}

// main()���� 2�� ���� ���� �� ���
// �����ϴ� ���� ���� ��� �Լ�
void NoteBook::display() {
	for (int i = 0; i < FILE_SIZE; i++) {

		string fileName = generateFileName(i);

		// fstream �ν��Ͻ� contentsFile�� �̿��Ͽ� ���� ���� - �б� 
		contentsFile.open(fileName, ios::in);

		// ���� ���ȴ��� Ȯ�� �� �Ҹ� �� isOpen ������ ����
		isOpen = contentsFile.is_open();

		if (!isOpen) { // ���� ���� ����
			cout << "num " << i + 1 << ". ";
			cout << "FILE = " << generateFileName(i) << " �� �������� ���� �����Դϴ�." << endl;
			continue;
		}

		else if (isOpen) {
			cout << "num " << i + 1 << ". ";
			cout << "�޸� ������ " << i + 1 << " ���� : ";
			cout << contents[i] << endl;
		}
		contentsFile.close();
	}
}

void NoteBook::file_Open() {

	// �����ϴ� ���� ���
	for (int i = 0; i < FILE_SIZE; i++) {

		string fileName = generateFileName(i);

		// fstream �ν��Ͻ� contentsFile�� �̿��Ͽ� ���� ���� - �б� 
		contentsFile.open(fileName, ios::in);

		// ���� ���ȴ��� Ȯ�� �� �Ҹ� �� isOpen ������ ����
		isOpen = contentsFile.is_open();

		if (!isOpen) { // ���� ���� ����
			cout << "num " << i + 1 << ". ";
			cout << "FILE = " << generateFileName(i) << " �� �������� ���� �����Դϴ�." << endl;
			continue;
		}

		cout << "num " << i + 1 << ". ";
		cout<< "memo0" << i << ".txt ���� ������" << endl;

		contentsFile.close();
	}
}