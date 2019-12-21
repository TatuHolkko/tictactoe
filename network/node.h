#ifndef INODE_H
#define INODE_H

using namespace std;

class INode
{
public:
    virtual ~INode();
    //get the current activation value of this node
    virtual float value();

    //update the activation value
    virtual void update();
};

#endif // INODE_H
