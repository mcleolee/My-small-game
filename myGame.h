#ifndef MYGAME
#define MYGAME

#include <iostream>
#include <ctime>
#include <type_traits>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#ifdef _WIN32
    #include <Windows.h>
#elif __linux__
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#define log(x) std::cout << "\n\t" << x << std::endl
using std::cout;
using std::endl;
using std::cin;


class text{
    public:
        int const printHello();
        int printHintForUnreadableCode();
        void static alignCenterLinux(std::string text);
};

class func:text{
    public:
        int const systemNum = whichSystem();

        int clear(int systemNum);
        int press_any_key_to_continue();
        void gameLoading();
        void gameStart(text& gameText);
        float randomNumGenerator();
        int whichSystem();
        int displayWhichSystem(int whichSystem);

        void sleeep(int systemNum);
};

class character{
    public:
        // 构造函数
        character(int hp, int attack, int defense):hp_(hp), attack_(attack), defence_(defense){}

        int attack(character &attackTarget);
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

class battle{
    public:
        int battleField(character& player, character& enemy, func& func);

        int playerRound(character& player, character& enemy, func& func);
        int enemyRound(character& player, character& enemy);
};



// -------------------- text --------------------

inline int const text::printHello() {
    cout << "\n\t欢迎来我的游戏！\n";
    return 0;
}

inline int text::printHintForUnreadableCode(){
    cout << "\t如果你现在是用的 Windows 的终端打开的这个程序\n\t那么你可以新开一个命令提示行或者终端";
    cout << "然后输入chcp 65001，回车，然后把exe文件拖进终端，回车就可以运行啦" << endl;
    return 0;
}

inline void text::alignCenterLinux(std::string text){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int consoleWidth = w.ws_col;

    // output
    // std::string text = "Hello world";
    int padding = (consoleWidth - text.length()) / 2 ;
    cout << "\033[1A" << std::string(padding, ' ') << text << "\033[1B" << endl;
}

// inline void text::alignCenter(int systemNum){
//     switch (systemNum) {
//     case 2:
        
//         break;

//     default:
//         log("fault: no text align center!");
//     }

// }

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
    cout << "\n\n\t- 按回车键继续 -" << endl;
    getchar();
    return 0;
}

inline void func::gameLoading(){
    // 啥呗进度条
    clear(systemNum);
    for(int i=0; i<1; i++)
    {
        clear(systemNum);
        log("正在加载.");
        sleep(1);
        clear(systemNum);
        log("正在加载..");
        sleep(1);
        clear(systemNum);
        // log("正在加载...");
        // sleep(1);
    }
    sleep(1);
}

inline void func::gameStart(text& gameText){
    clear(systemNum);
    gameText.printHello();
    press_any_key_to_continue();
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

inline void func::sleeep(int systemNum){
    #if systemNum == 1 // windows
        Sleep(500);
    #elif systemNum == 2 // linux
        sleep(1);
    #else
        log("CAN NOT RECOGNIZE YOUR SYSTEM");
    #endif
}


// -------------------- character --------------------

inline int character::attack(character &attackTarget){
    int damage = attack_ - attackTarget.defence_;
    // 可正可负，要是护甲太高了就打不动
    // 造成的伤害是 你的攻击 - 敌人的护甲
    if(damage > 0)
        attackTarget.hp_ -= damage;
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

// -------------------- battle --------------------

inline int battle::battleField(character &player, character &enemy, func &func){
    while (player.isAlive() && enemy.isAlive()) {
        cout << "your hp is:" << player.getHP() << endl;
        cout << "your enemy's hp is:" << enemy.getHP() << endl;
        cout << "\nwhat's your choice!!!\n\t1.attack\t2.defence\n" << endl;

        playerRound(player, enemy, func);
        enemyRound(player, enemy);
    }
    return 0;
}

inline int battle::playerRound(character& player, character& enemy, func& func) {
    int playerChoice;
    cin >> playerChoice;

    switch (playerChoice) {
    case 1:
        log("you are attacking your enemy!!");
        // player.attack(enemy);
        sleep(1);
        cout << "你对敌方造成了" << player.attack(enemy) << "点伤害" << endl;
        sleep(1);
        func.clear(func.systemNum);
        break;
    case 2:
        log("your enemy is going to attack you! DEFENCE!");
        sleep(1);
        player.increaseDefForOneRound();
        cout << "你的防御力提高到了" << player.getDefence() + 5 << "点" << endl;
        sleep(1);
        func.clear(func.systemNum);
        break;
    default:
        log("输数字，ok？");
        sleep(1);
        func.clear(func.systemNum);
        break;
    }
    return 0;
}

inline int battle::enemyRound(character& player, character& enemy) {
    // 如果敌人还在，就可以攻击玩家
    if (enemy.isAlive()) {
        int damage = enemy.attack(player);
        log("敌人的回合！！！");
        sleep(1);
        cout << "敌方实际对你造成了" << damage << "点伤害!" << endl;
        player.decreaseDefForOneRound();
    }
    return 0;
}












#endif 
//MYGAME
