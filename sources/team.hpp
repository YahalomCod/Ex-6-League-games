#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <unordered_map>
#include <limits>
#include <bits/stdc++.h>

#define MAX1 = 1000;

using namespace std;
class Team{
    
    private:
    
        string name;
        float talent;
        unsigned int victories = 0;
        int score_diff = 0;
        int longest_win = INT_MIN;
        int curr_win_strike = 0;
        int longest_lose = INT_MIN;
        int curr_lose_strike = 0;
        unsigned int home_won = 0;
        unsigned int out_won = 0;
        bool won_last_game = true;

    public:

        Team(string name, float talent);
        Team(string name);
        Team();
        ~Team();
        void restartTeam()&;
        string getName();
        float getTalent()const;
        void addWin(bool home);
        void addLose();
        void update_score(int score);
        unsigned int getVictories()const;
        int getScoreDiff()const;
        int getLongestWins();
        int getLongestloses();
        unsigned int homeWon()const;
        unsigned int outWon()const;
        bool getLastWin();
        bool operator < (Team&)const;
        friend ostream & operator<< (ostream& out, Team& team);

};