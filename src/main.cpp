#include "project.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    int choice = -1;

    cout << "Valorant Scoreboard Tracker" << endl;
    cout << "Tracks players, combat scores, ranks, and achievements." << endl;

    do {
        printMenu();
        choice = readMenuChoice();

      
        switch (choice) {
            case 1: {
                Player player("Reyna#KR1", "Reyna");
                player.getScoreList().addScore(298.5);
                player.getScoreList().addScore(341.0);
                player.getScoreList().addScore(355.0);
                player.getScoreList().sortDescending();

                printplayer(Player));
                cout << "Score 341 found at index "
                     << student.getScoreList().findScore(341.0)
                     << endl;

                break;
            }

            case 2: {
                AchievementLIst achievements;
                achievements.insertFront(Achievement("Ace", 5));
                achievements.insertFront(Achievement("1v4 clutch", 4));
                achievements.markAchievementDisputed("1v4 clutch");
                
                cout << "Achievement count: "
                     << achievements.countAchievements() << endl;
                cout << "Removed deleted achievements: "
                     << achievements.removeDeletedAchievements()
                     << endl;
                cout << "Remaining achievement count: "
                     << achievements.countAchievements() << endl;

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
