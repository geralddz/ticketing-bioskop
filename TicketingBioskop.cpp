#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);

struct Movie{
	char kode;
	string jam;
	int harga;
	string judul;
	string teks;
};
stack<Movie> movieStack;

//data film
#define kursi_max 120
typedef struct data_film{
	char kode;
	string jam,judul,ruang;
	int harga, total_kursi;
	long int total_pendapatan;
	struct data_kursi{
		string data[kursi_max], urutan[kursi_max];
	} kursi;
} datafilm;

datafilm film[6];
int total_tiket=0;
long int total=0;

//data pembelian
typedef struct pembelian_tiket{
	string nama, kode;
	int jumlah_tiket;
	long int harga_tiket, total_harga;
	string judul, ruang, jam, nomor_kursi[kursi_max];
} data_pembelian;

queue<data_pembelian> pembelian_queue;
data_pembelian beli[kursi_max*6];

//deklarasi variabel umum
int i, d=0, pilihan_menu;
char pilihan_film;



//============================================= DEKLARASI FUNGSI-FUNGSI =========================================================

void huruf_angka();			//Convert huruf ke angka
void kursi();				//Data nomor kursi
void denah_kursi();			//Denah kursi
void pilih_kursi();			//Pilih kursi
void riwayat_penjualan();	//laporan riwayat penjualan
void penjualan_film();		//laporan penjualan per film

void hal_utama();		//[0] Halaman Utama
void pembelian();		//[1] Halaman Pembelian
void cek_kursi();		//[2] Halaman Cek Sisa Kursi
void queue_pembelian();	//[4] Halaman Antrian Pembelian
void daftarfilm();			//[3] Halaman Daftarfilm



//=============================================== PROGRAM UTAMA =======================================================

//PROGRAM UTAMA
int main(){
	
	kursi(); //isi data nomor kursi
	
	do{
		hal_utama();
	
		switch(pilihan_menu){
			case 1:
				system("cls");
				daftarfilm();
				break;
			case 2:
				system("cls");
				pembelian();
				break;
			case 3:
				system("cls");
				cek_kursi();
				break;
			case 4:
				system("cls");
				queue_pembelian();
				break;
			case 5:
				system("cls");
				riwayat_penjualan();
				break;
			case 6:
				system("cls");
				penjualan_film();
				break;
			case 7:
				cout<<endl;
				cout<<"\t------------------------------------------------------------------"<<endl;
				cout<<endl;
				cout<<"\t			   TERIMA KASIH!"<<endl;
				return 0;
				break;
			}
		}
	while(pilihan_menu>=1 && pilihan_menu<=6);
}	
	


//============================================= DEFINISI FUNGSI-FUNGSI =========================================================

void displayMovie(Movie* movie) {
    cout<<"\t| ["<<movie->kode<<"]  |"<<"   "<<movie->judul<<"  |"<<"\t  "<<movie->jam<<" WIB"<<"\t|   Rp "<<movie->harga<<"\t|"<<endl;
}

void daftarfilm(){
	
	//isi daftar dengan Stack
	movieStack.push({'F',"20:30",35000,"MISSION IMPOSSIBLE     ","Mission Impossible"});
	movieStack.push({'E',"19:30",35000,"AVANGER : END GAME     ","Avanger : End Game"});
	movieStack.push({'D',"18:15",35000,"SPIDERMAN : NO WAY HOME","Spiderman : No Way Home"});
	movieStack.push({'C',"20:30",20000,"HOME ALONE             ","Home Alone"});
	movieStack.push({'B',"19:30",20000,"FROZEN                 ","Frozen"});
	movieStack.push({'A',"18:15",20000,"KUNGFU PANDA           ","Kungfu Panda"});
	
	cout<<"\t========================================================================="<<endl;
	cout<<"\t|\t\t\t\tDAFTAR FILM\t\t\t\t|"<<endl;
	cout<<"\t|\t\t\tMinggu, 24 Desember 2023\t\t\t|"<<endl;
	cout<<"\t========================================================================="<<endl<<endl;
	cout<<"\t========================================================================="<<endl;
	cout<<"\t| KODE |     	  NAMA FILM 	    |    JAM TAYANG     |  HARGA TIKET  |"<<endl;
	cout<<"\t-------------------------------------------------------------------------"<<endl;
	
	while (!movieStack.empty()) {
        Movie* currentMovie = &movieStack.top();
        displayMovie(currentMovie);
        movieStack.pop();
    }
    
    cout<<"\t========================================================================="<<endl;
    cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}

//Convert huruf ke angka
void huruf_angka(int *angka, char huruf){
	if(huruf=='A' || huruf=='a'){*angka=0;}
	else if(huruf=='B' || huruf=='b'){*angka=1;}
	else if(huruf=='C' || huruf=='c'){*angka=2;}
	else if(huruf=='D' || huruf=='d'){*angka=3;}
	else if(huruf=='E' || huruf=='e'){*angka=4;}
	else if(huruf=='F' || huruf=='f'){*angka=5;}
}

//Data nomor kursi
void kursi(){
	for(int i=0; i<6; i++){
		int k=0;
		for(char l='A'; l<='F'; l++){
			int j=0;
			for(j=1; j<=20; j++){
							
				//convert int ke string ke char
				string tmp;
				stringstream ss; //int ke string
				ss << j;
				ss >> tmp;
				
				char string_kursi[tmp.length()];
				
				strcpy(string_kursi, tmp.c_str()); //string ke char
				
				//memasukkan data char ke string data_kursi
				film[i].kursi.data[k].push_back(l);
				
				for(int a=0; a<tmp.length(); a++){
					film[i].kursi.data[k].push_back(string_kursi[a]);
				}
				k++;
			}
		}
	}
	
}


//Denah kursi
void denah_kursi(){
	cout<<endl<<endl;
	cout<<"\t======================================================================================="<<endl;
	cout<<"\t|				     "<<setw(22)<<film[i].judul<<"               	      |"<<endl;
	cout<<"\t======================================================================================="<<endl;
	cout<<endl;
	
	int k=0;
	for(int l=0; l<6; l++){
		int j=0;
		cout<<"\t---------------------------------------------------------------------------------------"<<endl;
		cout<<"\t| ";
		
		for(j=1; j<=20; j++){
			cout<<setiosflags(ios::left);
			
			//cek status kursi
			if(film[i].kursi.urutan[k].empty()){
				cout<<setw(4)<<film[i].kursi.data[k];
			}
			else{
				SetConsoleTextAttribute(h,6);
				cout<<setw(4)<<film[i].kursi.data[k];
			}
			
			SetConsoleTextAttribute(h,7);
			
			if(j==10){
				cout<<"    ";
			}
			
			k++;
		}
		cout<<"|"<<endl;
	}
	cout<<"\t======================================================================================="<<endl;
	
	cout<<endl;
	cout<<"\tKet. :"<<endl;
	cout<<"\t  Warna "; 
	SetConsoleTextAttribute(h,6); 
	cout<<"kuning "; 
	SetConsoleTextAttribute(h,7); 
	cout<<"= sudah dipesan"<<endl;
	cout<<"\t  Warna putih  = belum dipesan"<<endl;
	cout<<endl;
}


//Pilih kursi
void pilih_kursi(){
	
	denah_kursi();
	
	cout<<"\tJumlah kursi yang dipesan	: "; cin>>beli[d].jumlah_tiket;
	cout<<"\t------------------------------------"<<endl;
	
	for (int a = 0; a < beli[d].jumlah_tiket; a++) {
        bool seatFound = false;

        do {
            cout << "\t  Pilih nomor kursi ke-" << a + 1 << "\t: ";
            cin >> beli[d].nomor_kursi[a];

            for (int b = 0; b < kursi_max; b++) {
                if (film[i].kursi.data[b] == beli[d].nomor_kursi[a]) {
                    film[i].kursi.urutan[b] = film[i].kursi.data[b];
                    seatFound = true;
                    break;
                }
            }

            if (!seatFound) {
                cout<<"\n\t  Peringatan: Nomor kursi "<<beli[d].nomor_kursi[a]<<" tidak valid."<<endl;
                cout<<"\t  Silahkan Pilih Kursi yang tersedia\n"<<endl;
            }

        } while (!seatFound);
    }
	
	cout<<endl<<endl;
}


//struk pembelian
void struk_pembelian(){
	cout<<endl<<"\t================================================="<<endl;
	cout<<"\t|		 Struk Pembelian		|"<<endl;
	cout<<"\t================================================="<<endl<<endl;
	cout<<"\tNama			: "<<beli[d].nama<<endl;
	cout<<"\tJudul Film		: "<<beli[d].judul<<endl;
	cout<<"\tHarga Tiket		: Rp "<<beli[d].harga_tiket<<endl;
	cout<<"\tJumlah Tiket		: "<<beli[d].jumlah_tiket<<endl;
	cout<<"\tRuang			: "<<beli[d].ruang<<endl;
	cout<<"\tNomor Kursi		: ";
	
	int k=0;
	
	do{	
		int b=0;
		for(b=0; b<4; b++){
			cout<<beli[d].nomor_kursi[k];
			if(k < beli[d].jumlah_tiket-1){
				cout<<", ";
			}
			k++;
		}
		cout<<endl;
		cout<<"				  ";
	}
	while(k < beli[d].jumlah_tiket);
	
	cout<<endl;
	cout<<"\tHari, Tanggal		: "<<"Minggu, 24 Desember 2023"<<endl;
	cout<<"\tJam			: "<<beli[d].jam<<" WIB"<<endl;
	cout<<endl;
	cout<<"\tTotal harga		: Rp "<<beli[d].total_harga;
	
	cout<<endl<<endl;
	cout<<"\t-------------------------------------------------"<<endl<<endl;
	cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}

//Antrian Pembelian
void queue_pembelian() {
    cout<<endl<<"\t========================================================================="<<endl;
	cout<<"\t|			 Antrian Pembelian Tiket			|"<<endl;
	cout<<"\t========================================================================="<<endl<<endl;

	if (!pembelian_queue.empty()) {
	cout<<"\t========================================================================="<<endl;
	cout<<"\t| NO. |	      NAMA PEMBELI	| KODE FILM | JML TIKET |     TOTAL	|"<<endl;
	cout<<"\t-------------------------------------------------------------------------"<<endl;

	int counter = 1;
	    queue<data_pembelian> tempQueue = pembelian_queue;
    
    	//Menampilkan Queue
		while (!tempQueue.empty()) {
            data_pembelian purchase_data = tempQueue.front();
            tempQueue.pop();
		
			cout << setiosflags(ios::left);
    		cout << "\t| " << setw(4) << counter;
    		cout << "| " << setw(24) << purchase_data.nama;
    		cout << "|     " << setw(6) << purchase_data.kode;
    		cout << "|     " << setw(6) << purchase_data.jumlah_tiket;
    		cout << "| " << "Rp " << setw(11) << purchase_data.total_harga;
    		cout << "|" << endl;
			cout<<"\t-------------------------------------------------------------------------"<<endl;
			counter++;
		}
		
		char affirmation;
		cout<<"\n\tLakukan Panggilan Antrian (Y/N) : ";cin>>affirmation;
			if(affirmation=='Y'){
				//Melakukan Pop Queue
		        pembelian_queue.pop();
		        cout<<"\n\tPanggilan Antrian Barhasil\n";
			}else{
				cout<<"\n\tPanggilan Antrian Dibatalkan\n";
			}
	}else{
		cout << "\tAntrian Kosong" << endl;
	}
	
	cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}

//laporan riwayat penjualan
void riwayat_penjualan(){
	string temp;
	int pilihan_pengurutan;
	
	cout<<endl<<"\t========================================================================="<<endl;
	cout<<"\t|			 Riwayat Penjualan Tiket			|"<<endl;
	cout<<"\t========================================================================="<<endl<<endl;
	
	cout << "\t=========================================================================" << endl;
    cout << "\t|             Pilihan Pengurutan Riwayat Penjualan            |" << endl;
    cout << "\t=========================================================================" << endl;
    cout << "\t|  1. Pilih berdasarkan total terbanyak                          |" << endl;
    cout << "\t|  2. Pilih berdasarkan total sedikit                            |" << endl;
    cout << "\t=========================================================================" << endl;
    cout << "\tMasukkan pilihan (1-2): "; cin >> pilihan_pengurutan;
    cout << endl;
    
 // Tambahkan logika pengurutan berdasarkan pilihan_pengurutan
    switch(pilihan_pengurutan) {
        case 1:
        	
        		cout<<"\t========================================================================="<<endl;
				cout<<"\t| NO. |	      NAMA PEMBELI	| KODE FILM | JML TIKET |     TOTAL	|"<<endl;
				cout<<"\t-------------------------------------------------------------------------"<<endl;
            // Pengurutan berdasarkan total harga terbanyak (descending order)
            for (int i = 0; i < d - 1; i++) {
                for (int j = 0; j < d - i - 1; j++) {
                    if (beli[j].total_harga < beli[j + 1].total_harga) {
                        // Tukar elemen jika tidak sesuai urutan
                        swap(beli[j], beli[j + 1]);
                    }
                }
            }
            break;
        case 2:
            // Pengurutan berdasarkan total harga terkecil (ascending order)
            	cout<<"\t========================================================================="<<endl;
				cout<<"\t| NO. |	      NAMA PEMBELI	| KODE FILM | JML TIKET |     TOTAL	|"<<endl;
				cout<<"\t-------------------------------------------------------------------------"<<endl;
            for (int i = 0; i < d - 1; i++) {
                for (int j = 0; j < d - i - 1; j++) {
                    if (beli[j].total_harga > beli[j + 1].total_harga) {
                        // Tukar elemen jika tidak sesuai urutan
                        swap(beli[j], beli[j + 1]);
                    }
                }
            }
            break;
        default:
            cout << "\tPilihan tidak valid." << endl;
    }

	
	
	 // Cetak ulang data setelah diurutkan
    for (int i = 0; i < d; i++) {
        cout << setiosflags(ios::left);
        cout << "\t| " << setw(4) << i + 1;
        cout << "| " << setw(24) << beli[i].nama;
        cout << "|     " << setw(6) << beli[i].kode;
        cout << "|     " << setw(6) << beli[i].jumlah_tiket;
        cout << "| " << "Rp " << setw(11) << beli[i].total_harga;
        cout << "|";
        cout << endl;
    }

	
	
	
	cout<<"\t-------------------------------------------------------------------------"<<endl;
	cout<<"\t|		Total Penjualan		    ";
	cout<<"|     "<<setw(6)<<total_tiket;
	cout<<"| "<<"Rp "<<setw(11)<<total;
	cout<<"|";
	cout<<endl;
	cout<<"\t========================================================================="<<endl;
	
	cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}

//laporan penjualan per film
void penjualan_film(){
	cout<<endl<<"\t========================================================================="<<endl;
	cout<<"\t|			   Penjualan per Film				|"<<endl;
	cout<<"\t========================================================================="<<endl<<endl;
	
	cout<<"\t========================================================================="<<endl;
	cout<<"\t| NO. | KODE FILM |	   NAMA FILM	    | JML TIKET |     TOTAL	|"<<endl;
	cout<<"\t-------------------------------------------------------------------------"<<endl;
	
	
	for(i=0; i<6; i++){
		cout<<setiosflags(ios::left);
		cout<<"\t|  "<<setw(3)<<i+1;
		cout<<"|     "<<setw(6)<<film[i].kode;
		cout<<"| "<<setw(24)<<film[i].judul;
		cout<<"|     "<<setw(6)<<film[i].total_kursi;
		cout<<"| "<<"Rp "<<setw(11)<<film[i].total_pendapatan;
		cout<<"|";
		cout<<endl;
	}
	
	cout<<"\t-------------------------------------------------------------------------"<<endl;
	cout<<"\t|		Total Penjualan		    ";
	cout<<"|     "<<setw(6)<<total_tiket;
	cout<<"| "<<"Rp "<<setw(11)<<total;
	cout<<"|";
	cout<<endl;
	cout<<"\t========================================================================="<<endl;
	
	cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}


//=============================================== HALAMAN =======================================================

//[0] HALAMAN UTAMA
void hal_utama(){
	
	film[0].kode='A'; film[0].jam="18:15"; film[0].harga=20000; film[0].judul="KUNGFU PANDA"; 
	film[1].kode='B'; film[1].jam="19:30"; film[1].harga=20000; film[1].judul="FROZEN";
	film[2].kode='C'; film[2].jam="20:30"; film[2].harga=20000; film[2].judul="HOME ALONE";
	film[3].kode='D'; film[3].jam="18:15"; film[3].harga=35000; film[3].judul="SPIDERMAN : NO WAY HOME";
	film[4].kode='E'; film[4].jam="19:30"; film[4].harga=35000; film[4].judul="AVANGER : END GAME";
	film[5].kode='F'; film[5].jam="20:30"; film[5].harga=35000; film[5].judul="MISSION IMPOSSIBLE";
	
	for(int i=0; i<6; i++){
		if(i<3){
			film[i].ruang="Cinema 1";
		}
		else if(i>=3 && i<6){
			film[i].ruang="Cinema 2";
		}
	}
	
	cout<<endl<<"\t=================================================================="<<endl;
	cout<<"\t|		Ticketing Bioskop Ambarukmo Plaza XXI		 |"<<endl;
	cout<<"\t|	 Kota Yogyakarta, Daerah Istimewa Yogyakarta 55221	 |"<<endl;
	cout<<"\t=================================================================="<<endl<<endl;
	cout<<"\t\t\t\t      Daftar Menu"<<endl;
	cout<<"\t\t\t------------------------------------"<<endl;
	cout<<"\t\t\t  1. Daftar Film"<<endl;
	cout<<"\t\t\t  2. Pembelian Tiket"<<endl;
	cout<<"\t\t\t  3. Cek Sisa Kursi"<<endl;
	cout<<"\t\t\t  4. Antrian Pembelian Tiket"<<endl;
	cout<<"\t\t\t  5. Laporan Riwayat Penjualan Tiket"<<endl;
	cout<<"\t\t\t  6. Laporan Penjualan Tiket per Film"<<endl;
	cout<<"\t\t\t  7. Keluar"<<endl;
	cout<<endl;
	cout<<"\t\t\tMasukkan pilihan (1-6)	: "; cin>>pilihan_menu;
}

//[1] HALAMAN PEMBELIAN
void pembelian(){
	cin.sync();
	
	cout<<endl<<"\t================================================="<<endl;
	cout<<"\t|		 Pembelian Tiket		|"<<endl;
	cout<<"\t================================================="<<endl<<endl;
	
	cout<<"\tNama			: "; cin>>beli[d].nama;
	cout<<endl;
	cout<<"\t-------------------------------------------------"<<endl<<endl;
	cout<<"\tJadwal : Minggu, 24 Desember 2023"<<endl;
	cout<<endl;
	
	cout<<"\t[DAFTAR FILM]\n"<<endl;
	
	for(int i=0; i<6; i++){
		datafilm *filmptr = &film[i];
		cout<<"\t["<<filmptr->kode<<"] "<<filmptr->jam<<" WIB - "<<filmptr->judul<<endl;
	}
	
	cout<<endl;
	cout<<"\tMasukkan pilihan (A-F)	: "; cin>>pilihan_film;
	cout<<endl;
	cout<<"\t-------------------------------------------------"<<endl;
	
	//proses menambahkan data
	string tiket_habis="\t MAAF TIKET SUDAH HABIS!";
	string berhasil="\t\t    PEMBELIAN TIKET BERHASIL!";
	
	int angka;
	huruf_angka(&angka, pilihan_film); //convert inputan huruf ke angka
	
	for(i=0; i<6; i++){
		if(i==angka){
			if(film[i].total_kursi==kursi_max){
				cout<<tiket_habis<<endl;
			}
			else{
				pilih_kursi(); //pilih kursi
				beli[d].kode=film[i].kode;
				beli[d].judul=film[i].judul;
				beli[d].ruang=film[i].ruang;
				beli[d].jam=film[i].jam;
				beli[d].harga_tiket=film[i].harga;
				beli[d].total_harga=film[i].harga*beli[d].jumlah_tiket;
				
				cout<<"\t-------------------------------------------------"<<endl<<endl;
				cout<<"\tTotal harga		: Rp "<<beli[d].total_harga;
				cout<<endl<<endl;
				cout<<berhasil<<endl;
			
				film[i].total_kursi+=beli[d].jumlah_tiket;
				film[i].total_pendapatan+=beli[d].total_harga;
				total_tiket+=beli[d].jumlah_tiket;
				total+=beli[d].total_harga;
				
				pembelian_queue.push(beli[d]);
				
				cout<<endl;
				cout<<"\t================================================="<<endl<<endl;
				
				cout<<"\t"; system("pause"); system("cls");
				
				struk_pembelian();
				
				d++;
			}
		}
	}
}

//[2] HALAMAN CEK KURSI
void cek_kursi(){
	cout<<endl<<"\t======================================================================"<<endl;
	cout<<"\t|			    Cek Sisa Kursi			     |"<<endl;
	cout<<"\t======================================================================"<<endl<<endl;
	cout<<endl;
	
	cout<<"\t======================================================================"<<endl;
	cout<<"\t| NO. | KODE FILM |	   NAMA FILM	    |  TERJUAL  |  TERSEDIA  |"<<endl;
	cout<<"\t----------------------------------------------------------------------"<<endl;
	
	for(i=0; i<6; i++){
		cout<<setiosflags(ios::left);
		cout<<"\t|  "<<setw(3)<<i+1;
		cout<<"|     "<<setw(6)<<film[i].kode;
		cout<<"| "<<setw(24)<<film[i].judul;
		cout<<"|     "<<setw(6)<<film[i].total_kursi;
		cout<<"|     "<<setw(7)<<kursi_max-film[i].total_kursi;
		cout<<"|";
		cout<<endl;
	}
	
	cout<<"\t======================================================================"<<endl;
	cout<<endl;
	
	cout<<"\tLIHAT DENAH KURSI >> Masukkan pilihan (A-F)	: "; cin>>pilihan_film;
	
	int angka;
	huruf_angka(&angka, pilihan_film); //convert inputan huruf ke angka
	
	for(i=0; i<6; i++){
		if(i==angka){
			denah_kursi();
		}
	}
	
	cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}
