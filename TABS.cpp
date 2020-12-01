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


   /*      RUN ME FIRST BRO JUST RUN ME FIRST THEN ERASE ME TO FIX ERASE ME AND THE ONE BEFORE MAIN ERASE ME AND THE ONE BEFORE MAIN THERE ARE 3 TO ERASE



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

void openFile(string filename, vector<Player>& vect, vector<Player>& vectYears, unordered_map<string, int>& map) {
    ifstream workFile;
    workFile.open("C:\\Users\\ian\\Desktop\\TABS\\csvs\\" + filename);
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



//BUILDS THE VECTOR FULL OF PLAYERS FOR A TEAM

void teamBuilder(vector<pair<string, vector<Player>>> pos, vector<Player> plyrYear, vector<Player> plyrs, vector<Player> &team, string teamName) {
    int buildQuality = 0;
    int plyrStat = 0;
    int plyrPos = 0;
    string plyrNm;
    int yr;
    int bw;
    int bwNum;
    vector<Player> objects;
    cout << "WELCOME TO THE TEAMBUILDING ASPECT OF TABS ALSO KNOWN AS TOTALLY ACCURATE BASEBALL SIMULATOR, no inspo taken from the other TABS, TOTALLY ACCURATE BATTLE SIMULATOR on steam.......... :]\n";
    cout << "HOW WOULD YOU LIKE TO PICK THIS TEAM?\n1: GIMME RANDIES\n2: HEH...... YUGI I ALREADY KNOW HOW TO WIN....;) it's advanced search...\n3: BEST/WORST\n";
    cin >> buildQuality;

    switch (buildQuality) {

    //RANDOMS
    case 1:
        cout << "randies it is lol good luck\nAlright next point of contention is do you want the player overall stats or a very specific set of skills that will find you and play for you?\n1:overall\n2: the accuaracy of a dynamax move";
        cin >> plyrStat;

        switch (plyrStat) {


        //OVERALL STATS
        case 1:
            for (int i = 0; i < 8; i++) {

                cout << "OverALL k. pick a position\n1:Catcher\n2:LF\n3:CF\n4:RF\n5:TB\n6:FB\n7:SB\n8:HB\n";
                cin >> plyrPos;
                //sort function (pos, plyrs, &objects, plyrPos) not overly certain what EXACTLY you all will need for the sort funcs
                cout << "ight now choose wisely\n";
                //let them pick and add to the team and then clear the objects vector
            }
            break;


        //SPECIFIC STATS
        case 2:
            for (int i = 0; i < 8; i++) {
                cout << "details - Sherlock Holmes 221BC\npick a position\n1:Catcher\n2:LF\n3:CF\n4:RF\n5:TB\n6:FB\n7:SB\n8:HB\n";
                cin >> plyrPos;


                if (plyrPos <= 1 || plyrPos > 9) {
                    cout << "enter a valid input\n";
                    cin >> plyrPos;
                    i--;
                    continue;
                }


                //sort function (pos, plyrs, &objects, plyrPos)
                cout << "its dangerous to go alone take one of these Joe Schmoes\n";
                //print out the peeps
            }
            break;


        default:
            cout << "lol silly, reenter uwu\n";
            cin >> plyrStat;
        }
        break;

    
    //HE KNOWS TOO MUCH CUZ HE WANNA SEARCH PEOPLE
    case 2:
        cout << "okay, but first do you want to do a specific player with stats from specific years/teams or just overall stats?\n1:specific\n2: overall\n";
        cin >> plyrStat;

        switch (plyrStat) {

        //SPECIFIC STATS
        case 1:
            for (int i = 0; i < 10; i++) {
                cout << "okay we need a name\n";
                cin >> plyrNm;
                cout << "and now for a year that they played\n";
                cin >> yr;
                //find the player and add it then clear the objects vector, dunno if we need position played for this
                //maybe use a generic search func and if not found i.e NULL Player obj then decrement i and do not add anything
            }
            break;

        //OVERALL STATS
        case 2:
            for (int i = 0; i < 10; i++) {
                cout << "NAME PLEASE\n";
                cin >> plyrNm;
                //search func call
            }
            break;

        //INVALID INPUT
        default:
            cout << "please enter a valid option\n";
            cin >> plyrStat;
        }
        break;


    // BEST/WORST STATS FOR TEAMBUILDING
    case 3:
        cout << "Do you want the best or worst?\n1:Best\n2:Worst";
        cin >> bw;

        switch(bw){

        //BEST
        case 1:
            cout << "Gimme the best and be rid of the rest. How do you want your stats, overall or specific?\n1:Overall\n2:specific\n";

            cin >> plyrStat;

            switch (plyrStat) {

                //OVERALL
            case 1:
                cout << "Alright how many people would you like to pick from?\n";
                cin >> bwNum;

                for (int i = 0;i < 10; i++) {
                    cout << "pick a position to fill.\n1:Catcher\n2:LF\n3:CF\n4:RF\n5:TB\n6:FB\n7:SB\n8:HB\n";
                    cin >> plyrPos;
                    //sort func to get the bwNum number of players in plyrPos position
                }
                break;

            //SPECIFIC
            case 2:
                cout << "Alright how many people would you like to pick from?\n";
                cin >> bwNum;

                for (int i = 0;i < 10; i++) {
                    cout << "pick a position to fill.\n1:Catcher\n2:LF\n3:CF\n4:RF\n5:TB\n6:FB\n7:SB\n8:HB\n";
                    cin >> plyrPos;
                    //sort func to get the bwNum number of players in plyrPos position
                }
                break;

            //INVALID INPUT
            default:
                cout << "invalid input\n";
                cin >> plyrStat;
            }
            break;

        //WORST
        case 2:
            cout << "Who doesn't love a underdog team? How do you want your stats, overall or specific?\n1:Overall\n2:specific\n";

            cin >> plyrStat;

            switch (plyrStat) {

                //OVERALL
            case 1:
                cout << "Alright how many people would you like to pick from?\n";
                cin >> bwNum;

                for (int i = 0;i < 10; i++) {
                    cout << "pick a position to fill.\n1:Catcher\n2:LF\n3:CF\n4:RF\n5:TB\n6:FB\n7:SB\n8:HB\n";
                    cin >> plyrPos;
                    //sort func to get the bwNum number of players in plyrPos position
                }
                break;

                //SPECIFIC
            case 2:
                cout << "Alright how many people would you like to pick from?\n";
                cin >> bwNum;

                for (int i = 0;i < 10; i++) {
                    cout << "pick a position to fill.\n1:Catcher\n2:LF\n3:CF\n4:RF\n5:TB\n6:FB\n7:SB\n8:HB\n";
                    cin >> plyrPos;
                    //sort func to get the bwNum number of players in plyrPos position
                }
                break;

            //INVALID INPUT
            default:
                cout << "invalid input\n";
                cin >> plyrStat;
            }
        break;
        }
    break;


    //INVALID INPUT
    default:
        cout << "lol silly, reenter uwu\n";
        cin >> buildQuality;
    }

}




    */  //ERASE ME TO FIX ERASE ME TO FIX AS WELL AS THE ONE BELOW ME ASKING TO BE ERASED




int main()
{



    /*   ERASE MEEE TO FIX MAIN ERASE ME TO FIX MAIN
    


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

    // teamBuilder(positions, playersYears, players, team1, name1);
    // teamBuilder(positions, playersYears, players, team2, name2);

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

























    






     cout << "THERE IS NO TABS, GET NAKED\n";
}
