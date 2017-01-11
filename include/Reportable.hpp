#ifndef REPORTABLE_H
#define REPORTABLE_H

#include <string>
#include <vector>

namespace gba
{

    class Reportable
    {
        public:
            virtual ~Reportable(){};

            virtual std::vector<std::string> *getReports() = 0;
    };

}

#endif