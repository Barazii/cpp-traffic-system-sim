#pragma once

#include <string>
#include <opencv4/opencv2/core.hpp>

namespace graphics
{
    class graphics
    {
    public:
        graphics() = default;
        ~graphics() = default;

        void set_background_filename(std::string filename) { _filename = filename; }
        void simulate();

    private:
        std::string _filename{};
        std::vector<cv::Mat> _images{};
        std::string _window_name{};

        void load_background_image();
        void draw_traffic_objects();
    };
}