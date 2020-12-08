// TotallyAccurateBaseballSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cmath>
#include <chrono>
#include <stdlib.h>
#include <time.h>
using namespace std;

//DATA STRUCTURE FOR PLAYER OBJECTS
struct Player {
    string playerID;
    string name;
    int year = 0;
    string team;
    int atBats = 0;
    int hits = 0;
    int RBI = 0;
    double battingAvg = 0.00;
    int gamesPlayed = 0;
    bool isPitcher = false;
    double ERA = 0.00;   //earned run average is a measure of runs allowed per innings pitched, times 9 for the traditional game length (in innings)
    int ER = 0;
    int IPOuts = 0;
    int IP = 0;    // IPOuts divided by 3
};

//PARSES CSV DATA FOR MAIN
void openFile(string filename, vector<Player>& vect, vector<Player>& vectYears, vector<Player>& pitchers, vector<Player>& pitcherYears, unordered_map<string, int>& map) {
    ifstream workFile;
    workFile.open("../csvs/" + filename);
    if (workFile.good()) {
        cout << endl << filename << " is being loaded!" << endl;
    }
    else {
        cout << "Files have not loaded properly!" << endl;
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
        string RBI;
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
            for (int i = 0; i < 3; i++) {
                getline(ss, garbage, ',');
            }
            getline(ss, RBI, ',');

            vect.at(map[id]).gamesPlayed = vect.at(map[id]).gamesPlayed + stoi(games);
            vect.at(map[id]).atBats = vect.at(map[id]).atBats + stoi(atBat);
            vect.at(map[id]).hits = vect.at(map[id]).hits + stoi(hits);
            //cout << "RBI Read: " << RBI << endl;
            if (RBI != "") {
                vect.at(map[id]).RBI = vect.at(map[id]).RBI + stoi(RBI);
            }

            Player playerYear;
            playerYear.playerID = id + year + team;
            playerYear.name = vect.at(map[id]).name;
            playerYear.year = stoi(year);
            playerYear.team = team;
            playerYear.gamesPlayed = stoi(games);
            playerYear.atBats = stoi(atBat);
            playerYear.hits = stoi(hits);
            if (RBI != "") {
                playerYear.RBI = stoi(RBI);
            }
            vectYears.push_back(playerYear);
        }
        for (int i = 0; i < vect.size(); i++) {
            if (vect.at(i).atBats == 0) {
                vect.at(i).battingAvg = 0.00;
            }
            else {
                vect.at(i).battingAvg = double(vect.at(i).hits) / double(vect.at(i).atBats);
            }
        }
        for (int i = 0; i < vectYears.size(); i++) {
            if (vectYears.at(i).atBats == 0) {
                vectYears.at(i).battingAvg = 0.00;
            }
            else {
                vectYears.at(i).battingAvg = double(vectYears.at(i).hits) / double(vectYears.at(i).atBats);
            }
        }
    }
    else if (filename == "Pitching.csv") {
        string line;
        string id;
        string year;
        string team;
        string games;
        string IPOuts;
        string ER;
        string garbage;
        getline(workFile, line);
        while (getline(workFile, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, year, ',');
            getline(ss, garbage, ',');
            getline(ss, team, ',');
            for (int i = 0; i < 3; i++) {
                getline(ss, garbage, ',');
            }
            getline(ss, games, ',');
            for (int i = 0; i < 4; i++) {
                getline(ss, garbage, ',');
            }
            getline(ss, IPOuts, ',');
            getline(ss, garbage, ',');
            getline(ss, ER, ',');
            vect.at(map[id]).isPitcher = true;
            vect.at(map[id]).IPOuts = vect.at(map[id]).IPOuts + stoi(IPOuts);
            vect.at(map[id]).ER = vect.at(map[id]).ER + stoi(ER);

            Player pitcher;
            pitcher.isPitcher = true;
            pitcher.name = vect.at(map[id]).name;
            pitcher.playerID = id + year + team;
            pitcher.year = stoi(year);
            pitcher.team = team;
            pitcher.gamesPlayed = stoi(games);
            pitcher.ER = stoi(ER);
            pitcher.IPOuts = stoi(IPOuts);
            pitcher.IP = stoi(IPOuts) / 3;
            pitcher.ERA = (double(pitcher.ER) * 9) / double(pitcher.IP);

            pitcherYears.push_back(pitcher);
        }

        for (int i = 0; i < vect.size(); i++) {
            vect.at(i).IP = vect.at(i).IPOuts / 3;
            vect.at(i).ERA = (double(vect.at(i).ER) * 9) / double(vect.at(i).IP);

            if (vect.at(i).isPitcher == true) {
                pitchers.push_back(vect.at(i));
            }
        }

    }
    workFile.close();
}

//GIVEN TWO TEAMS, RETURNS RESULT OF THEIR GAME
pair<int, int> calculateResults(vector<Player> team1, vector<Player> team2)
{
    // Random generator
    random_device rnd;
    default_random_engine gen(rnd());

    int team1Runs, team2Runs;

    // Calculate mean for team 1
    double sum1 = 0;
    for (int i = 1; i < team1.size(); i++) // Calculate the sum of RBIs/game of each batter
        sum1 += (double)team1[i].RBI / (double)team1[i].gamesPlayed;
    double mean1 = (sum1 + team2[0].ERA) / 2; // Set the mean to the average of the sum and the ERA of the opposing pitcher

    // Get a value from a normal distribution with mean1 and 2 as mean and standard deviation
    normal_distribution<double> nd1(mean1, 2.0);
    team1Runs = int(nd1(gen));


    // Calculate mean for team 2
    double sum2 = 0;
    for (int i = 1; i < team2.size(); i++) // Calculate the sum of RBIs/game of each batter
        sum2 += (double)team2[i].RBI / (double)team2[i].gamesPlayed;
    double mean2 = (sum2 + team1[0].ERA) / 2; // Set the mean to the average of the sum and the ERA of the opposing pitcher

    // Get a value from a normal distribution with mean2 and 2 as mean and standard deviation
    normal_distribution<double> nd2(mean2, 2.0);
    team2Runs = int(nd2(gen));

    // Make sure the runs are not negative
    if (team1Runs < 0)
        team1Runs = 0;

    if (team2Runs < 0)
        team2Runs = 0;

    // Make sure there is no tie
    if (team1Runs == team2Runs)
    {
        if (mean1 > mean2)
            team1Runs++;
        else
            team2Runs++;
    }

    return make_pair(team1Runs, team2Runs);
}

//HELPER FOR MERGESORT, Professor Kapoor's OpenGDB referenced for help in structuring algorithm.
void merge(string param, vector<Player>& players, int left, int middle, int right) {
    int num1 = middle - left + 1;
    int num2 = right - middle;

    vector<Player> leftArr;
    vector<Player> rightArr;

    //Create the two subarrays from players vect
    for (int i = 0; i < num1; i++) {
        leftArr.push_back(players.at(left + i));
    }
    for (int j = 0; j < num2; j++) {
        rightArr.push_back(players.at(middle + 1 + j));
    }

    //Index of first subarray
    int i = 0;
    //Index of second subarray
    int j = 0;
    //Initial index of merged subarray
    int k = left;

    //Possible params to pass for batters: battingAvg, hits, ERA, AtBats
    if (param == "AVG") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).battingAvg <= rightArr.at(j).battingAvg) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    else if (param == "HITS") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).hits <= rightArr.at(j).hits) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    else if (param == "ATBAT") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).atBats <= rightArr.at(j).atBats) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    else if (param == "RBI") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).RBI <= rightArr.at(j).RBI) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    //Possible params to pass for pitchers: ERA, ER, IP

    else if (param == "ERA") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).ERA <= rightArr.at(j).ERA) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    else if (param == "ER") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).ER <= rightArr.at(j).ER) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    else if (param == "IP") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).IP <= rightArr.at(j).IP) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

    //Possible params for general information: Games Played

    else if (param == "GAMES") {
        while (i < num1 && j < num2) {
            if (leftArr.at(i).gamesPlayed <= rightArr.at(j).gamesPlayed) {
                players.at(k) = leftArr.at(i);
                i++;
            }
            else {
                players.at(k) = rightArr.at(j);
                j++;
            }
            k++;
        }

        while (i < num1) {
            players.at(k) = leftArr.at(i);
            i++;
            k++;
        }
        while (j < num2) {
            players.at(k) = rightArr.at(j);
            j++;
            k++;
        }
    }

}

//MERGESORT FUNCTION: UF COP3530, Professor Kapoor, OpenGDB source referenced for help structuring mergesort.
void mergeSort(string param, vector<Player>& players, int left, int right) {
    if (left >= right) {
        return;
    }
    int middle = (left + right - 1) / 2;

    mergeSort(param, players, left, middle);
    mergeSort(param, players, middle + 1, right);

    merge(param, players, left, middle, right);
}

//HELPER FOR QUICKSORT
int partition(int start, int end, vector<Player>& vect, string stat)
{
    Player pivot = vect[start];
    int up = start, down = end;

    while (up < down)
    {
        //BATTING STATISTIC SORTS

        if (stat == "AVG")
        {
            while (vect[up].battingAvg <= pivot.battingAvg && up < end)
                up++;
            while (vect[down].battingAvg >= pivot.battingAvg && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }
        else if (stat == "RBI")
        {
            while (vect[up].RBI <= pivot.RBI && up < end)
                up++;
            while (vect[down].RBI >= pivot.RBI && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }
        else if (stat == "HITS")
        {
            while (vect[up].hits <= pivot.hits && up < end)
                up++;
            while (vect[down].hits >= pivot.hits && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }
        else if (stat == "ATBAT")
        {
            while (vect[up].atBats <= pivot.atBats && up < end)
                up++;
            while (vect[down].atBats >= pivot.atBats && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }


        //PITCHING STATISTIC SORTS

        else if (stat == "ERA")
        {
            while (vect[up].ERA <= pivot.ERA && up < end)
                up++;
            while (vect[down].ERA >= pivot.ERA && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }
        else if (stat == "ER")
        {
            while (vect[up].ER <= pivot.ER && up < end)
                up++;
            while (vect[down].ER >= pivot.ER && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }
        else if (stat == "IP")
        {
            while (vect[up].IP <= pivot.IP && up < end)
                up++;
            while (vect[down].IP >= pivot.IP && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }

        //GENERAL STATISTICS

        else if (stat == "GAMES")
        {
            while (vect[up].gamesPlayed <= pivot.gamesPlayed && up < end)
                up++;
            while (vect[down].gamesPlayed >= pivot.gamesPlayed && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }

        else if (stat == "Year")
        {
            while (vect[up].year <= pivot.year && up < end)
                up++;
            while (vect[down].year >= pivot.year && down > start)
                down--;
            if (up < down)
                swap(vect[up], vect[down]);
        }
    }
    swap(vect[start], vect[down]);
    return down;
}

//QUICKSORT FUNCTION: GeeksForGeeks referenced for single tail recursion implementation.
void quickSort(int start, int end, vector<Player>& vect, string stat)
{
    while (start < end)
    {
        int pivotIndex = partition(start, end, vect, stat);
        if (pivotIndex - start < end - pivotIndex)
        {
            quickSort(start, pivotIndex - 1, vect, stat); //Recursively quick sort left of pivot
            start = pivotIndex + 1;
        }
        else
        {
            quickSort(pivotIndex + 1, end, vect, stat); //Recursively quick sort right of pivot
            end = pivotIndex - 1;
        }
    }
}

//Gives random vector of pitchers
vector<int> random(int a) {
    vector<int> randoms;
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int random = rand() % a;
        randoms.push_back(random);
    }
    return randoms;
}

//Checks if the player a user inputs to find actually exists overall
int exist_Overall(vector<Player> vect, string plyrNm) {
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i].name.compare(plyrNm) == 0) {
            return i;
        }
    }

    return -1;
}

vector<int> exist_Specific(vector<Player> vect, string plyrNm) {
    vector<int> nums;
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i].name.compare(plyrNm) == 0) {
            nums.push_back(i);
        }
    }

    return nums;
}

//Prints out the time it takes to sort the vectors using mergeSort as well as sorting the vectors, c++ reference referenced for implementation of chrono time readings.
void printTime(vector<Player>& players, vector<Player>& pitchers, string plyrSortStat, string pitchSortStat) {

    vector<Player> quickArrayPlayers = players;
    vector<Player> quickArrayPitchers = pitchers;

    cout << endl << "MergeSort on the Pitchers is beginning!" << endl;
    auto start = chrono::high_resolution_clock::now();
    mergeSort(pitchSortStat, pitchers, 0, pitchers.size() - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << endl << "Time taken for MergeSort on the Pitchers: " << duration.count() << " microseconds." << endl;

    cout << endl << "QuickSort on the Pitchers is beginning!" << endl;
    auto start2 = chrono::high_resolution_clock::now();
    mergeSort(pitchSortStat, quickArrayPitchers, 0, quickArrayPitchers.size() - 1);
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    cout << endl << "Time taken for QuickSort on the Pitchers: " << duration2.count() << " microseconds." << endl;

    if (duration.count() > duration2.count()) {
        cout << endl << "QuickSort was faster by " << duration.count() - duration2.count() << " microseconds." << endl;
    }
    else {
        cout << endl << "MergeSort was faster by " << duration2.count() - duration.count() << " microseconds." << endl;
    }

    cout << endl << "MergeSort on the Players is beginning!" << endl;
    start = chrono::high_resolution_clock::now();
    mergeSort(plyrSortStat, players, 0, players.size() - 1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << endl << "Time taken for MergeSort on the Players: " << duration.count() << " microseconds." << endl;

    cout << endl << "QuickSort on the Players is beginning!" << endl;
    start2 = chrono::high_resolution_clock::now();
    quickSort(0, quickArrayPlayers.size() - 1, quickArrayPlayers, plyrSortStat);
    stop2 = chrono::high_resolution_clock::now();
    duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);

    cout << endl << "Time taken for QuickSort on the Players: " << duration2.count() << " microseconds." << endl;

    if (duration.count() > duration2.count()) {
        cout << endl << "QuickSort was faster by " << duration.count() - duration2.count() << " microseconds." << endl << endl;
    }
    else {
        cout << "MergeSort was faster by " << duration2.count() - duration.count() << " microseconds." << endl << endl;
    }

}

//Allows user to pick stats to sort the arrays by
void pickStat(string& plyrSortStat, string& pitchSortStat) {
    cout << "FIRST THING WE NEED TO \"SORT\" OUT IS WHICH STAT YOU WOULD LIKE THE PITCHERS TO BE SORTED BY?\n1: ERA\n2: ER\n3: IP\n4: GAMES PLAYED\n";
    int sorter;
    bool gate = false;
    cin >> sorter;

    while (!gate) {
        if (sorter == 1) {
            pitchSortStat = "ERA";
            gate = true;
        }

        else if (sorter == 2) {
            pitchSortStat = "ER";
            gate = true;
        }

        else if (sorter == 3) {
            pitchSortStat = "IP";
            gate = true;
        }

        else if (sorter == 4) {
            pitchSortStat = "GAMES";
            gate = true;
        }

        else {
            cout << "Please enter a valid option.\n";
            cin >> sorter;
        }

    }

    gate = false;
    sorter = 0;

    cout << "NOW WHICH STAT WOULD YOU LIKE THE OTHER PLAYERS TO BE SORTED BY?\n1: BATTING AVERAGE\n2: HITS\n3: RBI\n4: TIMES THEY WENT TO BAT (at bat)\n5: GAMES PLAYED\n";
    cin >> sorter;

    while (!gate) {
        if (sorter == 1) {
            plyrSortStat = "AVG";
            gate = true;
        }

        else if (sorter == 2) {
            plyrSortStat = "HITS";
            gate = true;
        }

        else if (sorter == 3) {
            plyrSortStat = "RBI";
            gate = true;
        }

        else if (sorter == 4) {
            plyrSortStat = "ATBAT";
            gate = true;
        }

        else if (sorter == 5) {
            plyrSortStat = "GAMES";
            gate = true;
        }

        else {
            cout << "Please choose a valid option.\n";
            cin >> sorter;
        }
    }

    gate = false;
}

//Allows user to pick player to add to their team
void playerAdder(vector<Player>& objects, vector<Player>& team, bool isPitcher, bool specific) {
    int pick; //USER PICKS THE PLAYER THEY WANT
    int num = 0;
    bool gate = false;

    if (specific == false) {

        if (isPitcher == false) {
            for (int j = 0; j < objects.size(); j++) {
                cout << num << ": " << objects[j].name << " - Games: " << objects.at(j).gamesPlayed << " - At Bats: " << objects.at(j).atBats << " - Hits: " << objects.at(j).hits << " - Batting Average : " << objects.at(j).battingAvg << " - RBI: " << objects.at(j).RBI << endl;
                num++;
            }
        }
        else {
            for (int j = 0; j < objects.size(); j++) {
                cout << num << ": " << objects[j].name << " - Games: " << objects.at(j).gamesPlayed << " - ERA: " << objects.at(j).ERA << " - ER: " << objects.at(j).ER << " - IP: " << objects.at(j).IP << endl;
                num++;
            }
        }
    }

    else {
        if (isPitcher == false) {
            for (int j = 0; j < objects.size(); j++) {
                cout << num << ": " << objects[j].name << " - Year: " << objects[j].year << " - Games: " << objects.at(j).gamesPlayed << " - At Bats: " << objects.at(j).atBats << " - Hits: " << objects.at(j).hits << " - Batting Average : " << objects.at(j).battingAvg << " - RBI: " << objects.at(j).RBI << endl;
                num++;
            }
        }
        else {
            for (int j = 0; j < objects.size(); j++) {
                cout << num << ": " << objects[j].name << " - Year: " << objects[j].year << " - Games: " << objects.at(j).gamesPlayed << " - ERA: " << objects.at(j).ERA << " - ER: " << objects.at(j).ER << " - IP: " << objects.at(j).IP << endl;
                num++;
            }
        }
    }

    cin >> pick;
    cout << endl;

    while (!gate) {
        if (pick < 0 || pick > objects.size() - 1) {
            cout << "Please pick a player.\n";
            cin >> pick;
            cout << endl;
        }

        else {
            team.push_back(objects[pick]);
            //cout << objects[pick].name << " was added to the roster. Happy to have you!\n";
           // cout << endl;
            objects.clear();
            pick = 0;
            gate = true;
        }
    }
    objects.clear();
    cin.ignore();
}

//BUILDS THE VECTOR FULL OF PLAYERS FOR A TEAM
void teamBuilder(vector<Player> pitchers, vector<Player> pitchYr, vector<Player> plyrYear, vector<Player> plyrs, vector<Player>& team, string teamName) {
    int buildQuality; //DETERMINES IF USER WANTS TO SEACH FOR PLAYERS, WANTS THE BEST/WORST, OR WANTS RANDOM PLAYERS
    int plyrStat; //DETERMINES IF THE USER WANTS THE PLAYERS STATS TO BE OVERALL STATS OR BASED UPON A SPECIFIC YEAR
    int plyrPos; //USER PICKS THE POSITION THAT THEY WANT THE PLAYER TO BE FROM
    int yr; //USER ENTERS IN THE YEAR THE PLAYER THEY ARE LOOKING FOR PLAYED IN
    int bw; //USER CHOOSES IF THEY WANT THE BEST PLAYERS OR THE WORST PLAYERS
    int sorter; //USER CHOOSES THE STAT THEY WANT EVERY PLAYER TO BE SORTED BY
    int rando_segment = 0; //ALLOWS FOR THE USER TO HAVE 10 DIFFERENT PLAYERS FOR EVERY PLAYER SELECTION
    string bwNum; //USER CHOOSES HOW MANY OF THE BEST/WORST PLAYERS THEYLL HAVE TO CHOOSE FROM
    string plyrNm; //USER INPUTS THE NAME OF THE PLAYER THEY WANT
    string plyrSortStat; //THE STRING VERSION OF THE STAT THEY WANT GENERAL PLAYERS TO BE SORTED BY
    string pitchSortStat; //THE STRING VERSION OF THE STAT THE USER WANTS THEIR PITCHER TO BE SORTED BY
    vector<Player> objects; //STORES ALL THE PLAYERS THAT THE USER CAN CHOOSE FROM DURING EACH SELECTION
    vector<Player> sortedPitcherVect = pitchers; //STORES THE PITCHER VECTOR TO BE SORTED FOR OVERALL SELECTION
    vector<Player> sortedPlayerVect = plyrs; //STORES THE PLAYER VECTOR TO BE SORTED FOR OVERALL SELECTION
    vector<Player> sortPitchYr = pitchYr; //STORES THE PITCHER VECTOR TO BE SORTED FOR SPECIFIC YEARS
    vector<Player> sortPlyrYear = plyrYear; //STORES THE PLAYER VECTOR TO BE SORTED FOR SPECIFIC YEARS
    vector<int> randos; //STORES THE RANDOM NUMBERS NEEDED TO CHOOSE RANDOM PLAYERS
    vector<int> search_pos; //STORES THE POSITIONS OF ALL THE PLAYERS IN THEIR YEARS
    bool best = false; //IF FALSE THEN THE USER WANTS THE WORST PLAYERS AND IF TRUE THEN THE USER WANTS THE BEST PLAYERS
    bool gate = false; //ALLOWS FOR THE USE OF A WHILE LOOP WHEN USER IS CHOOSING AN OPTION IN CASE THE OPTION IS INVALID

    cout << "WELCOME TO THE TEAMBUILDER FOR " + teamName + "\nHERE YOU WILL PICK A TEAM OF 10 PLAYERS, INCLUDING ONE PITCHER AND THE REST BEING YOUR CHOICE\nPLEASE NOTE THAT YOU CANNOT GO BACK TO ALTER ANY CHOICES YOU MAKE WITHOUT RESTARTING THE PROGRAM SO CHOOSE CAREFULLY\n";



    cout << "HOW WOULD YOU LIKE TO HAVE PLAYERS PRESENTED?\n1: GIVE ME RANDOM PLAYERS\n2: ADVANCED SEARCH\n3: BEST/WORST\n";
    cin >> buildQuality;
    cout << endl;

    while (!gate) {
        if (buildQuality < 1 || buildQuality > 3) {
            cout << "Invalid input. please reenter.\n";
            cin >> buildQuality;
            cout << endl;
        }

        else {
            gate = true;
        }
    }

    gate = false;


    switch (buildQuality) {

        //RANDOMS
    case 1:
        cout << "RANDOM PLAYERS IT IS! WHICH WOULD YOU PREFER THE PLAYERS STATS TO BE: OVERALL (the totals for all the years they played), OR THEIR STATS FROM SPECIFIC YEARS?\n1: OVERALL\n2: BASED UPON YEAR\n";
        cin >> plyrStat;
        cout << endl;

        while (!gate) {
            if (plyrStat < 1 || plyrStat > 2) {
                cout << "Invalid input. please reenter.\n";
                cin >> plyrStat;
                cout << endl;
            }

            else {
                gate = true;
            }
        }

        gate = false;

        switch (plyrStat) {


            //OVERALL STATS
        case 1:
            for (int i = 0; i < 10; i++) {

                //MANDATORY PITCHER SELECTION
                if (i == 0) {
                    randos = random(pitchers.size() - 1);
                    cout << "Pick one of the following pitchers to add to your team.\n";
                    for (int j = 0; j < 10; j++) {
                        objects.push_back(pitchers[randos[j + rando_segment]]);
                    }
                    randos.clear();
                    playerAdder(objects, team, true, false);
                    cout << team[i].name << " was added to the team!\n" << endl;
                }
                else {
                    randos = random(plyrs.size() - 1);

                    cout << "PICK YOUR NEXT PLAYER:\n";
                    for (int j = 0; j < 10; j++) {
                        objects.push_back(plyrs[randos[j + rando_segment]]);
                    }
                    playerAdder(objects, team, false, false);
                    cout << team[i].name << " was added to the team!\n" << endl;
                    rando_segment += 10;
                }
            }
            break;


            //SPECIFIC STATS
        case 2:
            for (int i = 0; i < 10; i++) {
                //MANDATORY PITCHER SELECTION
                if (i == 0) {
                    randos = random(pitchYr.size() - 1);
                    cout << "Pick one of the following pitchers to add to your team.\n";
                    for (int j = 0; j < 10; j++) {
                        objects.push_back(pitchYr[randos[j + rando_segment]]);
                    }
                    randos.clear();
                    playerAdder(objects, team, true, true);
                    cout << team[i].name << " was added to the team!\n" << endl;
                }
                else {
                    randos = random(plyrYear.size() - 1);
                    cout << "PICK YOUR NEXT PLAYER:\n";

                    for (int j = 0; j < 10; j++) {
                        objects.push_back(plyrYear[randos[j + rando_segment]]);
                    }

                    playerAdder(objects, team, false, true);
                    cout << team[i].name << " was added to the team!\n" << endl;
                    rando_segment += 10;
                }
            }
            break;
        }
        break;

        //ADVANCED SEARCH
    case 2:
        cout << "WOULD YOU LIKE THE PLAYERS STATS TO BE BASED ON THEIR OVERALL PERFORMANCE OR FROM A SPECIFIC YEAR?\n1: Overall\n2: Specific (PLEASE KNOW THE PLAYER'S NAME AND A YEAR THAT THEY PLAYED IN)\n";
        cin >> plyrStat;
        cout << endl;

        while (!gate) {
            if (plyrStat < 1 || plyrStat > 2) {
                cout << "Invalid input. please reenter.\n";
                cin >> plyrStat;
                cout << endl;
            }

            else {
                gate = true;
            }
        }

        gate = false;

        cin.ignore();

        switch (plyrStat) {

            //OVERALL STATS
        case 1:

            for (int i = 0; i < 10; i++) {

                //MANDATORY PITCHER SELECTION
                if (i == 0) {
                    cout << "PLEASE ENTER THE  FIRST AND LAST NAMES OF A PITCHER WHO YOU WOULD LIKE TO ADD TO THE TEAM (be sure to check spelling and capitalization)\n";
                    getline(cin, plyrNm);
                    cout << endl;

                    if (exist_Overall(pitchers, plyrNm) == -1) {
                        cout << "So sorry we could not find " << plyrNm << "! They might not have existed or were not a pitcher.\n";
                        i--;
                    }

                    else {
                        team.push_back(pitchers[exist_Overall(pitchers, plyrNm)]);
                        cout << plyrNm << " was added to the roster! Happy to have you!\n";
                    }
                }

                else {
                    cout << "PLEASE ENTER THE FIRST AND LAST NAME OF THE PLAYER YOU WOULD LIKE TO FIND (First letter of each is capitalized)\n";
                    getline(cin, plyrNm);
                    cout << endl;

                    if (exist_Overall(plyrs, plyrNm) == -1) {
                        cout << plyrNm << " does not exist.\n";
                        i--;
                    }

                    else {
                        team.push_back(plyrs[exist_Overall(plyrs, plyrNm)]);
                        cout << plyrNm << " was added to the roster! Happy to have you!\n";
                    }
                }
            }
            break;

            //SPECIFIC STATS
        case 2:
            for (int i = 0; i < 10; i++) {

                //MANDATORY PITCHER SELECTION
                if (i == 0) {
                    cout << "PLEASE ENTER THE  FIRST AND LAST NAMES OF A PITCHER WHO YOU WOULD LIKE TO ADD TO THE TEAM (be sure to check spelling and capitalization)\n";
                    getline(cin, plyrNm);
                    cout << endl;

                    if (exist_Specific(pitchYr, plyrNm).size() == 0) {
                        cout << "So sorry we could not find " << plyrNm << "! They might not have existed or were not a pitcher, at least not during that year.\n";
                        cout << endl;
                        i--;
                    }

                    else {
                        search_pos = exist_Specific(pitchYr, plyrNm);

                        for (int z = 0; z < search_pos.size(); z++) {
                            objects.push_back(pitchYr[search_pos[z]]);
                        }
                        //sort objects
                        playerAdder(objects, team, true, true);
                        cout << plyrNm << " from: " << team[i].year << " was added to the roster! Happy to have you!\n";
                        cout << endl;
                        search_pos.clear();
                    }
                }

                else {
                    cout << "PLEASE ENTER A PLAYERS FIRST AND LAST NAME (First letter of both names capitalized)\n";
                    getline(cin, plyrNm);
                    cout << endl;

                    if (exist_Specific(plyrYear, plyrNm).size() == 0) {
                        cout << plyrNm << " does not exist." << " Please enter in a new selection\n";
                        i--;
                    }

                    else {
                        search_pos = exist_Specific(plyrYear, plyrNm);

                        for (int z = 0; z < search_pos.size(); z++) {
                            objects.push_back(plyrYear[search_pos[z]]);
                        }

                        playerAdder(objects, team, false, true);
                        cout << plyrNm << " from " << team[i].year << " was successfully added to the roster. Happy to have you!\n" << endl;
                    }
                }
            }
            break;
        }
        break;


        // BEST/WORST STATS FOR TEAMBUILDING
    case 3:
        cout << "Do you want the best or worst?\n1:Best\n2:Worst\n";
        cin >> bw;
        cout << endl;

        while (!gate) {
            if (bw < 1 || bw > 2) {
                cout << "Invalid input. please reenter.\n";
                cin >> bw;
                cout << endl;
            }

            else {
                gate = true;
            }
        }

        gate = false;


        switch (bw) {

            //BEST
        case 1:
            cout << "Gimme the best and be rid of the rest. How do you want your stats, overall or based on the performance from a specific year?\n1:Overall\n2:Specific\n";

            cin >> plyrStat;
            cout << endl;

            while (!gate) {
                if (plyrStat < 1 || plyrStat > 2) {
                    cout << "Invalid input. Please reenter.\n";
                    cin >> plyrStat;
                    cout << endl;
                }

                else {
                    gate = true;
                }
            }

            gate = false;

            switch (plyrStat) {

                //OVERALL
            case 1:
                cout << "How many people would you like to pick from?\n";
                cin >> bwNum;
                cout << endl;

                while (!gate) {
                    if (bwNum.find_first_not_of("1234567890") != string::npos || stoi(bwNum) == 0) {
                        cout << "Invalid input. please reenter.\n";
                        cin >> bwNum;
                        cout << endl;
                    }

                    else {
                        gate = true;
                    }
                }

                gate = false;

                pickStat(plyrSortStat, pitchSortStat);

                printTime(sortedPlayerVect, sortedPitcherVect, plyrSortStat, pitchSortStat);

                for (int i = 0; i < 10; i++) {
                    //MANDATORY PITCHER SELECTION
                    if (i == 0) {
                        cout << "Pick one of the following pitchers to add to your team.\n";
                        for (int j = sortedPitcherVect.size() - 1; j > sortedPitcherVect.size() - 1 - stoi(bwNum); j--) {
                            objects.push_back(sortedPitcherVect.at(j));
                        }
                        playerAdder(objects, team, true, false);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                    else {
                        cout << "PICK YOUR NEXT PLAYER:\n";

                        for (int j = sortedPlayerVect.size() - 1; j > sortedPlayerVect.size() - 1 - stoi(bwNum); j--) {
                            objects.push_back(sortedPlayerVect.at(j));
                        }

                        playerAdder(objects, team, false, false);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                }
                break;

                //SPECIFIC
            case 2:
                cout << "How many people would you like to pick from?\n";
                cin >> bwNum;
                cout << endl;

                while (!gate) {
                    if (bwNum.find_first_not_of("1234567890") != string::npos || stoi(bwNum) == 0) {
                        cout << "Invalid input. please reenter.\n";
                        cin >> bwNum;
                        cout << endl;
                    }

                    else {
                        gate = true;
                    }
                }

                gate = false;

                pickStat(plyrSortStat, pitchSortStat);

                printTime(sortPlyrYear, sortPitchYr, plyrSortStat, pitchSortStat);

                for (int i = 0; i < 10; i++) {
                    //MANDATORY PITCHER SELECTION
                    if (i == 0) {
                        cout << "Pick one of the following pitchers to add to your team.\n";
                        for (int j = sortPitchYr.size() - 1; j > sortPitchYr.size() - 1 - stoi(bwNum); j--) {
                            objects.push_back(sortPitchYr.at(j));
                        }
                        playerAdder(objects, team, true, true);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                    else {
                        cout << "PICK YOUR NEXT PLAYER:\n";

                        for (int j = sortPlyrYear.size() - 1; j > sortPlyrYear.size() - 1 - stoi(bwNum); j--) {
                            objects.push_back(sortPlyrYear.at(j));
                        }


                        playerAdder(objects, team, false, true);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                }
                break;
            }
            break;

            //WORST
        case 2:
            cout << "Who doesnt love a underdog team? How do you want your stats: overall or specific to a year?\n1:Overall\n2:specific\n";

            cin >> plyrStat;
            cout << endl;

            while (!gate) {
                if (plyrStat < 1 || plyrStat > 2) {
                    cout << "Invalid input. please reenter.\n";
                    cin >> plyrStat;
                }

                else {
                    gate = true;
                }
            }

            gate = false;



            switch (plyrStat) {

                //OVERALL
            case 1:
                cout << "Alright how many people would you like to pick from?\n";
                cin >> bwNum;
                cout << endl;

                while (!gate) {
                    if (bwNum.find_first_not_of("1234567890") != string::npos || stoi(bwNum) == 0) {
                        cout << "Invalid input. please reenter.\n";
                        cin >> bwNum;
                    }

                    else {
                        gate = true;
                    }
                }

                gate = false;

                pickStat(plyrSortStat, pitchSortStat);

                printTime(sortedPlayerVect, sortedPitcherVect, plyrSortStat, pitchSortStat);



                for (int i = 0; i < 10; i++) {
                    //MANDATORY PITCHER SELECTION
                    if (i == 0) {
                        cout << "Pick one of the following pitchers to add to your team.\n";
                        for (int j = 0; j < stoi(bwNum); j++) {
                            objects.push_back(sortedPitcherVect.at(j));
                        }
                        playerAdder(objects, team, true, false);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                    else {
                        cout << "PICK YOUR NEXT PLAYER:\n";

                        for (int j = 0; j < stoi(bwNum); j++) {
                            objects.push_back(sortedPlayerVect.at(j));
                        }

                        playerAdder(objects, team, false, false);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                }
                break;

                //SPECIFIC
            case 2:
                cout << "Alright how many people would you like to pick from?\n";
                cin >> bwNum;
                cout << endl;

                while (!gate) {
                    if (bwNum.find_first_not_of("1234567890") != string::npos || stoi(bwNum) == 0) {
                        cout << "Invalid input. please reenter.\n";
                        cin >> bwNum;
                        cout << endl;
                    }

                    else {
                        gate = true;
                    }
                }

                gate = false;

                pickStat(plyrSortStat, pitchSortStat);

                printTime(sortPlyrYear, sortPitchYr, plyrSortStat, pitchSortStat);

                for (int i = 0; i < 10; i++) {
                    //MANDATORY PITCHER SELECTION
                    if (i == 0) {
                        cout << "Pick one of the following pitchers to add to your team.\n";

                        for (int j = 0; j < stoi(bwNum); j++) {
                            objects.push_back(sortPitchYr.at(j));
                        }

                        playerAdder(objects, team, true, true);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                    else {
                        cout << "PICK YOUR NEXT PLAYER:\n";

                        for (int j = 0; j < stoi(bwNum); j++) {
                            objects.push_back(sortPlyrYear.at(j));
                        }

                        playerAdder(objects, team, false, true);
                        cout << team[i].name << " was added to the team!\n" << endl;
                    }
                }
                break;
            }
            break;
        }
        break;
    }
    cout << endl;
}


int main()
{
    int restart = 1;
    while (restart == 1) {
        //INSTANTIATE VECTORS AND VARIABLES

        vector<Player> pitchers; //Holds all pitchers, so that they can be selected individually
        vector<Player> pitcherYears; //Holds all pitchers individual pitching years
        vector<Player> playersYears;  //Holds all players individual batting years
        vector<Player> players;  //Holds all players overall stats, batting and pitching if they pitched
        unordered_map<string, int> indexMap;  //Holds map of player ids to ints for constant time access to overall statistics

        //LOAD FILES AND IMPORT INFORMATION INTO VECTORS

        openFile("People.csv", players, playersYears, pitchers, pitcherYears, indexMap);
        openFile("Batting.csv", players, playersYears, pitchers, pitcherYears, indexMap);
        openFile("Pitching.csv", players, playersYears, pitchers, pitcherYears, indexMap);


        //MENU SYSTEM

        int choice = 0;
        string name1;
        string name2;
        vector<Player> team1;
        vector<Player> team2;

        //cout << "All files have completed loading!" << endl;


        cout << "Welcome to T.A.B.S., the Totally Accurate Baseball Simulator" << endl;
        cout << "We will simulate the outcome of a baseball game between two teams chosen by YOU!" << endl;
        cout << "Begin by entering the name of the first team: " << endl;
        getline(cin, name1);
        cout << "Great! Now enter the name of the second team: " << endl;
        getline(cin, name2);

        //   for (int i = 0; i < 10; i++) {
        //     cout << playersYears[i].name << "\n";
        //   }

        //for (int i = 0; i < pitcherYears.size(); i++) {
        //    cout << pitcherYears.at(i).name << " G: " << pitcherYears.at(i).gamesPlayed << " ER: " << pitcherYears.at(i).ER << " IP: " << pitcherYears.at(i).IP << endl;
        //}

        teamBuilder(pitchers, pitcherYears, playersYears, players, team1, name1);
        teamBuilder(pitchers, pitcherYears, playersYears, players, team2, name2);

        cout << name1 << "'s lineup tonight features:\n";
        for (int i = 0; i < team1.size(); i++) {
            cout << i << ": " << team1[i].name << endl;
        }

        cout << endl;

        cout << name2 << "'s lineup tonight feautures:\n";
        for (int i = 0; i < team2.size(); i++) {
            cout << i << ": " << team2[i].name << endl;
        }


        cout << endl;
        string numGames;
        cout << "How many games would you like to simulate?" << endl;
        cin >> numGames;
        bool check = false;
        while (check == false) {
            if (numGames.find_first_not_of("1234567890") != string::npos || stoi(numGames) == 0) {
                cout << "Invalid input. please reenter.\n";
                cin >> numGames;
                cout << endl;
            }
            else {
                check = true;
            }
        }

        int team1wins = 0;
        int team2wins = 0;

        for (int i = 0; i < stoi(numGames); i++) {
            pair<int, int> pair = calculateResults(team1, team2);
            cout << endl;
            cout << "The match results were: " << endl;
            cout << name1 << ": " << pair.first << endl;
            cout << name2 << ": " << pair.second << endl;
            if (pair.first > pair.second) {
                team1wins++;
            }
            else {
                team2wins++;
            }
        }
        cout << endl << name1 << "'s total wins: " << team1wins << endl << name2 << "'s total wins: " << team2wins << endl << endl;
        if (team1wins > team2wins) {
            cout << name1 << " was the better team! Get squashed like a bug " << name2 << "." << endl;
        }
        else {
            cout << name2 << " was the better team! Get squashed like a bug " << name1 << "." << endl;
        }
        
        cout << endl << "Do you want to play again?\n1. Of course!\n2. Exit, get me out of here!" << endl;
        cin >> restart;

        while (restart != 1 && restart != 2) {
            cout << "Please reenter a valid number." << endl;
            cin >> restart;
        }

        if (restart == 1) {
            pitchers.clear();
            players.clear();
            playersYears.clear();
            pitcherYears.clear();
            team1.clear();
            team2.clear();
            cin.ignore();
        }
    }
    cout << "Thanks for playing!" << endl;
}
