#include "banker.h"
#include <cassert> // For assert function

using namespace std;


/**
 * @brief Constructor to initialize the system state.
 * @param threads The number of threads in the system (n).
 * @param resources The number of resource types in the system (m).
 */
SystemState::SystemState(const int threads, const int resources) : n(threads), m(resources) {}

/**
 * @brief Checks if one vector is less than or equal to another.
 * @param vec1 The first vector (left-hand side).
 * @param vec2 The second vector (right-hand side).
 * @return True if vec1 <= vec2 for all elements, false otherwise.
 */
bool SystemState::LTE(const vector<int>& vec1, const vector<int>& vec2) const {
    assert(vec1.size() == vec2.size()); // Ensure vectors are of the same size
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1[i] > vec2[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Determines if the system is in a safe state and provides the safe sequence.
 * @param allocation The current allocation matrix.
 * @param available The current available vector.
 * @param need The current need matrix.
 * @return A vector containing the safe sequence if the system is safe, or an empty vector if not.
 */

vector<int> SystemState::safe(const vector<vector<int>>& allocation,
    const vector<int>& available,
    const vector<vector<int>>& need) const {
    vector<int> thread_sequence; // Stores the safe sequence of threads
    vector<int> work = available; // Work vector, initially equal to available resources
    vector<int> finish(n, 0); // Finish vector to track completed threads (0 = false, 1 = true)
    int completed = 0; // Counter for completed threads

    while (completed < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            // Find a thread that can proceed
            if (!finish[i] && LTE(need[i], work)) {
                // Allocate resources to this thread
                for (int j = 0; j < m; j++) {
                    work[j] += allocation[i][j];
                }
                finish[i] = 1; // Mark thread as finished
                thread_sequence.push_back(i); // Add thread to safe sequence
                completed++;
                found = true;
                break;
            }
        }
        if (!found) break; // No thread can proceed, exit loop
    }

    // If all threads are completed, return the safe sequence; otherwise, return an empty vector
    return (completed == n) ? thread_sequence : vector<int>();
}

/**
 * @brief Inputs the initial state of the system from the user.
 */

void SystemState::inputState() {
    cout << "Enter the available vector: ";
    available.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    cout << "Enter MAX matrix:" << endl;
    MAX.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> MAX[i][j];
        }
    }

    cout << "Enter Allocation matrix:" << endl;
    allocation.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    // Calculate the Need matrix
    need.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = MAX[i][j] - allocation[i][j];
            assert(need[i][j] >= 0); // Ensure Need values are non-negative
        }
    }

    // Display the initial state
    displayState();
}

/**
 * @brief Displays the current state of the system, including all matrices and vectors.
 */
void SystemState::displayState() const {
    cout << "Available Vector:" << endl;
    for (const int& val : available) {
        cout << val << " ";
    }
    cout << endl;

    cout << "MAX Matrix:" << endl;
    for (const auto& row : MAX) {
        for (const int& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "Allocation Matrix:" << endl;
    for (const auto& row : allocation) {
        for (const int& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "Need Matrix:" << endl;
    for (const auto& row : need) {
        for (const int& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Checks if the system is in a safe state and prints the result.
 */
void SystemState::isSafeState() const {
    vector<int> threads = safe(allocation, available, need);
    if (!threads.empty()) {
        cout << "Yes, safe state <";
        for (size_t i = 0; i < threads.size(); i++) {
            cout << "P" << threads[i];
            if (i != threads.size() - 1) cout << ",";
        }
        cout << ">" << endl;
    }
    else {
        cout << "No, system is not in a safe state" << endl;
    }
}

/**
 * @brief Handles a resource request from a thread.
 * @param request The resource request vector.
 * @param Ti The thread index making the request.
 */
void SystemState::resourceRequest(const vector<int>& request, const int Ti) {
    assert(Ti >= 0 && Ti < n); // Ensure thread index is valid
    assert(request.size() == m); // Ensure request vector is of correct size

    if (!LTE(request, need[Ti])) {
        cout << "Thread exceeded Maximum claim" << endl;
        return;
    }
    if (!LTE(request, available)) {
        cout << "No, Thread must wait" << endl;
        return;
    }

    // Simulate resource allocation to test safety
    vector<int> av_temp = available;
    vector<vector<int>> allo_temp = allocation;
    vector<vector<int>> need_temp = need;

    for (int i = 0; i < m; i++) {
        av_temp[i] -= request[i];
        allo_temp[Ti][i] += request[i];
        need_temp[Ti][i] -= request[i];
    }

    // Check if the system is still in a safe state
    if (!safe(allo_temp, av_temp, need_temp).empty()) {
        available = av_temp;
        allocation = allo_temp;
        need = need_temp;
        cout << "Yes, request can be granted with safe state" << endl;
    }
    else {
        cout << "No, Thread must wait" << endl;
    }
}




