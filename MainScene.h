#pragma once
#include <QtWidgets/QWidget>
#include "ui_MainScene.h"
#include "Block.h"
#include "Charactors.h"
#include <QTimer>
#include <QKeyEvent>
#include<QList>
#include "Medicine.h"
class MainScene : public QWidget
{
    Q_OBJECT
        
public:
    MainScene(QWidget* parent);
    ~MainScene();
    void  initScene();
    void StartGame(int id);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* key);
    void keyReleaseEvent(QKeyEvent* key);
    void pause();
    void game_continue();
    void dead_game_over();
    void show_start_menu();
    void hide_start_menu();
    void show_upgrate_menu();
    void hide_upgrade_menu();
    void win_game_over();
    void game_main();
    void enemy_spown();

private:
    Ui::MainSceneClass ui;
    int seed; 
    Block block;
    QPixmap map_img;
    Charactors* player=nullptr;
    QTimer timer;
    QTimer total_timer;
    QTimer enemy_spown_timer;
    int time=GAME_TIME;//倒计时
    QList<enemy_1*> enemies_1;
    QList<enemy_2*> enemies_2;
    QList<bullet*> bullets;//子弹类
    QList <Medicine*> medicines;//回复药类（后期可扩展为掉落物类）
    int all_hp=0;
    int all_level=0;
    int all_speed=0;
    int kill_count=0;
    int level_point=0;
    int level_point_time=0;
    QString s;
};
