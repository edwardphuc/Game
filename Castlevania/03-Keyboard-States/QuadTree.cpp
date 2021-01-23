//#include "QuadTree.h"
//void Quadtree::Clear()
//{
//    // Clear all nodes
//    if (m_nodes)
//    {
//        for (int i = 0; i < 4; i++)
//        {
//            m_nodes[i]->Clear();
//            delete m_nodes[i];
//        }
//        delete[] m_nodes;
//    }
//
//    //// Clear current Quadtree
//    //object->clear();
//
//    //delete object;
//    //delete m_region;
//}
//
//bool Quadtree::IsContain(Entity* entity)
//{
//    Rect* bound = entity->GetBoundingBox();
//
//    return !(bound->x + bound->width < m_region->x ||
//        bound->y + bound->height < m_region->y ||
//        bound->x > m_region->x + m_region->width ||
//        bound->y > m_region->y + m_region->height);
//}
//
//void Quadtree::Insert(Entity* entity)
//{
//    // Insert entity into corresponding nodes
//    if (m_nodes)
//    {
//        if (m_nodes[0]->IsContain(entity))
//            m_nodes[0]->Insert(entity);
//        if (m_nodes[1]->IsContain(entity))
//            m_nodes[1]->Insert(entity);
//        if (m_nodes[2]->IsContain(entity))
//            m_nodes[2]->Insert(entity);
//        if (m_nodes[3]->IsContain(entity))
//            m_nodes[3]->Insert(entity);
//
//        return; // Return here to ignore rest.
//    }
//
//    // Insert entity into current quadtree
//    if (this->IsContain(entity))
//        m_objects_list->push_back(entity);
//
//    // Split and move all objects in list into it’s corresponding nodes
//    if (m_objects_list->size() > MAX_OBJECT_IN_REGION && m_level < MAX_LEVEL)
//    {
//        Split();
//
//        while (!m_objects_list->empty())
//        {
//            if (m_nodes[0]->IsContain(m_objects_list->back()))
//                m_nodes[0]->Insert(m_objects_list->back());
//            if (m_nodes[1]->IsContain(m_objects_list->back()))
//                m_nodes[1]->Insert(m_objects_list->back());
//            if (m_nodes[2]->IsContain(m_objects_list->back()))
//                m_nodes[2]->Insert(m_objects_list->back());
//            if (m_nodes[3]->IsContain(m_objects_list->back()))
//                m_nodes[3]->Insert(m_objects_list->back());
//
//            m_objects_list->pop_back();
//        }
//    }
//}
