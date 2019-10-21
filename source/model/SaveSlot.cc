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

#include "model/SaveSlot.hh"

using namespace emuWorks;

SaveSlot::SaveSlot(const char *nvram) {
    this->nvram = new unsigned char[GAME_SIZE];
    memcpy(this->nvram, nvram, GAME_SIZE);

    valid = (nvram[NAME_OFFSET] != '\xF4');

    setModified(false);

    checkForNewGame();
}

SaveSlot::~SaveSlot() {
    delete nvram;
}

void SaveSlot::checkForNewGame() {
    if (nvram[TRIFORCE_OFFSET] == 1) {
        setTriforce(true);

        setContainers(MAGICCONTAINER, 4);
        setContainers(LIFECONTAINER, 4);

        setItem(CANDLE, false);
        setItem(GLOVE, false);
        setItem(RAFT, false);
        setItem(BOOTS, false);
        setItem(CROSS, false);
        setItem(FLUTE, false);
        setItem(MAGICKEY, false);
        setItem(HAMMER, false);

        for (int palace = 0; palace < 6; palace++) {
            setSeal(palace, false);
        }

        setKeys(0);

        setModified(false);
    }
}

wxString SaveSlot::getName() const {
    wxString name;

    for (int pos = 0; pos < 8; pos++) {
        char letter = fromNES(nvram[NAME_OFFSET + pos]);
        name.append(1, letter);
    }

    return name.Trim();
}

void SaveSlot::setName(wxString &name) {
    int length = name.Length();

    for (int pos = 0; pos < 8; pos++) {
        unsigned char letter;

        if ((length - 1) < pos) {
            letter = static_cast<unsigned char>(0xF4);
        } else {
            letter = toNES(name.at(pos));
        }

        nvram[NAME_OFFSET + pos] = letter;
    }

    setModified();
}

int SaveSlot::getPlayCount() const {
    return nvram[PLAY_COUNT_OFFSET];
}

void SaveSlot::setPlayCount(unsigned char value) {
    nvram[PLAY_COUNT_OFFSET] = value;
    setModified();
}

bool SaveSlot::hasTriforce() const {
    return (nvram[TRIFORCE_OFFSET] == 2);
}

void SaveSlot::setTriforce(bool value) {
    nvram[TRIFORCE_OFFSET] = (value ? 2 : 0);
    setModified();
}

int SaveSlot::getLevel(int which) const {
    return nvram[LEVEL_OFFSET + which];
}

void SaveSlot::setLevel(int which, unsigned char value) {
    nvram[LEVEL_OFFSET + which] = value;
    setModified();
}

int SaveSlot::getContainers(int which) const {
    return nvram[CONTAINER_OFFSET + which];
}

void SaveSlot::setContainers(int which, unsigned char value) {
    nvram[CONTAINER_OFFSET + which] = value;
    setModified();
}

bool SaveSlot::hasTechnique(int technique) const {
    return ((nvram[TECHNIQUE_OFFSET] & technique) > 0);
}

void SaveSlot::setTechnique(int technique, bool value) {
    if (value) {
        nvram[TECHNIQUE_OFFSET] |= technique;
    } else {
        nvram[TECHNIQUE_OFFSET] &= (~technique);
    }

    setModified();
}

bool SaveSlot::hasSpell(int spell) const {
    return (nvram[SPELL_OFFSET + spell] == 1);
}

void SaveSlot::setSpell(int spell, bool value) {
    nvram[SPELL_OFFSET + spell] = (value ? 1 : 0);
    setModified();
}

bool SaveSlot::hasItem(int item) const {
    return (nvram[ITEM_OFFSET + item] == 1);
}

void SaveSlot::setItem(int item, bool value) {
    nvram[ITEM_OFFSET + item] = (value ? 1 : 0);
    setModified();
}

bool SaveSlot::hasSeal(int palace) const {
    return (nvram[PALACE_OFFSET + palace] == (palace + 1));
}

void SaveSlot::setSeal(int palace, bool value) {
    if (value) {
        nvram[SEAL_OFFSET]--;
    } else {
        nvram[SEAL_OFFSET]++;
    }

    nvram[PALACE_OFFSET + palace] = (value ? (palace + 1) : 0);
    setModified();
}

int SaveSlot::getKeys() const {
    return nvram[KEYS_OFFSET];
}

void SaveSlot::setKeys(unsigned char value) {
    nvram[KEYS_OFFSET] = value;
    setModified();
}

char SaveSlot::fromNES(unsigned char letter) {
    if ((letter >= 0xD0) && (letter <= 0xD9)) {
        return static_cast<char>('0' + (letter - 0xD0));
    } else if ((letter >= 0xDA) && (letter <= 0xF3)) {
        return static_cast<char>('A' + (letter - 0xDA));
    }

    return static_cast<char>(' ');
}

unsigned char SaveSlot::toNES(char letter) {
    if ((letter >= '0') && (letter <= '9')) {
        return static_cast<unsigned char>(0xD0 + (letter - '0'));
    } else if ((letter >= 'A') && (letter <= 'Z')) {
        return static_cast<unsigned char>(0xDA + (letter - 'A'));
    }

    return static_cast<unsigned char>(0xF4);
}
