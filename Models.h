#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Payment {
public:
    int paymentId;
    string paymentMethod;
    double amount;
    string date;
    string status;

    Payment(int id, string method, double amt, string d, string st)
        : paymentId(id), paymentMethod(method), amount(amt), date(d), status(st) {}
    Payment() {}
};

class Room {
public:
    int roomId;
    string roomName;
    string roomType;
    double price;
    string status;

    Room(int id, string name, string type, double p, string st)
        : roomId(id), roomName(name), roomType(type), price(p), status(st) {}

    void displayRoom() {
        cout << "| ID: " << roomId << " | " << left << setw(15) << roomName 
             << " | " << setw(10) << roomType 
             << " | Gia: " << (long)price << " VND | Trang thai: " << status << endl;
    }
};

class Booking {
public:
    int bookingId;
    int roomId;
    int customerId;
    int paymentId;
    string checkIn;
    string checkOut;
    double total;
    string status;

    Booking(int id, int rId, int cId, int pId, string in, string out, double t)
        : bookingId(id), roomId(rId), customerId(cId), paymentId(pId), checkIn(in), checkOut(out), total(t), status("Confirmed") {}
    
    void displayBooking() {
        cout << "   -> Ma Book: " << bookingId << " | Phong ID: " << roomId 
             << " | Ngay: " << checkIn << " den " << checkOut 
             << " | Tong: " << (long)total << endl;
    }
};

class Customer {
public:
    int customerId;
    string name;
    string email;
    string password;
    string phone;
    string address;

    Customer(int id, string n, string e, string pass, string p, string addr)
        : customerId(id), name(n), email(e), password(pass), phone(p), address(addr) {}
};

class Admin {
public:
    int adminId;
    string name;
    string email;
    string password;

    Admin(int id, string n, string e, string pass) 
        : adminId(id), name(n), email(e), password(pass) {}
};

#endif
