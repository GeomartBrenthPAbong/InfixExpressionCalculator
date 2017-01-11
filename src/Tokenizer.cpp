#include "Tokenizer.hpp"

std::vector<gba::Token*> *gba::Tokenizer::tokenize(std::string p_exp)
{
    gba::TokenOperation *token_operation = new gba::TokenOperation;
    std::vector<gba::Token*> *tokens = new std::vector<gba::Token*>;

    std::string *buffer = new std::string;
    std::string *current_char = new std::string;

    int exp_length = p_exp.length();
    for(int i = 0; i < exp_length; ++i)
    {
        current_char->push_back(p_exp[i]);

        if(" " == *current_char)
        {
            tokenizeBuffer(tokens, token_operation, buffer);
            buffer->clear();
        }
        else if(!token_operation->isOfType(TokenType::NUMBER, current_char))
        {
            tokenizeBuffer(tokens, token_operation, buffer);
            tokenizeBuffer(tokens, token_operation, current_char);

            buffer->clear();
        }
        else
            *buffer += *current_char;

        current_char->pop_back();
    }

    tokenizeBuffer(tokens, token_operation, buffer);

    delete token_operation;
    token_operation = 0;

    delete current_char;
    current_char = 0;

    delete buffer;
    buffer = 0;

    return tokens;
}


void gba::Tokenizer::tokenizeBuffer(std::vector<gba::Token*> *p_tokens, gba::TokenOperation *p_token_operation, std::string *p_buffer)
{
    if(0 != p_buffer->length())
        p_tokens->push_back(p_token_operation->createToken(p_buffer));
}