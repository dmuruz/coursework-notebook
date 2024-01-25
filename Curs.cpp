#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include "Note.h"
#include "Funcs.h"



using namespace std::filesystem;
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru-RU");

    path pathToFolder(L"C:/Users/User/source/repos/Curs/Curs");
    char mode = '.';
    map<string, Note> notes = loadFromFiles();


    string text, author, name ="";
    string tag = ".";
    vector<string> tags;
    vector<Note> res;
    int days;
    cout << "�������� ������ � ������:" << endl;

    while (mode != 'e') {
        cout << "�������� �������:" << endl;
        cout << "    c - ������� ������" << endl;
        cout << "    l - ��������� ������" << endl;
        cout << "    m - �������������� ������" << endl;
        cout << "    d - ������� ������" << endl;
        cout << "    t - ���������� ������� � ������������ �����" << endl;
        cout << "    a - ���������� ������� � ������������ �������" << endl;
        cout << "    f - ����� ������ � ������������ �����" << endl;
        cout << "    g - ����� ������ � ������������ �������" << endl;
        cout << "    r - ����� ������ ��������� �� ��������� N ����" << endl;

        cin >> mode;
        switch (mode)
        {
        case 'c':
            cout << "�������� ������:" << endl;
            cout << "������� �������� ������" << endl;
            getline(cin >> ws, name);
            while (exists(pathToFolder.concat("/" + name + ".txt"))) {
                cout << "������ � ������ ��������� ��� ����������. ���������� ������ ������ ��������" << endl;
                pathToFolder.remove_filename();
                getline(cin >> ws, name);
            }
            cout << "������� ������" << endl;
            getline(cin >> ws, author);
            cout << "������� ����. ��� ���������� �����, ������� / " << endl;
            tags.clear();
            while (tag != "/") {
                cin >> tag;
                if (tag != "/") {
                    tags.push_back(tag);
                }
            }
            cout << "������� ����� ������" << endl;
            getline(cin >> ws, text);
            notes[name] = Note(name, author, text, tags);
            break;
        case 'l':
            cout << "�������� ������:" << endl;
            cout << "������� �������� ������, ������� ����� �������:" << endl;
            cin >> name;
            if (notes.find(name) == notes.end()) {
                cout << "����� ������ ���." << endl;
            }
            else {
                cout << "������ ������:" << endl;
                notes[name].showFile();
            }
            break;
        case 'm':
            cout << "����������� ������:" << endl;
            cout << "������� �������� ������, ������� ����� ��������������:" << endl;
            cin >> name;
            if (notes.find(name) == notes.end()) {
                cout << "����� ������ ���." << endl;
            }
            else {
                cout << "������� ����� ������� ����� ��������:" << endl;
                getline(cin >> ws, text);
                notes[name].modifyFile(text);
            }
            break;
        case 'd':
        {
            cout << "�������� ������:" << endl;
            cout << "������� �������� ������, ������� ����� �������:" << endl;
            cin >> name;
            auto nameIt = notes.find(name);
            if (nameIt == notes.end()) {
                cout << "����� ������ ���." << endl;
            }
            else {
                remove(pathToFolder.concat("/" + name + ".txt"));
                pathToFolder.remove_filename();
                notes.erase(nameIt);
            }
            break;
        }
        case 't':
        {
            cout << "���������� ������� � �����:" << endl;
            cout << "������� ��� � ������� ����� ����� ������:" << endl;
            cin >> tag;
            cout << "���������� ��������� �������: " << countWithTag(tag, notes) << endl;
            break;
        }
        case 'a':
            cout << "���������� ������� � ������������ �������:" << endl;
            cout << "������� ������ ������ �������� ����� �����:" << endl;
            cin >> author;
            cout << "���������� ��������� �������: " << countWithAuthor(author, notes) << endl;
            break;
        case 'f':
            cout << "����� ������� � ������������ �����:" << endl;
            cout << "������� ��� ������ � ������� ����� �����:" << endl;
            cin >> tag;
            res = findNotesWithTag(notes, tag);
            if (res.empty()) {
                cout << "������ �� �������" << endl;
            }
            else {
                cout << "��������� ������: " << endl;
                for (Note note : res) {
                    cout << note.getName() << endl;
                }
                break;
        case 'g':
            cout << "����� ������� � ������������ �������:" << endl;
            cout << "������� ������ ������ �������� ����� �����:" << endl;
            cin >> author;
            res = findNotesWithAuthor(notes, author);
            if (res.empty()) {
                cout << "������ �� �������" << endl;
            }
            else
            {
                cout << "��������� ������: " << endl;
                for (Note note : res) {
                    cout << note.getName() << endl;
                }
            }
            break;

        case 'r':
            cout << "����� ������� ��������� �� ��������� N ����:" << endl;
            cout << "������� �� ����� ���������� �� ������ ����� ������:" << endl;
            cin >> days;
            res = filterNotesWithDate(notes,days);
            if (res.empty()) {
                cout << "������ �� �������" << endl;
            }
            else
            {
                cout << "��������� ������: " << endl;
                for (Note note : res) {
                    cout << note.getName() << endl;
                }
            }
            break;

        default:
            cout << "�� ����� ������������ �������, ���������� �����" << endl;
            break;
            }
        }
    }
}
