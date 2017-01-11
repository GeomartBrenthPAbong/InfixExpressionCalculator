#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <vector>

#include "LinkedListQueue.hpp"
#include "TokenType.hpp"
#include "TokenOperation.hpp"
#include "Token.hpp"
#include "ParseTreeNode.hpp"

namespace gba
{

    class ParseTree
    {
        public:
            typedef LinkedListQueue<gba::Token*> Tokens;

            ParseTree();
            ~ParseTree();

            ParseTreeNode *getRoot();

            void create(std::vector<Token*> *p_tokens);

        private:
            bool appendToChildren(ParseTreeNode *p_parent, ParseTreeNode *p_child);
            void separateOperandsAndOperator(std::vector<Token*>* p_tokens);
            short int compareOperatorsByHierarchy(TokenType p_first_op, TokenType p_second_op);
            ParseTreeNode *createSubTree();
            ParseTreeNode *hierarchicalInsert(ParseTreeNode *p_current_node, ParseTreeNode *p_new_node);
            void hierarchicalBubbleUp(ParseTreeNode *p_current_node, ParseTreeNode *p_new_node);
            void hierarchicalBubbleDown(ParseTreeNode *p_current_node, ParseTreeNode *p_new_node);
            void insertAndAssignNodeToParent(ParseTreeNode *p_to_be_child, ParseTreeNode *p_to_be_parent);
            void insertAndAssignNodeToChild(ParseTreeNode *p_to_be_child, ParseTreeNode *p_to_be_parent);
            void replaceChild(ParseTreeNode *p_parent, ParseTreeNode *p_current_child, ParseTreeNode *p_new_child);

            static std::map<gba::TokenType, int> m_operator_hierarchy;
            Tokens *m_operators;
            Tokens *m_operands;
            gba::ParseTreeNode *m_root;
    };

}

#endif