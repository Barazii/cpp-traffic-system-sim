#include "street.h"
#include "intersection.h"

void street::street::set_in_intersection(std::shared_ptr<intersection::intersection> intersection_ptr)
{
    in_intersection_ptr = intersection_ptr;
    intersection_ptr->add_street(shared_from_this());
}

void street::street::set_out_intersection(std::shared_ptr<intersection::intersection> intersection_ptr)
{
    out_intersection_ptr = intersection_ptr;
    intersection_ptr->add_street(shared_from_this());
}

std::shared_ptr<intersection::intersection> street::street::get_in_intersection() { return in_intersection_ptr; }

std::shared_ptr<intersection::intersection> street::street::get_out_intersection() { return out_intersection_ptr; }

float street::street::get_length() { return length; }
