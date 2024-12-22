#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <locale>



struct Record {
    int id;
    std::string name;
    int age;
};

void saveToFile(const std::string& filename, const std::vector<Record>& records) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
        return;
    }
    for (const auto& record : records) {
        outFile << record.id << "," << record.name << "," << record.age << "\n";
    }
    outFile.close();
}

std::vector<Record> loadFromFile(const std::string& filename) {
    std::vector<Record> records;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения." << std::endl;
        return records;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        Record record;
        size_t pos1 = line.find(",");
        size_t pos2 = line.find_last_of(",");
        if (pos1 != std::string::npos && pos2 != std::string::npos && pos1 != pos2) {
            record.id = std::stoi(line.substr(0, pos1));
            record.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            record.age = std::stoi(line.substr(pos2 + 1));
            records.push_back(record);
        }
    }
    inFile.close();
    return records;
}

void addRecord(std::vector<Record>& records) {
    Record newRecord;
    std::cout << "Введите ID: ";
    std::cin >> newRecord.id;
    std::cin.ignore();
    std::cout << "Введите имя: ";
    std::getline(std::cin, newRecord.name);
    std::cout << "Введите возраст: ";
    std::cin >> newRecord.age;
    records.push_back(newRecord);
    std::cout << "Запись добавлена!" << std::endl;
}

void displayRecords(const std::vector<Record>& records) {
    if (records.empty()) {
        std::cout << "База данных пуста." << std::endl;
        return;
    }
    for (const auto& record : records) {
        std::cout << "ID: " << record.id << ", Имя: " << record.name << ", Возраст: " << record.age << std::endl;
    }
}

void deleteRecord(std::vector<Record>& records) {
    int id;
    std::cout << "Введите ID записи для удаления: ";
    std::cin >> id;
    auto it = std::remove_if(records.begin(), records.end(), [id](const Record& record) { return record.id == id; });
    if (it != records.end()) {
        records.erase(it, records.end());
        std::cout << "Запись удалена!" << std::endl;
    } else {
        std::cout << "Запись с таким ID не найдена." << std::endl;
    }
}

int main() {
    std::vector<Record> records;
    const std::string filename = "database.txt";



    records = loadFromFile(filename);

    int choice;
    do {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Добавить запись" << std::endl;
        std::cout << "2. Показать все записи" << std::endl;
        std::cout << "3. Удалить запись" << std::endl;
        std::cout << "4. Сохранить и выйти" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1:
                addRecord(records);
                break;
            case 2:
                displayRecords(records);
                break;
            case 3:
                deleteRecord(records);
                break;
            case 4:
                saveToFile(filename, records);
                std::cout << "Данные сохранены. Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
