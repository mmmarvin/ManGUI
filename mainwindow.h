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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <wx/wx.h>
#include <wx/listctrl.h>

namespace mangui
{
  class MainWindow : public wxFrame
  {
    static constexpr auto SECTION_INDENT = 0;
    static constexpr auto SUBSECTION_INDENT = 50;
    static constexpr auto CONTENT_TEXT_INDENT = 150;

    // Widget IDs
    enum
    {
      MENU_FILE_QUIT,
      MENU_HELP_ABOUT,

      WIDGET_MAN_SEARCH,
      WIDGET_MAN_LIST,
    };

    class PageListPanel : public wxWindow
    {
    public:
      explicit PageListPanel(wxWindow* parent);

    private:
      friend class MainWindow;

      wxListBox* m_pageList;
    };

  public:
    MainWindow();

  private:
    struct ManPage
    {
      std::string name;
      size_t      id;
    };

    void createMenuBar();
    void createWidgets();

    void loadManPages();
    void loadManPagesToList(const std::string& pattern);

//    stroff::Parser        m_parser;
    wxListBox*            m_pageList;
    wxTextCtrl*           m_pageTextArea;
    std::vector<ManPage>  m_manPages;
  };
}

#endif // MAINWINDOW_H
