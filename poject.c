#pragma config(Sensor, S1,     TouchSensor,    sensorTouch)
#pragma config(Sensor, S2,     SonarSensorRight, sensorSONAR)
#pragma config(Sensor, S3,     SonarSensorLeft, sensorSONAR)
#pragma config(Sensor, S4,     LightSensor,    sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
void orientation (void);

int x = 0;
int y = 0;
int find = 0;
int direction = 1;
/*
1 = north
2 = east
3 = south
4 = west
*/

int forwardCounter = 0;
int tempforcounter = 0;

int templeft;
int minleft;
int tempright;
int minright;
int thresholdValue = 0;

task main()
{
		nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
		nMotorPIDSpeedCtrl[motorC] = mtrSpeedReg;
		int finish = 0;														//when 2 prgram stops
		int turns = 0;


		thresholdValue = 50;

		while(SensorValue(TouchSensor) == 0)
		{
		}

		wait1Msec(100);
		tempright = minright = SensorValue(SonarSensorRight);
		templeft = minleft = SensorValue(SonarSensorLeft);

		while(SensorValue(TouchSensor) == 0)
		{
		}
	/********************************************************************************************/

		while(finish !=2)
		{
			if(forwardCounter == 8 && tempforcounter == 1)
			{
				turnaround();
			}

		if(forwardCounter == 8)
			{
				turnaround();
				tempforcounter = 1;
			}

			if(forwardCounter == 0 && tempforcounter == 1)
			{
				turnaround();
			}

			eraseDisplay();
			nxtDisplayBigStringAt(0, 31, "%d,%d,%d,%d" ,y,x,direction,forwardCounter);

			scan();

			if (find == 2)
			{
				backhome ();
				finish = 2;
			}
			else
            {
                   if(x == 0 && y == 0)
                {
                    forwardsmall ();
                }

                if(SensorValue(LightSensor) < thresholdValue)
                {
                    backwardsmall();

                    if(turns == 0)
                    {
                        right();
                        forwardfull();
                        left();
                        turns++;
                    }
                    else
                    {
                        left();
                        forwardfull();
                        right();
                        turns--;
                    }

                    forwardsmall();
                }
                else
                {
                    forwardfull ();
                }

                if(SensorValue(TouchSensor) != 0 )
                {
                    find++;
                    PlaySound(soundBeepBeep);
                }

                eraseDisplay();
				nxtDisplayBigStringAt(0, 31, "%d,%d,%d,%d" ,y,x,direction,forwardCounter);
			}




		}
}// end main

void orientation (void)
{
	if(direction == 1)
	{
		y++;
	}
	if(direction == 2)
	{
		x++;
	}
	if(direction == 3)
	{
		y--;
	}
	if(direction == 4)
	{
		x--;
	}
}

void left (void)
{
	motor[motorA] = 0;
	motor[motorC] = 0;
	nMotorEncoder[motorA] = 0;//reset
	nMotorEncoder[motorC] = 0;
	nMotorEncoderTarget[motorA] = 180;
	nMotorEncoderTarget[motorC] = -180;
	motor[motorA] = 20;
	motor[motorC] = -20;


	while (nMotorRunState[motorA] != runStateIdle)
	{
		// idle loop
	}

	if(direction == 1)
	{
		direction = 4;
	}
	else
	{
		direction--;
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
	nMotorEncoderTarget[motorA] = 180;
	nMotorEncoderTarget[motorC] = -180;
	motor[motorA] = -20;
	motor[motorC] = 20;


	while (nMotorRunState[motorA] != runStateIdle)
	{
			// idle loop
	}

	if(direction == 4)
	{
		direction = 1;
	}
	else
	{
		direction++;
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
	nMotorEncoderTarget[motorA] = 290;
	nMotorEncoderTarget[motorC] = 290;

	motor[motorA] = 20;
	motor[motorC] = 20;

	while (nMotorRunState[motorA] != runStateIdle)
	{
		// idle loop
	}

	orientation();

	if(direction == 1)
    {
        forwardCounter++;
    }
    if(direction == 3)
    {
        forwardCounter--;
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
	nMotorEncoderTarget[motorA] = 75;
	nMotorEncoderTarget[motorC] = 75;
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
	nMotorEncoderTarget[motorA] = -75;
	nMotorEncoderTarget[motorC] = -75;
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
	int counter = 0;
	int touch = 0;

	if (y == 1|| y == 2 || y == 5 || y == 8)
	{
		left();
		forwardsmall();
		touch = SensorValue(TouchSensor);
		while(touch == 0)
		{
			forwardfull();
			counter++;
			touch = SensorValue(TouchSensor);
			if(touch != 0)
			{
				find++;
				PlaySound(soundBeepBeep);
			}
			if(SensorValue(LightSensor) < thresholdValue)
			{
				touch = 1;
			}

			if(counter == 3)
			{
				touch = 1;
			}

			if(touch != 0)
			{
				backwardsmall();
				turnaround();
				while(counter != 0)
				{
					counter--;
					forwardfull();
				}
				left();
			}

		 }
	}


	if (x == 0 && y == 0)
	{
		forwardsmall();
		left();
		forwardfull ();
		if (SensorValue(TouchSensor) != 0)
		{
			find++;
			PlaySound(soundBeepBeep);
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
		if(SensorValue(TouchSensor) != 0)
		{
			find++;
			PlaySound(soundBeepBeep);
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
		backwardsmall();
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
		if(SensorValue(TouchSensor) != 0)
		{//found and go back to line
			find++;
			PlaySound(soundBeepBeep);
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
			if(SensorValue(TouchSensor) != 0)
			{
				find++;
				PlaySound(soundBeepBeep);
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
				if(SensorValue(TouchSensor) != 0)
				{
					find++;
					PlaySound(soundBeepBeep);
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
        forwardfull();
        left();
        forwardfull();
        forwardfull();
        left();
        forwardfull();
        if(SensorValue(TouchSensor) != 0)
        {
            find++;
            PlaySound(soundBeepBeep);
            turnaround();
            forwardfull();
            right();
            forwardfull();
            forwardfull();
            right();
            forwardfull();
            turnaround();
        }
        else
        {
            right();
            forwardfull();
            if(SensorValue(TouchSensor) != 0)
            {
                find++;
                PlaySound(soundBeepBeep);
                turnaround();
                forwardfull();
                left();
                forwardfull();
                right();
                forwardfull();
                forwardfull();
                right();
                forwardfull();
                turnaround();
            }
            else
            {
                forwardfull();
                if(SensorValue(TouchSensor) != 0)
                {
                    find++;
                    PlaySound(soundBeepBeep);
                }
                turnaround();
                forwardfull();
                forwardfull();
                left();
                forwardfull();
                right();
                forwardfull();
                forwardfull();
                right();
                forwardfull();
                turnaround();
            }
        }
	}

	if(x == 0 && y == 6)
	{
        turnaround();
        forwardfull();
        right();
        forwardfull();
        forwardfull();
        forwardfull();
        right();
        forwardfull();
        if(SensorValue(TouchSensor) != 0)
        {
            find++;
            PlaySound(soundBeepBeep);
        }
        turnaround();
        forwardfull();
        left();
        forwardfull();
        forwardfull();
        forwardfull();
        left();
        forwardfull();
	}

	if (x == 0 && y == 7)
	{
        left();
        forwardfull();
        if(SensorValue(TouchSensor) != 0)
        {
            find++;
            PlaySound(soundBeepBeep);
            turnaround();
            left();
        }
        else
        {
           turnaround();
            forwardfull();
            right();
            forwardfull();
            forwardfull();
            right();
            forwardfull();
            forwardfull();
            forwardfull();
            right();
            forwardfull();
            forwardfull();
            if(SensorValue(TouchSensor) != 0)
            {
                find++;
                PlaySound(soundBeepBeep);
            }
            turnaround();
            forwardfull();
            forwardfull();
            left();
            forwardfull();
            forwardfull();
            forwardfull();
            left();
            forwardfull();
            forwardfull();
        }
	}

}

void findingright (void)
{

	int counter = 0;
	int touch = 0;

	if (y == 0|| y == 2 || y == 3 || y == 4 || y == 5 || y == 7 || y == 8)
	{
		right();
		forwardsmall();
		touch = SensorValue(TouchSensor);
		while(touch == 0)
		{
			forwardfull();
			counter++;
			touch = SensorValue(TouchSensor);
			if(touch != 0)
			{
				find++;
				PlaySound(soundBeepBeep);
			}
			if(SensorValue(LightSensor) < thresholdValue)
			{
				touch = 1;
			}

			if(counter == 3)
			{
				touch = 1;
			}


			if(touch != 0)
			{
				backwardsmall();
				turnaround();
				while(counter != 0)
				{
					counter--;
					forwardfull();
				}
				right();
			}

		 }
	}

	if (x == 0 && y == 1)
	{
		right();
		forwardfull();
		if(SensorValue(TouchSensor) != 0)
		{
			find++;
			PlaySound(soundBeepBeep);
			turnaround();
			forwardfull();
			right();
		}
		else
		{
			left();
			forwardfull();
			right();
			forwardfull();
			forwardfull();
			right();
			forwardfull();
			if(SensorValue(TouchSensor) != 0)
			{
				find++;
				PlaySound(soundBeepBeep);
			}
			turnaround();
			forwardfull();
			left();
			forwardfull();
			forwardfull();
			left();
			forwardfull();
			right();
			forwardfull();
			right();
		}
	}

	if(x == 0 && y == 6)
	{
		turnaround();
		forwardfull();
		left();
		forwardfull();
		forwardfull();
		left();
		forwardfull();
		if(SensorValue(TouchSensor) != 0)
		{
			find++;
			PlaySound(soundBeepBeep);
			turnaround();
			forwardfull();
			right();
			forwardfull();
			forwardfull();
			right();
			forwardfull();
		}
		else
		{
			right();
			forwardfull();
			if(SensorValue(TouchSensor) != 0)
			{
				find++;
				PlaySound(soundBeepBeep);
			}
			turnaround();
			forwardfull();
			left();
			forwardfull();
			right();
			forwardfull();
			forwardfull();
			right();
			forwardfull();
		}
	}
}

void scan (void)
{


	//finding object on left
	if(SensorValue(SonarSensorLeft) < 255)
	{
		backwardsmall();
		findingleft ();
		forwardsmall();
	}

	//finding object on right
	if(SensorValue(SonarSensorRight) < 255)
	{
		backwardsmall();
		findingright ();
		forwardsmall();
	}
}

void backhome (void)
{
	if(x==0)
	{
		while(direction!=3)
			{
				left();
			}
			while(y!=0)
			{
				forwardfull();
			}
	}
	else
	{
		if(x>0)
		{
			while(direction!=4)
			{
				left();
			}
			while(x!=0)
			{
				forwardfull();
			}
			while(direction!=3)
			{
				left();
			}
			while(y!=0)
			{
				forwardfull();
			}
		}
		else
		{
			while(direction!=2)
			{
				right();
			}
			while(x!=0)
			{
				forwardfull();
			}
			while(direction!=3)
			{
				right();
			}
			while(y!=0)
			{
				forwardfull();
			}
		}
	}
}
