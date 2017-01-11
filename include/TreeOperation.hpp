#ifndef TREE_OPERATION_H
#define TREE_OPERATION_H

#include "ParseTree.hpp"
#include "Reportable.hpp"

namespace gba
{

    class TreeOperation: public Reportable
    {
        public:
            virtual ~TreeOperation(){};

            virtual void execute(ParseTree *p_tree) = 0;
    };

}

#endif