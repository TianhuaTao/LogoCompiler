class Op
{
private:
    
public:
    Op();
    virtual ~Op();
    virtual void exec() = 0;
};

Op::Op()
{
}

Op::~Op()
{
}


class cloakOp:public Op
{
private:
    
public:
    cloakOp();
    ~cloakOp();
};

cloakOp::cloakOp()
{
}

cloakOp::~cloakOp()
{
}

class StartLoopOp
{
private:
    
public:
    StartLoopOp(int loops);
    ~StartLoopOp();
};

StartLoopOp::StartLoopOp(int loops)
{
}

StartLoopOp::~StartLoopOp()
{
}

class EndLoopOp
{
private:
    
public:
    EndLoopOp(Op* start);
    ~EndLoopOp();
};

EndLoopOp::EndLoopOp(Op* start)
{
}

EndLoopOp::~EndLoopOp()
{
}


class AddOp
{
private:
    
public:
    AddOp(Variable* v, int value);
    ~AddOp();
};

AddOp::AddOp(Variable* v, int value)
{
}

AddOp::~AddOp()
{
}

