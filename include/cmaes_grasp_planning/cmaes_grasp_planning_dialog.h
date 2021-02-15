#ifndef _CMAES_GRASP_PLANNING_DIALOG_H_
#define _CMAES_GRASP_PLANNING_DIALOG_H_

#include <QDialog>

#include "ui_cmaes_grasp_planning_dialog.h"


namespace cmaes_grasp_planning 
{

class CMAESGraspPlanningDialog : public QDialog, public Ui::CMAESGraspPlanningDialogBase
{
    Q_OBJECT
private:

public:
    CMAESGraspPlanningDialog(QWidget *parent=0);
    ~CMAESGraspPlanningDialog(){}

public slots:
    void planButtonPressed();
};

} // end of namespace cmaes_grasp_planning


#endif
