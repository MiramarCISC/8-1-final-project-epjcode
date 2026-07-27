[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=24269665)
# CISC 192 Final Project Template

## Overview

This repository contains a fully working sample project that demonstrates the course skills from Weeks 1–7.

The sample code is provided only as an example. It is **not intended to be submitted unchanged**.

## Important Student Instructions

Before submitting your own final project, delete the sample project code and replace it with your own open-ended project.

The sample code demonstrates patterns you may reuse:

- Classes named as nouns from the project
- Header/source separation
- Unit tests
- Arrays, searching, and sorting
- Strings and structures/classes
- A simple linked task list
- A file-based inventory report
- Test resource files stored in `tests/resources/`

Do not submit the unchanged sample project as your final project.

## Correct Course Topics

Your final project is worth **7 points total**.

Each topic is worth **1 point**:

- **0.5 points** for integrating the topic into reachable project code
- **0.5 points** for at least one unit test for that topic

The seven required topics are:

1. Week 1 Program Basics
2. Week 2 Decisions and Loops
3. Week 3 Functions and Program Design
4. Week 4 Arrays, Searching, and Sorting
5. Week 5 Strings and Structures
6. Week 6 Pointers, Dynamic Memory, and Linked Lists
7. Week 7 File I/O and Integration

## Unreachable Code Rule

Separate unreachable code is not acceptable.

A topic only earns credit if it is part of your working project and can be reached through normal program execution, another project function/method, or an automated unit test.

## Build and Run

```bash
make
./main
```

## Run Tests

```bash
make test
```

## Clean Build Files

```bash
make clean
```

## Object-Oriented Sample Design

This sample uses noun-based classes from the sample project:

| Class | Purpose |
|---|---|
| `ScoreList` | Demonstrates arrays, searching, sorting, and arithmetic |
| `Student` | Demonstrates strings and custom record/class design |
| `Task` | Demonstrates a task record |
| `TaskNode` | Demonstrates linked list nodes |
| `TaskList` | Demonstrates a simple linked task list |
| `InventoryItem` | Demonstrates inventory records |
| `InventoryReport` | Demonstrates file-based inventory reporting |

## Sample Code Is Example Only

The sample code in this repository should be deleted or replaced before final submission.

Students may keep the project structure, Makefile, GitHub Actions workflow, and testing pattern, but the submitted project should reflect the student's own project idea.

## Required README Update

Before submitting your final project, update this README.md so it describes your own project.

```text
## Course Topics Integrated and Tested

1. Week 1 Program Basics
   - Code location:
   - Test location:

2. Week 2 Decisions and Loops
   - Code location:
   - Test location:

3. Week 3 Functions and Program Design
   - Code location:
   - Test location:

4. Week 4 Arrays, Searching, and Sorting
   - Code location:
   - Test location:

5. Week 5 Strings and Structures
   - Code location:
   - Test location:

6. Week 6 Pointers, Dynamic Memory, and Linked Lists
   - Code location:
   - Test location:

7. Week 7 File I/O and Integration
   - Code location:
   - Test location:
```

## Final Submission Checklist

- [ ] My project compiles with `make`.
- [ ] My project runs with `./main`.
- [ ] My tests run with `make test`.
- [ ] I deleted or replaced the sample project code.
- [ ] My project uses class names that are nouns from my own project.
- [ ] My project integrates all 7 course topics in reachable code.
- [ ] My project includes at least one unit test per course topic.
- [ ] My README explains where each topic appears.
- [ ] My README explains which test verifies each topic.
- [ ] My code is committed and pushed to GitHub Classroom.
