#ifndef STUDENTS_H
#define STUDENTS_H

#include <algorithm>
#include <list>
#include <vector>

#include "Person.h"

const double PASS_MARK = 5.0;

bool byName(const Person& a, const Person& b);

bool byFinal(const Person& a, const Person& b);

void sortByName(std::vector<Person>& students);

template <typename Container>
void sortByFinal(Container& students) {
    std::sort(students.begin(), students.end(), byFinal);
}

inline void sortByFinal(std::list<Person>& students) {
    students.sort(byFinal);
}

template <typename Container>
void splitStudents(const Container& students, Container& passed, Container& failed) {
    for (const Person& student : students) {
        if (student.finalResult() < PASS_MARK)
            failed.push_back(student);
        else
            passed.push_back(student);
    }
}

#endif
