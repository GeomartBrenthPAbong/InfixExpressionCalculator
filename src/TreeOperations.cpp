#include "TreeOperations.hpp"

gba::TreeOperations::TreeOperations():
    m_tree_operations(new std::vector<TreeOperation*>), 
    m_reports(new std::vector<std::string>){}

gba::TreeOperations::~TreeOperations()
{
    delete m_tree_operations;
    m_tree_operations = 0;

    delete m_reports;
    m_reports = 0;
}

std::vector<std::string> *gba::TreeOperations::getReports()
{
    return m_reports;
}

void gba::TreeOperations::add(TreeOperation *p_tree_operation)
{
    m_tree_operations->push_back(p_tree_operation);
}

void gba::TreeOperations::execute(ParseTree *p_tree)
{
    if(0 == m_tree_operations->size())
        return;
    
    TreeOperation *current_operation;
    std::vector<std::string> *reports;
    int num_operations = m_tree_operations->size(), num_reports;

    for(int i = 0; i < num_operations; ++i)
    {
        current_operation = (*m_tree_operations)[i];

        current_operation->execute(p_tree);
        reports = current_operation->getReports();

        num_reports = reports->size();
        for(int j = 0; j < num_reports; ++j)
            m_reports->push_back((*reports)[j]);
    }

    current_operation = 0;
    reports = 0;
}