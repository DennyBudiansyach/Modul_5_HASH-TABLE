#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int TABLE_SIZE = 11;

class HashNode
{
public:
    string nim;
    int nilai;

    HashNode(string nim, int nilai)
    {
        this->nim = nim;
        this->nilai = nilai;
    }
};

class HashMap
{
private:
    vector<HashNode *> table[TABLE_SIZE];

    int hashFunc(string key)
    {
        int index = 0;
        for (char c : key)
        {
            index += c;
        }
        return index % TABLE_SIZE;
    }

public:
    void insert(string nim, int nilai)
    {
        int index = hashFunc(nim);
        for (auto node : table[index])
        {
            if (node->nim == nim)
            {
                node->nilai = nilai;
                return;
            }
        }
        table[index].push_back(new HashNode(nim, nilai));
    }

    void remove(string nim)
    {
        int index = hashFunc(nim);
        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if ((*it)->nim == nim)
            {
                table[index].erase(it);
                return;
            }
        }
    }

    int searchByNIM(string nim)
    {
        int index = hashFunc(nim);
        for (auto node : table[index])
        {
            if (node->nim == nim)
            {
                return node->nilai;
            }
        }
        return -1;
    }

    vector<string> searchByRange(int min, int max)
    {
        vector<string> result;
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            for (auto node : table[i])
            {
                if (node->nilai >= min && node->nilai <= max)
                {
                    result.push_back(node->nim);
                }
            }
        }
        return result;
    }

    void print()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << i << ": ";
            for (auto pair : table[i])
            {
                if (pair != nullptr)
                {
                    cout << "[" << pair->nim << ", " << pair->nilai << "]";
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    HashMap student_map;
    int choice;
    string nim;
    int nilai;

    do
    {
        cout << "\nMenu:\n"
             << "1. Tambah Data Mahasiswa\n"
             << "2. Hapus Data Mahasiswa\n"
             << "3. Cari Data Mahasiswa berdasarkan NIM\n"
             << "4. Cari Data Mahasiswa berdasarkan Rentang Nilai (80-90)\n"
             << "5. Keluar\n"
             << "Pilihan: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Masukkan NIM Mahasiswa: ";
            cin >> nim;
            cout << "Masukkan Nilai Mahasiswa: ";
            cin >> nilai;
            student_map.insert(nim, nilai);
            cout << "Data berhasil ditambahkan.\n";
            break;
        case 2:
            cout << "Masukkan NIM Mahasiswa yang akan dihapus: ";
            cin >> nim;
            student_map.remove(nim);
            cout << "Data berhasil dihapus.\n";
            break;
        case 3:
            cout << "Masukkan NIM Mahasiswa yang ingin dicari: ";
            cin >> nim;
            nilai = student_map.searchByNIM(nim);
            if (nilai != -1)
                cout << "Nilai Mahasiswa dengan NIM " << nim << " adalah: " << nilai << endl;
            else
                cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
            break;
        case 4:
            cout << "Mahasiswa dengan Nilai antara 80-90:\n";
            {
                vector<string> result = student_map.searchByRange(80, 90);
                if (result.empty())
                    cout << "Tidak ada mahasiswa dengan nilai antara 80-90.\n";
                else
                {
                    for (const auto &nim : result)
                    {
                        cout << "NIM: " << nim << ", Nilai: " << student_map.searchByNIM(nim) << endl;
                    }
                }
            }
            break;
        case 5:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            break;
        }

    } while (choice != 5);

    return 0;
}
