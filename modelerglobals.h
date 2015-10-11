#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{ 
	// First Lighting control, position and diffusion color
	LIGHT0_X,
	LIGHT0_Y,
	LIGHT0_Z,
	LIGHT0_R,
	LIGHT0_G,
	LIGHT0_B,
	// Second Lighting control, position and diffusion color
	LIGHT1_X,
	LIGHT1_Y,
	LIGHT1_Z,
	LIGHT1_R,
	LIGHT1_G,
	LIGHT1_B,
	// Modeler position control
	XPOS, 
	YPOS, 
	ZPOS, 
	HEIGHT, 
	ROTATE,
	//upperleg control
	LEFT_ULEG_ROTATE,
	LEFT_ULEG_SWAYLR,
	LEFT_ULEG_SWAYFB,
	RIGHT_ULEG_ROTATE,
	RIGHT_ULEG_SWAYLR,
	RIGHT_ULEG_SWAYFB,
	//knee angle control
	LEFT_KNEE,
	RIGHT_KNEE,
	//feet angle control
	//LEFT_FOOT_UD,
	LEFT_FOOT_LR,
	//RIGHT_FOOT_UD,
	RIGHT_FOOT_LR,
	//elbow angle control
	LEFT_ELBOW,
	RIGHT_ELBOW,
	//upperarm rotation
	LEFT_UARM_ROTATE,
	RIGHT_UARM_ROTATE,
	//Make sure this stays at the last
	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))
//CUSTOM: sets the control value
#define SET(controlNum, value) (ModelerApplication::Instance()->SetControlValue(controlNum, value))

#endif