#include "playqueue.h"

void PlayQueue::enqueue(const std::string &id) {
    q.push_back(id);
}

std::string PlayQueue::dequeue() {
    if (q.empty()) return "";
    std::string id = q.front();
    q.pop_front();
    return id;
}

bool PlayQueue::isEmpty() const {
    return q.empty();
}

void PlayQueue::clear() {
    q.clear();
}

std::vector<std::string> PlayQueue::toVector() const {
    return std::vector<std::string>(q.begin(), q.end());
}
