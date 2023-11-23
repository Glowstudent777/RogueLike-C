#include "rogue.h"

void makeFOV(Entity* player)
{
	int y, x, distance;
	int RADIUS = 15;
	Position target;

	map[player->pos.y][player->pos.x].visible = 1;
	map[player->pos.y][player->pos.x].seen = 1;

	for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++)
	{
		for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++)
		{
			target.y = y;
			target.x = x;
			distance = getDistance(player->pos, target);

			if (distance < RADIUS)
			{
				if (isInMap(y, x) && lineOfSight(player->pos, target))
				{
					map[y][x].visible = 1;
					map[y][x].seen = 1;
				}
			}
		}
	}
}

void clearFOV(Entity* player)
{
	int y, x;
	int RADIUS = 15;

	for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++)
	{
		for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++)
		{
			if (isInMap(y, x))
				map[y][x].visible = 0;
		}
	}
}

int getDistance(Position origin, Position target)
{
	double dy, dx;
	int distance;
	dx = target.x - origin.x;
	dy = target.y - origin.y;
	distance = floor(sqrt((dx * dx) + (dy * dy)));

	return distance;
}

bool isInMap(int y, int x)
{
	if ((0 < y && y < MAP_HEIGHT - 1) && (0 < x && x < MAP_WIDTH - 1))
	{
		return 1;
	}

	return 0;
}

bool lineOfSight(Position origin, Position target)
{
	int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

	delta_x = origin.x - target.x;
	delta_y = origin.y - target.y;

	abs_delta_x = abs(delta_x);
	abs_delta_y = abs(delta_y);

	sign_x = getSign(delta_x);
	sign_y = getSign(delta_y);

	x = target.x;
	y = target.y;

	if (abs_delta_x > abs_delta_y)
	{
		t = abs_delta_y * 2 - abs_delta_x;

		do
		{
			if (t >= 0)
			{
				y += sign_y;
				t -= abs_delta_x * 2;
			}

			x += sign_x;
			t += abs_delta_y * 2;

			if (x == origin.x && y == origin.y)
			{
				return 1;
			}
		} while (map[y][x].transparent);

		return 0;
	}
	else
	{
		t = abs_delta_x * 2 - abs_delta_y;

		do
		{
			if (t >= 0)
			{
				x += sign_x;
				t -= abs_delta_y * 2;
			}

			y += sign_y;
			t += abs_delta_x * 2;

			if (x == origin.x && y == origin.y)
			{
				return 1;
			}
		} while (map[y][x].transparent);

		return 0;
	}
}

int getSign(int a)
{
	return (a < 0) ? -1 : 1;
}