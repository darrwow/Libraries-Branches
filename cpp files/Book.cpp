#include "Book.h"
using namespace std;

Book::Book(int bookId, const string& bookTitle, int bookYear,
           const string& bookAuthor, const string& bookGenre, int bookPageCount)
    : LibraryItem(bookId, bookTitle, bookYear),
      author(bookAuthor), genre(bookGenre), pageCount(bookPageCount) {
}

string Book::getAuthor() const { return author; }
string Book::getGenre() const { return genre; }
int Book::getPageCount() const { return pageCount; }
void Book::setAuthor(string_view newAuthor) { author = newAuthor; }
void Book::setGenre(string_view newGenre) { genre = newGenre; }
void Book::setPageCount(int newPageCount) { pageCount = newPageCount; }

string Book::getType() const { return "Книга"; }

int Book::getLoanDays() const {
    if (pageCount > 500) {
        return 21;
    } else {
        return 14;
    }
}

double Book::calcOverdueFine(int daysLate) const {
    const double FINE_PER_DAY = 0.10;
    if (daysLate <= 0) return 0.0;
    return daysLate * FINE_PER_DAY;
}

double Book::calcLossCompensation() const {
    const double BASE_COST = 5.0;
    const double COST_PER_PAGE = 0.02;
    return BASE_COST + pageCount * COST_PER_PAGE;
}

void Book::printInfo(ostream& out) const {
    LibraryItem::printInfo(out);
    out << "Автор: " << author << "\n";
    out << "Жанр: " << genre << "\n";
    out << "Страниц: " << pageCount << "\n";
}

bool Book::canFinishInLoanPeriod(int pagesPerDay) const {
    if (pagesPerDay <= 0) return false;
    return pageCount <= pagesPerDay * getLoanDays();
}

bool sameAuthor(const Book& a, const Book& b) {
    return a.author == b.author;
}
