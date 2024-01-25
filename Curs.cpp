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
    cout << "Записная книжка с тэгами:" << endl;

    while (mode != 'e') {
        cout << "Выберите функцию:" << endl;
        cout << "    c - Создать запись" << endl;
        cout << "    l - Загрузить запись" << endl;
        cout << "    m - Модифицировать запись" << endl;
        cout << "    d - Удалить запись" << endl;
        cout << "    t - Количество записей с определенным тэгом" << endl;
        cout << "    a - Количество записей с определенным автором" << endl;
        cout << "    f - Найти записи с определенным тэгом" << endl;
        cout << "    g - Найти записи с определенным автором" << endl;
        cout << "    r - Найти записи созданные за последние N дней" << endl;

        cin >> mode;
        switch (mode)
        {
        case 'c':
            cout << "Создание записи:" << endl;
            cout << "Введите название записи" << endl;
            getline(cin >> ws, name);
            while (exists(pathToFolder.concat("/" + name + ".txt"))) {
                cout << "Запись с данным названием уже существует. Попробуйте ввести другое название" << endl;
                pathToFolder.remove_filename();
                getline(cin >> ws, name);
            }
            cout << "Введите автора" << endl;
            getline(cin >> ws, author);
            cout << "Введите тэги. Для завершения ввода, введите / " << endl;
            tags.clear();
            while (tag != "/") {
                cin >> tag;
                if (tag != "/") {
                    tags.push_back(tag);
                }
            }
            cout << "Введите текст записи" << endl;
            getline(cin >> ws, text);
            notes[name] = Note(name, author, text, tags);
            break;
        case 'l':
            cout << "Загрузка записи:" << endl;
            cout << "Введите название записи, которую нужно открыть:" << endl;
            cin >> name;
            if (notes.find(name) == notes.end()) {
                cout << "Такой записи нет." << endl;
            }
            else {
                cout << "Данная запись:" << endl;
                notes[name].showFile();
            }
            break;
        case 'm':
            cout << "Модификация записи:" << endl;
            cout << "Введите название записи, которую нужно модифицировать:" << endl;
            cin >> name;
            if (notes.find(name) == notes.end()) {
                cout << "Такой записи нет." << endl;
            }
            else {
                cout << "Введите текст который нужно добавить:" << endl;
                getline(cin >> ws, text);
                notes[name].modifyFile(text);
            }
            break;
        case 'd':
        {
            cout << "Удаление записи:" << endl;
            cout << "Введите название записи, которую нужно удалить:" << endl;
            cin >> name;
            auto nameIt = notes.find(name);
            if (nameIt == notes.end()) {
                cout << "Такой записи нет." << endl;
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
            cout << "Количество записей с тэгом:" << endl;
            cout << "Введите тэг с которым нужно найти записи:" << endl;
            cin >> tag;
            cout << "Количество найденных записей: " << countWithTag(tag, notes) << endl;
            break;
        }
        case 'a':
            cout << "Количество записей с определенным автором:" << endl;
            cout << "Введите автора записи которого нужно найти:" << endl;
            cin >> author;
            cout << "Количество найденных записей: " << countWithAuthor(author, notes) << endl;
            break;
        case 'f':
            cout << "Поиск записей с определенным тэгом:" << endl;
            cout << "Введите тэг записи с которым нужно найти:" << endl;
            cin >> tag;
            res = findNotesWithTag(notes, tag);
            if (res.empty()) {
                cout << "Записи не найдены" << endl;
            }
            else {
                cout << "Найденные записи: " << endl;
                for (Note note : res) {
                    cout << note.getName() << endl;
                }
                break;
        case 'g':
            cout << "Поиск записей с определенным автором:" << endl;
            cout << "Введите автора записи которого нужно найти:" << endl;
            cin >> author;
            res = findNotesWithAuthor(notes, author);
            if (res.empty()) {
                cout << "Записи не найдены" << endl;
            }
            else
            {
                cout << "Найденные записи: " << endl;
                for (Note note : res) {
                    cout << note.getName() << endl;
                }
            }
            break;

        case 'r':
            cout << "Поиск записей созаднных за последние N дней:" << endl;
            cout << "Введите за какой промежуток вы хотите найти записи:" << endl;
            cin >> days;
            res = filterNotesWithDate(notes,days);
            if (res.empty()) {
                cout << "Записи не найдены" << endl;
            }
            else
            {
                cout << "Найденные записи: " << endl;
                for (Note note : res) {
                    cout << note.getName() << endl;
                }
            }
            break;

        default:
            cout << "Вы ввели неправильную команду, попробуйте снова" << endl;
            break;
            }
        }
    }
}
