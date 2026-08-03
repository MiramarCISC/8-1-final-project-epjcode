#include "project.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool nearlyEqual(double actual, double expected, double tolerance = 0.0001) {
    return fabs(actual - expected) <= tolerance;
}

void createTestRosterFile(string filename) {
    ofstream out(filename);
 
    assert(out.is_open());
 
    out << "Ned#KR1 Reyna 3 900.0" << endl;
    out << "Peter#EUW Sova 4 800.0" << endl;
    out << "MJ#BR1 Sage 2 300.0" << endl;
 
    out.close();
}

// Week 1: Program Basics
void testWeek1ProgramBasics() {
    ScoreList scores;
    scores.addScore(280.0);
    scores.addScore(300.0);
 
    double average = scores.getAverage();
 
    assert(nearlyEqual(scores.getTotal(), 580.0));
    assert(nearlyEqual(average, 290.0));
    assert(scores.getCount() == 2);
 
    ScoreList empty;
    assert(nearlyEqual(empty.getAverage(), 0.0));
 
    assert(Player::determineRank(RADIANT_MINIMUM) == "Radiant");
    assert(Player::determineRank(GOLD_MINIMUM) == "Gold");
}

// Week 2: Decisions and Loops
void testWeek2DecisionsAndLoops() {
    assert(ScoreList::isValidScore(0.0));
    assert(ScoreList::isValidScore(MAX_SCORE));
    assert(!ScoreList::isValidScore(-1.0));
    assert(!ScoreList::isValidScore(MAX_SCORE + 1.0));
 
    assert(Achievement::isValidTier(MIN_TIER));
    assert(Achievement::isValidTier(MAX_TIER));
    assert(!Achievement::isValidTier(MIN_TIER - 1));
    assert(!Achievement::isValidTier(MAX_TIER + 1));
 
    assert(isValidMenuChoice(0));
    assert(isValidMenuChoice(4));
    assert(!isValidMenuChoice(5));
    assert(!isValidMenuChoice(-1));
 
    assert(Player::determineRank(RADIANT_MINIMUM) == "Radiant");
    assert(Player::determineRank(IMMORTAL_MINIMUM) == "Immortal");
    assert(Player::determineRank(DIAMOND_MINIMUM) == "Diamond");
    assert(Player::determineRank(GOLD_MINIMUM) == "Gold");
    assert(Player::determineRank(0.0) == "Iron");
}

// Week 3: Functions and Program Design
void testWeek3FunctionsAndProgramDesign() {
    ScoreList scores;
    scores.addScore(240.0);
    scores.addScore(260.0);
    scores.addScore(280.0);
 
    assert(nearlyEqual(scores.getTotal(), 780.0));
    assert(nearlyEqual(scores.getAverage(), 260.0));
 
    Player player("Ned#KR1", "Reyna");
    assert(player.getRiotId() == "Ned#KR1");
    assert(player.getAgent() == "Reyna");
}

// Week 4: Arrays, Searching, and Sorting
void testWeek4ArraysSearchingSorting() {
    ScoreList scores;
    scores.addScore(288.0);
    scores.addScore(172.5);
    scores.addScore(310.0);
    scores.addScore(291.0);
 
    assert(scores.findScore(310.0) == 2);
    assert(scores.findScore(50.0) == -1);
 
    assert(nearlyEqual(scores.getScoreAt(-1), 0.0));
    assert(nearlyEqual(scores.getScoreAt(99), 0.0));
 
    scores.sortDescending();
 
    assert(nearlyEqual(scores.getScoreAt(0), 310.0));
    assert(nearlyEqual(scores.getScoreAt(1), 291.0));
    assert(nearlyEqual(scores.getScoreAt(2), 288.0));
    assert(nearlyEqual(scores.getScoreAt(3), 172.5));
    RosterEntry entries[3];
    entries[0] = {"MJ#BR1", "Sage", 2, 300.0};
    entries[1] = {"Ned#KR1", "Reyna", 3, 900.0};
    entries[2] = {"Peter#EUW", "Sova", 4, 800.0};
    assert(RosterReport::findEntryByRiotId(entries, 3, "Ned#KR1") == 1);
    assert(RosterReport::findEntryByRiotId(entries, 3, "asdasd#NA1") == -1);
    assert(RosterReport::findTopFraggerIndex(entries, 3) == 1);
    assert(RosterReport::findTopFraggerIndex(entries, 0) == -1);
}

// Week 5: Strings and Structures
void testWeek5StringsAndStructures() {
    Player player("Ned#KR1", "Reyna");
 
    assert(Player::isValidRiotId("Ned#KR1"));
    assert(!Player::isValidRiotId("Ned"));
    assert(!Player::isValidRiotId("#KR1"));
 
    assert(player.getRiotId() == "Ned#KR1");
    assert(player.getRiotId().length() == 7);
    assert(player.getRiotId().find('#') == 3);
 
    RosterEntry entry = {"Peter#EUW", "Sova", 4, 800.0};
    assert(entry.riotId == "Peter#EUW");
    assert(entry.agent == "Sova");
    assert(entry.matchesPlayed == 4);
    assert(nearlyEqual(entry.totalCombatScore, 800.0));
}

// Week 6: Simple Linked Achievement List
void testWeek6SimpleLinkedAchievementList() {
    AchievementList achievements;
 
    assert(achievements.isEmpty());
    assert(achievements.countAchievements() == 0);
    assert(achievements.getHead() == nullptr);
 
    assert(achievements.insertByTier(Achievement("wall on B main", 2)));
    assert(achievements.insertByTier(Achievement("ace on Ascent", 5)));
    assert(achievements.insertByTier(Achievement("1v4 clutch", 4)));
 
    assert(!achievements.isEmpty());
    assert(achievements.countAchievements() == 3);
}

// Week 7: File-Based Roster Report
void testWeek7FileBasedRosterReport() {
    string inputFilename = "tests/resources/test_roster_input.txt";
    string outputFilename = "tests/resources/test_roster_report_output.txt";
 
    createTestRosterFile(inputFilename);
 
    RosterEntry entries[10];
    int count = RosterReport::readRosterFile(inputFilename, entries, 10);
 
    assert(count == 3);
    assert(entries[0].riotId == "Ned#KR1");
    assert(entries[0].agent == "Reyna");
    assert(entries[0].matchesPlayed == 3);
    assert(entries[2].agent == "Sage");
 
    assert(RosterReport::readRosterFile("tests/resources/missing.txt", entries, 10) == 0);
    assert(RosterReport::readRosterFile(inputFilename, entries, 2) == 2);
 
    count = RosterReport::readRosterFile(inputFilename, entries, 10);
 
    bool wroteReport = RosterReport::writeRosterReport(outputFilename, entries, count);
    assert(wroteReport);
 
    ifstream in(outputFilename);
    assert(in.is_open());
 
    string contents;
    string line;
 
    while (getline(in, line)) {
        contents += line + "\n";
    }
 
    assert(contents.find("Valorant Scoreboard Report") != string::npos);
    assert(contents.find("Ned#KR1") != string::npos);
    assert(contents.find("Team average combat score") != string::npos);
}

int main() {
    testWeek1ProgramBasics();
    testWeek2DecisionsAndLoops();
    testWeek3FunctionsAndProgramDesign();
    testWeek4ArraysSearchingSorting();
    testWeek5StringsAndStructures();
    testWeek6SimpleLinkedAchievementList();
    testWeek7FileBasedRosterReport();

    cout << "All corrected final project template tests passed!" << endl;
    return 0;
}
