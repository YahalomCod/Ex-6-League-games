#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include "team.hpp"


using namespace std;
class League{
    private:
        vector<Team> *league = new vector<Team>;
        int total_wins = 0;
        bool intialized = 0;
    public:
        League(vector <Team>&);
        League();
        League(int);
        bool isInitliazed(){return this->intialized;}
        void addTeam(Team&);
        Team& getTeam(unsigned int);
        void startGame();
        void runTournament(bool);
        void sort();
        friend ostream & operator<< (ostream& output, League& league);
        void addWin();
        void topTeams(int);
        Team longestLose();
        Team longestWin();
        Team mostHomeLose();
        Team mostOutWon();
        int positivePointScore();
        ~League();
};