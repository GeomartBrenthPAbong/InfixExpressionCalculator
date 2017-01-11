#include "ParseTree.hpp"
#include <iostream>

typedef gba::LinkedListQueue<gba::Token*> Tokens;

std::map<gba::TokenType, int> gba::ParseTree::m_operator_hierarchy;

gba::ParseTree::ParseTree():
    m_operators(0), m_operands(0), m_root(0)
{
    m_operator_hierarchy[TokenType::NUMBER] = 0;
    m_operator_hierarchy[TokenType::OPEN_PAR] = 1;
    m_operator_hierarchy[TokenType::POW] = 2;
    m_operator_hierarchy[TokenType::MULT] = 3;
    m_operator_hierarchy[TokenType::DIV] = 4;
    m_operator_hierarchy[TokenType::ADD] = 5;
    m_operator_hierarchy[TokenType::SUB] = 6;
}

gba::ParseTree::~ParseTree()
{
    delete m_root;
    m_root = 0;

    delete m_operands;
    m_operands = 0;

    delete m_operators;
    m_operators = 0;
}

void gba::ParseTree::create(std::vector<gba::Token*> *p_tokens)
{
    if(0 == p_tokens->size())
        return;
    
    separateOperandsAndOperator(p_tokens);
    m_root = createSubTree();
}

gba::ParseTreeNode *gba::ParseTree::getRoot()
{
    return m_root;
}

bool gba::ParseTree::appendToChildren(gba::ParseTreeNode *p_parent, gba::ParseTreeNode *p_child)
{
    if(0 == p_parent || 0 == p_child)
        return false;

    if(0 == p_parent->getLeftChild())
        p_parent->setLeftChild(p_child);
    else
        p_parent->setRightChild(p_child);

    return true;
}

void gba::ParseTree::separateOperandsAndOperator(std::vector<gba::Token*> *p_tokens)
{
    m_operands = new Tokens;
    m_operators = new Tokens;

    std::vector<Token*>::iterator i;
    for(i = p_tokens->begin(); i != p_tokens->end(); ++i)
    {
        if(TokenType::NUMBER == (*i)->type)
            m_operands->enqueue(*i);
        else
            m_operators->enqueue(*i);
    }
}

short int gba::ParseTree::compareOperatorsByHierarchy(gba::TokenType p_first_op, gba::TokenType p_second_op)
{
    if(m_operator_hierarchy[p_first_op] < m_operator_hierarchy[p_second_op])
        return -1;
    else if(m_operator_hierarchy[p_first_op] > m_operator_hierarchy[p_second_op])
        return 1;
    else
        return 0;
}

gba::ParseTreeNode *gba::ParseTree::createSubTree()
{
    if(0 == m_operators->size())
        return 0;

    ParseTreeNode *root = 0, *current_node = 0, *new_node = 0;
    Token *current_token = 0;
    TokenType current_token_type;

    do
    {
        current_token = m_operators->dequeue();
        current_token_type = current_token->type;

        if(TokenType::OPEN_PAR == current_token_type)
        {
            new_node = new gba::ParseTreeNode(current_token);

            if(0 == root)
            {
                root = new_node;
                root->setRightChild(createSubTree());
                current_node = new_node;
            }
            else
            {
                if(TokenType::OPEN_PAR == current_node->getData()->type)
                    current_node->setRightChild(new_node);
                else
                    appendToChildren(current_node, new_node);
                
                new_node->setRightChild(createSubTree());
            }
        }
        else if(TokenType::CLOSE_PAR == current_token_type)
        {
            if(0 != m_operands->size() && 0 == root)
                root = new gba::ParseTreeNode(m_operands->dequeue());
            else if(!current_node->isFull() && 0 != m_operands->size())
                appendToChildren(current_node, new gba::ParseTreeNode(m_operands->dequeue()));
        }
        else if(0 != current_node)
        {
            current_node = hierarchicalInsert(current_node, new gba::ParseTreeNode(current_token));

            if(0 == current_node->getParent())
                root = current_node;
        }
        else
        {
            root = new gba::ParseTreeNode(current_token);
            appendToChildren(root, new gba::ParseTreeNode(m_operands->dequeue()));
            current_node = root;
        }
    }
    while(0 != m_operators->size() && TokenType::CLOSE_PAR != current_token_type);
    
    return root;
}

gba::ParseTreeNode *gba::ParseTree::hierarchicalInsert(ParseTreeNode *p_current_node, ParseTreeNode *p_new_node)
{
    int hierarchy = compareOperatorsByHierarchy(p_current_node->getData()->type, p_new_node->getData()->type);

    if(TokenType::OPEN_PAR == p_current_node->getData()->type)
    {
        ParseTreeNode *parent = p_current_node->getParent();

        if(0 != parent)
            replaceChild(parent, p_current_node, p_new_node);

        insertAndAssignNodeToParent(p_current_node, p_new_node);
    }
    else if(1 == hierarchy)
        hierarchicalBubbleDown(p_current_node, p_new_node);
    else if(-1 == hierarchy)
        hierarchicalBubbleUp(p_current_node, p_new_node);
    else
    {
        ParseTreeNode *parent = p_current_node->getParent();

        if(0 != parent)
            replaceChild(parent, p_current_node, p_new_node);

        if(p_current_node->isFull())
            insertAndAssignNodeToParent(p_current_node, p_new_node);
        else
            insertAndAssignNodeToChild(p_current_node, p_new_node);
    }

    return p_new_node;
}

void gba::ParseTree::hierarchicalBubbleDown(ParseTreeNode *p_current_node, ParseTreeNode *p_new_node)
{
    ParseTreeNode *prev_node;
    prev_node = p_current_node->getParent();

    while(0 != p_current_node &&
          TokenType::OPEN_PAR != p_current_node->getData()->type &&
          1 == compareOperatorsByHierarchy(p_current_node->getData()->type, 
                                           p_new_node->getData()->type))
    {
        prev_node = p_current_node;
        p_current_node = p_current_node->getRightChild();
    }

    if(0 == p_current_node)
    {
        insertAndAssignNodeToChild(p_new_node, prev_node);
    }
    else if(TokenType::OPEN_PAR == p_current_node->getData()->type ||
            p_current_node->isFull() ||
            TokenType::NUMBER == p_current_node->getData()->type)
    {
        if(0 != prev_node)
            replaceChild(prev_node, p_current_node, p_new_node);

        insertAndAssignNodeToParent(p_current_node, p_new_node);
    }
    else
        insertAndAssignNodeToChild(p_new_node, p_current_node);
}

void gba::ParseTree::hierarchicalBubbleUp(ParseTreeNode *p_current_node, ParseTreeNode *p_new_node)
{
    ParseTreeNode *prev_node, *last_current_node = p_current_node;
    prev_node = p_current_node->getRightChild();

    while(0 != p_current_node &&
          TokenType::OPEN_PAR != p_current_node->getData()->type &&
          0 >= compareOperatorsByHierarchy(p_current_node->getData()->type, 
                                           p_new_node->getData()->type))
    {
        prev_node = p_current_node;
        p_current_node = p_current_node->getParent();
    }

    if(0 == p_current_node)
    {
        if(last_current_node->isFull())
        {
            if(prev_node->isFull())
                insertAndAssignNodeToParent(prev_node, p_new_node);
            else
                insertAndAssignNodeToChild(prev_node, p_new_node);
        }
        else
        {
            appendToChildren(p_new_node, prev_node);

            if(0 != m_operands->size())
                appendToChildren(last_current_node, new gba::ParseTreeNode(m_operands->dequeue()));
        }
    }
    else if(TokenType::OPEN_PAR == p_current_node->getData()->type || p_current_node->isFull())
    {
        if(0 != prev_node)
            replaceChild(p_current_node, prev_node, p_new_node);

        if(last_current_node->isFull())
            insertAndAssignNodeToParent(prev_node, p_new_node);
        else
        {
            appendToChildren(p_new_node, prev_node);

            if(0 != m_operands->size())
                appendToChildren(last_current_node, new gba::ParseTreeNode(m_operands->dequeue()));
        }
    }
    else
        insertAndAssignNodeToChild(p_new_node, p_current_node);
}

void gba::ParseTree::insertAndAssignNodeToParent(ParseTreeNode *p_to_be_child, ParseTreeNode *p_to_be_parent)
{
    appendToChildren(p_to_be_parent, p_to_be_child);

    if(0 != m_operands->size() && (0 == m_operators->size() || TokenType::OPEN_PAR != m_operators->front()->type))
        appendToChildren(p_to_be_parent, new gba::ParseTreeNode(m_operands->dequeue()));
}

void gba::ParseTree::insertAndAssignNodeToChild(ParseTreeNode *p_to_be_child, ParseTreeNode *p_to_be_parent)
{
    appendToChildren(p_to_be_parent, p_to_be_child);

    if(0 != m_operands->size() && (0 == m_operators->size() || TokenType::OPEN_PAR != m_operators->front()->type))
        appendToChildren(p_to_be_child, new gba::ParseTreeNode(m_operands->dequeue()));
}

void gba::ParseTree::replaceChild(ParseTreeNode *p_parent, ParseTreeNode *p_current_child, ParseTreeNode *p_new_child)
{
    if(p_current_child == p_parent->getLeftChild())
        p_parent->setLeftChild(p_new_child);
    else if(p_current_child == p_parent->getRightChild())
        p_parent->setRightChild(p_new_child);
}