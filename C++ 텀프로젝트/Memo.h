#pragma once
#pragma warning (disable: 4996)
#ifndef MEMO_H
#define MEMO_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define NUM 5

class NoteBook {
	// Constructors and Destructors
public:
	NoteBook();
	NoteBook(string noteName);
	~NoteBook();

	// Methods
	void write(int page, string content); // page�� �ش��ϴ� �ε��� ��ȣ�� content ���� �ۼ�
	void edit(int page, string content); // page�� �ش��ϴ� �ε��� ��ȣ�� ������ �Ű����� content �������� �ٲ�
	string& look(int page); // page�� �ش��ϴ� �ε��� ��ȣ�� ������ ���
	void remove(int page); // page�� �ش��ϴ� �ε��� ��ȣ�� �޸� ��� ����

	void open(string noteName); 
	void close();
	int Count() const;

	void display();
	void file_Open();

	// instance variable
private:
	// ������ ���ϸ� ���� ex) noteName01.txt ...
	string generateFileName(int i);

	string contents[NUM]; // 5���� �޸� ������ ���ڿ�
	fstream contentsFile; // fstream �ν��Ͻ� contentsFile
	string noteName; // �޸� ���� �̸�
	bool isOpen; // �޸��� ������ ����
	int count; // �޸�� ī��Ʈ
};

#endif // !MEMO_H
