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

#ifndef Z2SE_SRAMFILE_HH_
#define Z2SE_SRAMFILE_HH_

#include <wx/string.h>

/// The size of the SRAM file
#define SRAM_SIZE 0x2000

/// The starting offset of the games within the SRAM file
#define GAME_OFFSET 0x1402

namespace emuWorks {
    class SaveSlot;

    /**
     * Class to encapsulate an SRAM file.
     */
    class SRAMFile {
      private:
        wxString *file;
        std::array<SaveSlot *, 3> games;
        int current;
        char *data;

        /**
         * Loads the SRAM data from a file.
         *
         * @param filename The file to load SRAM data from.
         */
        void load(wxString &filename);

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
        auto isModified() -> bool;

        /**
         * Gets the current game.
         *
         * @return The current game data.
         */
        auto getCurrentGame() -> SaveSlot *;

        /**
         * Sets the current game.
         *
         * @param current The new game.
         *
         * @return true if the current game was changed; false otherwise.
         */
        auto setCurrentGame(unsigned int current) -> bool;

        /**
         * Checks if a particular game is valid.
         *
         * @param game The game to check.
         *
         * @return true if the game is valid; false otherwise.
         */
        auto isValidGame(int game) -> bool;

        /**
         * Saves the SRAM data to the file it was opened from.
         *
         * @return true if the data was saved; false otherwise.
         */
        auto save() -> bool;

        /**
         * Saves the SRAM data to a particular file.
         *
         * @param filename The file to save to.
         *
         * @return true if the data was saved; false otherwise.
         */
        auto save(wxString &filename) -> bool;
    };
} // namespace emuWorks

#endif
