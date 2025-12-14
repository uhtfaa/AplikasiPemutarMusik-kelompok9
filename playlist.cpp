#include "playlist.h"
#include "playqueue.h"
#include <iostream>

PlaylistNode::PlaylistNode(const Song& song) : data(song), next(nullptr), prev(nullptr) {}

Playlist::Playlist(const std::string& playlistName)
    : head(nullptr), currentPlayingInList(nullptr), name(playlistName) {}

Playlist::~Playlist() {
    while (head != nullptr) {
        PlaylistNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void Playlist::addSong(const Song& song) {
    PlaylistNode* newNode = new PlaylistNode(song);
    if (!head) {
        head = newNode;
        if (!currentPlayingInList) {
            currentPlayingInList = head;
        }
    } else {
        PlaylistNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
    std::cout << "Lagu '" << song.title << "' ditambahkan ke playlist '" << name << "'." << std::endl;
}

void Playlist::removeSong(const std::string& songId) {
    PlaylistNode* current = head;
    while (current && current->data.id != songId) {
        current = current->next;
    }

    if (!current) {
        std::cout << "Lagu dengan ID " << songId << " tidak ditemukan." << std::endl;
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

    if (current == currentPlayingInList) {
        if (current->next) {
            currentPlayingInList = current->next;
        } else if (current->prev) {
            currentPlayingInList = current->prev;
        } else {
            currentPlayingInList = nullptr;
        }
    }

    delete current;
    std::cout << "Lagu dengan ID " << songId << " dihapus dari playlist '" << name << "'." << std::endl;
}

void Playlist::printPlaylist() const {
    if (!head) {
        std::cout << "Playlist '" << name << "' kosong." << std::endl;
        return;
    }
    PlaylistNode* current = head;
    int index = 1;
    std::cout << "\n--- Isi Playlist: " << name << " ---" << std::endl;
    while (current) {
        std::cout << index << ". " << current->data.title << " - " << current->data.artist << std::endl;
        current = current->next;
        index++;
    }
    std::cout << "---------------------------\n" << std::endl;
}

void Playlist::printPlaylistWithIds() const {
    if (!head) {
        std::cout << "Playlist '" << name << "' kosong." << std::endl;
        return;
    }
    PlaylistNode* current = head;
    int index = 1;
    std::cout << "\n--- Isi Playlist: " << name << " (dengan ID) ---" << std::endl;
    while (current) {
        std::cout << index << ". [" << current->data.id << "] " << current->data.title << " - " << current->data.artist << std::endl;
        current = current->next;
        index++;
    }
    std::cout << "---------------------------\n" << std::endl;
}

void Playlist::playFirst() {
    if (head) {
        currentPlayingInList = head;
        std::cout << "Memutar lagu pertama: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
    } else {
        std::cout << "Playlist kosong." << std::endl;
    }
}

void Playlist::playNext() {
    if (!head) {
        std::cout << "Playlist kosong." << std::endl;
        return;
    }

    if (!currentPlayingInList) {
        // Jika belum ada yang diputar, mulai dari pertama
        currentPlayingInList = head;
        std::cout << "Memutar lagu: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
        return;
    }

    if (currentPlayingInList->next) {
        currentPlayingInList = currentPlayingInList->next;
        std::cout << "Memutar lagu berikutnya: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
    } else {
        // sudah di akhir, wrap ke awal
        currentPlayingInList = head;
        std::cout << "Sudah di lagu terakhir. Kembali ke lagu pertama: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
    }
}

void Playlist::playPrev() {
    if (!head) {
        std::cout << "Playlist kosong." << std::endl;
        return;
    }

    if (!currentPlayingInList) {
        // Jika belum ada yang diputar, mulai dari terakhir
        PlaylistNode* tail = head;
        while (tail->next) tail = tail->next;
        currentPlayingInList = tail;
        std::cout << "Memutar lagu: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
        return;
    }

    if (currentPlayingInList->prev) {
        currentPlayingInList = currentPlayingInList->prev;
        std::cout << "Memutar lagu sebelumnya: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
    } else {
        // sudah di awal, wrap ke akhir
        PlaylistNode* tail = head;
        while (tail->next) tail = tail->next;
        currentPlayingInList = tail;
        std::cout << "Sudah di lagu pertama. Kembali ke lagu terakhir: " << currentPlayingInList->data.title
                  << " oleh " << currentPlayingInList->data.artist << std::endl;
    }
}

void Playlist::stop() {
    if (currentPlayingInList) {
        std::cout << "Pemutaran dihentikan." << std::endl;
        currentPlayingInList = nullptr;
    } else {
        std::cout << "Tidak ada lagu yang diputar." << std::endl;
    }
}

Song* Playlist::getCurrentSong() {
    if (currentPlayingInList) {
        return &(currentPlayingInList->data);
    }
    return nullptr;
}

bool Playlist::isEmpty() const {
    return head == nullptr;
}

std::string Playlist::getName() const {
    return name;
}

// Queue-related methods
void Playlist::enqueueToQueue(const std::string& songId) {
    // lazy: store song IDs in the queue
    queue.enqueue(songId);
}

std::string Playlist::dequeueFromQueue() {
    return queue.dequeue();
}

std::vector<std::string> Playlist::getQueue() const {
    return queue.toVector();
}

bool Playlist::isQueueEmpty() const {
    return queue.isEmpty();
}

void Playlist::updateSong(const std::string& songId, const Song& updatedSong) {
    PlaylistNode* current = head;
    while (current && current->data.id != songId) {
        current = current->next;
    }
    if (current) {
        current->data = updatedSong;
        std::cout << "Lagu di playlist diperbarui." << std::endl;
    }
}

bool Playlist::containsSong(const std::string& songId) const {
    PlaylistNode* current = head;
    while (current) {
        if (current->data.id == songId) {
            return true;
        }
        current = current->next;
    }
    return false;
}