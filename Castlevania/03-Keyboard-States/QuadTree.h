#pragma once
#include "GameObject.h"
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
class Quadtree
{
private:
    /*Một Quadtree sẽ lưu trữ một số thông tin cần thiết như :
        Phạm vi của Quadtree.
        Danh sách các đối tượng.
        Danh sách các node dẫn xuất.
        Level.*/
    int        m_level; // level
    Quadtree** m_nodes; // danh sach node dan xuat
    vector<LPGAMEOBJECT> object; // danh sach doi tuong
    RECT rect;// Phạm vi của Quadtree.
    //bool       IsContain(Entity* entity);
public:
    Quadtree();
    //Quadtree(int level, Rect* region);
    ~Quadtree();

    void           Clear();
    void           Insert(CGameObject );
 
};

