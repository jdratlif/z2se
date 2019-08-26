/*
 * Zelda II SRAM Editor
 * Copyright (C) 2004-2005,2007 emuWorks
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

// $Id: SRAMFile.cc,v 1.6 2007/02/25 08:32:40 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <cstring>
#include <fstream>

#include "model/SaveSlot.hh"
#include "model/SRAMFile.hh"

using namespace emuWorks;

SRAMFile::SRAMFile(wxString &filename) {
    current = -1;
    load(filename);
}

SRAMFile::~SRAMFile() {
    delete file;
    delete data;
    delete games[0];
    delete games[1];
    delete games[2];
}

bool SRAMFile::isModified() {
    if (current == -1) {
        return false;
    }
    
    for (int game = 0; game < 3; game++) {
        if (games[game]->isModified()) {
            return true;
        }
    }
    
    return false;
}

SaveSlot *SRAMFile::getCurrentGame() {
    if (current == -1) {
        return 0;
    }
    
    return games[current];
}

bool SRAMFile::setCurrentGame(unsigned int current) {
    if (current > 2) {
        return false;
    }
    
    if (!isValidGame(current)) {
        return false;
    }
    
    this->current = current;
    return true;
}

bool SRAMFile::isValidGame(int game) {
    return games[game]->isValid();
}

bool SRAMFile::save() {
    return save(*file);
}

bool SRAMFile::save(wxString &filename) {
    for (int game = 0; game < 3; game++) {
        if (isValidGame(game)) {
            memcpy((data + GAME_OFFSET + (game * GAME_SIZE)), 
                   games[game]->nvram,
                   GAME_SIZE);
        }
    }
    
    std::ofstream out(filename.mb_str(), std::ios::binary | std::ios::out);
    
    if (!out) {
        wxMessageBox(wxT("Unable to open the SRAM file."),
                     wxT("File Open Error"), wxOK | wxICON_ERROR);
                     
        return false;
    }
    
    out.write(data, SRAM_SIZE);
    
    if (out.rdstate() & std::ios::failbit) {
        wxMessageBox(wxT("Unable to write to the SRAM file."),
                     wxT("File I/O error"), wxOK | wxICON_ERROR);
                     
        out.close();
        return false;
    }
    
    out.close();
    
    games[0]->setModified(false);
    games[1]->setModified(false);
    games[2]->setModified(false);
    
    return true;
}

void SRAMFile::load(wxString &filename) {
    std::ifstream in(filename.mb_str(), std::ios::in | std::ios::binary);
    
    if (!in) {
        wxMessageBox(wxT("Unable to open the SRAM file."),
                     wxT("File Open Error"), wxOK | wxICON_ERROR);
        return;
    }
    
    data = new char[SRAM_SIZE];
    in.read(data, SRAM_SIZE);
    
    if (in.rdstate() & std::ios::failbit) {
        wxMessageBox(wxT("Unable to read the SRAM file."),
                     wxT("File I/O Error"), wxOK | wxICON_ERROR);
        
        in.close();
        delete data;
        
        return;
    }
    
    in.close();
    
    for (int slot = 2; slot >= 0; slot--) {
        games[slot] = new SaveSlot(data + GAME_OFFSET + (slot * GAME_SIZE));
        
        if (games[slot]->isValid()) {
            current = slot;
        }
    }
    
    file = new wxString(filename);
    
    if (current != -1) {
        wxString bakfile = filename + wxT(".bak");
        std::ofstream out(bakfile.mb_str(), std::ios::out | std::ios::binary);
        
        if (out) {
            out.write(data, SRAM_SIZE);
            out.close();
        }
    }
}

