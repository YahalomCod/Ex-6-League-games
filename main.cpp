#include<iostream>
#include <string>
#include <vector>
#include "sources/league.cpp"
#include "sources/team.cpp"
#include "sources/game.cpp"
#include<iterator>
#include <list>
#include <bits/stdc++.h>

using namespace std; 

int main() {
    int flag = 0;
    League *league;
    int top_teams;
    vector<Team> teams;
    string name;
    while(flag != -1){
        cout << endl << "Options to build your league:" << endl;
        cout << "1: build random teams to be in the league" << endl;
        cout << "2: build teams" << endl;
        cout << "3: build the rest of the teams randomly" << endl <<endl;
        cin >> flag;
        switch(flag){
             case 1:{
                league = new League();
                flag = -1;
                break;
                }
            case 2:{
                cout <<  endl;
                cout << "Please enter the team name" << endl;
                cin >> name;
                try{
                    Team *curr = new Team(name);
                    bool canAdd = true;
                    for (size_t i = 0; i < teams.size() && canAdd; i++){
                        if(teams.at(i).getName() == name){
                            canAdd = false;
                        }            
                    }
                    if( canAdd){ teams.push_back(*curr); }
                    else{ cout << "Can't add team who is already playing in this league" << endl;}
                }
                catch(const exception& e){ 
                    cout <<"Invalid name, try again" << endl; }
                break;
                }
            case 3:{
                league = new League(teams);
                flag = -1;
                break;
            }
             default:
                cout << "Please choose 1 to 3" << endl;
                break;
        }
    }
    flag = 0;
    while (flag != -1) {
        cout << endl << "Option to do with the league:" << endl;
        cout << "1: start tournament" << endl;
        cout << "2: sort league" << endl;
        cout << "3: show top team" << endl;
        cout << "4: show who lost most in a row" << endl;
        cout << "5: show who won most in a row" << endl;
        cout << "6: show who lost most in a home games" << endl;
        cout << "7: show who won most in a out games" << endl;
        cout << "8: show tournament results" <<endl;
        cout << "-1: exit" << endl;
        cin >> flag;
        switch (flag) {
            case 1:{
                cout << "Tournament started" << endl;
                league->startGame();
                cout << "Tournament ended" << endl;
                break;
            }
            case 2:{
                league->sort();
                break;
            }
            case 3:{
                cout << "How many top teams do you want to see?"<<endl;
                cin >> top_teams;
                league->topTeams(top_teams);
                break;
            }
            case 4:{
                league->longestLose();
                break;
            }
            case 5:{
                league->longestWin();
                break;
            }
            case 6:{
                league->mostHomeLose();
                break;
            }
            case 7:{
                league->mostOutWon();
                break;
            }
            
            case 8:{
                cout << *league;
                break;
            }
            case -1:{
                break;
            }
            default:
                cout << "Please choose -1 or 1 to 10" << endl;
                break;
        }
    }
    return 0;
}