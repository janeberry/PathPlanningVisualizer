#include "astar.h"
#include <queue>

struct Node {
    int minRow;
    int minCol;
    int minFcost=1000;
};


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

    //f(n) = g(n) + f(n)
    // std::vector<std::vector<int>> gCost;
    // std::vector<std::vector<int>> hCost;
    

    //for backtracking (path)
    std::vector<std::vector<std::pair<int,int>>> parent(rows, std::vector<std::pair<int,int>>(cols, {-1,-1})); //(-1,-1)

    
    std::priority_queue<std::pair<int,int>> q;

    q.push(start);

    while (!q.empty()){
        auto [r,c] = q.top();
        q.pop();

        if (grid[r][c]->getType()==CellType::Empty) result.visitedOrder.push_back({r,c});
        if (grid[r][c]->getType()==CellType::Goal){
            result.found = true;
            break;
        }

        //searching (find lowest F Cost)
        Node current = {r, c, 1000};
        
        for (int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr<0 || nc<0 || nr>=rows || nc>=cols) continue;
            if (grid[nr][nc]->getType()==CellType::Wall) continue;

            int gCost = abs(start.first - nr) + abs(start.second - nc);
            int hCost = abs(goal.first - nr) + abs(goal.second - nc);

            int fCost = gCost + hCost;

            if (fCost <= current.minFcost){
                current.minRow = nr;
                current.minCol = nc;
                current.minFcost = fCost;
            }
        }

        parent[current.minRow][current.minCol]={r,c};
        q.push({current.minRow, current.minCol});

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