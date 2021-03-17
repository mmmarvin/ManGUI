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
#ifndef PFILEHOLDER_H
#define PFILEHOLDER_H

#include <cstdio>
#include <string>

namespace mangui
{
  class PFileHolder
  {
  public:
    PFileHolder(const std::string& filename, const std::string& flags);
    ~PFileHolder();

    void close();

    FILE* get() noexcept;
    const FILE* get() const noexcept;

  private:
    FILE* m_file;
  };
}

#endif // PFILEHOLDER_H
