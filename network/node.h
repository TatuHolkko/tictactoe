#ifndef NODE_H
#define NODE_H

using namespace std;

class Node
{
public:
    Node();

    //get the current activation value of this node
    virtual float value();

    //update the activation value
    virtual void update();
};

#endif // NODE_H
