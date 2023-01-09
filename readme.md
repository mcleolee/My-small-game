# 想加入的功能
- 每次战斗之后输出每个人物的状态
- 随机系统，包括暴击和闪避
- 多人物
- 选择难度
- 游戏结束后，根据当前选择的难度进行结算画面
- cs分离？
- 可以捡到武器

# VERSION
- 0.0.1 雏形，是答辩
- 0.0.2 加入了贴心的提示，不然会乱码噢
        加入了清屏的效果，界面看起来干净一点了！

# BUG
```
1. 

        your enemy is going to attack you! DEFENCE!
你的防御力提高到了11点
敌方实际对你造成了-3点伤害!your hp is:10
your enemy's hp is:8
```
显示的是-3，但是实际造成0伤害，只是显示问题

2.  构建生成的exe文件，在其他电脑上运行出现中文乱码
2023.1.9 22:30
用了 iconv 生成了 main_gbk.cpp。但是感觉并没有什么卵用。
用这个，万一以后要用呢
iconv -f UTF-8 -t GBK main.cpp > main_gbk.cpp

*不如把所有中文都改成英语
2023.1.9 23:30
解决了，看这个
https://blog.csdn.net/weixin_49189242/article/details/115701486?ops_request_misc=&request_id=&biz_id=102&utm_term=CMD如何改编码&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-115701486.142^v70^control,201^v4^add_ask&spm=1018.2226.3001.4449
然后把exe拖进终端运行

