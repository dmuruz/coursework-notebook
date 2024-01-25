#include "Note.h"
#include <fstream>


void Note::saveFile() {
	ofstream txtfile;
	txtfile.open(name + ".txt");
	txtfile << name << endl;
	txtfile << author << endl;

	for (auto& tag : tags) {
		txtfile << tag + " ";
	}
	txtfile << endl;
	txtfile << "���� ��������: " + creationDate.getDate() << endl;
	txtfile << "���� ���������: " + editDate.getDate() << endl;
	txtfile << endl;
	txtfile << text << endl;
}

void Note::showFile() {
	cout << this->name << endl;
	cout << this->author << endl;
	for (string tag : this->tags) {
		cout << tag + " ";
	}
	cout << endl;
	cout << "���� ��������: " << this->creationDate.getDate() << endl;
	cout << "���� ���������: " << this->editDate.getDate() << endl;
	cout << this->text << endl;
}

void Note::modifyFile(string text) {
	this->text += text;
	ofstream txtfile;
	txtfile.open(this->name + ".txt", ios_base::app);
	txtfile << text;
	txtfile.close();
	this->editDate.changeDate(this->name);
}