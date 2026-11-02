#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <compare>

inline int readNumber(std::istream& in) {
    int n = 0;
    if (!(in >> n)) {
        in.clear();
        n = 0;
    }
    in.ignore(1000, '\n');
    return n;
}

class LibraryItem {
private:
    int id;
    std::string title;
    int year;

public:
    LibraryItem(int itemId, const std::string& itemTitle, int itemYear);
    virtual ~LibraryItem() = default;

    int getId() const;
    std::string getTitle() const;
    int getYear() const;
    void setTitle(std::string_view newTitle);
    void setYear(int newYear);

    virtual std::string getType() const = 0;
    virtual int getLoanDays() const = 0;
    virtual double calcOverdueFine(int daysLate) const = 0;   
    virtual double calcLossCompensation() const = 0;          
    virtual void printInfo(std::ostream& out) const;
    void readFrom(std::istream& in);


    bool operator==(const LibraryItem& other) const;

    std::strong_ordering operator<=>(const LibraryItem& other) const;

    friend std::ostream& operator<<(std::ostream& out, const LibraryItem& item) {
        item.printInfo(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, LibraryItem& item) {
        item.readFrom(in);
        return in;
    }
};
