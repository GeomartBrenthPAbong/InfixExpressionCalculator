#include "Reporter.hpp"

void gba::Reporter::report(Reportable *p_reportable)
{
    if(0 == p_reportable)
        return;

    std::vector<std::string> *reports = p_reportable->getReports();
    int num_reports = reports->size();

    for(int i = 0; i < num_reports; ++i)
        std::cout << (*reports)[i] << std::endl;
}