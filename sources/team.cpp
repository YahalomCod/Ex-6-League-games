#include<iostream>
#include <string>
#include <vector>
#include "team.hpp"
#include<iterator>
#include <list>
#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <stdio.h>
#include <stdlib.h>
using namespace std; 

void check_input(string name){
    int countSpace = 0;
    bool flag = true;
    for(size_t i = 0; i < name.size(); i++){
        if(name.at(i) <= 'Z' && name.at(i) >= 'A'){}
        else if(name.at(i) <= 'z' && name.at(i) >= 'a'){}
        else if(name.at(i) == ' '){ countSpace++;}
        else{ flag = false;}
    }
    if(!flag){throw invalid_argument("Name can't be with just spaces");}
    if(countSpace == name.size()){
        throw invalid_argument("Name can't be with just spaces");
    }
}

Team::Team(){this->name = "";}

Team::Team(string name, float talent){
    check_input(name);
    this->name = move(name);
    this->talent = talent;
}

Team::Team(string name){
    check_input(name);

    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, 1000);
    this->name = move(name);
    this->talent = distrib(gen);
    this->talent = this->talent / 1000; 
}

string Team::getName(){ return this->name;}

float Team::getTalent()const{ return this->talent;}

void Team::addWin(bool home){
    if(home){
        this->home_won++;
    }
    else{
        this->out_won++;
    }
    this->victories ++;
    this->curr_lose_strike = 0;
    if(this->won_last_game){
        this->curr_win_strike ++;
        if(this->longest_win < this->curr_win_strike){
            this->longest_win = this->curr_win_strike;
        }
    }
    else{
        this->won_last_game = true;
    }
}

void Team::addLose(){
    this->curr_win_strike = 0;
    if(!this->won_last_game){
        this->curr_lose_strike ++;
        if(this->longest_lose < this->curr_lose_strike){
            this->longest_lose = this->curr_lose_strike;
        }
    }
    else{
        this->won_last_game = false;
    }
}

int Team::getLongestWins(){ return this->longest_win;}

int Team::getLongestloses(){ return this->longest_lose;}

void Team::update_score(int score){this->score_diff += score;}

unsigned int Team::getVictories() const{return this->victories;}

int Team::getScoreDiff() const{return this->score_diff;}

bool Team::operator < (Team& t)const{
    if(this->getVictories() < t.getVictories()){
        return false;
    }
    if(this->getVictories() > t.getVictories()){
        return true;
    }
    //both teams have same win amount
    if(this->getScoreDiff() < t.getScoreDiff()){
        return false;
    }
    if(this->getScoreDiff() > t.getScoreDiff()){
            return true;
    }
    //both teams also have the same score difference
    return this->talent > t.talent;
}

ostream & operator<< (ostream& out, Team& team){
    out << team.getName()<<" Won: " << team.getVictories() << " games,\tScore difference: " << team.getScoreDiff()<<",\tSkill: " << team.talent ;
    out << "  home won: " << team.homeWon() << ", out won: " << team.outWon() << endl;
    return out;
}

unsigned int Team::homeWon()const{return this->home_won;}

unsigned int Team::outWon()const{return this->out_won;}

void Team::restartTeam()&{
        this->victories = 0;
        this->score_diff = 0;
        this->longest_win = INT_MIN;
        this->curr_win_strike = 0;
        this->longest_lose = INT_MIN;
        this->curr_lose_strike = 0;
        this->home_won = 0;
        this->out_won = 0;
        this->won_last_game = true;
}

Team::~Team(){}
