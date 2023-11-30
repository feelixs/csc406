//
//  LinearInterpolator.hpp
//  Week 13 - Animation with LinearInterpolator
//
//  Created by Jean-Yves Hervé on 2023-11-30.
//

#ifndef LINEAR_INTERPOLATOR_H
#define LINEAR_INTERPOLATOR_H

#include "KeyframeAnimator.h"

class LinearInterpolationKeyframeAnimator : public KeyframeAnimator
{
	public:
	
		LinearInterpolationKeyframeAnimator(const std::vector<std::vector<float> > frameList);
		LinearInterpolationKeyframeAnimator(unsigned int numFrames, unsigned int dimStateVect, const float** frameList);
		
		~LinearInterpolationKeyframeAnimator() = default;
		LinearInterpolationKeyframeAnimator() = delete;
		LinearInterpolationKeyframeAnimator(const LinearInterpolationKeyframeAnimator&) = delete;
		LinearInterpolationKeyframeAnimator(LinearInterpolationKeyframeAnimator&&) = delete;
		LinearInterpolationKeyframeAnimator& operator =(const LinearInterpolationKeyframeAnimator&) = delete;
		LinearInterpolationKeyframeAnimator& operator =(LinearInterpolationKeyframeAnimator&&) = delete;
		
		std::vector<float> getStateVector(float t);
		
};

#endif //	LINEAR_INTERPOLATOR_H
