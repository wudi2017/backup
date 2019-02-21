@import "../iautolib.js"
@import "../libJSonDB/iautoJsonDbIF.js"

function EXPLOG(logstr)
{
    SLOG(logstr,"exportWinControl");
    log(logstr);
}

function export_SpecScreenSelect()
{
	EXPLOG("export_SpecScreenSelect");

	var expSelWin = NSPanel.alloc().init();
	//expSelWin.setStyleMask(NSTitledWindowMask + NSFullSizeContentViewWindowMask);
	expSelWin.setBackgroundColor(NSColor.colorWithRed_green_blue_alpha(0.95, 0.95, 0.95, 1));
	//expSelWin.setTitleVisibility(NSWindowTitleHidden);
	expSelWin.setTitlebarAppearsTransparent(true);
	expSelWin.setTitle("Export");
	expSelWin.setFrame_display(NSMakeRect(0, 0, 360, 370), false);
	expSelWin.setMovableByWindowBackground(true);
	expSelWin.becomeKeyWindow();
	expSelWin.setLevel(NSFloatingWindowLevel);
	expSelWin.contentView().setWantsLayer(true)

	//threadDictionary[identifier] = Toolbar;
	expSelWin.center();

	expSelWin.makeKeyAndOrderFront(nil);

	expListSelectView = SExportListSelectView.alloc().init();
	expSelWin.contentView().addSubview(expListSelectView);

	EXPLOG("export_SpecScreenSelect end");
}