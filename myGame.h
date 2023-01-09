#ifndef MYGAME
#define MYGAME

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class text{
    public:
        int printHello();
};

class func{
    public:
        int clear();
        int press_any_key_to_continue();
};

class character{
    public:
        // 构造函数
        character(int hp, int attack, int defense):hp_(hp), attack_(attack), defence_(defense){}

        int attack(character &enemy);
        int getHP();
        bool isAlive();
    private:
    // 生命，攻击力，防御力属性
        int hp_;
        int attack_;
        int defence_;
};





inline int text::printHello() {
    cout << "\n\t欢迎来我的游戏！\n";
    return 0;
}

inline int func::clear(){
    system("clear");
    return 0;
}

inline int func::press_any_key_to_continue()
{
    cout << "\n\n\t- 按任意键继续 -" << endl;
    getchar();
    return 0;
}

inline int character::attack(character &enemy){
    int damage = attack_ - enemy.defence_;
    // 可正可负，要是护甲太高了就打不动
    // 造成的伤害是 你的攻击 - 敌人的护甲
    if(damage > 0)
        enemy.hp_ -= damage;
    return damage;

}

inline int character::getHP() {
    return hp_;
}

inline bool character::isAlive(){
    if(hp_ > 0)
        return true;
    else
        return false;
}

#endif 
//MYGAME
