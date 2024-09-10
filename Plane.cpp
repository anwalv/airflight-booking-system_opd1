#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

/*class Plane{
private:
public:
    string FlightNumber;
    list seat;
};
class Seats{
    dictionary price;
    int seats_per_row;
    bool availability;
};
class Ticket{
    string passenger_name;
    string seat;
    string FlightNumber;
    string status;
};*/

class InfoReader {
private:
    int rowCount;
    int maxRows;
    int maxCols;
    vector<vector<string>> data;

public:
    InfoReader(int maxRows, int maxCols) : maxRows(maxRows), maxCols(maxCols), rowCount(0) {}
    bool readFromFile(const char* filePath) {
        FILE* file = fopen(filePath, "r");
        if (!file) {
            std::cerr << "Could not open the file!" << std::endl;
            return false;
        }
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            if (rowCount >= maxRows) break;
            stringstream ss(line);//почитати більше про цей клас
            vector<string> row;
            string item;
            while (getline(ss, item, ' ')) {
                row.push_back(item);
            }
            data.push_back(row);
            rowCount++;
        }
        fclose(file);
        return true;
    }
    void print() const {
        for (const auto& row : data) {
            for (const auto& item : row) {
                cout << item << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    const int MAX_ROWS = 230;
    const int MAX_COLS = 10;
    InfoReader infoReader(MAX_ROWS, MAX_COLS);
    const char* filePath = "C://Users//User//CLionProjects//airflight-booking-system_opd1//data.txt";
    if (infoReader.readFromFile(filePath)) {
        infoReader.print();
    } else {
        std::cerr << "Failed to read from file." << std::endl;
    }
    return 0;
}
