#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class BowlingGame {
private:
    vector<int> rolls;

public:
    void roll(int pins) {
        if (pins < 0 || pins > 10) {
            throw invalid_argument("Pin count must be between 0 and 10");
        }

        if (rolls.size() >= 21) {
            throw overflow_error("Too many rolls added");
        }

        rolls.push_back(pins);
    }

    int score() {
        int total = 0;
        int i = 0;

        for (int frame = 0; frame < 10; ++frame) {
            if (i >= rolls.size()) {
                throw out_of_range("Not enough rolls to complete frame");
            }

            if (rolls[i] == 10) { // Strike
                total += 10 + rolls[i + 1] + rolls[i + 2];
                i += 1;
            } else if (rolls[i] + rolls[i + 1] == 10) { // Spare
                total += 10 + rolls[i + 2];
                i += 2;
            } else {
                total += rolls[i] + rolls[i + 1];
                i += 2;
            }
        }

        return total;
    }
};

int main() {
    try {
        BowlingGame game;

        // Sample input: Score should be 133
        vector<int> inputRolls = {1, 4, 4, 5, 6, 4, 5, 5, 10,
                                  0, 1, 7, 3, 6, 4, 10, 2, 8, 6};

        for (int pins : inputRolls) {
            game.roll(pins);
        }

        cout << "Final Bowling Score: " << game.score() << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}