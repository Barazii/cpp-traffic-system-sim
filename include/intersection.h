#pragma once

#include <memory>

namespace street
{
    class street;
}

namespace intersection
{
    class intersection
    {
    public:
        intersection() = default;
        ~intersection() = default;

        void setPosition(float x, float y)
        {
            _pos_x = x;
            _pos_y = y;
        }

        void add_street(std::shared_ptr<street::street>);

    private:
        float _pos_x{}, _pos_y{};
    };
}