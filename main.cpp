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
    
}
