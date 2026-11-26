#ifndef SPEEDTEST_H
#define SPEEDTEST_H

#include <string>
#include <vector>

#include "FileIO.h"
#include "Person.h"
#include "Students.h"
#include "Timer.h"

const std::vector<int> TEST_SIZES = {1000, 10000, 100000, 1000000, 10000000};

const std::vector<std::string> CONTAINERS = {"vector", "list", "deque"};

std::string testFileName(int studentCount);

void generateTestFiles(int homeworkCount);

std::string outputName(const std::string& fileName, const std::string& suffix);

struct Timings {
    std::size_t students = 0;
    std::size_t passed = 0;
    std::size_t failed = 0;
    double read = 0;
    double sort = 0;
    double split = 0;
    double writePassed = 0;
    double writeFailed = 0;
    double total = 0;
};

template <typename Container>
Timings splitFile(const std::string& fileName, Method method) {
    Timings times;
    Timer total;
    Timer step;

    Container students = readStudentsFromFile<Container>(fileName);
    for (Person& student : students)
        student.calculateFinal(method);
    times.read = step.elapsed();
    times.students = students.size();

    step.reset();
    sortByFinal(students);
    times.sort = step.elapsed();

    step.reset();
    Container passed, failed;
    splitStudents(students, passed, failed);
    times.split = step.elapsed();
    times.passed = passed.size();
    times.failed = failed.size();

    Container().swap(students);

    step.reset();
    writeStudentsToFile(outputName(fileName, "_passed"), passed, method);
    times.writePassed = step.elapsed();

    step.reset();
    writeStudentsToFile(outputName(fileName, "_failed"), failed, method);
    times.writeFailed = step.elapsed();

    times.total = total.elapsed();
    return times;
}

void runSpeedTest(const std::vector<std::string>& fileNames, Method method,
                  const std::vector<std::string>& containers);

#endif
