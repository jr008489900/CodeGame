#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/**
 * Bring data on patient samples from the diagnosis machine to the laboratory with enough molecules to produce medicine!
 **/

class Bag
{
public:
    Bag()
    {
        storage_arr.resize(5, 0);
    }
    void print()
    {
        cerr << "Bag******" << endl;
        cerr << target << " " << eta << " " << score << " ";
        for (int i = 0; i < storage_arr.size(); ++i)
            cerr << storage_arr[i] << " ";
        cerr << endl;
        cerr << expertise_a << " " << expertise_b << " " << expertise_c << " " << expertise_d << " " << expertise_e << endl;
    }
    string target;
    int eta;
    int score;
    vector<int> storage_arr;

    int expertise_a;
    int expertise_b;
    int expertise_c;
    int expertise_d;
    int expertise_e;
};

class Sample
{
public:
    Sample()
    {
        costs.resize(5, 0);
    }
    void print()
    {
        cerr << sample_id << " " << carried_by << " " << rank << " " << expertise_gain << " " << health << " ";
        for (int i = 0; i < costs.size(); ++i)
            cerr << costs[i] << " ";
        cerr << endl;
    }
    int sample_id;
    int carried_by;
    int rank;
    string expertise_gain;
    int health;
    vector<int> costs;
};

class Project
{
public:
    Project()
    {
        arr.resize(5, 0);
        projectid = 0;
    }
    void print()
    {
        cerr << projectid << " ";
        for (int i = 0; i < arr.size(); ++i)
            cerr << arr[i] << " ";
        cerr << endl;
    }
    static bool cmp(Project &a, Project &b)
    {
        int sa = 0, sb = 0;
        for (auto i : a.arr)
            sa += i;
        for (auto i : b.arr)
            sb += i;
        return sa < sb;
    }
    vector<int> arr;
    int projectid;
};

class Object
{
public:
    virtual void Goto(){};
    virtual void Wait()
    {
        cout << "WAIT" << endl;
    }
    virtual void Connect(char n)
    {
        cout << "CONNECT " << n << endl;
    }
    virtual void Connect(int n)
    {
        cout << "CONNECT " << n << endl;
    }
};

class SampleObject : public Object
{
public:
    virtual void Goto() override
    {
        cout << "GOTO SAMPLES" << endl;
    }
};

class DiagnosticObject : public Object
{
public:
    virtual void Goto() override
    {
        cout << "GOTO DIAGNOSIS" << endl;
    }
};

class MoleObject : public Object
{
public:
    virtual void Goto() override
    {
        cout << "GOTO MOLECULES" << endl;
    }
};

class LabObject : public Object
{
public:
    virtual void Goto() override
    {
        cout << "GOTO LABORATORY" << endl;
    }
};

class Machine
{
public:
    Machine()
    {
        stateidx = 0;
        bagArr.resize(2);
        int e = INT_MAX;
        curobj = &sampleobj;
        available.resize(5, 0);
        bagcapacity = 0;
        rounds = 0;
        canprempt = 0;
        state = 0;
        FirstStage f1 = FirstStage(*this);
        stageArr = {f1};
    }
    void ClearBag()
    {
        bagArr.clear();
    }
    void ClearSample()
    {
        sampleArr.clear();
        cursample.clear();
    }

    void Execute()
    {
        Preprocessing();
        cerr << state << endl;
        for (auto s : cursample)
            s.print();
        bagArr[0].print();
        for (auto s : sampleArr)
            s.print();
        if (bagArr[0].eta > 0)
        {
            curobj->Wait();
            return;
        }

        switch (state)
        {
        case 0:
            if (stageArr[state].Execute(5))
                state++;
            break;
        case 1:
            break;

            state %= stageArr.size();
        }

        /*switch (state)
        {
        case 0:
            curobj = &sampleobj;
            curobj->Goto();
            break;
        case 1:
            curobj->Connect('1');
            break;
        case 2:
            curobj->Connect(max({rounds, 1}));
            break;
        case 3:
            curobj->Connect('2');
            break;
        case 4:
            curobj = &diagnosticobj;
            curobj->Goto();
            break;
        case 5:
        {
            bool check = 0;
            int t = 0;
            for (int i = 0; i < cursample.size(); ++i)
            {
                if (isdiagnosis(cursample[i]))
                {
                    t = i;
                    curobj->Connect(cursample[i].sample_id);
                    break;
                }
            }
            for (int i = 0; i < cursample.size(); ++i)
            {
                if (isdiagnosis(cursample[i]))
                {
                    if (t != i)
                        check = 1;
                }
            }
            if (check)
                state -= 1;
            break;
        }
        case 6:
        {
            bool check = 0;
            int t = 0;
            for (int i = 0; i < cursample.size(); ++i)
            {
                if (isdelete(cursample[i]))
                {
                    t = i;
                    curobj->Connect(cursample[i].sample_id);
                    break;
                }
            }
            for (int i = 0; i < cursample.size(); ++i)
            {
                if (isdelete(cursample[i]))
                {
                    if (t != i)
                        check = 1;
                }
            }
            if (check)
                state -= 1;
            else
                curobj->Wait();
            break;
        }
        case 7:
            curobj = &moleobj;
            curobj->Goto();
            break;
        case 8:
        {
            bagArr[0].print();
            if (rounds != 0 && bagArr[1].target == "MOLECULES" && !canprempt)
            {
                curobj->Wait();
                state -= 1;
            }
            else if (!iscomplete(bagArr[0], cursample[0]))
            {
                state -= 1;
            }
            else
            {
                canprempt = 0;
                curobj = &labobj;
                curobj->Goto();
                break;
            }
            break;
        }
        case 9:
        {
            curobj->Connect(cursample[0].sample_id);
            break;
        }
        case 10:
        {
            if (cursample.size() > 0)
            {
                curobj = &moleobj;
                curobj->Goto();
                state = 7;
            }
            else
            {
                state = 0;
                curobj = &sampleobj;
                curobj->Goto();
                rounds++;
            }
            break;
        }
        default:
            curobj->Wait();
            break;
        }
        */
    }

    vector<Bag> bagArr;
    vector<Sample> sampleArr;
    vector<int> available;
    vector<Project> projectArr;

private:
    int find_highvalue(vector<Sample> &s)
    {
        int maxs = -2147483648, pos = -1;
        for (int i = 0; i < s.size(); ++i)
        {
            if (record.find(s[i].sample_id) == record.end() && s[i].health > maxs)
            {
                pos = i;
                maxs = s[i].health;
            }
        }
        return pos;
    }
    bool iscomplete(Bag b, Sample s)
    {
        canprempt = 1;
        s.print();
        for (int i = 0; i < b.storage_arr.size(); ++i)
        {
            if (b.storage_arr[i] < s.costs[i] && available[i] > 0)
            {
                char c = ('A' + i);
                curobj->Connect(c);
                return false;
            }
            /*else if(b.storage_arr[i] < s.costs[i] && available[i]==0)
            {
                curobj->Wait();
                return false;
            }*/
        }
        return true;
    }
    bool isfinish(Bag b, Sample s)
    {
        for (int i = 0; i < 5; ++i)
            if (b.storage_arr[i] != s.costs[i])
                return 0;
        return 1;
    }

    void Preprocessing()
    {
        bagcapacity = 0;
        for (auto s : sampleArr)
            if (s.carried_by == 0)
                cursample.push_back(s);
        for (int i = 0; i < bagArr[0].storage_arr.size(); ++i)
            bagcapacity += bagArr[0].storage_arr[i];
    }

    bool isdelete(Sample s)
    {
        int total = 0;
        for (int i = 0; i < s.costs.size(); ++i)
        {
            total += s.costs[i];
            if (s.costs[i] > 5)
                return true;
        }
        if (total > 10)
            return true;
        return false;
    }

    bool isdiagnosis(Sample s)
    {
        for (auto v : s.costs)
            if (v == -1)
                return true;
        return false;
    }

    class Stage
    {
    public:
        Stage()
        {
            state = 0;
            rounds = 0;
            mptr = NULL;
        }
        Stage(Machine m)
        {
            state = 0;
            rounds = 0;
            mptr = &m;
        }
        virtual int Execute(int n) = 0;

    protected:
        int state;
        int rounds;
        Object *curobj;
        SampleObject sampleobj;
        DiagnosticObject diagnosticobj;
        MoleObject moleobj;
        LabObject labobj;
        Machine *mptr;
    };

    class FirstStage : public Stage
    {
    public:
        FirstStage(Machine m)
        {
            state = 0;
            rounds = 0;
            mptr = &m;
            curobj = &sampleobj;
        }
        int Execute(int n)
        {
            cerr << state << " stage" << endl;
            Preprocessing();
            if (mptr->bagArr[0].eta > 0)
            {
                curobj->Wait();
                return 0;
            }
            switch (state)
            {
            case 0:
                curobj = &sampleobj;
                curobj->Goto();
                break;
            case 1:
                curobj->Connect('1');
                break;
            case 2:
                curobj->Connect(max({rounds}));
                break;
            case 3:
                curobj->Connect('2');
                break;
            case 4:
                curobj = &diagnosticobj;
                curobj->Goto();
                break;
            case 5:
            {
                bool check = 0;
                int t = 0;
                for (int i = 0; i < cursample.size(); ++i)
                {
                    if (isdiagnosis(cursample[i]))
                    {
                        t = i;
                        curobj->Connect(cursample[i].sample_id);
                        break;
                    }
                }
                for (int i = 0; i < cursample.size(); ++i)
                {
                    if (isdiagnosis(cursample[i]))
                    {
                        if (t != i)
                            check = 1;
                    }
                }
                if (check)
                    state -= 1;
                break;
            }
            case 6:
            {
                if (cursample.size() > 1)
                    state -= 1;
                if (cursample.size() == 1)
                {
                    curobj->Connect(cursample[0].sample_id);
                    state = -1;
                }
                break;
            }
            default:
                cerr << "First Stage error" << endl;
                curobj->Wait();
                break;
            }
            state = (state + 1) % 7;
            bool check = 0;
            if (state == 0)
                rounds++;
            if (rounds == n)
            {
                check = 1;
                rounds = 0;
            }
            return check;
        }

    private:
        vector<Sample> cursample;
        void Preprocessing()
        {
            for (auto s : mptr->sampleArr)
                if (s.carried_by == 0)
                    cursample.push_back(s);
        }
        bool isdelete(Sample s)
        {
            int total = 0;
            for (int i = 0; i < s.costs.size(); ++i)
            {
                total += s.costs[i];
                if (s.costs[i] > 5)
                    return true;
            }
            if (total > 10)
                return true;
            return false;
        }

        bool isdiagnosis(Sample s)
        {
            for (auto v : s.costs)
                if (v == -1)
                    return true;
            return false;
        }
    };
    /**______________________________________________*/

    bool canprempt = 0;
    int bagcapacity;
    Object *curobj;
    SampleObject sampleobj;
    DiagnosticObject diagnosticobj;
    MoleObject moleobj;
    LabObject labobj;
    int state;
    set<int> record;
    vector<Stage> stageArr;
    vector<Sample> cursample;
    int stateidx;
    const int INT_MAX = 2147483647;
    int rounds;
    bool canprempt;
};

int main()
{
    Machine machine = Machine();
    int project_count;
    cin >> project_count;
    cin.ignore();
    for (int i = 0; i < project_count; i++)
    {
        Project p = Project();
        p.projectid = i;
        int a;
        int b;
        int c;
        int d;
        int e;
        cin >> a >> b >> c >> d >> e;
        cin.ignore();
        p.arr[0] = a;
        p.arr[1] = b;
        p.arr[2] = c;
        p.arr[3] = d;
        p.arr[4] = e;
        machine.projectArr.push_back(p);
    }

    for (auto i : machine.projectArr)
        i.print();

    // game loop
    while (1)
    {
        machine.ClearBag();
        machine.ClearSample();
        for (int i = 0; i < 2; i++)
        {
            Bag bag = Bag();
            string target;
            int eta;
            int score;
            int storage_a;
            int storage_b;
            int storage_c;
            int storage_d;
            int storage_e;
            int expertise_a;
            int expertise_b;
            int expertise_c;
            int expertise_d;
            int expertise_e;
            cin >> target >> eta >> score >> storage_a >> storage_b >> storage_c >> storage_d >> storage_e >> expertise_a >> expertise_b >> expertise_c >> expertise_d >> expertise_e;
            cin.ignore();
            bag.target = target;
            bag.eta = eta;
            bag.score = score;
            bag.storage_arr[0] = storage_a;
            bag.storage_arr[1] = storage_b;
            bag.storage_arr[2] = storage_c;
            bag.storage_arr[3] = storage_d;
            bag.storage_arr[4] = storage_e;
            bag.expertise_a = expertise_a;
            bag.expertise_b = expertise_b;
            bag.expertise_c = expertise_c;
            bag.expertise_d = expertise_d;
            bag.expertise_e = expertise_e;
            machine.bagArr.push_back(bag);
        }
        int available_a;
        int available_b;
        int available_c;
        int available_d;
        int available_e;
        cin >> available_a >> available_b >> available_c >> available_d >> available_e;
        cin.ignore();
        machine.available[0] = available_a;
        machine.available[1] = available_b;
        machine.available[2] = available_c;
        machine.available[3] = available_d;
        machine.available[4] = available_e;
        int sample_count;
        cin >> sample_count;
        cin.ignore();
        for (int i = 0; i < sample_count; i++)
        {
            Sample s = Sample();
            int sample_id;
            int carried_by;
            int rank;
            string expertise_gain;
            int health;
            int cost_a;
            int cost_b;
            int cost_c;
            int cost_d;
            int cost_e;
            cin >> sample_id >> carried_by >> rank >> expertise_gain >> health >> cost_a >> cost_b >> cost_c >> cost_d >> cost_e;
            cin.ignore();
            s.sample_id = sample_id;
            s.carried_by = carried_by;
            s.rank = rank;
            s.expertise_gain = expertise_gain;
            s.health = health;
            s.costs[0] = cost_a;
            s.costs[1] = cost_b;
            s.costs[2] = cost_c;
            s.costs[3] = cost_d;
            s.costs[4] = cost_e;
            machine.sampleArr.push_back(s);
        }

        machine.Execute();
    }
}