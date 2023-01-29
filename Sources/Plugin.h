#pragma once

#include "boost/config.hpp"

#include "IPlugin.h"

class Plugin : public IPlugin {
public:
	std::wstring getName() override;

	PluginType getType() override;

	void onTopMenuItemClicked(const std::wstring& openedProjectPath, HWND parent) override;
	std::wstring onWelcomeWindowButtonClicked(HWND parent) override;

	~Plugin() override;
};

extern "C" BOOST_SYMBOL_EXPORT Plugin plugin;
Plugin plugin;