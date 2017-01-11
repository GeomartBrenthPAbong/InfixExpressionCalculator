#include "Evaluator.hpp"

gba::Evaluator::Evaluator():
    m_reports(new std::vector<std::string>){}

gba::Evaluator::~Evaluator()
{
    delete m_reports;
    m_reports = 0;
}

std::vector<std::string> *gba::Evaluator::getReports()
{
    return m_reports;
}

void gba::Evaluator::execute(ParseTree *p_tree)
{
    if(0 == p_tree)
        return;
    
    ParseTreeNode *root = p_tree->getRoot();
    if(0 == root)
        return;

    m_reports->push_back("Answer: " + std::to_string(executeH(root)));
}

float gba::Evaluator::executeH(ParseTreeNode *p_node)
{
    if(0 == p_node)
        return 0;

    std::string *value = p_node->getData()->value;
    TokenType type = p_node->getData()->type;

    float answer;

    if(TokenType::NUMBER == type)
        answer = std::stof(*value);
    else if(TokenType::OPEN_PAR == type)
        answer = executeH(p_node->getRightChild());
    else if(TokenType::POW == type)
        answer = pow(executeH(p_node->getLeftChild()), executeH(p_node->getRightChild()));
    else if(TokenType::MULT == type)
        answer = executeH(p_node->getLeftChild()) * executeH(p_node->getRightChild());
    else if(TokenType::DIV == type)
        answer = executeH(p_node->getLeftChild()) / executeH(p_node->getRightChild());
    else if(TokenType::ADD == type)
        answer = executeH(p_node->getLeftChild()) + executeH(p_node->getRightChild());
    else if(TokenType::SUB == type)
        answer = executeH(p_node->getLeftChild()) - executeH(p_node->getRightChild());
    else
        answer = 0;

    value = 0;

    return answer;
}