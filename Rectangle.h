#pragma once

namespace utec
{
namespace spatial
{
    

template<typename Point>
struct Rectangle{
    Rectangle(Point min, Point max):_min(min),_max(max){}
    Point _min;
    Point _max;
    
    bool contains_in_rectangle(Point point){
        bool x = false, y = false;
        
        if(point.get(0) >= this->_min.get(0) and point.get(0) <= this->_max.get(0))
            x = true;
        if(point.get(1) >= this->_min.get(1) and point.get(1) <= this->_max.get(1))
            y = true;
        
        return (x and y);
    }
    
    
};

} //spatial
} //utec