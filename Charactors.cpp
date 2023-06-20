#pragma once
#include "Charactors.h"
#include<Qwidget>
#include <QPainter>
void Charactors::paint(QPainter& p) const
{
	p.drawPixmap(get_rect(), img);
	if (w != nullptr)
	{
		w->paint(p);
	}//绘制武器和角色图像
	QBrush brush(QColor("#F20900"));
	p.setBrush(brush);
	float rate = (float)hp / full_hp;
	p.drawRect(position_x - 5, position_y - 0.3 * size, size + 10, 0.2 * size);
	brush.setColor(QColor(255, 255, 255));
	p.setBrush(brush);
	p.drawRect(position_x - 5, position_y - 0.3 * size, rate * (size + 10), 0.2 * size);//绘制血条
}
int  Charactors::get_size()
{
	return size;
}
int  Charactors::get_id() const
{
	return id;
}
void  Charactors::weapon_pause()
{
	if (w != nullptr)
	{
		w->timer.stop();
	}
}
void  Charactors::weapon_continue()
{
	if (w != nullptr)
	{
		w->timer.start();
	}
}
QRect  Charactors::get_rect() const
{
	return QRect(position_x, position_y, size, size);
}
int   Charactors::Charactors::get_level() const
{
	return level;
}
int  Charactors::get_x() const
{
	return position_x;
}
int  Charactors::get_y() const
{
	return position_y;
}
void  Charactors::HP_up()
{
	if (id == 1)
		full_hp += 30;
	else if (id == 2)
		full_hp += 50;
	hp = full_hp;
}
void  Charactors::Speed_up()
{
	speed += 1;
}
void  Charactors::level_up()
{
	level++;
	full_hp += 10;
	hp = full_hp;
	w->interval *= 0.9;
	w->timer.setInterval(w->interval);
	w->range += 5;
	w->atk++;
}
bool  Charactors::is_attacked(const QRect& r)
{
	return get_rect().intersects(r);
}
void  Charactors::keyPressEvent(QKeyEvent* key)
{
	if (key->QKeyEvent::isAutoRepeat() == 0)
	{
		if (key->key() == Qt::Key_W)
		{
			v_y -= speed;
			if (id == 2)
			{
				img.load(RED_HEART_2_IMG);
				w->face = 1;
			}
		}
		if (key->key() == Qt::Key_S)
		{
			v_y += speed;
			if (id == 2)
			{
				img.load(RED_HEART_2__3IMG);
				w->face = 3;
			}
		}
		if (key->key() == Qt::Key_A)
		{
			v_x -= speed;
			if (id == 2)
			{
				img.load(RED_HEART_2__0IMG);
				w->face = 0;
			}
		}
		if (key->key() == Qt::Key_D)
		{
			v_x += speed;
			if (id == 2)
			{
				img.load(RED_HEART_2__2IMG);
				w->face = 2;
			}
		}
	}
}
void  Charactors::keyReleaseEvent(QKeyEvent* key)
{
	if (key->QKeyEvent::isAutoRepeat() == 0)
	{
		if (key->key() == Qt::Key_W)
		{
			v_y += speed;
		}
		if (key->key() == Qt::Key_S)
		{
			v_y -= speed;
		}
		if (key->key() == Qt::Key_A)
		{
			v_x += speed;
		}
		if (key->key() == Qt::Key_D)
		{
			v_x -= speed;
		}
	}
}
void  Charactors::move(Block& block)
{
	position_x += v_x;
	for (int i = 0; i < block.n; ++i)
	{
		if (QRect(position_x, position_y, size, size).intersects(block.b[i]) || position_y > GAME_HEIGHT - size || position_y < 0 || position_x<0 || position_x>GAME_WIDTH - size)
		{
			position_x -= v_x;
			break;
		}
	}
	position_y += v_y;
	for (int i = 0; i < block.n; ++i)
	{
		if (QRect(position_x, position_y, size, size).intersects(block.b[i]) || position_y > GAME_HEIGHT - size || position_y < 0 || position_x<0 || position_x>GAME_WIDTH - size)
		{
			position_y -= v_y;
			break;
		}
	}
	if (w != nullptr)
	{
		w->center_x = position_x + size / 2;
		w->center_y = position_y + size / 2;
	}
}
Charactors::Charactors() :id(0), hp(100), full_hp(100), level(0), speed(5)
{
	img.load(RED_HEART_IMG);
	w = new Weapon((position_x + size / 2), (position_y + size / 2), size, 0);
};
Charactors::Charactors(int id, int hp, int level, int speed) :id(id), hp(hp + 10 * level), full_hp(hp + 10 * level), level(level), speed(speed)
{
	if (id == 1)
	{
		img.load(RED_HEART_IMG);
		w = new Weapon((position_x + size / 2), (position_y + size / 2), size, level);
	}
	else if (id == 2)
	{
		img.load(RED_HEART_2_IMG);
		w = new Weapon_2((position_x + size / 2), (position_y + size / 2), size, level);
	}
}
Charactors::~Charactors()
{
	if (w != nullptr)
	{
		delete w;
		w = nullptr;
	}
}
enemy_1::enemy_1() :Charactors()
{
	img.load(WHITE_HEART_IMG);
	w = nullptr;
}
enemy_1::enemy_1(int id, int x, int y, int hp, int level, int speed) :Charactors(id, hp, level, speed)
{
	position_x = x;
	position_y = y;
	img.load(WHITE_HEART_IMG);
	w = nullptr;
}
void enemy_1::update_v(int x, int y)
{
	v_x = speed * (x - position_x) / qSqrt(pow(x - position_x, 2) + pow(y - position_y, 2));
	v_y = speed * (y - position_y) / qSqrt(pow(x - position_x, 2) + pow(y - position_y, 2));
}
enemy_2::enemy_2(int id, int x, int y, int hp, int level, int speed, QList<bullet*>& bullets) :Charactors(id, hp, level, speed)
{
	shot_timer.setInterval(5000);//单位ms
	shot_timer.start();
	connect(&shot_timer, &QTimer::timeout, [&]()
		{
			bullet* p = new bullet(position_x, position_y + size / 2, v_x, v_y, 0, this->level);
			bullets.append(p);
			p = new bullet(position_x + size / 2, position_y, v_x, v_y, 1, this->level);
			bullets.append(p);
			p = new bullet(position_x + size, position_y + size / 2, v_x, v_y, 2, this->level);
			bullets.append(p);
			p = new bullet(position_x + size / 2, position_y + size, v_x, v_y, 3, this->level);
			bullets.append(p);
		}
	);
	position_x = x;
	position_y = y;
	v_x = speed;
	v_y = speed;
	img.load(ENEMY_2_IMG);
	w = nullptr;
}
void enemy_2::move()
{
	if (v_y < 0)
	{
		if (position_y <= 0)
		{
			v_y = -1 * v_y;
		}
		position_y += v_y;
	}
	else if (v_y > 0)
	{
		if (position_y >= GAME_HEIGHT - size)
		{
			v_y = -1 * v_y;
		}
		position_y += v_y;
	}
	if (v_x < 0)
	{
		if (position_x <= 0)
		{
			v_x = -1 * v_x;
		}
		position_x += v_x;
	}
	else if (v_x > 0)
	{
		if (position_x >= GAME_WIDTH - size)
		{
			v_x = -1 * v_x;
		}
		position_x += v_x;
	}
}