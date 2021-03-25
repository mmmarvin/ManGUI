/**********
 *
 * This file is part of ManGUI.
 * 
 * ManGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ManGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ManGUI.  If not, see <https://www.gnu.org/licenses/>.
 *
 **********/
#include "version.h"

#include <array>

namespace mangui
{
  std::string getApp()
  {
    return APP_NAME;
  }

  std::string getVersion()
  {
    std::array<char, 255> buff;
    sprintf(buff.data(), "%d.%d%d", APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_PATCH);

    return std::string(buff.data());
  }
}
