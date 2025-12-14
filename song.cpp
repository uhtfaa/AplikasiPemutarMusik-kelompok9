#include "song.h"

Song::Song(const std::string& _id, const std::string& _title, const std::string& _artist,
           const std::string& _genre, int _year, const std::vector<std::string>& _lyrics)
       : id(_id), title(_title), artist(_artist), genre(_genre), year(_year), lyrics(_lyrics), liked(false) {}