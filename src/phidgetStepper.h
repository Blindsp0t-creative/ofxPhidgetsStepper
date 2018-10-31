
//standard libs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <phidget22.h>
#include "ofxXmlSettings.h"


//OF
#include "ofMain.h"

using namespace std;

void CCONV onAttachHandler(PhidgetHandle ph, void *ctx);
void CCONV onDetachHandler(PhidgetHandle ph, void *ctx);
void CCONV onErrorHandler(PhidgetHandle ph, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString);
void CCONV onPositionChangeHandler(PhidgetStepperHandle ph, void *ctx, double position);


class motor
{  
    
public:

    int     id;
    string  name ;
    int     vitrineId;

    void setup(bool verbose);
    void goToPosition(float _pos);

    ofParameterGroup setupGui();
    //gui parameters
        ofParameter<double> position;
        ofParameter<double> velocity;
        ofParameter<double> acceleration;


    void setVelocity(double _vel);
    void setAcceleration(double _acc);

    string getPositionAsString();

    void setSerialNumber(int _sn);
    void setHubPort(int _port);
    void setupStepper();
    void cleanExit();

        //phidgets ojects
            PhidgetStepperHandle ch = NULL;
	    PhidgetReturnCode prc; 

        //motor properties to be read from XML
            int serialNumber;
            int isRemote;
            int hubPort;
            double velocityFromConfigFile;
            double accelerationFromConfigFile;

            double minAccel, maxAccel, minVelocity, maxVelocity;

            double minPosition;
            double maxPosition;


};
