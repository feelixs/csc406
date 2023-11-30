//
//  LinearInterpolator.cpp
//  Week 13 - Animation with KeyFrameAnimator
//
//  Created by Jean-Yves Hervé on 2023-11-30.
//

#include "LinearInterpolator.h"

using namespace std;

LinearInterpolator::LinearInterpolator(const std::vector<std::vector<float> > frameList)
	:	KeyframeAnimator(frameList)
{
}
LinearInterpolator::LinearInterpolator(unsigned int numFrames, unsigned int dimStateVect, const float** frameList)
	:	KeyframeAnimator(numFrames, dimStateVect, frameList)
{
}

vector<float> LinearInterpolator::getStateVector(float t)
{
	vector<float> stateVect(getStateVectorDim());
	
	if (t < getkeyframeTime(getNumFrames()-1))
	{
		//  which interval do we fall into?
		for (unsigned int i=1; i<getNumFrames(); i++)
		{
			if (getkeyframeTime(i) >= t)
			{
				//we fall in the interval [i-1, i]
				
				//  compute interpolation factor
				float tau = (t - getkeyframeTime(i-1)) /
								(getkeyframeTime(i) - getkeyframeTime(i-1));
float tPrev = getkeyframeTime(i-1),
		tNext = getkeyframeTime(i);
				for (unsigned int k=0; k<getStateVectorDim(); k++)
				{
					stateVect[k] = getKeyframeElement(i-1, k) +
									tau * ( getKeyframeElement(i, k) -
											getKeyframeElement(i-1, k));
				}
			}
		}
	}
	//	If the animation is over, stick to the last key frame
	else
	{
		for (unsigned int k=0; k<getStateVectorDim(); k++)
		{
			stateVect[k] = getKeyframeElement(getNumFrames()-1, k);
		}
	
	}

	return stateVect;
}
