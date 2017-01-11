#include "MessageBag.hpp"

gba::MessageBag::MessageBag():
    m_reports(new std::vector<std::string>){}

gba::MessageBag::~MessageBag()
{
    delete m_reports;
    m_reports = 0;
}

void gba::MessageBag::add(std::string &p_message)
{
    m_reports->push_back(p_message);
}

std::vector<std::string> *gba::MessageBag::getReports()
{
    return m_reports;
}