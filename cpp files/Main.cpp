#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Book.h"
#include "Branch.h"
#include "LibraryItem.h"
#include "Magazine.h"
#include "Newspaper.h"
using namespace std;
const int CURRENT_YEAR = 2026;
int readInt(const string& prompt) {
    cout << prompt;
    return readNumber(cin);
}

void readSpecific(Book& book) {
    string text;
    cout << "Автор: ";
    getline(cin, text);
    book.setAuthor(text);
    cout << "Жанр: ";
    getline(cin, text);
    book.setGenre(text);
    cout << "Количество страниц: ";
    book.setPageCount(readNumber(cin));
}
void readSpecific(Newspaper& paper) {
    string text;
    cout << "Номер выпуска: ";
    paper.setIssueNumber(readNumber(cin));
    cout << "Тираж: ";
    paper.setCirculation(readNumber(cin));
    cout << "Издатель: ";
    getline(cin, text);
    paper.setPublisher(text);
}
void readSpecific(Magazine& magazine) {
    string text;
    cout << "Тематика: ";
    getline(cin, text);
    magazine.setTopic(text);
    cout << "Номер выпуска: ";
    magazine.setIssueNumber(readNumber(cin));
    cout << "Целевая аудитория: ";
    getline(cin, text);
    magazine.setTargetAudience(text);
}
void printBranches(const vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}
void showBranches(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printCatalog();
    }
}

LibraryItem* findItem(vector<Branch>& branches, int id) {
    for (Branch& branch : branches) {
        LibraryItem* item = branch.findItemById(id);
        if (item != nullptr) return item;
    }
    return nullptr;
}
Book* findBook(vector<Branch>& branches, int id) {
    for (Branch& branch : branches) {
        Book* book = branch.findBookById(id);
        if (book != nullptr) return book;
    }
    return nullptr;
}
Newspaper* findNewspaper(vector<Branch>& branches, int id) {
    for (Branch& branch : branches) {
        Newspaper* paper = branch.findNewspaperById(id);
        if (paper != nullptr) return paper;
    }
    return nullptr;
}
Magazine* findMagazine(vector<Branch>& branches, int id) {
    for (Branch& branch : branches) {
        Magazine* magazine = branch.findMagazineById(id);
        if (magazine != nullptr) return magazine;
    }
    return nullptr;
}

void printFullInfo(vector<Branch>& branches, int id) {
    const LibraryItem* item = findItem(branches, id);
    if (item == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << "Тип: " << item->getType() << "\n" << *item;  
}

void showItemInfo(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    printFullInfo(branches, id);
}

void addItem(vector<Branch>& branches, int& nextId) {
    cout << "Что добавить? 1 - книга, 2 - газета, 3 - журнал: ";
    int type = readNumber(cin);
    if (type < 1 || type > 3) {
        cout << "Некорректный тип.\n";
        return;
    }
    cout << "В какой филиал добавить?\n";
    printBranches(branches);
    int choice = readInt("Номер филиала: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    if (branches[index].isFull()) {
        cout << "Филиал \"" << branches[index].getName() << "\" переполнен.\n";
        return;
    }
    if (type == 1) {
        Book book(nextId, "", 0, "", "", 0);
        cin >> book;                 
        readSpecific(book);   
        branches[index] += book;     
    }
    else if (type == 2) {
        Newspaper paper(nextId, "", 0, 0, 0, "");
        cin >> paper;
        readSpecific(paper);
        branches[index] += paper;
    }
    else {
        Magazine magazine(nextId, "", 0, "", 0, "");
        cin >> magazine;
        readSpecific(magazine);
        branches[index] += magazine;
    }
    nextId++;
}
void deleteItem(vector<Branch>& branches) {
    printBranches(branches);
    int choice = readInt("Из какого филиала удалить издание: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    branches[index].printCatalog();
    int id = readInt("Введите ID издания для удаления: ");
    branches[index] -= id;  
}
void showSameAuthor(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    const Book* book = findBook(branches, id);
    if (book == nullptr) {
        cout << "Книга с таким ID не найдена (автор есть только у книг).\n";
        return;
    }
    cout << "Другие книги автора " << book->getAuthor() << ":\n";
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printOtherBooksBySameAuthor(*book);
    }
    if (total == 0) {
        cout << " Других книг этого автора нет.\n";
    }
}

void showUpToYear(const vector<Branch>& branches) {
    int year = readInt("Введите год: ");
    Book ref(0, "", year, "", "", 0);   
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printItemsUpToYear(ref);
    }
    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}
void showAfterYear(const vector<Branch>& branches) {
    int year = readInt("Введите год: ");
    Book ref(0, "", year, "", "", 0);
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printItemsAfterYear(ref);
    }
    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void showLoanTerms(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printLoanTerms();
    }
}

void useBookMethod(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    const Book* book = findBook(branches, id);
    if (book == nullptr) {
        cout << "Книга с таким ID не найдена.\n";
        return;
    }
    int pages = readInt("Сколько страниц в день читает читатель: ");
    if (book->canFinishInLoanPeriod(pages)) {
        cout << "Читатель успеет дочитать книгу за срок выдачи (" << book->getLoanDays() << " дн.).\n";
    }
    else {
        cout << "Читатель НЕ успеет дочитать книгу за срок выдачи (" << book->getLoanDays() << " дн.).\n";
    }
}

void useNewspaperMethod(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID газеты: ");
    const Newspaper* paper = findNewspaper(branches, id);
    if (paper == nullptr) {
        cout << "Газета с таким ID не найдена.\n";
        return;
    }
    if (paper->canTakeHome(CURRENT_YEAR)) {
        cout << "Номер можно взять домой.\n";
    }
    else {
        cout << "Номер домой брать нельзя (маленький тираж и/или старше 15 лет).\n";
    }
}

void useMagazineMethod(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID журнала: ");
    const Magazine* magazine = findMagazine(branches, id);
    if (magazine == nullptr) {
        cout << "Журнал с таким ID не найден.\n";
        return;
    }
    cout << "Введите аудиторию: ";
    string audience;
    getline(cin, audience);
    if (magazine->suitableFor(audience)) {
        cout << "Журнал подходит для этой аудитории.\n";
    }
    else {
        cout << "Журнал не подходит для этой аудитории.\n";
    }
}

void showAllInfo(const vector<Branch>& branches) {
    cout << "Полная информация обо всех изданиях (полиморфный вызов printInfo):\n\n";
    for (const Branch& branch : branches) {
        branch.printAllInfo();
    }
}

void showOverdueFines(const vector<Branch>& branches) {
    int days = readInt("Введите число дней просрочки: ");
    if (days < 0) {
        cout << "Число дней не может быть отрицательным.\n";
        return;
    }
    for (const Branch& branch : branches) {
        branch.printOverdueFines(days);
    }
}

void showLossCompensations(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printLossCompensations();
    }
}

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и издания в них\n";
    cout << "2. Информация об издании\n";
    cout << "3. Добавить издание\n";
    cout << "4. Удалить издание\n";
    cout << "5. Другие книги того же автора\n";
    cout << "6. Издания, выпущенные в указанном году и раньше\n";
    cout << "7. Издания, выпущенные после указанного года\n";
    cout << "8. Сроки выдачи изданий\n";
    cout << "9. Книга: успеет ли читатель дочитать\n";
    cout << "10. Газета: можно ли взять домой\n";
    cout << "11. Журнал: подходит ли аудитории\n";
    cout << "12. Полная информация обо всех изданиях\n";
    cout << "13. Штраф за просрочку для всех изданий\n";
    cout << "14. Компенсация за утерю для всех изданий\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}
int main() {
    vector<Branch> branches;
    branches.emplace_back("Филиал №1", 6);
    branches.emplace_back("Филиал №2", 6);
    int nextId = 1;
    branches[0] += Book(nextId++, "Война и мир", 1869, "Л.Н. Толстой", "Роман", 1225);
    branches[0] += Book(nextId++, "Мастер и Маргарита", 1967, "М.А. Булгаков", "Роман", 480);
    branches[0] += Newspaper(nextId++, "Звязда", 2026, 210, 25000, "Издательский дом «Звязда»");
    branches[1] += Book(nextId++, "Анна Каренина", 1877, "Л.Н. Толстой", "Роман", 864);
    branches[1] += Book(nextId++, "Воскресение", 1899, "Л.Н. Толстой", "Роман", 480);
    branches[1] += Magazine(nextId++, "Наука и жизнь", 2025, "Наука", 7, "взрослые");
    branches[1] += Newspaper(nextId++, "Советская Беларусь", 2025, 99, 80000, "Редакция СБ");
    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
        case 1: showBranches(branches); break;
        case 2: showItemInfo(branches); break;
        case 3: addItem(branches, nextId); break;
        case 4: deleteItem(branches); break;
        case 5: showSameAuthor(branches); break;
        case 6: showUpToYear(branches); break;
        case 7: showAfterYear(branches); break;
        case 8: showLoanTerms(branches); break;
        case 9: useBookMethod(branches); break;
        case 10: useNewspaperMethod(branches); break;
        case 11: useMagazineMethod(branches); break;
        case 12: showAllInfo(branches); break;
        case 13: showOverdueFines(branches); break;
        case 14: showLossCompensations(branches); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);
    return 0;
}
