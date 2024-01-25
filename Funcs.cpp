#include "Funcs.h"

using namespace std;

int countWithTag(string tag, map<string, Note>& notes) {
	int res = 0;
	if (find_if(notes.begin(), notes.end(), ComparerTags(tag)) != notes.end()) {
		for (map<string, Note>::iterator  it = notes.begin(); it != notes.end(); ++it) {
			pair<string, Note> notePair = *it;
			vector<string> tags = notePair.second.getTags();
			if (find(tags.begin(), tags.end(), tag) != tags.end())
			{
				res++;
			}
		}
		return res;
	}
	return 0;
}

int countWithAuthor(string author, map<string, Note>& notes) {
	return count_if(notes.begin(), notes.end(), [author](pair<string, Note> p) { return p.second.getAuthor() == author; });
}

map<string, Note> loadFromFiles() {
	map<string, Note> res;
	directory_iterator begin("C:/Users/User/source/repos/Curs/Curs");
	directory_iterator end;
	vector<path> txtFiles;
	copy_if(begin, end, back_inserter(txtFiles), [](const path& path) {
		return is_regular_file(path) && (path.extension() == ".txt");
	});

	for (path p : txtFiles) {
		string pathStr = p.filename().string();
		pathStr.erase(pathStr.end() - 4, pathStr.end());
		res[pathStr] = Note(p.string());
	}
	return res;
}

vector<Note> findNotesWithAuthor(map<string, Note>& notes, string author)
{
	map<string, Note>::iterator it = notes.begin();

	vector<Note> result;
	while (it != notes.end())
	{
		it = find_if(it, notes.end(), [author](pair<string, Note> p) { return p.second.getAuthor() == author; });

		if (it == notes.end()) break;
		pair<string, Note> pair = *it;
		result.push_back(pair.second);
		++it;
	}

	return result;
}

vector<Note> findNotesWithTag(map<string, Note>& notes, string tag)
{
	map<string, Note>::iterator it = notes.begin();

	vector<Note> result;
	while (it != notes.end())
	{
		it = find_if(it, notes.end(), ComparerTags(tag));

		if (it == notes.end()) break;
		pair<string, Note> pair = *it;
		result.push_back(pair.second);
		++it;
	}

	return result;
}
vector<Note> filterNotesWithDate(map<string, Note>& notes, int day) {
	map<string, Note>::iterator it = notes.begin();

	vector<Note> result;
	while (it != notes.end())
	{
		it = find_if(it, notes.end(), ComparerDates(day));

		if (it == notes.end()) break;
		pair<string, Note> pair = *it;
		result.push_back(pair.second);
		++it;
	}

	return result;
}