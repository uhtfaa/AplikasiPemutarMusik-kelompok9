#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

struct Song {
    std::string id;
    std::string title;
    std::string artist;
    std::string genre;
    int year;
    std::vector<std::string> lyrics;
    bool liked;

    Song(const std::string& _id = "", const std::string& _title = "", const std::string& _artist = "",
         const std::string& _genre = "", int _year = 0, const std::vector<std::string>& _lyrics = {});
};

#endif // SONG_H