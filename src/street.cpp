#include "street.h"
#include "intersection.h"

void street::street::set_in_intersection(std::shared_ptr<intersection::intersection> intersection_ptr)
{
    _in_intersection_ptr = intersection_ptr;
    intersection_ptr->add_street(shared_from_this());
}

void street::street::set_out_intersection(std::shared_ptr<intersection::intersection> intersection_ptr)
{
    _out_intersection_ptr = intersection_ptr;
    intersection_ptr->add_street(shared_from_this());
}