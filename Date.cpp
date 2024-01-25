#include "Date.h"
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS


using namespace std;
using namespace std::filesystem;

const std::string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

vector<std::string> split(const string& s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


void Date::setDate() {
    vector<string> dateLine = split(currentDateTime(), '.');
    vector<string> dateElements = split(dateLine[0], '-');
    vector<string> timeElements = split(dateLine[1], ':');
    year = stoi(dateElements[0]);
    month = stoi(dateElements[1]);
    day = stoi(dateElements[2]);
    hours = stoi(timeElements[0]);
    minutes = stoi(timeElements[1]);
}

void Date::setDate(string strDate) {
    vector<string> dateLine = split(strDate, ' ');
    vector<string> dateElements = split(dateLine[0], '.');
    vector<string> timeElements = split(dateLine[1], ':');
    year = stoi(dateElements[2]);
    month = stoi(dateElements[1]);
    day = stoi(dateElements[0]);
    hours = stoi(timeElements[0]);
    minutes = stoi(timeElements[1]);
}
template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

void EditDate::changeDate(string name) {
    path pathToFolder(L"C:/Users/User/source/repos/Curs/Curs");
    pathToFolder.concat("/" + name + ".txt");
    time_t time = to_time_t(last_write_time(pathToFolder));
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&time);
    strftime(buf, sizeof(buf), "%d.%m.%Y %X", &tstruct);
    this->setDate(buf);
}
