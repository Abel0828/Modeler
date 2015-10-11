/**
 * InverseKinematics.cpp
 * Contains the implementation of inverse kinematics calculation
 * and an sample metric function that operates upon the sample model
 */

#include<exception>
#include"InverseKinematics.h"
using namespace std;

void IKOneStep() {
	//Calculate the derivative using numerical method
	/**
	* The delta value signifying an increment.
	*/
	const float delta = 0.1f;
	const float learningRate = 1.5f;
	//Modify the parameters
	vector<float> gradient;
	//calculate gradient
	const int startPos = LEVEL_OF_DETAIL + 1;
	for (int i = startPos; i < NUMCONTROLS; ++i) {
		//backup parameter i
		float x = VAL(i);
		STEPUP(i);
		float plusCost = IKCostFunction();
		SET(i, x);
		STEPDOWN(i);
		float minusCost = IKCostFunction();
		SET(i, x); //restore parameter
		//calculate
		float deltaY = plusCost - minusCost;
		float derivative = deltaY / (2 * delta);
		gradient.push_back(derivative);
	}
	for (float& x : gradient) x = x * learningRate;
	//subtract the gradient from parameters
	for (int i = startPos; i < NUMCONTROLS; ++i) {
		SET(i, VAL(i) - gradient[i - startPos]);
	}
}

void IKOptimize() {
	const int maxNumIteration = 1000;
	const double epselon = 0.001;
	double lastCost = IKCostFunction(), thisCost = 0;
	for (int i = 0; i < maxNumIteration; ++i) {
		IKOneStep();
		thisCost = IKCostFunction();
		//for debug use
		printf("cost%d: %f\n", i, thisCost);

		//break if the change is small enough
		if (abs(lastCost - thisCost) < epselon) break;
		lastCost = thisCost;
	}
}

double IKCostFunction() {
	//Calculate the cost. Call refreshParameters() to make sure internal control parameters are 
	//up to date with sliders
	//head cost
	Model::m_modelList[HEAD]->refreshParameters();
	Vec3f headPos = Model::m_modelList[HEAD]->getOrigin();
	Vec3f headConstraint(VAL(HEAD_CSTRN_X), VAL(HEAD_CSTRN_Y), VAL(HEAD_CSTRN_Z));
	double headCost = (headPos - headConstraint).length();

	//left hand cost
	Model::m_modelList[LEFTHAND]->refreshParameters();
	Vec3f leftHandPos = Model::m_modelList[LEFTHAND]->getOrigin();
	Vec3f leftHandConstraint(VAL(LHAND_CSTRN_X), VAL(LHAND_CSTRN_Y), VAL(LHAND_CSTRN_Z));
	double leftHandCost = (leftHandPos - leftHandConstraint).length();

	//right hand cost
	Model::m_modelList[RIGHTHAND]->refreshParameters();
	Vec3f rightHandPos = Model::m_modelList[RIGHTHAND]->getOrigin();
	Vec3f rightHandConstraint(VAL(RHAND_CSTRN_X), VAL(RHAND_CSTRN_Y), VAL(RHAND_CSTRN_Z));
	double rightHandCost = (rightHandPos - rightHandConstraint).length();

	//left foot cost
	Model::m_modelList[LEFTFOOT]->refreshParameters();
	Vec3f leftFootPos = Model::m_modelList[LEFTFOOT]->getOrigin();
	Vec3f leftFootConstraint(VAL(LFOOT_CSTRN_X), VAL(LFOOT_CSTRN_Y), VAL(LFOOT_CSTRN_Z));
	double leftFootCost = (leftFootPos - leftFootConstraint).length();

	//right foot cost
	Model::m_modelList[RIGHTFOOT]->refreshParameters();
	Vec3f rightFootPos = Model::m_modelList[RIGHTFOOT]->getOrigin();
	Vec3f rightFootConstraint(VAL(RFOOT_CSTRN_X), VAL(RFOOT_CSTRN_Y), VAL(RFOOT_CSTRN_Z));
	double rightFootCost = (rightFootPos - rightFootConstraint).length();

	return headCost + leftHandCost + rightHandCost + leftFootCost + rightFootCost;
}