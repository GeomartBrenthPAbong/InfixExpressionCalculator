#include "ParenthesesCorrection.hpp"

gba::ParenthesesCorrection::ParenthesesCorrection():
    m_reports(new std::vector<std::string>){}

gba::ParenthesesCorrection::~ParenthesesCorrection()
{
    delete m_reports;
    m_reports = 0;
}

std::vector<std::string> *gba::ParenthesesCorrection::getReports()
{
    return m_reports;
}

void gba::ParenthesesCorrection::execute(ParseTree *p_tree)
{
    if(0 == p_tree)
        return;

    ParseTreeNode *root = p_tree->getRoot();
    if(0 == root)
        return;

    m_reports->push_back("Parenthesized: " + executeH(root));
}

std::string gba::ParenthesesCorrection::executeH(ParseTreeNode *p_node)
{
    if(0 == p_node)
        return "";

    std::string *value = p_node->getData()->value;
    TokenType type = p_node->getData()->type;

    std::string answer;

    if(TokenType::NUMBER == type)
        answer = *value;
    else if(TokenType::OPEN_PAR == type)
        answer = executeH(p_node->getRightChild());
    else if(TokenType::POW == type)
        answer = "(" + executeH(p_node->getLeftChild()) + " ^ " + executeH(p_node->getRightChild()) + ")";
    else if(TokenType::MULT == type)
        answer = "(" + executeH(p_node->getLeftChild()) + " * " + executeH(p_node->getRightChild()) + ")";
    else if(TokenType::DIV == type)
        answer = "(" + executeH(p_node->getLeftChild()) + " / " + executeH(p_node->getRightChild()) + ")";
    else if(TokenType::ADD == type)
        answer = "(" + executeH(p_node->getLeftChild()) + " + " + executeH(p_node->getRightChild()) + ")";
    else if(TokenType::SUB == type)
        answer = "(" + executeH(p_node->getLeftChild()) + " - " + executeH(p_node->getRightChild()) + ")";
    else
        answer = "";

    value = 0;

    return answer;
}