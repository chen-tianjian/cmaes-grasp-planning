#ifndef _CMAES_GRASP_PLANNING_PLUGIN_H_
#define _CMAES_GRASP_PLANNING_PLUGIN_H_

#include <stddef.h>

#include "graspit/plugin.h"

namespace cmaes_grasp_planning {

class CMAESGraspPlanningDialog;

class CMAESGraspPlanningPlugin : public Plugin
{
private:
    CMAESGraspPlanningDialog *dlg_;
public:  
    CMAESGraspPlanningPlugin() : dlg_(NULL) {}
    ~CMAESGraspPlanningPlugin();
    int init(int argc, char **argv);
    int mainLoop();
};

}
#endif