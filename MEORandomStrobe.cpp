/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright � 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <MEORandomStrobe.h>

MEORandomStrobe::MEORandomStrobe(MEOG35& g35, uint8_t pattern) : MEOLightProgram(g35, pattern), preFill_(false), strobe_(true), wait_(25), noAtATime_(1), colorMain_(COLOR(0,0,4)), colorFlash_(COLOR(15,15,15)), rainbowFlash_(false), rainbowMain_(false), rainbowFrame_(false), step_(0), myBulb_(0), pattern_(pattern)
{
}

//ToDo: reduce brightness of rainbowMain_ colour to increase contrast

uint32_t MEORandomStrobe::Do()
{
    switch (pattern_ % 11)
    {
    case 0: //Black - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,0);
        colorFlash_ = COLOR(15,15,15);
		noAtATime_ = 1;
		wait_ = 25;
        break;
    case 1: //Blue - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,4);
        colorFlash_ = COLOR(15,15,15);
		noAtATime_ = 1;
		wait_ = 25;
        break;
    case 2: //Red - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(4,0,0);
        colorFlash_ = COLOR(15,15,15);
		noAtATime_ = 1;
		wait_ = 25;
        break;
    case 3: //Green - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,4,0);
        colorFlash_ = COLOR(15,15,15);
		noAtATime_ = 1;
		wait_ = 25;
        break;
    case 4: //Black - rainbow flash - all bulbs of single colour before change
        rainbowMain_ = false;
        rainbowFlash_ = true;
        rainbowFrame_ = true;
        colorMain_ = COLOR(0,0,0);
		noAtATime_ = 5;
		wait_ = 25;
        break;
    case 5: //Black - rainbow flash - colour changes with each bulb flash
        rainbowMain_ = false;
        rainbowFlash_ = true;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,0);
		noAtATime_ = 5;
		wait_ = 25;
        break;
    case 6:  //Rainbow backround - white flash
        rainbowMain_ = true;
        rainbowFlash_ = false;
        rainbowFrame_ = true;
        colorFlash_ = COLOR(15,15,15);
		noAtATime_ = 5;
		wait_ = 25;
        break;
    case 7: //Multi-coloured background - white flash
        rainbowMain_ = true;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorFlash_ = COLOR(15,15,15);
		noAtATime_ = 2;
		wait_ = 25;
        break;
    case 8:  //red backround - blue flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(4,0,0);
        colorFlash_ = COLOR(0,0,15);
		noAtATime_ = 5;
		wait_ = 25;
        break;
    case 9: //blue backround - red flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,4);
        colorFlash_ = COLOR(15,0,0);
		noAtATime_ = 5;
		wait_ = 25;
		break;
	case 10: //warm white background - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR_WARMWHITE;
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 2;
		wait_ = 60;
    }


    ////// This commented out code works, but ideally needs to be outside this class and passed in, because as is the random sequence changes so it's no longer non-repeating
    ////// I've no idea how to do that, so I'm replacing with pre-generated random arrays
    ////// and a choice between 50 / 100 bulbs
    //int myBulbs[light_count_];
    //int myBulb;
    //myBulb = 0;
    //// Initialise myBulbs[] to an ordered range - i.e. myBulbs[0] = 0, myBulbs[1] = 1 etc...
    //for (int range = 0; range < light_count_; range++)
    //{
    //	myBulbs[range] = range;
    //}
    //// Random shuffle (note this will always be the same - maybe can re-seed with last number of shuffle?)
    //// so, myBulbs[0]=38, myBulbs[1]=13.. etc.. for example
    //for (int shuffle = 0; shuffle < light_count_ - 1; shuffle++)
    //{
    //	int myrand = shuffle + (rand() % (light_count_ - shuffle));
    //	int save = myBulbs[shuffle];
    //	myBulbs[shuffle] = myBulbs[myrand];
    //	myBulbs[myrand] = save;
    //}
    //srand(myBulbs[0]); //re-seed for next time
    ////// <<<

    ///// Replacement pre-defined random sequence of bulbs - comment this out, if uncommenting above
    // If you have different amounts of bulbs, you'll have to create your own non-repeating random sequences.
    int myBulbs050[100]= {3, 15, 49, 0, 41, 26, 5, 48, 29, 46, 34, 24, 18, 43, 28, 2, 9, 44, 39, 19, 16, 35, 42, 36, 38, 37, 20, 14, 32, 10, 47, 11, 8, 31, 13, 25, 7, 22, 6, 30, 23, 4, 12, 17, 33, 27, 40, 45, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int myBulbs100[100]= {85, 53, 88, 71, 6, 32, 91, 79, 15, 62, 80, 7, 28, 66, 27, 16, 23, 19, 54, 95, 0, 47, 40, 44, 2, 36, 31, 51, 48, 38, 87, 11, 70, 33, 56, 34, 92, 30, 5, 1, 78, 86, 84, 98, 12, 69, 77, 43, 97, 8, 94, 58, 55, 74, 4, 82, 99, 72, 20, 63, 29, 60, 89, 93, 45, 75, 13, 83, 67, 25, 21, 42, 52, 9, 49, 17, 41, 37, 50, 81, 96, 39, 46, 14, 35, 18, 76, 73, 24, 64, 10, 61, 3, 65, 57, 68, 26, 22, 59, 90};
    int myBulbs[100];
    //int myBulb;
    if (light_count_ == 50)
    {
        memcpy(myBulbs, myBulbs050, sizeof(myBulbs));
    }
    else     //assume 100 bulbs
    {
        memcpy(myBulbs, myBulbs100, sizeof(myBulbs));
    }
    ////// <<<


    // pre-fill with background colour if flag set, and first step in
    if (preFill_)
    {
        preFill_ = false;
        if (rainbowMain_)
        {
            g35_.fill_color(0, light_count_, MEOG35::MAX_INTENSITY, MEORandomStrobe::Wheel((step_ + 24) % 48));
        }
        else
        {
            g35_.fill_color(0, light_count_, MEOG35::MAX_INTENSITY, colorMain_);
        }

    }

    //turn on (set to colorFlash) and off (set to colorMain) the random bulbs
    //myBulb = 0;
    //do
    //{
    int simultan = 0;
    do
    {
        if (rainbowFlash_)
        {
            g35_.fill_color(myBulbs[myBulb_], 1, MEOG35::MAX_INTENSITY, MEORandomStrobe::Wheel(step_ % 48));
        }
        else
        {
            g35_.fill_color(myBulbs[myBulb_], 1, MEOG35::MAX_INTENSITY, colorFlash_);
        }

        myBulb_++;
        simultan++;
    }
    while (simultan < noAtATime_);
    delay(wait_);

    if (strobe_) //whether to keep the bulbs on or turn off
    {
        myBulb_ = myBulb_ - noAtATime_; //put back to where was before last do loop
        simultan = 0;
        do
        {
            if (rainbowMain_)
            {
                g35_.fill_color(myBulbs[myBulb_], 1, MEOG35::MAX_INTENSITY, MEORandomStrobe::Wheel((step_ + 24) % 48));
            }
            else
            {
                g35_.fill_color(myBulbs[myBulb_], 1, MEOG35::MAX_INTENSITY, colorMain_);
            }
            myBulb_++;
            simultan++;
        }
        while (simultan < noAtATime_);
    }
    //} while (myBulb < light_count_);

    if (rainbowFrame_) // change colour each frame - i.e. after all bulbs have been flashed
    {
        if (myBulb_ == light_count_)
        {
            myBulb_ = 0;
            step_++;
            if (step_ == 48) // all 48 colors in the wheel
            {
                step_ = 0;
            }
        }
    }
    else     // change colour after each individual flash
    {
        step_++;
        if (step_ == 48) // all 48 colors in the wheel
        {
            step_ = 0;
        }
        if (myBulb_ == light_count_)
        {
            myBulb_ = 0;
        }
    }

    return bulb_frame_;
}

// repeated from rainbow programs: To Do: learn how to just define once...
uint32_t MEORandomStrobe::Wheel(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 16)
    {
    case 0:
        r = 15 - WheelPos % 16; // red down
        g = WheelPos % 16;       // green up
        b = 0;                    // blue off
        break;
    case 1:
        g = 15 - WheelPos % 16; // green down
        b = WheelPos % 16;       // blue up
        r = 0;                    // red off
        break;
    case 2:
        b = 15 - WheelPos % 16; // blue down
        r = WheelPos % 16;       // red up
        g = 0;                    // green off
        break;
    }
    return(COLOR(r,g,b));
}