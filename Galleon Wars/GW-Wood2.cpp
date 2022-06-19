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
    virtual ~Entity() {}
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
        this->minecnt = 0;
        this->minecd = 4;
        this->firecd = 3;
        this->vx = 0;
        this->vy = 0;
        this->prex = 0;
        this->prey = 0;
        this->nextx = 0;
        this->nexty = 0;
        oddlineDirs = {{1, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}, {1, 1}};
        evenlineDirs = {{1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};
        this->solution = solution;
    }
    void Update(int x, int y, int param1, int param2, int param3, int param4);
    bool Fire();
    bool Mine();
    void CalculateDistance(vector<Entity> &entities);
    vector<pair<double, Entity *>> targets;
    int vx;
    int vy;
    int prex;
    int prey;
    int nextx;
    int nexty;

private:
    vector<pair<int, int>> oddlineDirs;
    vector<pair<int, int>> evenlineDirs;
    int minecnt;
    int minecd;
    int firecnt;
    int firecd;
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
    int turn = 0;
    vector<Entity> entities;

private:
    bool Check_No_Mine(int x, int y);
    unordered_map<int, Ship *> myships;
    unordered_map<int, Ship *> enemyships;
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

bool Ship::Fire()
{
    if (firecnt == 0)
    {
        firecnt += 1;
        return true;
    }
    return false;
}

string Solution::Execute(int shipid)
{
    Ship *ship = myships[shipid];
    ship->CalculateDistance(entities);

    int mins = 2147483647;
    Entity *target = nullptr;
    for (int i = 0; i < ship->targets.size(); i++)
    {
        if (ship->targets[i].first < mins && ship->targets[i].second->entity_type == "BARREL" && Check_No_Mine(ship->targets[i].second->x, ship->targets[i].second->y))
        {
            mins = ship->targets[i].first;
            target = ship->targets[i].second;
        }
        if (ship->targets[i].first <= 7 && ship->targets[i].second->entity_type == "SHIP" && ship->targets[i].second->arg_4 == 0)
        {
            Ship *enemy = NULL;
            enemy = (Ship *)enemyships[ship->targets[i].second->entity_id];
            if (enemy == NULL)
            {
                continue;
            }
            if (ship->Fire())
            {
                enemy->OutputData();
                return "FIRE " + to_string(enemy->nextx) + " " + to_string(enemy->nexty);
                // return "FIRE " + to_string(ship.targets[i].second->x) + " " + to_string(ship.targets[i].second->y);
            }
        }
    }

    if (target == nullptr)
    {
        return "WAIT";
    }

    string res = "MOVE " + to_string(target->x) + " " + to_string(target->y);

    return res;
}

bool Solution::Check_No_Mine(int x, int y)
{
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < entities.size(); i++)
    {
        for (int j = 0; j < directions.size(); j++)
        {
            if (entities[i].entity_type == "MINE" && entities[i].x == x + directions[j].first && entities[i].y == y + directions[j].second)
            {
                return false;
            }
        }
    }
    return true;
}

void Ship::Update(int x, int y, int param1, int param2, int param3, int param4)
{
    this->x = x;
    this->y = y;
    this->arg_1 = param1;
    this->arg_2 = param2;
    this->arg_3 = param3;
    this->arg_4 = param4;
    this->prex = x;
    this->prey = y;
    this->firecnt = (this->firecnt + 1) % this->firecd;
    bool isodd = ((x % 2) == 1 || (y % 2) == 1);
    int speed = arg_2;
    if (isodd)
    {
        this->nextx = x + this->oddlineDirs[this->arg_1].first * speed;
        this->nexty = y + this->oddlineDirs[this->arg_1].second * speed;
    }
    else
    {
        this->nextx = x + this->evenlineDirs[this->arg_1].first * speed;
        this->nexty = y + this->evenlineDirs[this->arg_1].second * speed;
    }
    this->vx = this->nextx - this->prex;
    this->vy = this->nexty - this->prey;
}

void Solution::Update(vector<Entity> entities, int my_ship_count)
{
    this->turn++;
    this->entities = entities;
    this->my_ship_count = my_ship_count;
    if (turn == 1)
    {
        for (int i = 0; i < entities.size(); i++)
        {
            if (entities[i].entity_type == "SHIP" && entities[i].arg_4 == 1)
            {
                myships[entities[i].entity_id] = new Ship(entities[i].entity_id, entities[i].entity_type, entities[i].x, entities[i].y, entities[i].arg_1, entities[i].arg_2, entities[i].arg_3, entities[i].arg_4, this);
            }
            else if (entities[i].entity_type == "SHIP" && entities[i].arg_4 == 0)
            {
                enemyships[entities[i].entity_id] = new Ship(entities[i].entity_id, entities[i].entity_type, entities[i].x, entities[i].y, entities[i].arg_1, entities[i].arg_2, entities[i].arg_3, entities[i].arg_4, this);
            }
        }
    }
    else
    {
        for (int i = 0; i < entities.size(); i++)
        {
            if (entities[i].entity_type == "SHIP" && entities[i].arg_4 == 1)
            {

                myships[entities[i].entity_id]->Update(entities[i].x, entities[i].y, entities[i].arg_1, entities[i].arg_2, entities[i].arg_3, entities[i].arg_4);
            }
            else if (entities[i].entity_type == "SHIP" && entities[i].arg_4 == 0)
            {

                enemyships[entities[i].entity_id]->Update(entities[i].x, entities[i].y, entities[i].arg_1, entities[i].arg_2, entities[i].arg_3, entities[i].arg_4);
            }
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
