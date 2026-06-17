#pragma once

#include <vector>
#include <utility>

#include "../grid/cell.h"

struct BFSResult {
    std::vector<std::pair<int,int>> visitedOrder;
    std::vector<std::pair<int,int>> path;
    bool found = false;
};

BFSResult runBFS(const std::vector<std::vector<Cell*>> &grid, int rows, int cols);