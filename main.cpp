#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

class DiningPhilosophers {
private:
    int num_philosophers;
    vector<thread> philosophers;
    vector<mutex> forks;
    vector<int> thinking_count;
    vector<int> eating_count;
    vector<int> waiting_count;
    vector<string> states;
    mutex print_mutex;
    bool running;

public:
    DiningPhilosophers(int n) : num_philosophers(n), forks(n), thinking_count(n, 0), eating_count(n, 0), waiting_count(n, 0), states(n, "THINKING"), running(true) {}

    void dine(int id) {
        while (running) {
            think(id);
            eat(id);
        }
    }

    void think(int id) {
        states[id] = "THINKING";
        thinking_count[id]++;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    void eat(int id) {
        int left = id;
        int right = (id + 1) % num_philosophers;

        states[id] = "WAITING";
        waiting_count[id]++;

        if (id % 2 == 0) { // Even philosophers pick left first
            forks[left].lock();
            forks[right].lock();
        } else { // Odd philosophers pick right first
            forks[right].lock();
            forks[left].lock();
        }

        states[id] = "EATING";
        eating_count[id]++;
        this_thread::sleep_for(chrono::milliseconds(1000));

        forks[left].unlock();
        forks[right].unlock();

        states[id] = "THINKING";
    }

    void update_status() {
        while (running) {
            {
                lock_guard<mutex> lock(print_mutex);
                cout << "\n------------------------------------------------------\n";
                cout << left << setw(12) << "Philosopher" << setw(12) << "State" << setw(10) << "Thinking" << setw(10) << "Eating" << setw(10) << "Waiting" << "\n";
                cout << "------------------------------------------------------\n";
                for (int i = 0; i < num_philosophers; i++) {
                    cout << setw(12) << i << setw(12) << states[i] << setw(10) << thinking_count[i] << setw(10) << eating_count[i] << setw(10) << waiting_count[i] << "\n";
                }
                cout << "------------------------------------------------------\n";
            }
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }

    void start() {
        thread status_thread(&DiningPhilosophers::update_status, this);
        
        for (int i = 0; i < num_philosophers; i++) {
            philosophers.emplace_back(&DiningPhilosophers::dine, this, i);
        }

        for (auto &philosopher : philosophers) {
            philosopher.join();
        }

        running = false;
        status_thread.join();
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number_of_philosophers>\n";
        return 1;
    }

    int num_philosophers = stoi(argv[1]);
    DiningPhilosophers dp(num_philosophers);
    dp.start();

    return 0;
}
