#include <gui/robot_en_match_screen/Robot_en_matchView.hpp>
#include "main.h"
#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include "math.h"

#define ARRIVEE_X 7000
#define ARRIVEE_Y 7000

extern int tirette;
extern int strat;

typedef struct {
	int16_t x;
	int16_t y;
	float distance_obstacle;
} lidar_pt_t;

lidar_pt_t points_lidar_match[360] = { 0 };
lidar_pt_t discontinuites_match[360] = { 0 };

uint16_t x_rob = 0, y_rob = 0, t_rob = 0;

bool detect_obstacle = 0;

Robot_en_matchView::Robot_en_matchView() {

}

void Robot_en_matchView::setupScreen() {
	Robot_en_matchViewBase::setupScreen();

	if (strat == 1) {
		uint16_t distance = 8000;
		uint16_t angle = 0;
		T_CAN_trame_tx trame_tx_moteurs = { 0 };

		trame_tx_moteurs.header.Identifier = 0x101;
		trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
		trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
		trame_tx_moteurs.header.DataLength = 4;
		trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
		trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
		trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
		trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
		trame_tx_moteurs.header.MessageMarker = 0;

		trame_tx_moteurs.data[0] = (uint8_t) distance;
		trame_tx_moteurs.data[1] = (uint8_t) (distance >> 8);
		trame_tx_moteurs.data[2] = (uint8_t) angle;
		trame_tx_moteurs.data[3] = (uint8_t) (angle >> 8);

		HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header,
				trame_tx_moteurs.data);
	}
}

void Robot_en_matchView::tearDownScreen() {
	Robot_en_matchViewBase::tearDownScreen();
}

void Robot_en_matchView::robot_en_match_tick() {
	uint16_t point_i;
	// point_i = angle
	fifo_params_t fifo = read_fifo();

	if (fifo.mess_avail) {
		for (uint16_t i_fifo = fifo.first_read; i_fifo < fifo.mess_amnt;
				i_fifo++) {

			uint16_t read_index = i_fifo % FIFO_SIZE;

			lidar_pt_t *tab = points_lidar_match;

			switch (tab_recep_trames_can[read_index].header.Identifier) {

			case 0x5FF:
				tab = discontinuites_match;

			case 0x601:
			case 0x600:
				point_i = tab_recep_trames_can[read_index].data[5] << 8
						| tab_recep_trames_can[read_index].data[4];

				tab[point_i].x = tab_recep_trames_can[read_index].data[1] << 8
						| tab_recep_trames_can[read_index].data[0];
				tab[point_i].y = tab_recep_trames_can[read_index].data[3] << 8
						| tab_recep_trames_can[read_index].data[2];

				tab[point_i].distance_obstacle = sqrt((tab[point_i].x) * ( tab[point_i].x) + (tab[point_i].y) * (tab[point_i].y));

				break;

			case 0x150:
				x_rob = tab_recep_trames_can[read_index].data[1] << 8
						| tab_recep_trames_can[read_index].data[0];
				y_rob = tab_recep_trames_can[read_index].data[3] << 8
						| tab_recep_trames_can[read_index].data[2];
				t_rob = tab_recep_trames_can[read_index].data[5] << 8
						| tab_recep_trames_can[read_index].data[4];

				t_rob /= 100.0;

				break;

			default:
				break;

			}
		}
	}

	//aller jusqu'à la diagonale puis stop puis angle inverse pour aller jusqu'à l'arrivée
	if (strat == 1) {
		if ((x_rob + y_rob) > 8000) {
			T_CAN_trame_tx trame_tx_moteurs = { 0 };

			trame_tx_moteurs.header.Identifier = 0x05;
			trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
			trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
			trame_tx_moteurs.header.DataLength = 0;
			trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
			trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
			trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
			trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			trame_tx_moteurs.header.MessageMarker = 0;

			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header,
					trame_tx_moteurs.data);

			uint16_t distance = sqrt(
					((x_rob - ARRIVEE_X) * (x_rob - ARRIVEE_X))
							+ ((y_rob - ARRIVEE_Y) * (y_rob - ARRIVEE_Y)));

			uint16_t angle = atan2((ARRIVEE_Y - y_rob), (ARRIVEE_X - x_rob));

			angle = (angle * 180.0 / M_PI) - t_rob;

			T_CAN_trame_tx trame_tx_consigne = { 0 };

			trame_tx_consigne.header.Identifier = 0x101;
			trame_tx_consigne.header.IdType = FDCAN_STANDARD_ID;
			trame_tx_consigne.header.TxFrameType = FDCAN_DATA_FRAME;
			trame_tx_consigne.header.DataLength = 4;
			trame_tx_consigne.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
			trame_tx_consigne.header.BitRateSwitch = FDCAN_BRS_OFF;
			trame_tx_consigne.header.FDFormat = FDCAN_CLASSIC_CAN;
			trame_tx_consigne.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
			trame_tx_consigne.header.MessageMarker = 0;

			trame_tx_consigne.data[0] = (uint8_t) distance;
			trame_tx_consigne.data[1] = (uint8_t) (distance >> 8);
			trame_tx_consigne.data[2] = (uint8_t) angle;
			trame_tx_consigne.data[3] = (uint8_t) (angle >> 8);

			HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_consigne.header,
					trame_tx_consigne.data);
		}
	}

	//détecter un obstacle à 30cm sur les angles compris entre 0° et 30° / 330° et 359°
	if (strat == 2) {
//		uint16_t distance = 2000;
//		uint16_t angle = 0;
//		T_CAN_trame_tx trame_tx_moteurs = { 0 };
//
//		trame_tx_moteurs.header.Identifier = 0x101;
//		trame_tx_moteurs.header.IdType = FDCAN_STANDARD_ID;
//		trame_tx_moteurs.header.TxFrameType = FDCAN_DATA_FRAME;
//		trame_tx_moteurs.header.DataLength = 4;
//		trame_tx_moteurs.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//		trame_tx_moteurs.header.BitRateSwitch = FDCAN_BRS_OFF;
//		trame_tx_moteurs.header.FDFormat = FDCAN_CLASSIC_CAN;
//		trame_tx_moteurs.header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//		trame_tx_moteurs.header.MessageMarker = 0;
//
//		trame_tx_moteurs.data[0] = (uint8_t) distance;
//		trame_tx_moteurs.data[1] = (uint8_t) (distance >> 8);
//		trame_tx_moteurs.data[2] = (uint8_t) angle;
//		trame_tx_moteurs.data[3] = (uint8_t) (angle >> 8);
//
//		HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_moteurs.header,
//				trame_tx_moteurs.data);


		for(uint16_t lidar_i = 150; lidar_i < 220; lidar_i++){
			if (points_lidar_match[lidar_i].distance_obstacle <= 600.0 && points_lidar_match[lidar_i].distance_obstacle != 0) {

				if (detect_obstacle == 0) {
					detect_obstacle = 1;
					T_CAN_trame_tx trame_tx_moteurs = { 0 };

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
			} else {
				detect_obstacle = false;

				if (detect_obstacle == 1) {
					detect_obstacle = 0;

					uint16_t distance = 2000;
					uint16_t angle = 0;
					T_CAN_trame_tx trame_tx_consigne = { 0 };

					trame_tx_consigne.header.Identifier = 0x101;
					trame_tx_consigne.header.IdType = FDCAN_STANDARD_ID;
					trame_tx_consigne.header.TxFrameType = FDCAN_DATA_FRAME;
					trame_tx_consigne.header.DataLength = 4;
					trame_tx_consigne.header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
					trame_tx_consigne.header.BitRateSwitch = FDCAN_BRS_OFF;
					trame_tx_consigne.header.FDFormat = FDCAN_CLASSIC_CAN;
					trame_tx_consigne.header.TxEventFifoControl =
					FDCAN_NO_TX_EVENTS;
					trame_tx_consigne.header.MessageMarker = 0;

					trame_tx_consigne.data[0] = (uint8_t) distance;
					trame_tx_consigne.data[1] = (uint8_t) (distance >> 8);
					trame_tx_consigne.data[2] = (uint8_t) angle;
					trame_tx_consigne.data[3] = (uint8_t) (angle >> 8);

					HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,
							&trame_tx_consigne.header, trame_tx_consigne.data);

				}
			}
		}
	}
}
