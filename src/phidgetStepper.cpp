
#include "phidgetStepper.h"

string positionAsString;


//--------------------------------------------------------------
void motor::setup(string _filename, bool verbose)
{
	ofxXmlSettings XML;
	XML.loadFile(_filename);

	id 			   = XML.getValue("STEPPER:ID", 0);
    serialNumber   = XML.getValue("STEPPER:SN", 0);
	isRemote	   = XML.getValue("STEPPER:REMOTE", 0);
    hubPort        = XML.getValue("STEPPER:HUBPORT", -1);

	velocityFromConfigFile	  	 = XML.getValue("STEPPER:VEL", 0);
	accelerationFromConfigFile   = XML.getValue("STEPPER:ACC", 0);

	minPosition = XML.getValue("STEPPER:MIN", -100);
	maxPosition = XML.getValue("STEPPER:MAX", 100);

	if(verbose)
	{
		cout << "setting motor : " 
			<< id << " " 
			<< "\nsn : " << serialNumber 
			<< "\nisRemote : " << isRemote
			<< "\nhubPort : " << hubPort
			<< "\nvelocity : " << velocityFromConfigFile
			<< "\nacceleration : " << accelerationFromConfigFile
			<< "\nminPosition : " << minPosition
			<< "\nmaxPosition : " << maxPosition
			<< endl; 
	}

	setupStepper();
	setVelocity(velocityFromConfigFile);
	setAcceleration(accelerationFromConfigFile);

}

//--------------------------------------------------------------
void motor::goToPosition(float _pos)
{
	if(_pos >= minPosition && _pos <= maxPosition)
		PhidgetStepper_setTargetPosition(ch, _pos);
	else
		cout << "WARNING : position out of range for motor " << id << endl;
}

//--------------------------------------------------------------
void motor::setupStepper()
{

	PhidgetStepper_create(&ch);

	if(isRemote)
	{
		Phidget_setIsRemote((PhidgetHandle)ch, 1);		
		PhidgetNet_enableServerDiscovery(PHIDGETSERVER_DEVICEREMOTE);	
	}
	else
	{
		Phidget_setDeviceSerialNumber((PhidgetHandle)ch, serialNumber);
		Phidget_setHubPort((PhidgetHandle)ch,hubPort);
		Phidget_setChannel((PhidgetHandle)ch, 0); //devrait toujours etre 0 (une seule entrée/sortie sur la carte)
	}
	

	Phidget_setOnAttachHandler((PhidgetHandle)ch, onAttachHandler, NULL);
	Phidget_setOnDetachHandler((PhidgetHandle)ch, onDetachHandler, NULL);
	Phidget_setOnErrorHandler((PhidgetHandle)ch, onErrorHandler, NULL);
	PhidgetStepper_setOnPositionChangeHandler(ch, onPositionChangeHandler, NULL);
	PhidgetReturnCode prc = Phidget_openWaitForAttachment((PhidgetHandle)ch, 5000);

	if (prc != EPHIDGET_OK) {
		cout << "error opening motor : " << id << endl;
	}
	else {
		cout << "motor " << id << " attached" << endl;
	}
}


//--------------------------------------------------------------
void motor::cleanExit()
{   
	PhidgetStepper_setOnPositionChangeHandler(ch, NULL, NULL);
	
	printf("Cleaning up...\n");
	Phidget_close((PhidgetHandle)ch);
	
	PhidgetStepper_delete(&ch);
}

//--------------------------------------------------------------
void motor::setVelocity(double _vel)
{
	PhidgetStepper_getMinVelocityLimit(ch, &minVelocity);
	PhidgetStepper_getMaxVelocityLimit(ch, &maxVelocity);

	if(_vel < minVelocity || _vel > maxVelocity)
	{
		cout << "specified velocity for motor " << id << " is not compatible with the hardware !" << endl;
		return;
	}
	else
	{
		PhidgetStepper_setVelocityLimit(ch, _vel);
	}
}

//--------------------------------------------------------------
void motor::setAcceleration(double _acc)
{
	PhidgetStepper_getMinAcceleration(ch, &minAccel);
	PhidgetStepper_getMaxAcceleration(ch, &maxAccel);

	if(_acc < minAccel || _acc > maxAccel)
	{
		cout << "specified acceleration for motor " << id << " is not compatible with the hardware !" << endl;
		return;
	}
	else
	{
		PhidgetStepper_setAcceleration(ch, _acc);
	}
}

//--------------------------------------------------------------
ofParameterGroup motor::setupGui()
{
	ofParameterGroup pg;
	
	pg.add(position.set("position", 0, minPosition, maxPosition));
	pg.add(velocity.set("velocity", velocityFromConfigFile, minVelocity+1, maxVelocity-1));
	pg.add(acceleration.set("acceleration", accelerationFromConfigFile, minAccel+1, maxAccel-1));

	return pg;
}

//--------------------------------------------------------------
void CCONV onAttachHandler(PhidgetHandle ph, void *ctx) {
	PhidgetReturnCode prc; 
	Phidget_DeviceClass deviceClass;
	const char* channelClassName;
	int32_t serialNumber;
	int32_t hubPort;
	int32_t channel;

	printf("\nAttach Event: ");

	Phidget_getDeviceSerialNumber(ph, &serialNumber);
	Phidget_getChannel(ph, &channel);
	Phidget_getChannelClassName(ph, &channelClassName);
	Phidget_getDeviceClass(ph, &deviceClass);

	if (deviceClass == PHIDCLASS_VINT) {
		Phidget_getHubPort(ph, &hubPort);

		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Hub Port: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, hubPort, channel);
	} else { //Not VINT
		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, channel);
	}

	cout << "Setting DataInterval to 100 ms" << endl;
	PhidgetStepper_setDataInterval((PhidgetStepperHandle)ph, 100);
	PhidgetStepper_setEngaged((PhidgetStepperHandle)ph, 1);
}


//--------------------------------------------------------------
void CCONV onDetachHandler(PhidgetHandle ph, void *ctx) {
	PhidgetReturnCode prc; 
	Phidget_DeviceClass deviceClass;
	const char* channelClassName;
	int32_t serialNumber;
	int32_t hubPort;
	int32_t channel;


	printf("\nDetach Event: ");

	Phidget_getDeviceSerialNumber(ph, &serialNumber);
	Phidget_getChannel(ph, &channel);
	Phidget_getChannelClassName(ph, &channelClassName);
	Phidget_getDeviceClass(ph, &deviceClass);

	if (deviceClass == PHIDCLASS_VINT) {
		Phidget_getHubPort(ph, &hubPort);

		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Hub Port: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, hubPort, channel);
	} else { //Not VINT
		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, channel);
	}
}


//--------------------------------------------------------------
void CCONV onErrorHandler(PhidgetHandle ph, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {

	fprintf(stderr, "[Phidget Error Event] -> %s (%d)\n", errorString, errorCode);
}

//--------------------------------------------------------------
void CCONV onPositionChangeHandler(PhidgetStepperHandle ph, void *ctx, double position) {

	positionAsString = ofToString(position);
}

//--------------------------------------------------------------
string motor::getPositionAsString()
{
	return positionAsString;
}