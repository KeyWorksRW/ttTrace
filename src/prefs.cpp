/////////////////////////////////////////////////////////////////////////////
// Purpose:		Class for setting what messageS to show or hide
// Author:		Ralph Walden
// Copyright:	Copyright (c) 1998-2020 KeyWorks Software (Ralph Walden)
// License:		Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "prefs.h"

void CPreferences::OnBegin(void)
{
    CHECK_DLG_ID(IDCHECK_SHOW_GENERAL);
    CHECK_DLG_ID(IDCHECK_SHOW_ERRORS);
    CHECK_DLG_ID(IDCHECK_SHOW_WARNINGS);
    CHECK_DLG_ID(IDCHECK_SHOW_EVENTS);
    CHECK_DLG_ID(IDCHECK_SHOW_PROPERTIES);
    CHECK_DLG_ID(IDCHECK_SHOW_SCRIPTS);

    SetCheck(IDCHECK_SHOW_GENERAL, uprof.ShowGeneral);
    SetCheck(IDCHECK_SHOW_ERRORS, uprof.ShowError);
    SetCheck(IDCHECK_SHOW_WARNINGS, uprof.ShowWarning);
    SetCheck(IDCHECK_SHOW_EVENTS, uprof.ShowEvent);
    SetCheck(IDCHECK_SHOW_PROPERTIES, uprof.ShowProperty);
    SetCheck(IDCHECK_SHOW_SCRIPTS, uprof.ShowScript);
}

void CPreferences::OnOK(void)
{
    uprof.ShowGeneral = GetCheck(IDCHECK_SHOW_GENERAL);
    uprof.ShowError = GetCheck(IDCHECK_SHOW_ERRORS);
    uprof.ShowWarning = GetCheck(IDCHECK_SHOW_WARNINGS);
    uprof.ShowEvent = GetCheck(IDCHECK_SHOW_EVENTS);
    uprof.ShowProperty = GetCheck(IDCHECK_SHOW_PROPERTIES);
    uprof.ShowScript = GetCheck(IDCHECK_SHOW_SCRIPTS);
}
