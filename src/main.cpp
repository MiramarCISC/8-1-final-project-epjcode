#include "project.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    RosterEntry entries[MAX_MATCH_ROWS];
    MatchQueue schedule;
    Player roster[MAX_ROSTER_ENTRIES];
    int choice = -1;

    cout << "Valorant Scoreboard Tracker" << endl;
    cout << "Tracks players, combat scores, ranks, and upcoming matches." << endl;

    int entryCount = RosterReport::readRosterFile(
        "data/matches.txt",
        entries,
        MAX_MATCH_ROWS
    );
    int playerCount = RosterReport::buildRoster(
        entries,
        entryCount,
        roster,
        MAX_ROSTER_ENTRIES
    );

    cout << "Loaded " << entryCount << " match row(s) into "
         << playerCount << " player(s)." << endl;

    do {
        printMenu();
        choice = readMenuChoice();

      
        switch (choice) {
            case 1: {
                string riotId = "";
                cout << "Riot ID to look up: ";
                cin >> riotId;

                int index = RosterReport::findEntryByRiotId(roster, playerCount, riotId);

                if (index == -1) {
                    cout << riotId << " is not on the roster." << endl;
                    break;
                }

                roster[index].sortScores();
                printPlayer(roster[index]);

                cout << "  Scores:";

                for (int i = 0; i < roster[index].getScoreList().getCount(); i++) {
                    cout << " " << roster[index].getScoreList().getScoreAt(i);
                }

                cout << endl;

                break;
            }
            case 2: {
                int action = -1;

                do {
                    cout << endl << "Upcoming matches ("
                         << schedule.countMatches() << " scheduled)" << endl;

                    if (schedule.isEmpty()) {
                        cout << "  (none yet)" << endl;
                    }

                    for (const MatchNode* node = schedule.getHead();
                         node != nullptr; node = node->next) {
                        cout << "  Match " << node->data.getMatchNumber()
                             << ": vs " << node->data.getOpponent()
                             << " on " << node->data.getMapName() << endl;
                    }

                    cout << "1. Add a match" << endl;
                    cout << "2. Delete a match" << endl;
                    cout << "0. Back to the main menu" << endl;
                    cout << "Choice: ";
                    cin >> action;

                    while (!cin || action < 0 || action > 2) {
                        if (cin.eof()) {
                            action = 0;
                            break;
                        }

                        cout << "Invalid choice. Enter 0-2: ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cin >> action;
                    }

                    if (action == 1) {
                        string opponent = "";
                        string mapName = "";
                        int number = 0;

                        cout << "Opponent: ";
                        getline(cin >> ws, opponent);
                        cout << "Map: ";
                        cin >> mapName;
                        cout << "Match number (1-30): ";
                        cin >> number;

                        if (schedule.insertByNumber(UpcomingMatch(opponent, mapName, number))) {
                            cout << "Added." << endl;
                        } 
                    } 
                    else if (action == 2) {
                        string opponent = "";
                        cout << "Opponent to delete: ";
                        getline(cin >> ws, opponent);

                        if (schedule.removeMatch(opponent)) {
                            cout << "Deleted." << endl;
                        } 
                        else {
                            cout << "No match against that opponent." << endl;
                        }
                    }
                } 
                while (action != 0);

                break;
            }

            case 3: {
                RosterReport::sortByAverage(roster, playerCount);

                cout << fixed << setprecision(1);
                cout << "Read " << playerCount << " player(s)." << endl;

                for (int i = 0; i < playerCount; i++) {
                    printPlayer(roster[i]);
                }

                cout << "Team average combat score: "
                     << RosterReport::calculateTeamAverage(roster, playerCount)
                     << endl;

                int top = RosterReport::findTopFraggerIndex(roster, playerCount);

                if (top != -1) {
                    cout << "Top fragger: " << roster[top].getRiotId() << " ("
                         << roster[top].getAverage() << ", "
                         << roster[top].getRank() << ")" << endl;
                }

                if (RosterReport::writeRosterReport(
                        "roster_report.txt",
                        roster,
                        playerCount
                    )) {
                    cout << "Report written to roster_report.txt" << endl;
                }

                break;
            }

            case 4:
                cout << fixed << setprecision(0);
                cout << "Rank is set by average combat score:" << endl;
                cout << "  Radiant  " << RADIANT_MINIMUM << " and above" << endl;
                cout << "  Immortal " << IMMORTAL_MINIMUM << " to " << RADIANT_MINIMUM - 1 << endl;
                cout << "  Diamond  " << DIAMOND_MINIMUM << " to " << IMMORTAL_MINIMUM - 1 << endl;
                cout << "  Gold     " << GOLD_MINIMUM << " to " << DIAMOND_MINIMUM - 1 << endl;
                cout << "  Iron     below " << GOLD_MINIMUM << endl;
                break;

            case 0:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Unexpected choice." << endl;
                break;
        }

    } while (choice != 0);

    return 0;
}