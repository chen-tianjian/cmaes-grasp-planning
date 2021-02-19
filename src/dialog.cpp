#include "cmaes_grasp_planning/dialog.h"
#include "tinyxml.h"
#include <iostream>
#include <QString>
#include <QFileDialog>

namespace cmaes_grasp_planning {

std::vector<double> parseMultiEntries(const QString & num_w_space)
{
    QStringList num_str_list = num_w_space.split(" ");
    bool ok;
    std::vector<double> num_vec (num_str_list.length());
    for(int i=0 ; i < num_str_list.length() ; i++)
    {
        num_vec[i] = (num_str_list[i]).toDouble(&ok);
        if (!ok) {
            std::cerr << "Failed to parse input values" << std::endl;
            return {};
        }
    }
    return num_vec;
}

double parseSingleEntry(const QString & num_str)
{
    bool ok;
    double num = num_str.toDouble(&ok);
    if (!ok) {
        std::cerr << "Failed to parse input values" << std::endl;
        return 0;
    }
    return num;
}


CMAESGraspPlanningDialog::CMAESGraspPlanningDialog(QWidget *parent):QDialog(parent)
{
    setupUi(this);
    QObject::connect(load_config_button, SIGNAL(clicked()),this,SLOT(loadConfigButtonPressed()));
    QObject::connect(plan_button, SIGNAL(clicked()),this,SLOT(planButtonPressed()));
}


bool CMAESGraspPlanningDialog::parseXML(const QString & filename)
{
    TiXmlDocument doc(filename);
    if (doc.LoadFile() == false)
    {
        std::cerr << "Failed to load xml file" << std::endl;
        return false;
    }
    const TiXmlElement * root = doc.RootElement();
    const TiXmlElement * child = root->FirstChildElement();
    while (child != NULL) 
    {
        QString element_type = child->Value();

        if (element_type == "lb")
        {
            QString element_name = child->GetText();
            params_.lb = parseMultiEntries(element_name);
        }
        else if (element_type == "ub")
        {
            QString element_name = child->GetText();
            params_.ub = parseMultiEntries(element_name);
        }
        else if (element_type == "x0")
        {
            QString element_name = child->GetText();
            params_.x0 = parseMultiEntries(element_name);
        }
        else if (element_type == "sigma0")
        {
            QString element_name = child->GetText();
            params_.sigma0 = parseSingleEntry(element_name);
        }
        else if (element_type == "lambda")
        {
            QString element_name = child->GetText();
            params_.lambda = int(parseSingleEntry(element_name));
        }
        else if (element_type == "xtol")
        {
            QString element_name = child->GetText();
            params_.xtol = parseSingleEntry(element_name);
        }
        else if (element_type == "ftol")
        {
            QString element_name = child->GetText();
            params_.ftol = parseSingleEntry(element_name);
        }
        else if (element_type == "max_iter")
        {
            QString element_name = child->GetText();
            params_.max_iter = int(parseSingleEntry(element_name));
        }
        else if (element_type == "max_feval")
        {
            QString element_name = child->GetText();
            params_.max_feval = int(parseSingleEntry(element_name));
        }
        else if (element_type == "render")
        {
            QString element_name = child->GetText();
            if (element_name == "false")
            {
                params_.render = false;
            }
            else if (element_name == "true")
            {
                params_.render = true;
            }
            else 
            {
                std::cerr << "XML element unrecognized" << std::endl;
                return false;
            }
        }
        else if (element_type == "best_grasp")
        {
            QString element_name = child->GetText();
            if (element_name == "latest")
            {
                params_.render = false;
            }
            else if (element_name == "seen")
            {
                params_.render = true;
            }
            else
            {
                std::cerr << "XML element unrecognized" << std::endl;
                return false;
            }
        }
        
        else
        {
            std::cerr << "XML element unrecognized" << std::endl;
            return false;
        }

        child = child->NextSiblingElement();
    }
    return true;
}


void CMAESGraspPlanningDialog::loadConfigButtonPressed()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", "../config", "XML files (*.xml)");
    bool ok = CMAESGraspPlanningDialog::parseXML(filename);
    if (!ok)
    {
        std::cerr << "Failed to load the XML file" << std::endl;
    }
    plan_button->setEnabled(true);

}

void CMAESGraspPlanningDialog::planButtonPressed()
{
    CMAESGraspPlanningOptimization opt(params_);
    opt.optimize();
}


} // end of namespace cmaes_grasp_planning