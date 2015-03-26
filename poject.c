
#pragma config(Sensor, S1, TouchSensor, sensorTouch)
#pragma config(Sensor, S2, SonarSensorRight, sensorSONAR)
#pragma config(Sensor, S3, SonarSensorLeft, sensorSONAR)
#pragma config(Sensor, S4, LightSensor, sensorLightActive)

//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//
void left (void);
void right (void);
void turnaround (void);
void forwardfull (void);
void forwardsmall (void);
void backwardsmall (void);
void findingleft (void);
void findingright (void);
void scan (void);
void backhome (void);

int x = 0;
int y = 0;
int find = 0;

task main()
{
		nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
		nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
		int countValue = 0;												//look if there is black cell
		int lineCounter = 0;											//counts lines
		int lightValue = 0;												//light value
		int darkValue = 0;												//dark value
		int thresholdValue = 0;
		int forwardLines = 7;											//number of lines forward
		int finish = 0;														//when 5 prgram stops


	/**************************************************************************************/
		if (1==1)// only to hide for clearly code
		{
		while(SensorValue(touchSensor) = 0)
		{
		}

		lightValue = SensorValue(lightSensor);

		while(SensorValue(touchSensor) == 0)
		{
		}

		darkValue = SensorValue(lightSensor);

		thresholdValue = (lightValue + darkValue)/2;

		while(SensorValue(touchSensor) == 0)
		{
		}
		}
	/********************************************************************************************/

		while(finish !=5)
		{
			scan ();
			if(x == 0 && y == 0)
			{
				forwardsmall ();
			}

			if(SensorValue(LightSensor) < thresholdValue)
			{
				backwardsmall();
				if (x == 0 && y == 2)
				{
					right ();
					forwardfull ();
					left ();
					forwardsmall ();
					x = x + 1;
				}

				if (x == 1 && y == 5)
				{
					left ();
					forwardfull ();
					right ();
					forwardsmall ();
					x = x - 1;
				}

			}
			forwardfull ();
			y = y + 1;

			if (find = 2)
			{
				backhome ();
				finish = 5;
			}
		}
}// end main


void left (void)
{
	motor[motorA] = 0;
	motor[motorC] = 0;
	nMotorEncoder[motorA] = 0;//reset
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorA] = 185;
	nMotorEncoderTarget[motorC] = -185;
	motor[motorA] = 20;
	motor[motorC] = -20;


	while (nMotorRunState[motorA] != runStateIdle)
	{
		// idle loop
	}

	motor[motorA] = 0;
	motor[motorC] = 0;
}


void right (void)
{
	motor[motorA] = 0;
	motor[motorC] = 0;
	nMotorEncoder[motorA] = 0;//reset
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorA] = 185;
	nMotorEncoderTarget[motorC] = -185;
	motor[motorA] = -20;
	motor[motorC] = 20;


	while (nMotorRunState[motorA] != runStateIdle)
	{
			// idle loop
	}

	motor[motorA] = 0;
	motor[motorC] = 0;
}

void turnaround(void)
{
	right ();
	right ();
}



void forwardfull (void)
{
	nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;

	motor[motorA] = 0;
	motor[motorC] = 0;

	nMotorEncoder[motorA] = 0;//reset
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorA] = 280;
	nMotorEncoderTarget[motorC] = 280;

	motor[motorA] = 40;
	motor[motorC] = 40;

	while (nMotorRunState[motorA] != runStateIdle)
	{
		// idle loop
	}

	motor[motorA] = 0;
	motor[motorC] = 0;
}

void forwardsmall (void)
{
	nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
	motor[motorA] = 0;
	motor[motorC] = 0;
	nMotorEncoder[motorA] = 0;//reset
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorA] = 80;
	nMotorEncoderTarget[motorC] = 80;
	motor[motorA] = 20;
	motor[motorC] = 20;

	while (nMotorRunState[motorA] != runStateIdle)
	{
		// idle loop
	}

	motor[motorA] = 0;
	motor[motorC] = 0;
}

void backwardsmall (void)
{
	nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
	motor[motorA] = 0;
	motor[motorC] = 0;
	nMotorEncoder[motorA] = 0;//reset
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorA] = -80;
	nMotorEncoderTarget[motorC] = -80;
	motor[motorA] = -20;
	motor[motorC] = -20;

	while (nMotorRunState[motorA] != runStateIdle)
	{
		// idle loop
	}

	motor[motorA] = 0;
	motor[motorC] = 0;
}
//remember to count x and y
void findingleft (void)
{
	left ();
	if (x == 0 && y == 0)
	{
		forwardfull ();
		if (SensorValue(touchSensor) != 0)
		{
			find++;
			turnaround ();
			forwardfull ();
			left ();
		}
		else
		{
		right ();
		forwardfull ();
		left ();
		forwardfull ();
		forwardfull ();
		left ();
		forwardfull ();
		if(sensorValue(touchSensor) != 0)
		{
			find++;
		}
		turnaround ();
		forwardfull ();
		right ();
		forwardfull ();
		forwardfull ();
		right ();
		forwardfull ();
		left ();
		forwardfull ();
		left ();
		}
	}

	if (x == 1 && y == 3)
	{
		turnaround ();
		forwardfull ();
		right();
		forwardfull ();
		forwardfull ();
		right();
		forwardfull ();
		if(sensorValue(touchSensor) != 0)
		{//found and go back to line
			find++;
			turnaround ();
			forwardfull ();
			left ();
			forwardfull ();
			forwardfull ();
			left ();
			forwardfull ();
		}
		else
		{
			left ();
			forwardfull ();
			if(sensorValue(touchSensor) != 0)
			{
				find++;
				turnaround ();
				forwardfull ();
				right ();
				forwardfull ();
				left ();
				forwardfull ();
				forwardfull ();
				left ();
				forwardfull ();
			}
			else
			{
				forwardfull ();
				if(sensorValue(touchSensor) != 0)
				{
					find++;
				}
				turnaround ();
				forwardfull ();
				forwardfull ();
				right ();
				forwardfull ();
				left ();
				forwardfull ();
				forwardfull ();
				left ();
				forwardfull ();
			}

		}
	}
	// finish it
	if (x == 1 && y == 4)
	{

	}

	if(x == 0 && y == 6)
	{

	}

	if (x == 0 && y == 7)
	{

	}

}

void findingright (void)
{
	if (x == 0 && y == 1)
	{

	}

	if(x == 0 && y == 6)
	{

	}
}

void scan (void)
{
	//finding object on left
	if(SensorValue(SonarSensorLeft) < 255)
	{
		findingleft ();
	}

	//finding object on right
	if(SensorValue(SonarSensorRight) < 255)
	{
		findingright ();
	}
}

void backhome (void)
{

}
