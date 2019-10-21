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
#include "model/SaveSlot.hh"
#include "model/SRAMFile.hh"
#include "res/icon32x32.xpm"
#include "view/FileDropTarget.hh"
#include "view/MainFrame.hh"

using namespace emuWorks;

MainFrame::MainFrame() {
    SetParent(NULL);
    CreateControls();
    GetSizer()->SetSizeHints(this);
    Centre();

    panel->Show(false);

    SetDropTarget(new FileDropTarget(this));
}

void MainFrame::CreateControls() {
    wxXmlResource::Get()->LoadFrame(this, GetParent(), wxT("IDF_FRAME"));
    SetIcon(icon32x32_xpm);

    wxMenuBar *menubar = GetMenuBar();

    fileCloseItem = menubar->FindItem(wxID_CLOSE);
    fileSaveItem = menubar->FindItem(wxID_SAVE);
    fileSaveAsItem = menubar->FindItem(wxID_SAVEAS);

    gameItems[0] = menubar->FindItem(XRCID("IDM_GAME_ONE"));
    gameItems[0]->Enable(false);

    gameItems[1] = menubar->FindItem(XRCID("IDM_GAME_TWO"));
    gameItems[1]->Enable(false);

    gameItems[2] = menubar->FindItem(XRCID("IDM_GAME_THREE"));
    gameItems[2]->Enable(false);

    panel = XRCCTRL(*this, "IDP_PANEL", wxPanel);

    wxArrayString letters;
    letters.Add(wxT("A")); letters.Add(wxT("B")); letters.Add(wxT("C"));
    letters.Add(wxT("D")); letters.Add(wxT("E")); letters.Add(wxT("F"));
    letters.Add(wxT("G")); letters.Add(wxT("H")); letters.Add(wxT("I"));
    letters.Add(wxT("J")); letters.Add(wxT("K")); letters.Add(wxT("L"));
    letters.Add(wxT("M")); letters.Add(wxT("N")); letters.Add(wxT("O"));
    letters.Add(wxT("P")); letters.Add(wxT("Q")); letters.Add(wxT("R"));
    letters.Add(wxT("S")); letters.Add(wxT("T")); letters.Add(wxT("U"));
    letters.Add(wxT("V")); letters.Add(wxT("W")); letters.Add(wxT("X"));
    letters.Add(wxT("Y")); letters.Add(wxT("Z")); letters.Add(wxT("0"));
    letters.Add(wxT("1")); letters.Add(wxT("2")); letters.Add(wxT("3"));
    letters.Add(wxT("4")); letters.Add(wxT("5")); letters.Add(wxT("6"));
    letters.Add(wxT("7")); letters.Add(wxT("8")); letters.Add(wxT("9"));
    letters.Add(wxT(" "));

    wxTextValidator nameValidator(wxFILTER_INCLUDE_CHAR_LIST);
    nameValidator.SetIncludes(letters);

    nameText = XRCCTRL(*this, "IDT_NAME", wxTextCtrl);
    nameText->SetValidator(nameValidator);
    nameText->SetMaxLength(8);

    playCountSlider = XRCCTRL(*this, "IDS_PLAY_COUNT", wxSlider);
    triforceCheck = XRCCTRL(*this, "IDC_TRIFORCE", wxCheckBox);

    swordLevelSlider = XRCCTRL(*this, "IDS_SWORD_LEVEL", wxSlider);
    magicLevelSlider = XRCCTRL(*this, "IDS_MAGIC_LEVEL", wxSlider);
    lifeLevelSlider = XRCCTRL(*this, "IDS_LIFE_LEVEL", wxSlider);

    magicContainerSlider = XRCCTRL(*this, "IDS_MAGIC_CONTAINER", wxSlider);
    lifeContainerSlider = XRCCTRL(*this, "IDS_LIFE_CONTAINER", wxSlider);

    downwardThrustCheck = XRCCTRL(*this, "IDC_DOWNWARD_THRUST", wxCheckBox);
    upwardThrustCheck = XRCCTRL(*this, "IDC_UPWARD_THRUST", wxCheckBox);

    shieldCheck = XRCCTRL(*this, "IDC_SHIELD", wxCheckBox);
    jumpCheck = XRCCTRL(*this, "IDC_JUMP", wxCheckBox);
    lifeCheck = XRCCTRL(*this, "IDC_LIFE", wxCheckBox);
    fairyCheck = XRCCTRL(*this, "IDC_FAIRY", wxCheckBox);
    fireCheck = XRCCTRL(*this, "IDC_FIRE", wxCheckBox);
    reflectCheck = XRCCTRL(*this, "IDC_REFLECT", wxCheckBox);
    spellCheck = XRCCTRL(*this, "IDC_SPELL", wxCheckBox);
    thunderCheck = XRCCTRL(*this, "IDC_THUNDER", wxCheckBox);

    candleCheck = XRCCTRL(*this, "IDC_CANDLE", wxCheckBox);
    gloveCheck = XRCCTRL(*this, "IDC_GLOVE", wxCheckBox);
    raftCheck = XRCCTRL(*this, "IDC_RAFT", wxCheckBox);
    bootsCheck = XRCCTRL(*this, "IDC_BOOTS", wxCheckBox);
    crossCheck = XRCCTRL(*this, "IDC_CROSS", wxCheckBox);
    fluteCheck = XRCCTRL(*this, "IDC_FLUTE", wxCheckBox);
    magicKeyCheck = XRCCTRL(*this, "IDC_MAGIC_KEY", wxCheckBox);
    hammerCheck = XRCCTRL(*this, "IDC_HAMMER", wxCheckBox);

    palaceCheck[0] = XRCCTRL(*this, "IDC_PARAPA", wxCheckBox);
    palaceCheck[1] = XRCCTRL(*this, "IDC_MIDORO", wxCheckBox);
    palaceCheck[2] = XRCCTRL(*this, "IDC_ISLAND", wxCheckBox);
    palaceCheck[3] = XRCCTRL(*this, "IDC_MAZE", wxCheckBox);
    palaceCheck[4] = XRCCTRL(*this, "IDC_SEA", wxCheckBox);
    palaceCheck[5] = XRCCTRL(*this, "IDC_THREE_EYE_ROCK", wxCheckBox);

    keySlider = XRCCTRL(*this, "IDS_KEY", wxSlider);

    setOpen(false);
}

void MainFrame::setOpen(bool open) {
    this->open = open;

    fileCloseItem->Enable(open);
    fileSaveItem->Enable(open);
    fileSaveAsItem->Enable(open);

    GetMenuBar()->EnableTop(2, open);
}

bool MainFrame::close() {
    if (!isOpen()) {
        return true;
    }

    if (sram->isModified()) {
        int choice = wxMessageBox(wxT("Save Game File Before Closing?"),
                                  wxT("Warning: Unsaved Changes"),
                                  wxYES_NO | wxCANCEL | wxICON_QUESTION);

        if (choice == wxYES) {
            if (!sram->save()) {
                return false;
            }
        } else if (choice == wxCANCEL) {
            return false;
        }
    }

    delete sram;

    for (int game = 0; game < 3; game++) {
        gameItems[game]->Enable(false);
    }

    panel->Show(false);
    setOpen(false);

    return true;
}

void MainFrame::loadGameData(int game) {
    sram->setCurrentGame(game);
    SaveSlot *slot = sram->getCurrentGame();

    nameText->SetValue(slot->getName());
    playCountSlider->SetValue(slot->getPlayCount());
    triforceCheck->SetValue(slot->hasTriforce());

    swordLevelSlider->SetValue(slot->getLevel(SWORDLEVEL));
    magicLevelSlider->SetValue(slot->getLevel(MAGICLEVEL));
    lifeLevelSlider->SetValue(slot->getLevel(LIFELEVEL));

    magicContainerSlider->SetValue(slot->getContainers(MAGICCONTAINER));
    lifeContainerSlider->SetValue(slot->getContainers(LIFECONTAINER));

    downwardThrustCheck->SetValue(slot->hasTechnique(DOWNWARDTHRUST));
    upwardThrustCheck->SetValue(slot->hasTechnique(UPWARDTHRUST));

    shieldCheck->SetValue(slot->hasSpell(SHIELD));
    jumpCheck->SetValue(slot->hasSpell(JUMP));
    lifeCheck->SetValue(slot->hasSpell(LIFE));
    fairyCheck->SetValue(slot->hasSpell(FAIRY));
    fireCheck->SetValue(slot->hasSpell(FIRE));
    reflectCheck->SetValue(slot->hasSpell(REFLECT));
    spellCheck->SetValue(slot->hasSpell(SPELL));
    thunderCheck->SetValue(slot->hasSpell(THUNDER));

    candleCheck->SetValue(slot->hasItem(CANDLE));
    gloveCheck->SetValue(slot->hasItem(GLOVE));
    raftCheck->SetValue(slot->hasItem(RAFT));
    bootsCheck->SetValue(slot->hasItem(BOOTS));
    crossCheck->SetValue(slot->hasItem(CROSS));
    fluteCheck->SetValue(slot->hasItem(FLUTE));
    magicKeyCheck->SetValue(slot->hasItem(MAGICKEY));
    hammerCheck->SetValue(slot->hasItem(HAMMER));

    for (int palace = 0; palace < 6; palace++) {
        palaceCheck[palace]->SetValue(slot->hasSeal(palace));
    }

    keySlider->SetValue(slot->getKeys());

    panel->Show(true);
}

void MainFrame::load(wxString &filename) {
    if (!close()) {
        return;
    }

    sram = new SRAMFile(filename);

    int first = -1;

    for (int game = 2; game >= 0; game--) {
        if (sram->isValidGame(game)) {
            gameItems[game]->Enable(true);
            first = game;
        }
    }

    if (first == -1) {
        delete sram;

        wxMessageBox(wxT("No game data is in the file you loaded."),
                     wxT("Error: No Data Found"), wxOK | wxICON_ERROR);
    } else {
        loadGameData(first);

        if (first != 0) {
            gameItems[first]->Check(true);
        }

        setOpen(true);
    }
}

void MainFrame::fileOpen(wxCommandEvent &) {
    static wxFileDialog *dlg = new wxFileDialog(this,
        wxT("Choose a .SAV File"), wxT(""), wxT(""),
        wxT("NES SRAM File (*.sav)|*.sav"), (wxFD_OPEN | wxFD_CHANGE_DIR));

    int value = dlg->ShowModal();

    if (value == wxID_OK) {
        wxString filename = dlg->GetPath();
        load(filename);
    }
}

void MainFrame::fileClose(wxCommandEvent &) {
    close();
}

void MainFrame::fileSave(wxCommandEvent &) {
    sram->save();
}

void MainFrame::fileSaveAs(wxCommandEvent &) {
    static wxFileDialog *dlg = new wxFileDialog(this,
        wxT("Choose a .SAV File"), wxT(""), wxT(""),
        wxT("NES SRAM File (*.sav)|*.sav"), (wxFD_SAVE | wxFD_CHANGE_DIR));

    int value = dlg->ShowModal();

    if (value == wxID_OK) {
        wxString filename = dlg->GetPath();
        sram->save(filename);
    }
}

void MainFrame::fileExit(wxCommandEvent &) {
    if (close()) {
        Close(true);
    }
}

void MainFrame::windowClosing(wxCloseEvent &event) {
    if (event.CanVeto()) {
        if (!close()) {
            event.Veto();
            return;
        }
    }

    Destroy();
}

void MainFrame::gameChange(wxCommandEvent &event) {
    int id = event.GetId();

    if (id == XRCID("IDM_GAME_ONE")) {
        loadGameData(0);
    } else if (id == XRCID("IDM_GAME_TWO")) {
        loadGameData(1);
    } else if (id == XRCID("IDM_GAME_THREE")) {
        loadGameData(2);
    }
}

void MainFrame::multiChange(wxCommandEvent &event) {
    SaveSlot *game = sram->getCurrentGame();
    int id = event.GetId();

    if (id == XRCID("IDM_HAVE_ALL_LEVELS")) {
        swordLevelSlider->SetValue(8);
        game->setLevel(SWORDLEVEL, 8);

        magicLevelSlider->SetValue(8);
        game->setLevel(MAGICLEVEL, 8);

        lifeLevelSlider->SetValue(8);
        game->setLevel(LIFELEVEL, 8);
    } else if (id == XRCID("IDM_HAVE_ALL_CONTAINERS")) {
        magicContainerSlider->SetValue(8);
        game->setContainers(MAGICCONTAINER, 8);

        lifeContainerSlider->SetValue(8);
        game->setContainers(LIFECONTAINER, 8);
    } else if (id == XRCID("IDM_HAVE_ALL_TECHNIQUES")) {
        downwardThrustCheck->SetValue(true);
        game->setTechnique(DOWNWARDTHRUST, true);

        upwardThrustCheck->SetValue(true);
        game->setTechnique(UPWARDTHRUST, true);
    } else if (id == XRCID("IDM_HAVE_ALL_SPELLS")) {
        shieldCheck->SetValue(true);
        game->setSpell(SHIELD, true);

        jumpCheck->SetValue(true);
        game->setSpell(JUMP, true);

        lifeCheck->SetValue(true);
        game->setSpell(LIFE, true);

        fairyCheck->SetValue(true);
        game->setSpell(FAIRY, true);

        fireCheck->SetValue(true);
        game->setSpell(FIRE, true);

        reflectCheck->SetValue(true);
        game->setSpell(REFLECT, true);

        spellCheck->SetValue(true);
        game->setSpell(SPELL, true);

        thunderCheck->SetValue(true);
        game->setSpell(THUNDER, true);
    } else if (id == XRCID("IDM_HAVE_ALL_ITEMS")) {
        candleCheck->SetValue(true);
        game->setItem(CANDLE, true);

        gloveCheck->SetValue(true);
        game->setItem(GLOVE, true);

        raftCheck->SetValue(true);
        game->setItem(RAFT, true);

        bootsCheck->SetValue(true);
        game->setItem(BOOTS, true);

        crossCheck->SetValue(true);
        game->setItem(CROSS, true);

        fluteCheck->SetValue(true);
        game->setItem(FLUTE, true);

        magicKeyCheck->SetValue(true);
        game->setItem(MAGICKEY, true);

        hammerCheck->SetValue(true);
        game->setItem(HAMMER, true);
    } else if (id == XRCID("IDM_HAVE_ALL_SEALS")) {
        palaceCheck[0]->SetValue(true);
        game->setSeal(0, true);

        palaceCheck[1]->SetValue(true);
        game->setSeal(1, true);

        palaceCheck[2]->SetValue(true);
        game->setSeal(2, true);

        palaceCheck[3]->SetValue(true);
        game->setSeal(3, true);

        palaceCheck[4]->SetValue(true);
        game->setSeal(4, true);

        palaceCheck[5]->SetValue(true);
        game->setSeal(5, true);
    } else if (id == XRCID("IDM_HAVE_ALL_KEYS")) {
        keySlider->SetValue(9);
        game->setKeys(9);
    } else if (id == XRCID("IDM_HAVE_NONE_LEVELS")) {
        swordLevelSlider->SetValue(1);
        game->setLevel(SWORDLEVEL, 1);

        magicLevelSlider->SetValue(1);
        game->setLevel(MAGICLEVEL, 1);

        lifeLevelSlider->SetValue(1);
        game->setLevel(LIFELEVEL, 1);
    } else if (id == XRCID("IDM_HAVE_NONE_CONTAINERS")) {
        magicContainerSlider->SetValue(4);
        game->setContainers(MAGICCONTAINER, 4);

        lifeContainerSlider->SetValue(4);
        game->setContainers(LIFECONTAINER, 4);
    } else if (id == XRCID("IDM_HAVE_NONE_TECHNIQUES")) {
        downwardThrustCheck->SetValue(false);
        game->setTechnique(DOWNWARDTHRUST, false);

        upwardThrustCheck->SetValue(false);
        game->setTechnique(UPWARDTHRUST, false);
    } else if (id == XRCID("IDM_HAVE_NONE_SPELLS")) {
        shieldCheck->SetValue(false);
        game->setSpell(SHIELD, false);

        jumpCheck->SetValue(false);
        game->setSpell(JUMP, false);

        lifeCheck->SetValue(false);
        game->setSpell(LIFE, false);

        fairyCheck->SetValue(false);
        game->setSpell(FAIRY, false);

        fireCheck->SetValue(false);
        game->setSpell(FIRE, false);

        reflectCheck->SetValue(false);
        game->setSpell(REFLECT, false);

        spellCheck->SetValue(false);
        game->setSpell(SPELL, false);

        thunderCheck->SetValue(false);
        game->setSpell(THUNDER, false);
    } else if (id == XRCID("IDM_HAVE_NONE_ITEMS")) {
        candleCheck->SetValue(false);
        game->setItem(CANDLE, false);

        gloveCheck->SetValue(false);
        game->setItem(GLOVE, false);

        raftCheck->SetValue(false);
        game->setItem(RAFT, false);

        bootsCheck->SetValue(false);
        game->setItem(BOOTS, false);

        crossCheck->SetValue(false);
        game->setItem(CROSS, false);

        fluteCheck->SetValue(false);
        game->setItem(FLUTE, false);

        magicKeyCheck->SetValue(false);
        game->setItem(MAGICKEY, false);

        hammerCheck->SetValue(false);
        game->setItem(HAMMER, false);
    } else if (id == XRCID("IDM_HAVE_NONE_SEALS")) {
        palaceCheck[0]->SetValue(false);
        game->setSeal(0, false);

        palaceCheck[1]->SetValue(false);
        game->setSeal(1, false);

        palaceCheck[2]->SetValue(false);
        game->setSeal(2, false);

        palaceCheck[3]->SetValue(false);
        game->setSeal(3, false);

        palaceCheck[4]->SetValue(false);
        game->setSeal(4, false);

        palaceCheck[5]->SetValue(false);
        game->setSeal(5, false);
    } else if (id == XRCID("IDM_HAVE_NONE_KEYS")) {
        keySlider->SetValue(0);
        game->setKeys(0);
    }
}

void MainFrame::helpAbout(wxCommandEvent &) {
    wxString msg = wxString(*GenApp::APP_FULL_NAME + wxT(' ') +
                            *GenApp::APP_VERSION + wxT('\n') +
                            *GenApp::APP_COPYRIGHT + wxT('\n') +
                            *GenApp::APP_URL);
    wxString title = wxString(wxT("About ") +
                              *GenApp::APP_FULL_NAME +
                              wxT("..."));

    wxMessageBox(msg, title, wxOK | wxICON_INFORMATION, this);
}

void MainFrame::nameChange(wxCommandEvent &) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxString name = nameText->GetValue();
    game->setName(name);
}

void MainFrame::playCountChange(wxScrollEvent &) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    game->setPlayCount(playCountSlider->GetValue());
}

void MainFrame::triforceChange(wxCommandEvent &) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    game->setTriforce(triforceCheck->IsChecked());
}

void MainFrame::levelChange(wxScrollEvent &event) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxSlider *ctrl = (wxSlider *)event.GetEventObject();

    int level = SWORDLEVEL;

    if (ctrl == magicLevelSlider) {
        level = MAGICLEVEL;
    } else if (ctrl == lifeLevelSlider) {
        level = LIFELEVEL;
    }

    game->setLevel(level, ctrl->GetValue());
}

void MainFrame::containerChange(wxScrollEvent &event) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxSlider *ctrl = (wxSlider *)event.GetEventObject();

    int container = ((ctrl == magicContainerSlider) ?
                        MAGICCONTAINER : LIFECONTAINER);

    game->setContainers(container, ctrl->GetValue());
}

void MainFrame::techniqueChange(wxCommandEvent &event) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();

    int technique = ((ctrl == downwardThrustCheck) ?
                        DOWNWARDTHRUST : UPWARDTHRUST);

    game->setTechnique(technique, ctrl->IsChecked());
}

void MainFrame::spellChange(wxCommandEvent &event) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();

    int spell = SHIELD;

    if (ctrl == jumpCheck) {
        spell = JUMP;
    } else if (ctrl == lifeCheck) {
        spell = LIFE;
    } else if (ctrl == fairyCheck) {
        spell = FAIRY;
    } else if (ctrl == fireCheck) {
        spell = FIRE;
    } else if (ctrl == reflectCheck) {
        spell = REFLECT;
    } else if (ctrl == spellCheck) {
        spell = SPELL;
    } else if (ctrl == thunderCheck) {
        spell = THUNDER;
    }

    game->setSpell(spell, ctrl->IsChecked());
}

void MainFrame::itemChange(wxCommandEvent &event) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();

    int item = CANDLE;

    if (ctrl == gloveCheck) {
        item = GLOVE;
    } else if (ctrl == raftCheck) {
        item = RAFT;
    } else if (ctrl == bootsCheck) {
        item = BOOTS;
    } else if (ctrl == crossCheck) {
        item = CROSS;
    } else if (ctrl == fluteCheck) {
        item = FLUTE;
    } else if (ctrl == magicKeyCheck) {
        item = MAGICKEY;
    } else if (ctrl == hammerCheck) {
        item = HAMMER;
    }

    game->setItem(item, ctrl->IsChecked());
}

void MainFrame::sealChange(wxCommandEvent &event) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();
    int palace;

    for (palace = 0; palace < 6; palace++) {
        if (palaceCheck[palace] == ctrl) {
            break;
        }
    }

    game->setSeal(palace, ctrl->IsChecked());
}

void MainFrame::keyChange(wxScrollEvent &) {
    if (!isOpen()) {
        return;
    }

    SaveSlot *game = sram->getCurrentGame();
    game->setKeys(keySlider->GetValue());
}

IMPLEMENT_DYNAMIC_CLASS(MainFrame, wxFrame)

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::windowClosing)

    EVT_MENU(wxID_OPEN, MainFrame::fileOpen)
    EVT_MENU(wxID_CLOSE, MainFrame::fileClose)
    EVT_MENU(wxID_SAVE, MainFrame::fileSave)
    EVT_MENU(wxID_SAVEAS, MainFrame::fileSaveAs)
    EVT_MENU(wxID_EXIT, MainFrame::fileExit)

    EVT_MENU(XRCID("IDM_GAME_ONE"), MainFrame::gameChange)
    EVT_MENU(XRCID("IDM_GAME_TWO"), MainFrame::gameChange)
    EVT_MENU(XRCID("IDM_GAME_THREE"), MainFrame::gameChange)

    EVT_MENU(XRCID("IDM_HAVE_ALL_LEVELS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_ALL_CONTAINERS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_ALL_TECHNIQUES"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_ALL_SPELLS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_ALL_ITEMS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_ALL_SEALS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_ALL_KEYS"), MainFrame::multiChange)

    EVT_MENU(XRCID("IDM_HAVE_NONE_LEVELS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_NONE_CONTAINERS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_NONE_TECHNIQUES"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_NONE_SPELLS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_NONE_ITEMS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_NONE_SEALS"), MainFrame::multiChange)
    EVT_MENU(XRCID("IDM_HAVE_NONE_KEYS"), MainFrame::multiChange)

    EVT_MENU(wxID_ABOUT, MainFrame::helpAbout)

    EVT_TEXT(XRCID("IDT_NAME"), MainFrame::nameChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_PLAY_COUNT"), MainFrame::playCountChange)
    EVT_CHECKBOX(XRCID("IDC_TRIFORCE"), MainFrame::triforceChange)

    EVT_COMMAND_SCROLL(XRCID("IDS_SWORD_LEVEL"), MainFrame::levelChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_MAGIC_LEVEL"), MainFrame::levelChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_LIFE_LEVEL"), MainFrame::levelChange)

    EVT_COMMAND_SCROLL(XRCID("IDS_MAGIC_CONTAINER"), MainFrame::containerChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_LIFE_CONTAINER"), MainFrame::containerChange)

    EVT_CHECKBOX(XRCID("IDC_DOWNWARD_THRUST"), MainFrame::techniqueChange)
    EVT_CHECKBOX(XRCID("IDC_UPWARD_THRUST"), MainFrame::techniqueChange)

    EVT_CHECKBOX(XRCID("IDC_SHIELD"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_JUMP"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_LIFE"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_FAIRY"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_FIRE"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_REFLECT"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_SPELL"), MainFrame::spellChange)
    EVT_CHECKBOX(XRCID("IDC_THUNDER"), MainFrame::spellChange)

    EVT_CHECKBOX(XRCID("IDC_CANDLE"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_GLOVE"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_RAFT"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_BOOTS"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_CROSS"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_FLUTE"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_MAGIC_KEY"), MainFrame::itemChange)
    EVT_CHECKBOX(XRCID("IDC_HAMMER"), MainFrame::itemChange)

    EVT_CHECKBOX(XRCID("IDC_PARAPA"), MainFrame::sealChange)
    EVT_CHECKBOX(XRCID("IDC_MIDORO"), MainFrame::sealChange)
    EVT_CHECKBOX(XRCID("IDC_ISLAND"), MainFrame::sealChange)
    EVT_CHECKBOX(XRCID("IDC_MAZE"), MainFrame::sealChange)
    EVT_CHECKBOX(XRCID("IDC_SEA"), MainFrame::sealChange)
    EVT_CHECKBOX(XRCID("IDC_THREE_EYE_ROCK"), MainFrame::sealChange)

    EVT_COMMAND_SCROLL(XRCID("IDS_KEY"), MainFrame::keyChange)
END_EVENT_TABLE()
