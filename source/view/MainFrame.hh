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

// $Id: MainFrame.hh,v 1.8 2004/12/10 16:10:32 technoplaza Exp $

#ifndef _MAIN_FRAME_HH
#define _MAIN_FRAME_HH

#include "wx/xrc/xmlres.h"
#include "wx/frame.h"
#include "wx/statusbr.h"

#include "model/SRAMFile.hh"
#include "FileDropTarget.hh"

namespace emuWorks {
    class MainFrame : public wxFrame {
    public:
        MainFrame();    
        void CreateControls();
        
        friend class FileDropTarget;
    
    private:
        DECLARE_DYNAMIC_CLASS(MainFrame)
        DECLARE_EVENT_TABLE()
        
        /**
         * Checks if we have an opem SRAM file.
         */
        bool isOpen() const { return open; }
        
        /**
         * Sets whether we have an open SRAM file or not.
         *
         * @param open true if open; false otherwise.
         */
        void setOpen(bool open);
        
        /**
         * Closes the current SRAM file.
         *
         * @return true if closed; false otherwise.
         */
        bool close();
        
        /**
         * Loads game data into the controls.
         *
         * @param game Which game to load.
         */
        void loadGameData(int game);
        
        /**
         * Loads an SRAM file for editing.
         *
         * @param filename The file to load.
         */
        void load(wxString &filename);
        
        /**
         * Callback triggered when open is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileOpen(wxCommandEvent &event);
        
        /**
         * Callback triggered when close is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileClose(wxCommandEvent &event);
        
        /**
         * Callback triggered when save is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileSave(wxCommandEvent &event);
        
        /**
         * Callback triggered when save as is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileSaveAs(wxCommandEvent &event);
        
        /**
         * Callback triggered when exit is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileExit(wxCommandEvent &event);
        
        /**
         * Callback triggered when the window is being closed.
         *
         * @param event The associated command event.
         */
        void windowClosing(wxCloseEvent &event);
        
        /**
         * Callback triggered when the current game is changed.
         *
         * @param event The associated command event.
         */
        void gameChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when something on the have menu is selected.
         *
         * @param event The associated command event.
         */
        void multiChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when about is selected from the help menu.
         *
         * @param event The associated command event.
         */
        void helpAbout(wxCommandEvent &event);
        
        /**
         * Callback triggered when the name is changed.
         *
         * @param event The associated command event.
         */
        void nameChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when the play count is changed.
         *
         * @param event The associated scroll event.
         */
        void playCountChange(wxScrollEvent &event);
        
        /**
         * Callback triggered when the triforce is changed.
         *
         * @param event The associated command event.
         */
        void triforceChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when an experience level is changed.
         *
         * @param event The associated scroll event.
         */
        void levelChange(wxScrollEvent &event);
        
        /**
         * Callback triggered when a container value is changed.
         *
         * @param event The associated scroll event.
         */
        void containerChange(wxScrollEvent &event);
        
        /**
         * Callback triggered when a technique is changed.
         *
         * @param event The associated command event.
         */
        void techniqueChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when a spell is changed.
         *
         * @param event The associated command event.
         */
        void spellChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when an item is changed.
         *
         * @param event The associated command event.
         */
        void itemChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when a palace seal is changed.
         *
         * @param event The associated command event.
         */
        void sealChange(wxCommandEvent &event);
        
        /**
         * Callback triggered when the keys are changed.
         *
         * @param event The associated scroll event.
         */
        void keyChange(wxScrollEvent &event);
        
        bool open;
        
        SRAMFile *sram;
        
        wxMenuItem *fileCloseItem;
        wxMenuItem *fileSaveItem;
        wxMenuItem *fileSaveAsItem;
        wxMenuItem *gameItems[3];
        
        wxPanel *panel;

        wxTextCtrl *nameText;
        wxSlider *playCountSlider;
        wxCheckBox *triforceCheck;
        
        wxSlider *swordLevelSlider;
        wxSlider *magicLevelSlider;
        wxSlider *lifeLevelSlider;
        
        wxSlider *magicContainerSlider;
        wxSlider *lifeContainerSlider;
        
        wxCheckBox *downwardThrustCheck;
        wxCheckBox *upwardThrustCheck;
        
        wxCheckBox *shieldCheck;
        wxCheckBox *jumpCheck;
        wxCheckBox *lifeCheck;
        wxCheckBox *fairyCheck;
        wxCheckBox *fireCheck;
        wxCheckBox *reflectCheck;
        wxCheckBox *spellCheck;
        wxCheckBox *thunderCheck;
        
        wxCheckBox *candleCheck;
        wxCheckBox *gloveCheck;
        wxCheckBox *raftCheck;
        wxCheckBox *bootsCheck;
        wxCheckBox *crossCheck;
        wxCheckBox *fluteCheck;
        wxCheckBox *magicKeyCheck;
        wxCheckBox *hammerCheck;
        
        wxCheckBox *palaceCheck[6];
        wxSlider *keySlider;
        
        /**
         * XPM icon used for the Frame icon.
         */
        static const char *ICON[];
    };
}

#endif
