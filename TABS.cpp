// TotallyAwesomeBaseballSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

void openFile(string filename, vector<Player> &vect, unordered_map<string, int> &map) {
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
        string garbage;
        getline(workFile, line);
        while (getline(workFile, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            for(int i = 0; i < 4; i++) {
                getline(ss, garbage, ',');
            }
            getline(ss, games, ',');
            getline(ss, atBat, ',');
            getline(ss, garbage, ',');
            getline(ss, hits, ',');
            vect.at(map[id]).gamesPlayed = vect.at(map[id]).gamesPlayed + stoi(games);
            vect.at(map[id]).atBats = vect.at(map[id]).atBats + stoi(atBat);
            vect.at(map[id]).hits = vect.at(map[id]).hits + stoi(hits);
        }
        for (int i = 0; i < vect.size(); i++) {
            vect.at(i).battingAvg = double(vect.at(i).hits) / double(vect.at(i).atBats);
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
    vector<pair<string, vector<Player>>> positions;   //String holds pos and vector of players in that pos
    vector<Player> players;  //Holds all players
    unordered_map<string, int> indexMap;
    openFile("People.csv", players, indexMap);
    openFile("Batting.csv", players, indexMap);
    openFile("Pitching.csv", players, indexMap);
    for (int i = 0; i < players.size(); i++) {
        cout << players.at(i).playerID << " - " << players.at(i).name << " - " << "Games Played: " << players.at(i).gamesPlayed;
        cout << " AB: " << players.at(i).atBats << " H: " << players.at(i).hits << endl;
        if (players.at(i).isPitcher == true && isnan(players.at(i).ERA) == false) {
            cout << "Pitching Stats - ERA: " << players.at(i).ERA << endl;
        }
    }
}