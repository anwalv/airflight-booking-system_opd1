#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Airplane{
private:
    string flightNumber;
    string date;
    unordered_map<string,int> seatPrices;
    unordered_map<string, bool> seatAvailability;
    vector<std::string> passengers;
    int seatsInRow;
public:
    Airplane(const string& date, const string& flightNumber,int seatsInRow, unordered_map<string,int>& seatPrices) :
    date(date), flightNumber(flightNumber),seatsInRow(seatsInRow), seatPrices(seatPrices) {}
    void print(){
        cout<< flightNumber<< endl;
        cout<< date <<endl;
    }
};

class Ticket{
    string passenger_name;
    string seat;
    string FlightNumber;
    string status;
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
    vector<vector<string>> returnData(){
        return data;
    }
};

int main() {
    int command;
    vector<vector<string>> data;
    string flightNumber;
    string date;
    int seatsInRow;
    unordered_map<string,string> seatPrices;
    unordered_map<string, bool> seatAvailability;

    string userInput;
    const int MAX_ROWS = 230;
    const int MAX_COLS = 10;
    InfoReader infoReader(MAX_ROWS, MAX_COLS);
    const char* filePath = "C://Users//User//CLionProjects//airflight-booking-system_opd1//data.txt";
    if (infoReader.readFromFile(filePath)) {
        data = infoReader.returnData();
    } else {
        std::cerr << "Failed to read from file." << std::endl;
    }
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<"Hi! What you want to do?"<<endl;
    cin>> command;
    cout<<"Enter date and flight number  "<<endl;
    getline(cin, userInput);

    if (command == 1){
        //подивитись чи створений цей літак
        stringstream ss(userInput);
        string item;
        vector<string> parts;
        while (getline(ss, item, ',')) {
            parts.push_back(item);
        }
        date = parts[0];
        flightNumber = parts[1];
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                const auto &cell = row[i];
                if (cell == date && i + 1 < row.size() && row[i + 1] == flightNumber) {
                    seatsInRow = stoi(row[2]);
                    for (size_t i = 3; i < row.size(); i += 2) {
                        string seatRange = row[i];
                        string priceStr = row[i + 1];
                        /*if (!priceStr.empty() && priceStr.back() == '$') {
                            priceStr.pop_back();
                        }*/
                        size_t dashPos = seatRange.find('-');
                        if (dashPos != string::npos) {
                            int startRow = stoi(seatRange.substr(0, dashPos));
                            int endRow = stoi(seatRange.substr(dashPos + 1));
                                for (int row = startRow; row <= endRow; ++row) {
                                    for (char seat = 'A'; seat < 'A' + seatsInRow; ++seat) {
                                        string seatLabel = to_string(row) + seat;
                                        seatPrices[seatLabel] = priceStr;
                                        seatAvailability[seatLabel] = true;
                                    }
                                }
                        }
                    }
                }
            }
        }
    }
    return 0;
};