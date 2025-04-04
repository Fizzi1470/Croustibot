#include <gui/choix_strategie_screen/Choix_strategieView.hpp>
#include "main.h"
#include <touchgfx/Color.hpp>
#include <gui_generated/choix_strategie_screen/Choix_strategieViewBase.hpp>

extern int strat;

Choix_strategieView::Choix_strategieView()
{

}

void Choix_strategieView::setupScreen()
{
    Choix_strategieViewBase::setupScreen();
}

void Choix_strategieView::tearDownScreen()
{
    Choix_strategieViewBase::tearDownScreen();
}

void Choix_strategieView::strategie_1()
{
	strat = 1;
}

void Choix_strategieView::strategie_2()
{
	strat = 2;
}

void Choix_strategieView::strategie_3()
{
	strat = 3;
}

void Choix_strategieView::strategie_4()
{
	strat = 4;
}

void Choix_strategieView::strategie_5()
{
	strat = 5;
}

void Choix_strategieView::strategie_6()
{
	strat = 6;
}

void Choix_strategieView::valider_strat()
{
	switch (strat)
	{
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;
	}
}
