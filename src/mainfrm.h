/////////////////////////////////////////////////////////////////////////////
// Purpose:     Main window frame
// Author:		Ralph Walden
// Copyright:	Copyright (c) 1998-2020 KeyWorks Software (Ralph Walden)
// License:		Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ttcstr.h>     // cstr -- Classes for handling zero-terminated char strings.
#include <ttwtlmsgs.h>  // Macros for mapping Windows messages to functions

#include "traceview.h"

extern const char* txtMainClass;  // "KeyViewMsgs";

// REVIEW: [randalphwa - 3/4/2019] This will share settings with the older KeyView. Is that a good thing?
constexpr const auto txtKeyViewRegKey = "Software\\KeyWorks\\KeyView";

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>, public CMessageFilter, public CIdleHandler
{
public:
    DECLARE_FRAME_WND_CLASS(ttlib::txtTraceClass, IDR_MAINFRAME)

    CTraceView m_view;

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle();

    BEGIN_UPDATE_UI_MAP(CMainFrame)
    UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CMainFrame)
        MSG_COMMAND_HANDLER(IDM_CLEAR, OnClearView)
        MSG_COMMAND_HANDLER(IDM_PREFERENCES, OnPreferences)
        MSG_COMMAND_HANDLER(IDM_FILE_SAVE_AS, OnSaveAs)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

        MSG_WMP_HANDLER(ttlib::WMP_CLEAR_TRACE, OnClear)
        MSG_WMP_HANDLER(ttlib::WMP_SET_TITLE, OnSetTitle)

        MSG_WMP_HANDLER(ttlib::WMP_TRACE_GENERAL, OnTraceGeneral);
        MSG_WMP_HANDLER(ttlib::WMP_TRACE_EVENT, OnTraceEvent);
        MSG_WMP_HANDLER(ttlib::WMP_TRACE_WARNING, OnTraceWarning);
        MSG_WMP_HANDLER(ttlib::WMP_TRACE_PROPERTY, OnTraceProperty);
        MSG_WMP_HANDLER(ttlib::WMP_TRACE_SCRIPT, OnTraceScript);
        MSG_WMP_HANDLER(ttlib::WMP_TRACE_ERROR, OnTraceError);

        MSG_WMP_HANDLER(ttlib::WMP_HIDE_GENERAL, OnHideTraceGeneral);
        MSG_WMP_HANDLER(ttlib::WMP_HIDE_EVENT, OnHideTraceEvent);
        MSG_WMP_HANDLER(ttlib::WMP_HIDE_WARNING, OnHideTraceWarning);
        MSG_WMP_HANDLER(ttlib::WMP_HIDE_PROPERTY, OnHideTraceProperty);
        MSG_WMP_HANDLER(ttlib::WMP_HIDE_SCRIPT, OnHideTraceScript);
        MSG_WMP_HANDLER(ttlib::WMP_HIDE_ERROR, OnHideTraceError);

        MSG_WMP_HANDLER(ttlib::WMP_SHOW_GENERAL, OnShowTraceGeneral);
        MSG_WMP_HANDLER(ttlib::WMP_SHOW_EVENT, OnShowTraceEvent);
        MSG_WMP_HANDLER(ttlib::WMP_SHOW_WARNING, OnShowTraceWarning);
        MSG_WMP_HANDLER(ttlib::WMP_SHOW_PROPERTY, OnShowTraceProperty);
        MSG_WMP_HANDLER(ttlib::WMP_SHOW_SCRIPT, OnShowTraceScript);
        MSG_WMP_HANDLER(ttlib::WMP_SHOW_ERROR, OnShowTraceError);

        COMMAND_ID_HANDLER(IDM_APP_EXIT, OnFileExit)
        COMMAND_ID_HANDLER(IDM_VIEW_TOOLBAR, OnViewToolBar)
        COMMAND_ID_HANDLER(IDM_APP_ABOUT, OnAppAbout)
        CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
        CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
    END_MSG_MAP()

protected:
    void OnClearView();
    void OnPreferences();
    void OnSaveAs();


    void OnClear(WPARAM /* wParam */, LPARAM /* lParam */);
    void OnSetTitle(WPARAM /* wParam */, LPARAM /* lParam */);

    void OnTraceGeneral(WPARAM wParam, LPARAM lParam);
    void OnTraceEvent(WPARAM wParam, LPARAM lParam);
    void OnTraceWarning(WPARAM wParam, LPARAM lParam);
    void OnTraceProperty(WPARAM wParam, LPARAM lParam);
    void OnTraceScript(WPARAM wParam, LPARAM lParam);
    void OnTraceError(WPARAM wParam, LPARAM lParam);

    void OnHideTraceGeneral(WPARAM wParam, LPARAM lParam);
    void OnHideTraceEvent(WPARAM wParam, LPARAM lParam);
    void OnHideTraceWarning(WPARAM wParam, LPARAM lParam);
    void OnHideTraceProperty(WPARAM wParam, LPARAM lParam);
    void OnHideTraceScript(WPARAM wParam, LPARAM lParam);
    void OnHideTraceError(WPARAM wParam, LPARAM lParam);

    void OnShowTraceGeneral(WPARAM wParam, LPARAM lParam);
    void OnShowTraceEvent(WPARAM wParam, LPARAM lParam);
    void OnShowTraceWarning(WPARAM wParam, LPARAM lParam);
    void OnShowTraceProperty(WPARAM wParam, LPARAM lParam);
    void OnShowTraceScript(WPARAM wParam, LPARAM lParam);
    void OnShowTraceError(WPARAM wParam, LPARAM lParam);

    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    HANDLE m_hMapping;
    char* m_pszMap { nullptr };  // points to data in shared memory
    ttlib::cstr m_cszLastMsg;
};
