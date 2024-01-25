#pragma once

#include <iostream>
#include <string>


using namespace std;

class Date
{
protected:
	int day;
	int month;
	int year;
	int hours;
	int minutes;

public:
	string getDate(){ return to_string(day) + "." + to_string(month) + "." + to_string(year) + " " + to_string(hours) + ":" + to_string(minutes); }
	void setDate();
	void setDate(string strDate);
};

class CreationDate : public Date
{
public:
	int getCreationDate() { return day; };
};

class EditDate : public Date
{
public:
	void changeDate(string name);
};