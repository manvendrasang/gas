#pragma once

#include <string>
#include <vector>

class WaveExporter
{
public:

    bool write(
        const std::string& path,
        const std::vector<float>& samples);
};