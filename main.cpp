#include "library.h"
#include "playlist.h"
#include "song.h"
#include "playqueue.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>  // Untuk parsing lirik jika diperlukan

int main() {
    Library musicLibrary;
    std::vector<Playlist> userPlaylists;

    // Tambah lagu dengan lirik
    std::vector<std::string> lyrics1 = {
        "Is this the real life?",
        "Is this just fantasy?",
        "Caught in a landslide,",
        "No escape from reality."
    };
    musicLibrary.addSong("Bohemian Rhapsody", "Queen", "Rock", 1975, lyrics1);

    std::vector<std::string> lyrics2 = {
        "Shape of you, my heart goes",
        "Dum dum dum",
        "On and on and on and"
    };
    musicLibrary.addSong("Shape of You", "Ed Sheeran", "Pop", 2017, lyrics2);

    std::vector<std::string> lyrics3 = {
        "Tumbuh lebih baik, cari panggilanmu",
        "Jadi lebih baik dibanding diriku",
        "'Tuk sementara ini aku mengembara jauh",
        "Saat dewasa kau kan mengerti"
    };
    musicLibrary.addSong("Nina", ".Feast", "Rock", 2024, lyrics3);

    std::vector<std::string> lyrics4 = {
        "Beri tahu aku cara melupakanmu",
        "Seperti kau ajarkanku dewasa",
        "Beri tahu aku cara merelakanmu",
        "Seperti kau ajarkanku bahagia"
    };
    musicLibrary.addSong("Serana", "For Revenge", "Pop", 2022, lyrics4);

    int roleChoice;
    std::cout << "=== Aplikasi Pemutar Musik ===" << std::endl;

    while (true) {
        std::cout << "\n--- Menu Utama ---" << std::endl;
        std::cout << "1. Login Admin" << std::endl;
        std::cout << "2. Login User" << std::endl;
        std::cout << "3. Keluar" << std::endl;
        std::cout << "Pilih: ";
        std::cin >> roleChoice;

        if (roleChoice == 1) {
            bool adminLoggedIn = true;
            while (adminLoggedIn) {
                int adminChoice;
                std::cout << "\n--- Menu Admin ---" << std::endl;
                std::cout << "1. Tambah Lagu" << std::endl;
                std::cout << "2. Lihat Library" << std::endl;
                std::cout << "3. Update Lagu" << std::endl;
                std::cout << "4. Hapus Lagu" << std::endl;
                std::cout << "5. Logout" << std::endl;
                std::cout << "Pilih: ";
                std::cin >> adminChoice;

                switch (adminChoice) {
                    case 1: {
                        std::cin.ignore();
                        std::string title, artist, genre;
                        int year;
                        std::vector<std::string> lyrics;
                        std::cout << "Judul: ";
                        std::getline(std::cin, title);
                        std::cout << "Artis: ";
                        std::getline(std::cin, artist);
                        std::cout << "Genre: ";
                        std::getline(std::cin, genre);
                        std::cout << "Tahun: ";
                        std::cin >> year;
                        std::cin.ignore();
                        std::cout << "Lirik (masukkan baris per baris, akhiri dengan baris kosong):" << std::endl;
                        std::string line;
                        while (std::getline(std::cin, line) && !line.empty()) {
                            lyrics.push_back(line);
                        }
                        musicLibrary.addSong(title, artist, genre, year, lyrics);
                        break;
                    }
                    case 2: {
                        musicLibrary.printLibrary();
                        break;
                    }
                    case 3: {
                        std::string searchId;
                        std::cout << "Masukkan ID Lagu untuk update: ";
                        std::cin >> searchId;
                        Song* foundSong = musicLibrary.findSongById(searchId);
                        if (foundSong) {
                            std::cin.ignore();
                            std::string newTitle = foundSong->title;
                            std::string newArtist = foundSong->artist;
                            std::string newGenre = foundSong->genre;
                            int newYear = foundSong->year;
                            std::vector<std::string> newLyrics = foundSong->lyrics;
                            
                            bool updateMore = true;
                            while (updateMore) {
                                std::cout << "\n--- Update Lagu: " << foundSong->title << " ---" << std::endl;
                                std::cout << "1. Update Judul (saat ini: " << newTitle << ")" << std::endl;
                                std::cout << "2. Update Artis (saat ini: " << newArtist << ")" << std::endl;
                                std::cout << "3. Update Genre (saat ini: " << newGenre << ")" << std::endl;
                                std::cout << "4. Update Tahun (saat ini: " << newYear << ")" << std::endl;
                                std::cout << "5. Update Lirik" << std::endl;
                                std::cout << "6. Selesai Update" << std::endl;
                                std::cout << "Pilih: ";
                                int updateChoice;
                                std::cin >> updateChoice;
                                std::cin.ignore();
                                
                                switch (updateChoice) {
                                    case 1:
                                        std::cout << "Judul Baru: ";
                                        std::getline(std::cin, newTitle);
                                        std::cout << "Judul diperbarui." << std::endl;
                                        break;
                                    case 2:
                                        std::cout << "Artis Baru: ";
                                        std::getline(std::cin, newArtist);
                                        std::cout << "Artis diperbarui." << std::endl;
                                        break;
                                    case 3:
                                        std::cout << "Genre Baru: ";
                                        std::getline(std::cin, newGenre);
                                        std::cout << "Genre diperbarui." << std::endl;
                                        break;
                                    case 4:
                                        std::cout << "Tahun Baru: ";
                                        std::cin >> newYear;
                                        std::cin.ignore();
                                        std::cout << "Tahun diperbarui." << std::endl;
                                        break;
                                    case 5: {
                                        std::cout << "Lirik Baru (masukkan baris per baris, akhiri dengan baris kosong):" << std::endl;
                                        newLyrics.clear();
                                        std::string line;
                                        while (std::getline(std::cin, line) && !line.empty()) {
                                            newLyrics.push_back(line);
                                        }
                                        std::cout << "Lirik diperbarui." << std::endl;
                                        break;
                                    }
                                    case 6:
                                        updateMore = false;
                                        std::cout << "Menyelesaikan update..." << std::endl;
                                        break;
                                    default:
                                        std::cout << "Pilihan tidak valid." << std::endl;
                                }
                            }
                            
                            musicLibrary.updateSong(searchId, newTitle, newArtist, newGenre, newYear, newLyrics);
                            for (auto& playlist : userPlaylists) {
                                playlist.updateSong(searchId, Song(searchId, newTitle, newArtist, newGenre, newYear, newLyrics));
                            }
                            std::cout << "Lagu berhasil diperbarui." << std::endl;
                        } else {
                            std::cout << "Lagu tidak ditemukan." << std::endl;
                        }
                        break;
                    }
                    case 4: {
                        std::string searchId;
                        std::cout << "Masukkan ID Lagu untuk hapus: ";
                        std::cin >> searchId;
                        Song* foundSong = musicLibrary.findSongById(searchId);
                        if (foundSong) {
                            musicLibrary.removeSong(searchId);
                            for (auto& playlist : userPlaylists) {
                                playlist.removeSong(searchId);
                            }
                        } else {
                            std::cout << "Lagu tidak ditemukan." << std::endl;
                        }
                        break;
                    }
                    case 5: {
                        adminLoggedIn = false;
                        std::cout << "Logout Admin." << std::endl;
                        break;
                    }
                    default:
                        std::cout << "Pilihan tidak valid." << std::endl;
                }
            }
        } else if (roleChoice == 2) {
            bool userLoggedIn = true;
            while (userLoggedIn) {
                int userChoice;
                std::cout << "\n--- Menu User ---" << std::endl;
                std::cout << "1. Cari Lagu" << std::endl;
                std::cout << "2. Putar Lagu dari Library" << std::endl;
                std::cout << "3. Buat/Atur Playlist" << std::endl;
                std::cout << "4. Kelola Antrian Playlist" << std::endl;
                std::cout << "5. Lagu Favorit" << std::endl;
                std::cout << "6. Logout" << std::endl;
                std::cout << "Pilih: ";
                std::cin >> userChoice;

                switch (userChoice) {
                    case 1: {
                        int searchChoice;
                        std::cout << "Cari berdasarkan (1) ID atau (2) Judul? ";
                        std::cin >> searchChoice;
                        if (searchChoice == 1) {
                            std::string searchId;
                            std::cout << "Masukkan ID: ";
                            std::cin >> searchId;
                            Song* foundSong = musicLibrary.findSongById(searchId);
                            if (foundSong) {
                                std::cout << "Ditemukan: ID: " << foundSong->id
                                          << " | Judul: " << foundSong->title
                                          << " | Artis: " << foundSong->artist << std::endl;
                            } else {
                                std::cout << "Tidak ditemukan." << std::endl;
                            }
                        } else if (searchChoice == 2) {
                            std::cin.ignore();
                            std::string searchTitle;
                            std::cout << "Masukkan Judul: ";
                            std::getline(std::cin, searchTitle);
                            std::vector<Song*> foundSongs = musicLibrary.findSongsByTitle(searchTitle);
                            if (!foundSongs.empty()) {
                                std::cout << "Ditemukan:" << std::endl;
                                for (auto song : foundSongs) {
                                    std::cout << "ID: " << song->id
                                              << " | Judul: " << song->title
                                              << " | Artis: " << song->artist << std::endl;
                                }
                            } else {
                                std::cout << "Tidak ada yang cocok." << std::endl;
                            }
                        } else {
                            std::cout << "Pilihan tidak valid." << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        std::string searchId;
                        std::cout << "Masukkan ID Lagu untuk putar: ";
                        std::cin >> searchId;
                        Song* foundSong = musicLibrary.findSongById(searchId);
                        if (foundSong) {
                            Song* current = foundSong;
                            bool playing = true;
                            while (playing && current) {
                                std::cout << "Memutar: " << current->title << " oleh " << current->artist << std::endl;
                                if (!current->lyrics.empty()) {
                                    std::cout << "-- Lirik --" << std::endl;
                                    for (const auto& line : current->lyrics) std::cout << line << std::endl;
                                    std::cout << "-- Selesai Lirik --" << std::endl;
                                } else {
                                    std::cout << "(Tidak ada lirik untuk lagu ini)" << std::endl;
                                }

                                std::cout << "(1) Next Similar, (2) Prev Similar, (3) Stop: ";
                                int playChoice;
                                std::cin >> playChoice;
                                if (playChoice == 1) {
                                    Song* next = musicLibrary.findNextSimilar(current);
                                    if (next) current = next; else { std::cout << "Tidak ada lagu berikutnya." << std::endl; }
                                } else if (playChoice == 2) {
                                    Song* prev = musicLibrary.findPrevSimilar(current);
                                    if (prev) current = prev; else { std::cout << "Tidak ada lagu sebelumnya." << std::endl; }
                                } else if (playChoice == 3) {
                                    playing = false;
                                    std::cout << "Pemutaran dihentikan." << std::endl;
                                } else {
                                    std::cout << "Pilihan tidak valid." << std::endl;
                                }
                            }
                        } else {
                            std::cout << "Lagu tidak ditemukan." << std::endl;
                        }
                        break;
                    }
                    case 3: {
                        while (true) {
                            int playlistChoice;
                            std::cout << "\n--- Menu Playlist ---" << std::endl;
                            std::cout << "1. Buat Playlist Baru" << std::endl;
                            std::cout << "2. Pilih Playlist" << std::endl;
                            std::cout << "3. Hapus Playlist" << std::endl;
                            std::cout << "4. Kembali" << std::endl;
                            std::cout << "Pilih: ";
                            std::cin >> playlistChoice;

                            if (playlistChoice == 1) {
                                std::cin.ignore();
                                std::string playlistName;
                                std::cout << "Nama Playlist: ";
                                std::getline(std::cin, playlistName);
                                userPlaylists.emplace_back(playlistName);
                                std::cout << "Playlist '" << playlistName << "' dibuat." << std::endl;
                            } else if (playlistChoice == 2) {
                                if (userPlaylists.empty()) {
                                    std::cout << "Belum ada playlist." << std::endl;
                                    continue;
                                }
                                std::cout << "Daftar Playlist:" << std::endl;
                                for (size_t i = 0; i < userPlaylists.size(); ++i) {
                                    std::cout << i + 1 << ". " << userPlaylists[i].getName() << std::endl;
                                }
                                int playlistIndex;
                                std::cout << "Pilih nomor: ";
                                std::cin >> playlistIndex;
                                if (playlistIndex > 0 && playlistIndex <= static_cast<int>(userPlaylists.size())) {
                                    auto& currentPlaylist = userPlaylists[playlistIndex - 1];
                                    bool playlistSelected = true;

                                    while (playlistSelected) {
                                        std::cout << "\n--- Menu Playlist: " << currentPlaylist.getName() << " ---" << std::endl;
                                        std::cout << "1. Tambah Lagu" << std::endl;
                                        std::cout << "2. Hapus Lagu" << std::endl;
                                        std::cout << "3. Lihat Playlist" << std::endl;
                                        std::cout << "4. Putar Lagu" << std::endl;
                                        std::cout << "5. Kembali" << std::endl;
                                        std::cout << "Pilih: ";
                                        std::cin >> playlistChoice;

                                        switch (playlistChoice) {
                                            case 1: {
                                                musicLibrary.printLibrary();
                                                std::string songIdToAdd;
                                                std::cout << "Masukkan ID Lagu: ";
                                                std::cin >> songIdToAdd;
                                                Song* songToAdd = musicLibrary.findSongById(songIdToAdd);
                                                if (songToAdd) {
                                                    currentPlaylist.addSong(*songToAdd);
                                                } else {
                                                    std::cout << "Lagu tidak ditemukan." << std::endl;
                                                }
                                                break;
                                            }
                                            case 2: {
                                                currentPlaylist.printPlaylist();
                                                std::string songIdToRemove;
                                                std::cout << "Masukkan ID Lagu: ";
                                                std::cin >> songIdToRemove;
                                                currentPlaylist.removeSong(songIdToRemove);
                                                break;
                                            }
                                            case 3: {
                                                currentPlaylist.printPlaylist();
                                                break;
                                            }
                                            case 4: {
                                                // Masuk ke mode putar: tetap di menu putar sampai user memilih Stop
                                                bool inPlayMenu = true;
                                                while (inPlayMenu) {
                                                    int playOpt;
                                                    std::cout << "\n--- Putar Lagu (Playlist: " << currentPlaylist.getName() << ") ---" << std::endl;
                                                    std::cout << "1. Putar Pertama" << std::endl;
                                                    std::cout << "2. Next Song" << std::endl;
                                                    std::cout << "3. Prev Song" << std::endl;
                                                    std::cout << "4. Stop" << std::endl;
                                                    std::cout << "Pilih: ";
                                                    std::cin >> playOpt;

                                                    if (playOpt == 1) {
                                                        currentPlaylist.playFirst();
                                                    } else if (playOpt == 2) {
                                                        currentPlaylist.playNext();
                                                    } else if (playOpt == 3) {
                                                        currentPlaylist.playPrev();
                                                    } else if (playOpt == 4) {
                                                        currentPlaylist.stop();
                                                        inPlayMenu = false; // keluar ke menu playlist
                                                    } else {
                                                        std::cout << "Pilihan tidak valid." << std::endl;
                                                        continue;
                                                    }

                                                    // Jika ada lagu yang sedang diputar di playlist dan user belum memilih Stop, tampilkan seluruh liriknya
                                                    if (!inPlayMenu) break;
                                                    Song* cur = currentPlaylist.getCurrentSong();
                                                    if (cur) {
                                                        if (!cur->lyrics.empty()) {
                                                            std::cout << "-- Lirik --" << std::endl;
                                                            for (const auto& l : cur->lyrics) std::cout << l << std::endl;
                                                            std::cout << "-- Selesai Lirik --" << std::endl;
                                                        } else {
                                                            std::cout << "(Tidak ada lirik untuk lagu ini)" << std::endl;
                                                        }
                                                    } else {
                                                        std::cout << "(Tidak ada lagu yang diputar)" << std::endl;
                                                    }
                                                }
                                                break;
                                            }
                                            case 5: {
                                                playlistSelected = false;
                                                break;
                                            }
                                            default:
                                                std::cout << "Pilihan tidak valid." << std::endl;
                                        }
                                    }
                                } else {
                                    std::cout << "Nomor tidak valid." << std::endl;
                                }
                            } else if (playlistChoice == 3) {
                                if (userPlaylists.empty()) {
                                    std::cout << "Belum ada playlist." << std::endl;
                                    continue;
                                }
                                std::cout << "Daftar Playlist:" << std::endl;
                                for (size_t i = 0; i < userPlaylists.size(); ++i) {
                                    std::cout << i + 1 << ". " << userPlaylists[i].getName() << std::endl;
                                }
                                int playlistIndex;
                                std::cout << "Pilih nomor playlist untuk dihapus: ";
                                std::cin >> playlistIndex;
                                if (playlistIndex > 0 && playlistIndex <= static_cast<int>(userPlaylists.size())) {
                                    std::string playlistName = userPlaylists[playlistIndex - 1].getName();
                                    userPlaylists.erase(userPlaylists.begin() + (playlistIndex - 1));
                                    std::cout << "Playlist '" << playlistName << "' telah dihapus." << std::endl;
                                } else {
                                    std::cout << "Nomor tidak valid." << std::endl;
                                }
                            } else if (playlistChoice == 4) {
                                break;
                            } else {
                                std::cout << "Pilihan tidak valid." << std::endl;
                            }
                        }
                        break;
                    }
                    case 4: {
                        // Kelola Queue Playlist - independent menu
                        if (userPlaylists.empty()) {
                            std::cout << "Belum ada playlist." << std::endl;
                        } else {
                            std::cout << "Daftar Playlist: " << std::endl;
                            for (size_t i = 0; i < userPlaylists.size(); ++i) {
                                std::cout << i + 1 << ". " << userPlaylists[i].getName() << std::endl;
                            }
                            int playlistIndex;
                            std::cout << "Pilih nomor: ";
                            std::cin >> playlistIndex;
                            if (playlistIndex > 0 && playlistIndex <= static_cast<int>(userPlaylists.size())) {
                                auto& qPlaylist = userPlaylists[playlistIndex - 1];
                                bool inQueueMenu = true;
                                while (inQueueMenu) {
                                    std::cout << "\n--- Kelola Antrian: " << qPlaylist.getName() << " ---" << std::endl;
                                    std::cout << "1. Tambah Lagu ke Antrian" << std::endl;
                                    std::cout << "2. Lihat Antrian" << std::endl;
                                    std::cout << "3. Putar Lagu" << std::endl;
                                    std::cout << "4. Kembali" << std::endl;
                                    std::cout << "Pilih: ";
                                    int qm; std::cin >> qm;
                                    if (qm == 1) {
                                        // Tampilkan daftar lagu di playlist dengan ID
                                        auto playlistSongs = qPlaylist.getQueue(); // ini akan diubah, tapi kita perlu cara lain
                                        // Untuk saat ini, tampilkan playlist dan buat submenu untuk memilih lagu
                                        std::cout << "\n--- Daftar Lagu di Playlist: " << qPlaylist.getName() << " ---" << std::endl;
                                        qPlaylist.printPlaylistWithIds();
                                        std::cout << "Masukkan ID Lagu dari playlist untuk ditambahkan ke antrian: ";
                                        std::string songIdToQueue;
                                        std::cin >> songIdToQueue;
                                        
                                        // Validasi bahwa lagu ada di playlist
                                        if (qPlaylist.containsSong(songIdToQueue)) {
                                            qPlaylist.enqueueToQueue(songIdToQueue);
                                            std::cout << "Lagu ditambahkan ke antrian." << std::endl;
                                        } else {
                                            std::cout << "Lagu tidak ada di playlist ini." << std::endl;
                                        }
                                    } else if (qm == 2) {
                                        auto qv = qPlaylist.getQueue();
                                        if (qv.empty()) {
                                            std::cout << "Antrian kosong." << std::endl;
                                        } else {
                                            std::cout << "Antrian: " << std::endl;
                                            for (size_t i=0;i<qv.size();++i) {
                                                Song* s = musicLibrary.findSongById(qv[i]);
                                                if (s) std::cout << i+1 << ". " << s->title << " (" << s->id << ")" << std::endl;
                                            }
                                        }
                                    } else if (qm == 3) {
                                        if (qPlaylist.isQueueEmpty()) {
                                            std::cout << "Antrian kosong." << std::endl;
                                        } else {
                                            while (!qPlaylist.isQueueEmpty()) {
                                                std::string id = qPlaylist.dequeueFromQueue();
                                                Song* s = musicLibrary.findSongById(id);
                                                if (s) {
                                                    std::cout << "Memutar (dari antrian): " << s->title << " oleh " << s->artist << std::endl;
                                                    if (!s->lyrics.empty()) {
                                                        std::cout << "-- Lirik --" << std::endl;
                                                        for (const auto &ln : s->lyrics) std::cout << ln << std::endl;
                                                        std::cout << "-- Selesai Lirik --" << std::endl;
                                                    }
                                                }
                                            }
                                        }
                                    } else if (qm == 4) {
                                        inQueueMenu = false;
                                    } else {
                                        std::cout << "Pilihan tidak valid." << std::endl;
                                    }
                                }
                            } else {
                                std::cout << "Nomor tidak valid." << std::endl;
                            }
                        }
                        break;
                    }
                    case 5: {
                        // Like / Favorites submenu
                        static std::vector<std::string> favorites; // store liked song IDs
                        bool inLikeMenu = true;
                        while (inLikeMenu) {
                            std::cout << "\n--- Like / Favorit ---" << std::endl;
                            std::cout << "1. Like Lagu" << std::endl;
                            std::cout << "2. Unlike Lagu" << std::endl;
                            std::cout << "3. Lihat Favorit" << std::endl;
                            std::cout << "4. Kembali" << std::endl;
                            std::cout << "Pilih: ";
                            int lm; std::cin >> lm;
                            if (lm == 1) {
                                std::string id; std::cout << "Masukkan ID Lagu untuk like: "; std::cin >> id;
                                if (musicLibrary.likeSong(id)) {
                                    bool found=false; for (auto &fid : favorites) if (fid==id) {found=true; break;} 
                                    if (!found) favorites.push_back(id);
                                } else std::cout << "Lagu tidak ditemukan." << std::endl;
                            } else if (lm == 2) {
                                std::string id; std::cout << "Masukkan ID Lagu untuk unlike: "; std::cin >> id;
                                if (musicLibrary.unlikeSong(id)) {
                                    favorites.erase(std::remove(favorites.begin(), favorites.end(), id), favorites.end());
                                } else std::cout << "Lagu tidak ditemukan." << std::endl;
                            } else if (lm == 3) {
                                if (favorites.empty()) { std::cout << "Belum ada favorits." << std::endl; }
                                else {
                                    std::cout << "Favorit:" << std::endl;
                                    for (size_t i=0;i<favorites.size();++i) {
                                        Song* s = musicLibrary.findSongById(favorites[i]);
                                        if (s) std::cout << i+1 << ". " << s->title << " (" << s->id << ")" << std::endl;
                                    }
                                }
                            } else if (lm == 4) { inLikeMenu = false; }
                            else std::cout << "Pilihan tidak valid." << std::endl;
                        }
                        break;
                    }
                    case 6: {
                        userLoggedIn = false;
                        std::cout << "Logout User." << std::endl;
                        break;
                    }
                    default:
                        std::cout << "Pilihan tidak valid." << std::endl;
                }
            }
        } else if (roleChoice == 3) {
            std::cout << "Terima kasih!" << std::endl;
            break;
        } else {
            std::cout << "Pilihan tidak valid." << std::endl;
        }
    }

    return 0;
}