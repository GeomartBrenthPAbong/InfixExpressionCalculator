#ifndef PARSE_TREE_NODE_H
#define PARSE_TREE_NODE_H

#include "Token.hpp"

namespace gba
{

    class ParseTreeNode
    {
        public:
            ParseTreeNode();
            ParseTreeNode(gba::Token *p_data);
            ~ParseTreeNode();

            void setData(gba::Token *p_data);
            void setLeftChild(ParseTreeNode *p_node);
            void setRightChild(ParseTreeNode *p_node);
            void setParent(ParseTreeNode *p_node);
            bool isFull();
            bool isEmpty();

            gba::Token *getData();
            ParseTreeNode *getLeftChild();
            ParseTreeNode *getRightChild();
            ParseTreeNode *getParent();

        private:
            gba::Token *m_data;
            ParseTreeNode *m_left_child;
            ParseTreeNode *m_right_child;
            ParseTreeNode *m_parent;
    };

}

#endif