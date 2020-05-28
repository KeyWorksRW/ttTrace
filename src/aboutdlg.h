/////////////////////////////////////////////////////////////////////////////
// Purpose:		Class for displaying About Box
// Author:      Ralph Walden
// Copyright:   Copyright (c) 1998-2020 KeyWorks Software (Ralph Walden)
// License:		Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef IDD_ABOUTBOX
    #include "resource.h"
#endif

#include <ttwindlg.h>  // dlg -- Class for displaying a dialog

class CAboutDlg : public ttlib::dlg
{
public:
    CAboutDlg() : ttlib::dlg(IDD_ABOUTBOX) {}
};
