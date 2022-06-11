#include<iostream>
#include <string>
#include <vector>
#include "league.hpp"
#include "team.hpp"
#include "game.hpp"
#include<iterator>
#include <list>
#include <bits/stdc++.h>

using namespace std; 
#define HALF_TOUR = 19;

vector<string> names = {
"Atlanta Hawks",
"Boston Celtics",
"Brooklyn Nets",
"Charlotte Hornets",
"Chicago Bulls",
"Cleveland Cavaliers",
"Dallas Mavericks",
"Denver Nuggets",
"Detroit Pistons",
"Golden State Warriors",
"Houston Rockets",
"Indiana Pacers",
"Los Angeles Clippers",
"Los Angeles Lakers",
"Memphis Grizzlies",
"Miami Heat",
"Milwaukee Bucks",
"Minnesota Timberwolves",
"New Orleans Pelicans",
"New York Knicks",
"Oklahoma City Thunder",
"Orlando Magic",
"Philadelphia" ,
"Phoenix Suns",
"Portland Trail Blazers",
"Sacramento Kings",
"San Antonio Spurs",
"Toronto Raptors",
"Utah Jazz",
"Washington Wizards"
};

League::League(){
    for (size_t i = 0; i < 20; i++){
        Team *curr = new Team(names.at(i));
        this->league->push_back(*curr);
    }       
    this->intialized = true;
}

League::League(int a){
    this->league = new vector<Team>;
}

League::League(vector<Team> & league){
    if(league.size() > 20){
        throw ("Too many team are in this league need to be 20");
    }
    this->league = &league;
    int i =0;
    while(this->league->size() < 20){
        Team *curr = new Team(names.at((++i)%30));
        this->addTeam(*curr);
    }           
    this->intialized = true;
}

void League::addTeam(Team &team){
    if(this->league->size() >= 20) { throw("can't add more teams");}
    bool flag = true;
    for (size_t i = 0; i < this->league->size(); i++){
            if(this->league->at(i).getName() == team.getName()){
                flag = false;
                break;
            }            
        }
    if( flag){ this->league->push_back(team); }
    else{throw("can't add team with the same name");}
}

Team& League::getTeam(unsigned int loc){
    return this->league->at(loc);
}

void League::startGame(){
    if(this->league->size() > 20){ throw invalid_argument ("must be 20 teams in the league before starting tournament"); }
    if(this->getTeam(0).getVictories() != 0){
        for (size_t i = 0; i < 20; i++)
        {
            this->getTeam(i).restartTeam();
        }
    }
    this->runTournament(true);
    this->runTournament(false);
}

void League::runTournament(bool t){
    deque<unsigned int> groupA;
    deque<unsigned int> groupB;
    vector<unsigned int> vec;
    for (size_t i = 0; i < 20; i++) {
        vec.push_back(i);
    }
    for (size_t i = 1; i < 10; i++){
        groupA.push_back(i);
    }
    for (size_t i = 10; i < 20; i++){
        groupB.push_back(i);
    }    
    unsigned int x = 0;
    vector<vector<vector<unsigned int>>> rounds;
    for (int i = 1; i < 20; i++) {
        vector<vector<unsigned int>> roun;
        for (int j = 0; j < 10; j++) {
            unsigned int first;
            if (j == 0){
                first = x;
            }
            else{
                first = groupA.front();
            }
            unsigned int sec = groupB.back();
            vector<unsigned int> a;
            a.push_back(first);
            a.push_back(sec);
            roun.push_back(a);
            groupB.pop_back();
            if (j != 0){
                groupA.pop_front();
                groupA.push_back(first); 
            }
            
            groupB.push_front(sec);
            if(t){
                Game *game = new Game(this->getTeam(first), this->getTeam(sec));
            }
            else{
                Game *game = new Game(this->getTeam(sec), this->getTeam(first));
            }
        }
        unsigned int first = groupA.front();
        unsigned int sec = groupB.front();
        groupA.pop_front();
        groupB.pop_front();
        groupA.push_back(sec);
        groupB.push_back(first);
        rounds.push_back(roun);
    }
}

void League::sort(){ std::sort(this->league->begin(), this->league->end());}

ostream & operator<< (ostream & out, League& league){
    if(league.intialized){
        for (unsigned int i = 0; i < 20; i++){
            Team t = league.getTeam(i);
            out << t;
        }
    }
    return out;
}

void League::topTeams(int n){
    this->sort();
    cout << n << " Top Teams:" <<endl;
    for (size_t i = 0; i < n; i++){
        cout << (i+1) << " Place"  <<": " <<this->league->at(i).getName()<< endl;
    }
}

Team League::longestLose(){
    int longest_strike = 0;
    Team loser;
    for(auto t: *this->league){
        if(t.getLongestloses() > longest_strike){
            longest_strike = t.getLongestloses();
            loser = t;
        }
    }
    cout << loser.getName() << " losing strike of: "<< longest_strike<<endl;
    return loser;
}

Team League::longestWin(){
    int longest_strike = 0;
    Team winner;
    for(auto t: *this->league){
        if(t.getLongestWins() > longest_strike){
            longest_strike = t.getLongestloses();
            winner = t;
        }
    }
    cout << winner.getName() << " Winning strike of: "<< longest_strike<<endl;
    return winner;
}

int League::positivePointScore(){
    int count = 0;
    for(auto t : *this->league){
        if(t.getScoreDiff() > 0){ count++;}
    }
    return count;
}

Team League::mostHomeLose(){
    unsigned int home_lost = 0;
    Team ans;
    for(auto team : *this->league){
        if(19 - team.homeWon() > home_lost){
            home_lost = 19 - team.homeWon();
            ans = team;
        }
    }
    cout << ans.getName() << " Lost in home games " << home_lost << " times"<<endl;
    return ans;
}

Team League::mostOutWon(){
    unsigned int out_won = 0;
    Team ans;
    for(auto team : *this->league){
        if(team.outWon() > out_won){
            out_won = team.outWon();
            ans = team;
        }
    }
    cout << ans.getName() << " Won in out games " << out_won << " times"<<endl;
    return ans;
}

League::~League(){
    delete(this->league);
}