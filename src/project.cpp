#include "project.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// ===============================
// ScoreList
// ===============================

ScoreList::ScoreList() {
    count = 0;

    for (int i = 0; i < 10; i++) {
        scores[i] = 0.0;
    }
}

bool ScoreList::addScore(double score) {
    if (!isValidScore(score) || count >= 10) {
        return false;
    }

    scores[count] = score;
    count++;

    return true;
}

int ScoreList::getCount() const {
    return count;
}

double ScoreList::getScoreAt(int index) const {
    if (index < 0 || index >= count) {
        return 0.0;
    }

    return scores[index];
}

double ScoreList::getTotal() const {
    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += scores[i];
    }

    return total;
}

double ScoreList::getAverage() const {
    if (count == 0) {
        return 0.0;
    }

    return getTotal() / count;
}

int ScoreList::findScore(double target) const {
    for (int i = 0; i < count; i++) {
        if (scores[i] == target) {
            return i;
        }
    }

    return -1;
}

void ScoreList::sortAscending() {
    for (int start = 0; start < count - 1; start++) {
        int minIndex = start;

        for (int i = start + 1; i < count; i++) {
            if (scores[i] < scores[minIndex]) {
                minIndex = i;
            }
        }

        double temp = scores[start];
        scores[start] = scores[minIndex];
        scores[minIndex] = temp;
    }
}

bool ScoreList::isValidScore(double score) {
    return score >= 0.0 && score <= 100.0;
}

// ===============================
// Student
// ===============================

Player::Player() {
    riotId = "";
    agent = "";
}
 
Player::Player(string playerRiotId, string mainAgent) {
    riotId = playerRiotId;
    agent = mainAgent;
}

string Player::getRiotId() const {
    return riotId;
}
 
string Player::getAgent() const {
    return agent;
}
 
ScoreList& Player::getScoreList() {
    return scoreList;
}
 
const ScoreList& Player::getScoreList() const {
    return scoreList;
}

double Student::getAverage() const {
    return scoreList.getAverage();
}

char Student::getLetterGrade() const {
    return determineLetterGrade(getAverage());
}

bool Student::isValidId(string id) {
    return id.length() >= 3 && id[0] >= 'A' && id[0] <= 'Z';
}

char Student::determineLetterGrade(double average) {
    if (average >= A_MINIMUM) {
        return 'A';
    } else if (average >= B_MINIMUM) {
        return 'B';
    } else if (average >= C_MINIMUM) {
        return 'C';
    } else if (average >= D_MINIMUM) {
        return 'D';
    } else {
        return 'F';
    }
}

// ===============================
// Task and TaskList
// ===============================

Task::Task() {
    description = "";
    priority = 1;
    completed = false;
}

Task::Task(string taskDescription, int taskPriority) {
    description = taskDescription;

    if (isValidPriority(taskPriority)) {
        priority = taskPriority;
    } else {
        priority = 1;
    }

    completed = false;
}

string Task::getDescription() const {
    return description;
}

int Task::getPriority() const {
    return priority;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::markComplete() {
    completed = true;
}

bool Task::isValidPriority(int priority) {
    return priority >= 1 && priority <= 5;
}

TaskNode::TaskNode(Task task) {
    data = task;
    next = nullptr;
}

TaskList::TaskList() {
    head = nullptr;
}

TaskList::~TaskList() {
    clear();
}

void TaskList::insertFront(Task task) {
    TaskNode* newNode = new TaskNode(task);
    newNode->next = head;
    head = newNode;
}

int TaskList::countTasks() const {
    int count = 0;
    const TaskNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

TaskNode* TaskList::findTask(string description) {
    TaskNode* current = head;

    while (current != nullptr) {
        if (current->data.getDescription() == description) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

const TaskNode* TaskList::findTask(string description) const {
    const TaskNode* current = head;

    while (current != nullptr) {
        if (current->data.getDescription() == description) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool TaskList::markTaskComplete(string description) {
    TaskNode* found = findTask(description);

    if (found == nullptr) {
        return false;
    }

    found->data.markComplete();
    return true;
}

int TaskList::removeCompletedTasks() {
    int removed = 0;

    while (head != nullptr && head->data.isCompleted()) {
        TaskNode* nodeToRemove = head;
        head = head->next;
        delete nodeToRemove;
        removed++;
    }

    TaskNode* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->next->data.isCompleted()) {
            TaskNode* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;
            removed++;
        } else {
            current = current->next;
        }
    }

    return removed;
}

void TaskList::clear() {
    TaskNode* current = head;

    while (current != nullptr) {
        TaskNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

bool TaskList::isEmpty() const {
    return head == nullptr;
}

// ===============================
// InventoryReport
// ===============================

bool InventoryReport::isValidQuantity(int quantity) {
    return quantity >= 0;
}

bool InventoryReport::isValidPrice(double price) {
    return price >= 0.0;
}

double InventoryReport::calculateItemValue(const InventoryItem& item) {
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) {
        return 0.0;
    }

    return item.quantity * item.price;
}

int InventoryReport::readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    if (items == nullptr || maxItems <= 0) {
        return 0;
    }

    ifstream in(filename);

    if (!in.is_open()) {
        return 0;
    }

    int count = 0;
    InventoryItem item;

    while (count < maxItems &&
           in >> item.sku >> item.name >> item.quantity >> item.price) {
        if (isValidQuantity(item.quantity) && isValidPrice(item.price)) {
            items[count] = item;
            count++;
        }
    }

    return count;
}

bool InventoryReport::writeInventoryReport(string filename, const InventoryItem items[], int count) {
    if (items == nullptr || count < 0) {
        return false;
    }

    ofstream out(filename);

    if (!out.is_open()) {
        return false;
    }

    out << fixed << setprecision(2);
    out << "Inventory Report" << endl;
    out << "SKU Name Quantity Price Value" << endl;

    for (int i = 0; i < count; i++) {
        out << items[i].sku << " "
            << items[i].name << " "
            << items[i].quantity << " "
            << items[i].price << " "
            << calculateItemValue(items[i]) << endl;
    }

    out << "Total inventory value: "
        << calculateTotalInventoryValue(items, count)
        << endl;

    return true;
}

double InventoryReport::calculateTotalInventoryValue(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0) {
        return 0.0;
    }

    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += calculateItemValue(items[i]);
    }

    return total;
}

int InventoryReport::findItemBySku(const InventoryItem items[], int count, string sku) {
    if (items == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (items[i].sku == sku) {
            return i;
        }
    }

    return -1;
}

int InventoryReport::findHighestValueItemIndex(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0) {
        return -1;
    }

    int highestIndex = 0;

    for (int i = 1; i < count; i++) {
        if (calculateItemValue(items[i]) > calculateItemValue(items[highestIndex])) {
            highestIndex = i;
        }
    }

    return highestIndex;
}

// ===============================
// Menu helpers
// ===============================

bool isValidMenuChoice(int choice) {
    return choice >= 0 && choice <= 4;
}

void printMenu() {
    cout << endl;
    cout << "Final Project Sample Menu" << endl;
    cout << "1. Demonstrate student scores" << endl;
    cout << "2. Demonstrate linked task list" << endl;
    cout << "3. Demonstrate inventory report" << endl;
    cout << "4. Show instructions" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}

void printStudent(const Student& student) {
    cout << student.getId() << " "
         << student.getName() << " "
         << "Average: " << student.getAverage() << " "
         << "Grade: " << student.getLetterGrade()
         << endl;
}
