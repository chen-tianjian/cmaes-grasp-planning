#include "cmaes_grasp_planning/cmaes_grasp_planning_dialog.h"

#include <iostream>

#include <QFileDialog>
#include <QString>

namespace cmaes_grasp_planning {

CMAESGraspPlanningDialog::CMAESGraspPlanningDialog(QWidget *parent):QDialog(parent)
{
    setupUi(this);
    QObject::connect(plan_button_, SIGNAL(clicked()),this,SLOT(planButtonPressed()));
}


void CMAESGraspPlanningDialog::planButtonPressed()
{
    std::cout << "button pressed!" << std::endl;
}

} // end of namespace cmaes_grasp_planning