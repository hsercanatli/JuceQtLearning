#include "GainController.h"

void GainController::updateGain(qreal gain) {
    mGainModel->updateGain(gain);
}
void GainController::updateBypass(bool bypass) {
    mGainModel->updateBypass(bypass);
}
