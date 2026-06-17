#pragma once
#include<map>
#include "Core.h"
#include "Inventory.h"
#include <limits>
#include<vector>
#include<string>
using namespace std;
class Receiver : public Person {
private:
    string hospitalName;
    int unitsNeeded;
public:
    Receiver(string n, int a, string bg, string hosp, int u)
        : Person(n, a, bg), hospitalName(hosp), unitsNeeded(u) {}

    void displayDetails() const override {
        cout << "Patient: " << name << " Needs " << unitsNeeded << " units at " << hospitalName << endl;
    }
};
class CompatibilityChecker {
public:
    static vector<string> GetCompatType(string ReqGroup) {
        if (ReqGroup == "A+")
        return {"A+", "A-", "O+", "O-"};
        if (ReqGroup == "O+")
        return {"O+", "O-"};
        if (ReqGroup == "B+")
        return {"B+", "B-", "O+", "O-"};
        if (ReqGroup == "AB+")
        return {"AB+", "AB-", "A+", "A-", "B+", "B-", "O+", "O-"};
        if (ReqGroup == "A-")
        return {"A-", "O-"};
        if (ReqGroup == "O-")
        return {"O-"};
        if (ReqGroup == "B-")
        return {"B-", "O-"};
        if (ReqGroup == "AB-")
        return {"AB-", "A-", "B-", "O-"};
        return {ReqGroup};
    }
};
struct BloodRequest{
string name;
string BloodGroup;
int units_req;
};
class ReceiverManager {
private:
map<string, vector<BloodRequest>> waitingList;
public:
string waitListFile = "waitlist.txt";
    void fulfillRequest(InventoryManager& warehouse) {
        string name, bg, hosp;
        int units;
        cout << "\nEMERGENCY BLOOD REQUEST\n"<<endl;
        cout<<"Enter Patient Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter Blood Group Needed: "; cin >> bg;
        cout << "Enter Units Needed: "; cin >> units;
        cout << "Enter Hospital Admitted To: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, hosp);
        warehouse.removeExpiredBlood();
        cout << "\nSEARCHING INVENTORY FOR " << units << " UNITS OF " << bg <<endl;
        int totalFound = 0;
        vector<string> safeTypes = CompatibilityChecker::GetCompatType(bg);
        for (const string& type : safeTypes) {
            if (totalFound >= units) {
            break;
            }
            int remainingNeeded = units - totalFound;
            totalFound += warehouse.issueBlood(type, remainingNeeded);
        }
        if (totalFound == units) {
            cout << "\n[SUCCESS] All " << units << " units found and dispatched to " << hosp << ".\n";
        } else if (totalFound > 0 && totalFound < units) {
            cout << "\n[PARTIAL MATCH] Only found " << totalFound << " units in the system.\n";
        } else {
            cout << "\n[CRITICAL] No compatible blood available!\n";
        }
    }
void addToWaitList(){

}
};
