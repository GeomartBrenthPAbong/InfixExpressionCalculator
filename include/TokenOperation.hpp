#ifndef TOKEN_OPERATION_H
#define TOKEN_OPERATION_H

#include <map>
#include <vector>
#include <regex>

#include "TokenType.hpp"
#include "Token.hpp"

namespace gba
{

    class TokenOperation
    {
        public:
            

            TokenOperation();

            Token *createToken(std::string *p_str);
            bool isOfType(TokenType p_type, std::string *p_str);

        private:
            static std::map<TokenType, std::regex> m_token_type_map;
    };

}

#endif