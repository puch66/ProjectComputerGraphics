 void place_wood(glm::mat4 *WoodWM) {
	
		WoodWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 0));
		WoodWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 1.0f)), glm::vec3(0, 0, -2));
		WoodWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, -4));
		WoodWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 0));
		WoodWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 0));
		WoodWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 8));
		WoodWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 8));
		WoodWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 4));
		WoodWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 4));
		WoodWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, -4));
		WoodWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, -8));
		WoodWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, -8));
		WoodWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 0));
		WoodWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 0));
		WoodWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 8));
		WoodWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, -8));
		WoodWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 8));
		WoodWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 8));
		WoodWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, -8));
		WoodWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, -4));
		WoodWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, -8));
		WoodWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, -4));
		WoodWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 4));
		WoodWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 4));
		WoodWM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 4));
	}


void place_ground(glm::mat4 *GroundWM) {
	GroundWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 0));
	GroundWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, -8));
	GroundWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-8, 0, -8));
	GroundWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-8, 0, 0));
	GroundWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(8, 0, 0));
	GroundWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-8, 0, 8));
	GroundWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(8, 0, -8));
	GroundWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(8, 0, 8));
	GroundWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 8));
}

void place_water(glm::mat4 *WaterWM) {
	WaterWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, -12));
	WaterWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, -8));
	WaterWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, -4));
	WaterWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 0));
	WaterWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 4));
	WaterWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 8));
	WaterWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-12, 0, 12));
	WaterWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, -12));
	WaterWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, -8));
	WaterWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, -4));
	WaterWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 0));
	WaterWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 4));
	WaterWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 8));
	WaterWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(12, 0, 12));
	WaterWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, -12));
	WaterWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, -12));
	WaterWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, -12));
	WaterWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, -12));
	WaterWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, -12));
	WaterWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-8, 0, 12));
	WaterWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(-4, 0, 12));
	WaterWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(0, 0, 12));
	WaterWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(4, 0, 12));
	WaterWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.0f, 2.0f)), glm::vec3(8, 0, 12));
}

/**/

int insertLog(int nLog, float angRot, glm::vec3 startPos, int indexNow, bool isPlus, glm::mat4* LogWM) {
	for (int i = 0; i < nLog; i++) {
		glm::vec3 addOneLog;
		if (angRot == 0.f) {
			addOneLog = glm::vec3(float(i), 0.f, 0.f);
		}
		else {
			addOneLog = glm::vec3(0.f, 0.f, float(i));

		}
		LogWM[indexNow + i] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.f, 1.0f)), startPos + (isPlus ? addOneLog : -addOneLog)) *
			glm::rotate(glm::mat4(1.0), angRot, glm::vec3(0, 1, 0));
	}
	return nLog;
}

glm::vec3 findNewPos(int oldNLog, bool isPlus, float angRot, glm::vec3 oldPos, bool oldPlus) {
	float newAdd = float(oldNLog) - 0.5f;

	if (angRot == 0.f) { // da vert a ori
		oldPos += glm::vec3((isPlus ? 0.5f : -0.5f), 0.f, (oldPlus ? newAdd : -newAdd));
	}
	else {
		oldPos += glm::vec3((oldPlus ? newAdd : -newAdd), 0.f, (isPlus ? 0.5f : -0.5f));
	}

	return oldPos;
}

void place_logs(glm::mat4 *LogWM) {
	int countLog = 0;

	countLog += insertLog(15, 30.f, glm::vec3(0, 0.2, 3), countLog, true, LogWM);
	countLog += insertLog(12, 30.f, glm::vec3(2.5f, 0.2, 3), countLog, true, LogWM);

	countLog += insertLog(5, 0.f, glm::vec3(0.8, 0.2, 17.5), countLog, true, LogWM);
	countLog += insertLog(3, 0.f, glm::vec3(3.3f, 0.2, 14.5), countLog, true, LogWM);

	countLog += insertLog(5, 30.f, glm::vec3(5, 0.2, 18), countLog, true, LogWM);
	countLog += insertLog(20, 0.f, glm::vec3(5.8, 0.2, 22.5), countLog, true, LogWM);
	countLog += insertLog(4, 30.f, glm::vec3(25, 0.2, 23), countLog, true, LogWM);
	countLog += insertLog(10, 0.f, glm::vec3(25, 0.2, 26.5), countLog, false, LogWM);
	countLog += insertLog(3, 30.f, glm::vec3(15.8, 0.2, 27), countLog, true, LogWM);
	countLog += insertLog(13, 0.f, glm::vec3(16.6, 0.2, 29.5), countLog, true, LogWM);
	countLog += insertLog(19, 30.f, glm::vec3(28.8, 0.2, 29.), countLog, false, LogWM);
	countLog += insertLog(4, 0.f, glm::vec3(28.8, 0.2, 10.5), countLog, false, LogWM);
	countLog += insertLog(9, 30.f, glm::vec3(25.6, 0.2, 11.), countLog, true, LogWM);
	countLog += insertLog(18, 0.f, glm::vec3(25.6, 0.2, 19.5), countLog, false, LogWM);
	countLog += insertLog(6, 30.f, glm::vec3(8.4, 0.2, 19.), countLog, false, LogWM);
	countLog += insertLog(14, 0.f, glm::vec3(8.4, 0.2, 14.), countLog, true, LogWM);
	countLog += insertLog(4, 30.f, glm::vec3(21.6, 0.2, 14.), countLog, false, LogWM);
	countLog += insertLog(17, 0.f, glm::vec3(21.6, 0.2, 10.5), countLog, false, LogWM);
	countLog += insertLog(4, 30.f, glm::vec3(5.6, 0.2, 11.), countLog, true, LogWM);

	countLog += insertLog(30, 0.f, glm::vec3(3.f, 0.2, 2.5), countLog, true, LogWM);
	countLog += insertLog(3, 30.f, glm::vec3(32.5f, 0.2, 2.), countLog, false, LogWM);
	countLog += insertLog(4, 0.f, glm::vec3(32.f, 0.2, -.5), countLog, false, LogWM);
	countLog += insertLog(8, 30.f, glm::vec3(28.5f, 0.2, -1.), countLog, false, LogWM);
	countLog += insertLog(12, 0.f, glm::vec3(29.f, 0.2, -8.5), countLog, true, LogWM);
	countLog += insertLog(20, 30.f, glm::vec3(40.5f, 0.2, -9.), countLog, false, LogWM);
	countLog += insertLog(3, 0.f, glm::vec3(40.f, 0.2, -28.5), countLog, false, LogWM);
	countLog += insertLog(16, 30.f, glm::vec3(37.5f, 0.2, -28.), countLog, true, LogWM);
	countLog += insertLog(18, 0.f, glm::vec3(37.f, 0.2, -12.5), countLog, false, LogWM);
	countLog += insertLog(16, 30.f, glm::vec3(19.5f, 0.2, -13.), countLog, false, LogWM);
	countLog += insertLog(3, 0.f, glm::vec3(19.f, 0.2, -28.5), countLog, false, LogWM);
	countLog += insertLog(16, 30.f, glm::vec3(16.5f, 0.2, -28.), countLog, true, LogWM);
	countLog += insertLog(32, 0.f, glm::vec3(16.f, 0.2, -12.5), countLog, false, LogWM);
	countLog += insertLog(16, 30.f, glm::vec3(-15.5f, 0.2, -13.), countLog, false, LogWM);
	countLog += insertLog(3, 0.f, glm::vec3(-16.f, 0.2, -28.5), countLog, false, LogWM);
	countLog += insertLog(16, 30.f, glm::vec3(-18.5f, 0.2, -28.), countLog, true, LogWM);
	countLog += insertLog(6, 0.f, glm::vec3(-19.f, 0.2, -12.5), countLog, false, LogWM);
	countLog += insertLog(16, 30.f, glm::vec3(-24.5f, 0.2, -13.), countLog, false, LogWM);
	countLog += insertLog(3, 0.f, glm::vec3(-25.f, 0.2, -28.5), countLog, false, LogWM);
	countLog += insertLog(20, 30.f, glm::vec3(-27.5f, 0.2, -28.), countLog, true, LogWM);
	countLog += insertLog(24, 0.f, glm::vec3(-27.f, 0.2, -8.5), countLog, true, LogWM);
	countLog += insertLog(8, 30.f, glm::vec3(-3.5f, 0.2, -8.), countLog, true, LogWM);
	countLog += insertLog(22, 0.f, glm::vec3(3.f, 0.2, -0.5), countLog, true, LogWM);
	countLog += insertLog(8, 30.f, glm::vec3(2.5f, 0.2, -1.), countLog, false, LogWM);
	countLog += insertLog(8, 30.f, glm::vec3(24.5f, 0.2, -1.), countLog, false, LogWM);
	countLog += insertLog(22, 0.f, glm::vec3(3.f, 0.2, -8.5), countLog, true, LogWM);

	countLog += insertLog(12, 0.f, glm::vec3(-0.5, 0.2, 2.5), countLog, false, LogWM);
	glm::vec3 oldPositionVec = findNewPos(12, true, 30.f, glm::vec3(-0.5, 0.2, 2.5), false);
	countLog += insertLog(8, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(8, false, 0.f, oldPositionVec, true);
	countLog += insertLog(8, 0.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(8, true, 30.f, oldPositionVec, false);
	countLog += insertLog(8, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(8, false, 0.f, oldPositionVec, true);
	countLog += insertLog(12, 0.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(12, true, 30.f, oldPositionVec, false);
	countLog += insertLog(4, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(4, true, 0.f, oldPositionVec, true);
	countLog += insertLog(21, 0.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(21, true, 30.f, oldPositionVec, true);
	countLog += insertLog(3, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(3, false, 0.f, oldPositionVec, true);
	countLog += insertLog(24, 0.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(24, false, 30.f, oldPositionVec, false);
	countLog += insertLog(18, 30.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(18, true, 0.f, oldPositionVec, false);
	countLog += insertLog(3, 0.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(3, true, 30.f, oldPositionVec, true);
	countLog += insertLog(8, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(8, true, 0.f, oldPositionVec, true);
	countLog += insertLog(9, 0.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(9, false, 30.f, oldPositionVec, true);
	countLog += insertLog(12, 30.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(12, false, 0.f, oldPositionVec, false);
	countLog += insertLog(12, 0.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(12, false, 30.f, oldPositionVec, false);
	countLog += insertLog(15, 30.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(15, true, 0.f, oldPositionVec, false);
	countLog += insertLog(3, 0.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(3, true, 30.f, oldPositionVec, true);
	countLog += insertLog(12, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(12, true, 0.f, oldPositionVec, true);
	countLog += insertLog(13, 0.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(13, true, 30.f, oldPositionVec, true);
	countLog += insertLog(7, 30.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(7, true, 0.f, oldPositionVec, true);
	countLog += insertLog(4, 0.f, oldPositionVec, countLog, true, LogWM);
	oldPositionVec = findNewPos(4, false, 30.f, oldPositionVec, true);
	countLog += insertLog(8, 30.f, oldPositionVec, countLog, false, LogWM);
	oldPositionVec = findNewPos(8, true, 0.f, oldPositionVec, false);
	countLog += insertLog(12, 0.f, oldPositionVec, countLog, true, LogWM);
}



void place_coins_first_level(glm::mat4 *CoinWM) {
	CoinWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(17., 0.7, 28.));
	CoinWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(31.5, 0.7, 1.2));
	CoinWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-33.4, 0.7, -9.7));
	CoinWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12.5, 0.7, 24.));
	CoinWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(39.2, 0.7, -27.5));
}

void place_coins_second_level(glm::mat4 *CoinWM) {
	CoinWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0.7f, -14));
	CoinWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.7, -18));
	CoinWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.7, 2));
	CoinWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.7, 18));
	CoinWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.7, 18));
}

void place_coins_third_level(glm::mat4 *CoinWM) {
	CoinWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0.7f, -16));
	CoinWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0.7, -8));
	CoinWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0.7, 0));
	CoinWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0.7, 12));
	CoinWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(16, 0.7, 14));
}

void place_small_water(glm::mat4 *SmallWaterWM) {
	SmallWaterWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, -6));
	SmallWaterWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, -2));
	SmallWaterWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, 2));
	SmallWaterWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, 6));
	SmallWaterWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, -6));
	SmallWaterWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, -2));
	SmallWaterWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, 2));
	SmallWaterWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, 6));
	SmallWaterWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, -6));
	SmallWaterWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, -6));
	SmallWaterWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, 6));
	SmallWaterWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, -18));
	SmallWaterWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, -14));
	SmallWaterWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, -14));
	SmallWaterWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, -14));
	SmallWaterWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, -14));
	SmallWaterWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, -14));
	SmallWaterWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, -14));
	SmallWaterWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, -10));
	SmallWaterWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0.1, -10));
	SmallWaterWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, -2));
	SmallWaterWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 2));
	SmallWaterWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 6));
	SmallWaterWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 10));
	SmallWaterWM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 14));
	SmallWaterWM[25] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0.1, 18));
	SmallWaterWM[26] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0.1, -2));
	SmallWaterWM[27] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, 6));
	SmallWaterWM[28] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0.1, 14));
	SmallWaterWM[29] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0.1, 14));
	SmallWaterWM[30] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0.1, 14));
	SmallWaterWM[31] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0.1, 14));
	SmallWaterWM[32] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0.1, 14));
	SmallWaterWM[33] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, 14));
	SmallWaterWM[34] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, 18));
	SmallWaterWM[35] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, -6));
	SmallWaterWM[36] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, -2));
	SmallWaterWM[37] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, 2));
	SmallWaterWM[38] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0.1, 6));
	SmallWaterWM[39] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0.1, 6));
	SmallWaterWM[40] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 6));
	SmallWaterWM[41] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 10));
	SmallWaterWM[42] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 14));
	SmallWaterWM[43] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0.1, 18));
}

void place_lily(glm::mat4 *LilyWM) {
	LilyWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-8, 0.2, -8));
}

void place_bridges(glm::mat4 *BridgeWM) {
	BridgeWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 1.0f)), glm::vec3(-1, 0, 6)) *
		glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0, 1, 0));
	BridgeWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 1.0f)), glm::vec3(-9, 0, -10)) *
		glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0, 1, 0));
	BridgeWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(0, 0, -5));
	BridgeWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 1.0f)), glm::vec3(-7, 0, 14)) *
		glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0, 1, 0));
	BridgeWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 1.0f)), glm::vec3(7, 0, 14)) *
		glm::rotate(glm::mat4(1.0), glm::radians(90.0f), glm::vec3(0, 1, 0));
}

void place_clouds(glm::mat4 *Cloud1WM, glm::mat4 *Cloud2WM, glm::mat4 *Cloud3WM) {
	Cloud1WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(9.7f, 8.7f, 3));
	Cloud1WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(30.5, 8.7, -11));
	Cloud1WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-21.7, 8.7, 4.2));
	Cloud1WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-7.5, 8.7, -0.6));
	Cloud1WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(5.15, 8.7, 18.5));

	Cloud2WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18.7f, 8.7f, 0));
	Cloud2WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(24.5, 8.7, -21));
	Cloud2WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18.7, 8.7, -14.2));
	Cloud2WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2.5, 8.7, 15.6));
	Cloud2WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(21.15, 8.7, 28.5));

	Cloud3WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12.7f, 8.7f, 10));
	Cloud3WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(39.5, 8.7, -1));
	Cloud3WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-28.7, 8.7, 0.2));
	Cloud3WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12.5, 8.7, 8.6));
	Cloud3WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18.15, 8.7, 20.5));
}

void place_dirt(glm::mat4 *DirtWM) {
	DirtWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 0));
	DirtWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-2, 0, -2));
	DirtWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, -2));
	DirtWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-2, 0, 0));
	DirtWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(2, 0, 0));
	DirtWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-2, 0, 4));
	DirtWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(2, 0, 4));
	DirtWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(2, 0, 2));
	DirtWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 2));
	DirtWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(4, 0, -2));
	DirtWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, -4));
	DirtWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-4, 0, -4));
	DirtWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-4, 0, 0));
	DirtWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(4, 0, 0));
	DirtWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-4, 0, 4));
	DirtWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(4, 0, -4));
	DirtWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(4, 0, 4));
	DirtWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(0, 0, 4));
	DirtWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-2, 0, -4));
	DirtWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-4, 0, -2));
	DirtWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(2, 0, -4));
	DirtWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(2, 0, -2));
	DirtWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-4, 0, 2));
	DirtWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(-2, 0, 2));
	DirtWM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(4.0f, 1.0f, 4.0f)), glm::vec3(4, 0, 2));
}

void place_tree2(glm::mat4 *Tree2WM) {
	//BORDER TREES
	Tree2WM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -18));
	Tree2WM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, -18));
	Tree2WM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, -18));
	Tree2WM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12, 0, -18));
	Tree2WM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -18));
	Tree2WM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-8, 0, -18));
	Tree2WM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, -18));
	Tree2WM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, -18));
	Tree2WM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, -18));
	Tree2WM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0, -18));
	Tree2WM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0, -18));
	Tree2WM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, -18));
	Tree2WM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, -18));
	Tree2WM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, -18));
	Tree2WM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0, -18));
	Tree2WM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, -18));
	Tree2WM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -18));
	Tree2WM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(16, 0, -18));
	Tree2WM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -18));
	Tree2WM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 18));
	Tree2WM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, 18));
	Tree2WM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, 18));
	Tree2WM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12, 0, 18));
	Tree2WM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, 18));
	Tree2WM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-8, 0, 18));
	Tree2WM[25] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 18));
	Tree2WM[26] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, 18));
	Tree2WM[27] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 18));
	Tree2WM[28] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0, 18));
	Tree2WM[29] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0, 18));
	Tree2WM[30] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, 18));
	Tree2WM[31] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 18));
	Tree2WM[32] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 18));
	Tree2WM[33] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0, 18));
	Tree2WM[34] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, 18));
	Tree2WM[35] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, 18));
	Tree2WM[36] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(16, 0, 18));
	Tree2WM[37] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 18));
	Tree2WM[38] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 16));
	Tree2WM[39] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 14));
	Tree2WM[40] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 12));
	Tree2WM[41] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 10));
	Tree2WM[42] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 8));
	Tree2WM[43] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 6));
	Tree2WM[44] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 4));
	Tree2WM[45] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 2));
	Tree2WM[46] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, 0));
	Tree2WM[47] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -2));
	Tree2WM[48] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -4));
	Tree2WM[49] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -6));
	Tree2WM[50] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -8));
	Tree2WM[51] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -10));
	Tree2WM[52] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -12));
	Tree2WM[53] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -14));
	Tree2WM[54] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-18, 0, -16));
	Tree2WM[55] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 16));
	Tree2WM[56] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 14));
	Tree2WM[57] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 12));
	Tree2WM[58] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 10));
	Tree2WM[59] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 8));
	Tree2WM[60] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 6));
	Tree2WM[61] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 4));
	Tree2WM[62] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 2));
	Tree2WM[63] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, 0));
	Tree2WM[64] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -2));
	Tree2WM[65] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -4));
	Tree2WM[66] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -6));
	Tree2WM[67] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -8));
	Tree2WM[68] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -10));
	Tree2WM[69] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -12));
	Tree2WM[70] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -14));
	Tree2WM[71] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(18, 0, -16));

	//INSIDE TREES
	Tree2WM[72] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, 10));
	Tree2WM[73] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, 10));
	Tree2WM[74] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12, 0, 10));
	Tree2WM[75] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, 12));
	Tree2WM[76] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, 12));
	Tree2WM[77] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12, 0, 12));
	Tree2WM[78] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 10));
	Tree2WM[79] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 12));
	Tree2WM[80] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 14));
	Tree2WM[81] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 16));
	Tree2WM[82] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 14));
	Tree2WM[83] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0, 14));
	Tree2WM[84] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0, 14));
	Tree2WM[85] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, 14));
	Tree2WM[86] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 14));
	Tree2WM[87] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 14));
	Tree2WM[88] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 12));
	Tree2WM[89] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 10));
	Tree2WM[90] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 8));
	Tree2WM[91] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, 6));
	Tree2WM[92] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-12, 0, 6));
	Tree2WM[93] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, 6));
	Tree2WM[94] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-8, 0, 6));
	Tree2WM[95] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 6));
	Tree2WM[96] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, 6));
	Tree2WM[97] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, 6));
	Tree2WM[98] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0, 6));
	Tree2WM[99] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0, 6));
	Tree2WM[100] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2000, -1000, 2000));
	Tree2WM[101] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, 6));
	Tree2WM[102] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 6));
	Tree2WM[103] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 6));
	Tree2WM[104] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0, 8));
	Tree2WM[105] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0, 8));
	Tree2WM[106] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, 8));
	Tree2WM[107] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 8));
	Tree2WM[108] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 8));
	Tree2WM[109] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 10));
	Tree2WM[110] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0, 10));
	Tree2WM[111] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, 10));
	Tree2WM[112] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, 12));
	Tree2WM[113] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, 14));
	Tree2WM[114] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, 16));
	Tree2WM[115] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(16, 0, 8));
	Tree2WM[116] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(16, 0, 10));
	Tree2WM[117] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, 4));
	Tree2WM[118] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, 6));
	Tree2WM[119] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, 0));
	Tree2WM[120] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -2));
	Tree2WM[121] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -4));
	Tree2WM[122] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -6));
	Tree2WM[123] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -8));
	Tree2WM[124] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -10));
	Tree2WM[125] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -12));
	Tree2WM[126] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(14, 0, -14));
	Tree2WM[127] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, -14));
	Tree2WM[128] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0, -14));
	Tree2WM[129] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(12, 0, -14));
	Tree2WM[130] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, -10));
	Tree2WM[131] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, -10));
	Tree2WM[132] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, -10));
	Tree2WM[133] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(10, 0, -10));
	Tree2WM[134] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, -12));
	Tree2WM[135] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, -14));
	Tree2WM[136] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, -16));
	Tree2WM[137] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, -16));
	Tree2WM[138] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, -14));
	Tree2WM[139] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, -12));
	Tree2WM[140] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, -16));
	Tree2WM[141] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, -14));
	Tree2WM[142] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, -12));
	Tree2WM[143] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, -6));
	Tree2WM[144] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-4, 0, -6));
	Tree2WM[145] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-2, 0, -6));
	Tree2WM[146] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(0, 0, -6));
	Tree2WM[147] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(2, 0, -6));
	Tree2WM[148] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(4, 0, -6));
	Tree2WM[149] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, -6));
	Tree2WM[150] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, -4));
	Tree2WM[151] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, -2));
	Tree2WM[152] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 0));
	Tree2WM[153] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 2));
	Tree2WM[154] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(6, 0, 4));
	Tree2WM[155] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, -2));
	Tree2WM[156] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 0));
	Tree2WM[157] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 2));
	Tree2WM[158] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(8, 0, 4));
	Tree2WM[159] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -14));
	Tree2WM[160] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -12));
	Tree2WM[161] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -10));
	Tree2WM[162] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -8));
	Tree2WM[163] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -6));
	Tree2WM[164] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -4));
	Tree2WM[165] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-10, 0, -2));
	Tree2WM[166] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-8, 0, -2));
	Tree2WM[167] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, -2));
	Tree2WM[168] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 0));
	Tree2WM[169] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 2));
	Tree2WM[170] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-6, 0, 4));
	Tree2WM[171] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, -8));
	Tree2WM[172] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, -6));
	Tree2WM[173] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, -4));
	Tree2WM[174] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, -2));
	Tree2WM[175] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-16, 0, 0));
	Tree2WM[176] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, -6));
	Tree2WM[177] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, -4));
	Tree2WM[178] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, -2));
	Tree2WM[179] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec3(-14, 0, 0));
}

void place_spikes(glm::mat4 *SpikeWM) {
	SpikeWM[0] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-6, 0, 8));
	SpikeWM[1] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-5, 0, 8));
	SpikeWM[2] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-4, 0, 8));
	SpikeWM[3] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-4, 0, 7));
	SpikeWM[4] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-4, 0, 6));
	SpikeWM[5] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(1, 0, 6));
	SpikeWM[6] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(2, 0, 6));
	SpikeWM[7] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(7, 0, 8));
	SpikeWM[8] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(8, 0, 8));
	SpikeWM[9] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(6, 0, 2));
	SpikeWM[10] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(6, 0, 3));
	SpikeWM[11] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-8, 0, 1));
	SpikeWM[12] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-7, 0, 1));
	SpikeWM[13] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-6, 0, 1));
	SpikeWM[14] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-5, 0, 1));
	SpikeWM[15] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-4, 0, 5));
	SpikeWM[16] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-1, 0, -1));
	SpikeWM[17] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(0, 0, -1));
	SpikeWM[18] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(1, 0, -1));
	SpikeWM[19] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-1, 0, 1));
	SpikeWM[20] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(0, 0, 1));
	SpikeWM[21] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(1, 0, 1));
	SpikeWM[22] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-1, 0, 0));
	SpikeWM[23] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-8, 0, -7));
	SpikeWM[24] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-8, 0, -6));
	SpikeWM[25] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-8, 0, -5));
	SpikeWM[26] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-6, 0, -7));
	SpikeWM[27] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-6, 0, -6));
	SpikeWM[28] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(-6, 0, -5));
	SpikeWM[29] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(6, 0, -3));
	SpikeWM[30] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(6, 0, -2));
	SpikeWM[31] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(6, 0, -1));
	SpikeWM[32] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(6, 0, 0));
	SpikeWM[33] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(5, 0, -4));
	SpikeWM[34] = glm::translate(glm::scale(glm::mat4(1), glm::vec3(2.0f, 1.5f, 2.0f)), glm::vec3(5, 0, -3));
}