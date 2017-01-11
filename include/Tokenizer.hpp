#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>

#include "TokenType.hpp"
#include "TokenOperation.hpp"
#include "Token.hpp"

namespace gba
{

    class Tokenizer
    {
        public:
            std::vector<Token*> *tokenize(std::string p_exp);

        private:
            void tokenizeBuffer(std::vector<Token*> *p_tokens, TokenOperation *p_token_type, std::string *p_buffer);
    };

}

#endif