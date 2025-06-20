#include "graphics.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "traffic_object.h"
#include "intersection.h"
#include "vehicle.h"
#include <iostream>

void graphics::graphics::simulate(std::vector<std::shared_ptr<traffic_object::traffic_object>> &&traffic_objects_ptrs)
{
    auto tops = traffic_objects_ptrs;
    this->load_background_image();
    while (true)
    {
        this->draw_traffic_objects(tops);
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

void graphics::graphics::draw_traffic_objects(std::vector<std::shared_ptr<traffic_object::traffic_object>> traffic_objects_ptrs)
{
    _images.at(1) = _images.at(0).clone();
    _images.at(2) = _images.at(0).clone();

    for (auto top : traffic_objects_ptrs)
    {
        traffic_object::position position = top->get_position();

        if (top->get_object_type() == traffic_object::object_type::OBJECT_INTERSECTION)
        {
            auto intersection_ptr = std::dynamic_pointer_cast<intersection::intersection>(top);
            cv::Scalar light_color = intersection_ptr->get_current_light() == traffic_light::traffic_light_state::GREEN ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255);
            cv::circle(_images.at(1), cv::Point2d(position.x, position.y), 25, light_color, -1);
        }
        else if (top->get_object_type() == traffic_object::object_type::OBJECT_VEHICLE)
        {
            cv::RNG rng(top->get_id());
            int b = rng.uniform(0, 255);
            int g = rng.uniform(0, 255);
            int r = sqrt(255 * 255 - g * g - b * b);
            cv::Scalar vehicle_color = cv::Scalar(b, g, r);
            cv::circle(_images.at(1), cv::Point2d(position.x, position.y), 50, vehicle_color, -1);
        }
    }

    float opacity = 0.85;
    cv::addWeighted(_images.at(1), opacity, _images.at(0), 1.0 - opacity, 0, _images.at(2));

    cv::Mat img;
    cv::resize(_images.at(2), img, cv::Size(1040, 720), 0, 0, 1);
    cv::imshow(_window_name, img);

    cv::waitKey(33);
}