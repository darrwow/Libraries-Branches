#pragma once
#include "LibraryItem.h"

class Magazine : public LibraryItem {
private:
    std::string topic;
    int issueNumber;
    std::string targetAudience;

public:
    Magazine(int magId, const std::string& magTitle, int magYear,
             const std::string& magTopic, int magIssueNumber, const std::string& magTargetAudience);
    ~Magazine() override = default;

    std::string getTopic() const;
    int getIssueNumber() const;
    std::string getTargetAudience() const;
    void setTopic(std::string_view newTopic);
    void setIssueNumber(int newIssueNumber);
    void setTargetAudience(std::string_view newTargetAudience);

    std::string getType() const override;
    int getLoanDays() const override;
    double calcOverdueFine(int daysLate) const override;
    double calcLossCompensation() const override;
    void printInfo(std::ostream& out) const override;
    bool suitableFor(std::string_view audience) const;
};

