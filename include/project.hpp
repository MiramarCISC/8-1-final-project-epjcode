#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

using namespace std;

const int MAX_SCORES = 10;
const int MAX_ROSTER_ENTRIES = 20;

const double MIN_SCORE = 0.0;
const double MAX_SCORE = 1000.0;

const double RADIANT_MINIMUM = 300.0;
const double IMMORTAL_MINIMUM = 260.0;
const double DIAMOND_MINIMUM = 220.0;
const double GOLD_MINIMUM = 180.0;

const int MIN_TIER = 1;
const int MAX_TIER = 5;

struct RosterEntry {
    string riotId;
    string agent;
    int matchesPlayed;
    double totalCombatScore;
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
    ScoreList& getScoreList();
    const ScoreList& getScoreList() const;
    double getAverage() const;
    string getRank() const;
    static bool isValidRiotId(string riotId);
    static string determineRank(double average);
};

class Achievement {
private:
    string label;
    int tier;
    bool disputed;

public:
    Achievement();
    Achievement(string achievementLabel, int achievementTier);
    string getLabel() const;
    int getTier() const;
    bool isDisputed() const;
    void markDisputed();
    static bool isValidTier(int tier);
};

struct AchievementNode {
    Achievement data;
    AchievementNode* next;

    AchievementNode(Achievement achievement);
};

class AchievementList {
private:
    AchievementNode* head;

public:
    AchievementList();
    ~AchievementList();
    bool insertByTier(Achievement achievement);     
    int countAchievements() const;
    AchievementNode* findAchievement(string label);
    const AchievementNode* findAchievement(string label) const;
    bool removeAchievement(string label);          
    const AchievementNode* getHead() const;     
    void clear();
    bool isEmpty() const;
};

class RosterReport {
public:
    static bool isValidMatchCount(int matchesPlayed);
    static bool isValidTotalScore(double totalCombatScore);
    static double calculateAverageScore(const RosterEntry& entry);
    static int readRosterFile(string filename, RosterEntry entries[], int maxEntries);
    static bool writeRosterReport(string filename, const RosterEntry entries[], int count);
    static double calculateTeamAverage(const RosterEntry entries[], int count);
    static int findEntryByRiotId(const RosterEntry entries[], int count, string riotId);
    static int findTopFraggerIndex(const RosterEntry entries[], int count);
};

bool isValidMenuChoice(int choice);
void printMenu();
void printPlayer(const Player& player);
int readMenuChoice();

#endif