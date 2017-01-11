#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H

#include <vector>

#include "Reportable.hpp"
#include "TreeOperation.hpp"

namespace gba
{

    class TreeOperations: public Reportable
    {
        public:
            TreeOperations();
            ~TreeOperations();

            std::vector<std::string> *getReports();

            void add(TreeOperation *p_operation);
            void execute(ParseTree *p_tree);

        private:
            std::vector<TreeOperation*> *m_tree_operations;
            std::vector<std::string> *m_reports;
    };

}

#endif