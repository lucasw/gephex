#ifndef INCLUDED_ABOUT_DIALOG_IMPL
#define INCLUDED_ABOUT_DIALOG_IMPL

#include "aboutdialog.h"

class AboutDialogImpl : public AboutDialog
{
public:
	AboutDialogImpl( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
};

#endif
