#pragma once
#include "GameObject.h"
class Grid
{
	struct gridround
	{
		int Id;
		int Left;
		int Right;
	};
	static Grid* _instance;
	int mapwidth;
	//vector<vector<CGameObject*>> object;
	vector<LPGAMEOBJECT> object;
	Grid();
public:
	void insertlistgrid(int id, int left, int right);
	//void insert(int gridId, CGameObject *object);
	static Grid* getInstace();
	vector<int> checkingrid();
	//vector<CGameObject*> getlistobject();
	bool isincurrentGrid(vector<LPGAMEOBJECT> object);
	~Grid();
};

