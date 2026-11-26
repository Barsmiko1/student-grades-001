#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>

#include "Person.h"

int readNumber(const std::string& question, int min, int max);

Method chooseMethod();

std::vector<Person> enterStudents();

std::vector<Person> generateStudents();

void printFinals(const std::vector<Person>& students, Method method);

void printBothFinals(const std::vector<Person>& students);

#endif
