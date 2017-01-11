#ifndef REPORTER_H
#define REPORTER_H

#include <iostream>
#include "Reportable.hpp"

namespace gba
{

    class Reporter
    {
        public:
            void report(Reportable *p_reportable);
    };

}

#endif