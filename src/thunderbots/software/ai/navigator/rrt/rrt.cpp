#include "rrt.h"

#include "ai/intent/move_intent.h"
#include "ai/navigator/RobotObstacle.h"
#include "ai/primitive/move_primitive.h"

RRTNav::RRTNav() {}

std::vector<std::unique_ptr<Primitive>> RRTNav::getAssignedPrimitives(
    const World &world, const std::vector<std::unique_ptr<Intent>> &assignedIntents) const
{
    std::vector<std::unique_ptr<Primitive>> assigned_primitives =
        std::vector<std::unique_ptr<Primitive>>();

    // Hand the different types of Intents here
    for (const auto &intent : assignedIntents)
    {
        if (intent->getIntentName() == MOVE_INTENT_NAME)
        {
            // TODO: Implement this
            // https://github.com/UBC-Thunderbots/Software/issues/23
            // Cast down to the MoveIntent class so we can access its members
            MoveIntent move_intent = dynamic_cast<MoveIntent &>(*intent);

            // Get vectors of robot obstacles
            // TODO: do something with these for path planning
            std::vector<RobotObstacle> friendly_obsts = generate_friendly_obstacles(
                world.friendlyTeam(),
                DynamicParameters::Navigator::default_avoid_dist.value());
            std::vector<RobotObstacle> enemy_obsts = generate_enemy_obstacles(
                world.enemyTeam(),
                DynamicParameters::Navigator::default_avoid_dist.value());

            std::unique_ptr<Primitive> move_prim = std::make_unique<MovePrimitive>(
                move_intent.getRobotId(), move_intent.getDestination(),
                move_intent.getFinalAngle(), move_intent.getFinalSpeed());

            assigned_primitives.emplace_back(std::move(move_prim));
        }
        else
        {
            // TODO: Throw a proper exception here
            // https://github.com/UBC-Thunderbots/Software/issues/16
            std::cerr << "Error: Unrecognized Intent given to navigator" << std::endl;
            exit(1);
        }
    }

    return assigned_primitives;
}
