#include "ParseTreeNode.hpp"

gba::ParseTreeNode::ParseTreeNode():
    m_data(0), m_left_child(0), m_right_child(0), m_parent(0){}

gba::ParseTreeNode::ParseTreeNode(gba::Token *p_data):
    m_data(p_data), m_left_child(0), m_right_child(0), m_parent(0){}

gba::ParseTreeNode::~ParseTreeNode()
{
    if(0 != m_left_child)
        delete m_left_child;

    m_left_child = 0;

    if(0 != m_right_child)
        delete m_right_child;

    m_right_child = 0;

    m_parent = 0;
    m_data = 0;
}


void gba::ParseTreeNode::setData(gba::Token *p_data)
{
    m_data = p_data;
}

void gba::ParseTreeNode::setLeftChild(ParseTreeNode *p_node)
{
    if(0 != m_left_child)
        m_left_child->setParent(0);

    m_left_child = p_node;

    if(0 == p_node)
        return;

    if(0 != p_node->getParent())
        p_node->getParent()->setLeftChild(0);

    p_node->setParent(this);
}

void gba::ParseTreeNode::setRightChild(ParseTreeNode *p_node)
{
    if(0 != m_right_child)
        m_right_child->setParent(0);

    m_right_child = p_node;

    if(0 == p_node)
        return;

    if(0 != p_node->getParent())
        p_node->getParent()->setRightChild(0);

    p_node->setParent(this);
}

void gba::ParseTreeNode::setParent(ParseTreeNode *p_node)
{
    m_parent = p_node;
}

gba::Token *gba::ParseTreeNode::getData()
{
    return m_data;
}

gba::ParseTreeNode *gba::ParseTreeNode::getLeftChild()
{
    return m_left_child;
}

gba::ParseTreeNode *gba::ParseTreeNode::getRightChild()
{
    return m_right_child;
}

gba::ParseTreeNode *gba::ParseTreeNode::getParent()
{
    return m_parent;
}

bool gba::ParseTreeNode::isFull()
{
    return 0 != m_right_child && 0 != m_left_child;
}

bool gba::ParseTreeNode::isEmpty()
{
    return 0 == m_right_child && 0 == m_left_child;
}