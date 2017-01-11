#ifndef MESSAGE_BAG_HPP
#define MESSAGE_BAG_HPP

#include "Reportable.hpp"

namespace gba
{

    class MessageBag: public Reportable
    {
        public:
            MessageBag();
            ~MessageBag();

            void add(std::string &p_message);

            std::vector<std::string> *getReports();

        private:
            std::vector<std::string> *m_reports;
    };

}

#endif