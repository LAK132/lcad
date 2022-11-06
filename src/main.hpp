#ifndef LCAD_MAIN_HPP
#define LCAD_MAIN_HPP

#include "git_hash.hpp"
#include "git_tag.hpp"

#include "lak/compiler.hpp"
#include "lak/macro_utils.hpp"

#define APP_NAME "LCAD " STRINGIFY(LAK_ARCH) " " GIT_TAG "-" GIT_HASH

#endif
