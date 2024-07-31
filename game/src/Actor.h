
class Actor
{
public:
    enum State
    {
        stateActive,
        statePaused,
        stateDead
    };

    Actor(class Game* game);
    virtual ~Actor();

    

};

