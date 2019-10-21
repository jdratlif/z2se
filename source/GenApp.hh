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

#ifndef Z2SE_GENAPP_HH_
#define Z2SE_GENAPP_HH_

/**
 * Private namespace used by all emuWorks programs.
 */
namespace emuWorks {
    /**
     * The main class. Initializes the application and creates the view.
     */
    class GenApp : public wxApp {
        DECLARE_CLASS(GenApp)

    public:
        /// The short name of the application.
        static const wxString *APP_NAME;

        /// The full name of the application
        static const wxString *APP_FULL_NAME;

        /// The version of the application.
        static const wxString *APP_VERSION;

        /// The copyright notice for the application.
        static const wxString *APP_COPYRIGHT;

        /// The website URL for this application.
        static const wxString *APP_URL;

        /**
         * Called by wxWidgets to start initialization of the application.
         *
         * @return true if initialization should proceed; false otherwise.
         */
        virtual bool OnInit();
    };

    DECLARE_APP(GenApp)
}

#endif
