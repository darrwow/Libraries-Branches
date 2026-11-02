#include "Publication.h"
using namespace std;

Publication::Publication(int publicationId, const string& publicationTitle, const string& publicationPublisher, int publicationYear)
    : id(publicationId), title(publicationTitle), publisher(publicationPublisher), year(publicationYear) {}

int Publication::getId() const { return id; }
string Publication::getTitle() const { return title; }
string Publication::getPublisher() const { return publisher; }
int Publication::getYear() const { return year; }

void Publication::printShort() const {
    cout << " ID " << id << ": \"" << title << "\", " << publisher << ", " << year << " г.\n";
}

bool Publication::operator==(const Publication& other) const { return id == other.id; }
bool Publication::operator<=(const Publication& other) const { return year <= other.year; }
bool Publication::operator>(const Publication& other) const { return year > other.year; }


bool samePublisher(const Publication& a, const Publication& b) {
    return a.publisher == b.publisher;
}
