#ifndef _CMAES_GRASP_PLANNING_DIALOG_H_
#define _CMAES_GRASP_PLANNING_DIALOG_H_

#include <QDialog>
#include "ui_dialog.h"
#include "cmaes_grasp_planning/optimization.h"

namespace cmaes_grasp_planning 
{

class CMAESGraspPlanningDialog : public QDialog, public Ui::CMAESGraspPlanningDialogBase
{
    Q_OBJECT
private:
    CMAESParams params_;

public:
    CMAESGraspPlanningDialog(QWidget *parent=0);
    ~CMAESGraspPlanningDialog(){}
    bool parseXML(const QString & filename);

public slots:
    void loadConfigButtonPressed();
    void planButtonPressed();
};

} // end of namespace cmaes_grasp_planning


#endif
