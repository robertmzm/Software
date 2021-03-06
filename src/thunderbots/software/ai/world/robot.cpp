#include "robot.h"

Robot::Robot(const unsigned int id, std::chrono::steady_clock::time_point timestamp)
    : id_(id),
      position_(Point()),
      velocity_(Vector()),
      orientation_(Angle::zero()),
      angularVelocity_(AngularVelocity::zero()),
      last_update_timestamp(timestamp)
{
}

Robot::Robot(unsigned int id, const Point &position, const Vector &velocity,
             const Angle &orientation, const AngularVelocity &angular_velocity,
             std::chrono::steady_clock::time_point timestamp)
    : id_(id),
      position_(position),
      velocity_(velocity),
      orientation_(orientation),
      angularVelocity_(angular_velocity),
      last_update_timestamp(timestamp)
{
}

void Robot::updateState(const Point &new_position, const Vector &new_velocity,
                        const Angle &new_orientation,
                        const AngularVelocity &new_angular_velocity,
                        std::chrono::steady_clock::time_point timestamp)
{
    if (timestamp < last_update_timestamp)
    {
        // TODO: Error. We should never be updating with times from the past
        // TODO: Throw a proper exception here
        // https://github.com/UBC-Thunderbots/Software/issues/16
        exit(1);
    }

    position_             = new_position;
    velocity_             = new_velocity;
    orientation_          = new_orientation;
    angularVelocity_      = new_angular_velocity;
    last_update_timestamp = timestamp;
}

void Robot::updateState(const Robot &new_robot_data)
{
    if (new_robot_data.id() != id())
    {
        // TODO: Throw a proper exception here. We should not update a robot using a robot
        // with a different id (a different robot)
        // https://github.com/UBC-Thunderbots/Software/issues/16
        std::cerr << "Error: Robot updated using a robot with a mismatched id"
                  << std::endl;
        exit(1);
    }

    updateState(new_robot_data.position(), new_robot_data.velocity(),
                new_robot_data.orientation(), new_robot_data.angularVelocity(),
                new_robot_data.lastUpdateTimestamp());
}

void Robot::updateStateToPredictedState(std::chrono::steady_clock::time_point timestamp)
{
    if (timestamp < last_update_timestamp)
    {
        // TODO: Error. We should never be updating with times from the past
        // TODO: Throw a proper exception here
        // https://github.com/UBC-Thunderbots/Software/issues/16
        exit(1);
    }

    auto milliseconds_in_future = std::chrono::duration_cast<std::chrono::milliseconds>(
        timestamp - last_update_timestamp);
    Point new_position    = estimatePositionAtFutureTime(milliseconds_in_future);
    Vector new_velocity   = estimateVelocityAtFutureTime(milliseconds_in_future);
    Angle new_orientation = estimateOrientationAtFutureTime(milliseconds_in_future);
    AngularVelocity new_angular_velocity =
        estimateAngularVelocityAtFutureTime(milliseconds_in_future);

    updateState(new_position, new_velocity, new_orientation, new_angular_velocity,
                timestamp);
}

std::chrono::steady_clock::time_point Robot::lastUpdateTimestamp() const
{
    return last_update_timestamp;
}

unsigned int Robot::id() const
{
    return id_;
}

Point Robot::position() const
{
    return position_;
}

Point Robot::estimatePositionAtFutureTime(
    const std::chrono::milliseconds &milliseconds_in_future) const
{
    if (milliseconds_in_future < std::chrono::milliseconds(0))
    {
        // TODO: Error. We should never be updating with times from the past
        // TODO: Throw a proper exception here
        // https://github.com/UBC-Thunderbots/Software/issues/16
    }

    // TODO: This is a simple linear implementation that does not necessarily reflect
    // real-world behavior. Position prediction should be improved as outlined in
    // https://github.com/UBC-Thunderbots/Software/issues/50
    typedef std::chrono::duration<double> double_seconds;
    double seconds_in_future =
        std::chrono::duration_cast<double_seconds>(milliseconds_in_future).count();
    return position_ + velocity_.norm(velocity_.len() * seconds_in_future);
}

Vector Robot::velocity() const
{
    return velocity_;
}

Vector Robot::estimateVelocityAtFutureTime(
    const std::chrono::milliseconds &milliseconds_in_future) const
{
    if (milliseconds_in_future < std::chrono::milliseconds(0))
    {
        // TODO: Error. We should never be updating with times from the past
        // TODO: Throw a proper exception here
        // https://github.com/UBC-Thunderbots/Software/issues/16
    }

    // TODO: This simple implementation that assumes the robot maintains the same velocity
    // and does not necessarily reflect real-world behavior. Velocity prediction should be
    // improved as outlined in https://github.com/UBC-Thunderbots/Software/issues/50
    return velocity_;
}

Angle Robot::orientation() const
{
    return orientation_;
}

Angle Robot::estimateOrientationAtFutureTime(
    const std::chrono::milliseconds &milliseconds_in_future) const
{
    if (milliseconds_in_future < std::chrono::milliseconds(0))
    {
        // TODO: Error. We should never be updating with times from the past
        // TODO: Throw a proper exception here
        // https://github.com/UBC-Thunderbots/Software/issues/16
    }

    // TODO: This is a simple linear implementation that does not necessarily reflect
    // real-world behavior. Orientation prediction should be improved as outlined in
    // https://github.com/UBC-Thunderbots/Software/issues/50
    typedef std::chrono::duration<double> double_seconds;
    double seconds_in_future =
        std::chrono::duration_cast<double_seconds>(milliseconds_in_future).count();
    return orientation_ + angularVelocity_ * seconds_in_future;
}

AngularVelocity Robot::angularVelocity() const
{
    return angularVelocity_;
}

AngularVelocity Robot::estimateAngularVelocityAtFutureTime(
    const std::chrono::milliseconds &milliseconds_in_future) const
{
    if (milliseconds_in_future < std::chrono::milliseconds(0))
    {
        // TODO: Error. We should never be updating with times from the past
        // TODO: Throw a proper exception here
        // https://github.com/UBC-Thunderbots/Software/issues/16
    }

    // TODO: This simple implementation that assumes the robot maintains the same
    // angular velocity and does not necessarily reflect real-world behavior. Angular
    // velocity prediction should be improved as outlined in
    // https://github.com/UBC-Thunderbots/Software/issues/50
    return angularVelocity_;
}

bool Robot::operator==(const Robot &other) const
{
    return this->id_ == other.id_ && this->position_ == other.position_ &&
           this->velocity_ == other.velocity_ &&
           this->orientation_ == other.orientation_ &&
           this->angularVelocity_ == other.angularVelocity_;
}

bool Robot::operator!=(const Robot &other) const
{
    return !(*this == other);
}
