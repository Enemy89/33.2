#include <iostream>
#include <ctime>

class Fish {
public:
    Fish() {}
    ~Fish() {std::cout << "Clear fish" << std::endl;}
};

class Boot {
public:
    Boot() {}
    ~Boot() {std::cout << "Clear boot" << std::endl;}
};

class Sector {
public:
    Fish* fish;
    Boot* boot;
    bool fishCreated;
    bool bootCreated;

    Sector() : fish(nullptr), boot(nullptr), fishCreated(false), bootCreated(false) {}

    void placeFish() {
        if (!fishCreated) {
            fish = new Fish();
            fishCreated = true;
        }
    }

    void placeBoot() {
        if (!bootCreated) {
            boot = new Boot();
            bootCreated = true;
        }
    }

    bool isFishCaught() const {
        return (fish != nullptr);
    }

    bool hasBoot() const {
        return (boot != nullptr);
    }

    ~Sector() {
        if (fishCreated) {
            delete fish;
            std::cout << "Clear fish" << std::endl;
        }
        if (bootCreated) {
            delete boot;
            std::cout << "Clear boot" << std::endl;
        }
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
        } while (attempts < 9 && !field[sectorIndex].isFishCaught());
    }

    ~FishingGame() {
        for (int i = 0; i < 9; ++i) {
            delete field[i].fish;
            delete field[i].boot;
            std::cout << "Clear sector " << i << std::endl;
        }
    }

private:
    void checkSector(int sectorIndex) {
        if (field[sectorIndex].isFishCaught()) {
            if (field[sectorIndex].fishCreated) {
                field[sectorIndex].fishCreated = false;
                throw Fish();
            }
        } else if (field[sectorIndex].hasBoot()) {
            if (field[sectorIndex].bootCreated) {
                field[sectorIndex].bootCreated = false;
                throw Boot();
            }
        }
    }
};

int main() {
    FishingGame game;
    game.play();
}
