#include <wx/wx.h>
#include "Framework.h"

class MyApp : public wxApp {
public:
	virtual bool OnInit() override {
		Framework* frame = new Framework("UNTITLED TYPING GAME", wxPoint(100, 100), wxSize(1280, 800));
		frame->Show();
		frame->Centre();
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);