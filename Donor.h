#pragma once
#include "Core.h"
#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
class Donor : public Person {
public:
    Donor(string n, int a, string bg) : Person(n,a,bg) {
        name = n;
        age = a;
        bloodGroup = bg;
    }
    string getName() const {
    return name;
}

int getAge() const {
    return age;
}

string getBloodGroup() const {
    return bloodGroup;
}
    void displayDetails() const override {
        cout << "\nDonor Details\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Blood Group: " << bloodGroup << endl;
    }
};
class DonorManager {
private:
    string donorsFile = "donors.txt";
    vector<Donor> donors;
public:
    void processDonation(InventoryManager& warehouse) {
        string name, bloodGroup, location;
        int age;
        char healthCheck;
        cout << "\n=== Blood Donation Form ===\n";
        cout << "Enter Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Blood Group (A+, O-, etc): ";
        cin >> bloodGroup;
        cout << "\nDo you have HIV, Hepatitis, cold or infection? (Y/N): ";
        cin >> healthCheck;
        if (healthCheck == 'Y' || healthCheck == 'y') {
            cout << "\n Sorry, you are not eligible to donate right now.\n";
            return;
        }
        cout << "Enter Donation Location: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, location);
        Donor donor(name, age, bloodGroup);
        donors.push_back(donor);
        /*
        ofstream file(donorsFile, ios::app);
        if (file.is_open()) {
            file << name << "|" << age << "|" << bloodGroup << endl;
            file.close();
        } else {
            cout << " Error saving donor data.\n";
        }
        cout << "\n Donor Registered Successfully!\n";
        */
        donor.displayDetails();
        string collectionDate = TimeUtils::getCurrentDate();
        string expiryDate = TimeUtils::getExpiryDate();
        warehouse.addBloodUnit(bloodGroup, location, collectionDate, expiryDate);
        cout << "\n Blood unit added to inventory!\n";
    }
    void SaveAllDonors(){
            ofstream file(donorsFile);
            if(file.is_open()){
                for(auto& donor : donors){
    file << donor.getName()
         << "|"
         << donor.getAge()
         << "|"
         << donor.getBloodGroup()
         << endl;
}
            }
            file.close();
        }
};