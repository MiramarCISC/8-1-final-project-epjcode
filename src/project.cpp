#include "project.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidMenuChoice(int choice) {
    return choice >= 0 && choice <= 4;
}

 
void printMenu() {
    cout << endl;
    cout << "Valorant Scoreboard Tracker" << endl;
    cout << "1. Show a player's scores and rank" << endl;
    cout << "2. Show, add, or delete a notable achievement" << endl;
    cout << "3. Read the roster file and write a report" << endl;
    cout << "4. Show the rank scale" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}
 
void printPlayer(const Player& player) {
    cout << fixed << setprecision(1);
    cout << player.getRiotId() << " "
         << player.getAgent() << " "
         << "Average: " << player.getAverage() << " "
         << "Rank: " << player.getRank()
         << endl;
}

int readMenuChoice() {
    int choice = 0;
    while(true){
        if (cin >> choice && isValidMenuChoice(choice)) {
            return choice;
        }
 
        if (cin.eof()) {
            return 0;
        }
 
        cout << "Invalid choice.\n";
        cin.clear();
        cin.ignore(10000, '\n');

    }
}

ScoreList::ScoreList() {
    count = 0;

    for (int i = 0; i < 10; i++) {
        scores[i] = 0.0;
    }
}

bool ScoreList::addScore(double score) {
    if (!isValidScore(score) || count >= MAX_SCORES) {
        return false;
    }

    scores[count] = score;
    count++;

    return true;
}

int ScoreList::getCount() const {
    return count;
}

double ScoreList::getScoreAt(int index) const {
    if (index < 0 || index >= count) {
        return 0.0;
    }

    return scores[index];
}

double ScoreList::getTotal() const {
    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += scores[i];
    }

    return total;
}

double ScoreList::getAverage() const {
    if (count == 0) {
        return 0.0;
    }

    return getTotal() / count;
}

int ScoreList::findScore(double target) const {
    for (int i = 0; i < count; i++) {
        if (scores[i] == target) {
            return i;
        }
    }

    return -1;
}

void ScoreList::sortDescending() {
    for (int start = 0; start < count - 1; start++) {
        int maxIndex = start;

        for (int i = start + 1; i < count; i++) {
            if (scores[i] > scores[maxIndex]) {
                maxIndex = i;
            }
        }

        double temp = scores[start];
        scores[start] = scores[maxIndex];
        scores[maxIndex] = temp;
    }
}

bool ScoreList::isValidScore(double score) {
    return score >= 0.0 && score <= MAX_SCORE;
}

Player::Player() {
    riotId = "";
    agent = "";
}
 
Player::Player(string playerRiotId, string mainAgent) {
    riotId = playerRiotId;
    agent = mainAgent;
}

string Player::getRiotId() const {
    return riotId;
}
 
string Player::getAgent() const {
    return agent;
}
 
ScoreList& Player::getScoreList() {
    return scoreList;
}
 
const ScoreList& Player::getScoreList() const {
    return scoreList;
}

double Player::getAverage() const {
    return scoreList.getAverage();
}
 
string Player::getRank() const {
    return determineRank(getAverage());
}
 
bool Player::isValidRiotId(string riotId) {
    size_t hash = riotId.find('#');
 
    return hash != string::npos && hash > 0 && hash < riotId.length() - 1 &&
           riotId.find(' ') == string::npos;
}

string Player::determineRank(double average) {
    if (average >= RADIANT_MINIMUM) {
        return "Radiant";
    } else if (average >= IMMORTAL_MINIMUM) {
        return "Immortal";
    } else if (average >= DIAMOND_MINIMUM) {
        return "Diamond";
    } else if (average >= GOLD_MINIMUM) {
        return "Gold";
    } else {
        return "Iron";
    }
}

Achievement::Achievement() {
    label = "";
    tier = MIN_TIER;
    disputed = false;
}
 
Achievement::Achievement(string achievementLabel, int achievementTier) {
    label = achievementLabel;
 
    if (isValidTier(achievementTier)) {
        tier = achievementTier;
    } else {
        tier = MIN_TIER;
    }
 
    disputed = false;
}
 
string Achievement::getLabel() const {
    return label;
}
 
int Achievement::getTier() const {
    return tier;
}
 
bool Achievement::isDisputed() const {
    return disputed;
}
 
void Achievement::markDisputed() {
    disputed = true;
}
 
bool Achievement::isValidTier(int tier) {
    return tier >= MIN_TIER && tier <= MAX_TIER;
}
 
AchievementNode::AchievementNode(Achievement achievement) {
    data = achievement;
    next = nullptr;
}
 
AchievementList::AchievementList() {
    head = nullptr;
}
 
AchievementList::~AchievementList() {
    clear();
}

 
int AchievementList::countAchievements() const {
    int count = 0;
    const AchievementNode* current = head;
 
    while (current != nullptr) {
        count++;
        current = current->next;
    }
 
    return count;
}
 
AchievementNode* AchievementList::findAchievement(string label) {
    AchievementNode* current = head;
 
    while (current != nullptr) {
        if (current->data.getLabel() == label) {
            return current;
        }
 
        current = current->next;
    }
 
    return nullptr;
}
 
const AchievementNode* AchievementList::findAchievement(string label) const {
    const AchievementNode* current = head;
 
    while (current != nullptr) {
        if (current->data.getLabel() == label) {
            return current;
        }
 
        current = current->next;
    }
 
    return nullptr;
}
 
void AchievementList::clear() {
    AchievementNode* current = head;
 
    while (current != nullptr) {
        AchievementNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
 
    head = nullptr;
}
 
bool AchievementList::isEmpty() const {
    return head == nullptr;
}
// ===============================
// InventoryReport
// ===============================

bool RosterReport::isValidMatchCount(int matchesPlayed) {
    return matchesPlayed >= 0;
}
 
bool RosterReport::isValidTotalScore(double totalCombatScore) {
    return totalCombatScore >= 0.0;
}
 
double RosterReport::calculateAverageScore(const RosterEntry& entry) {
    if (!isValidMatchCount(entry.matchesPlayed) ||
        !isValidTotalScore(entry.totalCombatScore) ||
        entry.matchesPlayed == 0) {
        return 0.0;
    }
 
    return entry.totalCombatScore / entry.matchesPlayed;
}
 
int RosterReport::readRosterFile(string filename, RosterEntry entries[], int maxEntries) {
    if (entries == nullptr || maxEntries <= 0) {
        return 0;
    }
 
    ifstream in(filename);
 
    if (!in.is_open()) {
        return 0;
    }
 
    int count = 0;
    RosterEntry entry;
 
    while (count < maxEntries &&
           in >> entry.riotId >> entry.agent >> entry.matchesPlayed
              >> entry.totalCombatScore) {
        if (Player::isValidRiotId(entry.riotId) &&
            isValidMatchCount(entry.matchesPlayed) &&
            isValidTotalScore(entry.totalCombatScore)) {
            entries[count] = entry;
            count++;
        }
    }
 
    return count;
}
 
bool RosterReport::writeRosterReport(string filename, const RosterEntry entries[], int count) {
    if (entries == nullptr || count < 0) {
        return false;
    }
 
    ofstream out(filename);
 
    if (!out.is_open()) {
        return false;
    }
 
    out << fixed << setprecision(1);
    out << "Valorant Scoreboard Report" << endl;
    out << "RiotID Agent Matches Total Average Rank" << endl;
 
    for (int i = 0; i < count; i++) {
        out << entries[i].riotId << " "
            << entries[i].agent << " "
            << entries[i].matchesPlayed << " "
            << entries[i].totalCombatScore << " "
            << calculateAverageScore(entries[i]) << " "
            << Player::determineRank(calculateAverageScore(entries[i])) << endl;
    }
 
    out << "Team average combat score: "
        << calculateTeamAverage(entries, count)
        << endl;
 
    return true;
}
 
double RosterReport::calculateTeamAverage(const RosterEntry entries[], int count) {
    if (entries == nullptr || count <= 0) {
        return 0.0;
    }
 
    double total = 0.0;
 
    for (int i = 0; i < count; i++) {
        total += calculateAverageScore(entries[i]);
    }
 
    return total / count;
}
 
int RosterReport::findEntryByRiotId(const RosterEntry entries[], int count, string riotId) {
    if (entries == nullptr || count <= 0) {
        return -1;
    }
 
    for (int i = 0; i < count; i++) {
        if (entries[i].riotId == riotId) {
            return i;
        }
    }
 
    return -1;
}
 
int RosterReport::findTopFraggerIndex(const RosterEntry entries[], int count) {
    if (entries == nullptr || count <= 0) {
        return -1;
    }
 
    int topIndex = 0;
 
    for (int i = 1; i < count; i++) {
        if (calculateAverageScore(entries[i]) > calculateAverageScore(entries[topIndex])) {
            topIndex = i;
        }
    }
 
    return topIndex;
}

bool AchievementList::insertByTier(Achievement achievement) {
    if (achievement.getLabel().length() == 0 ||
        findAchievement(achievement.getLabel()) != nullptr) {
        return false;
    }

    AchievementNode* newNode = new AchievementNode(achievement);

    if (head == nullptr || achievement.getTier() > head->data.getTier()) {
        newNode->next = head;
        head = newNode;
        return true;
    }

    AchievementNode* current = head;

    while (current->next != nullptr &&
           current->next->data.getTier() >= achievement.getTier()) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return true;
}

bool AchievementList::removeAchievement(string label) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getLabel() == label) {
        AchievementNode* nodeToRemove = head;
        head = head->next;
        delete nodeToRemove;
        return true;
    }

    AchievementNode* current = head;

    while (current->next != nullptr) {
        if (current->next->data.getLabel() == label) {
            AchievementNode* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;
            return true;
        }

        current = current->next;
    }

    return false;
}

const AchievementNode* AchievementList::getHead() const {
    return head;
}
