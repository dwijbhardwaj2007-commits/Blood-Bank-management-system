#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include"Core.h"
using namespace std;
struct BloodUnit {
    int    unitId;
    string bloodGroup;
    string location;
    string collectionDate;
    string expiryDate;
};
class InventoryManager {
private:
    string filename = "inventory.txt";
    int    nextId   = 1;
    vector<BloodUnit> units;
public:
    InventoryManager()
    {
        units = loadAll();
    }
    vector<BloodUnit> loadAll() {
        vector<BloodUnit> tempunits;
        ifstream file(filename);
        if (!file.is_open()) return tempunits;
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;
            BloodUnit u;
            try {
                getline(ss, token, '|'); u.unitId         = stoi(token);
                getline(ss, token, '|'); u.bloodGroup     = token;
                getline(ss, token, '|'); u.location       = token;
                getline(ss, token, '|'); u.collectionDate = token;
                getline(ss, token, '|'); u.expiryDate     = token;
                tempunits.push_back(u);
            } catch (...) {
            }
        }
        file.close();
        return tempunits;
    }
    void saveAll(const vector<BloodUnit>& units) {
        ofstream file(filename);
        for (auto& u : units) {
            file << u.unitId       << "|"
                 << u.bloodGroup   << "|"
                 << u.location     << "|"
                 << u.collectionDate << "|"
                 << u.expiryDate   << "\n";
        }
        file.close();
    }
    int getNextId() {
        int maxId = 0;
        for (auto& u : units)
            if (u.unitId > maxId) maxId = u.unitId;
        return maxId + 1;
    }
public:
    void addBloodUnit(const string& bloodGroup,
                      const string& location,
                      const string& collectionDate,
                      const string& expiryDate) {
        BloodUnit newUnit;
        newUnit.unitId         = getNextId();
        newUnit.bloodGroup     = bloodGroup;
        newUnit.location       = location;
        newUnit.collectionDate = collectionDate;
        newUnit.expiryDate     = expiryDate;
        units.push_back(newUnit);
        saveAll(units);
        cout << "  Unit ID  : " << newUnit.unitId       << "\n";
        cout << "  Group    : " << bloodGroup            << "\n";
        cout << "  Location : " << location              << "\n";
        cout << "  Collected: " << collectionDate        << "\n";
        cout << "  Expires  : " << expiryDate            << "\n";
    }
    void removeExpiredBlood() {
        string today = TimeUtils::getCurrentDate();
        int before = units.size();
        vector<BloodUnit> valid;
        units = valid;
        for (auto& u : units) {
            if (u.expiryDate >= today)
                valid.push_back(u);
            else
                cout << "  [REMOVED] Unit " << u.unitId
                     << " (" << u.bloodGroup << ") expired on "
                     << u.expiryDate << "\n";
        }
        saveAll(valid);
        int removed = before - valid.size();
        if (removed > 0)
            cout << "[CLEANUP] Removed " << removed
                 << " expired unit(s) from inventory.\n";
        else
            cout << "[CLEANUP] No expired blood found."
                 << " Inventory is clean.\n";
    }
    int issueBlood(const string& bloodGroup, int unitsNeeded) {
        sort(units.begin(), units.end(),
             [](const BloodUnit& a, const BloodUnit& b) {
                 return a.collectionDate < b.collectionDate;
             });

        vector<int> issuedIds;
        int unitsFound = 0;

        cout << "\n[ISSUING BLOOD - " << bloodGroup << "]\n";
        cout << "  " << string(65, '-') << "\n";
        printf("  %-6s %-6s %-28s %-10s %-10s\n",
               "ID", "Group", "Location", "Collected", "Expires");
        cout << "  " << string(65, '-') << "\n";

        for (auto& u : units) {
            if (unitsFound >= unitsNeeded) break;
            if (u.bloodGroup == bloodGroup) {
                printf("  %-6d %-6s %-28s %-10s %-10s\n",
                       u.unitId,
                       u.bloodGroup.c_str(),
                       u.location.c_str(),
                       u.collectionDate.c_str(),
                       u.expiryDate.c_str());
                issuedIds.push_back(u.unitId);
                unitsFound++;
            }
        }

        if (unitsFound == 0) {
            cout << "  [!] No " << bloodGroup
                 << " blood available in inventory.\n";
            return 0;
        }
        if (unitsFound < unitsNeeded) {
            cout << "  [WARNING] Only " << unitsFound
                 << " unit(s) available (needed "
                 << unitsNeeded << ").\n";
        }

        vector<BloodUnit> remaining;
        units = remaining; 
        for (auto& u : units) {
            bool issued = false;
            for (int id : issuedIds)
                if (u.unitId == id) { issued = true; break; }
            if (!issued) remaining.push_back(u);
        }
        saveAll(remaining);

        cout << "  [SUCCESS] " << unitsFound
             << " unit(s) issued and removed from inventory.\n";

        return unitsFound;
    }
    void displayInventory() {
        string today = TimeUtils::getCurrentDate();

        cout << "\n╔══════════════════════════════════════════════════════╗\n";
        cout << "║             CURRENT BLOOD INVENTORY                  ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n";
        printf("  %-6s %-6s %-28s %-10s %-10s\n",
               "ID", "Group", "Location", "Collected", "Expires");
        cout << "  " << string(65, '-') << "\n";

        if (units.empty()) {
            cout << "  (Inventory is empty)\n";
        } else {
            for (auto& u : units) {
                string warning = (u.expiryDate < today) ? " [EXPIRED]" : "";
                printf("  %-6d %-6s %-28s %-10s %-10s%s\n",
                       u.unitId,
                       u.bloodGroup.c_str(),
                       u.location.c_str(),
                       u.collectionDate.c_str(),
                       u.expiryDate.c_str(),
                       warning.c_str());
            }
            cout << "  " << string(65, '-') << "\n";
            cout << "  Total units: " << units.size() << "\n";
        }
        cout << "\n";
    }
};