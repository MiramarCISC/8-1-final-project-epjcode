# Valorant Scoreboard Tracker - CISC 192 Final Project

## Overview

This repository contains a fully working Valorant tracker that manages players,
combat scores, ranks, and the team's upcoming match schedule. The program reads a
match file, groups the rows into `Player` objects, and lets the user look up a
player, edit the upcoming match schedule, and write a roster report as a file.

## Compile

```bash
make
```

## Run

```bash
./main
```

## Test

```bash
make test
```

## Clean Build Files

```bash
make clean
```

## Course Topics Integrated and Tested

1. Week 1 Program Basics
   - Code location: `src/project.cpp` (`ScoreList::getTotal()`, `ScoreList::getAverage()`, `printPlayer()`, `printMenu()`)
   - Test location: `tests/test_project.cpp` (`testProgramBasicsAverageCalculation()`)

2. Week 2 Decisions and Loops
   - Code location: `src/main.cpp` (menu `do/while`) and `src/project.cpp` (`readMenuChoice()` loop, `isValidMenuChoice()`, `ScoreList::isValidScore()`, `UpcomingMatch::isValidMatchNumber()`, `Player::determineRank()`)
   - Test location: `tests/test_project.cpp` (`testDecisionsAndValidation()`)

3. Week 3 Functions and Program Design
   - Code location: `src/project.cpp` (`Player::addScore()`, `Player::sortScores()`, `Player::getAverage()`, `Player::getRank()`, `Player::getScoreList()`)
   - Test location: `tests/test_project.cpp` (`testPlayerInstanceMethodsReturnValues()`)

4. Week 4 Arrays, Searching, and Sorting
   - Code location: `src/project.cpp` (`ScoreList::findScore()`, `ScoreList::sortDescending()`, `ScoreList::getScoreAt()`, `RosterReport::findEntryByRiotId()`, `RosterReport::findTopFraggerIndex()`, `RosterReport::sortByAverage()`)
   - Test location: `tests/test_project.cpp` (`testArraySearchAndSort()`)

5. Week 5 Strings and Structures
   - Code location: `include/project.hpp` (`RosterEntry`) and `src/project.cpp` (`Player::isValidRiotId()`)
   - Test location: `tests/test_project.cpp` (`testStringsAndStructuresRosterEntry()`)

6. Week 6 Pointers, Dynamic Memory, and Linked Lists
   - Code location: `src/project.cpp` (`MatchNode`, `MatchQueue::insertByNumber()`, `MatchQueue::findMatch()`, `MatchQueue::removeMatch()`, `MatchQueue::clear()`)
   - Test location: `tests/test_project.cpp` (`testLinkedMatchQueueInsertSearchAndCleanup()`)

7. Week 7 File I/O and Integration
   - Code location: `src/project.cpp` (`RosterReport::readRosterFile()`, `RosterReport::buildRoster()`, `RosterReport::writeRosterReport()`)
   - Test location: `tests/test_project.cpp` (`testFileBasedRosterLoadAndAverage()`)
   - Files: `data/matches.txt`

## Final Submission Checklist

- [X] My project compiles with `make`.
- [X] My project runs with `./main`.
- [X] My tests run with `make test`.
- [X] I deleted or replaced the sample project code.
- [X] My project uses class names that are nouns from my own project.
- [X] My project integrates all 7 course topics in reachable code.
- [X] My project includes at least one unit test per course topic.
- [X] My README explains where each topic appears.
- [X] My README explains which test verifies each topic.
- [X] My code is committed and pushed to GitHub Classroom.