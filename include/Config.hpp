#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(Config,
    CONFIG_VALUE(Permissions, std::vector<std::string>, "Permissions", std::vector<std::string>());
)