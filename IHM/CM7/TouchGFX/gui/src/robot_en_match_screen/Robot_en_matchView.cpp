#include <gui/robot_en_match_screen/Robot_en_matchView.hpp>
#include "main.h"
#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include "math.h"

#define MAX_LIDAR_DIST 9000

#define ARRIVEE_X 7000
#define ARRIVEE_Y 7000

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

bool avoid = false;

union {
	struct {
		int16_t x, y;
	} xy;
	struct {
		float angle;
		float distance;
	} rd;
} waypoints[] = {
	{.rd = {-30, 10000}},
	{.xy = {ARRIVEE_X, ARRIVEE_Y}},
};

uint16_t move = 0;

bool diago = false;

void robot_stop(){

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

void robot_goto(int16_t x, int16_t y){
	x_dest = x, y_dest = y;

	uint16_t distance = sqrt(((x_dest - x_rob) * (x_dest - x_rob)) + ((y_dest - y_rob) * (y_dest - y_rob)));

	float angle_to_dest = atan2((y_dest - y_rob), (x_dest - x_rob)) * -180.0 / M_PI;

	int16_t angle_diz_deg = (int16_t)(angle_to_dest - t_rob) * 100;

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

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &trame_tx_consigne.header, trame_tx_consigne.data);
}

void robot_moveby(float distance, float angle){
	angle = -angle /  180 * M_PI;

	robot_goto(x_rob + lroundf(distance * cos(angle)), y_rob + lroundf(distance * sin(angle)));
}

void robot_resume(){
	robot_goto(x_dest, y_dest);
}


void next_move(){
	if(waypoints[move].rd.angle == 0 && waypoints[move].rd.distance == 0) {
		robot_goto(waypoints[move].xy.x, waypoints[move].xy.y);
	} else {
		robot_moveby(waypoints[move].rd.distance, waypoints[move].rd.angle);
	}

	if(move < sizeof(waypoints) / sizeof(waypoints[0])) move++;
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

	fifo_params_t fifo = read_fifo();

	received += fifo.mess_amnt;

	if (fifo.mess_avail) {
		for (uint16_t i_fifo = fifo.first_read; i_fifo < fifo.mess_amnt + fifo.first_read; i_fifo++) {

			uint16_t read_index = i_fifo % FIFO_SIZE;
			seen ++;

			int16_t t_rob_dix = 0;

			switch (tab_recep_trames_can[read_index].header.Identifier) {



			case 0x05 : // stop (envoyé par les lidars)
				//robot_stop(); NON ! cette trame est déjà envoyée par les lidars
				avoid = true;
				break;

			case 0x06 : // reprise (envoyé par les lidars)
				avoid = false;
				robot_resume();
				break;

			case 0x10 : // fin de mouvement
				if(!avoid) next_move();
				break;

			case 0x150: // telemetrie
				x_rob = tab_recep_trames_can[read_index].data[1] << 8 | tab_recep_trames_can[read_index].data[0];
				y_rob = tab_recep_trames_can[read_index].data[3] << 8 | tab_recep_trames_can[read_index].data[2];
				t_rob_dix = tab_recep_trames_can[read_index].data[5] << 8 | tab_recep_trames_can[read_index].data[4];

				t_rob = (float)t_rob_dix / 100.0;
				break;

			case 0x400 ... 0x4FF : // lidar avant
				start_angle = (tab_recep_trames_can[read_index].header.Identifier - 0x400) * 8;

				start_angle += 270;
				start_angle %= 360;

				for(uint16_t i = 0; i < 8; i++){
					points_lidar_match[start_angle + i].distance = tab_recep_trames_can[read_index].data[i] * MAX_LIDAR_DIST / 255;
				}

				break;
			case 0x500 ... 0x5FF : // lidar arriere
				start_angle = (tab_recep_trames_can[read_index].header.Identifier - 0x500) * 8;

				start_angle += 270 + 180;
				start_angle %= 360;

				for(uint16_t i = 0; i < 8; i++){
					points_lidar_match[start_angle + i].distance = tab_recep_trames_can[read_index].data[i] * MAX_LIDAR_DIST / 255;
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
	}
}
