Readme



Deskripsi Aplikasi



&nbsp;	Aplikasi Pemutar Musik berbasis C++ (Console) ini digunakan untuk mengelola data lagu dan playlist, serta menyediakan fitur simulasi pemutaran lagu.

Aplikasi menerapkan konsep Struktur Data Linked List, yaitu:



\- Double Linked List (DLL) untuk menyimpan data lagu



\- Multi Linked List (MLL) untuk mengelola playlist dan hubungan lagu–playlist



Aplikasi memiliki dua peran pengguna, yaitu Admin dan User, dengan hak akses dan fitur yang berbeda.



1\.Struktur Data yang Digunakan

a. Data Lagu (Double Linked List)



Data lagu disimpan dalam Double Linked List, sehingga setiap lagu memiliki pointer ke:



\- Lagu sebelumnya (prev)



\- Lagu berikutnya (next)



Struktur data lagu (InfoLagu) meliputi:



\- ID Lagu



\- Judul Lagu



\- Penyanyi



\- Album



\- Genre



\- Tahun Rilis



\- Durasi Lagu (detik)



Double Linked List memudahkan navigasi Next dan Prev saat pemutaran lagu.



b. Playlist (Multi Linked List / MLL)



Playlist diimplementasikan menggunakan Multi Linked List (MLL), di mana:



\- Satu playlist dapat memiliki banyak lagu



\- Satu lagu dapat berada di banyak playlist



\- Node playlist menyimpan pointer ke lagu di library



Dengan konsep MLL:



\- Data lagu tidak disalin, hanya direferensikan



\- Penghapusan lagu di library otomatis menghapus referensi lagu tersebut di semua playlist



2\.Role dan Fitur Aplikasi

a. Admin



Admin bertanggung jawab mengelola library lagu.



Fitur Admin:



\- Menambahkan lagu baru ke library



\- Menampilkan seluruh lagu di library



\- Mengubah (update) data lagu berdasarkan judul



\- Menghapus lagu berdasarkan ID



\- Menghapus lagu sekaligus membersihkan relasi lagu pada semua playlist (MLL)



b. User



User dapat mengelola playlist dan memutar lagu.



Fitur User:



\- Menampilkan seluruh lagu di library



\- Membuat playlist baru



\- Menampilkan daftar playlist



\- Menambahkan lagu ke playlist



\- Menghapus lagu dari playlist



\- Melihat isi playlist



\- Memutar lagu



3\. Fitur Pemutaran Lagu



a. Fitur pemutaran lagu mendukung:



\- Menampilkan detail lagu yang sedang diputar



b. Next / Prev berdasarkan:



\- Urutan library (Double Linked List)



\- Urutan lagu dalam playlist aktif (MLL)



\- Mengatur playlist aktif sebagai acuan pemutaran



\- Menghentikan pemutaran lagu



4\.Struktur File Program



a. header.h

Berisi deklarasi struktur data dan prototipe fungsi



b. header.cpp

Berisi implementasi:



\- Manajemen lagu (DLL)



\- Manajemen playlist (MLL)



\- Relasi lagu–playlist



\- Pemutaran lagu



\- Menu Admin dan User



c. main.cpp

Berisi fungsi main() sebagai titik awal program dan pemilihan role



5\. Cara Menjalankan Program (Menggunakan CodeBlocks)



Berikut cara menjalankan aplikasi menggunakan CodeBlocks:



&nbsp;	Cara menjalankan program menggunakan CodeBlocks adalah dengan membuka aplikasi CodeBlocks, kemudian membuat project baru bertipe Console Application dengan bahasa C++. Setelah project berhasil dibuat, tambahkan file main.cpp, header.cpp, dan header.h ke dalam project. Pastikan seluruh file berada dalam satu project dan bahasa yang digunakan adalah C++. Selanjutnya pilih menu Build and Run atau tekan tombol F9 untuk melakukan kompilasi dan menjalankan program. Apabila tidak terdapat kesalahan, program akan berjalan pada jendela console dan pengguna dapat langsung berinteraksi dengan menu yang tersedia menggunakan input keyboard.

