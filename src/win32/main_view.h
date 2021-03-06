/**
 * Copyright (C) 2010 syndicode
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 **/

#ifndef _MAIN_VIEW_H
#define _MAIN_VIEW_H

#include "nfo_view_ctrl.h"
#include "infekt_global.h"
#include "infobar.h"

class CViewContainer : public CWnd
{
public:
	CViewContainer();
	virtual ~CViewContainer();

	bool ForwardFocusTypeMouseKeyboardEvent(const MSG* pMsg);
	PNFOViewControl& GetRenderCtrl() { return m_renderControl; }
	PNFOViewControl& GetClassicCtrl() { return m_classicControl; }
	PNFOViewControl& GetTextOnlyCtrl() { return m_textOnlyControl; }
	PNFOViewControl& GetActiveCtrl() { return m_curViewCtrl; }
	PNFOData& GetNfoData() { return m_nfoData; }

	bool OpenFile(const std::wstring& a_filePath, ENfoCharset a_charset = NFOC_AUTO);
	bool OpenLoadedFile(PNFOData a_nfoData);
	void SwitchView(EMainView a_view);
	EMainView GetViewType() const { return m_curViewType; }

	void SetCopyOnSelect(bool nb) {
		m_renderControl->SetCopyOnSelect(nb);
		m_classicControl->SetCopyOnSelect(nb);
		m_textOnlyControl->SetCopyOnSelect(nb);
	}

	void SetCenterNfo(bool nb) {
		m_renderControl->SetCenterNfo(nb);
		m_classicControl->SetCenterNfo(nb);
	}

	void SetOnDemandRendering(bool nb) {
		m_renderControl->SetOnDemandRendering(nb);
		m_classicControl->SetOnDemandRendering(nb);
		m_textOnlyControl->SetOnDemandRendering(nb);
	}

	bool GetWrapLines() const { return m_wrapLines; }
	void SetWrapLines(bool);

	const std::wstring GetSelectedText() const;
	void CopySelectedTextToClipboard() const;
	void SelectAll();
	bool ReloadFile(ENfoCharset a_charset = NFOC_AUTO);

	void ScrollPageDown();
	void ScrollPageUp();
protected:
	PNFOViewControl m_renderControl;
	PNFOViewControl m_classicControl;
	PNFOViewControl m_textOnlyControl;

	EMainView m_curViewType;
	PNFOViewControl m_curViewCtrl;
	PNFOData m_nfoData;
	bool m_wrapLines;
	std::wstring m_nfoFilePath;

	bool m_showInfoBar;
	std::shared_ptr<CInfektInfoBar> m_infoBar;
	int m_infoBarHeight;
	bool m_infoBarResizing;

	LPTSTR m_cursor;
	HMENU m_contextMenuHandle;
	bool m_resized;

	virtual void OnCreate();
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnAfterResize(bool a_fake);
	bool CurAssignNfo();
	bool IsYOnSplitter(int a_y);
};

#endif /* !_MAIN_VIEW_H */
