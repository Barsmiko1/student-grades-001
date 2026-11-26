#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

enum class Method { Average, Median };

class Person {
public:
    Person();
    Person(const std::string& name, const std::string& surname);

    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    Person(Person&& other) noexcept;
    Person& operator=(Person&& other) noexcept;

    void generateRandomScores(int homeworkCount);

    double finalGrade(Method method) const;
    void calculateFinal(Method method);

    const std::string& name() const { return name_; }
    const std::string& surname() const { return surname_; }
    double finalResult() const { return final_; }

    friend std::istream& operator>>(std::istream& in, Person& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

private:
    double average() const;
    double median() const;

    std::string name_;
    std::string surname_;
    std::vector<int> homework_;
    int exam_;
    double final_;
};

#endif
