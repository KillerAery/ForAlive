# ForAlive Ver-0.213
使用C++和cocos2d-x 3.10库开发的一款俯视角丧尸生存2D像素游戏demo
（ps:已停止更新）

> 由于使用cocos2d-x 3.10库遇到一些bug，便修改了部分源码（已集成修改过的cocos2dx库）
> 
## 技术栈
- 基于cocos2d-x库，使用C++编写程序主体
- sqlite3数据库记录物品数值
- lua脚本编写游戏AI
- 使用tiledmap地图生成地图
- 使用box2d物理引擎

## 游戏介绍
开放性剧情——
你可以自由探索地图各处，做出任何抉择，发掘末世下的各种故事，遇到各种人，经历各种事。
有人宁愿死也要坚守旧世界的道德，有人为了活下去掠夺其他幸存者的食物，有人则是失去了活下去的意义...
游戏开发思想是体现末日下各个人对生存的追求(ForAlive为了活下去)
简单来说就是让玩家感受末日众生，希望每个形形色色的人物都能给玩家留下一个思考：为什么活着
（灵感来自于这是我的战争，辐射，饥荒，Dayz这些游戏）

美术：像素画自画+网上的RPGmaker素材
音乐：均来自网上资源

## 游戏截图

![](https://github.com/KillerAery/ForAlive/blob/master/MarkDown_Image/%20(2).jpg)

![](https://github.com/KillerAery/ForAlive/blob/master/MarkDown_Image/%20(3).jpg)

![](https://github.com/KillerAery/ForAlive/blob/master/MarkDown_Image/%20(1).jpg)

## 玩法结构
- 实体类体系设计：实体，容器，生物，NPC，玩家
- 背包系统：交互背包栏，装备改装机制，搜刮掉落机制
- NPC系统：游戏AI，寻路，对话系统
- 好感度系统：每个NPC的关系，态度
- 战斗系统：两种武器子弹射击，丧尸近战攻击
- 音乐系统：管理音效音乐播放（基于距离）。
