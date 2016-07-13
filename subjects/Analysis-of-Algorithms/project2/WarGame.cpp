/*
 * Original link problem: https://goo.gl/0vXz6m
 * Idea reference: http://goo.gl/aLhnm2
 * Implentation reference: http://goo.gl/xKCz23
 */

#include <iostream>
#include <cstdio>

#define maxn 20001
  
#define set_friends 1
#define set_enemies 2
#define are_friends 3
#define are_enemies 4
  
#define no 0
#define yes 1
#define err (-1)

using namespace std;

int p[maxn]; // parent of nodes

void init_set(int sz)
{
	sz <<= 1;
	for(int i = 0; i < sz; i++)
	{
		p[i] = i;
	}
}

int find_set(int x)
{
	if (x != p[x])
		p[x] = find_set(p[x]);
	return p[x];
}


void areFriends(int x, int y, int sz)
{
	int px = find_set(x);
	int py = find_set(y);
	int ret = (px == py) ? yes : no;
	printf("%d\n",ret);
}

void areEnemies(int x, int y, int sz)
{
	int px = find_set(x);
	int py = find_set(y);
	int opx = find_set(x+sz);
	int opy = find_set(y+sz);
	int ret = (px == opy || py == opx ) ? yes : no;
	printf("%d\n",ret);
}

void setFriends(int x, int y, int sz)
{
	int px = find_set(x);
	int py = find_set(y);
	int opx = find_set(x+sz);
	int opy = find_set(y+sz);
	if (px == opy || py == opx)
		printf("%d\n",err);
	else
	{
		p[py] = px;
		p[opy] = opx;
	}
}

void setEnemies(int x, int y, int sz)
{
	int px = find_set(x);
	int py = find_set(y);
	int opx = find_set(x+sz);
	int opy = find_set(y+sz);
	if (px == py)
		printf("%d\n",err);
	else
	{
		p[opx] = py;
		p[opy] = px;
	}
}

int main()
{
	int sz, c, x, y;
	scanf("%d",&sz);
	init_set( sz );
	while(scanf("%d %d %d",&c,&x,&y)!=EOF)
	{
		if (!c && !x && !y) break;
		switch(c)
		{
			case set_friends:
			{
				setFriends(x, y, sz);
				break;
			}
			case set_enemies:
			{
				setEnemies(x, y, sz);
				break;
			}
			case are_friends:
			{
				areFriends(x, y, sz);
				break;
			}
			case are_enemies:
			{
				areEnemies(x, y, sz);
				break;
			}
			default: printf("ERR: c=%d invalid option!",c);
		}
	}
	return 0;
}