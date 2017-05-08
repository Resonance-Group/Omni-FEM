#ifndef CUSTOM_EVENT_H_
#define CUSTOM_EVENT_H_
/*
#include <wx/wx.h>


class MyFooEvent;
wxDECLARE_EVENT(MY_NEW_TYPE, MyFooEvent);
 
class MyFooEvent: public wxCommandEvent
{
public:
	MyFooEvent(wxEventType commandType = MY_NEW_TYPE, int id = 0)
        		:  wxCommandEvent(commandType, id) { }
 
	// You *must* copy here the data to be transported
	MyFooEvent(const MyFooEvent& event)
        		:  wxCommandEvent(event) { this->SetPoint(event.GetPoint()); }
 
	// Required for sending with wxPostEvent()
	wxEvent* Clone() const { return new MyFooEvent(*this); }
 
	wxRealPoint GetPoint() const { return m_RealPoint; }
	void SetPoint(const wxRealPoint& rp) { m_RealPoint = rp; }
 
private:
	wxRealPoint m_RealPoint;
};

typedef void (wxEvtHandler::*MyFooEventFunction)(MyFooEvent &);
 
#define MyFooEventHandler(func) wxEVENT_HANDLER_CAST(MyFooEventFunction, func)                    
 
// Optional: define an event table entry
#define EVT_MYFOO(id, func) \
 	wx__DECLARE_EVT1(MY_NEW_TYPE, id, MyFooEventHandler(func))
 
// Very optionally, you can do a similar #define for EVT_MYFOO_RANGE.
#define EVT_MYFOO_RANGE(id1,id2, func) \
	wx__DECLARE_EVT2(MY_NEW_TYPE, id1, id2, MyFooEventHandler(func))
     */ 


#endif