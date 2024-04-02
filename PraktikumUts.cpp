#include <iostream>
using namespace std;

//menentukan maksimal penyimpanan history
const int MAX_HISTORY_SIZE = 10;

//struktur node untuk riwayat perhitungan 

struct HistoryNode
{
    char operation; //untuk operasi perhitungan menggunakan tipe data char yang artinya untuk menampung satu digit karakter
    double operand1, operand2; //unutk nilai angka digunakan tipe data double agar angka desimal juga bisa dimasukan ke dalam perhitungan
    double hasil; // hasil juga menggunakan tipe data double agar dapat menghasilkan jumlah desimal juga
    HistoryNode* next; //simpul history
};

// fungsi untuk menambah riwayat perhitungan dengan isi parameternya
void addhistoryNode(HistoryNode*& head, char operat, double op1, double op2, double res)
{
    HistoryNode* newNode = new HistoryNode; //membuat newnode untuk ditambahkan ke linked list. newnode inidialokasikan ke memorimenggunakan operator new
    newNode->operation = operat; //mengatur nilai operasi pada newNode dengan nilai parameter yang diterima dari parameter operat
    newNode->operand1 = op1; //Mengatur nilai operand1 pada newNode dengan nilai yang diterima dari parameter op1.
    newNode->operand2 = op2; // Mengatur nilai operand2 pada newNode dengan nilai yang diterima dari parameter op2.
    newNode->hasil = res; // Mengatur nilai hasil perhitungan pada newNode dengan nilai yang diterima dari parameter res.
    newNode->next = head; //Mengatur pointer next dari newNode untuk menunjuk ke node yang sebelumnya menjadi head dari linked list.
    head = newNode; //Mengubah pointer head untuk menunjuk ke node baru, menjadikannya newNode sebagai head dari linked list.
}

// fungsi untuk menanmpilkan riwat perhitungan
void tampilHistory(HistoryNode *head) //definisi fungsi tampilHisotory dengan mengambil parameter pointer ke head  dari linkedlist (head)
{
    HistoryNode* temp = head; //membuat pointer sementara (temp) dan menginisialisasinya dengan pointer ke head dari linked list
   // loop while yang akan terus berjalan selama pointer sementara (temp) tidak menunjuk ke NULL, menandakan masih ada node dalam linked list yang harus ditampilkan.
    while (temp != NULL)
    {
        //mencetak informasi tentang setiap node dalam linked list. 
        cout << temp->operand1 << " " << temp->operation<< " " << temp->operand2 << "=" << temp->hasil << endl;
        temp = temp->next; //menggeser pointer sementara (temp) ke node berikutnya dalam linked list, sehingga iterasi dapat melanjutkan ke node berikutnya.
    }
}

int main()
{
    HistoryNode* history = NULL; //Pointer ke linked list riwayat perhitungan
    double lastResult[MAX_HISTORY_SIZE] = {0}; //mendefinisikan lokasi penyimpanan perhitungan sebelumnnya
    int resultCount = 0; //mendefinisikan resulcount

//mendefinisikan untuk penggunaan kallkulator
    double operand1, operand2, hasil; //mengunkan tipe data double agar pengguna bebas memakai angka desimal 
    char operation; //menggunankan tipe data char untuk menyimpan simbol operatornya
    char choice; //menggunakan tipe data char untuk menyimpan huruf y/n

//switch case untuk mengeksekusi statement dari berbagai kondisi
    do
    {
        cout << "Masukan angka pertama, operator(+,-,*,/), dan angka kedua: ";
        cin >> operand1 >> operation >> operand2;

        // proses hitung
        switch (operation)
        {
        case '+':
            hasil = operand1 + operand2; //operasi penjumlahan
            break;
        case '-':
            hasil = operand1 - operand2; //operasi pembagian
            break;
        case '*':
            hasil = operand1 * operand2; //operasi perkalian
            break;
        case '/':
            if (operand2 != 0) //kondisi untuk memeriksa apakah operand2 tidak sama dengan nol sebelum melakukan operasi pembagian. Ini untuk menghindari kesalahan pembagian oleh nol.
            {
               hasil = operand1 / operand2; //opeasi pembagian
            }
            else
            {
                cout << "Error: pepmbagian dengan tidak memiliki hasil";
                continue; //pernyataan yang digunakan untuk melanjutkan iterasi berikutnya dari loop do-while jika terjadi kesalahan pembagian oleh nol atau jika operator tidak valid.
            }
            break;
        default:
            cout << "Operasi tidak valid." << endl;
            continue;
        }
        // tambahkan hasil perhitungan ke dalam array
        if (resultCount < MAX_HISTORY_SIZE)  //kondisi untuk memeriksa apakah array lastResult masih memiliki ruang untuk menyimpan hasil perhitungan baru. Jika iya, hasil perhitungan baru akan ditambahkan ke dalam array. Jika tidak, maka hasil perhitungan baru akan menggantikan hasil yang paling awal.
        {
            lastResult[resultCount] = hasil;
            resultCount++;
            
        }
        else
        {
            for (int i = 0; i < MAX_HISTORY_SIZE - 1; ++i)
            {
                lastResult[i] = lastResult[i + 1];
            }
            lastResult[MAX_HISTORY_SIZE - 1] = hasil;
        }

        addhistoryNode(history, operation, operand1, operand2, hasil); //panggilan fungsi yang menambahkan riwayat operasi ke dalam struktur data history.

        cout << "Hasil: " << hasil << endl; //mencetak hasil perhitungan
        cout << "Lanjutkan perhitungan? (y/n): "; //meminta pengguna apakah ingin melanjutkan perhitungan atau tidak. Jika pengguna memilih 'y', loop akan terus berlanjut.
        cin >> choice;
    } while (choice == 'y'); //loop do-while yang akan terus berjalan selama pengguna memilih untuk melanjutkan perhitungan (memasukkan 'y').

     // menampilkan hasil perhitungan terakhir
    cout << "\nHasil Perhitungan Terakhir:\n";
    for (int i = 0; i < resultCount; ++i) {
        cout << lastResult[i] << endl;
    }

    // menampilkan riwayat perhitungan
    cout << "\nRiwayat Perhitungan: " << endl;
    tampilHistory(history);

    // dealokasi memori yang digunakan oleh linkedlist
    while (history != NULL) //Loop akan terus berjalan selama history tidak menunjuk ke NULL. Ini berarti selama masih ada node dalam struktur data history, proses penghapusan akan dilakukan.
    {
        HistoryNode* temp = history; //Sebuah pointer sementara temp dibuat untuk menunjuk ke node yang sedang diproses. Hal ini dilakukan agar node tersebut tidak hilang sebelum dihapus.
        history = history->next; //Pointer history digeser ke node berikutnya dalam struktur data history. Dengan cara ini, setelah penghapusan node saat ini, proses dapat dilanjutkan ke node berikutnya.
        delete temp; //Node yang ditunjuk oleh temp (node saat ini) dihapus dari memori.
    }
    return 0;
}
