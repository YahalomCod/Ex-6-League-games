#include<iostream>
#include <string>
#include <vector>
#include "game.hpp"
#include<iterator>
#include <list>
#include <bits/stdc++.h>
#include <random>
#include <chrono>

using namespace std; 


Game::Game(Team &home, Team &out){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    normal_distribution<float> distribution (70,15);
    default_random_engine generator (seed);
    int score_home = distribution(generator) + (home.getTalent() * 10);
    int score_out = distribution(generator) + (out.getTalent() * 10);
    if(home.getTalent() >= 0.95){
        score_home ++;
    }
    if(out.getTalent() >= 0.95){
        score_out ++;
    }
    if(score_home < 55){
        score_home = 55;
    }
    if(score_home > score_out){
        this->winner = home;
        home.addWin(true);
        out.addLose();
    }
    else if(score_home < score_out){
        this->winner = out;
        out.addWin(false);
        home.addLose();
    }
    else{//if they have the same score
        if(home.getTalent() > out.getTalent()){
            home.addWin(true);
            out.addLose();
            this->winner = home;
        }
        else{
            out.addWin(false);
            home.addLose();
            this->winner = out;
        }
    }
    home.update_score(score_home - score_out);
    out.update_score(score_out - score_home);
}

