#include "MainFrame.h"
#include "wx/wx.h"

enum IDs {
	buttonID = 2,
	sliderID = 3,
	textID = 4
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(buttonID, MainFrame::OnButtonClicked)
	EVT_SLIDER(sliderID, MainFrame::OnSliderChanged)
	EVT_TEXT(textID, MainFrame::OntextChanged)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);

	wxButton* button = new wxButton(panel, buttonID, "Button", wxPoint(300, 275), wxSize(200, 50));
	wxSlider* slider = new wxSlider(panel, sliderID, 50, 0, 100, wxPoint(300, 350), wxSize(200, -1));
	wxTextCtrl* text = new wxTextCtrl(panel, textID, "", wxPoint(300, 425), wxSize(200, -1));

	CreateStatusBar();
	
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button clicked");
}

void MainFrame::OnSliderChanged(wxCommandEvent& evt) {
	wxString str = wxString::Format("Slider value set to: %d", evt.GetInt());
	wxLogStatus(str);
}

void MainFrame::OntextChanged(wxCommandEvent& evt) {
	wxString str = wxString::Format("Text Changed: %s", evt.GetString());
	wxLogStatus(str);
}
 