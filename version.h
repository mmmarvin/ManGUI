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
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 **********/
#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace mangui
{
  static constexpr auto APP_NAME = "ManGUI";
  static constexpr auto APP_VERSION_MAJOR = 0;
  static constexpr auto APP_VERSION_MINOR = 0;
  static constexpr auto APP_VERSION_PATCH = 1;

  std::string getApp();
  std::string getVersion();
}

#endif // VERSION_H
