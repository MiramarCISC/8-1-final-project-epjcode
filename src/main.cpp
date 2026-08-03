#include "project.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    AchievementList achievements;
    int choice = -1;

    cout << "Valorant Scoreboard Tracker" << endl;
    cout << "Tracks players, combat scores, ranks, and achievements." << endl;

    do {
        printMenu();
        choice = readMenuChoice();

      
        switch (choice) {
            case 1: {
                RosterEntry entries[MAX_ROSTER_ENTRIES];
                int count = RosterReport::readRosterFile(
                    "data/roster.txt",
                    entries,
                    MAX_ROSTER_ENTRIES
                );
 
                if (count == 0) {
                    cout << "Could not read data/roster.txt" << endl;
                    break;
                }
 
                string riotId = "";
                cout << "Riot ID to search for: ";
                cin >> riotId;
 
                int index = RosterReport::findEntryByRiotId(entries, count, riotId);
 
                if (index == -1) {
                    cout << riotId << " is not in the roster file." << endl;
                    break;
                }
 
                double average = RosterReport::calculateAverageScore(entries[index]);
 
                cout << fixed << setprecision(1);
                cout << "Found at entry " << index + 1 << " of " << count << endl;
                cout << "  Riot ID: " << entries[index].riotId << endl;
                cout << "  Agent:   " << entries[index].agent << endl;
                cout << "  Matches: " << entries[index].matchesPlayed << endl;
                cout << "  Total:   " << entries[index].totalCombatScore << endl;
                cout << "  Average: " << average << endl;
                cout << "  Rank:    " << Player::determineRank(average) << endl;
 
                break;
            }
            case 2: {
                int action = -1;
 
                do {
                    cout << endl << "Achievements ("
                         << achievements.countAchievements() << " recorded)" << endl;
 
                    if (achievements.isEmpty()) {
                        cout << "  (none yet)" << endl;
                    }
 
                    for (const AchievementNode* node = achievements.getHead();
                         node != nullptr; node = node->next) {
                        cout << "  [tier " << node->data.getTier() << "] "
                             << node->data.getLabel() << endl;
                    }
 
                    cout << "1. Add an achievement" << endl;
                    cout << "2. Delete an achievement" << endl;
                    cout << "0. Back to the main menu" << endl;
                    action = readMenuChoice();
 
                    if (action == 1) {
                        string label = "";
                        cout << "Achievement: ";
                        getline(cin >> ws, label);
 
                        int tier = 0;
                        cout << "Tier (1-5): ";
                        cin >> tier;
 
                        if (achievements.insertByTier(Achievement(label, tier))) {
                            cout << "Added." << endl;
                        } else {
                            cout << "That achievement is already recorded." << endl;
                        }
                    } else if (action == 2) {
                        string label = "";
                        cout << "Achievement to delete: ";
                        getline(cin >> ws, label);
 
                        if (achievements.removeAchievement(label)) {
                            cout << "Deleted." << endl;
                        } else {
                            cout << "No achievement with that label." << endl;
                        }
                    }
                } while (action != 0);
 
                break;
            }

            case 3: {
                RosterEntry entries[MAX_ROSTER_ENTRIES];
                int count = RosterReport::readRosterFile(
                    "data/roster.txt",
                    entries,
                    MAX_ROSTER_ENTRIES
                );

                cout << fixed << setprecision(1);
                cout << "Read " << count << " roster entr(ies)." << endl;
                cout << "Team average combat score: "
                     << RosterReport::calculateTeamAverage(entries, count)
                     << endl;
                int top = RosterReport::findTopFraggerIndex(entries, count);

                if (top != -1) {
                    cout << "Top fragger: " << entries[top].riotId << " ("
                         << RosterReport::calculateAverageScore(entries[top])
                         << ", "
                         << Player::determineRank(
                                RosterReport::calculateAverageScore(entries[top]))
                         << ")" << endl;
                }

                if (RosterReport::writeRosterReport(
                        "roster_report.txt",
                        entries,
                        count
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
