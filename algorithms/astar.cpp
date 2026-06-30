#include "astar.h"
#include <queue>

AStarResult runAStar(const std::vector<std::vector<Cell*>> &grid, int rows, int cols) {
    AStarResult result;

    std::pair<int,int> start={-1,-1}, goal={-1,-1};

    //get start & goal point
    for (int r=0;  r<rows; r++){
        for (int c=0; c<cols; c++){
            if (grid[r][c]->getType()==CellType::Start) start={r,c};
            if (grid[r][c]->getType()==CellType::Goal) goal={r,c};
        }
    }

    if (start.first == -1 || goal.first == -1) return result;

    //east, west, north, south
    const int dr[4]={-1,1,0,0};
    const int dc[4]={0,0,-1,1};

    //gCost
    std::vector<std::vector<int>> gCost(rows, std::vector<int>(cols, 1e9));
    gCost[start.first][start.second] = 0;

    //hCost
    int hStart = abs(start.first - goal.first) + abs(start.second - goal.second);

    //{fCost, {row, col}}
    using QueueItem = std::pair<int, std::pair<int,int>>;
    std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<>> q; 
    q.push({hStart, start}); 
    
    //visited check
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false)); //[false][false]
    visited[start.first][start.second] = true;
    
    //for backtracking (path)
    std::vector<std::vector<std::pair<int,int>>> parent(rows, std::vector<std::pair<int,int>>(cols, {-1,-1})); 
    

    while (!q.empty()){
        auto [fCost, position] = q.top();
        auto [r,c] = position;
        q.pop();

        if (grid[r][c]->getType()==CellType::Empty) result.visitedOrder.push_back({r,c});
        if (grid[r][c]->getType()==CellType::Goal){
            result.found = true;
            break;
        }

        //searching (find lowest F Cost)        
        for (int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr<0 || nc<0 || nr>=rows || nc>=cols) continue;
            if (grid[nr][nc]->getType()==CellType::Wall) continue;
            if (visited[nr][nc]) continue;
            
            int newGCost = gCost[r][c] + 1; 

            if (newGCost < gCost[nr][nc]) { 
                gCost[nr][nc] = newGCost;
                int hCost = abs(goal.first - nr) + abs(goal.second - nc);
                int newFCost = newGCost + hCost;

                parent[nr][nc] = {r, c};
                q.push({newFCost, {nr, nc}});
            }

            visited[nr][nc]=true;
        }
    }
    
    if (!result.found) return result;

    //backtracking to find path
    std::pair<int,int> tracking = goal;
    while (tracking != start){
        if (grid[tracking.first][tracking.second]->getType()==CellType::Empty){
            result.path.push_back(tracking);
        }
        tracking = parent[tracking.first][tracking.second];
    }

    return result;
}