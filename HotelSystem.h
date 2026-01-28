#ifndef HOTELSYSTEM_H
#define HOTELSYSTEM_H

#include "Models.h"
#include <vector>
#include <fstream> 

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

    
    void saveData();
    void loadData();
    void seedData(); 

public:
    int currentUserId;
    string currentUserRole;
    string currentUserName;

    HotelSystem();  
    ~HotelSystem();
    bool login();
    void registerCustomer();
    void logout();

    int processPayment(double amount);
    string getCustomerNameById(int id);

    void adminMenu();
    void customerMenu();
};

#endif
