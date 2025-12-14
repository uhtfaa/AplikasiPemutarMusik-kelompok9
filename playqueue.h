#ifndef PLAYQUEUE_H
#define PLAYQUEUE_H

#include <string>
#include <deque>
#include <vector>

class PlayQueue {
private:
    std::deque<std::string> q; // store song IDs
public:
    void enqueue(const std::string &id);
    std::string dequeue();
    bool isEmpty() const;
    void clear();
    std::vector<std::string> toVector() const;
};

#endif // PLAYQUEUE_H
