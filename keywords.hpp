#pragma once

#include "token.hpp"
#include <string>
#include <unordered_map>

extern const
std::unordered_map<std::string, Token::Kind> keyword_map;
