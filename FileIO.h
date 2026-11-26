#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Errors.h"
#include "Person.h"

std::string finalTitle(Method method);

void generateStudentFile(const std::string& fileName, int studentCount, int homeworkCount);

template <typename Container>
Container readStudentsFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file)
        throw FileError("cannot open file \"" + fileName + "\"");

    std::string line;
    std::getline(file, line);

    Container students;
    std::istringstream input;
    Person student;
    int skipped = 0;
    while (std::getline(file, line)) {
        if (line.find_first_not_of(" \t\r") == std::string::npos)
            continue;
        input.clear();
        input.str(line);
        if (input >> student)
            students.push_back(student);
        else
            ++skipped;
    }

    if (skipped > 0)
        std::cerr << "Skipped " << skipped << " line(s) that could not be read.\n";
    if (students.empty())
        throw DataError("file \"" + fileName + "\" contains no students");
    return students;
}

template <typename Container>
void writeStudentsToFile(const std::string& fileName, const Container& students, Method method) {
    std::ofstream file(fileName);
    if (!file)
        throw FileError("cannot create file \"" + fileName + "\"");

    file << std::left << std::setw(20) << "Name" << std::setw(20) << "Surname"
         << std::right << std::setw(18) << finalTitle(method) << "\n"
         << std::string(58, '-') << "\n";
    for (const Person& student : students)
        file << student << "\n";

    if (!file)
        throw FileError("could not write to file \"" + fileName + "\"");
}

#endif
