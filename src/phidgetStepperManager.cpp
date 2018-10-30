#include "phidgetStepperManager.h"

void phidgetStepperManager::setup(string _filename)
{

	//JSON
	ofFile file(_filename);
	if(file.exists())
	{
		cout << "\nloading Motors.json" << endl;
		file >> settings;
		
		for(auto & elements: settings)
		{
			if(!elements.empty())
			{
				cout << "nb d'elements " << elements.size() << endl;
				for(int i=0; i<elements.size(); i++)
				{
                    motor temp;

                    temp.name                       = elements[i]["NAME"];
                    temp.id                         = elements[i]["ID"];
                    temp.serialNumber               = elements[i]["SN"] ;
                    temp.isRemote                   = elements[i]["REMOTE"] ;
                    temp.hubPort                    = elements[i]["HUBPORT"] ;
                    temp.velocityFromConfigFile     = elements[i]["VEL"] ;
                    temp.accelerationFromConfigFile = elements[i]["ACC"] ;
                    temp.minPosition                = elements[i]["MIN"] ;
                    temp.maxPosition                = elements[i]["MAX"] ;
                    temp.vitrineId                  = elements[i]["VITRINE"] ;

                    motors.push_back(temp);
				}
			}
		}
	}
	
    //setup motors : 
    for(int i=0; i<motors.size();i++)
    {
        motors[i].setup(true);
    }


};


void phidgetStepperManager::setupGui()
{
    guiMotors.setup("motors");
    for(int i=0; i<motors.size();i++)
    {
        guiMotors.add(motors[i].setupGui());
    }
    guiMotors.minimizeAll();
}