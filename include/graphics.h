#pragma once

#include <string>
#include <opencv4/opencv2/core.hpp>
#include <memory>
#include <vector>

namespace traffic_object
{
    class traffic_object;
}

namespace graphics
{
    class graphics
    {
    public:
        graphics() = default;
        ~graphics() = default;

        void set_background_filename(std::string filename) { _filename = filename; }
        void simulate(std::vector<std::shared_ptr<traffic_object::traffic_object>> &&);

    private:
        std::string _filename{};
        std::vector<cv::Mat> _images{};
        std::string _window_name{};

        void load_background_image();
        void draw_traffic_objects(std::vector<std::shared_ptr<traffic_object::traffic_object>> );
    };
}