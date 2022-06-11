#include <iostream>
#include "doctest.h"
#include <stdexcept>
#include "sources/league.cpp"
#include "sources/team.cpp"
#include "sources/game.cpp"
using namespace std;
#include <vector>
#include <string>


TEST_CASE("Good input") {
    League league;
    league.startGame();
    int totalGamesWon = 0;
    int totalGamesLost = 0;
    int totalDiff = 0;
    for(size_t i = 0; i < 20; i++){
        Team curr = league.getTeam(i);
        totalGamesWon += curr.getVictories();
        CHECK(curr.getVictories() == curr.homeWon() + curr.outWon());
        totalGamesLost += 38 - curr.getVictories();
        totalDiff += curr.getScoreDiff();
    }
    CHECK(totalGamesLost == totalGamesWon);
    CHECK(totalGamesLost + totalGamesWon == 760);
    CHECK(totalDiff == 0);
}

TEST_CASE("Bad input") {
    CHECK_THROWS(Team("0"));
    CHECK_THROWS(Team("! me"));
    CHECK_THROWS(Team("   "));
    Team *t = new Team("ME");
    League *l = new League;// building complete league
    League l2(0);//building empty league
    l2.addTeam(*t);
    CHECK_THROWS(l2.addTeam(*t));
    CHECK_THROWS(l->addTeam(*t));
}