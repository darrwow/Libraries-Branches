#include "Newspaper.h"
using namespace std;

Newspaper::Newspaper(int paperId, const string& paperTitle, int paperYear,
                     int paperIssueNumber, int paperCirculation, const string& paperPublisher)
    : LibraryItem(paperId, paperTitle, paperYear),
      issueNumber(paperIssueNumber), circulation(paperCirculation), publisher(paperPublisher) {
}

int Newspaper::getIssueNumber() const { return issueNumber; }
int Newspaper::getCirculation() const { return circulation; }
string Newspaper::getPublisher() const { return publisher; }
void Newspaper::setIssueNumber(int newIssueNumber) { issueNumber = newIssueNumber; }
void Newspaper::setCirculation(int newCirculation) { circulation = newCirculation; }
void Newspaper::setPublisher(string_view newPublisher) { publisher = newPublisher; }

string Newspaper::getType() const { return "Газета"; }
int Newspaper::getLoanDays() const { return 3; }

double Newspaper::calcOverdueFine(int daysLate) const {
    const double FINE_PER_DAY = 0.05;
    if (daysLate <= 0) return 0.0;
    return daysLate * FINE_PER_DAY;
}

double Newspaper::calcLossCompensation() const {
    const double FIXED_COST = 1.0;
    return FIXED_COST;
}

void Newspaper::printInfo(ostream& out) const {
    LibraryItem::printInfo(out);
    out << "Номер выпуска: " << issueNumber << "\n";
    out << "Тираж: " << circulation << "\n";
    out << "Издатель: " << publisher << "\n";
}

bool Newspaper::canTakeHome(int currentYear) const {
    const int MIN_CIRCULATION = 700;
    const int MAX_AGE = 15;
    bool smallCirculation = circulation < MIN_CIRCULATION;
    bool tooOld = currentYear - getYear() > MAX_AGE;
    return !smallCirculation && !tooOld;
}

