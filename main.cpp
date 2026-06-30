#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Core.h"
#include "Inventory.h"
#include "Donor.h"
#include "Receiver.h"
using namespace std;
int main() {
    srand(time(0)); 
    InventoryManager warehouse; 
    DonorManager donorSystem;
    ReceiverManager receiverSystem;
    int choice;
    while (true) {
        cout << "\n=============WELCOME TO============="<<endl;;
        cout << "\n----BLOOD BANK MANAGEMENT SYSTEM----"<<endl;
        cout << "\n========MADE BY Dwij Bhardwaj============"<<endl;
        cout << "\n1. Donate Blood (Enter 1)";
        cout << "\n2. Request Blood (Enter 2)";
        cout << "\n3. View Blood Inventory(Enter 3)";
        cout << "\n4. Save donors and Exit(Enter 4)";
        cout << "\n> Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            donorSystem.processDonation(warehouse);
        } else if (choice == 2) {
            receiverSystem.fulfillRequest(warehouse);
        } else if (choice == 3) {
            warehouse.displayInventory();
        } 
        else if(choice == 4){
    donorSystem.SaveAllDonors();
    break;
}
         else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
