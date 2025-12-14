#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include <string>
#include "playqueue.h"

struct PlaylistNode {
    Song data;
    PlaylistNode* next;
    PlaylistNode* prev;
    PlaylistNode(const Song& song);
};

class Playlist {
private:
    PlaylistNode* head;
    PlaylistNode* currentPlayingInList;
    std::string name;
    PlayQueue queue;

public:
    Playlist(const std::string& playlistName);
    ~Playlist();

    // Queue operations for this playlist
    void enqueueToQueue(const std::string& songId);
    std::string dequeueFromQueue();
    std::vector<std::string> getQueue() const;
    bool isQueueEmpty() const;

    void addSong(const Song& song);
    void removeSong(const std::string& songId);
    void printPlaylist() const;
    void printPlaylistWithIds() const;
    void playFirst();
    void playNext();
    void playPrev();
    void stop();
    Song* getCurrentSong();
    bool isEmpty() const;
    std::string getName() const;
    void updateSong(const std::string& songId, const Song& updatedSong);
    bool containsSong(const std::string& songId) const;
};

#endif // PLAYLIST_H