#ifndef INODE_H
#define INODE_H

using namespace std;

class INode
{
public:
    virtual ~INode();
    //get the current activation value of this node
    virtual float value() const = 0;

    //update the activation value
    virtual void update() = 0;
};

#endif // INODE_H
