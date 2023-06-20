#pragma once
#include <QPixmap>
#include<QWidget>
#include<QPainter>
#include"config.h"
class Block
{
public:
	unsigned n;
	QRect* b;
	Block()
	{
		n = 0;
		b = NULL;
	}
	Block(int Seed) 
	{
		srand(Seed);
		n = (rand() % (MAX_BLOCK_NUM-MIN_BLOCK_NUM)) +MIN_BLOCK_NUM ;
		b = new QRect[n];
		for (int i = 0; i < n; i++)
		{
			while (1) 
			{
				b[i] = QRect(rand() % (GAME_WIDTH - MAX_BLOCK_SIZE-140) + 70, rand() % (GAME_HEIGHT - MAX_BLOCK_SIZE-140) + 70, rand() % (MAX_BLOCK_SIZE - MIN_BLOCK_SIZE) + MIN_BLOCK_SIZE, rand() % (MAX_BLOCK_SIZE - MIN_BLOCK_SIZE) + MIN_BLOCK_SIZE);
				if (!b[i].intersects(QRect(GAME_WIDTH / 2, GAME_HEIGHT / 2, 100, 100)))
				{
					break;
				}
			}
		}
	};
	Block& operator =(Block&& a)
	{
		n = a.n;
		if (b != NULL)
		{
			delete[] b;
		}
		b = a.b;
		a.b = NULL;
		return *this;
	}
	~Block() 
	{
		n = 0;
		if(b != NULL)
		{
			delete[] b;
			b = NULL;
		}
	}
};
