#include <iostream>
#include <ctime>

class Fish {
public:
    Fish() {}
    ~Fish() {}
};

class Boot {
public:
    Boot() {}
    ~Boot() {}
};

class Sector {
public:
    Fish* fish;
    Boot* boot;

    Sector() : fish(nullptr), boot(nullptr) {}

    void placeFish() {
        fish = new Fish();
    }

    void placeBoot() {
        boot = new Boot();
    }

    bool isFishCaught() const {
        return (fish != nullptr);
    }

    bool hasBoot() const {
        return (boot != nullptr);
    }
    ~Sector() {
        delete fish;
        delete boot;
    }
};

class FishingGame {
private:
    Sector field[9];
    int attempts;

public:
    FishingGame() : attempts(0) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        field[std::rand() % 9].placeFish();
        for (int i = 0; i < 3; ++i) {
            int sectorIndex;
            do {
                sectorIndex = std::rand() % 9;
            } while (field[sectorIndex].isFishCaught());
            field[sectorIndex].placeBoot();
        }
    }

    void play() {
        int sectorIndex;
        do {
            std::cout << "Enter the sector number for casting the rod (0-8): ";
            std::cin >> sectorIndex;

            try {
                checkSector(sectorIndex);
                attempts++;
            } catch (Fish& f) {
                std::cout << "Congratulations! You caught a fish for " << attempts << " attempts." << std::endl;
                return;
            } catch (Boot& b) {
                std::cout << "You've caught a shoe. The game is over." << std::endl;
                return;
            }
        } while (true);
    }

    ~FishingGame() {
        for (int i = 0; i < 9; ++i) {
            delete field[i].fish;
            delete field[i].boot;
        }
    }

private:
    void checkSector(int sectorIndex) {
        if (field[sectorIndex].isFishCaught()) {
            throw Fish();
        } else if (field[sectorIndex].hasBoot()) {
            throw Boot();
        }
    }
};

int main() {
    FishingGame game;
    game.play();
}
