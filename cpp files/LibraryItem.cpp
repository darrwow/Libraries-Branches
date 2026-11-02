#include "LibraryItem.h"
using namespace std;

LibraryItem::LibraryItem(int itemId, const string& itemTitle, int itemYear)
    : id(itemId), title(itemTitle), year(itemYear) {}

int LibraryItem::getId() const { return id; }
string LibraryItem::getTitle() const { return title; }
int LibraryItem::getYear() const { return year; }
void LibraryItem::setTitle(string_view newTitle) { title = newTitle; }
void LibraryItem::setYear(int newYear) { year = newYear; }

void LibraryItem::printInfo(ostream& out) const {
    out << "ID: " << id << "\n";
    out << "Название: " << title << "\n";
    out << "Год: " << year << "\n";
}

void LibraryItem::readFrom(istream& in) {
    cout << "Название: ";
    getline(in, title);
    cout << "Год издания: ";
    year = readNumber(in);
}

bool LibraryItem::operator==(const LibraryItem& other) const { return id == other.id; }
strong_ordering LibraryItem::operator<=>(const LibraryItem& other) const { return year <=> other.year; }
