#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    std::vector<Point> result;
    recursive_range(region, this->root, result);
    return result;
}


template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::recursive_range(Rectangle region, std::shared_ptr<Node>& node_ptr, std::vector<Point>& result_vector){
    if(node_ptr == nullptr) return;
    
    Point point = node_ptr->get_point();

    //Check if the point is in the region (rectangle).
    if(region.contains_in_rectangle(point))
        result_vector.push_back(point);

    //If it has a NW, NE, SW or SE child, then apply the recursion there.
    if(node_ptr->NW())
        recursive_range(region, node_ptr->NW(), result_vector);

    if(node_ptr->NE())
        recursive_range(region, node_ptr->NE(), result_vector);

    if(node_ptr->SW())
        recursive_range(region, node_ptr->SW(), result_vector);

    if(node_ptr->SE())
        recursive_range(region, node_ptr->SE(), result_vector);

}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
