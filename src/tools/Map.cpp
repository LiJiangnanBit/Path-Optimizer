//
// Created by ljn on 20-2-12.
//

#include "tools/Map.hpp"

namespace PathOptimizationNS {

Map::Map(const grid_map::GridMap &grid_map) :
    maps(grid_map) {
    if (!grid_map.exists("distance")) {
        LOG(ERROR) << "grid map must contain 'distance' layer";
    }
}

double Map::getObstacleDistance(const grid_map::Position &pos) const {
    if (maps.isInside(pos)) {
        return this->maps.atPosition("distance", pos, grid_map::InterpolationMethods::INTER_LINEAR);
    } else {
        return 0.0;
    }
}
}