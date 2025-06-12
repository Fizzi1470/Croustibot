#include <gui/tests_moteurs_screen/Tests_moteursView.hpp>
#include "main.h"
#include <gui_generated/tests_moteurs_screen/Tests_moteursViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

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
//	T_CAN_trame_tx trame_tx_moteurs = {0};
//
//	trame_tx_moteurs.header.Identifier = 0x101;
//	trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
//	trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
//	trame_tx_moteurs.header.DataLength = 0;
//	trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//	trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
//	trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
//	trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	trame_tx_moteurs.header.MessageMarker = 0;
//
//	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header, trame_tx_moteurs.data);
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

void Tests_moteursView::moteurs_aller_la_bas()
{
	uint16_t distance = 2000;
	uint16_t angle = 0;
	T_CAN_trame_tx trame_tx_moteurs = {0};

	trame_tx_moteurs.header.Identifier = 0x101;
	trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
	trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
	trame_tx_moteurs.header.DataLength = 4;
	trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
	trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
	trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	trame_tx_moteurs.header.MessageMarker = 0;

	trame_tx_moteurs.data[0] = (uint8_t)distance;
	trame_tx_moteurs.data[1] = (uint8_t)(distance >> 8);
	trame_tx_moteurs.data[2] = (uint8_t)angle;
	trame_tx_moteurs.data[3] = (uint8_t)(angle >> 8);

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

void Tests_moteursView::active_tout_le_tps()
{
//	fifo_params_t fifo = read_fifo();
//
//		if(fifo.mess_avail){
//		for(uint16_t i_fifo = fifo.first_read; i_fifo < fifo.mess_amnt; i_fifo++){
//
//			uint16_t read_index = i_fifo % FIFO_SIZE;
//
//			switch (tab_recep_trames_can[read_index].header.Identifier){
//
//			default: break;
//
//			case 0x213:
//				uint16_t distance = 5000;
//				uint16_t angle = 90;
//				T_CAN_trame_tx trame_tx_moteurs = { 0 };
//
//				trame_tx_moteurs.header.Identifier = 0x101;
//				trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
//				trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
//				trame_tx_moteurs.header.DataLength = 4;
//				trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//				trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
//				trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
//				trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//				trame_tx_moteurs.header.MessageMarker = 0;
//
//				trame_tx_moteurs.data[0] = (uint8_t) distance;
//				trame_tx_moteurs.data[1] = (uint8_t) (distance >> 8);
//				trame_tx_moteurs.data[2] = (uint8_t) angle;
//				trame_tx_moteurs.data[3] = (uint8_t) (angle >> 8);
//
//				HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,
//						&trame_tx_moteurs.header, trame_tx_moteurs.data);
//				break;
//			}
//		}
//		}
}

