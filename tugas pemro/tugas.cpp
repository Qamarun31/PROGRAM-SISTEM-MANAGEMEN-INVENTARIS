#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Enum untuk status barang
enum ItemStatus {
    AVAILABLE, // Tersedia
    OUT_OF_STOCK // Habis stok
};

// Kelas yang merepresentasikan barang dalam inventaris
class Item {
public:
    string name; // Nama barang
    int quantity; // Jumlah barang
    float price; // Harga barang
    ItemStatus status; // Status barang

    // Konstruktor
    Item(string name, int quantity, float price) {
        this->name = name;
        this->quantity = quantity;
        this->price = price;
        this->status = (quantity > 0) ? AVAILABLE : OUT_OF_STOCK; // Tentukan status berdasarkan jumlah barang
    }
};

// Kelas yang merepresentasikan inventaris
class Inventory {
private:
    vector<Item> items; // Daftar barang

public:
    // Menambahkan barang baru ke inventaris
    void addItem(const string& name, int quantity, float price) {
        items.emplace_back(name, quantity, price);
        cout << "Barang berhasil ditambahkan: " << name << endl;
    }

    // Menampilkan semua barang dalam inventaris
    void displayItems() {
        if (items.empty()) {
            cout << "\nInventaris kosong!\n";
            return;
        }
        cout << "\nDaftar Barang dalam Inventaris:\n";
        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].name
                 << " - Jumlah: " << items[i].quantity
                 << ", Harga: " << items[i].price
                 << ", Status: " << (items[i].status == AVAILABLE ? "Tersedia" : "Habis Stok") << endl;
        }
    }

    // Memperbarui jumlah barang
    void updateItemQuantity(int index, int quantity) {
        if (index < 0 || index >= items.size()) {
            cout << "Indeks barang tidak valid!" << endl;
            return;
        }
        items[index].quantity = quantity;
        items[index].status = (quantity > 0) ? AVAILABLE : OUT_OF_STOCK;
        cout << "Jumlah barang diperbarui: " << items[index].name << endl;
    }

    // Menghitung total stok menggunakan rekursi
    int calculateTotalStock() {
        return calculateTotalStockRecursive(items.size() - 1);
    }

    // Fungsi pembantu rekursif untuk menghitung total stok
    int calculateTotalStockRecursive(int index) {
        if (index < 0) return 0;
        return items[index].quantity + calculateTotalStockRecursive(index - 1);
    }

    // Menyimpan inventaris ke file CSV
    void saveToCSV(const string& filename) {
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            cerr << "Kesalahan: Tidak dapat membuka file untuk menulis!" << endl;
            return;
        }
        outfile << "Nama,Jumlah,Harga,Status\n"; // Header CSV
        for (const auto& item : items) {
            outfile << item.name << ","
                    << item.quantity << ","
                    << item.price << ","
                    << (item.status == AVAILABLE ? "Tersedia" : "Habis Stok") << "\n";
        }
        outfile.close();
        cout << "Data berhasil disimpan ke " << filename << endl;
    }
};

// Program utama
int main() {
    Inventory inventory;
    int pilihan;
    string name;
    int quantity;
    float price;

    do {
        cout << "\n=== Sistem Manajemen Inventaris ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Inventaris\n";
        cout << "3. Perbarui Jumlah Barang\n";
        cout << "4. Hitung Total Stok\n";
        cout << "5. Simpan ke CSV\n";
        cout << "6. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama barang: ";
                getline(cin, name);
                cout << "Masukkan jumlah: ";
                cin >> quantity;
                cout << "Masukkan harga: ";
                cin >> price;
                inventory.addItem(name, quantity, price);
                break;
            case 2:
                inventory.displayItems();
                break;
            case 3:
                cout << "Masukkan indeks barang yang ingin diperbarui (dimulai dari 1): ";
                int index;
                cin >> index;
                cout << "Masukkan jumlah baru: ";
                cin >> quantity;
                inventory.updateItemQuantity(index - 1, quantity);
                break;
            case 4:
                cout << "Total Stok: " << inventory.calculateTotalStock() << endl;
                break;
            case 5:
                inventory.saveToCSV("inventory_output.csv");
                break;
            case 6:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 6);

    return 0;
}  