/************************
 学生証番号: 345387
 氏     名: 盛房 亮輔
 
 テーマ「バスのアニメーション」
 
 2final.c
 ***********************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <eggx.h>

/* プリプロセッサー */
#define WIDTH  600
#define HEIGHT 600
#define PI 3.1415926

/* グローバル変数の宣言 */
int win;
int time = 0;       // 時間経過を数える変数
int sprTime = 650;  // 春になる時間
int sumTime = 1420; // 夏になる時間
int autTime = 2190; // 秋になる時間
double move = 4.0;  // 速度
double ex_r = 30.0; // 爆発円の半径


/********** 関数プロトタイプ宣言 **********/
void background(void);  // バスより奥の関数を描く関数
void drawBus(void);     // 主役のバスを描く関数
void background2(void); // バスより手前の関数を描く関数

/* 関数 background 内 */
void sky_winter(void);  // 空を描く関数　（冬）
void sky_spring(void);  // 空を描く関数　（春）
void sky_summer(void);  // 空を描く関数　（夏）
void sky_autumn(void);  // 空を描く関数　（秋）
void sun(void);         // 太陽を描く関数
void settingsun(void);  // 太陽（夕日）を描く関数（秋）
void cloud(void);       // 雲を描く関数
void mountain(void);    // 山を描く関数
void building(void);    // ビルを描く関数
void sidewalk(void);    // 歩道を描く関数
void tree(void);        // 街路樹を描く関数
void busstop(void);     // バス停を描く関数
void people(void);      // 人を描く関数
void devil(void);       // 強盗を描く関数（秋）
void road(void);        // 車道を描く関数
/* 関数 background2 内 */
void car(void);         // 対向車を描く関数
void patrol(void);      // パトカーを描く関数
void tree2(void);       // 街路樹を描く関数
void snow(void);        // 降ってくる雪を描く関数（冬限定）
void blossom(void);     // 降ってくる桜の花を描く関数（春限定）
void telop(void);       // テロップを表示させる関数
void explode(void);     // 爆発するところを描画する関数
/********** 関数プロトタイプ宣言終了 **********/




/***************** main関数 *******************/
int main(void)
{
    
    /* オープニング画面の描画 */
    while (1) {
        win=gopen(WIDTH, HEIGHT); // 画面を開く
        winname(win, "start");
        newpen(win, 3);
        
        /* 文字を表示 */
        gsetfontset(win, "-*-helvetica-medium-r-normal--70-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--50-*-*-*-*-*-jisx0208.1983-0");
        drawstr(win, WIDTH/2.0-300.0, HEIGHT-120.0, FONTSET, 0.0, "「バスのアニメーション」");
        newrgbcolor(win, 255, 255, 200);
        gsetfontset(win, "-*-helvetica-medium-r-normal--70-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--30-*-*-*-*-*-jisx0208.1983-0");
        drawstr(win, WIDTH/2.0-250.0, HEIGHT/2.0+50.0, FONTSET, 0.0, "学生証番号： ３４５３８７");
        gsetfontset(win, "-*-helvetica-medium-r-normal--70-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--30-*-*-*-*-*-jisx0208.1983-0");
        drawstr(win, WIDTH/2.0-250.0, HEIGHT/2.0, FONTSET, 0.0, "氏　　　名： 盛房 亮輔");
        newpen(win, 7);
        gsetfontset(win, "-*-helvetica-medium-r-normal--40-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--38-*-*-*-*-*-jisx0208.1983-0");
        drawstr(win, WIDTH/2.0-295.0, HEIGHT/2.0-150.0, FONTSET, 0.0, "SPACEキーを押すと、始まります");
        gsetfontset(win, "-*-helvetica-medium-r-normal--40-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--25-*-*-*-*-*-jisx0208.1983-0");
        drawstr(win, WIDTH/2.0-260.0, HEIGHT/2.0-200.0, FONTSET, 0.0, "（それ以外のキーが押されても始まりません）");
        if (0x020 == ggetch()) break; // spaceキーが押されたらループを抜け出す
        gclose(win); // spaceキーが押されなかったら、ループ（画面を閉じて、また同じ画面を開く）する
    }
    gclose(win); // オープニング画面を閉じる
    
    
    /*** メイン画面の描画 ***/
    win=gopen(WIDTH, HEIGHT);  // 画面を開く
    winname(win, "2final.c");
    gsetbgcolor(win, "white"); // 画面の背景色は白
    gclr(win);
    
    /*** メインのアニメーションの描画をするループ ***/
    while (1) {
        gclr(win);
        background();  // 背景（バスより奥）を描く関数へ
        drawBus();     // 主役のバスを描く関数へ
        background2(); // 背景（バスより手前）を描く関数へ
        time++; // ループするたびに時間経過を表す変数timeの値を1増やす
        if ((time >= 175 && time <= 260) || (time >= sprTime+275 && time <= sprTime+360) || (time >= sumTime+275 && time <= sumTime+360) || (time >= autTime+275 && time <= autTime+360)) {
            if (move >= 0.05) move -= 0.05;
        } // バス停に近づくにつれ減速
        if ((time >= 320 && time <= sprTime-100) || (time >= sprTime+420 && time <= sumTime-100) || (time >= sumTime+420 && time <= autTime-100) || (time >= autTime+420 && time <= 2980)) {
            if (move <= 3.95) move += 0.05;
        } // バスがバス停から出発すると加速（一定の速さまで）
        if (time >= autTime+1630) {
            if (move <= 12.0) move += 0.05;
        } // パトカーから逃げるとき、加速（高速）
        msleep(20);
        if (ex_r >= WIDTH+100) break; // 爆発が大きくなったら、ループを抜け出す
    }
    
    /* 最後に文字を表示 */
    newpen(win, 7);
    gsetfontset(win, "-*-helvetica-medium-r-normal--50-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--50-*-*-*-*-*-jisx0208.1983-0");
    drawstr(win, WIDTH/2.0, HEIGHT/2.0, FONTSET, 0.0, "〜おしまい〜");
    gsetfontset(win, "-*-helvetica-medium-r-normal--40-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--40-*-*-*-*-*-jisx0208.1983-0");
    drawstr(win, WIDTH/2.0-295.0, HEIGHT/2.0-150.0, FONTSET, 0.0, "どこかキーを押すと、終了します");
    
    ggetch();    // 何かキーが入力されると
    gclose(win); // 画面を閉じる
    return 0;
}
/************ main関数終了（プログラム終了） ****************/



/***** 背景（バスより奥）を描く関数 (main関数からジャンプ） *****/
void background(void)
{
    if (time >= 0 && time < sprTime) {
        sky_winter(); // 空を描く関数へ　（冬）
    } else if (time >= sprTime && time < sumTime) {
        sky_spring(); // 空を描く関数へ　（春）
    } else if (time >= sumTime && time < autTime) {
        sky_summer(); // 空を描く関数へ　（夏）
    } else {
        sky_autumn(); // 空を描く関数へ　（秋）
    }
    if (time >= sprTime+10) {
        if (time <= autTime) {
            sun();    // 太陽を描く関数へ（春、夏）
        } else {
            settingsun(); // 夕日を描く関数へ（秋）
        }
    }
    if (time < sumTime || time >= autTime) {
        cloud();      // 雲を描く関数へ
    }
    mountain();       // 山を描く関数へ
    building();       // ビルを描く関数へ
    sidewalk();       // 歩道を描く関数へ
    tree();           // 街路樹を描く関数へ
    busstop();        // バス停を描く関数へ
    if (time <= 300 || (time >= sprTime+200 && time <= sprTime+400) || (time >= sumTime+200 && time <= sumTime+400)) people(); // 人を描く関数へ
    if (time >= autTime+200) devil();          // 強盗を描く関数へ
    road();           // 車道を描く関数へ
}
/***** バスを描く関数 (main関数からジャンプ) *****/
void drawBus(void)
{
    static double bX, theta3;
    double bY = 200.0;
    double w=240.0, h=80.0;
    double tireL = bX+w/4.0, tireR = bX+w/4.0*3.0;
    double r=25.0, theta;
    double i;
    
    if (time == 0) theta3 = 2*PI;
    if (time < autTime+1850) bX = 70.0;
    if (time >= autTime+1850) {
        if (bX+w <= WIDTH) bX += 1.0;
    }
    /* 本体 */
    newpen(win, 3);
    fillrect(win, bX, bY, w, h);
    /* タイヤ */
    newpen(win, 0);
    fillcirc(win, tireL, bY+10.0, r, r);
    fillcirc(win, tireR, bY+10.0, r, r);
    newpen(win, 1);
    drawarc(win, tireL, bY+10.0, r, r, 0.0, 180.0, -1);
    drawarc(win, tireR, bY+10.0, r, r, 0.0, 180.0, -1);
    drawcirc(win, tireL, bY+10.0, r/2.0, r/2.0);
    drawcirc(win, tireR, bY+10.0, r/2.0, r/2.0);
    /* 窓 */
    newpen(win, 8);
    fillrect(win, bX+200, bY+30.0, 35.0, 45.0);
    for (i = 50.0; i <= 155.0; i += 35.0) {
        fillrect(win, bX+i, bY+40.0, 30.0, 30.0);
    }
    fillrect(win, bX+15.0, bY+30.0, 15.0, 40.0);
    /* タイヤの中 */
    newpen(win, 1);
    for (theta = 0; theta <= 2*PI; theta += PI/4.0) {
        fillcirc(win, tireL+18.0*cos(theta+theta3), bY+10.0+20.0*sin(theta+theta3), 2.0, 2.0);
        fillcirc(win, tireR+18.0*cos(theta+theta3), bY+10.0+20.0*sin(theta+theta3), 2.0, 2.0);
    }
    theta3 -= 0.03*move;
    if (theta3 <= 0.0) theta3 = 2*PI;
}
/***** 背景を描く関数 (main関数からジャンプ) *****/
void background2(void)
{
    car();      // 対向車を描く関数へ
    if (time >= autTime+1100) patrol();  // パトカーを描く関数へ
    tree2();    // 街路樹（対向車側）を描く関数へ
    if (time < sprTime)  snow(); // 雪を降らす関数へ（冬）
    if (time >= sprTime+100 && time < sumTime-100) blossom(); // 桜の花びらを降らす関数へ（春）
    telop();    // テロップを表示する関数へ
    if (time >= 4322) explode(); // 爆発を描画する関数へ
}



/********** サブ関数達 **********/

/*** background からジャンプ ***/
/* 空を描く関数 */
void sky_winter(void) // 冬
{
    int i;
    for (i = 128; i <= 255; i++) {
        newrgbcolor(win, i, i, i);    // グラデーション（灰色）
        fillrect(win, 0.0, HEIGHT-i+127.0, WIDTH, 2.0);
    }
}
void sky_spring(void) // 春
{
    int i;
    for (i = 128; i <= 255; i++) {
        newrgbcolor(win, i, i, 255);  // グラデーション（薄い青色）
        fillrect(win, 0.0, HEIGHT-i+127.0, WIDTH, 2.0);
    }
}
void sky_summer(void) // 夏
{
    int i;
    for (i = 0; i <= 255; i++) {
        newrgbcolor(win, i, i, 255);  // グラデーション（青色）
        fillrect(win, 0.0, HEIGHT-i-1.0, WIDTH, 1.0);
    }
}
void sky_autumn(void) // 秋
{
    int i;
    for (i = 0; i < 255; i++) {
        newrgbcolor(win, 255, 135, 0); // 橙色
        fillrect(win, 0.0, HEIGHT-i-1.0, WIDTH, 1.0);
    }
}
/* 太陽を描く関数 */
void sun(void)
{
    double sX, sY, sR, theta, l;
    
    sR = 18.0; l = sR+15.0;
    sX = WIDTH-2.0*sR;
    sY = HEIGHT-2.0*sR;
    newpen(win, 2);
    fillcirc(win, sX, sY, sR, sR);
    newlinewidth(win, 2);
    for (theta = PI/6.0; theta <= 2*PI+PI/6.0; theta += PI/4.0) {
        drawline(win, sX, sY, sX+l*cos(theta), sY+l*sin(theta));
    }
    newlinewidth(win, 1);
}
/* 夕日を描く関数 */
void settingsun(void)
{
    double sX, sY, sR;
    
    sR = 22.0;
    sX = WIDTH-3.0*sR;
    sY = HEIGHT-3.0*sR;
    newpen(win, 7);
    fillcirc(win, sX, sY, sR, sR);
}
/* 雲を描く関数 */
void cloud(void)
{
    int i;
    static double cX[4];
    double cY=HEIGHT-30.0, r=15.0;
    
    if (time == 0 || time == autTime) {
        cX[0] = 150.0;
        cX[1] = 300.0;
        cX[2] = 450.0;
        cX[3] = WIDTH;
    }
    newpen(win, 1);
    for (i = 0; i < 4; i++) {
        fillarc(win, cX[i], cY, r, r, 0.0, 180.0, 1);
        fillarc(win, cX[i]+2.0*r, cY, r, r, 0.0, 180.0, 1);
        fillarc(win, cX[i]-r, cY-r, r, r, 90.0, 270.0, 1);
        fillarc(win, cX[i]+3.0*r, cY-r, r, r, 0.0, 90.0, 1);
        fillarc(win, cX[i]+3.0*r, cY-r, r, r, 0.0, 90.0, -1);
        fillarc(win, cX[i], cY-2.0*r, r, r, 0.0, -180.0, -1);
        fillarc(win, cX[i]+2.0*r, cY-2.0*r, r, r, 0.0, -180.0, -1);
        fillrect(win, cX[i]-r, cY-2.0*r, 4.0*r, 2.0*r);
        cX[i] -= 0.5*move;
        if ((cX[i]+3.0*r) <= 0.0) cX[i] = WIDTH+r;
    }
}
/* 山を描く関数 */
void mountain(void)
{
    int i;
    static double mX[4], mX2[4];
    double mY[4];
    
    newpen(win, 11);
    if (time == 0) {
        mX[0] = 230.0;
        mX[1] = 350.0;
        mX[2] = 420.0;
        mX[3] = 540.0;
        for (i = 0; i < 4; i++) {
            mX2[i] = mX[i]+350.0;
        }
    }
    if (time == sprTime || time == sumTime || time == autTime) {
        mX[0] = WIDTH;
        mX[1] = WIDTH+120.0;
        mX[2] = WIDTH+190.0;
        mX[3] = WIDTH+310.0;
        for (i = 0; i < 4; i++) {
            mX2[i] = mX[i]+350.0;
        }
    }
    mY[0] = 330.0;
    mY[1] = 560.0;
    mY[2] = 560.0;
    mY[3] = 330.0;
    
    fillpoly(win, mX, mY, 4, 0);
    fillpoly(win, mX2, mY, 4, 0);
    for (i = 0; i < 4; i++) {
        mX[i] -= 0.7*move;
        mX2[i] -= 0.7*move;
    }
    
    if ((time >= 0 && time < sprTime-250) || (time >= sprTime && time <= sumTime-250) || (time >= sumTime && time <= autTime-250) || time >= autTime) {
        if (mX[3] <= 0.0) {
            for (i = 0; i < 4; i++) {
                mX[i] += WIDTH+300.0;
            }
        }
        if (mX2[3] <= 0.0) {
            for (i = 0; i < 4; i++) {
                mX2[i] += WIDTH+300.0;
            }
        }
    }
}
/* ビルを描く関数 */
void building(void)
{
    int i;
    static double builX[7];
    double j, k, w=90.0, h=180.0;
    
    if (time == 0) {
        for (i = 0; i < 7; i++) {
            builX[i] = 10+i*100.0;
        }
    }
    if (time == sprTime || time == sumTime || time == autTime) {
        for (i = 0; i < 7; i++) {
            builX[i] = WIDTH+10+i*100.0;
        }
    }
    
    for (i = 0; i < 7; i++) {
        newpen(win, 8);
        fillrect(win, builX[i], 320.0, w, h); // 本体
        // 窓
        for (j = h/9.0; j <= h-(h/9.0)*2.0; j += (h/9.0)*2.0) {
            for (k = w/15.0; k <= w; k += (w/15.0)*5.0) {
                newpen(win, 0); // 窓の淵
                fillrect(win, builX[i]+k-2, 320.0+j-2, 3.0*(w/15.0)+4, (h/9.0)+4);
                newpen(win, 7);
                fillrect(win, builX[i]+k, 320.0+j, 3.0*(w/15.0), (h/9.0));
            }
        }
        builX[i] -= 1.0*move;
        if ((time >= 0 && time < sprTime-180) || (time >= sprTime && time <= sumTime-180) || (time >= sumTime && time <= autTime-180) || (time >= autTime && time <= 2860)) {
            if (builX[i]+100.0 <= 0.0) builX[i] = WIDTH;
        }
    }
}
/* 歩道を描く関数 */
void sidewalk(void)
{
    /* 歩道の描画 */
    newpen(win, 9);
    fillrect(win, 0.0, 250.0, WIDTH, 60.0);
    fillrect(win, 0.0, 40.0, WIDTH, 60.0);
    // 対向車側
    newpen(win,8);
    fillrect(win, 0.0, 0.0, WIDTH, 40.0);
}
/* 街路樹の描画 */
void tree(void)
{
    int i;
    static double treeX[7];
    
    if (time == 0) {
        for (i = 0; i < 7; i++) {
            treeX[i] = 20.0+i*100.0;
        }
    }
    if (time == sprTime || time == sumTime || time == autTime) {
        for (i = 0; i < 7; i++) {
            treeX[i] = WIDTH+20.0+i*100.0;
        }
    }
    if (time <= sprTime) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, treeX[i], 300.0, 20.0, 40.0);
            newlinewidth(win, 6);
            drawline(win, treeX[i]+10.0, 340.0, treeX[i]+10.0, 430.0);
            drawline(win, treeX[i]+10.0, 360.0, treeX[i]-20.0, 390.0);
            drawline(win, treeX[i]+10.0, 360.0, treeX[i]+40.0, 390.0);
            drawline(win, treeX[i]+10.0, 400.0, treeX[i]-20.0, 420.0);
            drawline(win, treeX[i]+10.0, 400.0, treeX[i]+40.0, 420.0);
            treeX[i] -= 1.0*move;
            if (time >= 0 && time < sprTime-180) {
                if (treeX[i]+40.0 <= 0.0) {
                    treeX[i] = WIDTH+70.0;
                }
            }
        }
        newlinewidth(win, 1);
    }
    if (time >= sprTime && time < sumTime) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, treeX[i], 300, 20.0, 40.0);
            newrgbcolor(win, 254, 238, 237);
            fillcirc(win, treeX[i]+10.0, 380.0, 40.0, 50.0);
            treeX[i] -= 1.0*move;
            if (time >= sprTime && time < sumTime-180) {
                if (treeX[i]+40.0 <= 0.0) {
                    treeX[i] = WIDTH+70.0;
                }
            }
        }
    }
    if (time >= sumTime && time < autTime) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, treeX[i], 300, 20.0, 40.0);
            newrgbcolor(win, 0, 255, 0);
            fillcirc(win, treeX[i]+10.0, 380.0, 45.0, 50.0);
            treeX[i] -= 1.0*move;
            if (time >= sumTime && time <= autTime-180) {
                if (treeX[i]+45.0 <= 0.0) {
                    treeX[i] = WIDTH+70.0;
                }
            }
        }
    }
    if (time >= autTime && time <= 3160) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, treeX[i], 300, 20.0, 40.0);
            newrgbcolor(win, 255, 255, 0);
            fillcirc(win, treeX[i]+10.0, 380.0, 45.0, 50.0);
            treeX[i] -= 1.0*move;
            if (time >= autTime && time <= 2960) {
                if (treeX[i]+45.0 <= 0.0) {
                    treeX[i] = WIDTH+70.0;
                }
            }
        }
    }
}
/* バス停を描く関数 */
void busstop(void)
{
    static double busstopX;
    if (time == 100 || time == sprTime+200 || time == sumTime+200 || time == autTime+200) {
        busstopX = 670.0;
    }
    newpen(win, 0);
    drawline(win, busstopX, 250.0, busstopX, 320.0);
    fillcirc(win, busstopX, 250.0, 10.0, 5.0);
    newpen(win, 8);
    fillrect(win, busstopX-7.5, 260.0, 15.0, 45.0);
    newpen(win, 4);
    fillcirc(win, busstopX, 320.0, 12.0, 12.0);
    newpen(win, 7);
    drawcirc(win, busstopX, 320.0, 12.0, 12.0);
    busstopX -= 1.0*move;
}
/* 人の描画 */
void people(void)
{
    int i;
    static double man_x[14], woman_x[18];
    double man_y[14], woman_y[18];
    // 男
    if (time == 100 || time == sprTime+200 || time == sumTime+200 || time == autTime+200) {
        man_x[0] = 6.0;
        man_x[1] = 0.0;
        man_x[2] = 2.0;
        man_x[3] = 6.0;
        man_x[4] = 6.0;
        man_x[5] = 10.0;
        man_x[6] = 10.0;
        man_x[7] = 12.0;
        man_x[8] = 12.0;
        man_x[9] = 16.0;
        man_x[10] = 16.0;
        man_x[11] = 20.0;
        man_x[12] = 22.0;
        man_x[13] = 16.0;
        for (i = 0; i < 14; i++) {
            man_x[i] += 700.0;
        }
    }
    man_y[0] = 65.0;
    man_y[1] = 40.0;
    man_y[2] = 35.0;
    man_y[3] = 50.0;
    man_y[4] = 10.0;
    man_y[5] = 10.0;
    man_y[6] = 45.0;
    man_y[7] = 45.0;
    man_y[8] = 10.0;
    man_y[9] = 10.0;
    man_y[10] = 50.0;
    man_y[11] = 35.0;
    man_y[12] = 40.0;
    man_y[13] = 65.0;
    for (i = 0; i < 14; i++) {
        man_y[i] += 240.0;
    }
    newpen(win, 4);
    if (time >= sprTime+200 && time < sumTime) {
        for (i = 0; i < 2; i++) {
            fillcirc(win, man_x[6]+1+i*40.0, 75.0+240.0, 8.0, 8.0);
        }
        fillpoly(win, man_x, man_y, 14, 0);
        for (i = 0; i < 14; i++) {
            man_x[i] += 40.0;
        }
        fillpoly(win, man_x, man_y, 14, 0);
        for (i = 0; i < 14; i++) {
            man_x[i] -= 40.0;
        }
    } else if (time < autTime+200) {
        fillcirc(win, man_x[6]+1, 75.0+240.0, 8.0, 8.0);
        fillpoly(win, man_x, man_y, 14, 0);
    }
    for (i = 0; i < 14; i++) {
        man_x[i] -= 1.0*move;
    }
    // 女
    if (time == 100 || time == sprTime+200 || time == sumTime+200 || time == autTime+200) {
        woman_x[0] = 6.0;
        woman_x[1] = 0.0;
        woman_x[2] = 1.0;
        woman_x[3] = 5.0;
        woman_x[4] = 4.0;
        woman_x[5] = 6.0;
        woman_x[6] = 6.0;
        woman_x[7] = 8.0;
        woman_x[8] = 8.0;
        woman_x[9] = 10.0;
        woman_x[10] = 10.0;
        woman_x[11] = 12.0;
        woman_x[12] = 12.0;
        woman_x[13] = 15.0;
        woman_x[14] = 14.0;
        woman_x[15] = 17.0;
        woman_x[16] = 18.0;
        woman_x[17] = 12.0;
        for (i = 0; i < 18; i++) {
            woman_x[i] += 720.0;
        }
    }
    woman_y[0] = 60.0;
    woman_y[1] = 35.0;
    woman_y[2] = 30.0;
    woman_y[3] = 40.0;
    woman_y[4] = 25.0;
    woman_y[5] = 25.0;
    woman_y[6] = 10.0;
    woman_y[7] = 10.0;
    woman_y[8] = 25.0;
    woman_y[9] = 25.0;
    woman_y[10] = 10.0;
    woman_y[11] = 10.0;
    woman_y[12] = 25.0;
    woman_y[13] = 25.0;
    woman_y[14] = 40.0;
    woman_y[15] = 30.0;
    woman_y[16] = 35.0;
    woman_y[17] = 60.0;
    for (i = 0; i < 18; i++) {
        woman_y[i] += 240.0;
    }
    newpen(win, 2);
    if (time >= sprTime+200 && time < sumTime) {
        for (i = 0; i < 2; i++) {
            fillcirc(win, woman_x[8]+1+i*40.0, 70.0+240.0, 6.0, 6.0);
        }
        fillpoly(win, woman_x, woman_y, 18, 0);
        for (i = 0; i < 18; i++) {
            woman_x[i] += 40.0;
        }
        fillpoly(win, woman_x, woman_y, 18, 0);
        for (i = 0; i < 18; i++) {
            woman_x[i] -= 40.0;
        }
    } else if (time < autTime+200) {
        fillcirc(win, woman_x[8]+1, 70.0+240.0, 6.0, 6.0);
        fillpoly(win, woman_x, woman_y, 18, 0);
    }
    for (i = 0; i < 18; i++) {
        woman_x[i] -= 1.0*move;
    }
}
/* 強盗を描く関数 */
void devil(void)
{
    int i;
    static double devilX[14], gunX[8];
    double devilY[14], gunY[8];
    
    if (time == autTime+200.0) {
        devilX[0] = 6.0;
        devilX[1] = 2.0;
        devilX[2] = 0.0;
        devilX[3] = 6.0;
        devilX[4] = 6.0;
        devilX[5] = 10.0;
        devilX[6] = 10.0;
        devilX[7] = 12.0;
        devilX[8] = 12.0;
        devilX[9] = 16.0;
        devilX[10] = 16.0;
        devilX[11] = 20.0;
        devilX[12] = 22.0;
        devilX[13] = 16.0;
        for (i = 0; i < 14; i++) {
            devilX[i] *= 2.0;
            devilX[i] += 700.0;
        }
        gunX[0] = 9.0;
        gunX[1] = 6.0;
        gunX[2] = 10.0;
        gunX[3] = 13.0;
        gunX[4] = 14.0;
        gunX[5] = 15.0;
        gunX[6] = 2.0;
        gunX[7] = 0.0;
        for (i = 0; i < 8; i++) {
            gunX[i] *= 1.5;
            gunX[i] += 685.0;
        }
    }
    devilY[0] = 65.0;
    devilY[1] = 80.0;
    devilY[2] = 75.0;
    devilY[3] = 50.0;
    devilY[4] = 10.0;
    devilY[5] = 10.0;
    devilY[6] = 45.0;
    devilY[7] = 45.0;
    devilY[8] = 10.0;
    devilY[9] = 10.0;
    devilY[10] = 50.0;
    devilY[11] = 35.0;
    devilY[12] = 40.0;
    devilY[13] = 65.0;
    gunY[0] = 6.0;
    gunY[1] = 2.0;
    gunY[2] = 0.0;
    gunY[3] = 5.0;
    gunY[4] = 4.0;
    gunY[5] = 7.0;
    gunY[6] = 18.0;
    gunY[7] = 14.0;
    for (i = 0; i < 14; i++) {
        devilY[i] += 240.0;
    }
    for (i = 0; i < 8; i++) {
        gunY[i] += 315.0;
    }
    
    if (time <= autTime+400.0) {
        newpen(win, 0);
        fillcirc(win, devilX[6]+1, 75.0+245.0, 12.0, 12.0);
        newpen(win, 1);
        fillcirc(win, devilX[6]+6, 75.0+250.0, 2.0, 2.0);
        fillcirc(win, devilX[6]-4, 75.0+250.0, 2.0, 2.0);
        fillrect(win, devilX[6]-4, 75.0+240.0, 10.0, 3.0);
        newpen(win, 0);
        drawline(win, devilX[6]-2, 75.0+243.0, devilX[6]-2, 75.0+240.0);
        drawline(win, devilX[6], 75.0+243.0, devilX[6], 75.0+240.0);
        drawline(win, devilX[6]+2, 75.0+243.0, devilX[6]+2, 75.0+240.0);
        drawline(win, devilX[6]+4, 75.0+243.0, devilX[6]+4, 75.0+240.0);
        fillpoly(win, gunX, gunY, 8, 0);
        fillpoly(win, devilX, devilY, 14, 0);
        for (i = 0; i < 14; i++) {
            devilX[i] -= 1.0*move;
        }
        for (i = 0; i < 8; i++) {
            gunX[i] -= 1.0*move;
        }
    }
}
/* 車道を描く関数 */
void road(void)
{
    int i;
    static double roadwayX[14];
    newpen(win, 8);
    fillrect(win, 0, 100.0, WIDTH, 150.0);
    newpen(win, 1);
    fillrect(win, 0, 170.0, WIDTH, 5.0);
    newpen(win, 8);
    if (time == 0) {
        for (i = 0; i < 14; i++) {
            roadwayX[i] = 20.0+i*45.0;
        }
    }
    for (i = 0; i < 14; i++) {
        fillrect(win, roadwayX[i], 170.0, 15.0, 5.0);
        roadwayX[i] -= 1.0*move;
        if (roadwayX[i]+15.0 <= 0.0) {
            roadwayX[i] = WIDTH;
        }
    }
}



/***** background2 からジャンプ *****/
/* 対向車を描く関数 */
void car(void)
{
    int i;
    static double cX[3], theta2, color_r[3], color_g[3], color_b[3];
    double cY, r=15.0, theta;
    
    if (time == 0) {
        for (i = 0; i < 3; i++) {
            cX[i] = 470.0+i*250.0;
            color_r[i] = rand()%255;
            color_g[i] = rand()%255;
            color_b[i] = rand()%255;
        }
        theta2 = 0.0;
    }
    if (time == sprTime+50 || time == sumTime+50 || time == autTime+50) {
        for (i = 0; i < 3; i++) {
            cX[i] = 670.0+i*(250.0+(double)(rand()%150));
            color_r[i] = rand()%255;
            color_g[i] = rand()%255;
            color_b[i] = rand()%255;
        }
        theta2 = 0.0;
    }
    cY = 170.0;
    for (i = 0; i < 3; i++) {
        newrgbcolor(win, color_r[i], color_g[i], color_b[i]);
        fillarc(win, cX[i], cY, 45.0, 30.0, 0.0, 180.0, 1);
        fillarc(win, cX[i]-60.0, cY-40.0, 10.0, 40.0, 90.0, 180.0, 1);
        fillarc(win, cX[i]+60.0, cY-40.0, 10.0, 40.0, 0.0, 90.0, 1);
        fillrect(win, cX[i]-60.0, cY-40.0, 120.0, 40.0);
        newpen(win, 0);
        fillrect(win, cX[i]-41.0, cY-14.0, 22.0, 22.0);
        fillrect(win, cX[i]-13.0, cY-14.0, 22.0, 22.0);
        fillrect(win, cX[i]+15.0, cY-14.0, 22.0, 22.0);
        newpen(win, 9);
        fillrect(win, cX[i]-39.0, cY-12.0, 18.0, 18.0);
        fillrect(win, cX[i]-11.0, cY-12.0, 18.0, 18.0);
        fillrect(win, cX[i]+17.0, cY-12.0, 18.0, 18.0);
        newpen(win, 1);
        fillarc(win, cX[i]-30.0, cY-42.0, r+1, r+1, 0.0, 180.0, -1);
        fillarc(win, cX[i]+30.0, cY-42.0, r+1, r+1, 0.0, 180.0, -1);
        newrgbcolor(win, 0, 70, 100);
        fillcirc(win, cX[i]-30.0, cY-42.0, r, r);
        fillcirc(win, cX[i]+30.0, cY-42.0, r, r);
        newpen(win, 1);
        for (theta = -PI/3.0; theta <= 2*PI; theta += 2.0*PI/3.0) {
            fillcirc(win, (cX[i]-30.0)+8.0*cos(theta+theta2), (cY-42.0)+8.0*sin(theta+theta2), 2.0, 2.0);
            fillcirc(win, (cX[i]+30.0)+8.0*cos(theta+theta2), (cY-42.0)+8.0*sin(theta+theta2), 2.0, 2.0);
        }
        cX[i] -= 3.0*move+2.0;
        if ((time >= 0 && time < sprTime-100) || (time >= sprTime+50 && time < sumTime-100) || (time >= sumTime+50 && time < autTime-100) || (time >= autTime+50 && time < 3060)) {
            if (cX[i]+70.0 <= 0.0) {
                cX[i] = WIDTH+250.0;
            }
        }
    }
    theta2 += 0.1*move+0.1;
    if (theta2 >= 2*PI) {
        theta2 = 0.0;
    }
}
/* パトカーを描く関数 */
void patrol(void)
{
    static double pX, pY, theta4;
    double qX[4], qY[4];
    double r=15.0, theta;
    if (time == autTime+1100) {
        pX = -200.0;
        theta4 = 2*PI;
    }
    pY = 170.0;
    qX[0] = pX-20.0;
    qX[1] = pX-60.0;
    qX[2] = pX+60.0;
    qX[3] = pX+20.0;
    qY[0] = pY+35.0;
    qY[1] = pY+10.0;
    qY[2] = pY+10.0;
    qY[3] = pY+35.0;
    /* 車の本体 */
    newpen(win, 1);
    fillpoly(win, qX, qY, 4, 0);
    newpen(win, 2);
    fillcirc(win, pX, pY+43.0, 15.0, 5.0);
    fillrect(win, pX-2.0, pY+35.0, 4.0, 5.0);
    newpen(win, 0);
    fillarc(win, pX-60.0, pY-30.0, 10.0, 40.0, 90.0, 180.0, 1);
    fillarc(win, pX+60.0, pY-30.0, 10.0, 40.0, 0.0, 90.0, 1);
    fillrect(win, pX-60.0, pY-30.0, 120.0, 20.0);
    newpen(win, 1);
    fillarc(win, pX-60.0, pY-10.0, 10.0, 20.0, 90.0, 180.0, 1);
    fillarc(win, pX+60.0, pY-10.0, 10.0, 20.0, 0.0, 90.0, 1);
    fillrect(win, pX-60.0, pY-10.0, 120.0, 20.0);
    /* 窓 */
    newpen(win, 0);
    fillrect(win, pX-41.0, pY-8.0, 26.0, 20.0);
    fillrect(win, pX+15.0, pY-8.0, 26.0, 20.0);
    newpen(win, 9);
    fillrect(win, pX-39.0, pY-6.0, 22.0, 16.0);
    fillrect(win, pX+17.0, pY-6.0, 22.0, 16.0);
    /* タイヤ */
    newpen(win, 1);
    fillarc(win, pX-30.0, pY-32.0, r+1, r+1, 0.0, 180.0, -1);
    fillarc(win, pX+30.0, pY-32.0, r+1, r+1, 0.0, 180.0, -1);
    newpen(win, 8);
    fillcirc(win, pX-30.0, pY-32.0, r, r);
    fillcirc(win, pX+30.0, pY-32.0, r, r);
    newpen(win, 1);
    for (theta = -PI/3.0; theta <= 2*PI; theta += 2.0*PI/3.0) {
        fillcirc(win, (pX-30.0)+8.0*cos(theta+theta4), (pY-32.0)+8.0*sin(theta+theta4), 2.0, 2.0);
        fillcirc(win, (pX+30.0)+8.0*cos(theta+theta4), (pY-32.0)+8.0*sin(theta+theta4), 2.0, 2.0);
    }
    theta4 -= 0.03*5.0;
    if (theta4 <= 0.0) theta4 = 2*PI;
    if (pX <= WIDTH/2.0 && time < autTime+1850) pX += 3.0;
    if (time >= autTime+1850) pX -= 3.0;
}
/* 街路樹（対向車側）を描く関数 */
void tree2(void)
{
    int i;
    static double tree2X[7];
    if (time == 0) {
        for (i = 0; i < 7; i++) {
            tree2X[i] = 20.0+i*100.0;
        }
    }
    if (time == sprTime || time == sumTime || time == autTime) {
        for (i = 0; i < 7; i++) {
            tree2X[i] = WIDTH+20.0+i*100.0;
        }
    }
    
    if (time <= sprTime) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, tree2X[i], 10.0, 20.0, 40.0);
            newlinewidth(win, 6);
            drawline(win, tree2X[i]+10.0, 50.0, tree2X[i]+10.0, 140.0);
            drawline(win, tree2X[i]+10.0, 70.0, tree2X[i]-20.0, 100.0);
            drawline(win, tree2X[i]+10.0, 70.0, tree2X[i]+40.0, 100.0);
            drawline(win, tree2X[i]+10.0, 90.0, tree2X[i]-20.0, 130.0);
            drawline(win, tree2X[i]+10.0, 90.0, tree2X[i]+40.0, 130.0);
            tree2X[i] -= 1.0*move;
            if (time >= 0 && time < sprTime-180) {
                if (tree2X[i]+40.0 <= 0.0) {
                    tree2X[i] = WIDTH+70.0;
                }
            }
        }
        newlinewidth(win, 1);
    }
    if (time >= sprTime && time < sumTime) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, tree2X[i], 10.0, 20.0, 40.0);
            newrgbcolor(win, 254, 238, 237);
            fillcirc(win, tree2X[i]+10.0, 90.0, 40.0, 50.0);
            tree2X[i] -= 1.0*move;
            if (time >= sprTime && time <= sumTime-180) {
                if (tree2X[i]+40.0 <= 0.0) {
                    tree2X[i] = WIDTH+70.0;
                }
            }
        }
    }
    if (time >= sumTime && time < autTime) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, tree2X[i], 10, 20.0, 40.0);
            newrgbcolor(win, 0, 255, 0);
            fillcirc(win, tree2X[i]+10.0, 90.0, 45.0, 50.0);
            tree2X[i] -= 1.0*move;
            if (time >= sumTime && time <= autTime-180) {
                if (tree2X[i]+45.0 <= 0.0) {
                    tree2X[i] = WIDTH+70.0;
                }
            }
        }
    }
    if (time >= autTime && time <= 3160) {
        for (i = 0; i < 7; i++) {
            newrgbcolor(win, 153, 76, 0);
            fillrect(win, tree2X[i], 10, 20.0, 40.0);
            newrgbcolor(win, 255, 255, 0);
            fillcirc(win, tree2X[i]+10.0, 90.0, 45.0, 50.0);
            tree2X[i] -= 1.0*move;
            if (time >= autTime && time <= 2960) {
                if (tree2X[i]+45.0 <= 0.0) {
                    tree2X[i] = WIDTH+70.0;
                }
            }
        }
    }
}
/* 雪が降ってくる描画をする関数*/
void snow(void)
{
    int i, seed;
    static double x[50], y[50], kasoku_count[50];
    
    if (time == 0) {
        seed = 4;
        srand(seed);
        for (i = 0; i < 50; i++) {
            x[i] = 200+(double)(rand()%600);
            y[i] = 600+(double)(rand()%600);
            kasoku_count[i] = 0.0;
        }
    }
    newpen(win, 1);
    for (i = 0; i < 50; i++) {
        fillcirc(win, x[i], y[i], 3, 3);
        kasoku_count[i]++;
        x[i] -= 1+0.04*kasoku_count[i];
        y[i] -= 2+0.06*kasoku_count[i];
        if (y[i] < 0.0) {
            x[i] = 200+(double)(rand()%600);
            y[i] = 600;
            kasoku_count[i] = 0;
        }
    }
}
/* 桜の花びらがふってくる描画をする関数 */
void blossom(void)
{
    int i, seed;
    static double x[50], y[50], kasoku_count[50];
    
    if (time == sprTime+100) {
        seed = 4;
        srand(seed);
        for (i = 0; i < 50; i++) {
            x[i] = 200+(double)(rand()%600);
            y[i] = (double)(rand()%600);
            kasoku_count[i] = 0.0;
        }
    }
    newrgbcolor(win, 254, 238, 237);
    for (i = 0; i < 50; i++) {
        fillcirc(win, x[i], y[i], 5.0, 8.0);
        kasoku_count[i]++;
        x[i] -= 1+0.04*kasoku_count[i];
        y[i] -= 2+0.06*kasoku_count[i];
        if (y[i] < 0.0) {
            x[i] = 200+(double)(rand()%600);
            y[i] = 600;
            kasoku_count[i] = 0;
        }
    }
}
/* テロップを表示する（描画する）関数 */
void telop(void)
{
    gsetfontset(win, "-*-helvetica-medium-r-normal--28-*-*-*-*-*-iso8859-1, ""-jis-fixed-medium-r-normal--28-*-*-*-*-*-jisx0208.1983-0");
    
    // 以下、時間経過に合わせて表示
    if (time >= 50 && time <= 170) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 350.0, 40.0);
        newpen(win, 7);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "バスは今日も走り続ける");
    }
    if (time >= 200 && time <= 350) {
        newpen(win, 0);
        fillrect(win, 170.0, 5.0, 280.0, 40.0);
        newpen(win, 7);
        drawstr(win, 190.0, 13.0, FONTSET, 0.0, "雪が降る寒い冬も");
    }
    if (time >= sprTime+150 && time <= sprTime+300) {
        newpen(win, 0);
        fillrect(win, 180.0, 5.0, 200.0, 40.0);
        newpen(win, 7);
        drawstr(win, 200.0, 13.0, FONTSET, 0.0, "桜が舞う春も");
    }
    if (time >= sumTime+150 && time <= sumTime+300) {
        newpen(win, 0);
        fillrect(win, 180.0, 5.0, 200.0, 40.0);
        newpen(win, 7);
        drawstr(win, 200.0, 13.0, FONTSET, 0.0, "クソ暑い夏も");
    }
    if (time >= autTime+80 && time <= autTime+220) {
        newpen(win, 0);
        fillrect(win, 180.0, 5.0, 300.0, 40.0);
        newpen(win, 7);
        drawstr(win, 200.0, 13.0, FONTSET, 0.0, "そして、快適な秋....");
    }
    if (time >= autTime+225 && time <= autTime+240) {
        newpen(win, 0);
        fillrect(win, 230.0, 5.0, 115.0, 40.0);
        newpen(win, 7);
        drawstr(win, 250.0, 13.0, FONTSET, 0.0, "おや？");
    }
    if (time >= autTime+250 && time <= autTime+290) {
        newpen(win, 0);
        fillrect(win, 120.0, 5.0, 350.0, 40.0);
        newpen(win, 7);
        drawstr(win, 140.0, 13.0, FONTSET, 0.0, "銃を持った強盗がいるぞ");
    }
    if (time >= autTime+420 && time <= autTime+480) {
        newpen(win, 0);
        fillrect(win, 180.0, 5.0, 230.0, 40.0);
        newpen(win, 7);
        drawstr(win, 200.0, 13.0, FONTSET, 0.0, "乗ってきた〜〜");
    }
    if (time >= autTime+520 && time <= autTime+580) {
        newpen(win, 0);
        fillrect(win, 120.0, 5.0, 360.0, 40.0);
        newpen(win, 2);
        drawstr(win, 140.0, 13.0, FONTSET, 0.0, "強盗「両手を上げるんだ」");
    }
    if ((time >= autTime+600 && time <= autTime+650) || (time >= autTime+840 && time <= autTime+940)) {
        newpen(win, 0);
        fillrect(win, 160.0, 5.0, 300.0, 40.0);
        newpen(win, 5);
        drawstr(win, 180.0, 13.0, FONTSET, 0.0, "乗客「ヒャー〜！！」");
    }
    if (time >= autTime+680 && time <= autTime+740) {
        newpen(win, 0);
        fillrect(win, 50.0, 5.0, 500.0, 40.0);
        newpen(win, 3);
        drawstr(win, 70.0, 13.0, FONTSET, 0.0, "運転手「ら、乱暴はやめて下さい！」");
    }
    if (time >= autTime+760 && time <= autTime+820) {
        newpen(win, 0);
        fillrect(win, 90.0, 5.0, 450.0, 40.0);
        newpen(win, 2);
        drawstr(win, 110.0, 13.0, FONTSET, 0.0, "強盗「うるせぇ バーン（銃声）」");
    }
    if (time >= autTime+1000 && time <= autTime+1150) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 390.0, 40.0);
        newpen(win, 1);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "「ウーー（サイレンの音）」");
    }
    if (time >= autTime+1300 && time <= autTime+1350) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 350.0, 40.0);
        newpen(win, 1);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "警察「止まりなさい！」");
    }
    if (time >= autTime+1360 && time <= autTime+1410) {
        newpen(win, 0);
        fillrect(win, 30.0, 5.0, 550.0, 40.0);
        newpen(win, 1);
        drawstr(win, 50.0, 13.0, FONTSET, 0.0, "警察「お前は完全に包囲されている！」");
    }
    if (time >= autTime+1450 && time <= autTime+1520) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 440.0, 40.0);
        newpen(win, 2);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "強盗「チッ 邪魔がはいったぜ」");
    }
    if (time >= autTime+1550 && time <= autTime+1600) {
        newpen(win, 0);
        fillrect(win, 30.0, 5.0, 530.0, 40.0);
        newpen(win, 2);
        drawstr(win, 50.0, 13.0, FONTSET, 0.0, "強盗「おいっ スピードを上げるんだ」");
    }
    if (time >= autTime+1620 && time <= autTime+1680) {
        newpen(win, 0);
        fillrect(win, 150.0, 5.0, 330.0, 40.0);
        newpen(win, 3);
        drawstr(win, 170.0, 13.0, FONTSET, 0.0, "運転手「はっ はいー」");
    }
    if (time >= autTime+1800 && time <= autTime+1880) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 320.0, 40.0);
        newpen(win, 1);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "警察「待ちなさい！」");
    }
    if (time >= autTime+1890 && time <= autTime+1950) {
        newpen(win, 0);
        fillrect(win, 80.0, 5.0, 450.0, 40.0);
        newpen(win, 1);
        drawstr(win, 100.0, 13.0, FONTSET, 0.0, "警察「お前は完全に包囲され...」");
    }
    if (time >= autTime+2000 && time <= autTime+2050) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 400.0, 40.0);
        newpen(win, 3);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "運転手「うぁー ぶつかる〜」");
    }
    if (time >= autTime+2080 && time <= autTime+2100) {
        newpen(win, 0);
        fillrect(win, 100.0, 5.0, 350.0, 40.0);
        newpen(win, 3);
        drawstr(win, 120.0, 13.0, FONTSET, 0.0, "運転手「ギャーァ〜〜」");
    }
}
/* 爆発するところを描画する関数 */
void explode(void)
{
    int i;
    newrgbcolor(win, 255, 255, 0);
    fillcirc(win, WIDTH-10.0, 280.0, ex_r+2.0, ex_r+2.0);
    for (i = 0; i < 180; i++) {
        newrgbcolor(win, 255, 180-i, 0);
        fillcirc(win, WIDTH-10.0, 280.0, ex_r-(double)i*(ex_r/3.0*2.0/180.0), ex_r-(double)i*(ex_r/3.0*2.0/180.0));
    }
    newrgbcolor(win, 255, 0, 0);
    fillcirc(win, WIDTH-10.0, 280.0, ex_r/3.0, ex_r/3.0);
    ex_r += 30.0;
}
