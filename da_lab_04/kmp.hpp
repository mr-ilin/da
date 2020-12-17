#pragma once

#include <vector>
#include <string>

size_t KMPSearch(const std::vector<std::vector<std::string>>& text, const std::vector<std::string>& pattern);

void KMPSearch(const std::string& text, const std::string& sample);
