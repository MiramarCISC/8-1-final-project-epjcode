# Valorant Scoreboard Tracker - CISC 192 Final Project

## Overview

This repository contains a fully working Valorant tracker that manages players, ranks, and notable achievements. This program takes a roster file as input and allows users to search for players, receive a roster report, and edit achievements.

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
   - Code location: `include/project.hpp` (rank cutoffs and array-size constants) and `src/project.cpp` (`ScoreList::getTotal()`, `ScoreList::getAverage()`, `printMenu()`)
   - Test location: `tests/test_project.cpp` (`testWeek1ProgramBasics()`)

2. Week 2 Decisions and Loops
   - Code location: `src/main.cpp` (menu `do/while` loop) and `src/project.cpp` (`readMenuChoice()` loop, `isValidMenuChoice()`, `ScoreList::isValidScore()`, `Achievement::isValidTier()`, `Player::determineRank()`)
   - Test location: `tests/test_project.cpp` (`testWeek2DecisionsAndLoops()`)

3. Week 3 Functions and Program Design
   - Code location: `src/project.cpp` (`RosterReport::calculateAverageScore()`, `ScoreList::getTotal()`, `Player`)
   - Test location: `tests/test_project.cpp` (`testWeek3FunctionsAndProgramDesign()`)

4. Week 4 Arrays, Searching, and Sorting
   - Code location: `src/project.cpp` (`ScoreList::findScore()`, `ScoreList::sortDescending()`, `ScoreList::getScoreAt()`, `RosterReport::findEntryByRiotId()`, `RosterReport::findTopFraggerIndex()`)
   - Test location: `tests/test_project.cpp` (`testWeek4ArraysSearchingSorting()`)

5. Week 5 Strings and Structures
   - Code location: `include/project.hpp` (`RosterEntry`) and `src/project.cpp` (`Player::isValidRiotId()`)
   - Test location: `tests/test_project.cpp` (`testWeek5StringsAndStructures()`)

6. Week 6 Pointers, Dynamic Memory, and Linked Lists
   - Code location: `src/project.cpp` (`AchievementNode`, `AchievementList::insertByTier()`, `AchievementList::findAchievement()`, `AchievementList::removeAchievement()`, `AchievementList::clear()`)
   - Test location: `tests/test_project.cpp` (`testWeek6SimpleLinkedAchievementList()`)

7. Week 7 File I/O and Integration
   - Code location: `src/project.cpp` (`RosterReport::readRosterFile()`, `RosterReport::writeRosterReport()`)
   - Test location: `tests/test_project.cpp` (`testWeek7FileBasedRosterReport()`)
   - Files: `data/roster.txt`


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
