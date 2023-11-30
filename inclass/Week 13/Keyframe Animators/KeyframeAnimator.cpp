//
//  KeyframeAnimator.cpp
//  Week 13 - Animation with KeyFrameAnimator
//
//  Created by Jean-Yves Hervé on 2023-11-29.
//

#include "KeyframeAnimator.h"

using namespace std;

KeyframeAnimator::KeyframeAnimator(const vector<vector<float> > frameList)
	try	:	numFrames_(static_cast<unsigned int>(frameList.size())),
			dimStateVect_(static_cast<unsigned int>(frameList[0].size())),
			frameList_(frameList)
{
	for (size_t i=1; i<numFrames_; i++)
	{
		if (frameList_[i].size() != dimStateVect_)
		{
			cout << "Improperly sized keyframe " << i << endl;
			exit(4);
		}
	}
}
//	We get there because the keyframe vector isn't properly initialized
catch(...)
{
	//	In an ideal world I would throw
	cout << "keyframe vector isn't properly initialized" << endl;
	exit(3);
}

KeyframeAnimator::KeyframeAnimator(unsigned int numFrames, unsigned int dimStateVect,
								   const float** frameList)
		:	numFrames_(numFrames),
			dimStateVect_(dimStateVect),
			frameList_(vector<vector<float> >(numFrames_))
{
	for (size_t i=1; i<numFrames; i++)
	{
		try
		{
			frameList_[i] = vector<float>(frameList[i], frameList[i]+dimStateVect);
		}
		catch(...)
		{
			cout << "Improperly sized keyframe " << i << endl;
			exit(4);
		}
	}
}
