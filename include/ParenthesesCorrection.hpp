#ifndef PARENTHESES_CORRECTION_H
#define PARENTHESES_CORRECTION_H

#include <string>

#include "TokenType.hpp"
#include "ParseTreeNode.hpp"
#include "TreeOperation.hpp"

namespace gba
{

    class ParenthesesCorrection: public TreeOperation
    {
        public:
            ParenthesesCorrection();
            ~ParenthesesCorrection();

            std::vector<std::string> *getReports();

            void execute(ParseTree *p_tree);

        private:
            std::string executeH(ParseTreeNode *p_node);

            std::vector<std::string> *m_reports;
    };

}

#endif