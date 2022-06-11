#pragma once

#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include "team.hpp"
#include <unordered_map>

using namespace std;
class Game{
    private:
        Team winner;
    public:
        Game(Team&, Team&);
};