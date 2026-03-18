#pragma once

struct Keyframe
{
	f32 time;
	f32 value;
};

struct AnimationCurve
{
	List<Keyframe> keys;
};

struct AnimationClip
{
	f32 lenth = 0.0f;
	Dictionary<string, AnimationCurve> curves;
};