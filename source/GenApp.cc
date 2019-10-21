/*
 * Zelda II SRAM Editor
 * Copyright (C) 2004-2005,2007-2008 emuWorks
 * http://games.technoplaza.net/
 *
 * This file is part of z2se.
 *
 * z2se is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * z2se is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with z2se; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <wx/xrc/xmlres.h>

#include "GenApp.hh"
#include "view/MainFrame.hh"

using namespace emuWorks;

const wxString *GenApp::APP_NAME =
    new wxString(wxT("z2se"));

const wxString *GenApp::APP_FULL_NAME =
    new wxString(wxT("Zelda II SRAM Editor"));

const wxString *GenApp::APP_VERSION =
    new wxString(wxT("1.1a"));

const wxString *GenApp::APP_COPYRIGHT =
    new wxString(wxT("Copyright (C) 2004-2005,2007-2008 emuWorks"));

const wxString *GenApp::APP_URL =
    new wxString(wxT("http://games.technoplaza.net/"));

// prototype for InitXmlResource function
void InitXmlResource();

bool GenApp::OnInit() {
    // initialize the XRC resources
    wxXmlResource::Get()->InitAllHandlers();
    InitXmlResource();

    MainFrame *frame = new MainFrame;
    frame->Show(true);

    return true;
}

IMPLEMENT_CLASS(GenApp, wxApp)
IMPLEMENT_APP(GenApp)
