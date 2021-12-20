#pragma once
#include "simp.h"
class simp_dual : public simp
{
public:
	simp_dual();
	virtual void print_optimal() override;
};