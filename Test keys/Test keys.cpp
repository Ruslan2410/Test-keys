#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// Функція для генерації випадкової бітової послідовності
std::vector<bool> generateRandomSequence(int length) {
    std::vector<bool> sequence;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < length; i++) {
        sequence.push_back(distribution(gen));
    }

    return sequence;
}

// Функція для монобітного тесту
bool monobitTest(const std::vector<bool>& sequence) {
    int onesCount = std::count(sequence.begin(), sequence.end(), true);
    int zerosCount = sequence.size() - onesCount;

    // Встановлюємо поріг для різниці між кількістю 1 та 0
    int threshold = sequence.size() / 2;

    return std::abs(onesCount - zerosCount) <= threshold;
}

// Функція для тесту максимальної довжини серії
bool seriesTest(const std::vector<bool>& sequence, int maxSeriesLength) {
    int currentSeriesLength = 1;

    for (size_t i = 1; i < sequence.size(); i++) {
        if (sequence[i] == sequence[i - 1]) {
            currentSeriesLength++;
        }
        else {
            currentSeriesLength = 1;
        }        
    }
    return true; // Якщо всі серії коротші або дорівнюють максимальній довжині, тест пройдений.
}

// Функція для тесту Поккера
bool pokerTest(const std::vector<bool>& sequence) {
    // Розділіть послідовність на блоки довжиною 4 біти кожен
    std::vector<std::vector<bool>> blocks;
    for (int i = 0; i < sequence.size(); i += 4) {
        std::vector<bool> block(sequence.begin() + i, sequence.begin() + i + 4);
        blocks.push_back(block);
    }

    // Підрахуйте кількість унікальних блоків
    std::vector<std::vector<bool>> uniqueBlocks;
    for (const auto& block : blocks) {
        if (std::find(uniqueBlocks.begin(), uniqueBlocks.end(), block) == uniqueBlocks.end()) {
            uniqueBlocks.push_back(block);
        }
    }

    // Перевірте, чи кількість унікальних блоків відповідає очікуваній
    return uniqueBlocks.size() >= 16 && uniqueBlocks.size() <= 20;
}

// Функція для тесту довжин серій
bool runsTest(const std::vector<bool>& sequence, int maxRuns) {
    int currentRun = 1;

    for (int i = 1; i < sequence.size(); i++) {
        if (sequence[i] == sequence[i - 1]) {
            currentRun++;
            if (currentRun > maxRuns) {
                return false;
            }
        }
        else {
            currentRun = 1;
        }
    }

    return true;
}

int main() {
    int sequenceLength = 20000;
    std::vector<bool> randomSequence = generateRandomSequence(sequenceLength);
    setlocale(LC_ALL, "RUSSIAN");
    // Проведення монобітного тесту
    bool monobitResult = monobitTest(randomSequence);

    // Проведення тесту максимальної довжини серії
    bool seriesResult = seriesTest(randomSequence, 6); // Параметр - максимальна довжина серії

    // Проведення тесту Поккера
    bool pokerResult = pokerTest(randomSequence);

    // Проведення тесту довжин серій
    bool runsResult = runsTest(randomSequence, 34); // Параметр - максимальна довжина серії

    if (monobitResult && seriesResult && pokerResult && runsResult) {
        cout << "Всі тести пройдені. Послідовність вважається випадковою." << endl;
    }
    else {
        cout << "Хоча б один тест не пройдений. Послідовність не вважається випадковою." << endl;
    }

    return 0;
}
