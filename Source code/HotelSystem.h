#ifndef HOTELSYSTEM_H
#define HOTELSYSTEM_H

#include "Models.h"
#include <vector>
#include <fstream> // Thu vien doc ghi file

class HotelSystem {
private:
    vector<Room> rooms;
    vector<Customer> customers;
    vector<Booking> bookings;
    vector<Admin> admins;
    vector<Payment> payments;
    
    int nextCustomerId;
    int nextBookingId;
    int nextPaymentId;

    // Ham ho tro Save/Load
    void saveData();
    void loadData();
    void seedData(); // Tao du lieu mau neu file rong

public:
    int currentUserId;
    string currentUserRole;
    string currentUserName;

    HotelSystem();  // Constructor (se goi loadData)
    ~HotelSystem(); // Destructor (se goi saveData)

    bool login();
    void registerCustomer();
    void logout();

    int processPayment(double amount);
    string getCustomerNameById(int id);

    void adminMenu();
    void customerMenu();
};

#endif
