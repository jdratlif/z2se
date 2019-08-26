/*
 * Copyright (C) 2004 emuWorks
 * http://games.technoplaza.net/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

// $Id: SRAMFile.hh,v 1.2 2004/12/10 10:01:43 technoplaza Exp $

#ifndef _SRAM_FILE_HH
#define _SRAM_FILE_HH

/// The size of the SRAM file
#define SRAM_SIZE 0x2000

/// The starting offset of the games within the SRAM file
#define GAME_OFFSET 0x1402

#include "SaveSlot.hh"

namespace emuWorks {
    /**
     * Class to encapsulate an SRAM file.
     */
    class SRAMFile {
    public:
        /**
         * Constructor for an SRAMFile object.
         *
         * @param filename The SRAM file to use.
         */
        SRAMFile(wxString &filename);
        
        /**
         * Destructor for an SRAMFile object.
         */
        ~SRAMFile();
        
        /**
         * Checks if this SRAM file has been modified.
         *
         * @return true if modified; false otherwise.
         */
        bool isModified();
        
        /**
         * Gets the current game.
         *
         * @return The current game data.
         */
        SaveSlot *getCurrentGame();
        
        /**
         * Sets the current game.
         *
         * @param current The new game.
         *
         * @return true if the current game was changed; false otherwise.
         */
        bool setCurrentGame(unsigned int current);
        
        /**
         * Checks if a particular game is valid.
         *
         * @param game The game to check.
         *
         * @return true if the game is valid; false otherwise.
         */
        bool isValidGame(int game);
        
        /**
         * Saves the SRAM data to the file it was opened from.
         *
         * @return true if the data was saved; false otherwise.
         */
        bool save();
        
        /**
         * Saves the SRAM data to a particular file.
         *
         * @param filename The file to save to.
         *
         * @return true if the data was saved; false otherwise.
         */
        bool save(wxString &filename);
        
    private:
        /**
         * Loads the SRAM data from a file.
         *
         * @param filename The file to load SRAM data from.
         */
        void load(wxString &filename);
    
        wxString *file;
        char *data;
        
        int current;
        SaveSlot *games[3];
    };
}

#endif