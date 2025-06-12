#include <gui/robot_en_match_screen/Robot_en_matchView.hpp>
#include "main.h"
#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include "math.h"

#define MAX_LIDAR_DIST 9000

#define ARRIVEE_X 7250
#define ARRIVEE_Y 7250

extern int tirette;
extern int strat;

typedef struct {
	int16_t x;
	int16_t y;
	float distance;
} lidar_pt_t;

lidar_pt_t points_lidar_match[360] = { 0 };
//lidar_pt_t discontinuites_match[360] = { 0 };

int16_t x_rob = 0, y_rob = 0;
float t_rob = 0;
int16_t x_dest = 0, y_dest = 0;

bool manuel = false;
bool avoid = false;

typedef enum {
	xy, rd, rd_abs, done,
} mov_type_t;

struct {
	mov_type_t type;
	union {
		struct {
			int16_t x, y;
		};
		struct {
			float angle, distance;
		};
	};
} waypoints[] = { { .type = rd_abs, .angle = -30, .distance = 10000 }, { .type =
		xy, .x = ARRIVEE_X, .y = ARRIVEE_Y }, { .type = done }, };

uint16_t move = 0;

bool diago = false;

void robot_stop() {

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

}

void robot_moveby(float dist, float angle, bool abs_angle) {
	if(abs_angle) angle -= t_rob;

	float angle_rad = -angle / 180.0 * M_PI;

	x_dest += dist * cos(angle_rad), y_dest += dist * sin(angle_rad);

	int16_t distance = lroundf(dist);
	int16_t angle_diz_deg = lroundf(angle * 100);

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

	trame_tx_consigne.data[0] = distance & 0xFF;
	trame_tx_consigne.data[1] = (distance >> 8) & 0xFF;
	trame_tx_consigne.data[2] = angle_diz_deg & 0xFF;
	trame_tx_consigne.data[3] = (angle_diz_deg >> 8) & 0xFF;

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_consigne.header,
			trame_tx_consigne.data);
}

void robot_goto(float x, float y) {
	float distance = sqrt(((x - x_rob) * (x - x_rob)) + ((y - y_rob) * (y - y_rob)));

	volatile float angle_to_dest = atan2((y - y_rob), (x - x_rob)) * -180.0 / M_PI;

	robot_moveby(distance, angle_to_dest, true);
}

void robot_resume() {
	robot_goto(x_dest, y_dest);
}

void next_move() {
	switch (waypoints[move].type) {
	case xy:
		robot_goto(waypoints[move].x, waypoints[move].y);
		move++;
		break;
	case rd:
		robot_moveby(waypoints[move].distance, waypoints[move].angle, 0);
		move++;
		break;
	case rd_abs:
		robot_moveby(waypoints[move].distance, waypoints[move].angle, 1);
		move++;
		break;
	case done:
		break;
	}
}

Robot_en_matchView::Robot_en_matchView() {

}

void Robot_en_matchView::setupScreen() {
	Robot_en_matchViewBase::setupScreen();

	if (strat == 1) {
		next_move();
	}
}

void Robot_en_matchView::tearDownScreen() {
	Robot_en_matchViewBase::tearDownScreen();
}

uint16_t start_angle = 0;
uint32_t received = 0;
uint32_t seen = 0;

void Robot_en_matchView::robot_en_match_tick() {

	static uint32_t tick_debut_stop = 0;
	static uint8_t etat_evitement = 0;

	fifo_params_t
	fifo = read_fifo();

	received += fifo.mess_amnt;

	if (fifo.mess_avail) {
		for (uint16_t i_fifo = fifo.first_read;
				i_fifo < fifo.mess_amnt + fifo.first_read; i_fifo++) {

			uint16_t read_index = i_fifo % FIFO_SIZE;
			seen++;

			int16_t t_rob_dix = 0;

			switch (tab_recep_trames_can[read_index].header.Identifier) {

			case 0x05: // stop (envoyé par les lidars)
				//robot_stop(); NON ! cette trame est déjà envoyée par les lidars
				avoid = true;
				tick_debut_stop = HAL_GetTick();
				break;

			case 0x06: // reprise (envoyé par les lidars)
				avoid = false;
				if (!manuel)
					robot_resume();
				break;

			case 0x10: // fin de mouvement
				if (!avoid && !manuel)
					next_move();
				else if(manuel)
				{
					switch(etat_evitement)
					{
					case 0:
						robot_moveby(550, 0, 0);
						etat_evitement ++;
						break;

					case 1:
						manuel = false;
						robot_resume();
						etat_evitement = 0;
						break;
					}
				}
				break;

			case 0x150: // telemetrie
				x_rob = tab_recep_trames_can[read_index].data[1] << 8
						| tab_recep_trames_can[read_index].data[0];
				y_rob = tab_recep_trames_can[read_index].data[3] << 8
						| tab_recep_trames_can[read_index].data[2];
				t_rob_dix = tab_recep_trames_can[read_index].data[5] << 8
						| tab_recep_trames_can[read_index].data[4];

				t_rob = (float) t_rob_dix / 100.0;
				break;

			case 0x400 ... 0x4FF: // lidar avant
				start_angle =
						(tab_recep_trames_can[read_index].header.Identifier
								- 0x400) * 8;

				start_angle += 270;
				start_angle %= 360;

				for (uint16_t i = 0; i < 8; i++) {
					points_lidar_match[start_angle + i].distance =
							tab_recep_trames_can[read_index].data[i]
									* MAX_LIDAR_DIST / 255;
				}

				break;
			case 0x500 ... 0x5FF: // lidar arriere
				start_angle =
						(tab_recep_trames_can[read_index].header.Identifier
								- 0x500) * 8;

				start_angle += 270 + 180;
				start_angle %= 360;

				for (uint16_t i = 0; i < 8; i++) {
					points_lidar_match[start_angle + i].distance =
							tab_recep_trames_can[read_index].data[i]
									* MAX_LIDAR_DIST / 255;
				}

				break;

			default:
				break;

			}
		}
	}

	//aller jusqu'à la diagonale puis stop puis angle inverse pour aller jusqu'à l'arrivée
	if (strat == 1) {
		if ((x_rob + y_rob) > 8000 && diago == false) {
			robot_stop();
			next_move();
			diago = true;
		}

		if (avoid == true) {
			if (HAL_GetTick() - tick_debut_stop >= 1000) {
				manuel = true;
				avoid = false;
				robot_moveby(0, 90, 0);

			}
		}

	}
}
