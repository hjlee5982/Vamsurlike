#include "pch.h"
#include "Global.h"

ClientOption Global::ClientOption;

Matrix Global::ViewMatrix = Matrix::Identity;
Matrix Global::ProjMatrix = Matrix::Identity;

Matrix Global::UIViewMatrix = Matrix::Identity;
Matrix Global::UIProjMatrix = Matrix::Identity;