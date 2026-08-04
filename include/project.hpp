#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

using namespace std;

const int MAX_SCORES = 10;
const int MAX_ROSTER_ENTRIES = 20;
const int MAX_MATCH_ROWS = 100;
const double MAX_SCORE = 1000.0;

const double RADIANT_MINIMUM = 300.0;
const double IMMORTAL_MINIMUM = 260.0;
const double DIAMOND_MINIMUM = 220.0;
const double GOLD_MINIMUM = 180.0;

const int MIN_MATCH_NUMBER = 1;
const int MAX_MATCH_NUMBER = 30;

struct RosterEntry {
    string riotId;
    string agent;
    double combatScore;
};

class ScoreList {
private:
    double scores[MAX_SCORES];
    int count;

public:
    ScoreList();
    bool addScore(double score);
    int getCount() const;
    double getScoreAt(int index) const;
    double getTotal() const;
    double getAverage() const;
    int findScore(double target) const;
    void sortDescending();
    static bool isValidScore(double score);
};

class Player {
private:
    string riotId;
    string agent;
    ScoreList scoreList;

public:
    Player();
    Player(string playerRiotId, string mainAgent);
    string getRiotId() const;
    string getAgent() const;
    bool addScore(double score);     
    void sortScores();
    ScoreList& getScoreList();
    const ScoreList& getScoreList() const;
    double getAverage() const;
    string getRank() const;
    static bool isValidRiotId(string riotId);
    static string determineRank(double average);
};

class UpcomingMatch {
private:
    string opponent;
    string mapName;
    int matchNumber;

public:
    UpcomingMatch();
    UpcomingMatch(string opponentName, string map, int number);
    string getOpponent() const;
    string getMapName() const;
    int getMatchNumber() const;
    static bool isValidMatchNumber(int number);
};

struct MatchNode {
    UpcomingMatch data;
    MatchNode* next;

    MatchNode(UpcomingMatch match);
};

class MatchQueue {
private:
    MatchNode* head;

public:
    MatchQueue();
    ~MatchQueue();
    bool insertByNumber(UpcomingMatch match);
    bool removeMatch(string opponentName);
    int countMatches() const;
    MatchNode* findMatch(string opponentName);
    const MatchNode* findMatch(string opponentName) const;
    const MatchNode* getHead() const;
    void clear();
    bool isEmpty() const;
};

class RosterReport {
public:
    static int readRosterFile(string filename, RosterEntry entries[], int maxEntries);
    static int buildRoster(const RosterEntry entries[], int entryCount,
                           Player players[], int maxPlayers);
    static bool writeRosterReport(string filename, const Player players[], int count);
    static double calculateTeamAverage(const Player players[], int count);
    static int findEntryByRiotId(const Player players[], int count, string riotId);
    static int findTopFraggerIndex(const Player players[], int count);
    static void sortByAverage(Player players[], int count);
};

bool isValidMenuChoice(int choice);
void printMenu();
void printPlayer(const Player& player);
int readMenuChoice();

#endif