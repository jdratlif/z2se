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

#ifndef Z2SE_FILEDROPTARGET_HH_
#define Z2SE_FILEDROPTARGET_HH_

#include <wx/dnd.h>

namespace emuWorks {
    class MainFrame;

    /**
     * Class implementing a wxFileDropTarget for the MainFrame class.
     */
    class FileDropTarget : public wxFileDropTarget {
      private:
        MainFrame *owner;

      public:
        /**
         * Constructor for the FileDropTarget.
         *
         * @param owner The MainFrame associated with this FileDropTarget.
         */
        FileDropTarget(MainFrame *owner) : owner(owner) {}

        /**
         * Virtual method called when files are dropped on this target.
         *
         * @param x The x-coordinate of the drop.
         * @param y The y-coordinate of the drop.
         * @param files The files dropped on this target.
         */
        auto OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &files)
            -> bool override;
    };
} // namespace emuWorks

#endif
