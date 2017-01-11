#include "SyntaxAnalyzer.hpp"

gba::SyntaxAnalyzer::SyntaxAnalyzer():
    m_current_state('A'), m_par_pairer(0){}

void gba::SyntaxAnalyzer::analyze(std::vector<Token*> *p_tokens)
{
    stateA((*p_tokens)[0]);

    if('A' != m_current_state)
        throw new std::exception;

    Token *current_token;
    int num_tokens = p_tokens->size();
    for(int i = 1; i < num_tokens; ++i)
    {
        current_token = (*p_tokens)[i];

        if('A' == m_current_state)
            stateA(current_token);
        else if('B' == m_current_state)
            stateB(current_token);
        else if('C' == m_current_state)
            stateC(current_token);
        else if('D' == m_current_state)
            stateD(current_token);
        else
            break;
    }

    if('D' != m_current_state || 0 != m_par_pairer)
        throw new std::exception;
}

void gba::SyntaxAnalyzer::stateA(Token *p_token)
{
    if(TokenType::OPEN_PAR == p_token->type)
    {
        m_current_state = 'A';
        m_par_pairer++;
    }
    else if(TokenType::NUMBER == p_token->type)
        m_current_state = 'B';
    else 
        m_current_state = 'Z';
}

void gba::SyntaxAnalyzer::stateB(Token *p_token)
{
    if(isOperator(p_token))
        m_current_state = 'C';
    else if(TokenType::CLOSE_PAR == p_token->type)
    {
        m_current_state = 'D';
        m_par_pairer--;
    }
    else
        m_current_state = 'Z';
}

void gba::SyntaxAnalyzer::stateC(Token *p_token)
{
    if(TokenType::NUMBER == p_token->type)
        m_current_state = 'B';
    else if(TokenType::OPEN_PAR == p_token->type)
    {
        m_current_state = 'A';
        m_par_pairer++;
    }
    else
        m_current_state = 'Z';
}

void gba::SyntaxAnalyzer::stateD(Token *p_token)
{
    if(isOperator(p_token))
        m_current_state = 'C';
    else if(TokenType::CLOSE_PAR == p_token->type)
    {
        m_current_state = 'D';
        m_par_pairer--;
    }
    else
        m_current_state = 'Z';
}

bool gba::SyntaxAnalyzer::isOperator(Token *p_token)
{
    TokenType type = p_token->type;

    return (TokenType::NUMBER != type && 
            TokenType::OPEN_PAR != type && 
            TokenType::CLOSE_PAR != type && 
            TokenType::UNKNOWN != type);
}