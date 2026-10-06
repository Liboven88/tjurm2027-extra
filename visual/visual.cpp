/*本题目主要考查类的使用,不了解类的同学建议先去学习相关知识。

    背景介绍：在Robomaster比赛中，一个机器人在进行自瞄的时候有时会同时识别到多个敌方目标。此时机器人需要
    选择其中一个来作为最佳打击目标并进行打击。通常我们会锁定距离准心（操作手端的屏幕中心）最近的目标。
    示例    ————————————————————————————————————————————
            |                       T                  |
            |        H            (1,4)                |
            |      (-9,3)                              |         
            |                                          |
            |                     +                    |      此时应当锁定S目标
            |                S                         |
            |              (-3,1)                      |
            |                              I           |
            |                            (7,-3)        |
            ————————————————————————————————————————————

    题目：编写一个程序，记录4个敌方目标的二维坐标，锁定距离准心最近的目标并输出对应的兵种ID。
    
    要求：采用面向对象的方法，设计两个类：
    Enemy 类：包含敌人的坐标和兵种ID，以及相应的设置和获取函数。
    Target 类：包含一个 Enemy 类的对象数组，并具备选择并返回最佳打击目标和输出的功能。

    PS：获取输入数据的框架已经替各位实现好了，在对应的地方调用你们编写的设置函数即可。
*/

#include <iostream>
#include <cmath>

using namespace std;

// ==================== 在此处编写 Enemy和Target 类 ====================
class Enemy {
    public:
    Enemy(): id('?'), x_(0), y_(0) {}
    void Set(char ID,double x,double y)
    {id = ID;x_ = x; y_ = y;}
    double getX() const {return x_;}
    double getY() const {return y_;}//函数不需要参数，因为它本身是Enemy里的成员，可以直接访问和使用自身属性
    char getid() const {return id;}
    private:
    char id; double x_ , y_;
};
class Target {
    public:
    void setEnemy (int index,char ID,double x,double y){
        enemies[index].Set(ID,x,y);
    }
    char choose () const {
        int best = 0;
        for (int i = 1; i < 4; ++i){
            double d = enemies[i].getX() * enemies[i].getX() + enemies[i].getY() * enemies[i].getY();
            if (d < enemies[best].getX() * enemies[best].getX() + enemies[best].getY() * enemies[best].getY()) best = i;
        }//调用Enemy的成员函数必须要有enemy对象，此处对象由target本身成员提供
        return enemies[best].getid();
    }
    private:
    Enemy enemies[4];
};


// ====================================================================


int main() {
    Target target;

    for (int i = 0; i < 4; i++) {
        double x, y;
        char id;
        cout << "请输入第 " << i + 1 << " 个目标的兵种ID和坐标(x y): ";
        cin >> id >> x >> y;

        //在此处调用你的Enemy的设置函数，传入id,x,y
        target.setEnemy(i,id,x,y);//不能直接用Enemy里的Set函数，没有相应的Enemy对象，无法访问和更改private里的参数
    }

    // 调用查找并输出最佳目标
    cout << target.choose() << endl;

    return 0;
}
