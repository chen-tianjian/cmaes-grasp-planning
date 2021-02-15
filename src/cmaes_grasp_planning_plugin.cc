#include "cmaes_grasp_planning/cmaes_grasp_planning_dialog.h"
#include "cmaes_grasp_planning/cmaes_grasp_planning_plugin.h"

namespace cmaes_grasp_planning {

CMAESGraspPlanningPlugin::~CMAESGraspPlanningPlugin()
{
  delete dlg_;
}

int CMAESGraspPlanningPlugin::init(int, char**)
{
  dlg_ = new CMAESGraspPlanningDialog();
  dlg_->setAttribute(Qt::WA_ShowModal, false);
  dlg_->show();  
  return 0;
}

int CMAESGraspPlanningPlugin::mainLoop()
{
  return 0;
}

} //end of namespace cmaes_grasp_planning

extern "C" Plugin* createPlugin() {
  return new cmaes_grasp_planning::CMAESGraspPlanningPlugin();
}

extern "C" std::string getType() {
  return "CMAES grasp planning";
}