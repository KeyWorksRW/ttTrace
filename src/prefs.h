/////////////////////////////////////////////////////////////////////////////
// Name:		Prefs.h
// Purpose:		Class for setting what message to accept/ignore
// Author:		Ralph Walden
// Copyright:	Copyright (c) 1998-2020 KeyWorks Software (Ralph Walden)
// License:		Apache License (see ../LICENSE)
/////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef IDDLG_PREFERENCES
    #include "resource.h"
#endif

#include <ttwindlg.h>  // Class for displaying a dialog

class CPreferences : public ttlib::dlg
{
public:
    CPreferences() : ttlib::dlg(IDDLG_PREFERENCES) {}

protected:
    void OnBegin(void) override;
    void OnOK(void) override;
};
