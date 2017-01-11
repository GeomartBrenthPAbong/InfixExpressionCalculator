#include "Token.hpp"

gba::Token::~Token()
{
    delete value;
    value = 0;
}