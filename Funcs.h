#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <map>
#include "Note.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS


using namespace std::filesystem;
using namespace std;

map<string, Note> loadFromFiles();
int countWithTag(string tag, map<string, Note>& notes);
int countWithAuthor(string author, map<string, Note>& notes);
vector<Note> findNotesWithAuthor(map<string, Note>& notes, string author);
vector<Note> findNotesWithTag(map<string, Note>& notes, string tag);
vector<Note> filterNotesWithDate(map<string, Note>& notes, int day);

static class ComparerTags
{
	string _tag;

public:
	ComparerTags(string tag) : _tag(tag) {}

	bool operator() (pair<string,Note> p)
	{
		vector<string> tags= p.second.getTags();
		return find(tags.begin(), tags.end(), _tag) != tags.end();
	}
};

static class ComparerDates
{
	int _days;
	int currDate;
public:
	ComparerDates(int days) : _days(days) {
		time_t Now = time(0);
		tm* time = localtime(&Now);
		currDate = time->tm_mday;
	}

	bool operator() (pair<string, Note> p)
	{
		return currDate - p.second.getCreationDateInt() < _days;
	}
};
