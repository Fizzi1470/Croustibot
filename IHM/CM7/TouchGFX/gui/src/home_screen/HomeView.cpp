#include <gui/home_screen/HomeView.hpp>
#include "main.h"
#include <gui_generated/home_screen/HomeViewBase.hpp>

extern FDCAN_HandleTypeDef hfdcan1;

HomeView::HomeView()
{

}

void HomeView::setupScreen()
{
    HomeViewBase::setupScreen();
}

void HomeView::tearDownScreen()
{
    HomeViewBase::tearDownScreen();
}

void HomeView::pos_depart()
{
	HAL_NVIC_SystemReset();
}

void HomeView::envoi_trame_can()
{
	//HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	static uint8_t cpt = 0;
	T_CAN_trame_tx trame_tx;

	trame_tx.header.Identifier = 0x7B0;
	trame_tx.header.IdType = FDCAN_STANDARD_ID;
	trame_tx.header.TxFrameType = FDCAN_DATA_FRAME;
	trame_tx.header.DataLength = 2;
	trame_tx.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	trame_tx.header.BitRateSwitch = FDCAN_BRS_OFF;
	trame_tx.header.FDFormat = FDCAN_CLASSIC_CAN;
	trame_tx.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	trame_tx.header.MessageMarker = 0;

	trame_tx.data[0] = (uint8_t)(cpt >> 8);
	trame_tx.data[1] = (uint8_t)cpt;

	cpt++;

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx.header, trame_tx.data);

	//NVIC_SystemReset();
}
