#include <iostream>
#include <string>
#include <ctime>
#include "sqlite3.h"


using namespace std;

void purchase(sqlite3 *db);
void addMember(sqlite3 *db);
void retrieveMemberData(sqlite3 *db);
void removeMember(sqlite3 *db);
//void executeTransaction(sqlite3 &db);
//void retrieveData(sqlite3 &db);

int main() {
    sqlite3 *db;

    int rc = sqlite3_open("sakila.db", &db);


    while (true) { 
        cout << "Menu:\n"
             << "1. Make a purchase\n"
             << "2. Add new member\n"
             << "3. Delete Record\n"
             << "4. Execute Transaction\n"
             << "5. Retrieve Data\n"
             << "6. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                purchase(db);
                break;
            case 2:
                addMember(db);
                break;
            //case 3:
            //    deleteRecord(db);
            //    break;
            case 4:
                retrieveMemberData(db);
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void purchase(sqlite3 *db) {
    sqlite3_stmt *stmt;
    cout << left; 
    cout << "-------MENU---------\n";
    cout << "1. Shampoo\n";
    cout << "2. Food\n";
    int choice;
    cin >> choice;
    
    int id = 1;
    string description;
    int quantity = 1;
    double price = 5.00;

    switch (choice) {
        case 1:
            description = "Shampoo";
            break;
        case 2:
            description = "Food";
            break;
    }
    

    const char* query = "INSERT INTO purchase(id, description, quantity, price) VALUES (?, ?, ?, ?);";

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, quantity);
    sqlite3_bind_double(stmt, 4, price);

    if (sqlite3_open("store.db", &db) == SQLITE_OK) {
        if (sqlite3_prepare(db, query, -1, &stmt, NULL) == SQLITE_OK) {

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "Data inserted successfully\n";
            } else {
                std::cout << "Failed to execute the statement: " << sqlite3_errmsg(db) << "\n";
            }

            sqlite3_finalize(stmt);
        } else {
            std::cout << "Failed to prepare the statement\n";
        }

        sqlite3_close(db);
    } else {
        std::cout << "Failed to open db\n";
    }
}

void addMember(sqlite3 *db) {
    sqlite3_stmt *stmt;
    string name;
    cout << "1. Enter your name: \n";
    cin >> name;
    string email;
    cout << "2. Enter your email: \n";
    cin >> email;
    
    int id = 1;

    string query = "INSERT INTO members(id, name, number, email, discounts, time, total) VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, number.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, discounts);
    sqlite3_bind_double(stmt, 4, price);

    time_t time;
    struct tm* timeInfo;
    time(&time);
    timeinfo = localtime(&time);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    sqlite3_bind_text(stmt, 5, timestamp, -1, SQLITE_STATIC);

    if (sqlite3_open("store.db", &db) == SQLITE_OK) {
        if (sqlite3_prepare(db, query, -1, &stmt, NULL) == SQLITE_OK) {

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                std::cout << "Data inserted successfully\n";
            } else {
                std::cout << "Failed to execute the statement: " << sqlite3_errmsg(db) << "\n";
            }

            sqlite3_finalize(stmt);
        } else {
            std::cout << "Failed to prepare the statement\n";
        }

        sqlite3_close(db);
    } else {
        std::cout << "Failed to open db\n";
    }
}

void retrieveMemberData(sqlite3 *db) {
    string query = "SELECT * FROM MEMBERS;";
    if (sqlite3_open("store.db", &db) == SQLITE_OK) {
        if (sqlite3_prepare(db, query, -1, &stmt, NULL) == SQLITE_OK) {
            int id;
            std::cout << "Enter the id of the customer you would like to see information about: ";
            std::cin >> id;

            sqlite3_bind_int(stmt, 1, id);

            int result = sqlite3_step(stmt);
            if (result == SQLITE_ROW) {
                int memberId = sqlite3_column_int(stmt, 0);
                int name = sqlite3_column_text(stmt, 1);
                int number = sqlite3_column_text(stmt, 2);
                int email = sqlite3_column_text(stmt, 3);
                int discounts = sqlite3_column_int(stmt, 4);
                int time = sqlite3_column_blob(stmt, 5);
                double total = sqlite3_column_real(stmt, 6);
                
                cout << left;
                cout << "Member id: " << memberId << '\n';
                cout << "Name: "      << name << '\n';
                cout << "Number: " << number << '\n';
                cout << "Email: " << email << '\n';
                cout << "Discounts: " << discounts << '\n';
                cout << "Time: " << time << '\n';
                cout << "Total: " << total << "\n\n";

            } else if (result == SQLITE_DONE) {
                std::cout << "No member found with the specified ID\n";
            } else {
                std::cout << "Failed to execute the statement: " << sqlite3_errmsg(db) << "\n";
            }

            sqlite3_finalize(stmt);         
        }

        sqlite3_close(db);
    } else {
        std::cout << "Failed to open db\n";
    }
}

void removeMember(sqlite3 *db) {
    int memberId = 0;
    
}

void viewMembers(sqlite *db) {
    string query = "SELECT * FROM Members;";

    sqlite3_stmt stmt;
    if (sqlite3_prepare(db, query, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int memberId = sqlite3_column_int(stmt, 0);
            int name = sqlite3_column_text(stmt, 1);
            int number = sqlite3_column_text(stmt, 2);
            int email = sqlite3_column_text(stmt, 3);

            cout << left;
            cout << "Member id: " << memberId << '\n';
            cout << "Name: "      << name << '\n';
            cout << "Number: " << number << '\n';
            cout << "Email: " << email << '\n';
        }
        sqlite3_finalize(stmt);
    } else {
        std::cout << "Failed to prepare the SELECT statment\n";
    }
}






























