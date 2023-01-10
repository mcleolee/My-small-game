#ifndef MYGAME
#define MYGAME

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#define log(x) std::cout << "\n\t" << x << std::endl

using namespace std;

class text{
    public:
        int printHello();
        int printHintForUnreadableCode();
};

class func{
    public:
        int clear(int systemNum);
        int press_any_key_to_continue();
        float randomNumGenerator();
        int whichSystem();
        int displayWhichSystem(int whichSystem);
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

        int enemyRandomChoice(func& func);
    private:
    // 生命，攻击力，防御力属性
        int hp_;
        int attack_;
        int defence_;
};



// -------------------- text --------------------

inline int text::printHello() {
    cout << "\n\t欢迎来我的游戏！\n";
    return 0;
}

inline int text::printHintForUnreadableCode(){
    cout << "\t如果你现在是用的 Windows 的终端打开的这个程序\n\t那么你可以新开一个命令提示行或者终端";
    cout << "然后输入chcp 65001，回车，然后把exe文件拖进终端，回车就可以运行啦" << endl;
    return 0;
}


// -------------------- func --------------------

inline int func::clear(int systemNum){
    if(systemNum == 1)
        system("cls");
    else if (systemNum == 2)
        system("clear");
    else
        log("no clear in macOS");
    
    return 0;
}

inline int func::press_any_key_to_continue()
{
    cout << "\n\n\t- 按任意键继续 -" << endl;
    getchar();
    return 0;
}

inline float func::randomNumGenerator(){
    std::mt19937 randomNumGenerator; // 创建一个随机数生成器
    randomNumGenerator.seed(std::random_device()()); // 设置随机数种子
    std::uniform_real_distribution<double> dist(0,1);  // 创建一个随机数分布
    
    // 生成并返回一个随机数
    return dist(randomNumGenerator);
}

inline int func::whichSystem(){
    #ifdef _WIN32
    return 1;
    #endif

    #ifdef __linux__
    return 2;
    #endif

    #ifdef __APPLE__
    return 3;
    #endif
}

inline int func::displayWhichSystem(int whichSystem){
    switch (whichSystem) {
    case 1: log("YOUR SYSTEM IS WINDOWS");return 1;break;
    case 2: log("YOUR SYSTEM IS LINUX");return 2;break;
    case 3: log("YOUR SYSTEM IS macOS");return 3;break;
    default:log("CAN NOT RECOGNIZE YOUR SYSTEM");return 0;
    }
}


// -------------------- character --------------------

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

inline int character::enemyRandomChoice(func& func){
    // 这里意思是，40%几率攻击，60%几率防御
    int rNum = 100*func.randomNumGenerator();
    if(rNum < 40){
        // attack
    }else{
        // defence
    }
    return rNum;
}
















#endif 
//MYGAME
