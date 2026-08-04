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
    cout << "1. Look up a player" << endl;
    cout << "2. Show, add, or delete an upcoming match" << endl;
    cout << "3. Show the scoreboard and write a report" << endl;
    cout << "4. Show the rank scale" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}
 

void printPlayer(const Player& player) {
    cout << fixed << setprecision(1);
    cout << player.getRiotId() << " "
         << player.getAgent() << " "
         << "Matches: " << player.getScoreList().getCount() << " "
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

    for (int i = 0; i < MAX_SCORES; i++) {
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

bool Player::addScore(double score) {
    return scoreList.addScore(score);
}

void Player::sortScores() {
    scoreList.sortDescending();
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

UpcomingMatch::UpcomingMatch() {
    opponent = "";
    mapName = "";
    matchNumber = MIN_MATCH_NUMBER;
}

UpcomingMatch::UpcomingMatch(string opponentName, string map, int number) {
    opponent = opponentName;
    mapName = map;

    if (isValidMatchNumber(number)) {
        matchNumber = number;
    } else {
        matchNumber = MIN_MATCH_NUMBER;
    }
}

string UpcomingMatch::getOpponent() const {
    return opponent;
}

string UpcomingMatch::getMapName() const {
    return mapName;
}

int UpcomingMatch::getMatchNumber() const {
    return matchNumber;
}

bool UpcomingMatch::isValidMatchNumber(int number) {
    return number >= MIN_MATCH_NUMBER && number <= MAX_MATCH_NUMBER;
}

MatchNode::MatchNode(UpcomingMatch match) {
    data = match;
    next = nullptr;
}

MatchQueue::MatchQueue() {
    head = nullptr;
}

MatchQueue::~MatchQueue() {
    clear();
}


bool MatchQueue::insertByNumber(UpcomingMatch match) {
    if (match.getOpponent().length() == 0 ||
        findMatch(match.getOpponent()) != nullptr) {
        return false;
    }

    MatchNode* newNode = new MatchNode(match);

    if (head == nullptr || match.getMatchNumber() < head->data.getMatchNumber()) {
        newNode->next = head;
        head = newNode;
        return true;
    }

    MatchNode* current = head;

    while (current->next != nullptr &&
           current->next->data.getMatchNumber() <= match.getMatchNumber()) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return true;
}

bool MatchQueue::removeMatch(string opponentName) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getOpponent() == opponentName) {
        MatchNode* nodeToRemove = head;
        head = head->next;
        delete nodeToRemove;
        return true;
    }

    MatchNode* current = head;

    while (current->next != nullptr) {
        if (current->next->data.getOpponent() == opponentName) {
            MatchNode* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;
            return true;
        }

        current = current->next;
    }

    return false;
}

int MatchQueue::countMatches() const {
    int count = 0;
    const MatchNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

MatchNode* MatchQueue::findMatch(string opponentName) {
    MatchNode* current = head;

    while (current != nullptr) {
        if (current->data.getOpponent() == opponentName) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

const MatchNode* MatchQueue::findMatch(string opponentName) const {
    const MatchNode* current = head;

    while (current != nullptr) {
        if (current->data.getOpponent() == opponentName) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

const MatchNode* MatchQueue::getHead() const {
    return head;
}

void MatchQueue::clear() {
    MatchNode* current = head;

    while (current != nullptr) {
        MatchNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

bool MatchQueue::isEmpty() const {
    return head == nullptr;
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
           in >> entry.riotId >> entry.agent >> entry.combatScore) {
        if (Player::isValidRiotId(entry.riotId) &&
            ScoreList::isValidScore(entry.combatScore)) {
            entries[count] = entry;
            count++;
        }
    }

    return count;
}

int RosterReport::buildRoster(const RosterEntry entries[], int entryCount,
                             Player players[], int maxPlayers) {
    if (entries == nullptr || players == nullptr) {
        return 0;
    }

    int playerCount = 0;

    for (int i = 0; i < entryCount; i++) {
        int index = findEntryByRiotId(players, playerCount, entries[i].riotId);

        if (index == -1) {
            if (playerCount >= maxPlayers) {
                continue;
            }

            players[playerCount] = Player(entries[i].riotId, entries[i].agent);
            index = playerCount;
            playerCount++;
        }

        players[index].addScore(entries[i].combatScore);
    }

    return playerCount;
}

bool RosterReport::writeRosterReport(string filename, const Player players[], int count) {
    if (players == nullptr || count < 0) {
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
        out << players[i].getRiotId() << " "
            << players[i].getAgent() << " "
            << players[i].getScoreList().getCount() << " "
            << players[i].getScoreList().getTotal() << " "
            << players[i].getAverage() << " "
            << players[i].getRank() << endl;
    }

    out << "Team average combat score: "
        << calculateTeamAverage(players, count)
        << endl;

    return true;
}

double RosterReport::calculateTeamAverage(const Player players[], int count) {
    if (players == nullptr || count <= 0) {
        return 0.0;
    }

    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += players[i].getAverage();
    }

    return total / count;
}

int RosterReport::findEntryByRiotId(const Player players[], int count, string riotId) {
    if (players == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (players[i].getRiotId() == riotId) {
            return i;
        }
    }

    return -1;
}

int RosterReport::findTopFraggerIndex(const Player players[], int count) {
    if (players == nullptr || count <= 0) {
        return -1;
    }

    int topIndex = 0;

    for (int i = 1; i < count; i++) {
        if (players[i].getAverage() > players[topIndex].getAverage()) {
            topIndex = i;
        }
    }

    return topIndex;
}

void RosterReport::sortByAverage(Player players[], int count) {
    for (int start = 0; start < count - 1; start++) {
        int maxIndex = start;

        for (int i = start + 1; i < count; i++) {
            if (players[i].getAverage() > players[maxIndex].getAverage()) {
                maxIndex = i;
            }
        }

        Player temp = players[start];
        players[start] = players[maxIndex];
        players[maxIndex] = temp;
    }
}