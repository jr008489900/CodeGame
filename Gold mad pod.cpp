#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class Player
{
public:
    Player();
    void OutputData();
    string Run(Player *, Player *, Player *);
    string Attack(Player *, Player *, Player *);

private:
    double Distance(pair<int, int> a, pair<int, int> b);
    pair<int, int> Find_optimal_move(pair<int, int> p1, pair<int, int> p2);
    pair<int, int> Lengthen(pair<int, int> p, pair<int, int> target);
    double Angle_between_2p(pair<int, int> p1, pair<int, int> p2);
    pair<int, int> Basis_transform(pair<int, int> p1);
    int x;                   // x position of your pod
    int y;                   // y position of your pod
    int vx;                  // x speed of your pod
    int vy;                  // y speed of your pod
    int angle;               // angle of your pod
    int next_check_point_id; // next check point id of your pod
    int padradius;
    int checkpointradius;
    pair<int, int> logs;
    int ax;
    int ay;
    int prev_x;
    int prev_y;
    int laps;
    int Rounds;
    vector<int, int> nextpos;
    vector<int, int> nextvel;
    vector<pair<int, int>> checkpoints;
    int thrust;
    Player *teammate;
    Player *opponent;
    Player *opponent2;
};

int main()
{
    int laps;
    cin >> laps;
    cin.ignore();
    int checkpoint_count;
    vector < pair<int, int> checkpoints;

    cin >> checkpoint_count;
    cin.ignore();
    for (int i = 0; i < checkpoint_count; i++)
    {
        int checkpoint_x;
        int checkpoint_y;
        cin >> checkpoint_x >> checkpoint_y;
        cin.ignore();
        checkpoints.push_back(make_pair(checkpoint_x, checkpoint_y));
    }

    // game loop
    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            int x;                   // x position of your pod
            int y;                   // y position of your pod
            int vx;                  // x speed of your pod
            int vy;                  // y speed of your pod
            int angle;               // angle of your pod
            int next_check_point_id; // next check point id of your pod
            cin >> x >> y >> vx >> vy >> angle >> next_check_point_id;
            cin.ignore();
        }
        for (int i = 0; i < 2; i++)
        {
            int x_2;                   // x position of the opponent's pod
            int y_2;                   // y position of the opponent's pod
            int vx_2;                  // x speed of the opponent's pod
            int vy_2;                  // y speed of the opponent's pod
            int angle_2;               // angle of the opponent's pod
            int next_check_point_id_2; // next check point id of the opponent's pod
            cin >> x_2 >> y_2 >> vx_2 >> vy_2 >> angle_2 >> next_check_point_id_2;
            cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        cout << "8000 4500 100" << endl;
        cout << "8000 4500 100" << endl;
    }
}