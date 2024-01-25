#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Date.h"

using namespace std;

class Note
{
private:
	string name;
	string author;
	string text;
	vector<string> tags;
	CreationDate creationDate;
	EditDate editDate;
	
public:
	string getName() { return name; }
	string getText() { return text; }
	string getAuthor() { return author; }
	vector<string> getTags() { return tags; }
	CreationDate getCreationDate() { return creationDate; }
	int getCreationDateInt() { return creationDate.getCreationDate(); }
	EditDate getEditDate(){ return editDate; }
	void saveFile();
	void showFile();
	void modifyFile(string text);
	Note(string name, string author, string text, vector<string> tags) {
		this->name = name;
		this->author = author;
		this->text = text;
		this->tags = tags;
		this->creationDate.setDate();
		this->editDate.setDate();
		this->saveFile();
	}
	Note(string txtFilePath) {
		ifstream txtfile;
		char buff[50];
		txtfile.open(txtFilePath);
		txtfile.getline(buff, 50);
		this->name = buff;
		txtfile.getline(buff, 50);
		this->author = buff;
		string val;
		txtfile.getline(buff, 50);
		string tags = buff;
		stringstream stream(tags);
		while (getline(stream, val, ' ')) {
			this->tags.push_back(val);
		}
		txtfile.getline(buff, 50);
		string dateStr = buff;
		dateStr.erase(dateStr.begin(), dateStr.begin() + 15);
		this->creationDate.setDate(dateStr);
		txtfile.getline(buff, 50);
		this->editDate.changeDate(this->name);
		while (!txtfile.eof()) {
			txtfile.getline(buff, 50);
			this->text += buff;
		}
	}
	Note() {

	}
};

