#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Complains {
protected:
    string complainRelated;

public:
    Complains(string complains) {
        this->complainRelated = complains;
    }

    string getComplainRelated() {
        return complainRelated;
    }

    virtual void writtenComplains() {
        cout << "Complaint about: " << complainRelated << endl;
    }
};

class QueryProgress : public Complains {
protected:
    vector<string> hierarchy;
    int currentLevelIndex;
    int daysUnresolved;

public:
    QueryProgress(string related, vector<string> levels)
        : Complains(related), hierarchy(levels), currentLevelIndex(0), daysUnresolved(0) {}

    string getCurrentLevel() {
        return hierarchy[currentLevelIndex];
    }

    void increaseDaysUnresolved() {
        daysUnresolved++;
    }

    int getDaysUnresolved() {
        return daysUnresolved;
    }

    void escalate() {
        if (currentLevelIndex < hierarchy.size() - 1) {
            currentLevelIndex++;
            cout << "Escalated to: " << hierarchy[currentLevelIndex] << endl;
            daysUnresolved = 0;
        } else {
            cout << "Already at the highest escalation level: " << hierarchy[currentLevelIndex] << endl;
        }
    }

    void writtenComplains() override {
        Complains::writtenComplains();
        cout << "Current escalation level: " << getCurrentLevel() << endl;
    }
};

vector<QueryProgress> fetchComplaintsFromCSV(const string& filename) {
    vector<QueryProgress> complaintsList;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string complainRelated, level1, level2, level3, level4;
            vector<string> hierarchy;

            getline(ss, complainRelated, ',');
            getline(ss, level1, ',');
            getline(ss, level2, ',');
            getline(ss, level3, ',');
            getline(ss, level4, ',');

            hierarchy.push_back(level1);
            hierarchy.push_back(level2);
            if (!level3.empty() && level3 != "-") hierarchy.push_back(level3);
            if (!level4.empty() && level4 != "-") hierarchy.push_back(level4);

            QueryProgress query(complainRelated, hierarchy);
            complaintsList.push_back(query);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    return complaintsList;
}

int main() {
    string file = "Level.csv";
    vector<QueryProgress> complaints = fetchComplaintsFromCSV(file);
    int ch;

    for (auto compain : complaints) {
        compain.writtenComplains();
    }

    while (1) {
        cout << "\n======================================================================" << endl;
        cout << "1. Course Related (Graduate Algorithm)" << endl;
        cout << "2. Course Related (Machine Learning)" << endl;
        cout << "3. Course Related (OOPD)" << endl;
        cout << "4. Registration (BTech)" << endl;
        cout << "5. Registration (MTech)" << endl;
        cout << "6. Registration (PhD)" << endl;
        cout << "7. Other Academic Issues (BTech)" << endl;
        cout << "8. Other Academic Issues (MTech)" << endl;
        cout << "9. Other Academic Issues (PhD)" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter Your Query Type: ";
        cin >> ch;

        if (ch >= 1 && ch <= 9) {
            int index = ch - 1;
            QueryProgress& complaint = complaints[index];
            char resolved;

            while (true) {
                complaint.increaseDaysUnresolved();
                complaint.writtenComplains();

                cout << "Has the issue been resolved? (y/n): ";
                cin >> resolved;

                if (resolved == 'y' || resolved == 'Y') {
                    cout << "Complaint resolved at level: " << complaint.getCurrentLevel() << endl;
                    break;
                } else if (resolved == 'n' || resolved == 'N') {
                    cout << "Waiting for 3 seconds before escalation..." << endl;
                    this_thread::sleep_for(seconds(3));

                    if (complaint.getDaysUnresolved() >= 3) {
                        complaint.escalate();
                    } else {
                        cout << "Complaint has been unresolved for " << complaint.getDaysUnresolved()
                             << " days. Escalation will happen after 3 days." << endl;
                    }
                }
            }
        } else if (ch == 10) {
            cout << "Exiting...." << endl;
            return 0;
        } else {
            cout << "Invalid Input...(Please Enter Again)" << endl;
        }
    }

    return 0;
}
