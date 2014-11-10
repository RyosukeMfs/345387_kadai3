/************************
 学生証番号: 345387
 氏     名: 盛房 亮輔
 
 課　　　題: 「電気力線を描くプログラム」
 プログラム名: denki.c
 ***********************/

#include <stdio.h>
#include <stdlib.h>
#include <eggx.h>
#include <math.h>

#define WIDTH  600
#define HEIGHT 600
#define PI 3.1415926

int main(void)
{
    /* 変数の宣言 */
    int win, count;
    double x, y, r, theta, e_r, e_theta, theta2, ds, ds_x, ds_y, l=15.0;
    
    /* 変数の説明
     int型
       count : ループが何周したか数える変数
     
     double型
        x, y : x, y 座標値
           r : 原点から点Pまでの距離（ r^2 = x^2+y^2) の値
       theta : PO+q の3つの点の間の角度の値
        e_r  : Er(r, θ)の値
     e_theta : Eθ(r, θ)の値
      theta2 : PとP'と x軸 の角度の値
          ds : 微小距離
        ds_x : 微小距離動かすごとの x座標の変化量
        ds_y : 微小距離動かすごとの y座標の変化量
           l : 2点 +q, -q 間の距離
     */
    
    /**** 描画開始 *****/
    win = gopen(WIDTH, HEIGHT);             // 画面を開く
    winname(win, "line of electric force"); // 画面に名前をつける
    
    /* 座標軸の描画 */
    newpen(win, 1); // 色は白
    line(win, 5.0, 300.0, PENUP);
    line(win, 595.0, 300.0, PENDOWN);
    line(win, 300.0, 5.0, PENUP);
    line(win, 300.0, 595.0, PENDOWN);
    /* 原点, +q, -q の描画 */
    newpen(win, 7); // 色は黄
    fillcirc(win, WIDTH/2.0, HEIGHT/2.0, 3.0, 3.0);
    fillcirc(win, WIDTH/2.0, HEIGHT/2.0+l/2.0, 3.0, 3.0);
    fillcirc(win, WIDTH/2.0, HEIGHT/2.0-l/2.0, 3.0, 3.0);
    drawstr(win, WIDTH/2.0-20.0, HEIGHT/2.0-5.0, 20, 0.0, "O");
    drawstr(win, WIDTH/2.0-25.0, HEIGHT/2.0+20.0, 20, 0.0, "+q");
    drawstr(win, WIDTH/2.0-25.0, HEIGHT/2.0-25.0, 20, 0.0, "-q");
    /* 原点から x軸方向に 5L, 7L, 10L, 15L の距離の点の描画 */
    fillcirc(win, WIDTH/2.0+5*l, HEIGHT/2.0, 3.0, 3.0);
    fillcirc(win, WIDTH/2.0+7*l, HEIGHT/2.0, 3.0, 3.0);
    fillcirc(win, WIDTH/2.0+10*l, HEIGHT/2.0, 3.0, 3.0);
    fillcirc(win, WIDTH/2.0+15*l, HEIGHT/2.0, 3.0, 3.0);
    drawstr(win, WIDTH/2.0+5*l-20.0, HEIGHT/2.0+10.0, 20, 0.0, "5L");
    drawstr(win, WIDTH/2.0+7*l-20.0, HEIGHT/2.0+10.0, 20, 0.0, "7L");
    drawstr(win, WIDTH/2.0+10*l-20.0, HEIGHT/2.0+10.0, 20, 0.0, "10L");
    drawstr(win, WIDTH/2.0+15*l-20.0, HEIGHT/2.0+10.0, 20, 0.0, "15L");
    
    /* 初期点 P の x, y 座標値 */
    x = 5.0*l;
    y = 0.0;
    
    /* 微小距離 ds を設定 */
    ds = l/100.0;
    
    
    /******* 電気力線の描画処理 *******/
    count = 0; // 初期化
    newpen(win, 2); // 色は赤
    /** ループ開始 **/
    while (count < 4)
    {
        switch (count) {
            case 1:
                x = 7.0*l;
                break;
            case 2:
                x = 10.0*l;
                break;
            case 3:
                x = 15.0*l;
                break;
            default:
                break;
        }
        do {
            pset(win, WIDTH/2.0+x, HEIGHT/2.0+y);
            pset(win, WIDTH/2.0+x, HEIGHT/2.0-y);
            r = sqrt(x*x + y*y);
            theta = PI/2.0-atan(y/x);
            e_r = cos(theta);
            e_theta = sin(theta)/2.0;
            theta2 = atan(e_r/e_theta)-theta;
            ds_x = ds*cos(theta2);
            ds_y = ds*sin(theta2);
            x += ds_x;
            y += ds_y;
        } while (x >= 0.0);
        count++;
    }/** ループ終了 **/
    
    /********** 描画終了 ***********/
    
    ggetch();    // 何かキーを押すと
    gclose(win); // 画面を閉じる
    return 0;
}
//  プログラム終了