#include <iostream>
#include "HotelSystem.h"

using namespace std;

int main() {
    // Khoi tao he thong
    // Khi chay dong nay, no se tu dong load file txt (neu co)
    // Hoac tao du lieu mau (neu chay lan dau)
    HotelSystem system; 
    
    int choice;

    while (true) {
        if (system.currentUserId == -1) {
            cout << "\n==========================================" << endl;
            cout << "   HE THONG QUAN LY KHACH SAN      " << endl;
            cout << "==========================================" << endl;
            cout << "1. Dang nhap (Admin/Khach)" << endl;
            cout << "2. Dang ky tai khoan khach moi" << endl;
            cout << "0. Thoat chuong trinh" << endl;
            cout << "Lua chon: ";
            
            // Fix loi nhap ky tu la bi lap vo tan
            if (!(cin >> choice)) {
                cin.clear(); 
                cin.ignore(1000, '\n'); 
                choice = -1;
            }

            switch (choice) {
                case 1:
                    if (system.login()) {
                        if (system.currentUserRole == "ADMIN") system.adminMenu();
                        else system.customerMenu();
                    }
                    break;
                case 2:
                    system.registerCustomer();
                    break;
                case 0:
                    cout << "Tam biet!";
                    return 0;
                default:
                    cout << "Lua chon khong hop le!\n";
            }
        } 
    }
    return 0;
}
