#ifndef LIBRARY_H
#define LIBRARY_H

#include "song.h"
#include <vector>
#include <string>

struct LibraryNode {
    Song data;
    LibraryNode* next;
    LibraryNode* prev;
    LibraryNode(const Song& song);
};

class Library {
private:
    LibraryNode* head;
    int songCounter;

public:
    Library();
    ~Library();

    void addSong(const std::string& title, const std::string& artist, const std::string& genre, int year, const std::vector<std::string>& lyrics);
    void printLibrary() const;
    Song* findSongById(const std::string& id) const;
    std::vector<Song*> findSongsByTitle(const std::string& title) const;
    Song* findNextSimilar(const Song* current) const;
    Song* findPrevSimilar(const Song* current) const;
    void updateSong(const std::string& id, const std::string& newTitle, const std::string& newArtist,
                    const std::string& newGenre, int newYear, const std::vector<std::string>& newLyrics);
    void removeSong(const std::string& id);
    bool likeSong(const std::string& id);
    bool unlikeSong(const std::string& id);
    std::vector<Song*> getLikedSongs() const;
};

#endif // LIBRARY_H