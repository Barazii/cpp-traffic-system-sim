#include "graphics.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "traffic_object.h"

void graphics::graphics::simulate(std::vector<std::shared_ptr<traffic_object::traffic_object>> &traffic_objects_ptrs)
{
    this->load_background_image();
    while (true)
    {
        this->draw_traffic_objects(traffic_objects_ptrs);
    }
}

void graphics::graphics::load_background_image()
{
    _window_name = "Traffic System Simulation";
    cv::namedWindow(_window_name, cv::WINDOW_NORMAL);
    cv::Mat background = cv::imread(_filename);
    _images.push_back(background);         // first element is the original background
    _images.push_back(background.clone()); // second element will be the transparent overlay
    _images.push_back(background.clone()); // third element will be the result image for display
}

void graphics::graphics::draw_traffic_objects(std::vector<std::shared_ptr<traffic_object::traffic_object>> &traffic_objects_ptrs)
{
    _images.at(1) = _images.at(0).clone();
    _images.at(2) = _images.at(0).clone();

    for (auto top : traffic_objects_ptrs)
    {
        traffic_object::position position = top->get_position();

        if (top->get_object_type() == traffic_object::object_type::OBJECT_INTERSECTION)
        {
        }
        else if (top->get_object_type() == traffic_object::object_type::OBJECT_VEHICLE)
        {
        }
    }

    cv::Mat img;
    cv::resize(_images.at(2), img, cv::Size(1040, 720), 0, 0, 1);
    cv::imshow(_window_name, img);

    cv::waitKey(33);
}