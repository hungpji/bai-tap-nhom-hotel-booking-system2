#include "HotelSystem.h"
#include <iostream>
#include <sstream> 
#include <cstdlib> // <--- QUAN TRONG: Thu vien de dung atoi/atof

using namespace std;

// --- PHAN 1: KHOI TAO & HUY ---

HotelSystem::HotelSystem() {
    currentUserId = -1;
    currentUserRole = "";
    currentUserName = "";
    
    // Thu load du lieu tu file
    loadData();

    // Neu load xong ma danh sach van rong (lan dau chay), thi tao du lieu mau
    if (admins.empty() && customers.empty()) {
        seedData();
    }

    // Tinh toan ID tiep theo dua tren du lieu hien co
    nextCustomerId = customers.empty() ? 1 : customers.back().customerId + 1;
    nextBookingId = bookings.empty() ? 1 : bookings.back().bookingId + 1;
    nextPaymentId = payments.empty() ? 1 : payments.back().paymentId + 1;
}

HotelSystem::~HotelSystem() {
    saveData();
}

void HotelSystem::seedData() {
    admins.push_back(Admin(1, "Quan Tri Vien", "admin", "123"));
    rooms.push_back(Room(101, "Phong 101", "Standard", 500000, "Available"));
    rooms.push_back(Room(102, "Phong 102", "Standard", 500000, "Available"));
    rooms.push_back(Room(201, "Phong VIP 1", "VIP", 1500000, "Available"));
    cout << ">> Da tao du lieu mau lan dau!\n";
}

// --- PHAN 2: DOC GHI FILE ---

void HotelSystem::saveData() {
    ofstream f1("admins.txt");
    for(const auto& a : admins) f1 << a.adminId << "|" << a.name << "|" << a.email << "|" << a.password << endl;
    
    ofstream f2("customers.txt");
    for(const auto& c : customers) f2 << c.customerId << "|" << c.name << "|" << c.email << "|" << c.password << "|" << c.phone << "|" << c.address << endl;
    
    ofstream f3("rooms.txt");
    for(const auto& r : rooms) f3 << r.roomId << "|" << r.roomName << "|" << r.roomType << "|" << r.price << "|" << r.status << endl;

    ofstream f4("bookings.txt");
    for(const auto& b : bookings) f4 << b.bookingId << "|" << b.roomId << "|" << b.customerId << "|" << b.paymentId << "|" << b.checkIn << "|" << b.checkOut << "|" << b.total << endl;

    ofstream f5("payments.txt");
    for(const auto& p : payments) f5 << p.paymentId << "|" << p.paymentMethod << "|" << p.amount << "|" << p.date << "|" << p.status << endl;
}

void HotelSystem::loadData() {
    // Luu y: O phien ban nay da chuyen stoi -> atoi(s.c_str()) de tranh loi Dev-C++
    
    ifstream f1("admins.txt");
    string line;
    while(getline(f1, line)) {
        stringstream ss(line); string s; vector<string> v;
        while(getline(ss, s, '|')) v.push_back(s);
        if(v.size() >= 4) admins.push_back(Admin(atoi(v[0].c_str()), v[1], v[2], v[3]));
    }
    
    ifstream f2("customers.txt");
    while(getline(f2, line)) {
        stringstream ss(line); string s; vector<string> v;
        while(getline(ss, s, '|')) v.push_back(s);
        if(v.size() >= 6) customers.push_back(Customer(atoi(v[0].c_str()), v[1], v[2], v[3], v[4], v[5]));
    }

    ifstream f3("rooms.txt");
    while(getline(f3, line)) {
        stringstream ss(line); string s; vector<string> v;
        while(getline(ss, s, '|')) v.push_back(s);
        if(v.size() >= 5) rooms.push_back(Room(atoi(v[0].c_str()), v[1], v[2], atof(v[3].c_str()), v[4]));
    }

    ifstream f4("bookings.txt");
    while(getline(f4, line)) {
        stringstream ss(line); string s; vector<string> v;
        while(getline(ss, s, '|')) v.push_back(s);
        if(v.size() >= 7) bookings.push_back(Booking(atoi(v[0].c_str()), atoi(v[1].c_str()), atoi(v[2].c_str()), atoi(v[3].c_str()), v[4], v[5], atof(v[6].c_str())));
    }
    
    ifstream f5("payments.txt");
    while(getline(f5, line)) {
        stringstream ss(line); string s; vector<string> v;
        while(getline(ss, s, '|')) v.push_back(s);
        if(v.size() >= 5) payments.push_back(Payment(atoi(v[0].c_str()), v[1], atof(v[2].c_str()), v[3], v[4]));
    }
}

// --- PHAN 3: LOGIC CHINH ---

bool HotelSystem::login() {
    string email, pass;
    cout << "\n--- DANG NHAP HE THONG ---" << endl;
    cout << "Email/User: "; cin >> email;
    cout << "Mat khau: "; cin >> pass;

    for (const auto& admin : admins) {
        if (admin.email == email && admin.password == pass) {
            currentUserId = admin.adminId;
            currentUserRole = "ADMIN";
            currentUserName = admin.name;
            cout << ">> Xin chao Admin: " << admin.name << "!\n";
            return true;
        }
    }

    for (const auto& cust : customers) {
        if (cust.email == email && cust.password == pass) {
            currentUserId = cust.customerId;
            currentUserRole = "CUSTOMER";
            currentUserName = cust.name;
            cout << ">> Xin chao Khach hang: " << cust.name << "!\n";
            return true;
        }
    }

    cout << "!!! Sai email hoac mat khau.\n";
    return false;
}

void HotelSystem::registerCustomer() {
    string name, email, pass, phone, addr;
    cout << "\n--- DANG KY TAI KHOAN ---" << endl;
    cin.ignore(); 
    cout << "Ho ten day du: "; getline(cin, name);
    cout << "Email (Ten dang nhap): "; cin >> email;
    
    for(const auto& c : customers) {
        if(c.email == email) {
            cout << "!!! Email nay da ton tai.\n";
            return;
        }
    }

    cout << "Mat khau: "; cin >> pass;
    cout << "SDT: "; cin >> phone;
    cin.ignore(); 
    cout << "Dia chi: "; getline(cin, addr);

    customers.push_back(Customer(nextCustomerId++, name, email, pass, phone, addr));
    saveData(); 
    cout << ">> Dang ky thanh cong! Hay dang nhap ngay.\n";
}

void HotelSystem::logout() {
    currentUserId = -1;
    currentUserRole = "";
    currentUserName = "";
    cout << ">> Da dang xuat.\n";
}

string HotelSystem::getCustomerNameById(int id) {
    for (const auto& c : customers) {
        if (c.customerId == id) return c.name;
    }
    return "Khach Vang Lai";
}

int HotelSystem::processPayment(double amount) {
    cout << "\n--- CONG THANH TOAN ---" << endl;
    cout << "Tong tien can tra: " << (long)amount << " VND" << endl;
    cout << "Chon phuong thuc:\n1. The Tin Dung\n2. Chuyen Khoan\n3. Tien Mat\n0. Huy bo\nChon: ";
    int c; cin >> c;
    
    if (c == 0) return -1;

    string method = (c==1) ? "Credit Card" : (c==2 ? "Banking" : "Cash");
    
    cout << ">> Dang xu ly...";
    int pId = nextPaymentId++;
    payments.push_back(Payment(pId, method, amount, "Hom nay", "Completed"));
    saveData(); 
    cout << " [THANH CONG]\n";
    
    return pId;
}

void HotelSystem::adminMenu() {
    while(currentUserId != -1 && currentUserRole == "ADMIN") {
        cout << "\n=== BANG DIEU KHIEN ADMIN (" << currentUserName << ") ===" << endl;
        cout << "1. Them phong moi" << endl;
        cout << "2. Xem bao cao doanh thu" << endl;
        cout << "3. Danh sach Booking" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon: ";
        int choice; 
        if(!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); choice = -1; }

        switch(choice) {
            case 1: {
                int id; string name, type; double price;
                cout << "ID Phong: "; cin >> id; cin.ignore();
                cout << "Ten Phong: "; getline(cin, name);
                cout << "Loai: "; getline(cin, type);
                cout << "Gia: "; cin >> price;
                rooms.push_back(Room(id, name, type, price, "Available"));
                saveData(); 
                cout << ">> Da them phong moi.\n";
                break;
            }
            case 2: {
                double total = 0;
                cout << "\n--- BAO CAO TAI CHINH ---" << endl;
                for(auto& p : payments) {
                    if(p.status == "Completed") total += p.amount;
                }
                cout << "Tong doanh thu thuc te: " << (long)total << " VND" << endl;
                break;
            }
            case 3:
                cout << "\n--- DANH SACH DON DAT PHONG ---" << endl;
                if(bookings.empty()) cout << "Chua co don nao.\n";
                else {
                    for(auto& b : bookings) {
                        string customerName = getCustomerNameById(b.customerId);
                        cout << "-----------------------------------" << endl;
                        cout << "KHACH HANG: " << customerName << " (ID: " << b.customerId << ")" << endl;
                        b.displayBooking();
                    }
                    cout << "-----------------------------------" << endl;
                }
                break;
            case 0: logout(); return;
            default: cout << "Sai lua chon!\n";
        }
    }
}

void HotelSystem::customerMenu() {
    while(currentUserId != -1 && currentUserRole == "CUSTOMER") {
        cout << "\n=== MENU KHACH HANG (" << currentUserName << ") ===" << endl;
        cout << "1. Xem tat ca phong" << endl;
        cout << "2. Dat phong" << endl;
        cout << "3. Lich su dat phong" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon: ";
        int choice; 
        if(!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); choice = -1; }

        switch(choice) {
            case 1:
                cout << "\n--- DANH SACH TRANG THAI PHONG ---" << endl;
                for(auto& r : rooms) r.displayRoom();
                break;
            case 2: {
                int rId; cout << "Nhap ID phong muon dat: "; cin >> rId;
                bool found = false;
                for(auto& r : rooms) {
                    if(r.roomId == rId) { 
                        if(r.status != "Available") {
                            cout << "!!! Phong nay da co nguoi dat/bao tri.\n";
                            found = true; break;
                        }
                        
                        string in, out;
                        cout << "Check-in: "; cin >> in;
                        cout << "Check-out: "; cin >> out;
                        
                        int pId = processPayment(r.price);
                        
                        if(pId != -1) {
                            bookings.push_back(Booking(nextBookingId++, rId, currentUserId, pId, in, out, r.price));
                            r.status = "Booked"; 
                            saveData(); 
                            cout << ">> DAT PHONG THANH CONG!\n";
                        } else {
                            cout << ">> Huy giao dich.\n";
                        }
                        
                        found = true; break;
                    }
                }
                if(!found) cout << "!!! Phong khong ton tai.\n";
                break;
            }
            case 3:
                cout << "\n--- LICH SU CUA BAN ---" << endl;
                for(auto& b : bookings) {
                    if(b.customerId == currentUserId) b.displayBooking();
                }
                break;
            case 0: logout(); return;
            default: cout << "Sai lua chon!\n";
        }
    }
}
