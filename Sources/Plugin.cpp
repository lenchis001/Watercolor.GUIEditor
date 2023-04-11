#include "Plugin.h"

#include "GameUIEditor.h"
#include "Services/FunctionsProcessing/FunctionsProcessingManager.h"

#define CURRENR_MODULE_NAME L"GUIEditor.dll"

using namespace GUIEditor;

std::wstring Plugin::getName()
{
    return L"GUI editor";
}

PluginType Plugin::getType()
{
    return PluginType::TOP_MENU;
}

void Plugin::onTopMenuItemClicked(const std::wstring& openedProjectPath, HWND parent) {
    // That's okay, don't worry. wxWidgets library
    // will clean the memory on it's own
    new wxApp();

    wxImage::AddHandler(new wxJPEGHandler);

    auto handle = GetModuleHandle(CURRENR_MODULE_NAME);

    assert(handle != nullptr);
    wxEntryStart(handle);

    wxWindow parentWindow;
    parentWindow.SetHWND((WXHWND)parent);
    parentWindow.AdoptAttributesFromHWND();
    wxTopLevelWindows.Append(&parentWindow);

    boost::shared_ptr<IFunctionsProcessingManager> functionsProcessingManager = boost::make_shared<FunctionsProcessingManager>();

    // This too
    GameUIEditor* dialog = new GameUIEditor(&parentWindow, functionsProcessingManager, openedProjectPath);
    dialog->ShowModal();

    wxTopLevelWindows.DeleteObject(&parentWindow);
    parentWindow.SetHWND((WXHWND)NULL);

    wxEntryCleanup();
}

std::wstring Plugin::onWelcomeWindowButtonClicked(HWND parent) { return L""; }

Plugin::~Plugin()
{

}