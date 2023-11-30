//
//  KeyframeAnimator.h
//  Week 13 - Animation with KeyFrameAnimator
//
//  Created by Jean-Yves Hervé on 2023-11-29.
//

#ifndef KEYFRAME_ANIMATOR_H
#define KEYFRAME_ANIMATOR_H

#include <iostream>
#include <vector>

class KeyframeAnimator
{
	public:
	
		KeyframeAnimator(const std::vector<std::vector<float> > frameList);
		KeyframeAnimator(unsigned int numFrames, unsigned int dimStateVect, const float** frameList);
		
		~KeyframeAnimator() = default;
		KeyframeAnimator() = delete;
		KeyframeAnimator(const KeyframeAnimator&) = delete;
		KeyframeAnimator(KeyframeAnimator&&) = delete;
		KeyframeAnimator& operator =(const KeyframeAnimator&) = delete;
		KeyframeAnimator& operator =(KeyframeAnimator&&) = delete;
		
		virtual std::vector<float> getStateVector(float t) = 0;
		
		inline float getKeyframeElement(unsigned int frameIndex, unsigned int componentIndex) const
		{
			if (frameIndex < numFrames_ && componentIndex < dimStateVect_)
			{
				return frameList_[frameIndex][componentIndex];
			}
			else if (frameIndex >= numFrames_)
			{
				std::cout << "Invalid frame index: " << frameIndex << std::endl;
				exit(1);
			}
			else //	componentIndex >= dimStateVect_)
			{
				std::cout << "Invalid state vector component index: " << componentIndex << std::endl;
				exit(2);
			}
		}
		
		inline float getkeyframeTime(unsigned int frameIndex) const
		{
			if (frameIndex < numFrames_)
			{
				return frameList_[frameIndex][dimStateVect_];
			}
			else // (frameIndex >= numFrames)
			{
				std::cout << "Invalid frame index: " << frameIndex << std::endl;
				exit(1);
			}
		}
		
		inline unsigned int getNumFrames() const
		{
			return numFrames_;
		}

		inline unsigned int getStateVectorDim() const
		{
			return dimStateVect_;
		}

		inline float getLastKeyFrameTime() const
		{
			return frameList_[numFrames_-1][dimStateVect_];
		}
				
	private:
	
		unsigned int numFrames_;
		unsigned int dimStateVect_;
		std::vector<std::vector<float> > frameList_;

};

#endif //	KEYFRAME_ANIMATOR_H
