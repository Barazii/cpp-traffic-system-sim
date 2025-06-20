#pragma once

#include <thread>
#include <vector>
#include <memory>

namespace vehicle
{
    class vehicle;
}

namespace street
{
    class street;
}

namespace intersection
{
    class intersection;
}

namespace traffic_object
{
    void create_traffic_objects(std::vector<std::shared_ptr<street::street>> &, std::vector<std::shared_ptr<intersection::intersection>> &, std::vector<std::shared_ptr<vehicle::vehicle>> &);

    struct position
    {
        float x{}, y{};
    };

    enum class object_type
    {
        OBJECT_NULL,
        OBJECT_INTERSECTION,
        OBJECT_VEHICLE
    };

    class traffic_object
    {
    public:
        traffic_object();
        ~traffic_object();

        position get_position();
        void set_position(float, float);
        object_type get_object_type();
        virtual void simulate() {}
        int get_id();

    protected:
        std::vector<std::thread> _threads{};
        float _posx{}, _posy{};
        object_type _object_type{};
        int _id{};

    private:
        static int _id_count;
    };
}
