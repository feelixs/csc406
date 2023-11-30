//
//  LinearInterpolator.hpp
//  Week 13 - Animation with LinearInterpolator
//
//  Created by Jean-Yves Hervé on 2023-11-30.
//

#ifndef LINEAR_INTERPOLATOR_H
#define LINEAR_INTERPOLATOR_H

#include "KeyframeAnimator.h"

class LinearInterpolator : public KeyframeAnimator
{
	public:
	
		LinearInterpolator(const std::vector<std::vector<float> > frameList);
		LinearInterpolator(unsigned int numFrames, unsigned int dimStateVect, const float** frameList);
		
		~LinearInterpolator() = default;
		LinearInterpolator() = delete;
		LinearInterpolator(const LinearInterpolator&) = delete;
		LinearInterpolator(LinearInterpolator&&) = delete;
		LinearInterpolator& operator =(const LinearInterpolator&) = delete;
		LinearInterpolator& operator =(LinearInterpolator&&) = delete;
		
		std::vector<float> getStateVector(float t);
		
};

#endif //	LINEAR_INTERPOLATOR_H
