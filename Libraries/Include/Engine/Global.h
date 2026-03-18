#pragma once

class Global
{
public:
	static ClientOption ClientOption;
public:
	static Matrix ViewMatrix;
	static Matrix ProjMatrix;
public:
	static Matrix UIViewMatrix;
	static Matrix UIProjMatrix;
public:
	static f32 Aspect()
	{
		return ClientOption.width / ClientOption.height;
	}
};