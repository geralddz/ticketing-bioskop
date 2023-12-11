#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <sstream>

using namespace std;

HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);


//stack
struct stack{
	int atas[6];
} tumpuk;

//data film
#define kursi_max 120
typedef struct data_film{
	char kode;
	string jam, judul, ruang, teks;
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
	char nama[60], kode;
	int jenis_tiket, jumlah_tiket;
	long int harga_tiket, total_harga;
	string judul, ruang, jam, nomor_kursi[kursi_max];
} data_pembelian;

data_pembelian beli[kursi_max*6];
char nama[60];

//deklarasi variabel umum
int i, d=0, pilihan_menu, pilihan_kategori, pilihan_laporan;
char pilihan_film;



//============================================= DEKLARASI FUNGSI-FUNGSI =========================================================

void huruf_angka();			//Convert huruf ke angka
void kursi();				//Data nomor kursi
void denah_kursi();			//Denah kursi
void pilih_kursi();			//Pilih kursi
void riwayat_penjualan();	//laporan riwayat penjualan
void penjualan_film();		//laporan penjualan per film

void hal_utama();	//[0] Halaman Utama
void pembelian();	//[1] Halaman Pembelian
void cek_kursi();	//[2] Halaman Cek Sisa Kursi
void laporan();		//[3] Halaman Laporan


//=============================================== PROGRAM UTAMA =======================================================

//PROGRAM UTAMA
int main(){
	for(i=0; i<6; i++){
		tumpuk.atas[i]=-1;
		film[i].total_kursi=0;
	}
	
	//isi data film
	film[0].kode='A'; film[0].jam="18:15"; film[0].harga=20000; film[0].teks="         NUSSA         "; film[0].judul="Nussa";
	film[1].kode='B'; film[1].jam="19:30"; film[1].harga=20000; film[1].teks="      UPIN & IPIN      "; film[1].judul="Upin & Ipin";
	film[2].kode='C'; film[2].jam="20:30"; film[2].harga=20000; film[2].teks="      TOM & JERRY      "; film[2].judul="Tom & Jerry";
	film[3].kode='D'; film[3].jam="18:15"; film[3].harga=35000; film[3].teks="SPIDERMAN : NO WAY HOME"; film[3].judul="Spiderman: No Way Home";
	film[4].kode='E'; film[4].jam="19:30"; film[4].harga=35000; film[4].teks="     THE ICE ROAD      "; film[4].judul="The Ice Road";
	film[5].kode='F'; film[5].jam="20:30"; film[5].harga=35000; film[5].teks="     RESIDENT EVIL     "; film[5].judul="Resident Evil";
	
	for(int i=0; i<6; i++){
		if(i<3){
			film[i].ruang="Cinema 1";
		}
		else if(i>=3 && i<6){
			film[i].ruang="Cinema 2";
		}
	}
	
	kursi(); //isi data nomor kursi
	
	do{
		hal_utama();
	
		switch(pilihan_menu){
			case 1:
				system("cls");
				pembelian();
				break;
			case 2:
				system("cls");
				cek_kursi();
				break;
			case 3:
				system("cls");
				laporan();
				break;
			case 4:
				cout<<endl;
				cout<<"\t------------------------------------------------------------------"<<endl;
				cout<<endl;
				cout<<"\t			   TERIMA KASIH!"<<endl;
				return 0;
				break;
			}
		}
	while(pilihan_menu>=1 && pilihan_menu<=3);
}


//============================================= DEFINISI FUNGSI-FUNGSI =========================================================

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
	cout<<"\t|				"<<setw(22)<<film[i].teks<<"				      |"<<endl;
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
	
	for(int a=0; a < beli[d].jumlah_tiket; a++){
		cout<<"\t  Pilih nomor kursi ke-"<<a+1<<"	: "; cin>>beli[d].nomor_kursi[a];
		
		//cek posisi indeks kursi
		for(int b=0; b<kursi_max; b++){
			if(film[i].kursi.data[b]==beli[d].nomor_kursi[a]){
				film[i].kursi.urutan[b]=film[i].kursi.data[b];
			}
		}
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
	cout<<"\tHari, Tanggal		: "<<"Minggu, 30 Jan 2022"<<endl;
	cout<<"\tJam			: "<<beli[d].jam<<" WIB"<<endl;
	cout<<endl;
	cout<<"\tTotal harga		: Rp "<<beli[d].total_harga;
	
	cout<<endl<<endl;
	cout<<"\t-------------------------------------------------"<<endl<<endl;
	cout<<endl;
	cout<<"\t"; system("pause"); system("cls");
}


//laporan riwayat penjualan
void riwayat_penjualan(){
	cout<<endl<<"\t========================================================================="<<endl;
	cout<<"\t|			 Riwayat Penjualan Tiket			|"<<endl;
	cout<<"\t========================================================================="<<endl<<endl;
	
	cout<<"\t========================================================================="<<endl;
	cout<<"\t| NO. |	      NAMA PEMBELI	| KODE FILM | JML TIKET |     TOTAL	|"<<endl;
	cout<<"\t-------------------------------------------------------------------------"<<endl;
	
	for(i=0; i<d; i++){
		cout<<setiosflags(ios::left);
		cout<<"\t| "<<setw(4)<<i+1;
		cout<<"| "<<setw(24)<<beli[i].nama;
		cout<<"|     "<<setw(6)<<beli[i].kode;
		cout<<"|     "<<setw(6)<<beli[i].jumlah_tiket;
		cout<<"| "<<"Rp "<<setw(11)<<beli[i].total_harga;
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
	cout<<endl<<"\t=================================================================="<<endl;
	cout<<"\t|		Ticketing Bioskop Ambarukmo Plaza XXI		 |"<<endl;
	cout<<"\t|	 Kota Yogyakarta, Daerah Istimewa Yogyakarta 55221	 |"<<endl;
	cout<<"\t=================================================================="<<endl<<endl;
	
	cout<<"\tDaftar Menu"<<endl;
	cout<<"\t------------------------------------"<<endl;
	cout<<"\t  1. Pembelian Tiket"<<endl;
	cout<<"\t  2. Cek Sisa Kursi"<<endl;
	cout<<"\t  3. Laporan Penjualan Tiket"<<endl;
	cout<<"\t  4. Keluar"<<endl;
	cout<<endl;
	cout<<"\tMasukkan pilihan (1-4)	: "; cin>>pilihan_menu;
}

//[1] HALAMAN PEMBELIAN
void pembelian(){
	cin.sync();
	
	cout<<endl<<"\t================================================="<<endl;
	cout<<"\t|		 Pembelian Tiket		|"<<endl;
	cout<<"\t================================================="<<endl<<endl;
	
	cout<<"\tNama			: "; gets(beli[d].nama);
	cout<<endl;
	cout<<"\t-------------------------------------------------"<<endl<<endl;
	cout<<"\tJENIS TIKET"<<endl;
	cout<<"\t  1. Anak-anak"<<"\tRp 20.000"<<endl;
	cout<<"\t  2. Dewasa"<<"\tRp 35.000"<<endl;
	cout<<endl;
	cout<<"\tMasukkan pilihan (1-2)	: "; cin>>pilihan_kategori;
	cout<<endl;
	cout<<"\t-------------------------------------------------"<<endl<<endl;
	cout<<"\tJadwal : Minggu, 30 Jan 2022"<<endl;
	cout<<endl;
			
	switch(pilihan_kategori){
		case 1:
			cout<<"\tDAFTAR FILM ANAK-ANAK"<<endl;
			
			for(i=0; i<3; i++){
				cout<<"\t  ["<<film[i].kode<<"] "<<film[i].jam<<" WIB - "<<film[i].judul<<endl;
			}
			
			cout<<endl;
			cout<<"\tMasukkan pilihan (A-C)	: "; cin>>pilihan_film;
			break;
		case 2:
			cout<<"\tDAFTAR FILM DEWASA"<<endl;
			
			for(i=3; i<6; i++){
				cout<<"\t  ["<<film[i].kode<<"] "<<film[i].jam<<" WIB - "<<film[i].judul<<endl;
			}
			
			cout<<endl;
			cout<<"\tMasukkan pilihan (D-G)	: "; cin>>pilihan_film;
	}
	
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
				tumpuk.atas[i]++;
				beli[d].jenis_tiket=pilihan_kategori;
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

//[3] HALAMAN LAPORAN
void laporan(){
	cout<<endl<<"\t========================================================================="<<endl;
	cout<<"\t|			  Laporan Penjualan Tiket			|"<<endl;
	cout<<"\t========================================================================="<<endl<<endl;
	
	cout<<"\t  1. Riwayat Penjualan"<<endl;
	cout<<"\t  2. Penjualan per Film"<<endl;
	cout<<endl;
	cout<<"\tMasukkan pilihan (1-2)	: "; cin>>pilihan_laporan;
	cout<<endl;
	cout<<"\t-------------------------------------------------"<<endl<<endl;
	
	switch(pilihan_laporan){
		case 1:
			system("cls");
			riwayat_penjualan();
			break;
		case 2:
			system("cls");
			penjualan_film();
			break;
	}
}


