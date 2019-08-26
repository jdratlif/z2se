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

// $Id: SaveSlot.hh,v 1.9 2008/12/17 06:24:27 jdratlif Exp $

#ifndef Z2SE_SAVESLOT_HH_
#define Z2SE_SAVESLOT_HH_

/// Game Size
#define GAME_SIZE 0x32

/// Starting SRAM offset of the experience levels
#define LEVEL_OFFSET 0x00

/// Starting SRAM offset for the spells
#define SPELL_OFFSET 0x04

/// Starting SRAM offset for the containers
#define CONTAINER_OFFSET 0x0C

/// Starting SRAM offset for the items
#define ITEM_OFFSET 0x0E

/// Starting SRAM offset for the palace seals
#define PALACE_OFFSET 0x16

/// SRAM offset for the seal count
#define SEAL_OFFSET 0x1D

/// SRAM offset for the keys
#define KEYS_OFFSET 0x1C

/// SRAM offset for the name
#define NAME_OFFSET 0x2A

/// SRAM offset for the sword techniques
#define TECHNIQUE_OFFSET 0x1F

/// SRAM offset for the play count
#define PLAY_COUNT_OFFSET 0x28

/// SRAM offset for the triforce
#define TRIFORCE_OFFSET 0x29

namespace emuWorks {
    /// the levels of experience
    enum Levels {
        SWORDLEVEL, MAGICLEVEL, LIFELEVEL
    };
    
    /// The spells that can be learned
    enum Spells {
        SHIELD, JUMP, LIFE, FAIRY, FIRE, REFLECT, SPELL, THUNDER
    };
    
    /// The containers
    enum Containers {
        MAGICCONTAINER, LIFECONTAINER
    };
    
    /// The game items
    enum Items {
        CANDLE, GLOVE, RAFT, BOOTS, CROSS, FLUTE, MAGICKEY, HAMMER
    };
    
    /// The sword techniques
    enum Techniques {
        DOWNWARDTHRUST = 0x10, UPWARDTHRUST = 0x04
    };
    
    /**
     * Class encapsulating a SaveSlot for a Zelda II game.
     */
    class SaveSlot {
        friend class SRAMFile;
        
    private:
        unsigned char *nvram;
        bool modified, valid;
        
        /**
         * Sets if this game has been modified or not.
         */
        void setModified(bool modified = true) { this->modified = modified; }
        
        /**
         * Translates a character from the Zelda II alphabet to ASCII.
         *
         * @param letter The letter to translate.
         *
         * @return The translated letter.
         */
        static char fromNES(unsigned char letter);
        
        /**
         * Translates a character from ASCII to the Zelda II alphabet.
         *
         * @param letter The letter to translate.
         *
         * @return The translated letter.
         */
        static unsigned char toNES(char letter);

    public:
        /**
         * Constructor for a SaveSlot.
         *
         * @param nvram The SRAM data for this SaveSlot.
         */
        SaveSlot(const char *nvram);
        
        /**
         * Destructor for a SaveSlot object.
         */
        ~SaveSlot();
        
        /**
         * Queries if this SaveSlot has been modified;
         *
         * @return true if modified; false otherwise.
         */
        bool isModified() const { return modified; }
        
        /**
         * Queries if this SaveSlot is valid.
         *
         * @return true if valid; false otherwise.
         */
        bool isValid() const { return valid; }
        
        /**
         * Fixes data for a new quest game.
         */
        void checkForNewGame();

        /**
         * Gets the name of the character.
         *
         * @return The name.
         */
        wxString getName() const;
        
        /**
         * Sets the name of the character.
         *
         * @param value The new name.
         */
        void setName(wxString &value);
        
        /**
         * Gets the play count.
         *
         * @return The play count.
         */
        int getPlayCount() const;
        
        /**
         * Sets the play count.
         *
         * @param value The new play count.
         */
        void setPlayCount(unsigned char value);
        
        /**
         * Queries if the player has saved the Triforce before.
         *
         * @return true if they have; false otherwise.
         */
        bool hasTriforce() const;
        
        /**
         * Sets whether this player has saved the Triforce before.
         *
         * @param value true if they have; false otherwise.
         */
        void setTriforce(bool value);
        
        /**
         * Gets one of the experience level elements.
         *
         * @param which Which level to retrieve. Valid values are one of the
         *              Levels enumeration.
         *
         * @return The experience level.
         */
        int getLevel(int which) const;
        
        /**
         * Sets one of the experience level elements.
         *
         * @param which Which level to set. Valid values are one of the
         *              Levels enumeration.
         * @param value The new experience level.
         */
        void setLevel(int which, unsigned char value);
        
        /**
         * Gets one of the container values.
         *
         * @param which Which container value to get. Valid values are one of
         *              Containers enumeration.
         *
         * @return The number of containers.
         */
        int getContainers(int which) const;
        
        /**
         * Sets one of the container values.
         *
         * @param which Which container value to set. Valid values are one of
         *              Containers enumeration.
         * @param value The new container value.
         */
        void setContainers(int which, unsigned char value);
        
        /**
         * Queries if the player has a sword technique.
         *
         * @param technique Which technique to check for. Valid values are in
         *                  the Techniques enumeration.
         *
         * @return true if they have the technique; false otherwise.
         */
        bool hasTechnique(int technique) const;
        
        /**
         * Sets if the player has a sword technique or not.
         * 
         * @param technique Which technique to set. Valid values are in
         *                  the Techniques enumeration.
         * @param value true to have the technique; false otherwise.
         */
        void setTechnique(int technique, bool value);
        
        /**
         * Queries if the player has a certain spell.
         *
         * @param spell Which spell. Valid values are in the Spells enumeration.
         *
         * @return true if they have it; false otherwise.
         */
        bool hasSpell(int spell) const;
        
        /**
         * Sets if the player has a certain spell.
         *
         * @param spell Which spell. Valid values are in the Spells enumeration.
         * @param value true to have the spell; false otherwise.
         */
        void setSpell(int spell, bool value);
        
        /**
         * Queries if the player has a certain item.
         *
         * @param item Which item. Valid values are in the Items enumeration.
         *
         * @return true if they have it; false otherwise.
         */
        bool hasItem(int item) const;
        
        /**
         * Sets if the player has a certain item.
         *
         * @param item Which item. Valid values are in the Items enumeration.
         * @param value true to have the item; false otherwise.
         */
        void setItem(int item, bool value);
        
        /**
         * Queries if the player has sealed a certain palace.
         *
         * @param palace Which palace. Valid values are 0-5.
         *
         * @return true if they have sealed it; false otherwise.
         */
        bool hasSeal(int palace) const;
        
        /**
         * Sets if the player has sealed a certain palace.
         *
         * @param palace Which palace. Valid values are 0-5.
         * @param value true to seal; false otherwise.
         */
        void setSeal(int palace, bool value);
        
        /**
         * Gets the number of keys the player has.
         *
         * @return The number of keys.
         */
        int getKeys() const;
        
        /**
         * Sets the number of keys the player has.
         *
         * @param value The new number of keys.
         */
        void setKeys(unsigned char value);
    };
}

#endif

