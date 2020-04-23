/////////////////////////////////////////////////////////////////////////////
// Name:		AboutDlg.h
// Purpose:		Class for handling About Box
// Author:      Ralph Walden
// Copyright:   Copyright (c) 1998-2020 KeyWorks Software (Ralph Walden)
// License:		Apache License (see LICENSE)
/////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef IDD_ABOUTBOX
    #include "resource.h"
#endif

#include <ttwindlg.h>  // Class for displaying a dialog

class CAboutDlg : public ttlib::dlg
{
public:
    CAboutDlg() : ttlib::dlg(IDD_ABOUTBOX) {}
};
