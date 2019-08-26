/*
 * z2se
 * Copyright (C) 2004-2005 emuWorks
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

// $Id: GenApp.cc,v 1.2 2005/08/04 05:23:21 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <iostream>
#include <sys/stat.h>

#include "GenApp.hh"
#include "view/MainFrame.hh"

using namespace emuWorks;

const wxString *GenApp::APP_NAME =
    new wxString(wxT(PACKAGE_NAME));
    
const wxString *GenApp::APP_FULL_NAME =
    new wxString(wxT(PACKAGE_FULL_NAME));

const wxString *GenApp::APP_VERSION =
    new wxString(wxT(PACKAGE_VERSION));

const wxString *GenApp::APP_COPYRIGHT =
    new wxString(wxT("Copyright (C) 2004-2005 emuWorks"));

const wxString *GenApp::APP_URL =
    new wxString(wxT("http://games.technoplaza.net/"));

IMPLEMENT_APP(GenApp)
IMPLEMENT_CLASS(GenApp, wxApp)

bool GenApp::OnInit() {
    wxString *xrcfile;
    
    if (argc == 2) {
        xrcfile = new wxString(argv[1]);
    } else {
        xrcfile = new wxString(XRC_FILE);
    }
    
    struct stat xrcstats;
    
    if (stat(xrcfile->mb_str(), &xrcstats) != 0) {
        std::cerr << "error: unable to locate XRC file " << 
            xrcfile->mb_str() << std::endl;
        return false;
    }
    
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(*xrcfile);
    
    MainFrame *frame = new MainFrame;
    frame->SetTitle(*APP_FULL_NAME + wxT(' ') + *APP_VERSION);
    frame->Show(true);
    SetTopWindow(frame);
    
    return true;
}
