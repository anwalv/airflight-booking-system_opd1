#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Airplane {
private:
    string flightNumber;
    string date;
    unordered_map<string, int> seatPrices;
    unordered_map<string, bool> seatAvailability;
    int seatsInRow;

public:
    Airplane() : seatsInRow(0) {}
    Airplane(const string& date, const string& flightNumber, int seatsInRow) :
            date(date), flightNumber(flightNumber), seatsInRow(seatsInRow) {}
    void setSeatPrice(const string& seat, int price) {
        seatPrices[seat] = price;
    }
    void setSeatAvailability(const string& seat, bool isAvailable) {
        seatAvailability[seat] = isAvailable;
    }
    void print() const {
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Date: " << date << endl;
    }
    void printSeatAvailability() const {
        cout << "Available seats for flight " << flightNumber << " on " << date << ":" << endl;
        for (const auto& pair : seatPrices) {
            const string& seat = pair.first;
            int price = pair.second;
            if (seatAvailability.at(seat)) {
                cout << "Seat: " << seat << ", Price: " << price << "$" << endl;
            }
        }
    }
};

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
            cerr << "Failed to open file." << endl;
            return false;
        }
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            if (rowCount >= maxRows) break;
            stringstream ss(line);
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

    vector<vector<string>> getData() const {
        return data;
    }
};
/*void addAirplane(const vector<vector<string>>& data, unordered_map<string, Airplane>& airplanes, const string& date, const string& flightNumber) {
    string key = flightNumber + date;
    Airplane airplane(date, flightNumber, 0);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            const auto& cell = row[i];
            if (cell == date && i + 1 < row.size() && row[i + 1] == flightNumber) {
                int seatsInRow = stoi(row[2]);
                airplane = Airplane(date, flightNumber, seatsInRow);
                for (size_t i = 3; i < row.size(); i += 2) {
                    string seatRange = row[i];
                    string priceStr = row[i + 1];

                    size_t dashPos = seatRange.find('-');
                    if (dashPos != string::npos) {
                        int startRow = stoi(seatRange.substr(0, dashPos));
                        int endRow = stoi(seatRange.substr(dashPos + 1));

                        for (int row = startRow; row <= endRow; ++row) {
                            for (char seat = 'A'; seat < 'A' + seatsInRow; ++seat) {
                                string seatLabel = to_string(row) + seat;
                                int price = stoi(priceStr);
                                airplane.setSeatPrice(seatLabel, price);
                                airplane.setSeatAvailability(seatLabel, true);
                            }
                        }
                    }
                }
                airplanes[key] = airplane;
                return;
            }
        }
    }
    cerr << "No data found for the given date and flight number." << endl;
}

void viewAirplaneInfo(const vector<vector<string>>& data, unordered_map<string, Airplane>& airplanes, const string& date, const string& flightNumber) {
    string key = flightNumber + date;

    if (airplanes.find(key) != airplanes.end()) {
        Airplane& airplane = airplanes[key];
        airplane.print();
        airplane.printSeatAvailability();
    } else {

        addAirplane(data, airplanes, date, flightNumber);

        // Check again after adding
        if (airplanes.find(key) != airplanes.end()) {
            Airplane& airplane = airplanes[key];
            airplane.print();
            airplane.printSeatAvailability();
        } else {
            cerr << "Failed to add airplane information." << endl;
        }
    }
}
*/
int main() {
    int command;
    vector<vector<string>> data;
    unordered_map<string, Airplane> airplanes;
    string flightNumber;
    string date;
    int seatsInRow;
    const int MAX_ROWS = 230;
    const int MAX_COLS = 10;
    InfoReader infoReader(MAX_ROWS, MAX_COLS);
    const char* filePath = "C://Users//User//CLionProjects//airflight-booking-system_opd1//data.txt";

    if (infoReader.readFromFile(filePath)) {
        data = infoReader.getData();
    }
    else {
        cerr << "Failed to read file." << endl;
        return 1;
    }

    cout << "---------------------------------------------------------------------" << endl;
    cout<< "1. Check available places. \n"
           "2. Buy a ticket.\n"
           "3. Return ticket.\n"
           "4. View the booking info.\n"
           "5. View all user tickets\n"
           "6. View information about booked tickets on particular flight"<<endl;
    cout << "Hello! What do you want to do?" << endl;
    cin >> command;

    if (command == 1) {

        cout << "Enter the date and flight number (format: date,flightNumber) to view: " << endl;
        string userInput;
        cin.ignore();
        getline(cin, userInput);
        stringstream ss(userInput);
        string item;
        vector<string> parts;
        while (getline(ss, item, ',')) {
            parts.push_back(item);
        }
        if (parts.size() != 2) {
            cerr << "Invalid input format. Please use: date,flightNumber" << endl;
            return 1;
        }

        date = parts[0];
        flightNumber = parts[1];
        string key = flightNumber + date;

        if (airplanes.find(key) != airplanes.end()) {
            Airplane &airplane = airplanes[key];
            airplane.print();
            airplane.printSeatAvailability();
        } else {
            string key = flightNumber + date;// замінити  на ,
            Airplane airplane(date, flightNumber, 0);
            for (const auto &row: data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    const auto &cell = row[i];
                    if (cell == date && i + 1 < row.size() && row[i + 1] == flightNumber) {
                        int seatsInRow = stoi(row[2]);
                        airplane = Airplane(date, flightNumber, seatsInRow);
                        for (size_t i = 3; i < row.size(); i += 2) {
                            string seatRange = row[i];
                            string priceStr = row[i + 1];

                            size_t dashPos = seatRange.find('-');
                            if (dashPos != string::npos) {
                                int startRow = stoi(seatRange.substr(0, dashPos));
                                int endRow = stoi(seatRange.substr(dashPos + 1));

                                for (int row = startRow; row <= endRow; ++row) {
                                    for (char seat = 'A'; seat < 'A' + seatsInRow; ++seat) {
                                        string seatLabel = to_string(row) + seat;
                                        int price = stoi(priceStr);
                                        airplane.setSeatPrice(seatLabel, price);
                                        airplane.setSeatAvailability(seatLabel, true);
                                    }
                                }
                            }
                        }
                        airplanes[key] = airplane;
                    }
                }
            }
            airplane.print();
            airplane.printSeatAvailability();
        }
    }
    if (command == 2)
    return 0;

}
