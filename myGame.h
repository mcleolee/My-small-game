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
        int printHintForUnreadableCode();
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
        int getDefence();
        bool isAlive();
        int increaseDefForOneRound();
        int decreaseDefForOneRound();
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

inline int text::printHintForUnreadableCode(){
    cout << "\t如果你现在是用的 Windows 的终端打开的这个程序\n\t那么你可以新开一个命令提示行或者终端";
    cout << "然后输入chcp 65001，回车，然后把exe文件拖进终端，回车就可以运行啦" << endl;
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

inline int character::getDefence(){
    return defence_;
}

inline int character::increaseDefForOneRound(){
    defence_ += 5;
    return defence_;
}

inline int character::decreaseDefForOneRound(){
    defence_ -= 5;
    return defence_;
}
#endif 
//MYGAME
