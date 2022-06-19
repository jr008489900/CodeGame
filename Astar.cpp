#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Robot
{
    Robot() {}
    Robot(int x, int y, string dir)
    {
        this->x = x;
        this->y = y;
        this->dir = dir;
    }
    int x;
    int y;
    string dir;
    vector<vector<bool>> vis;
};

class Solution
{
public:
    Solution(){};
    string Execute();
    vector<Robot> robots;
    vector<string> maze;

private:
    int dirs[5] = {-1, 0, 1, 0, -1};
    string AStar(Robot);
};

int main()
{
    Solution solution;
    for (int i = 0; i < 10; i++)
    {
        string line;
        getline(cin, line);
        solution.maze.push_back(line);
    }
    int robot_count;
    cin >> robot_count;
    cin.ignore();
    for (int i = 0; i < robot_count; i++)
    {
        int x;
        int y;
        string direction;
        cin >> x >> y >> direction;
        cin.ignore();
        Robot r = Robot(x, y, direction);
        r.vis.resize(solution.maze.size(), vector<bool>(solution.maze[0].size(), 0));
        solution.robots.push_back(Robot(x, y, direction));
    }
    cout << solution.Execute() << endl;

    cout << "3 4 R 1 1 R 2 2 D 3 3 L" << endl;
}

Solution::Execute()
{
    string res = "";
    for (int i = 0; i < robots.size; ++i)
    {
        res += AStar(robots[i]);
    }
    return res;
}

Solution::AStar(Robot r)
{
    queue<pair<int, int>> que;
}
