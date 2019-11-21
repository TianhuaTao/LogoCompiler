#if !defined(OPSQUEUE_H)
#define OPSQUEUE_H
#include <string>
#include <vector>
class Op;
class OpsQueue {
private:
    std::vector<Op*> _ops;
    std::string ownerName;

public:
    OpsQueue(std::string ownerName);
    ~OpsQueue();
    std::vector<Op *> *getOps() {
        return &_ops;
    }
    std::string getName() const {
        return ownerName;
    }
};

#endif // OPSQUEUE_H





