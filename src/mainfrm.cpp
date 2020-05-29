/////////////////////////////////////////////////////////////////////////////
// Purpose:		Main frame window
// Author:		Ralph Walden
// Copyright:	Copyright (c) 1998-2020 KeyWorks Software (Ralph Walden)
// License:		Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <commdlg.h>

#include <tttextfile.h>  // textfile -- Classes for reading and writing line-oriented files

#include "resource.h"

#include "aboutdlg.h"  // CAboutDlg
#include "mainfrm.h"
#include "prefs.h"
#include "traceview.h"

TRACE_FLAGS uprof;

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
        return TRUE;

    return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    UIUpdateToolBar();
    return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    m_hMapping = CreateFileMapping((HANDLE) -1, NULL, PAGE_READWRITE, 0, 4096, ttlib::txtTraceShareName);
    ttASSERT(m_hMapping);
    if (!m_hMapping)
    {
        ttlib::MsgBox(IDS_FILE_MAPPING_ERROR);
        ExitProcess((UINT) -1);
    }
    m_pszMap = (char*) MapViewOfFile(m_hMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    ttASSERT(m_pszMap);
    if (!m_pszMap)
    {
        ttlib::MsgBox(IDS_FILE_MAPPING_ERROR);
        ExitProcess((UINT) -1);
    }

    CreateSimpleToolBar();

    m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL,
                                 WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL |
                                     ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_SAVESEL,
                                 WS_EX_CLIENTEDGE);

    UIAddToolBar(m_hWndToolBar);
    UISetCheck(ID_VIEW_TOOLBAR, 1);

    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);

    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    CRegKey key;
    if (key.Create(HKEY_CURRENT_USER, txtKeyViewRegKey) == ERROR_SUCCESS)
    {
        if (!IsIconic())
        {
            RECT rc;
            GetWindowRect(&rc);
            RegSetValueEx(key, "WindowRect", 0, REG_BINARY, (CONST BYTE*) &rc, sizeof(RECT));
        }
    }

    bHandled = FALSE;
    return 0;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
    ::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_TOOLBAR, bVisible);
    UpdateLayout();
    return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CAboutDlg dlg;
    dlg.DoModal(*this);
    return 0;
}

void CMainFrame::OnTraceGeneral(WPARAM /* wParam */, LPARAM /* lParam */)
{
    if (!uprof.ShowGeneral)
        return;

    if (ttlib::issameas(m_pszMap, m_cszLastMsg, tt::CASE::either))
        return;  // duplicate message
    m_cszLastMsg = m_pszMap;

    m_view.SetSel(-1, -1);
    ::SendMessageW(m_view, EM_REPLACESEL, (WPARAM) true, (LPARAM) m_cszLastMsg.to_utf16().c_str());

    m_view.SetSel(-1, -1);
    m_view.ReplaceSel("\n");
}

void CMainFrame::OnTraceWarning(WPARAM /* wParam */, LPARAM /* lParam */)
{
    if (!uprof.ShowWarning)
        return;

    m_view.SetSel(-1, -1);
    ::SendMessageW(m_view, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) ttlib::utf8to16(m_pszMap).c_str());
}

void CMainFrame::OnTraceError(WPARAM /* wParam */, LPARAM /* lParam */)
{
    if (!uprof.ShowError)
        return;

    m_view.SetSel(-1, -1);
    ::SendMessageW(m_view, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) ttlib::utf8to16(m_pszMap).c_str());
}

void CMainFrame::OnTraceEvent(WPARAM /* wParam */, LPARAM /* lParam */)
{
    if (!uprof.ShowEvent)
        return;

    m_view.SetSel(-1, -1);
    ::SendMessageW(m_view, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) ttlib::utf8to16(m_pszMap).c_str());
}

void CMainFrame::OnTraceProperty(WPARAM /* wParam */, LPARAM /* lParam */)
{
    if (!uprof.ShowProperty)
        return;

    m_view.SetSel(-1, -1);
    ::SendMessageW(m_view, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) ttlib::utf8to16(m_pszMap).c_str());
}

void CMainFrame::OnTraceScript(WPARAM /* wParam */, LPARAM /* lParam */)
{
    if (!uprof.ShowScript)
        return;

    m_view.SetSel(-1, -1);
    ::SendMessageW(m_view, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) ttlib::utf8to16(m_pszMap).c_str());
}

void CMainFrame::OnClear(WPARAM /* wParam */, LPARAM /* lParam */)
{
    m_view.SetSel(0, -1);
    m_view.ReplaceSel("");
    m_view.SendMessage(EM_SCROLLCARET, (WPARAM) 0, (LPARAM) 0);
}

void CMainFrame::OnClearView()
{
    m_view.SetSel(0, -1);
    m_view.ReplaceSel("");
    m_view.SendMessage(EM_SCROLLCARET, (WPARAM) 0, (LPARAM) 0);
    m_cszLastMsg.clear();
}

void CMainFrame::OnSaveAs()
{
    char szPath[MAX_PATH];
    szPath[0] = '\0';

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof ofn;
    ofn.hwndOwner = *this;
    ofn.hInstance = GetModuleHandle(NULL);
    ofn.lpstrFile = szPath;
    ofn.nMaxFile = sizeof(szPath);
    ofn.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileName(&ofn))
    {
        ttlib::cstr buffer;
        buffer.GetWndText(m_view);
        ttlib::viewfile file;
        file.ReadString(buffer);

        if (file.WriteFile(ofn.lpstrFile))
            ttlib::MsgBox(_tt(IDS_FILE_SAVED) + ofn.lpstrFile, "ttTrace", MB_OK);
        else
            ttlib::MsgBox(_tt(IDS_FILE_SAVED) + ofn.lpstrFile, "ttTrace");
    }
}

void CMainFrame::OnPreferences()
{
    CPreferences dlg;
    dlg.DoModal(*this);
}

void CMainFrame::OnSetTitle(WPARAM /* wParam */, LPARAM /* lParam */)
{
    ::SetWindowTextW(*this, ttlib::utf8to16(m_pszMap).c_str());
}

void CMainFrame::OnHideTraceGeneral(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowGeneral = false;
}

void CMainFrame::OnHideTraceEvent(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowEvent = false;
}

void CMainFrame::OnHideTraceWarning(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowWarning = false;
}

void CMainFrame::OnHideTraceProperty(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowProperty = false;
}

void CMainFrame::OnHideTraceScript(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowScript = false;
}

void CMainFrame::OnHideTraceError(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowError = false;
}

void CMainFrame::OnShowTraceGeneral(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowGeneral = true;
}

void CMainFrame::OnShowTraceEvent(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowEvent = true;
}

void CMainFrame::OnShowTraceWarning(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowWarning = true;
}

void CMainFrame::OnShowTraceProperty(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowProperty = true;
}

void CMainFrame::OnShowTraceScript(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowScript = true;
}

void CMainFrame::OnShowTraceError(WPARAM /* wParam */, LPARAM /* lParam */)
{
    uprof.ShowError = true;
}
