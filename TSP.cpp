#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double Distance(pair<int, int> a, pair<int, int> b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) - (a.second - b.second) * (a.second - b.second));
}
bool isend(vector<int> &vis)
{
    for (int i = 0; i < vis.size(); ++i)
        if (!vis[i])
            return 0;
    return 1;
}

string NearstNeighbor(vector<pair<int, int>> &nodes)
{
    vector<int> vis(nodes.size(), 0);
    string res = "0 ";
    int cur = 0;
    while (!isend(vis))
    {
        vis[cur] = 1;
        int nexts = -1, mins = 2147483647;
        for (int i = 0; i < vis.size(); ++i)
        {
            if (vis[i])
                continue;
            else
            {
                double distance = Distance(nodes[cur], nodes[i]);
                if (distance < mins)
                {
                    nexts = i, mins = distance;
                }
            }
        }

        cerr << nexts << endl;

        res += to_string(nexts) + ' ';
        cur = nexts;
        vis[cur] = 1;
    }

    res += '0';
    return res;
}

int main()
{
    int n; // This variables stores how many nodes are given
    cin >> n;
    cin.ignore();
    vector<pair<int, int>> arr;
    for (int i = 0; i < n; i++)
    {
        int x; // The x coordinate of the given node
        int y; // The y coordinate of the given node
        cin >> x >> y;
        cin.ignore();
        arr.push_back({x, y});
    }

    string res = NearstNeighbor(arr);
    cout << res << endl; // You have to output a valid path
}