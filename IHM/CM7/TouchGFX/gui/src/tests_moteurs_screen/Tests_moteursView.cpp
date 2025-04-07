#include <gui/tests_moteurs_screen/Tests_moteursView.hpp>
#include "main.h"
#include <gui_generated/tests_moteurs_screen/Tests_moteursViewBase.hpp>

Tests_moteursView::Tests_moteursView()
{

}

void Tests_moteursView::setupScreen()
{
    Tests_moteursViewBase::setupScreen();
}

void Tests_moteursView::tearDownScreen()
{
    Tests_moteursViewBase::tearDownScreen();
}


void Tests_moteursView::moteurs_avancer()
{
	T_CAN_trame_tx trame_tx_moteurs = {0};

	trame_tx_moteurs.header.Identifier = 0x101;
	trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
	trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
	trame_tx_moteurs.header.DataLength = 0;
	trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
	trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
	trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	trame_tx_moteurs.header.MessageMarker = 0;

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header, trame_tx_moteurs.data);
}

void Tests_moteursView::moteurs_tourner_90()
{
	T_CAN_trame_tx trame_tx_moteurs = {0};

	trame_tx_moteurs.header.Identifier = 0x90;
	trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
	trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
	trame_tx_moteurs.header.DataLength = 0;
	trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
	trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
	trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	trame_tx_moteurs.header.MessageMarker = 0;

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header, trame_tx_moteurs.data);
}

void Tests_moteursView::moteurs_tourner_180()
{
	T_CAN_trame_tx trame_tx_moteurs = {0};

	trame_tx_moteurs.header.Identifier = 0x180;
	trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
	trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
	trame_tx_moteurs.header.DataLength = 0;
	trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
	trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
	trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	trame_tx_moteurs.header.MessageMarker = 0;

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header, trame_tx_moteurs.data);
}

void Tests_moteursView::stop()
{
	T_CAN_trame_tx trame_tx_moteurs = {0};

	trame_tx_moteurs.header.Identifier = 0x05;
	trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
	trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
	trame_tx_moteurs.header.DataLength = 0;
	trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
	trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
	trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	trame_tx_moteurs.header.MessageMarker = 0;

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header, trame_tx_moteurs.data);
}
