#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class Entity
{
public:
    Entity() {}
    Entity(int entity_id, string entity_type, int x, int y, int param1, int param2, int param3, int param4)
    {
        this->entity_id = entity_id;
        this->entity_type = entity_type;
        this->x = x;
        this->y = y;
        this->arg_1 = param1;
        this->arg_2 = param2;
        this->arg_3 = param3;
        this->arg_4 = param4;
    }
    void OutputData();
    int entity_id;
    string entity_type;
    int x;
    int y;
    int arg_1;
    int arg_2;
    int arg_3;
    int arg_4;
};

class Solution;

class Ship : public Entity
{
public:
    Ship();
    Ship(int entity_id, string entity_type, int x, int y, int param1, int param2, int param3, int param4, Solution *solution)
    {
        this->entity_id = entity_id;
        this->entity_type = entity_type;
        this->x = x;
        this->y = y;
        this->arg_1 = param1;
        this->arg_2 = param2;
        this->arg_3 = param3;
        this->arg_4 = param4;
        this->solution = solution;
    }

    void CalculateDistance(vector<Entity> &entities);
    vector<pair<double, Entity *>> targets;

private:
    Solution *solution;
};

class Solution
{
public:
    Solution() {}
    Solution(int my_ship_count)
    {
        this->my_ship_count = my_ship_count;
    }
    void OutputData();
    void Update(vector<Entity> entities, int my_ship_count);
    double Distance(Entity e1, Entity e2);
    string Execute(int shipid);

private:
    vector<Entity> entities;
    vector<Ship> ships;
    int my_ship_count;
};

int main()
{

    Solution solution;

    // game loop
    while (1)
    {
        vector<Entity> entities;
        int my_ship_count; // the number of remaining ships
        cin >> my_ship_count;
        cin.ignore();
        int entity_count; // the number of entities (e.g. ships, mines or cannonballs)
        cin >> entity_count;
        cin.ignore();
        for (int i = 0; i < entity_count; i++)
        {
            int entity_id;
            string entity_type;
            int x;
            int y;
            int arg_1;
            int arg_2;
            int arg_3;
            int arg_4;
            cin >> entity_id >> entity_type >> x >> y >> arg_1 >> arg_2 >> arg_3 >> arg_4;
            entities.push_back(Entity(entity_id, entity_type, x, y, arg_1, arg_2, arg_3, arg_4));
            cin.ignore();
        }
        solution.Update(entities, my_ship_count);
        for (int i = 0; i < my_ship_count; i++)
        {
            string res = solution.Execute(i);
            cout << res << endl; // Any valid action, such as "WAIT" or "MOVE x y"
        }
    }
}

void Ship::CalculateDistance(vector<Entity> &entities)
{
    targets.clear();
    for (int i = 0; i < entities.size(); i++)
    {
        double distance = solution->Distance(*this, entities[i]);
        targets.push_back(make_pair(distance, &entities[i]));
    }
    sort(targets.begin(), targets.end());
    return;
}

string Solution::Execute(int shipid)
{
    Ship &ship = ships[shipid];
    ship.CalculateDistance(entities);

    int mins = 2147483647;
    Entity *target = nullptr;
    for (int i = 0; i < ship.targets.size(); i++)
    {
        if (ship.targets[i].first < mins && ship.targets[i].second->entity_type != "SHIP")
        {
            mins = ship.targets[i].first;
            target = ship.targets[i].second;
        }
    }

    string res = "MOVE " + to_string(target->x) + " " + to_string(target->y);

    return res;
}

void Solution::Update(vector<Entity> entities, int my_ship_count)
{
    this->entities = entities;
    this->my_ship_count = my_ship_count;
    ships.clear();
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i].entity_type == "SHIP")
        {
            ships.push_back(Ship(entities[i].entity_id, entities[i].entity_type, entities[i].x, entities[i].y, entities[i].arg_1, entities[i].arg_2, entities[i].arg_3, entities[i].arg_4, this));
        }
    }
}

double Solution::Distance(Entity e1, Entity e2)
{
    return sqrt(pow(e1.x - e2.x, 2) + pow(e1.y - e2.y, 2));
}

void Entity::OutputData()
{
    cerr << "Entity ID: " << entity_id << endl;
    cerr << "Entity Type: " << entity_type << endl;
    cerr << "X: " << x << endl;
    cerr << "Y: " << y << endl;
    cerr << "Arg 1: " << arg_1 << endl;
    cerr << "Arg 2: " << arg_2 << endl;
    cerr << "Arg 3: " << arg_3 << endl;
    cerr << "Arg 4: " << arg_4 << endl;
}