#pragma once

#include "ai/primitive/primitive.h"
#include "geom/angle.h"
#include "geom/point.h"

class MovePrimitive : public Primitive
{
   public:
    static const std::string PRIMITIVE_NAME;
    /**
     * Creates a new Move Primitive
     *
     * @param robot_id The id of the Robot to run this Primitive
     * @param dest The final destination of the movement
     * @param final_angle The final orientation the robot should have at the end
     * of the movement
     * @param final_speed The final speed the Robot should have when it reaches
     * its destination at the end of the movement
     */
    explicit MovePrimitive(unsigned int robot_id, const Point &dest,
                           const Angle &final_angle, double final_speed);

    /**
     * Creates a new Move Primitive from a Primitive message
     *
     * @param primtiive_msg The message from which to create the Move Primitive
     */
    explicit MovePrimitive(const thunderbots_msgs::Primitive &primtiive_msg);

    std::string getPrimitiveName() const override;

    unsigned int getRobotId() const override;

    std::vector<double> getParameterArray() const override;

    std::vector<bool> getExtraBitArray() const override;

   private:
    unsigned int robot_id;
    Point dest;
    Angle final_angle;
    double final_speed;
};
