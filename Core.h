#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;
class TimeUtils {
public:
    static string getCurrentDate() {
        time_t now = time(0); tm *ltm = localtime(&now);
        char buf[11]; snprintf(buf, sizeof(buf), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
        return string(buf);

    }
    static string getExpiryDate() {
        time_t now = time(0); now += (42 * 24 * 60 * 60); tm *ltm = localtime(&now);
        char buf[11]; snprintf(buf, sizeof(buf), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
        return string(buf);
    }
};
class Person { 
protected:
    string name;
    int age;
    string bloodGroup;
public:
    Person(string n, int a, string bg) : name(n), age(a), bloodGroup(bg) {}
    string getName() const {
    return name;
}
int getAge() const {
    return age;
}
string getBloodGroup() const {
    return bloodGroup;
}
    virtual void displayDetails() const = 0; 
     virtual ~Person() {}
};

 