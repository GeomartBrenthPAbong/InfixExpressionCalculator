#include "TokenOperation.hpp"

#include <iostream>

typedef std::map<gba::TokenType, std::regex> TypeMap;

TypeMap gba::TokenOperation::m_token_type_map;

gba::TokenOperation::TokenOperation()
{
    if(0 == m_token_type_map.size())
    {
        m_token_type_map[TokenType::OPEN_PAR] = std::regex("\\(");
        m_token_type_map[TokenType::CLOSE_PAR] = std::regex("\\)");
        m_token_type_map[TokenType::ADD] = std::regex("\\+");
        m_token_type_map[TokenType::SUB] = std::regex("\\-");
        m_token_type_map[TokenType::MULT] = std::regex("\\*");
        m_token_type_map[TokenType::DIV] = std::regex("/");
        m_token_type_map[TokenType::POW] = std::regex("\\^");
        m_token_type_map[TokenType::NUMBER] = std::regex("[0-9]+(.[0-9]*)?");
        m_token_type_map[TokenType::UNKNOWN] =std::regex(".*");
    }
}

gba::Token *gba::TokenOperation::createToken(std::string *p_str)
{
    TypeMap::iterator i;
    gba::Token *token = new gba::Token;

    for(i = m_token_type_map.begin(); i != m_token_type_map.end(); ++i)
    {
        if(std::regex_match(*p_str, (*i).second))
        {
            token->type = (*i).first;
            token->value = new std::string(*p_str);

            break;
        }
    }

    return token;
}

bool gba::TokenOperation::isOfType(TokenType p_type, std::string *p_str)
{
    return std::regex_match(*p_str, m_token_type_map[p_type]);
}