#include "Branch.h"
#include <iostream>
#include <iomanip>
using namespace std;

Branch::Branch(const string& branchName, int branchCapacity)
    : name(branchName), capacity(branchCapacity) {}

void Branch::printLine(const LibraryItem& item) const {
    cout << " [" << item.getType() << "] ID " << item.getId() << ": \""
         << item.getTitle() << "\", " << item.getYear() << " г.\n";
}

LibraryItem* Branch::findItemById(int id) {
    for (const auto& item : items) {
        if (item->getId() == id) return item.get();
    }
    return nullptr;
}

Book* Branch::findBookById(int id) { return dynamic_cast<Book*>(findItemById(id)); }
Newspaper* Branch::findNewspaperById(int id) { return dynamic_cast<Newspaper*>(findItemById(id)); }
Magazine* Branch::findMagazineById(int id) { return dynamic_cast<Magazine*>(findItemById(id)); }

bool Branch::isFull() const { return getItemsCount() >= capacity; }
string Branch::getName() const { return name; }
int Branch::getCapacity() const { return capacity; }
int Branch::getItemsCount() const { return static_cast<int>(items.size()); }

void Branch::printCatalog() const {
    cout << "=== Филиал \"" << name << "\" (изданий: " << getItemsCount()
         << "/" << capacity << ") ===\n";
    if (getItemsCount() == 0) {
        cout << " В филиале нет изданий.\n";
    }
    for (const auto& item : items) {
        printLine(*item);
    }
}

void Branch::printShort() const {
    cout << name << " (изданий: " << getItemsCount() << "/" << capacity << ")\n";
}

int Branch::printOtherBooksBySameAuthor(const Book& ref) const {
    int count = 0;
    for (const auto& item : items) {
        const Book* book = dynamic_cast<const Book*>(item.get());
        if (book != nullptr && *book != ref && sameAuthor(*book, ref)) {
            cout << name << ":";
            printLine(*book);
            count++;
        }
    }
    return count;
}

int Branch::printItemsUpToYear(const LibraryItem& ref) const {
    int count = 0;
    for (const auto& item : items) {
        if (*item <= ref) {
            cout << name << ":";
            printLine(*item);
            count++;
        }
    }
    return count;
}

int Branch::printItemsAfterYear(const LibraryItem& ref) const {
    int count = 0;
    for (const auto& item : items) {
        if (*item > ref) {
            cout << name << ":";
            printLine(*item);
            count++;
        }
    }
    return count;
}

void Branch::printLoanTerms() const {
    for (const auto& item : items) {
        cout << name << ": [" << item->getType() << "] \"" << item->getTitle()
             << "\" - срок выдачи " << item->getLoanDays() << " дн.\n";
    }
}

void Branch::printAllInfo() const {
    for (const auto& item : items) {
        cout << "[" << item->getType() << ", " << name << "]\n" << *item << "\n";
    }
}


void Branch::printOverdueFines(int daysLate) const {
    for (const auto& item : items) {
        double fine = item->calcOverdueFine(daysLate);
        cout << name << ": [" << item->getType() << "] \"" << item->getTitle()
             << "\" - штраф за " << daysLate << " дн.: " << fixed << setprecision(2) << fine << "\n";
    }
}


void Branch::printLossCompensations() const {
    for (const auto& item : items) {
        double sum = item->calcLossCompensation();
        cout << name << ": [" << item->getType() << "] \"" << item->getTitle()
             << "\" - компенсация за утерю: " << fixed << setprecision(2) << sum << "\n";
    }
}

Branch& Branch::operator+=(const Book& book) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    items.push_back(make_unique<Book>(book));
    cout << "Добавлено: [" << book.getType() << "] \"" << book.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator+=(const Newspaper& paper) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    items.push_back(make_unique<Newspaper>(paper));
    cout << "Добавлено: [" << paper.getType() << "] \"" << paper.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator+=(const Magazine& magazine) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    items.push_back(make_unique<Magazine>(magazine));
    cout << "Добавлено: [" << magazine.getType() << "] \"" << magazine.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator-=(int id) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getId() == id) {
            cout << "Удалено: [" << items[i]->getType() << "] \"" << items[i]->getTitle()
                 << "\" из филиала \"" << name << "\".\n";
            items.erase(items.begin() + i);
            return *this;
        }
    }
    cout << "Ошибка: такого издания нет в филиале \"" << name << "\".\n";
    return *this;
}
