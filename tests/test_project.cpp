#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include "project.hpp"

using namespace std;

bool nearlyEqual(double actual, double expected, double tolerance = 0.0001) {
    return fabs(actual - expected) <= tolerance;
}

void testProgramBasicsAverageCalculation() {
    ScoreList scores;
    scores.addScore(280.0);
    scores.addScore(300.0);

    assert(scores.getCount() == 2);
    assert(nearlyEqual(scores.getTotal(), 580.0));
    assert(nearlyEqual(scores.getAverage(), 290.0));
}

void testDecisionsAndValidation() {
    assert(ScoreList::isValidScore(95.0) == true);
    assert(ScoreList::isValidScore(-1.0) == false);
    assert(ScoreList::isValidScore(MAX_SCORE + 1.0) == false);

    assert(isValidMenuChoice(0) == true);
    assert(isValidMenuChoice(5) == false);

    assert(Player::determineRank(RADIANT_MINIMUM) == "Radiant");
    assert(Player::determineRank(0.0) == "Iron");

    Player full("Fill#TST", "Neon");
    for (int i = 0; i < MAX_SCORES; i++) {
        assert(full.addScore(200.0) == true);
    }
    assert(full.addScore(200.0) == false);
}

void testPlayerInstanceMethodsReturnValues() {
    Player player("Ned#KR1", "Reyna");
    player.addScore(320.0);
    player.addScore(300.0);

    assert(player.getRiotId() == "Ned#KR1");
    assert(player.getAgent() == "Reyna");
    assert(nearlyEqual(player.getAverage(), 310.0));
    assert(player.getRank() == "Radiant");

    assert(player.addScore(-5.0) == false);
    player.sortScores();
    assert(nearlyEqual(player.getScoreList().getScoreAt(0), 320.0));
}

void testArraySearchAndSort() {
    ScoreList scores;
    scores.addScore(72.5);
    scores.addScore(288.0);
    scores.addScore(310.0);

    assert(scores.findScore(310.0) == 2);
    assert(scores.findScore(50.0) == -1);

    scores.sortDescending();

    assert(nearlyEqual(scores.getScoreAt(0), 310.0));
    assert(nearlyEqual(scores.getScoreAt(2), 72.5));
    assert(nearlyEqual(scores.getTotal(), 670.5));
}

void testStringsAndStructuresRosterEntry() {
    RosterEntry entry;
    entry.riotId = "Ned#KR1";
    entry.agent = "Reyna";
    entry.combatScore = 298.5;

    assert(entry.riotId == "Ned#KR1");
    assert(entry.agent == "Reyna");
    assert(nearlyEqual(entry.combatScore, 298.5));

    assert(Player::isValidRiotId(entry.riotId) == true);
    assert(Player::isValidRiotId("Ned") == false);
    assert(Player::isValidRiotId("Ned#") == false);
    assert(Player::isValidRiotId("two words#KR1") == false);
}

void testLinkedMatchQueueInsertSearchAndCleanup() {
    MatchQueue schedule;

    schedule.insertByNumber(UpcomingMatch("Sentinels", "Ascent", 5));
    schedule.insertByNumber(UpcomingMatch("LOUD", "Bind", 2));

    assert(schedule.countMatches() == 2);
    assert(schedule.getHead()->data.getOpponent() == "LOUD");
    assert(schedule.findMatch("Sentinels") != nullptr);
    assert(schedule.findMatch("missing") == nullptr);

    const MatchNode* firstMatch = schedule.getHead();
    const MatchNode* secondMatch = firstMatch->next;

    assert(firstMatch->data.getMatchNumber() == 2);
    assert(secondMatch->data.getMatchNumber() == 5);
    assert(secondMatch->next == nullptr);

    assert(schedule.insertByNumber(UpcomingMatch("", "Split", 4)) == false);

    assert(schedule.removeMatch("LOUD") == true);
    assert(schedule.countMatches() == 1);

    schedule.clear();
    assert(schedule.isEmpty() == true);
}

void testFileBasedRosterLoadAndAverage() {
    ofstream output("tests/resources/sample_matches.txt");
    output << "Ned#KR1 Reyna 300.0" << endl;
    output << "Peter#EUW Sova 200.0" << endl;
    output << "bad Reyna 250.0" << endl;
    output << "Ned#KR1 Reyna 360.0" << endl;
    output.close();

    RosterEntry entries[10];
    int entryCount = RosterReport::readRosterFile(
        "tests/resources/sample_matches.txt", entries, 10);

    assert(entryCount == 3);
    assert(entries[0].riotId == "Ned#KR1");
    assert(entries[1].agent == "Sova");
    assert(RosterReport::readRosterFile("tests/resources/missing.txt", entries, 10) == 0);

    Player roster[MAX_ROSTER_ENTRIES];
    int playerCount = RosterReport::buildRoster(entries, entryCount, roster,
                                                MAX_ROSTER_ENTRIES);

    assert(playerCount == 2);
    assert(nearlyEqual(roster[0].getAverage(), 330.0));
    assert(nearlyEqual(RosterReport::calculateTeamAverage(roster, playerCount), 265.0));

    assert(RosterReport::findEntryByRiotId(roster, playerCount, "Peter#EUW") == 1);
    assert(RosterReport::findEntryByRiotId(roster, playerCount, "missing#NA1") == -1);
    assert(RosterReport::findTopFraggerIndex(roster, playerCount) == 0);

    RosterReport::sortByAverage(roster, playerCount);
    assert(roster[0].getRiotId() == "Ned#KR1");

    assert(RosterReport::writeRosterReport(
               "tests/resources/sample_report.txt", roster, playerCount) == true);

    ifstream input("tests/resources/sample_report.txt");
    assert(input.is_open());

    string contents;
    string line;

    while (getline(input, line)) {
        contents += line + "\n";
    }
    input.close();

    assert(contents.find("Valorant Scoreboard Report") != string::npos);
    assert(contents.find("Ned#KR1") != string::npos);
    assert(contents.find("Team average combat score") != string::npos);
}

int main() {
    testProgramBasicsAverageCalculation();
    testDecisionsAndValidation();
    testPlayerInstanceMethodsReturnValues();
    testArraySearchAndSort();
    testStringsAndStructuresRosterEntry();
    testLinkedMatchQueueInsertSearchAndCleanup();
    testFileBasedRosterLoadAndAverage();

    cout << "All final project tests passed!" << endl;
    return 0;
}