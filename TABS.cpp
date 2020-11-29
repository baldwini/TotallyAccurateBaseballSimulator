// TotallyAccurateBaseballSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
using namespace std;

struct Player {
    string playerID;
    string name;
    int year = 0;
    string team;
    int atBats = 0;
    int hits = 0;
    double battingAvg = 0.00;
    int gamesPlayed = 0;
    bool isPitcher = false;
    double ERA = 0.00;   //earned run average is a measure of runs allowed per innings pitched, times 9 for the traditional game length (in innings)
    int ER = 0;
    int IPOuts = 0;
    int IP = 0;    // IPOuts divided by 3
};

void openFile(string filename, vector<Player> &vect, vector<Player> &vectYears, unordered_map<string, int> &map) {
    ifstream workFile;
    workFile.open("C:\\Users\\ian\\Desktop\\TABS\\csvs\\"+filename);
    if (workFile.good()) {
        cout << "open" << endl;
    }
    if (filename == "People.csv") {
        string line;
        string first;
        string last;
        string id;
        string garbage;
        int count = 0;
        getline(workFile, line);  //gets rid of index line
        while (getline(workFile, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            for (int i = 0; i < 12; i++) {
                getline(ss, garbage, ',');
            }
            getline(ss, first, ',');
            getline(ss, last, ',');
            
            Player player;
            player.playerID = id;
            player.name = first + " " + last;
            vect.push_back(player);
            map[id] = count;
            count++;
        }
    }
    else if (filename == "Batting.csv") {
        string line;
        string atBat;
        string hits;
        string id;
        string games;
        string year;
        string team;
        string garbage;
        getline(workFile, line);
        while (getline(workFile, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, year, ',');
            getline(ss, garbage, ',');
            getline(ss, team, ',');
            getline(ss, garbage, ',');
            getline(ss, games, ',');
            getline(ss, atBat, ',');
            getline(ss, garbage, ',');
            getline(ss, hits, ',');
            
            vect.at(map[id]).gamesPlayed = vect.at(map[id]).gamesPlayed + stoi(games);
            vect.at(map[id]).atBats = vect.at(map[id]).atBats + stoi(atBat);
            vect.at(map[id]).hits = vect.at(map[id]).hits + stoi(hits);
            
            Player playerYear;
            playerYear.playerID = id + year + team;
            playerYear.name = vect.at(map[id]).name;
            playerYear.year = stoi(year);
            playerYear.team = team;
            playerYear.gamesPlayed = stoi(games);
            playerYear.atBats = stoi(atBat);
            playerYear.hits = stoi(hits);
            vectYears.push_back(playerYear);
        }
        for (int i = 0; i < vect.size(); i++) {
            vect.at(i).battingAvg = double(vect.at(i).hits) / double(vect.at(i).atBats);
        }
        for (int i = 0; i < vectYears.size(); i++) {
            vectYears.at(i).battingAvg = double(vectYears.at(i).hits) / double(vectYears.at(i).atBats);
        }
    }
    else if (filename == "Pitching.csv") {
        string line;
        string id;
        string IPOuts;
        string ER;
        string garbage;
        getline(workFile, line);
        while (getline(workFile, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            for (int i = 0; i < 11; i++) {
                getline(ss, garbage, ',');
            }
            getline(ss, IPOuts, ',');
            getline(ss, garbage, ',');
            getline(ss, ER, ',');
            vect.at(map[id]).isPitcher = true;
            vect.at(map[id]).IPOuts = vect.at(map[id]).IPOuts + stoi(IPOuts);
            vect.at(map[id]).ER = vect.at(map[id]).ER + stoi(ER);
        }
        for (int i = 0; i < vect.size(); i++) {
            vect.at(i).IP = vect.at(i).IPOuts / 3;
            vect.at(i).ERA = (double(vect.at(i).ER) * 9) / double(vect.at(i).IP);
        }
    }
    workFile.close();
}

int main()
{
    //INSTANTIATE VECTORS AND VARIABLES
    
    vector<pair<string, vector<Player>>> positions;   //String holds pos and vector of players in that pos
    vector<Player> playersYears;  //Holds all players individual batting years
    vector<Player> players;  //Holds all players overall stats, batting and pitching if they pitched
    unordered_map<string, int> indexMap;  //Holds map of player ids to ints for constant time access to overall statistics
    
    //LOAD FILES AND IMPORT INFORMATION INTO VECTORS

    openFile("People.csv", players, playersYears, indexMap);
    openFile("Batting.csv", players, playersYears, indexMap);
    openFile("Pitching.csv", players, playersYears, indexMap);
    
    //MENU SYSTEM

    int choice = 0;
    string name1;
    string name2;
    vector<Player> team1;
    vector<Player> team2;

    while (true) {
        cout << "All files have completed loading!" << endl;
        cout << "Welcome to T.A.B.S., the Totally Accurate Baseball Simulator" << endl;
        cout << "We will simulate the outcome of a baseball game between two teams chosen by YOU!" << endl;
        cout << "Begin by entering the name of the first team: " << endl;
        cin >> name1;
        cout << "Great! Now enter the name of the second team: " << endl;
        cin >> name2;
        cout << name1 << ": " << endl;
        for (int i = 0; i < team1.size(); i++) {    //Print team1 Members

        }
        for (int i = 0; i < 9 - team1.size(); i++) {  //Print Empty Values of team1
            cout << "Team Member Must be Chosen" << endl;
        }
        cout << endl;
        cout << name2 << ": " << endl;
        for (int i = 0; i < team2.size(); i++) {    //Print team2 Members

        }
        for (int i = 0; i < 9 - team2.size(); i++) {  //Print empty values of team2
            cout << "Team Member Must be Chosen" << endl;
        }

    }

    /*
    for (int i = 0; i < players.size(); i++) {
        cout << players.at(i).playerID << " - " << players.at(i).name << " - " << "Games Played: " << players.at(i).gamesPlayed;
        cout << " AB: " << players.at(i).atBats << " H: " << players.at(i).hits << endl;
        if (players.at(i).isPitcher == true && isnan(players.at(i).ERA) == false) {
            cout << "Pitching Stats - ERA: " << players.at(i).ERA << endl;
        }
    }
    
    for (int i = 0; i < playersYears.size(); i++) {
        cout << playersYears.at(i).playerID << " - " << playersYears.at(i).name << " - " << "Games Played: " << playersYears.at(i).gamesPlayed;
        cout << " Team: " << playersYears.at(i).team << " Year: " << playersYears.at(i).year;
        cout << " AB: " << playersYears.at(i).atBats << " H: " << playersYears.at(i).hits << " BA: " << playersYears.at(i).battingAvg << endl;
    }
    */
}
