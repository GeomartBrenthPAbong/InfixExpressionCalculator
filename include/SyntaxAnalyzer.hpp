#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include "ParseTree.hpp"
#include "TokenType.hpp"
#include "Token.hpp"

namespace gba
{

    class SyntaxAnalyzer
    {
        public:
            SyntaxAnalyzer();

            void analyze(std::vector<Token*> *p_tokens);

        private:
            void stateA(Token *p_token);
            void stateB(Token *p_token);
            void stateC(Token *p_token);
            void stateD(Token *p_token);
            bool isOperator(Token *p_token);

            char m_current_state;
            int m_par_pairer;
    };

}

#endif