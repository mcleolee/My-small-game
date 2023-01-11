#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "myGame.h"
// #include <SFML/Graghcs.hpp>

#define log(x) std::cout << "\n\t" << x << std::endl




int main() {
    // -- 初始化 --
    // system("iconv -f utf-8 -t gbk main.exe > main.gbk.exe"); // 不知道能不能行 // 不能行
    text text;
    func func;
    character player(10,2,2);
    character enemy(10,3,0);
    battle battle;

    // -- 判断系统 --
    func.displayWhichSystem(func.whichSystem());
    func.press_any_key_to_continue();

    func.gameLoading();
    func.gameStart(text);
    func.clear(func.systemNum);

    // 战斗环节
    battle.battleField(player, enemy, func);
    
    // -- 游戏结束 --
    if(player.isAlive()){
        log("恭喜你获胜了！");
    }else{
        log("很拉胯，你失败了...");
    }
    return 0;
}
