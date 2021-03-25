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
#include "pfileholder.h"

namespace mangui
{
  PFileHolder::PFileHolder(const std::string& filename, const std::string& flags) :
    m_file(nullptr)
  {
    m_file = popen(filename.c_str(), flags.c_str());
  }

  PFileHolder::~PFileHolder()
  {
    close();
  }

  void PFileHolder::close()
  {
    if(m_file) {
      pclose(m_file);
      m_file = nullptr;
    }
  }

  FILE* PFileHolder::get() noexcept
  {
    return m_file;
  }

  const FILE* PFileHolder::get() const noexcept
  {
    return m_file;
  }
}
