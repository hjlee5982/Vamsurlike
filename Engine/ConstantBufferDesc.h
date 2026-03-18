#pragma once

struct CB_PerFrame
{
	Matrix viewMatrix;
	Matrix projMatrix;
};

struct CB_PerObject
{
	Matrix worldMatrix;
	Vector4 UIColor;
};

struct CB_PerUI
{
	Matrix  worldMatrix;
	Vector4 color;
};