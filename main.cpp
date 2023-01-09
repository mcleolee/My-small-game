#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "myGame.h"

#define log(x) std::cout << "\n\t" << x << std::endl

using namespace std;



void gameLoading(func& func){
    // 啥呗进度条
    func.clear();
    for(int i=0; i<1; i++)
    {
        func.clear();
        log("正在加载.");
        sleep(1);
        func.clear();
        log("正在加载..");
        sleep(1);
        func.clear();
        log("正在加载...");
        sleep(1);
    }
    sleep(1);
}

void gameStart(func& func, text& gameText){
    func.clear();
    gameText.printHello();
    func.press_any_key_to_continue();
}


int main() {
    // -- 初始化 --
    text gameText;
    func func;
    character player(10,2,1);
    character enemy(10,3,1);

    gameLoading(func);
    gameStart(func, gameText);

    while (player.isAlive() && enemy.isAlive()) {
        cout << "your hp is:" << player.getHP() << endl;
        cout << "your enemy's hp is:" << enemy.getHP() << endl;
        cout << "\nwhat's your choice!!!\n\t1.attack\t2.defence\n" << endl;

        int playerChoice;
        cin >> playerChoice;

        switch (playerChoice) {
        case 1:
            log("you are attacking your enemy!!");
            // player.attack(enemy);
            sleep(1);
            cout << "你对敌方造成了" << player.attack(enemy) << "点伤害" << endl;
            break;
        case 2:
            log("your enemy is going to attack you! DEFENCE!");
            sleep(1);
            player.increaseDefForOneRound();
            cout << "你的防御力提高到了" << player.getDefence() + 5 << "点" << endl;
            // cout << "你的防御力提高到了" << player.getDefence() + 5 << "点" << endl;
            sleep(1);
            cout << "敌方实际对你造成了" << enemy.attack(player) << "点伤害!" << endl;
            player.decreaseDefForOneRound();
            break;
        default:
            log("输数字，ok？");
            break;
        }
    }

    // -- 游戏结束 --
    if(player.isAlive()){
        log("恭喜你获胜了！");
    }else{
        log("很拉胯，你失败了...");
    }
    return 0;
}
