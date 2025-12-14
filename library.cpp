#include "library.h"
#include <iostream>
#include <algorithm>
#include <cctype>

LibraryNode::LibraryNode(const Song& song) : data(song), next(nullptr), prev(nullptr) {}

Library::Library() : head(nullptr), songCounter(1) {}

Library::~Library() {
    while (head != nullptr) {
        LibraryNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void Library::addSong(const std::string& title, const std::string& artist, const std::string& genre, int year, const std::vector<std::string>& lyrics) {
    std::string id = "S" + std::to_string(songCounter++);
    LibraryNode* newNode = new LibraryNode(Song(id, title, artist, genre, year, lyrics));
    if (!head) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    std::cout << "Lagu '" << title << "' oleh " << artist << " ditambahkan ke library dengan ID " << id << "." << std::endl;
}

void Library::printLibrary() const {
    if (!head) {
        std::cout << "Library kosong." << std::endl;
        return;
    }
    LibraryNode* current = head;
    std::cout << "\n--- Isi Library ---" << std::endl;
    while (current) {
        std::cout << "ID: " << current->data.id << " | Judul: " << current->data.title
                  << " | Artis: " << current->data.artist << std::endl;
        current = current->next;
    }
    std::cout << "-------------------\n" << std::endl;
}

Song* Library::findSongById(const std::string& id) const {
    LibraryNode* current = head;
    while (current) {
        if (current->data.id == id) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

std::vector<Song*> Library::findSongsByTitle(const std::string& title) const {
    std::vector<Song*> results;
    LibraryNode* current = head;
    std::string lowerTitle = title;
    std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
    while (current) {
        std::string currentTitle = current->data.title;
        std::transform(currentTitle.begin(), currentTitle.end(), currentTitle.begin(), ::tolower);
        if (currentTitle.find(lowerTitle) != std::string::npos) {
            results.push_back(&(current->data));
        }
        current = current->next;
    }
    return results;
}

void Library::updateSong(const std::string& id, const std::string& newTitle, const std::string& newArtist,
                        const std::string& newGenre, int newYear, const std::vector<std::string>& newLyrics) {
    LibraryNode* current = head;
    while (current) {
        if (current->data.id == id) {
            current->data.title = newTitle;
            current->data.artist = newArtist;
            current->data.genre = newGenre;
            current->data.year = newYear;
            current->data.lyrics = newLyrics;
            std::cout << "Data lagu dengan ID " << id << " telah diperbarui." << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Lagu dengan ID " << id << " tidak ditemukan." << std::endl;
}

void Library::removeSong(const std::string& id) {
    LibraryNode* current = head;
    while (current && current->data.id != id) {
        current = current->next;
    }

    if (!current) {
        std::cout << "Lagu dengan ID " << id << " tidak ditemukan." << std::endl;
        return;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    }

    delete current;
    std::cout << "Lagu dengan ID " << id << " telah dihapus dari library." << std::endl;
}

Song* Library::findNextSimilar(const Song* current) const {
    if (!current || !head) return nullptr;

    // 1) cari lagu lain dengan artis sama
    LibraryNode* node = head;
    while (node) {
        if (node->data.artist == current->artist && node->data.id != current->id) return &(node->data);
        node = node->next;
    }

    // 2) cari lagu lain dengan genre sama
    node = head;
    while (node) {
        if (node->data.genre == current->genre && node->data.id != current->id) return &(node->data);
        node = node->next;
    }

    // 3) fallback: next node in list after current
    node = head;
    while (node && node->data.id != current->id) node = node->next;
    if (node && node->next) return &(node->next->data);

    // 4) otherwise return head (wrap)
    return head ? &(head->data) : nullptr;
}

Song* Library::findPrevSimilar(const Song* current) const {
    if (!current || !head) return nullptr;

    // 1) cari lagu lain dengan artis sama (cari dari akhir ke awal)
    LibraryNode* node = head;
    LibraryNode* lastMatch = nullptr;
    while (node) {
        if (node->data.artist == current->artist && node->data.id != current->id) lastMatch = node;
        node = node->next;
    }
    if (lastMatch) return &(lastMatch->data);

    // 2) cari lagu lain dengan genre sama (dari akhir)
    node = head;
    lastMatch = nullptr;
    while (node) {
        if (node->data.genre == current->genre && node->data.id != current->id) lastMatch = node;
        node = node->next;
    }
    if (lastMatch) return &(lastMatch->data);

    // 3) fallback: previous node in list before current
    node = head;
    while (node && node->data.id != current->id) node = node->next;
    if (node && node->prev) return &(node->prev->data);

    // 4) otherwise return tail (wrap)
    node = head;
    if (!node) return nullptr;
    while (node->next) node = node->next;
    return &(node->data);
}

bool Library::likeSong(const std::string& id) {
    LibraryNode* current = head;
    while (current) {
        if (current->data.id == id) {
            if (!current->data.liked) {
                current->data.liked = true;
                std::cout << "Lagu dengan ID " << id << " telah dilike." << std::endl;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

bool Library::unlikeSong(const std::string& id) {
    LibraryNode* current = head;
    while (current) {
        if (current->data.id == id) {
            if (current->data.liked) {
                current->data.liked = false;
                std::cout << "Lagu dengan ID " << id << " telah di-unlike." << std::endl;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

std::vector<Song*> Library::getLikedSongs() const {
    std::vector<Song*> results;
    LibraryNode* current = head;
    while (current) {
        if (current->data.liked) results.push_back(&(current->data));
        current = current->next;
    }
    return results;
}