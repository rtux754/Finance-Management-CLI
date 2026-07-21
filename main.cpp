#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
//  JIKA DI WINDOWS AKTIFKAN LIBRARY ANSI CODE
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ======= Struktur Data =======
struct Transaction {
    int id;           // id untuk setiap transaksi
    string date;      // Tanggal transaksi
    string type;      // Tipe transaksi "pemasukan" atau "pengeluaran"
    double amount;    // nominal uang. double agar bisa desimal
    string category;  // kategori misalnya : "Makanan", "Gaji"
    string note;      // catatan atau deskripsi singkat
};

vector<Transaction> transactions;

// ======== FUNGSI UI =======
void clearScreen();
void setupTerminal();
void organizer();
void customer();

// ======= Warna =======
void setHexColor(string hexCode);
void primaryColor();
void secondaryColor();
void warningColor();
void errorColor();
void successColor();
void resetColor();

// ======= FUNGSI I/O =======
void addIncome();
void addExpense();
void viewAllTransactions();
void checkBalance();

// ======= OPERASI SPESIFIK =======
void deleteTransactionById(int targetId);
void updateTransactionById(int targetId); // digunakan untuk mengedit salah nomial atau mengubah nominal transaksi yang sudah lewat
void exportToReceipt(int targetId);
void filterByCategory(string catName);
void clearAllHistory();

// ======= SISTEM FILE =======
void load();
void save();

// ======= FUNGSI PEMBERSIH LAYAR AGAR BERSIH =======
void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
    system("clear");
#endif
}

void setupTerminal() {

}

int main() {
    clearScreen();

    load();

    cout << "                                           ****************************************************" << endl;
    cout << "                                                                                               " << endl;
    cout << "                                                     WELCOME TO FINANCE MANAGEMENT CLI         " << endl;
    cout << "                                                                                               " << endl;
    cout << "                                           ****************************************************" << endl;
    cout << "                                                Catat | Atur | Pantau | Amankan Keuanganmu     " << endl;
    cout << "                                           ****************************************************" << endl;

    while (true) {
        cout << "\n                                                          Menu Main:" << endl;
        cout << "                                                          1. Organizer Menu (Auditor)" << endl;
        cout << "                                                          2. Customer Menu (Pencatat)" << endl;
        cout << "                                                          3. Close & Save System" << endl;
        cout << "                                                          Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "                                                          Masukkan angka yang valid!\n";
            continue;
        }

        switch (choice) {
        case 1:
            clearScreen();
            organizer();
            break;
        case 2:
            clearScreen();
            customer();
            break;
        case 3:
            clearScreen();
            save();
            cout << "                                      **********************************************************\n";
            cout << "                                        Terima kasih telah menggunakan FINANCE MANAGEMENT CLI!\n";
            cout << "                                      **********************************************************\n";
            return 0;
        default:
            cout << "                                                          Pilihan Tidak Valid. Mohon Coba Kembali.\n";
        }
    }
    return 0;
}

// MODE EDIT UNTUK MENGUBAH ISI TRANSAKSI
void organizer() {
    int choice;
    do {
        cout << "                                                         ============================================\n";
        cout << "                                                                           ORGANIZER MENU            \n";
        cout << "                                                         ============================================\n";
        cout << "                                                         1. View All Transactions" << endl;
        cout << "                                                         2. Delete Transaction By Id" << endl;
        cout << "                                                         3. Clear All History" << endl;
        cout << "                                                         4. Back to Main Menu" << endl;
        cout << "                                                         Enter your choice ";

        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "                                                         Masukkan input angka!\n";
            continue;
        }

        switch (choice) {
        case 1:
            clearScreen();
            viewAllTransactions();
            break;
        case 2:
            int targetId;
            cout << "                                                         Enter Target ID to Delete: ";
            cin >> targetId;
            clearScreen();
            deleteTransactionById(targetId);
            break;
        case 3:
            clearScreen();
            clearAllHistory();
            break;
        case 4:
            clearScreen();
            return;
        default:
            cout << "                                                         Pilihan tidak valid, coba lagi.\n";
        }
    }while (choice != 4);
}

// TAMPILAN MENU UNTUK PENGGUNA
void customer() {
    int choice;
     do {
         cout << "                                                    ============================================\n";
         cout << "                                                                    CUSTOMER MENU                \n";
         cout << "                                                    ============================================\n";
         cout << "                                                    1. Add Income" << endl;
         cout << "                                                    2. Add Expense" << endl;
         cout << "                                                    3. Check Balance" << endl;
         cout << "                                                    4. Update Transaction" << endl;
         cout << "                                                    5. Export To Receipt" << endl;
         cout << "                                                    6. Filter By Category" << endl;
         cout << "                                                    7. Back to Main menu" << endl;
         cout << "                                                    Enter your choice: ";

         if(!(cin >> choice)) {
             cin.clear();
             cin.ignore(1000, '\n');
             cout << "                                                    Masukkan input angka!\n";
             continue;
         }

        switch (choice) {
        case 1:
            clearScreen();
            addIncome();
            break;
        case 2:
            clearScreen();
            addExpense();
            break;
        case 3:
            clearScreen();
            checkBalance();
            break;
        case 4: {
            int targetId;
            cout << "                                                     Masukkan ID Transaksi yang ingin di update: ";
            cin >> targetId;
            clearScreen();
            updateTransactionById(targetId);
            break;
        }
        case 5: {
            int targetId;
            cout << "                                                     Masukkan ID Transaksi untuk Cetak Struk: ";
            cin >> targetId;
            clearScreen();
            exportToReceipt(targetId);
            break;
        }
        case 6: {
            string catName;
            cout << "                                                     Masukkan Nama Kategori yang ingin dicari: ";
            cin.ignore();
            getline(cin, catName);
            clearScreen();
            filterByCategory(catName);
            break;
        }
        case 7:
            clearScreen();
            return;
        default:
            cout << "                                                     Pilihan Tidak Valid!\n";
        }
     } while (choice != 7);
}

// FUNGSI UNTUK MENAMBAHKAN PEMASUKAN
//
void addIncome() {
    Transaction newTx;
    cout << "                                                     ============================================\n";
    cout << "                                                                   TAMBAH PEMASUKAN              \n";
    cout << "                                                     ============================================\n";

    newTx.id = transactions.empty() ? 1 : transactions.back().id + 1;
    newTx.type = "Pemasukan";

    cin.ignore();
    cout << "                                                     Masukkan Tanggal (DD-MM-YYYY): ";
    getline(cin, newTx.date);
    cout << "                                                     Masukkan Nominal (Rp)        : ";
    cin >> newTx.amount;
    cin.ignore();
    cout << "                                                     Masukkan Kategori (cth: Gaji): ";
    getline(cin, newTx.category);
    cout << "                                                     Catatan / Deskripsi Singkat  : ";
    getline(cin, newTx.note);

    transactions.push_back(newTx);
    cout << "\n                                                     [SUKSES] Pemasukan berhasil dicatat!\n";
    cout << "                                                     ============================================\n";
}

// FUNGSI UNTUK MENAMBAHKAN PENGELUARAN
//
void addExpense() {
    Transaction newTx;

    cout << "                                                     ============================================\n";
    cout << "                                                                  TAMBAH PENGELUARAN             \n";
    cout << "                                                     ============================================\n";

    newTx.id = transactions.size() + 1;
    newTx.type = "Pengeluaran";

    cin.ignore();
    cout << "                                                     Masukkan Tanggal (DD-MM-YYYY): ";
    getline(cin, newTx.date);
    cout << "                                                     Masukkan Nominal (Rp)        : ";
    cin >> newTx.amount;
    cin.ignore();
    cout << "                                                     Masukkan Kategori (cth: Makan): ";
    getline(cin, newTx.category);
    cout << "                                                     Catatan / Deskripsi Singkat   : ";
    getline(cin, newTx.note);

    transactions.push_back(newTx);
    cout << "\n                                                     [SUKSES] Pengeluaran berhasil dicatat!\n";
    cout << "                                                     ============================================\n";
}

void viewAllTransactions() {
    cout << "========================================================================================================\n";
    cout << "                                           DAFTAR SEMUA TRANSAKSI                                       \n";
    cout << "========================================================================================================\n";
    cout << " " << setw(5) << left << "ID"
         << " | " << setw(12) << left << "Tanggal"
         << " | " << setw(13) << left << "Tipe"
         << " | " << setw(18) << left << "Nominal (Rp)"
         << " | " << setw(15) << left << "Kategori"
         << " | " << left << "Catatan" << endl;
    cout << "--------------------------------------------------------------------------------------------------------\n";

    if (transactions.empty()) {
        cout << "                                    --- Belum ada data transaksi ---                                    \n";
    } else {
        for (const Transaction& tx : transactions) {
            cout << " " << setw(5) << left << tx.id
                 << " | " << setw(12) << left << tx.date
                 << " | " << setw(13) << left << tx.type
                 << " | " << setw(18) << left << fixed << setprecision(0) << tx.amount
                 << " | " << setw(15) << left << tx.category
                 << " | " << left << tx.note << endl;
        }
    }
    cout << "========================================================================================================\n\n";
}

void checkBalance() {
    double totalIncome = 0;
    double totalExpense = 0;

    for (const Transaction& tx: transactions) {
        if (tx.type == "Pemasukan") {
            totalIncome += tx.amount;
        } else if (tx.type == "Pengeluaran") {
            totalExpense += tx.amount;
        }
    }
    double currentBalance = totalIncome - totalExpense;

    cout << "                                                     ============================================\n";
    cout << "                                                                 RINGKASAN REKENING ANDA         \n";
    cout << "                                                     ============================================\n";
    cout << "                                                      Total Pemasukan   : Rp " << fixed << setprecision(0) << totalIncome << endl;
    cout << "                                                      Total Pengeluaran : Rp " << totalExpense << endl;
    cout << "                                                     --------------------------------------------\n";
    cout << "                                                      SALDO SAAT INI    : Rp " << currentBalance << endl;
    cout << "                                                     ============================================\n\n";
}

void updateTransactionById(int targetId) {
    auto it = find_if(transactions.begin(), transactions.end(), [targetId](const Transaction& item) {
        return item.id == targetId;
    });

    if (it != transactions.end()) {
        cout << "                                                     ============================================\n";
        cout << "                                                                 EDIT DATA TRANSAKSI             \n";
        cout << "                                                     ============================================\n";
        cout << "                                                      Data Lama Anda: \n";
        cout << "                                                      Tanggal  : " << it->date << endl;
        cout << "                                                      Nominal  : Rp " << fixed << setprecision(0) << it->amount << endl;
        cout << "                                                      Kategori : " << it->category << endl;
        cout << "                                                      Catatan  : " << it->note << endl;
        cout << "                                                     --------------------------------------------\n";

        cout << "                                                      Masukkan Data Pembaruan:\n";
        cin.ignore();
        cout << "                                                      Tanggal Baru (DD-MM-YYYY): ";
        getline(cin, it->date);
        cout << "                                                      Nominal Baru (Rp)        : ";
        cin >> it->amount;
        cin.ignore();
        cout << "                                                      Kategori Baru            : ";
        getline(cin, it->category);
        cout << "                                                      Catatan Baru             : ";
        getline(cin, it->note);

        cout << "                                                     ============================================\n";
        cout << "                                                     [SUKSES] Data Transaksi Berhasil Di-update! \n";
        cout << "                                                     ============================================\n";
    } else {
        cout << "                                                     [ERROR] ID " << targetId << " tidak ditemukan di database.\n";
    }
}

void deleteTransactionById(int targetId) {
    auto it = find_if(transactions.begin(), transactions.end(), [targetId](const Transaction& item) {
        return item.id == targetId;
    });
    if (it != transactions.end()) {
        cout << "                                                     ============================================\n";
        cout << "                                                     [SUKSES] ID " << targetId << " (" << it->note << ") Ditemukan.\n";
        cout << "                                                     Catatan Transaksi Resmi Dihapus dari Sistem.\n";
        cout << "                                                     ============================================\n";
        transactions.erase(it);
    } else {
        cout << "                                                     [ERROR] Transaksi dengan ID "<< targetId << " Tidak Ditemukan.\n";
    }
}

void exportToReceipt(int targetId) {
    auto it = find_if(transactions.begin(), transactions.end(), [targetId](const Transaction& item) {
        return item.id == targetId;
    });

    if (it != transactions.end()) {
        cout << "                                                     ============================================\n";
        cout << "                                                                   OFFICIAL RECEIPT              \n";
        cout << "                                                     ============================================\n";
        cout << "                                                      ID Transaksi : " << it->id << endl;
        cout << "                                                      Tanggal      : " << it->date << endl;
        cout << "                                                      Jenis Kas    : " << it->type << endl;
        cout << "                                                      Kategori     : " << it->category << endl;
        cout << "                                                      Keterangan   : " << it->note << endl;
        cout << "                                                     --------------------------------------------\n";
        cout << "                                                      TOTAL DANA   : Rp " << fixed << setprecision(0) << it->amount << endl;
        cout << "                                                     ============================================\n\n";
    } else {
        cout << "                                                     [ERROR] ID Transaksi " << targetId << " tidak valid.\n";
    }
}

void filterByCategory(string catName) {
    bool ditemukan = false;
    cout << "========================================================================================================\n";
    cout << "                                      HASIL FILTER KATEGORI: " << catName << "                           \n";
    cout << "========================================================================================================\n";
    cout << " " << setw(5) << left << "ID"
         << " | " << setw(12) << left << "Tanggal"
         << " | " << setw(13) << left << "Tipe"
         << " | " << setw(18) << left << "Nominal (Rp)"
         << " | " << left << "Catatan" << endl;
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (const auto& tx : transactions) {
        if (tx.category == catName) {
            cout << " " << setw(5) << left << tx.id
                 << " | " << setw(12) << left << tx.date
                 << " | " << setw(13) << left << tx.type
                 << " | " << setw(18) << left << fixed << setprecision(0) << tx.amount
                 << " | " << left << tx.note << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "                               --- Tidak ada transaksi di kategori ini ---                              \n";
    }
    cout << "========================================================================================================\n\n";
}

void clearAllHistory() {
    char confirm;
    cout << "                                                     Apakah anda yakin ingin menghapus seluruh data? (y/n): ";
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        transactions.clear();
        cout << "                                                     [SUKSES] Seluruh riwayat transaksi dikosongkan!\n";
    } else {
        cout << "                                                     [INFO] Pembatalan penghapusan riwayat.\n";
    }
}

void save() {
    ofstream bookAccount("database.csv");
    if (bookAccount.is_open()) {
        for (const Transaction& tx: transactions) {
            bookAccount << tx.id << ","
                        << tx.date << ","
                        << tx.type << ","
                        << fixed << setprecision(0) << tx.amount << ","
                        << tx.category << ","
                        << tx.note << "\n";
        }
        bookAccount.close();
        cout << "                                          [SYSTEM] Database sinkron. Data berhasil disimpan.\n";
    } else {
        cout << "                                          [ERROR] Gagal menulis ke berkas backup!\n";
    }
}

void load() {
    ifstream bookAccount("database.csv");
    if (!bookAccount.is_open()) {
        return;
    }

    string line;
    while (getline(bookAccount, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Transaction tx;
        string tempId, tempAmount;

        getline(ss ,tempId, ',');
        getline(ss, tx.date, ',');
        getline(ss, tx.type, ',');
        getline(ss, tempAmount, ',');
        getline(ss, tx.category, ',');
        getline(ss, tx.note, ',');

        tx.id = stoi(tempId);
        tx.amount = stod(tempAmount);

        transactions.push_back(tx);
    }
    bookAccount.close();
}
