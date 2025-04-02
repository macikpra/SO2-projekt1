#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

class DiningPhilosophers {
private:
    int num_philosophers;
    vector<thread> philosophers;
    vector<mutex> forks;

public:
    DiningPhilosophers(int n) : num_philosophers(n), forks(n) {}

    void dine(int id) {
        while (true) {
            think(id);
            eat(id);
        }
    }

    void think(int id) {
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    void eat(int id) {
        int left = id;
        int right = (id + 1) % num_philosophers;

        if (id % 2 == 0) { // Even philosophers pick left first
            forks[left].lock();
            cout << "Philosopher " << id << " picked up left fork.\n";
            forks[right].lock();
        } else { // Odd philosophers pick right first
            forks[right].lock();
            cout << "Philosopher " << id << " picked up right fork.\n";
            forks[left].lock();
        }

        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::milliseconds(1000));

        forks[left].unlock();
        forks[right].unlock();
        cout << "Philosopher " << id << " put down forks.\n";
    }

    void start() {
        for (int i = 0; i < num_philosophers; i++) {
            philosophers.emplace_back(&DiningPhilosophers::dine, this, i);
        }

        for (auto &philosopher : philosophers) {
            philosopher.join();
        }
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
