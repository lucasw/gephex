#ifndef CHANGESDIALOG_H
#define CHANGESDIALOG_H
#include "changesdialog.h"

class ChangesDialog : public ChangesDialogBase
{ 
public:
    ChangesDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ChangesDialog();

};

#endif // CHANGESDIALOG_H
