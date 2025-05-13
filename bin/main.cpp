#include <iostream>

#include <Manager/Manager.hpp>

int main() {
    BattleShipGame::Manager manager = BattleShipGame::Manager();

    while (manager.Run()) {}
    
    return 0;
}