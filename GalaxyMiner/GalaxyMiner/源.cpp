//*------------------【头文件】-------------------
#include <conio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include<string>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
using namespace std;
#pragma comment(lib,"Winmm.lib");//音乐
//*------------------【宏变量】-------------------
#define PI 3.1415926//圆周率
#define center_x 444 //宇航员的中心坐标
#define center_y 100  //宇航员的中心坐标
//*------------------【图片全局变量】-------------------
IMAGE backgSignUp; IMAGE Name; IMAGE password;
IMAGE returnPage;
IMAGE nextBtnChosen; IMAGE  nextBtn;
IMAGE tryagain; IMAGE passwordTry;
IMAGE backgStart; IMAGE startNowBtn; IMAGE startNowBtnChosen;
IMAGE loginButton; IMAGE loginButtonChosen;
IMAGE signUpButton; IMAGE signUpButtonChosen;
IMAGE ruleButton; IMAGE ruleButtonChosen;
IMAGE gamePass; IMAGE story1;
IMAGE story2; IMAGE storyLast;
IMAGE gameNotPass;
IMAGE backgLogIn; IMAGE logInBtn; IMAGE logInBtnChosen;
IMAGE eye; IMAGE eyeClose;
IMAGE eyeB; IMAGE eyeCloseB;
IMAGE storyStart;
IMAGE storyStartRule;
IMAGE storyUranus;
IMAGE storySaturn;
IMAGE storyJupiter;
IMAGE storyNeptune;
IMAGE startingNextGame;
IMAGE imgPeople; IMAGE imgPeopleB;
IMAGE ufoB; IMAGE ufo;
IMAGE jupiterBackground;
IMAGE saturnBackground;
IMAGE neptuneBackground;
IMAGE uranusBackground;
IMAGE canNotStart;
IMAGE Earth; IMAGE EarthB;
IMAGE Jupiter; IMAGE JupiterB;
IMAGE Mars; IMAGE MarsB;
IMAGE Mercury; IMAGE MercuryB;
IMAGE Moon; IMAGE MoonB;
IMAGE Neptune; IMAGE NeptuneB;
IMAGE Saturn; IMAGE SaturnB;
IMAGE Uranus; IMAGE UranusB;
IMAGE Venus; IMAGE VenusB;
IMAGE star1; IMAGE star1B;
IMAGE star2; IMAGE star2B;
IMAGE choseGameBackground;
IMAGE chose1; IMAGE waitingChose1;
IMAGE chose2; IMAGE waitingChose2;
IMAGE chose3; IMAGE waitingChose3;
IMAGE chose4; IMAGE waitingChose4;
IMAGE exitBtn; IMAGE exitBtnChosen;
IMAGE backBtn; IMAGE backBtnChosen;
IMAGE rectangel; IMAGE rectangelChosen;
IMAGE timeOver; IMAGE touchMonster;
IMAGE stopBtn; IMAGE stopBtnChosen;
IMAGE conBtn; IMAGE conBtnChosen;
//*------------------【结构体】-------------------
//星星结构体
typedef struct star
{
    int number;//每个星星的特别参数，代表其对于starString[9]中的位置，即其图片
    int imgLeft, imgRight, imgTop, imgBottom;//星星图片四个角的位置
    int x, y;//星星贴图的坐标
    int money = 10;//星星代表的默认分值
    int flag = 1;//等于1是平常状态，等于2是被抓状态,3是回收状态
    struct star* next;
}Star;
//用户结构体
typedef struct user
{
    char name[10];//用户姓名
    char password[10];//用户密码
    int score = 0;//用户分数
    //用户是否可以开始下一具游戏
    bool game1 = true;
    bool game2 = false;
    bool game3 = false;
    bool game4 = false;
}User;
//宇航员结构体
typedef struct Yuhangyuan
{
    IMAGE img = imgPeople;
    IMAGE imgB = imgPeopleB;
    int x;//人物对应位置
    int y;//任务对应位置

}People;
//怪物结构体
typedef struct Monster {
    IMAGE M[20];//图片
    IMAGE MB[20];//掩码图
    //坐标
    int x;
    int y;
    //应该贴第几个图片
    int putNum = 8;
    //奔跑速度
    int run_v = 3;
    //宇航员是否碰到怪物
    bool notTouchMonster = true;
}Monster;
//位置结构体，用于星星位置的输出
typedef struct Position {
    int x;
    int y;
}Position;
//*------------------【全局变量】-------------------
int angle = 30;//初始旋转角度
int angle_v = 1; //旋转的速度
int dig_v = 5;//挖取的速度，抓到大星星时变为3
int r = 80;//宇航员旋转半径
int flag_Dig = 0;//用户是否按下s抓取。按下后变为1
extern int restTime = 20;//剩余时间
int    mycount = 0;//时间
clock_t start, finish;//计时
double Total_time;
int timewtf=0;
int timeForStop = 0;
TCHAR nowTime[5], num[5];//为了输出时间和分数
bool gameNotOver = true;
IMAGE starString[20];//储存星星图片,0是普通的小星星，1-9是太阳系行星
IMAGE starBString[20];//同上储存掩码图
int peopleX;//宇航员坐标
int peopleY;//宇航员坐标
People people;//宇航员
Monster monster;//怪物
Position position[20];//星星的初始位置
User player;//用户玩家
int returnNum = 10;
int gameStatue = 1;//1正常进行，2游戏时间到，3游戏过关，4点击返回，5为碰到怪物

//*------------------【函数声明】-------------------
void stop();
void loadimg();//加载数据，初始化全局变量
int startup();//用户看到的第一个页面，以及进行画选择
void hook(Star* s);//hook函数包含了1.每次对角度和宇航员位置进行改变；2.对被抓住的星星进行位置改变
void updateWithInput(Star* s);//处理用户操作
void updateWithoutInput(Star* s);//用户没有操作时
void gameover();
void gameUI(Star* s);//绘制整个游戏画面
void check();//确认用户是否以存在
void wirteFile(User user);//写出用户信息
void putStar(Star* h);//利用链表遍历绘制星星
void putMonster();
int inTriggeringArea(int m_x, int m_y, int x1, int y1, int x2, int y2);//鼠标进入某一区域
int OptionWhenStart(int x, int y);
int OptionWhenGameStart(int x, int y);
int OptionWhenChoseLevel();
Star* creat();//创建头链表
Star* add(Star* h, int i);//加链表
void game1();//第一关
void game2();//第二关
void game3();//第三关
void game4();//第四关
void LogIn();//用户登录
void LogIn_password(char* u);//登录时输密码
void SignUp();//用户注册
void SignUp_password();//注册时输密码
void Rule();//阅读规则
//*------------------【函数主体】-------------------
void LogIn() {
    FlushBatchDraw();
    MOUSEMSG m;//鼠标
    FILE* fp;//文件指针
    char u[20], c[20], temp[20];//用于字符串的操作
    //设置文字格式
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 30, _T("Consolas"));
    //背景
    putimage(0, 0, &backgLogIn);
    putimage(125, 250, &Name);
    while (1) {
        m = GetMouseMsg();
        //如果点击密码框
        if (inTriggeringArea(m.x, m.y, 223, 427, 885, 497)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                scanf("%s", u);
                outtextxy(276, 463, u);
            }
        }
        //点击下一步
        if (inTriggeringArea(m.x, m.y, 428, 571, 670, 650)) {
            putimage(428, 571, &nextBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                //如果用户名不存在，需要重新输入
                fp = fopen(u, "r+");
                temp[0] = '0';
                if (fp == NULL) {
                    putimage(223, 250, &tryagain);
                    Sleep(2000);
                    return LogIn();
                }
                //存在则输入密码
                else {
                    return LogIn_password(u);
                }
            }
        }
        else {
            putimage(424, 571, &nextBtn);
        }
        //选择退出
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &exitBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                exit(0);
            }
        }
        else
        {
            putimage(30, 710, &exitBtn);
        }
        //选择返回
        if (m.x >= 30 && m.x <= 162 && m.y >= 0 && m.y < 85) {
            putimage(30, 0, &backBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
               startup();
               return;
            }
        }
        else
        {
            putimage(30, 0, &backBtn);
        }
    }

}
void LogIn_password(char* u) {
    FlushBatchDraw();
    MOUSEMSG m;
    FILE* fp;
    bool judge = true;
    char c[20], temp[20];
    fp = fopen(u, "r+");
    //
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 30, _T("Consolas"));
    putimage(0, 0, &backgLogIn);
    putimage(125, 250, &password);
    while (1) {
        m = GetMouseMsg();
        if (inTriggeringArea(m.x, m.y, 223, 427, 885, 497)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (judge == true) fread(&player, sizeof(User), 1, fp); //读取用户信息，即用户名和密码
                scanf("%s", c);
                outtextxy(276, 463, c);

            }

        }
        if (inTriggeringArea(m.x, m.y, 428, 571, 670, 650)) {
            putimage(428, 571, &nextBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                if (strcmp(player.password, c) != 0) {
                    putimage(223, 250, &passwordTry);
                    Sleep(2000);

                }
                return;
            }
        }
        else {
            putimage(424, 571, &nextBtn);
        }
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &exitBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                exit(0);
            }
        }
        else
        {
            putimage(30, 710, &exitBtn);
        }
    }
}
//用户注册时输入y密码
void SignUp_password() {
    FlushBatchDraw();
    MOUSEMSG m;
    FILE* fp;
    //设置文字
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 30, _T("Consolas"));
    putimage(0, 0, &backgLogIn);
    putimage(125, 250, &password);
    while (1) {
        m = GetMouseMsg();
        //如果点击密码输入框
        if (inTriggeringArea(m.x, m.y, 223, 427, 885, 497)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                scanf("%s", player.password);
                outtextxy(276, 463, player.password);
            }

        }
        //点击下一步
        if (inTriggeringArea(m.x, m.y, 428, 571, 670, 650)) {
            putimage(428, 571, &nextBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                return;
            }
        }
        else {
            putimage(428, 571, &nextBtn);
        }
        //点击退出
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &exitBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                exit(0);
            }
        }
        else
        {
            putimage(30, 710, &exitBtn);
        }
    }
}
void SignUp() {
    FlushBatchDraw();
    MOUSEMSG m;
    FILE* fp;
    //设置文字
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 30, _T("Consolas"));
    //名字输入
    char temp[20], txt[100], cha;
    putimage(0, 0, &backgSignUp);
    putimage(125, 250, &Name);
    while (1) {
        m = GetMouseMsg();
        //点击用户名输入框
        if (inTriggeringArea(m.x, m.y, 223, 427, 885, 497)) {
            if (m.uMsg == WM_LBUTTONDOWN) {
                scanf("%s", player.name);
                fp = fopen(player.name, "w");
                //写文件
                if (fp != NULL) {
                    fclose(fp);
                }
            }
        }
        //显示用户名
        outtextxy(276, 463, player.name);
        //点击下一步，输入用户名
        if (inTriggeringArea(m.x, m.y, 428, 571, 670, 650)) {
            putimage(428, 571, &nextBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                EndBatchDraw();
                SignUp_password();
                return;
            }
        }
        else {
            putimage(428, 571, &nextBtn);
        }
        //点击退出
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &exitBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                exit(0);
            }
        }
        else
        {
            putimage(30, 710, &exitBtn);
        }

    }
    //密码输入

}
//阅读规则
void Rule() {
    FlushBatchDraw();
    putimage(0, 0, &story2);
    MOUSEMSG m;
    while (1) {
        m = GetMouseMsg();
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &backBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
               return;
            }
        }
        else
        {
            putimage(30, 710, &backBtn);
        }
    }


}
//鼠标进入某一范围
int inTriggeringArea(int m_x, int m_y, int x1, int y1, int x2, int y2) {
    if (m_x > x1&& m_x<x2 && m_y>y1&& m_y < y2)
        return 1;
    return 0;

}
void stop() {


    while (1) {
        MOUSEMSG m = GetMouseMsg();
        if (inTriggeringArea(m.x, m.y, 947, 717, 1080, 800)) {
            printf("you enter area/n");
            putimage(947, 717, &conBtnChosen);

            if (m.uMsg == WM_LBUTTONDOWN) {
                printf("you click/n");
                start = clock();
                timeForStop = timewtf;
                printf("startInStop:%d\n", start);
                return;
            }
        }
        else {
            putimage(947, 717, &conBtn);
        }
        if (inTriggeringArea(m.x, m.y, 0, 0, 136, 82)) {
            putimage(0, 0, &backBtnChosen);

            if (m.uMsg == WM_LBUTTONDOWN) {
                gameStatue = 4;
                return;

            }
        }

    }
}

int OptionWhenStart(int x, int y) {
    MOUSEMSG m;
    FlushBatchDraw();
    while (1) {
        m = GetMouseMsg();

        if (m.x >= x && m.x <= 690 && m.y >= y && m.y < 411) {
            putimage(x, y, &startNowBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 1;
            }
        }
        else {
            putimage(x, y, &startNowBtn);
        }

    }
}
int OptionWhenGameStart(int x, int y) {
    MOUSEMSG m;
    FlushBatchDraw();
    while (1) {
        m = GetMouseMsg();

        if (m.x >= x && m.x <= x + 400 && m.y >= y && m.y < y + 70) {
            putimage(395, 391, &startNowBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 1;
            }
        }
        else {
            putimage(395, 391, &startNowBtn);

        }

    }
}
int OptionWhenChoseLevel() {
    MOUSEMSG m;
    FlushBatchDraw();
    putimage(0, 0, &choseGameBackground);
    putimage(460, 134, &waitingChose1);
    putimage(460, 290, &waitingChose2);
    putimage(460, 446, &waitingChose3);
    putimage(460, 604, &waitingChose4);
    putimage(30, 710, &exitBtn);
    FlushBatchDraw();
    while (1) {

        m = GetMouseMsg();
        if (m.x > 460 && m.x < 700 && m.y >= 134 && m.y < 220) {
            putimage(460, 134, &chose1);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 1;
            }
        }
        else
        {
            putimage(460, 134, &waitingChose1);
        }
        if (m.x >= 460 && m.x <= 700 && m.y >= 290 && m.y < 375) {
            putimage(460, 290, &chose2);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 2;
            }
        }
        else
        {
            putimage(460, 290, &waitingChose2);
        }
        //
        if (m.x >= 460 && m.x <= 700 && m.y >= 446 && m.y < 534) {
            putimage(460, 446, &chose3);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 3;
            }
        }
        else
        {
            putimage(460, 446, &waitingChose3);
        }
        //
        if (m.x >= 400 && m.x <= 700 && m.y >= 604 && m.y < 690) {
            putimage(460, 604, &chose4);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 4;
            }
        }
        else
        {
            putimage(460, 604, &waitingChose4);
        }
        //
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &exitBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                exit(0);
            }
        }
        else
        {
            putimage(30, 710, &exitBtn);
        }


    }


}

void loadimg() {
    //加载数据，初始化全局变量
    mciSendString("open .\\1.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
    mciSendString("play bkmusic repeat", NULL, 0, NULL);
    //
    loadimage(&returnPage, _T("returnPage.png"));
    loadimage(&stopBtn, _T("stopBtn.png"));
    loadimage(&stopBtnChosen, _T("stopBtnChosen.png"));
    loadimage(&conBtn, _T("conBtn.png"));
    loadimage(&conBtnChosen, _T("conBtnChosen.png"));
    loadimage(&backgSignUp, _T("backgSignUp.png"));
    loadimage(&Name, _T("Name.png"));
    loadimage(&password, _T("password.png"));
    loadimage(&nextBtnChosen, _T("nextBtnChosen.png"));
    loadimage(&nextBtn, _T("nextBtn.png"));
    loadimage(&tryagain, _T("tryagain.png"));
    loadimage(&passwordTry, _T("passwordTry.png"));
    loadimage(&gamePass, _T("gamePass.png"));
    loadimage(&story1, _T("story1.png"));
    loadimage(&story2, _T("story2.png"));
    loadimage(&storyLast, _T("storyLast.png"));
    loadimage(&gameNotPass, _T("gameNotPass.png"));
    //
    loadimage(&backgStart, _T("backgStart.png"));
    loadimage(&startNowBtn, _T("startNowBtn.png"));
    loadimage(&startNowBtnChosen, _T("startNowBtnChosen.png"));
    loadimage(&loginButton, _T("loginButton.png"));
    loadimage(&loginButtonChosen, _T("loginButtonChosen.png"));
    loadimage(&signUpButton, _T("signUpButton.png"));
    loadimage(&signUpButtonChosen, _T("signUpButtonChosen.png"));
    loadimage(&ruleButton, _T("ruleButton.png"));
    loadimage(&ruleButtonChosen, _T("ruleButtonChosen.png"));
    //
    loadimage(&backgLogIn, _T("backgLogIn.PNG"));
    loadimage(&logInBtn, _T("logInBtn.PNG"));
    loadimage(&logInBtnChosen, _T("logInBtnChosen.PNG"));
    loadimage(&eyeB, _T("eyeB.PNG"));
    loadimage(&eye, _T("eye.PNG"));
    loadimage(&eyeCloseB, _T("eyeCloseB.PNG"));
    loadimage(&eyeClose, _T("leyeClose.PNG"));
    //
    loadimage(&storyStart, _T("storyStart.PNG"));
    loadimage(&storyStartRule, _T("storyStartRule.PNG"));
    loadimage(&storyUranus, _T("storyUranus.PNG"));
    loadimage(&storySaturn, _T("storySaturn.PNG"));
    loadimage(&storyJupiter, _T("storyJupiter.PNG"));
    loadimage(&storyNeptune, _T("storyNeptune.PNG"));
    loadimage(&startingNextGame, _T("startingNextGame.PNG"));
    loadimage(&timeOver, _T("timeOver.PNG"));
    loadimage(&touchMonster, _T("touchMonster.PNG"));
    loadimage(&canNotStart, _T("canNotStart.png"));
    //
    loadimage(&ufoB, _T("ufoB.PNG"));
    loadimage(&ufo, _T("ufo.PNG"));
    loadimage(&imgPeopleB, _T("peopleB.PNG"));
    loadimage(&imgPeople, _T("people.PNG"));
    //
    loadimage(&choseGameBackground, _T("choseGameBackground.png"));
    loadimage(&chose1, _T("chose1.PNG"));
    loadimage(&chose2, _T("chose2.PNG"));
    loadimage(&chose3, _T("chose3.PNG"));
    loadimage(&chose4, _T("chose4.PNG"));
    loadimage(&waitingChose1, _T("waitingChose1.PNG"));
    loadimage(&waitingChose2, _T("waitingChose2.PNG"));
    loadimage(&waitingChose3, _T("waitingChose3.PNG"));
    loadimage(&waitingChose4, _T("waitingChose4.PNG"));
    loadimage(&exitBtn, _T("exitBtn.PNG"));
    loadimage(&exitBtnChosen, _T("exitBtnChosen.PNG"));
    loadimage(&backBtn, _T("backBtn.PNG"));
    loadimage(&backBtnChosen, _T("backBtnChosen.PNG"));
    loadimage(&rectangel, _T("rectangel.png"));
    loadimage(&rectangelChosen, _T("rectangelChosen.png"));
    //
    loadimage(&jupiterBackground, _T("jupiterBackground.PNG"));
    loadimage(&saturnBackground, _T("saturnBackground.PNG"));
    loadimage(&neptuneBackground, _T("neptuneBackground.PNG"));
    loadimage(&uranusBackground, _T("uranusBackground.PNG"));
    //
    loadimage(&monster.M[0], _T("M1.png"));
    loadimage(&monster.MB[0], _T("M1B.png"));
    loadimage(&monster.M[1], _T("M2.png"));
    loadimage(&monster.MB[1], _T("M2B.png"));
    loadimage(&monster.M[2], _T("M3.png"));
    loadimage(&monster.MB[2], _T("M3B.png"));
    loadimage(&monster.M[3], _T("M4.png"));
    loadimage(&monster.MB[3], _T("M4B.png"));
    loadimage(&monster.M[4], _T("M5.png"));
    loadimage(&monster.MB[4], _T("M5B.png"));
    loadimage(&monster.M[5], _T("M6.png"));
    loadimage(&monster.MB[5], _T("M6B.png"));
    loadimage(&monster.M[6], _T("M7.png"));
    loadimage(&monster.MB[6], _T("M7B.png"));
    loadimage(&monster.M[7], _T("M8.png"));
    loadimage(&monster.MB[7], _T("M8B.png"));
    //
    loadimage(&monster.M[8], _T("M9.png"));
    loadimage(&monster.MB[8], _T("M9B.png"));
    loadimage(&monster.M[9], _T("M10.png"));
    loadimage(&monster.MB[9], _T("M10B.png"));
    loadimage(&monster.M[10], _T("M11.png"));
    loadimage(&monster.MB[10], _T("M11B.png"));
    loadimage(&monster.M[11], _T("M12.png"));
    loadimage(&monster.MB[11], _T("M12B.png"));
    loadimage(&monster.M[12], _T("M13.png"));
    loadimage(&monster.MB[12], _T("M13B.png"));
    loadimage(&monster.M[13], _T("M14.png"));
    loadimage(&monster.MB[13], _T("M14B.png"));
    loadimage(&monster.M[14], _T("M15.png"));
    loadimage(&monster.MB[14], _T("M15B.png"));
    loadimage(&monster.M[15], _T("M16.png"));
    loadimage(&monster.MB[15], _T("M16B.png"));

    //加载星星的图片
    loadimage(&star1, _T("star1.png"));
    loadimage(&star1B, _T("star1B.png"));
    loadimage(&star2, _T("star2.png"));
    loadimage(&star2B, _T("star2B.png"));
    loadimage(&JupiterB, _T("JupiterB.png"));
    loadimage(&Jupiter, _T("Jupiter.png"));
    loadimage(&EarthB, _T("EarthB.png"));
    loadimage(&Earth, _T("Earth.png"));
    loadimage(&MoonB, _T("MoonB.png"));
    loadimage(&Moon, _T("Moon.png"));
    //
    loadimage(&MarsB, _T("MarsB.png"));
    loadimage(&Mars, _T("Mars.png"));
    loadimage(&MercuryB, _T("MercuryB.png"));
    loadimage(&Mercury, _T("Mercury.png"));
    loadimage(&UranusB, _T("UranusB.png"));
    loadimage(&Uranus, _T("Uranus.png"));
    //
    loadimage(&NeptuneB, _T("NeptuneB.png"));
    loadimage(&Neptune, _T("Neptune.png"));
    loadimage(&SaturnB, _T("SaturnB.png"));
    loadimage(&Saturn, _T("Saturn.png"));

    loadimage(&VenusB, _T("VenusB.png"));
    loadimage(&Venus, _T("Venus.png"));



    //加载图片之后给全局变量赋值
    //人物图片赋值
    people.img = imgPeople;
    people.imgB = imgPeopleB;

    //星星图片赋值
    //第一关
    starString[0] = star1;
    starBString[0] = star1B;
    starString[1] = Saturn;
    starBString[1] = SaturnB;
    starString[2] = star1;
    starBString[2] = star1B;
    starString[3] = Mercury;
    starBString[3] = MercuryB;
    starString[4] = Jupiter;
    starBString[4] = JupiterB;
    starString[5] = star1;
    starBString[5] = star1B;
    //
    starString[6] = Mars;
    starBString[6] = MarsB;
    starString[7] = star1;
    starBString[7] = star1B;
    starString[8] = Moon;
    starBString[8] = MoonB;
    starString[9] = star1;
    starBString[9] = star1B;
    starString[10] = Neptune;
    starBString[10] = NeptuneB;
    //
    starString[11] = Saturn;
    starBString[11] = SaturnB;
    starString[12] = star1;
    starBString[12] = star1B;
    starString[13] = Venus;
    starBString[13] = VenusB;
    starString[14] = star1;
    starBString[14] = star1B;
    starString[15] = Uranus;
    starBString[15] = UranusB;
    //
    starString[16] = star1;
    starBString[16] = star1B;
    starString[17] = star1;
    starBString[17] = star1B;
    starString[18] = star1;
    starBString[18] = star1B;
    starString[19] = Moon;
    starBString[19] = MoonB;
    starString[20] = Earth;
    starBString[20] = EarthB;
    //星星位置初始
    position[0].x = 200;
    position[0].y = 377;
    position[1].x = 650;
    position[1].y = 640;
    position[2].x = 340;
    position[2].y = 540;
    position[3].x = 436;
    position[3].y = 500;
    position[4].x = 89;
    position[4].y = 640;
    position[5].x = 653;
    position[5].y = 450;
    //
    position[6].x = 100;
    position[6].y = 520;
    position[7].x = 360;
    position[7].y = 700;
    position[8].x = 379;
    position[8].y = 433;
    position[9].x = 650;
    position[9].y = 475;
    position[10].x = 650;
    position[10].y = 640;
    //
    position[11].x = 630;
    position[11].y = 510;
    position[12].x = 130;
    position[12].y = 400;
    position[13].x = 300;
    position[13].y = 680;
    position[14].x = 636;
    position[14].y = 350;
    position[15].x = 26;
    position[15].y = 600;
    //
    position[16].x = 214;
    position[16].y = 598;
    position[17].x = 420;
    position[17].y = 481;
    position[18].x = 750;
    position[18].y = 410;
    position[19].x = 800;
    position[19].y = 540;
    position[20].x = 484;
    position[20].y = 654;
    //
}
int startup() {
    MOUSEMSG m;
    //用户选择开始游戏
    putimage(0, 0, &backgStart);//背景
    FlushBatchDraw();
    while (1) {
        m = GetMouseMsg();
        //
        if (m.x > 422 && m.x < 622 && m.y >= 256 && m.y < 353) {
            putimage(422, 256, &loginButtonChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {
                return 1;
            }
        }
        else
        {
            putimage(422, 256, &loginButton);
        }
        //
        if (m.x >= 422 && m.x <= 622 && m.y >= 443 && m.y < 541) {
            putimage(422, 443, &signUpButtonChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 2;
            }
        }
        else
        {
            putimage(422, 443, &signUpButton);
        }
        //
        if (m.x >= 422 && m.x <= 662 && m.y >= 636 && m.y < 731) {
            putimage(422, 636, &ruleButtonChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                return 3;
            }
        }
        else
        {
            putimage(422, 636, &ruleButton);
        }

        //
        if (m.x >= 30 && m.x <= 162 && m.y >= 709 && m.y < 788) {
            putimage(30, 710, &exitBtnChosen);
            if (m.uMsg == WM_LBUTTONDOWN) {

                exit(0);
            }
        }
        else
        {
            putimage(30, 710, &exitBtn);
        }
    }

    people.x = 500;
    people.y = 20;
    monster.x = 500;
    monster.y = 400;


}
void hook(Star* s) {
    //hook函数包含了1.每次对角度和宇航员位置进行改变；2.对被抓住的星星进行位置改变
    Sleep(18);//防止转速过快，画面不适
    FlushBatchDraw();
    Star* temp = s;//临时指针遍历链表
    //角度限定在-100到100范围内
    if (angle >= 100 || angle <= -100)
        angle_v = -angle_v;
    //没有挖矿时角度会变化
    if (!flag_Dig)
        angle = angle + angle_v;
    //人物位置随角度变化，由关于角度的参数方程写出
    people.x = center_x + r * sin(angle * PI / 180);
    people.y = center_y + r * cos(angle * PI / 180);

    int peopleX = people.x + people.img.getwidth() / 2;
    int peopleY = people.y + people.img.getheight() / 2;

    //改变星星位置
    while (temp != NULL) {
        //如果抓住星星的话，星星的坐标会一起变化
        if (temp->flag == 2) {
            temp->x = people.x - ((starBString[temp->number]).getheight()) / 2;
            temp->y = people.y - 20;
            temp->imgLeft = temp->x;
            temp->imgTop = temp->y;
            temp->imgRight = temp->x + starBString[0].getwidth();
            temp->imgBottom = temp->y + starBString[0].getheight();
        }
        temp = temp->next;
    }
    //绘制图像
    gameUI(s);


}
void updateWithoutInput(Star* s) {


    BeginBatchDraw();
    hook(s);

}

void updateWithInput(Star* s) {
    int rOringe = 80;//本来的旋转半径
    int notTouch = 1;//用来在抓到星星，碰到边界，回到初始位置这三种情况下的跳出循环的参数
    char input;//用户输入

    if (_kbhit()) {
        input = _getch();
        if (input == 's' || input == 'S') {
            //播放抓下时的音乐
            mciSendString("stop gemusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
            mciSendString("close gemusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
            mciSendString("open .\\hook.mp3 alias gemusic", NULL, 0, NULL); // 打开点击音乐
            mciSendString("play gemusic", NULL, 0, NULL); // 仅播放一次
            flag_Dig = 1;

            while (notTouch) {

                //每次都会增加半径来使人物向下运动
                r = r + dig_v;

                hook(s);

                //碰到边界
                if (people.x >= 800 || people.x <= 0 || people.y >= 800 || people.y <= 0)
                    dig_v = -dig_v;
                //回到原来位置
                if (r == rOringe) {
                    dig_v = -dig_v;
                    flag_Dig = 0;
                    notTouch = 0;
                }
            }

            /*            if(level==2)*/


        }
    }
    //在gameUI这个函数中对抓到的星星进行处理

    gameUI(s);


}
void gameover() {
    system("pause");
    closegraph();
}

void gameUI(Star* s) {
    //game UI的作用是根据输入情况和参数变化情况，每次绘制图形
    //并且因为gameUI是每次都要运行，所以选择在这个函数中判断是否抓住星星
    Star* p = s;//临时指针遍历链表
   
    //根据返回值代表的关卡，选择绘制背景
    if (returnNum == 1) {
        putimage(0, 0, &jupiterBackground);//背景图
    }
    if (returnNum == 2) {
        putimage(0, 0, &saturnBackground);//背景图
    }
    if (returnNum == 3) {
        putimage(0, 0, &neptuneBackground);//背景图
    }
    if (returnNum == 4) {
        putimage(0, 0, &uranusBackground);//背景图
    }
    //游戏中的元素
    putimage(440, 20, &ufoB, SRCPAINT);//ufo
    putimage(440, 20, &ufo, SRCAND);//ufo掩码图
    putimage(people.x, people.y, &people.imgB, SRCPAINT);//宇航员
    putimage(people.x, people.y, &people.img, SRCAND);//宇航员掩码图
    putimage(0, 0, &backBtn);
    putimage(947, 736, &stopBtn);

    //绘制星星
    putStar(s);
    //如果是第三关或者第四关，会绘制怪物
    if (returnNum == 3) {
        putMonster();
    }
    if (returnNum == 4) {
        putMonster();
    }
    //如果选择返回键的话，会跳转到关卡选择
    while (MouseHit()) {
        MOUSEMSG m = GetMouseMsg();
        if (inTriggeringArea(m.x, m.y, 0, 0, 136, 82)) {
            putimage(0, 0, &backBtnChosen);

            if (m.uMsg == WM_LBUTTONDOWN) {
                gameStatue = 4;

            }
        }

        if (inTriggeringArea(m.x, m.y, 947, 717, 1080, 800)) {
            putimage(947, 717, &stopBtnChosen);

            if (m.uMsg == WM_LBUTTONDOWN) {
                stop();
            }
        }

    }
    //判断是否被抓,以及是否回收
    while (p != NULL) {
        //抓到星星，即宇航员图片位置坐标进入星星图片的某一范围
        if (p->flag == 1 && people.x + 30 >= p->imgLeft && people.x - 30 <= p->imgRight && people.y - 30 <= p->imgBottom && people.y + 30 >= p->imgTop) {

            p->flag = 2;//表示已经被抓到
            dig_v = -dig_v;//速度变成相反数，向回走
            player.score = player.score + p->money;//相应分数增加
            if (p->number == 1) {
                player.game2 = true;
                gameStatue = 3;
            }
            if (p->number == 10) {
                player.game3 = true;
                gameStatue = 3;
            }
            if (p->number == 15) {
                player.game4 = true;
                gameStatue = 3;
            }

        }
        //应该回收星星
        if (p->y <= 150 && flag_Dig == 0) {
            p->flag = 3;
        }
        p = p->next;
    }
    //显示分数
    wsprintf(num, "%d", player.score);
    setbkcolor(RGB(35, 181, 240));
    settextstyle(30, 0, "宋体");
    outtextxy(1030, 130, num);
    //计算并显示倒计时
    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
   timewtf = (int)Total_time+timeForStop;
    wsprintf(nowTime, "%d", timewtf);
    setbkcolor(RGB(35, 181, 240));
    settextstyle(30, 0, "宋体");
    outtextxy(1030, 60, nowTime);
    printf("timewtf:%d\n", timewtf);
    if (timewtf > 30) {
        printf("gameShouldOver\n");
        gameStatue = 2;
    }

}


void wirteFile(User user) {
    FILE* fp1, * fp2;
    errno_t err;
    fp1 = fopen("userName.txt", "w");
    fprintf(fp1, "%s", user.name);
    fclose(fp1);
    fp2 = fopen("userPassword.txt", "w");
    fprintf(fp2, "%s", user.password);
    fclose(fp2);




}
//创建头指针
Star* creat() {
    //头指针
    Star* h;
    h = (Star*)malloc(sizeof(Star));
    //结构体中参数的初始化
    h->number = 0;
    h->flag = 1;
    h->money = 5;
    h->x = position[0].x;
    h->y = position[0].y;
    h->imgLeft = position[0].x;
    h->imgTop = position[0].y;
    h->imgRight = position[0].x + starBString[0].getwidth();
    h->imgBottom = position[0].y + starBString[0].getheight();
    h->next = NULL;
    //返回
    return h;
}
//尾插添加
Star* add(Star* h, int i) {
    //方便遍历的指针，和新建的指针
    Star* p, * s;
    //结构体中参数的初始化
    s = (Star*)malloc(sizeof(Star));
    s->number = i;
    s->flag = 1;
    s->money = 5;
    s->x = position[i].x;
    s->y = position[i].y;
    s->imgLeft = position[i].x;
    s->imgTop = position[i].y;
    s->imgRight = position[i].x + starBString[i].getwidth();
    s->imgBottom = position[i].y + starBString[i].getheight();
    //赋值尾插
    s->next = NULL;
    p = h;
    while (p->next != NULL)
        p = p->next;
    p->next = s;
    //返回
    return h;
}
//专门绘制星星
void putStar(Star* h) {
    Star* temp, * p;
    p = h;
    temp = h;
    //遍历链表
    while (temp != NULL) {
        //如果抓住星星的话，星星的坐标会一起变化
        if (temp->flag == 2) {
            //星星的位置与宇航员有关
            temp->x = people.x - ((starBString[temp->number]).getheight()) / 2;
            temp->y = people.y - 20;
            temp->imgLeft = temp->x;
            temp->imgTop = temp->y;
            temp->imgRight = temp->x + starBString[0].getwidth();
            temp->imgBottom = temp->y + starBString[0].getheight();
        }
        //如果需要回收（即抓回到原处）应该回收时防止的位置，根据星星编号进行变化
        if (temp->flag == 3) {

            temp->x = 900 + (temp->number) * 5;
            temp->y = 414;
        }
        temp = temp->next;
    }
    //星星贴图
    while (p != NULL) {
        putimage(p->x, p->y, &(starBString[p->number]), SRCPAINT);
        putimage(p->x, p->y, &(starString[p->number]), SRCAND);
        printf("%d\n", p->flag);
        p = p->next;
    }

}
void putMonster() {
    //当怪兽跑完一次时（左到右或者右到左），需要进行速度的反向，以及贴图的变化
    if (monster.run_v < 0) {
        if (monster.putNum >= 0 && monster.putNum <= 7) {
            monster.putNum--;
        }
        else {
            monster.putNum = 7;
        }
    }

    if (monster.run_v > 0) {
        if (monster.putNum >= 8 && monster.putNum <= 15) {
            monster.putNum++;
        }
        else {
            monster.putNum = 8;
        }
    }
    //贴图
    putimage(monster.x, monster.y, &monster.MB[monster.putNum], SRCPAINT);
    putimage(monster.x, monster.y, &monster.M[monster.putNum], SRCAND);
    Sleep(18);
    //实现奔跑
    if (monster.notTouchMonster) {
        monster.x = monster.x + monster.run_v;
    }
    //碰到怪兽
    if (people.x + 30 >= monster.x && people.x - 30 <= monster.x && people.y - 30 <= monster.y && people.y + 30 >= monster.y) {
        monster.notTouchMonster = false;
        gameStatue = 5;
    }
    //反向
    if (monster.x > 800)
        monster.run_v = -2;
    if (monster.x < 0)
        monster.run_v = 2;
}
void game1() {
    timeForStop = 0;
    gameStatue = 1;
    Star* starsL1 = creat();
    starsL1 = add(starsL1, 1);
    starsL1 = add(starsL1, 2);
    starsL1 = add(starsL1, 3);
    starsL1 = add(starsL1, 4);
    starsL1 = add(starsL1, 5);
    //
    putimage(0, 0, &storyJupiter);
    Sleep(10000);
    //
    start = clock();
    gameUI(starsL1);
    //

    //
    while (gameStatue == 1) {
        updateWithoutInput(starsL1);
        updateWithInput(starsL1);
    }
    EndBatchDraw();
    //
    if (gameStatue == 2) {
        putimage(0, 0, &timeOver);
    }

    if (gameStatue == 3) {
        putimage(0, 0, &startingNextGame);
    }
    if (gameStatue == 4) {
        putimage(0, 0, &returnPage);
    }
    Sleep(3000);

}
void game2() {
    //
    timeForStop = 0;
    gameStatue = 1;
    Star* starsL2 = creat();
    starsL2 = add(starsL2, 6);
    starsL2 = add(starsL2, 7);
    starsL2 = add(starsL2, 8);
    starsL2 = add(starsL2, 9);
    starsL2 = add(starsL2, 10);
    //
    putimage(0, 0, &storySaturn);
    Sleep(10000);
    //
    start = clock();
    gameUI(starsL2);

    //
    while (gameStatue == 1) {
        updateWithoutInput(starsL2);
        updateWithInput(starsL2);
    }
    EndBatchDraw();
    //
    if (gameStatue == 2) {
        putimage(0, 0, &timeOver);
    }
    if (gameStatue == 3) {
        putimage(0, 0, &startingNextGame);
    }
    if (gameStatue == 4) {
        putimage(0, 0, &returnPage);
    }
    Sleep(3000);

}
void game3() {
    //
    timeForStop = 0;
    gameStatue = 1;
    Star* stars = creat();
    stars = add(stars, 11);
    stars = add(stars, 12);
    stars = add(stars, 13);
    stars = add(stars, 14);
    stars = add(stars, 15);
    //
    putimage(0, 0, &storyNeptune);
    Sleep(10000);
    monster.x = 500;
    monster.y = 400;
    monster.putNum = 8;
    monster.notTouchMonster = true;
    //
    start = clock();
    gameUI(stars);

    //
    while (gameStatue == 1) {
        updateWithoutInput(stars);
        updateWithInput(stars);
    }
    EndBatchDraw();
    if (gameStatue == 2) {
        putimage(0, 0, &timeOver);
    }
    if (gameStatue == 5) {
        putimage(0, 0, &touchMonster);
    }
    if (gameStatue == 3) {
        putimage(0, 0, &startingNextGame);
    }
    if (gameStatue == 4) {
        putimage(0, 0, &returnPage);
    }
    Sleep(3000);

}
void game4() {
    //
    putimage(0, 0, &storyLast);
    Sleep(10000);
    timeForStop = 0;
    gameStatue = 1;
    Star* stars = creat();
    stars = add(stars, 16);
    stars = add(stars, 17);
    stars = add(stars, 18);
    stars = add(stars, 19);
    stars = add(stars, 20);
    //

    monster.x = 500;
    monster.y = 400;
    monster.putNum = 8;
    monster.notTouchMonster = true;
    //

    //
    start = clock();
    gameUI(stars);

    while (gameStatue == 1) {
        updateWithoutInput(stars);
        updateWithInput(stars);
    }
    //
    if (gameStatue == 2) {
        putimage(0, 0, &timeOver);
    }
    else if (gameStatue == 4) {
        putimage(0, 0, &returnPage);
    }
    else if (gameStatue == 5) {
        putimage(0, 0, &touchMonster);
    }
    else if (player.score > 40) {
        putimage(0, 0, &gamePass);
    }
    else {
        putimage(0, 0, &gameNotPass);
    }
    Sleep(3000);
 

}
int main()
{
    //初始化画布
    initgraph(1080, 800);
    //加载图片
    loadimg();
    //背景故事
    putimage(0, 0, &story1);
    Sleep(10000);
    //整个游戏键盘输入只能识别英文
    //用户选择登录，注册，阅读规则
    bool StillLoop=true;
    while (StillLoop) {
        int StartNum = startup();
        //选择登录
        if (StartNum == 1) {
            LogIn();  
            StillLoop = false;
        }
        //选择注册
        if (StartNum == 2) {
            SignUp();
            StillLoop = false;
        }
        //选择阅读规则
        if (StartNum == 3) {
            Rule();
        }
    }

    EndBatchDraw();
    //用户选择关卡
    returnNum = OptionWhenChoseLevel();
    gameStatue = 1;
    //主引擎
    while (1) {
        //第一关
        if (returnNum == 1) {
            game1();
            start = clock();
            //结束返回，继续选择
            returnNum = OptionWhenChoseLevel();
        }
        //第二关：第一关通过才可以
        if (returnNum == 2) {

            if (player.game2) {
                start = clock();
                game2();
               
            }
            else {
                putimage(0, 0, &canNotStart);
                Sleep(1000);
            }
            //结束返回，继续选择
            returnNum = OptionWhenChoseLevel();
        }
        //第三关：第二关通过才可以
        if (returnNum == 3) {
            if (player.game3) {
                start = clock();
                game3();
              
            }
            else {
                putimage(0, 0, &canNotStart);
                Sleep(1000);
            }
            EndBatchDraw();
            //结束返回，继续选择
            returnNum = OptionWhenChoseLevel();
        }
        //第四关：第三关通关才可以
        if (returnNum == 4) {
            //

            if (player.game4) {
                start = clock();
                game4();
               

            }
            else {
                putimage(0, 0, &canNotStart);
                Sleep(1000);
            }

            returnNum = OptionWhenChoseLevel();
        }

    }
    //写出用户数据，游戏结束。
    wirteFile(player);
    return 0;
}
