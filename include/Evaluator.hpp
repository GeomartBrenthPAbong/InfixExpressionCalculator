#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <math.h>

#include "TokenType.hpp"
#include "ParseTreeNode.hpp"
#include "TreeOperation.hpp"

namespace gba
{

    class Evaluator: public TreeOperation
    {
        public:
            Evaluator();
            ~Evaluator();

            std::vector<std::string> *getReports();

            void execute(ParseTree *p_tree);

        private:
            float executeH(ParseTreeNode *p_node);

            std::vector<std::string> *m_reports;
    };

}

#endif