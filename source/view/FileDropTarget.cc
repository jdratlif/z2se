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

// $Id: FileDropTarget.cc,v 1.7 2008/12/17 06:24:27 jdratlif Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "view/FileDropTarget.hh"
#include "view/MainFrame.hh"

using namespace emuWorks;

bool FileDropTarget::OnDropFiles(wxCoord, wxCoord, const wxArrayString &files) {
    int size = files.GetCount();

    if (size > 0) {
        wxString filename = files[0];
        
        wxString ext = filename.Mid(filename.Length() - 4);
        
        if (ext.CmpNoCase(wxT(".sav")) != 0) {
            wxMessageBox(wxT("Only NES SRAM (*.sav) files can be dropped."),
                         wxT("Error: Invalid File Drop"),
                         wxICON_ERROR | wxOK);
            
            return false;
        }
        
        owner->load(filename);
    }

    return true;
}

