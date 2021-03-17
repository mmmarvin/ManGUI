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
#include "mainwindow.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <wx/aboutdlg.h>
#include <wx/splitter.h>
#include <fnmatch.h>
#include "pfileholder.h"
#include "man.h"
#include "version.h"

namespace mangui
{
  MainWindow::PageListPanel::PageListPanel(wxWindow* parent) :
    wxWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(150, 1))
  {
    auto* layout = new wxBoxSizer(wxVERTICAL);

    auto* search_box = new wxTextCtrl(this, WIDGET_MAN_SEARCH);
    m_pageList = new wxListBox(this, WIDGET_MAN_LIST, wxDefaultPosition, wxDefaultSize);

    layout->Add(search_box, 0, wxEXPAND);
    layout->Add(m_pageList, 1, wxEXPAND);

    this->SetSizer(layout);
  }

  MainWindow::MainWindow() :
    wxFrame(nullptr, wxID_ANY, getApp())
  {
    this->SetMinSize(wxSize(800, 600));

    createMenuBar();
    createWidgets();

    loadManPages();
  }

  void MainWindow::createMenuBar()
  {
    auto* menu_bar = new wxMenuBar;
    auto* file_menu = new wxMenu;
    file_menu->Append(MENU_FILE_QUIT,
                      wxT("Quit"));

    auto* help_menu = new wxMenu;
    help_menu->Append(MENU_HELP_ABOUT,
                      wxT("About"));

    menu_bar->Append(file_menu, wxT("&File"));
    menu_bar->Append(help_menu, wxT("&Help"));
    this->SetMenuBar(menu_bar);

    Bind(wxEVT_MENU, [this](wxCommandEvent&) { this->Close(); }, MENU_FILE_QUIT);
    Bind(wxEVT_MENU, [this](wxCommandEvent&) {
      wxAboutDialogInfo info;
      info.SetName("ManGUI");
      info.SetVersion((getApp() + std::string("v.") + getVersion()).c_str());
      info.SetCopyright("Copyright (c) 2020-2021");
      info.AddDeveloper("Marvin Manese");

      wxAboutBox(info);
    }, MENU_HELP_ABOUT);
  }

  void MainWindow::createWidgets()
  {
    auto* splitter = new wxSplitterWindow(this);
    auto page_list = new PageListPanel(splitter);
    m_pageList = page_list->m_pageList;

    wxTextAttr attr;
    attr.SetLeftIndent(200);

    m_pageTextArea = new wxTextCtrl(splitter,
                                    wxID_ANY,
                                    "",
                                    wxDefaultPosition,
                                    wxDefaultSize,
                                    wxTE_MULTILINE | wxTE_READONLY);
    m_pageTextArea->SetDefaultStyle(attr);
    splitter->SplitVertically(page_list, m_pageTextArea);
  }

  void MainWindow::loadManPages()
  {
    // get man pages
    for(const auto& fode : std::filesystem::directory_iterator("/usr/share/man")) {
      const auto& fop = fode.path();
      if(!fnmatch("man*", fop.filename().string().c_str(),  FNM_PATHNAME)) {
        for(const auto& fide : std::filesystem::recursive_directory_iterator(fop.string())) {
          m_manPages.push_back({ getPageName(fide.path().string()), 0 });
        }
      }
    }

    // sort man pages list
    std::sort(m_manPages.begin(),
              m_manPages.end(),
              [](const ManPage& l, const ManPage& r) {
      return l.name < r.name;
    });

    // update list index
    for(size_t i = 0, isize = m_manPages.size(); i < isize; ++i) {
      auto& man_page = m_manPages[i];
      man_page.id = i;
    }

    // load pages to list
    loadManPagesToList("");

    Bind(wxEVT_LISTBOX_DCLICK, [this](wxCommandEvent& e) {
      const auto& name = m_manPages[*static_cast<size_t*>(e.GetClientData())].name;

      PFileHolder pfile("man " + name, "r");
      if(pfile.get()) {
        std::vector<std::string> lines;
        std::array<char, 255> buffer;
        while(fgets(buffer.data(), buffer.size(), pfile.get()) != nullptr) {
          lines.push_back(std::string(buffer.data(),
                                      buffer.data() + strnlen(buffer.data(), buffer.size()))) ;
          for(auto& c : lines.back()) {
            if(c < 0) {
              c = '-';
            }
          }
        }
        pfile.close();

        m_pageTextArea->Clear();
        for(const auto& line : lines) {
          if(!line.empty()) {
            m_pageTextArea->AppendText(wxString(line.c_str(), line.size()));
            m_pageTextArea->AppendText("\n");
          }
        }
      }
    }, WIDGET_MAN_LIST);

    Bind(wxEVT_COMMAND_TEXT_UPDATED, [this](wxCommandEvent& e) {
      if(!e.GetString().empty()) {
        loadManPagesToList("*" + std::string(e.GetString().c_str()) + "*");
      } else {
        loadManPagesToList("");
      }
    }, WIDGET_MAN_SEARCH);
  }

  void MainWindow::loadManPagesToList(const std::string& pattern)
  {
    m_pageList->Clear();
    if(pattern.empty()) {
      for(size_t i = 0, isize = m_manPages.size(); i < isize; ++i) {
        auto& man_page = m_manPages[i];
        m_pageList->Insert(man_page.name.c_str(),
                           i,
                           static_cast<void*>(&man_page.id));
      }
    } else {
      size_t list_index = 0;
      for(size_t i = 0, isize = m_manPages.size(); i < isize; ++i) {
        auto& man_page = m_manPages[i];
        auto page_name = man_page.name;
        if(!fnmatch(pattern.c_str(), page_name.c_str(), FNM_FILE_NAME)) {
          m_pageList->Insert(page_name.c_str(),
                             list_index++,
                             static_cast<void*>(&man_page.id));
        }
      }
    }
  }
}
