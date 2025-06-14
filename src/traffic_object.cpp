#include <algorithm>
#include "traffic_object.h"

traffic_object::traffic_object::~traffic_object()
{
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &thread)
                  { 
            if(thread.joinable())
                thread.join(); });
}